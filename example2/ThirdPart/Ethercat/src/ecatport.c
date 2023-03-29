/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
\addtogroup EL9800_HW EL9800 Platform (Serial ESC Access)
@{
*/

/**
\file    el9800hw.c
\author EthercatSSC@beckhoff.com
\brief Implementation
Hardware access implementation for EL9800 onboard PIC18/PIC24 connected via SPI to ESC

\version 5.12

<br>Changes to version V5.11:<br>
V5.12 EL9800 1: improve the SPI access<br>
<br>Changes to version V5.10:<br>
V5.11 ECAT10: change PROTO handling to prevent compiler errors<br>
V5.11 EL9800 2: change PDI access test to 32Bit ESC access and reset AL Event mask after test even if AL Event is not enabled<br>
<br>Changes to version V5.01:<br>
V5.10 ESC5: Add missing swapping<br>
V5.10 HW3: Sync1 Isr added<br>
V5.10 HW4: Add volatile directive for direct ESC DWORD/WORD/BYTE access<br>
           Add missing swapping in mcihw.c<br>
           Add "volatile" directive vor dummy variables in enable and disable SyncManger functions<br>
           Add missing swapping in EL9800hw files<br>
<br>Changes to version V5.0:<br>
V5.01 HW1: Invalid ESC access function was used<br>
<br>Changes to version V4.40:<br>
V5.0 ESC4: Save SM disable/Enable. Operation may be pending due to frame handling.<br>
<br>Changes to version V4.30:<br>
V4.40 : File renamed from spihw.c to el9800hw.c<br>
<br>Changes to version V4.20:<br>
V4.30 ESM: if mailbox Syncmanger is disabled and bMbxRunning is true the SyncManger settings need to be revalidate<br>
V4.30 EL9800: EL9800_x hardware initialization is moved to el9800.c<br>
V4.30 SYNC: change synchronisation control function. Add usage of 0x1C32:12 [SM missed counter].<br>
Calculate bus cycle time (0x1C32:02 ; 0x1C33:02) CalcSMCycleTime()<br>
V4.30 PDO: rename PDO specific functions (COE_xxMapping -> PDO_xxMapping and COE_Application -> ECAT_Application)<br>
V4.30 ESC: change requested address in GetInterruptRegister() to prevent acknowledge events.<br>
(e.g. reading an SM config register acknowledge SM change event)<br>
GENERIC: renamed several variables to identify used SPI if multiple interfaces are available<br>
V4.20 MBX 1: Add Mailbox queue support<br>
V4.20 SPI 1: include SPI RxBuffer dummy read<br>
V4.20 DC 1: Add Sync0 Handling<br>
V4.20 PIC24: Add EL9800_4 (PIC24) required source code<br>
V4.08 ECAT 3: The AlStatusCode is changed as parameter of the function AL_ControlInd<br>
<br>Changes to version V4.02:<br>
V4.03 SPI 1: In ISR_GetInterruptRegister the NOP-command should be used.<br>
<br>Changes to version V4.01:<br>
V4.02 SPI 1: In HW_OutputMapping the variable u16OldTimer shall not be set,<br>
             otherwise the watchdog might exceed too early.<br>
<br>Changes to version V4.00:<br>
V4.01 SPI 1: DI and DO were changed (DI is now an input for the uC, DO is now an output for the uC)<br>
V4.01 SPI 2: The SPI has to operate with Late-Sample = FALSE on the Eva-Board<br>
<br>Changes to version V3.20:<br>
V4.00 ECAT 1: The handling of the Sync Manager Parameter was included according to<br>
              the EtherCAT Guidelines and Protocol Enhancements Specification<br>
V4.00 APPL 1: The watchdog checking should be done by a microcontroller<br>
                 timer because the watchdog trigger of the ESC will be reset too<br>
                 if only a part of the sync manager data is written<br>
V4.00 APPL 4: The EEPROM access through the ESC is added

*/


/*--------------------------------------------------------------------------------------
------
------    Includes
------
--------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "ecatslv.h"


#define    _EL9800HW_ 1
#include "ecatport.h"
#undef    _EL9800HW_
/*remove definition of _EL9800HW_ (#ifdef is used in el9800hw.h)*/

#include "ecatappl.h"
#include "md_ethercat.h"
#include "bsp_spi.h"
#include "bsp_sys.h"
#include "bsp_systick.h"
#include "bsp_time.h"
/*--------------------------------------------------------------------------------------
------
------    internal Types and Defines
------
--------------------------------------------------------------------------------------*/

typedef union
{
    unsigned short    Word;
    unsigned char    Byte[2];
} UBYTETOWORD;

typedef union 
{
    UINT8           Byte[2];
    UINT16          Word;
}
UALEVENT;

/*-----------------------------------------------------------------------------------------
------
------    SPI defines/macros
------
-----------------------------------------------------------------------------------------*/
#define RxTxSpiData         spi_data_rw
#define SELECT_SPI          gpio_bit_reset(GPIOE, GPIO_PIN_4);  
#define DESELECT_SPI        gpio_bit_set(GPIOE, GPIO_PIN_4);
/*-----------------------------------------------------------------------------------------
------
------    Global Interrupt setting
------
-----------------------------------------------------------------------------------------*/
#define DISABLE_GLOBAL_INT      __disable_irq()			
#define ENABLE_GLOBAL_INT       __enable_irq()
/*-----------------------------------------------------------------------------------------
------
------    ESC Interrupt
------
-----------------------------------------------------------------------------------------*/
#define INIT_ESC_INT        ethercat_pdi_init()
#define ACK_ESC_INT         exti_interrupt_flag_clear(EXTI_3);
#define EscIsr              EXTI3_IRQHandler

/*-----------------------------------------------------------------------------------------
------
------    SYNC0 Interrupt
------
-----------------------------------------------------------------------------------------*/
#define INIT_SYNC0_INT     ethercat_sync0_init()
#define ACK_SYNC0_INT      exti_interrupt_flag_clear(EXTI_13)
#define Sync0Isr           EXTI10_15_IRQHandler

#define INIT_SYNC1_INT     ethercat_sync1_init()
#define ACK_SYNC1_INT      exti_interrupt_flag_clear(EXTI_1)
#define Sync1Isr           EXTI1_IRQHandler
/*-----------------------------------------------------------------------------------------
------
------    Hardware timer
------
-----------------------------------------------------------------------------------------*/
#define INIT_ECAT_TIMER    ethercat_timer_init()
#define ethercat_timer_isr TIMER4_IRQHandler
#define ACK_TIMER_INT      timer_interrupt_flag_clear(TIMER4, TIMER_INT_UP)
/*-----------------------------------------------------------------------------------------
------
------    Configuration Bits
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    LED defines
------
-----------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
------
------    internal Variables
------
--------------------------------------------------------------------------------------*/
UALEVENT         EscALEvent;            //contains the content of the ALEvent register (0x220), this variable is updated on each Access to the Esc
/*--------------------------------------------------------------------------------------
------
------    internal functions
------
--------------------------------------------------------------------------------------*/


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Command    ESC_WR performs a write access; ESC_RD performs a read access.

 \brief The function addresses the EtherCAT ASIC via SPI for a following SPI access.
*////////////////////////////////////////////////////////////////////////////////////////
static void AddressingEsc( UINT16 Address, UINT8 Command )
{
    VARVOLATILE UBYTETOWORD tmp;
    tmp.Word = ( Address << 3 ) | Command;



    /* select the SPI */
    SELECT_SPI;

    /* send the first address/command byte to the ESC 
       receive the first AL Event Byte*/
    EscALEvent.Byte[0] = RxTxSpiData(tmp.Byte[1]);

    EscALEvent.Byte[1] = RxTxSpiData(tmp.Byte[0]);
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief  The function operates a SPI access without addressing.

        The first two bytes of an access to the EtherCAT ASIC always deliver the AL_Event register (0x220).
        It will be saved in the global "EscALEvent"
*////////////////////////////////////////////////////////////////////////////////////////
static void GetInterruptRegister(void)
{
    // VARVOLATILE UINT8            dummy;
    // HW_EscRead((MEM_ADDR *)&dummy, 0, 1);

    DISABLE_GLOBAL_INT;
    SELECT_SPI;
	
	 HW_EscReadIsr((MEM_ADDR *)&EscALEvent.Word, 0x220, 2);
	/* if the SPI transmission rate is higher than 15 MBaud, the Busy detection shall be
       done here */
	
    DESELECT_SPI;
    ENABLE_GLOBAL_INT;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief  The function operates a SPI access without addressing.
        Shall be implemented if interrupts are supported else this function is equal to "GetInterruptRegsiter()"

        The first two bytes of an access to the EtherCAT ASIC always deliver the AL_Event register (0x220).
        It will be saved in the global "EscALEvent"
*////////////////////////////////////////////////////////////////////////////////////////
static void ISR_GetInterruptRegister(void)
{
    DESELECT_SPI;
    // VARVOLATILE UINT8 dummy;
    // HW_EscReadIsr((MEM_ADDR *)&dummy, 0, 1);
    /* select the SPI */
    SELECT_SPI;

		 HW_EscReadIsr((MEM_ADDR *)&EscALEvent.Word, 0x220, 2);

  /* if the SPI transmission rate is higher than 15 MBaud, the Busy detection shall be
       done here */

    DESELECT_SPI;

}
/*ECATCHANGE_END(V5.12) EL9800 1*/

/*--------------------------------------------------------------------------------------
------
------    exported hardware access functions
------
--------------------------------------------------------------------------------------*/


/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0 if initialization was successful

 \brief    This function intialize the Process Data Interface (PDI) and the host controller.
*////////////////////////////////////////////////////////////////////////////////////////
UINT8 HW_Init(void)
{
    UINT32 intMask;
    sysTick_init();
    nvic_configuration();	
    ethercat_gpio_init();
    bsp_spi3_init();
    do
    {
        intMask = 0x93;
        HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
        intMask = 0;
        HW_EscReadDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
    } while (intMask != 0x93);

    intMask = 0x00;

    HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);

    INIT_ESC_INT;
    ENABLE_ESC_INT();

    INIT_SYNC0_INT;
    INIT_SYNC1_INT;



    INIT_ECAT_TIMER;


    /* enable all interrupts */
    ENABLE_GLOBAL_INT;
    delay_ms(2000);
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    This function shall be implemented if hardware resources need to be release
        when the sample application stops
*////////////////////////////////////////////////////////////////////////////////////////
void HW_Release(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    first two Bytes of ALEvent register (0x220)

 \brief  This function gets the current content of ALEvent register
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 HW_GetALEventRegister(void)
{
    GetInterruptRegister();
    return EscALEvent.Word;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    first two Bytes of ALEvent register (0x220)

 \brief  The SPI PDI requires an extra ESC read access functions from interrupts service routines.
        The behaviour is equal to "HW_GetALEventRegister()"
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 HW_GetALEventRegister_Isr(void)
{
     ISR_GetInterruptRegister();
    return EscALEvent.Word;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param RunLed            desired EtherCAT Run led state
 \param ErrLed            desired EtherCAT Error led state

  \brief    This function updates the EtherCAT run and error led
*////////////////////////////////////////////////////////////////////////////////////////
void HW_SetLed(UINT8 RunLed,UINT8 ErrLed)
{
}

/*ECATCHANGE_START(V5.12) EL9800 1*/
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves read data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

 \brief  This function operates the SPI read access to the EtherCAT ASIC.
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscRead( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    /* HBu 24.01.06: if the SPI will be read by an interrupt routine too the
                     mailbox reading may be interrupted but an interrupted
                     reading will remain in a SPI transmission fault that will
                     reset the internal Sync Manager status. Therefore the reading
                     will be divided in 1-byte reads with disabled interrupt */
    UINT16 i = Len;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* loop for all bytes to be read */
    while ( i-- > 0 )
    {
/*ECATCHANGE_START(V5.12) EL9800 1*/
        /* the reading of data from the ESC can be interrupted by the
           AL Event ISR, in that case the address has to be reinitialized,
           in that case the status flag will indicate an error because
           the reading operation was interrupted without setting the last
           sent byte to 0xFF */
        DISABLE_GLOBAL_INT;
/*ECATCHANGE_END(V5.12) EL9800 1*/

         AddressingEsc( Address, ESC_RD );

         /*Each Byte will be read with a new addressing phase so the out data is 0xFF*/
         *pTmpData = RxTxSpiData(0xFF);
         
         pTmpData++;

/*ECATCHANGE_START(V5.12) EL9800 1*/        

        /* there has to be at least 15 ns + CLK/2 after the transmission is finished
           before the SPI1_SEL signal shall be 1 */
        DESELECT_SPI

        ENABLE_GLOBAL_INT;
/*ECATCHANGE_END(V5.12) EL9800 1*/

        /* next address */
        Address++;

    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves read data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

\brief  The SPI PDI requires an extra ESC read access functions from interrupts service routines.
        The behaviour is equal to "HW_EscRead()"
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    UINT8 data = 0;

   UINT8 *pTmpData = (UINT8 *)pData;

    /* send the address and command to the ESC */
     AddressingEsc( Address, ESC_RD );

    /* loop for all bytes to be read */
    while ( i-- > 0 )
    {
        if ( i == 0 )
        {
            /* when reading the last byte the DI pin shall be 1 */
            data = 0xFF;
        }

        *pTmpData = RxTxSpiData(data);

        pTmpData++;
    }
    
    /* there has to be at least 15 ns + CLK/2 after the transmission is finished
       before the SPI1_SEL signal shall be 1 */
    DESELECT_SPI
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves write data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

  \brief  This function operates the SPI write access to the EtherCAT ASIC.
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    VARVOLATILE UINT8 dummy;

    UINT8 *pTmpData = (UINT8 *)pData;

    /* loop for all bytes to be written */
    while ( i-- > 0 )
    {
/*ECATCHANGE_START(V5.12) EL9800 1*/
        /* the reading of data from the ESC can be interrupted by the
           AL Event ISR, so every byte will be written separate */
        DISABLE_GLOBAL_INT;
/*ECATCHANGE_END(V5.12) EL9800 1*/

        /* HBu 24.01.06: wrong parameter ESC_RD */
         AddressingEsc( Address, ESC_WR );

         dummy = RxTxSpiData(*pTmpData);
         pTmpData++;
        /* there has to be at least 15 ns + CLK/2 after the transmission is finished
           before the SPI1_SEL signal shall be 1 */

        DESELECT_SPI


        ENABLE_GLOBAL_INT;
/*ECATCHANGE_END(V5.12) EL9800 1*/

        /* next address */
        Address++;


    }
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves write data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

 \brief  The SPI PDI requires an extra ESC write access functions from interrupts service routines.
        The behaviour is equal to "HW_EscWrite()"
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    VARVOLATILE UINT16 dummy;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* send the address and command to the ESC */
     AddressingEsc( Address, ESC_WR );
     /* loop for all bytes to be written */
    while ( i-- > 0 )
    {

         dummy = RxTxSpiData(*pTmpData);
         pTmpData++;
    }

    /* there has to be at least 15 ns + CLK/2 after the transmission is finished
       before the SPI1_SEL signal shall be 1 */
    DESELECT_SPI
}
/*ECATCHANGE_END(V5.12) EL9800 1*/


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    This function resets the hardware
*////////////////////////////////////////////////////////////////////////////////////////

void HW_RestartTarget(void)
{
}



/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    Interrupt service routine for the PDI interrupt from the EtherCAT Slave Controller
*////////////////////////////////////////////////////////////////////////////////////////

void EscIsr(void)
{
     PDI_Isr();

    /* reset the interrupt flag */
    ACK_ESC_INT;

}



/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    Interrupt service routine for the interrupts from SYNC0
*////////////////////////////////////////////////////////////////////////////////////////
void Sync0Isr(void)
{
    Sync0_Isr();

    /* reset the interrupt flag */
    ACK_SYNC0_INT;
}
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    Interrupt service routine for the interrupts from SYNC1
*////////////////////////////////////////////////////////////////////////////////////////
void Sync1Isr(void)
{
    Sync1_Isr();

    /* reset the interrupt flag */
    ACK_SYNC1_INT;
}

void ethercat_timer_isr(void)
{
    ECAT_CheckTimer();
    ACK_TIMER_INT;
}
/** @} */





