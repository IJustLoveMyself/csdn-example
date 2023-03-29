/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
* \addtogroup myapp myapp
* @{
*/

/**
\file myappObjects
\author ET9300Utilities.ApplicationHandler (Version 1.5.0.0) | EthercatSSC@beckhoff.com

\brief myapp specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_MYAPP_) && (_MYAPP_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1600 : RPDO
******************************************************************************/
/**
* \addtogroup 0x1600 0x1600 | RPDO
* @{
* \brief Object 0x1600 (RPDO) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - SUB1<br>
* SubIndex 2 - SUB2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1600[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - SUB1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex2 - SUB2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1600[] = "RPDO\000"
"SUB1\000"
"SUB2\000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1600;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1600 RPDO0x1600
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={2,0x70010120,0x70010220}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : TPDO
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | TPDO
* @{
* \brief Object 0x1A00 (TPDO) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - SUB1<br>
* SubIndex 2 - SUB2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 - SUB1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex2 - SUB2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "TPDO\000"
"SUB1\000"
"SUB2\000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 TPDO0x1A00
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={2,0x60010120,0x60010220}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : SyncManager 2 assignment
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | SyncManager 2 assignment
* @{
* \brief Object 0x1C12 (SyncManager 2 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "SyncManager 2 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={1,{0x1600}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : SyncManager 3 assignment
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | SyncManager 3 assignment
* @{
* \brief Object 0x1C13 (SyncManager 3 assignment) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "SyncManager 3 assignment\000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={1,{0x1A00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x2002 : Res1
******************************************************************************/
/**
* \addtogroup 0x2002 0x2002 | Res1
* @{
* \brief Object 0x2002 (Res1) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2002 = { DEFTYPE_UNSIGNED8 , 0x08 , ACCESS_READ | OBJACCESS_TXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2002[] = "Res1\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT8 Res10x2002
#if defined(_MYAPP_) && (_MYAPP_ == 1)
= 0x00
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x2003 : Res2
******************************************************************************/
/**
* \addtogroup 0x2003 0x2003 | Res2
* @{
* \brief Object 0x2003 (Res2) definition
*/
#ifdef _OBJD_
/**
* \brief Entry description
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM sEntryDesc0x2003 = { DEFTYPE_UNSIGNED8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING };
/**
* \brief Object name
*/
OBJCONST UCHAR OBJMEM aName0x2003[] = "Res2\000\377";
#endif //#ifdef _OBJD_

/**
* \brief Object variable
*/
PROTO UINT8 Res20x2003
#if defined(_MYAPP_) && (_MYAPP_ == 1)
= 0x00
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : Digtal input
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | Digtal input
* @{
* \brief Object 0x6000 (Digtal input) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x08 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "Digtal input\000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT8 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 DigtalInput0x6000
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={1,{0x00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6001 : SENDDATA
******************************************************************************/
/**
* \addtogroup 0x6001 0x6001 | SENDDATA
* @{
* \brief Object 0x6001 (SENDDATA) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - SEND1<br>
* SubIndex 2 - SEND2<br>
* SubIndex 3 - SEND3<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6001[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - SEND1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - SEND2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex3 - SEND3 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6001[] = "SENDDATA\000"
"SEND1\000"
"SEND2\000"
"SEND3\000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SEND1; /* Subindex1 - SEND1 */
UINT32 SEND2; /* Subindex2 - SEND2 */
UINT32 SEND3; /* Subindex3 - SEND3 */
} OBJ_STRUCT_PACKED_END
TOBJ6001;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6001 SENDDATA0x6001
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={3,0x00000000,0x00000000,0x00000000}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7000 : LED
******************************************************************************/
/**
* \addtogroup 0x7000 0x7000 | LED
* @{
* \brief Object 0x7000 (LED) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x08 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x7000[] = "LED\000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT8 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ7000;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7000 LED0x7000
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={1,{0x00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7001 : RECVDATA
******************************************************************************/
/**
* \addtogroup 0x7001 0x7001 | RECVDATA
* @{
* \brief Object 0x7001 (RECVDATA) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - RECV1<br>
* SubIndex 2 - RECV2<br>
* SubIndex 3 - RECV3<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7001[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - RECV1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - RECV2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex3 - RECV3 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7001[] = "RECVDATA\000"
"RECV1\000"
"RECV2\000"
"RECV3\000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 RECV1; /* Subindex1 - RECV1 */
UINT32 RECV2; /* Subindex2 - RECV2 */
UINT32 RECV3; /* Subindex3 - RECV3 */
} OBJ_STRUCT_PACKED_END
TOBJ7001;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7001 RECVDATA0x7001
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={3,0x00000000,0x00000000,0x00000000}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0xF000 : Modular Device Profile
******************************************************************************/
/**
* \addtogroup 0xF000 0xF000 | Modular Device Profile
* @{
* \brief Object 0xF000 (Modular Device Profile) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Index distance <br>
* SubIndex 2 - Maximum number of modules <br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0xF000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }, /* Subindex1 - Index distance  */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ }}; /* Subindex2 - Maximum number of modules  */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0xF000[] = "Modular Device Profile\000"
"Index distance \000"
"Maximum number of modules \000\377";
#endif //#ifdef _OBJD_

#ifndef _MYAPP_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 IndexDistance; /* Subindex1 - Index distance  */
UINT16 MaximumNumberOfModules; /* Subindex2 - Maximum number of modules  */
} OBJ_STRUCT_PACKED_END
TOBJF000;
#endif //#ifndef _MYAPP_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJF000 ModularDeviceProfile0xF000
#if defined(_MYAPP_) && (_MYAPP_ == 1)
={2,0x0010,0x0003}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1600 */
{NULL , NULL ,  0x1600 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1600 , aName0x1600 , &RPDO0x1600 , NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &TPDO0x1A00 , NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign , NULL , NULL , 0x0000 },
/* Object 0x2002 */
{NULL , NULL ,  0x2002 , {DEFTYPE_UNSIGNED8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2002 , aName0x2002 , &Res10x2002 , NULL , NULL , 0x0000 },
/* Object 0x2003 */
{NULL , NULL ,  0x2003 , {DEFTYPE_UNSIGNED8 , 0 | (OBJCODE_VAR << 8)} , &sEntryDesc0x2003 , aName0x2003 , &Res20x2003 , NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_UNSIGNED8 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x6000 , aName0x6000 , &DigtalInput0x6000 , NULL , NULL , 0x0000 },
/* Object 0x6001 */
{NULL , NULL ,  0x6001 , {DEFTYPE_RECORD , 3 | (OBJCODE_REC << 8)} , asEntryDesc0x6001 , aName0x6001 , &SENDDATA0x6001 , NULL , NULL , 0x0000 },
/* Object 0x7000 */
{NULL , NULL ,  0x7000 , {DEFTYPE_UNSIGNED8 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x7000 , aName0x7000 , &LED0x7000 , NULL , NULL , 0x0000 },
/* Object 0x7001 */
{NULL , NULL ,  0x7001 , {DEFTYPE_RECORD , 3 | (OBJCODE_REC << 8)} , asEntryDesc0x7001 , aName0x7001 , &RECVDATA0x7001 , NULL , NULL , 0x0000 },
/* Object 0xF000 */
{NULL , NULL ,  0xF000 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0xF000 , aName0xF000 , &ModularDeviceProfile0xF000 , NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _MYAPP_OBJECTS_H_
