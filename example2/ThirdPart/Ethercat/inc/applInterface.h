/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
\addtogroup EcatAppl EtherCAT application
@{
*/

/**
\file applInterface.h
\author EthercatSSC@beckhoff.com
\brief Definition of the application interface functions

\version 5.12

<br>Changes to version V5.11:<br>
V5.12 APPL1: add optional application function called from the main loop (after mbx and esm are executed)<br>
V5.12 EEPROM3: implement a store EEPROM timeout handler<br>
V5.12 EOE1: move icmp sample to the sampleappl,add EoE application interface functions<br>
V5.12 FOE1: update new interface,move the FoE sample to sampleappl,add FoE application callback functions<br>
<br>Changes to version - :<br>
V5.10.1 : Start file change log
*/

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/


#ifndef _APPL_INTERFACE_H_
#define _APPL_INTERFACE_H_

#include "ecat_def.h"
#include <stdlib.h>
#include <string.h>
#include "esc.h"
#include "ecatslv.h"
#include "objdef.h"
#include "ecatappl.h"





#endif /*#ifndef _APPL_INTERFACE_H_*/

#if defined(_APPL_INTERFACE_) && (_APPL_INTERFACE_ == 1)
   #define PROTO
#else
    #define PROTO extern
#endif

/*-----------------------------------------------------------------------------------------
------
------    Function pointer which are used to call optional functions from the application
------
-----------------------------------------------------------------------------------------*/






/*ECATCHANGE_START(V5.12) APPL1*/
/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function is called by the SSC from the main loop
*////////////////////////////////////////////////////////////////////////////////////////
PROTO void(*pAPPL_MainLoop)();
/*ECATCHANGE_END(V5.12) APPL1*/

/*-----------------------------------------------------------------------------------------
------
------    Functions provided by the SSC to be called from the application
------
-----------------------------------------------------------------------------------------*/


/////////////////////////////////////////////////////////////////////////////////////////
/**
\return   0 if successful or greater 0 in case of an error

\brief    Initialize the generic slave stack.
\brief    This function should be called after the platform including operating system and
\brief    ESC is ready to use.
*////////////////////////////////////////////////////////////////////////////////////////
PROTO UINT16 MainInit(void);


/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function handles the low priority function like EtherCAT state machine
\brief    handling, mailbox protocols and if no synchronization is enabled also the
\brief    application.
\brief    This function shall be called cyclically from the application.
*////////////////////////////////////////////////////////////////////////////////////////
PROTO void MainLoop(void);


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param    alStatus       requested AL Status 
\param    alStatusCode   requested AL Status Code

\brief    This function shall be called by the application to trigger state transition in case
\brief    of an application error or to complete a pending transition.
\brief    If the function was called due to an error it shall be again if the error is gone.
\brief    NOTE: state requests to a higher state than the current state are not allowed.
*////////////////////////////////////////////////////////////////////////////////////////
PROTO void ECAT_StateChange(UINT8 alStatus, UINT16 alStatusCode);



#undef PROTO
