/*! \file ice_base_type.h
\brief ice_base_type.h document.
*/

#ifndef __ICE_BASE_TYPE_H__
#define __ICE_BASE_TYPE_H__

#if !defined _CRT_SECURE_NO_DEPRECATE && _MSC_VER > 1300
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>



#ifdef __cplusplus
extern "C"{
#endif


//----------------------------------------------
// EXPORTS and IMPORTS definition
//----------------------------------------------
#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined ICE_API_EXPORTS
    #define ICE_EXPORTS __declspec(dllexport)
#else
    #define ICE_EXPORTS
#endif


//----------------------------------------------
// The common data type, will be used in the whole project.
//----------------------------------------------

typedef unsigned char           ICE_U8;
typedef unsigned short          ICE_U16;
typedef unsigned int            ICE_U32;

typedef char                    ICE_S8;
typedef short                   ICE_S16;
typedef int                     ICE_S32;
typedef float 					ICE_FLOAT;

#ifndef _M_IX86
    typedef unsigned long long  ICE_U64;
    typedef long long           ICE_S64;
#else
    typedef __int64             ICE_U64;
    typedef __int64             ICE_S64;
#endif

typedef char                    ICE_CHAR;
typedef void*                   ICE_HANDLE;


//----------------------------------------------
// constant definition
//----------------------------------------------

typedef enum
{
    ICE_FALSE = 0,
    ICE_TRUE  = 1,
} ICE_BOOL;

#ifndef NULL
    #define NULL    0L
#endif

#define ICE_NULL     0L
#define ICE_SUCCESS  0
#define ICE_FAILURE  (-1)


#define ICE_MODULE_DATLEN	1024
//! \ingroup group_core
//! object definition
typedef struct
{
	ICE_U8 auBuffer[ICE_MODULE_DATLEN];				//!< Buffer
} ICE_OBJ;

//! \ingroup group_core
//! status definition
typedef enum
{
	ICE_STATUS_ERROR = 0,                           //!< Error
	ICE_STATUS_OK    = 1,                           //!< Ok
	ICE_STATUS_SKIP  = 2,                           //!< Skip
} ICE_STATUS_E;

//! \ingroup group_core
//! error code definition
typedef enum
{
	ICE_ERR_NULL_PTR       = 0xA00A0001,            //!< null pointer
	ICE_ERR_ILLEGAL_PARAM  = 0xA00A0002,            //!< illegal param
	ICE_ERR_INVALID_ADDR   = 0xA00A0003,            //!< invalid address
	ICE_ERR_NOT_CONFIG     = 0xA00A0004,            //!< not config
	ICE_ERR_NO_LISENCE     = 0xA00A0005,            //!< no valid liceence
	ICE_ERR_INVALID_IMAGE  = 0xA00A0006,            //!< invalid image
} ICE_ERROR_CODE_E;

//! \ingroup group_core
//! system time definition
typedef struct 
{
	ICE_U16 u16Year;								//!< year
	ICE_U16 u16Month;								//!< month
	ICE_U16 u16DayOfWeek;							//!< week
	ICE_U16 u16Day;									//!< day
	ICE_U16 u16Hour;								//!< hour
	ICE_U16 u16Minute;								//!< minute
	ICE_U16 u16Second;								//!< second
	ICE_U16 u16Milliseconds;						//!< milliseconds
}ICE_SYSTEMTIME_S;

//! \ingroup group_core
//! pixel format of the Yuv image 
typedef enum
{
	ICE_YUV_PLANAR_422 = 0x01,                    //!<  YYY UUU VVV	
	ICE_YUV_SEMIPLANAR_422 = 0x02                 //!<  [Y0 Y1 Y2] [U0V0 U1V1 V2V2] 
} ICE_YUV_FORMAT_E;

//! \ingroup group_core
//! point definition
typedef struct
{
	ICE_S16 s16X;               //!< x
	ICE_S16 s16Y;               //!< y
} ICE_POINT_S;

//! \ingroup group_core
//! line definition
typedef struct
{
	ICE_POINT_S stPStart;       //!< start point
	ICE_POINT_S stPEnd;         //!< end point
} ICE_LINE_S;

//! \ingroup group_core
//! rect definition
typedef struct
{
	ICE_S16 s16Left;            //!< letf x
	ICE_S16 s16Top;             //!< top y
	ICE_S16 s16Right;           //!< right x
	ICE_S16 s16Bottom;          //!< bottom y
} ICE_RECT_S;

#define  ICE_MAX_POLYGON_NUM 32
//! \ingroup group_core
//! polygon definition
typedef struct
{
	ICE_S32 s32Num;             //!< polygon point num
	ICE_POINT_S astPoints[ICE_MAX_POLYGON_NUM]; //!< polygon point array
} ICE_POLYGON_S;

//! \ingroup group_core
//! quadrangle definition
typedef struct
{
	ICE_POINT_S astPoints[4];   //!< quadrangle point array
} ICE_QUADRANGLE_S;

//! \ingroup group_core
//! BRG pixel definition
typedef struct
{
	ICE_U8 u8B;                 //!< blue
	ICE_U8 u8G;                 //!< green
	ICE_U8 u8R;                 //!< red
} ICE_PIXEL_S;

//! \ingroup group_core
//! gray image definition
typedef struct
{
	ICE_S32 s32Width;           //!< width of the image
	ICE_S32 s32Height;          //!< height of the image
	ICE_U8 *pu8Data;            //!< data buffer of the image
} ICE_GRAY_IMAGE_S;

//! \ingroup group_core
//! yuv422p image definition
typedef struct
{
	ICE_YUV_FORMAT_E  enPixelFormat;     //!< pixel format of the image()
	ICE_S32 s32Width;					 //!< width of the image
	ICE_S32 s32Height;					 //!< height of the image
	ICE_U8 *pu8YData;					 //!< Y data buffer of the image
	ICE_U8 *pu8UData;					 //!< U data buffer of the image
	ICE_U8 *pu8VData;				     //!< V data buffer of the image
	ICE_U8 *pu8UVData;					 //!< UV data buffer of the image
} ICE_YUV422P_IMAGE_S;

//! \ingroup group_core
//! RBG image definition
typedef struct
{
	ICE_S32 s32Width;           //!< width of the image
	ICE_S32 s32Height;          //!< height of the image
	ICE_U8 *pu8RData;           //!< red data buffer of the image
	ICE_U8 *pu8GData;           //!< green data buffer of the image
	ICE_U8 *pu8BData;           //!< blue data buffer of the image
} ICE_RBG_IMAGE_S;

//! Section line
typedef struct
{
	ICE_LINE_S line;            //!< Line segment position (unit: pixel)
} ICE_CUT_LINE;

//! Prohibited scope
typedef struct
{
	ICE_S32 forbidden;              //!< Prohibition flag (0: enabled; 1: prohibited)
	ICE_S32 minimum;                //!< Minimum value, -1 means no constraint
	ICE_S32 maximum;                //!< The maximum value, a value of -1 means no constraint
} ICE_FORBIDDEN_INTERVAL;


//----------------------------------------------
// Target definition
//----------------------------------------------

//! \ingroup group_core
//! Target type
typedef enum
{
	ICETGT_TYPE_UNKNOWN			= 0,        
	ICETGT_TYPE_HUMAN			= 1,        
	ICETGT_TYPE_VEHICLE			= 2        
} ICE_TGT_TYPE;

//! \ingroup group_core
#define ICE_MAX_TRAJECT_LEN	40
typedef struct
{
	ICE_S32 length;							
	ICE_POINT_S	points[ICE_MAX_TRAJECT_LEN];
} ICE_TGT_TRAJECT;

//! \ingroup group_core
typedef struct
{
	ICE_U32 u32ID;                          
	ICE_S32 u32Type;                       
	ICE_POINT_S stPoint;                   
	ICE_RECT_S stRect;                     
	ICE_S32 s32AreaPix;                   
	ICE_S32 s32Area;                       
	ICE_S32 s32Direct;                    
	ICE_FLOAT fSpeed;                       
	ICE_TGT_TRAJECT stTraject;				
} ICE_TARGET;

#define ICE_MAX_TGT_NUM 64                 
//! \ingroup group_core

typedef struct
{
	ICE_S32 s32TargetNum;                
	ICE_TARGET astTargets[ICE_MAX_TGT_NUM]; 
} ICE_TARGET_SET;


//----------------------------------------------
// event define
//----------------------------------------------

//! \ingroup group_core

typedef enum
{
	ICEEVT_TYPE_UNKNOWN             = 0000, 

	ICEEVT_TYPE_PERIMETER           = 1000, 
	ICEEVT_TYPE_LOITER              = 1001,	
	ICEEVT_TYPE_ABNORMALVEL         = 1002,
	ICEEVT_TYPE_CONVERSE            = 1003,	
	ICEEVT_TYPE_TRIPWIRE            = 1004,	
	ICEEVT_TYPE_MTRIPWIRE           = 1005,
	ICEEVT_TYPE_OBJLEFT             = 1006,	
	ICEEVT_TYPE_OBJREMOVED          = 1007,	
	ICEEVT_TYPE_MLOITER             = 1008,
	ICEEVT_TYPE_NOPARKING           = 1009, 
	ICEEVT_TYPE_VEHICLE_CONVERSE    = 1101, 
	ICEEVT_TYPE_VEHICLE_PARK        = 1102, 
	ICEEVT_TYPE_VEHICLE_OVERSPEED   = 1103, 
	ICEEVT_TYPE_VEHICLE_UNDERSPEED  = 1104, 
	ICEEVT_TYPE_HUMAN_ACROSS        = 1105, 
	ICEEVT_TYPE_OBJECT_LEFT         = 1106, 
	ICEEVT_TYPE_VEHICLE_OCCUPATION  = 1107, 

	ICEEVT_TYPE_TGTCOUNT            = 1201,	
	ICEEVT_TYPE_HUMANCOUNT          = 1202,

	ICEEVT_TYPE_SIGNAL_BAD  		= 2001  

} ICE_EVT_TYPE;

//! \ingroup group_core
typedef enum
{
	ICEEVT_STATUS_NOSTA	= 0,              
	ICEEVT_STATUS_START	= 1,              
	ICEEVT_STATUS_END	= 2              
} ICE_EVT_STATUS;

//! \ingroup group_core
typedef struct
{
	ICE_U32 u32Type;                       
	ICE_U32 u32ID;                          
	ICE_U32 u32Status;                     
	ICE_U32 u32Zone;                       
	ICE_U32 u32TgtID;                      
	ICE_U8  u8Data[16];                    
} ICE_EVENT;

#define ICE_MAX_EVT_NUM	128                 
//! \ingroup group_core

typedef struct
{
	ICE_S32	s32EventNum;                   
	ICE_EVENT astEvents[ICE_MAX_EVT_NUM];   
} ICE_EVENT_SET;

//! \ingroup group_core
typedef struct
{
	ICE_TARGET_SET stTargetSet;             
	ICE_EVENT_SET stEventSet;               
} ICE_ALGO_RESULT;

//! \ingroup group_core
typedef enum
{
	ICEALARM_LEVEL_ALARM      = 0,    
	ICEALARM_LEVEL_PREALARM   = 1      
} ICE_ALARM_LEVEL;


#define ICE_VERSION_A( type1, type2, seri_m1, seri_m2, seri_s ) \
	( 0	\
	| ( (((ICE_U32)type1)		& 0xFF) << 24 ) \
	| ( (((ICE_U32)type2)		& 0xFF) << 16 ) \
	| ( (((ICE_U32)seri_m1)		& 0x0F) << 12 ) \
	| ( (((ICE_U32)seri_m2)		& 0x1F) << 7 ) \
	| ( (((ICE_U32)seri_s)		& 0x7F) << 0 ) \
	)

#define ICE_VER_A_TYPE1( ver )		( (((ICE_U32)ver)>>24)	& 0xFF )
#define ICE_VER_A_TYPE2( ver )		( (((ICE_U32)ver)>>16)	& 0xFF )
#define ICE_VER_A_SER_M1( ver )		( (((ICE_U32)ver)>>12)	& 0x0F )
#define ICE_VER_A_SER_M2( ver )		( (((ICE_U32)ver)>>7)	& 0x1F )
#define ICE_VER_A_SER_S( ver )		( (((ICE_U32)ver)>>0)	& 0x7F )

ICE_EXPORTS void ICECORE_FormatVersion( ICE_U32 nSeriNum, char *pVerion );


#ifdef __cplusplus
}
#endif


#endif // __ICE_TYPE_H__

