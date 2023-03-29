/*
 * @******************************************************************************: 
 * @Description: 
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2023-03-29 10:07:52
 * @LastEditors: gxf
 * @LastEditTime: 2023-03-29 11:43:21
 * @==============================================================================: 
 */
/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
 * \addtogroup myapp myapp
 * @{
 */

/**
\file myapp.h
\brief myapp function prototypes and defines

\version 1.0.0.11
 */

 
 #ifndef _MYAPP_H_
#define _MYAPP_H_


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "ecatappl.h"

/*-----------------------------------------------------------------------------------------
------
------    Defines and Types
------
-----------------------------------------------------------------------------------------*/

#endif //_MYAPP_H_

//include custom application object dictionary 
#include "myappObjects.h"


#if defined(_MYAPP_) && (_MYAPP_ == 1)
    #define PROTO
#else
    #define PROTO extern
#endif


PROTO void APPL_Application(void);
#if EXPLICIT_DEVICE_ID
PROTO UINT16 APPL_GetDeviceID(void);
#endif

typedef struct{
  unsigned int  data1;
  unsigned int  data2;
} __attribute__((__packed__)) _tpdo1A00_t;

typedef struct{
  unsigned int  data1;
  unsigned int  data2;
} __attribute__((__packed__)) _rpdo1600_t;

PROTO void   APPL_AckErrorInd(UINT16 stateTrans);
PROTO UINT16 APPL_StartMailboxHandler(void);
PROTO UINT16 APPL_StopMailboxHandler(void);
PROTO UINT16 APPL_StartInputHandler(UINT16 *pIntMask);
PROTO UINT16 APPL_StopInputHandler(void);
PROTO UINT16 APPL_StartOutputHandler(void);
PROTO UINT16 APPL_StopOutputHandler(void);

PROTO UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize);
PROTO void APPL_InputMapping(UINT16* pData);
PROTO void APPL_OutputMapping(UINT16* pData);

#undef PROTO
/** @}*/

