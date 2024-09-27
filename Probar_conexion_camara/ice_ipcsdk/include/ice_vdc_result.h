/*! \file ice_vd_result.h
\brief ice_vd_result.h document.
*/
#ifndef __ICE_VDC_RESULT_H__
#define __ICE_VDC_RESULT_H__

#include "ice_base_type.h"
#include "ice_vlpr_result.h"
#include "ice_vdc_config.h"
#include "ice_vehibrand_interface.h"
#include "ice_vehicolor_interface.h"
#include "ice_com_type.h"

#ifdef __cplusplus
extern "C"
{
#endif


typedef enum
{
	ICE_VDC_HD_TRIGER,						//real-time_hard trigger+temporary vehicle(0)
	ICE_VDC_VIDEO_TRIGER, 					//real-time_video trigger+temporary vehicle£¨1£©
	ICE_VDC_SOFT_TRIGER,						//real-time_software trigger+temporary vehicle£¨2£©
	ICE_VDC_HD_TRIGER_AND_WHITELIST,		//real-time_hard trigger+valid white list(3)
	ICE_VDC_VIDEO_TRIGER_AND_WHITELIST,	//real-time_video trigger+valid white list£¨4£©
	ICE_VDC_SOFT_TRIGER_AND_WHITELIST,  	//real-time_software trigger+valid white list£¨5£©
	ICE_VDC_HD_TRIGER_AND_BLACKLIST,		//real-time_hard trigger+black list(6)
	ICE_VDC_VIDEO_TRIGER_AND_BLACKLIST,	//real-time_video trigger+black list£¨7£©
	ICE_VDC_SOFT_TRIGER_AND_BLACKLIST,  	//real-time_software trigger+black list£¨8£©

	ICE_VDC_NC_HD_TRIGER,					//offline_hard trigger+temporary vehicle(9)
	ICE_VDC_NC_VIDEO_TRIGER, 				//offline_video trigger+temporary vehicle£¨10£©
	ICE_VDC_NC_SOFT_TRIGER,					//offline_software trigger+temporary vehicle£¨11£©
	ICE_VDC_NC_HD_TRIGER_AND_WHITELIST,	//offline_hard trigger+valid white list(12)
	ICE_VDC_NC_VIDEO_TRIGER_AND_WHITELIST,//offline_video trigger+valid white list£¨13£©
	ICE_VDC_NC_SOFT_TRIGER_AND_WHITELIST,  //offline_software trigger+valid white list£¨14£©
	ICE_VDC_NC_HD_TRIGER_AND_BLACKLIST,	//offline_hard trigger+black list(15)
	ICE_VDC_NC_VIDEO_TRIGER_AND_BLACKLIST,//offline_video trigger+black list£¨16£©
	ICE_VDC_NC_SOFT_TRIGER_AND_BLACKLIST,  //offline_software trigger+black list£¨17£©

	ICE_VDC_HD_TRIGER_AND_OVERDUE_WHITELIST,			//real-time_hard trigger+Overdue white list(18)
	ICE_VDC_VIDEO_TRIGER_AND_OVERDUE_WHITELIST,		//real-time_video trigger+Overdue white list£¨19£©
	ICE_VDC_SOFT_TRIGER_AND_OVERDUE_WHITELIST,  		//real-time_software trigger+Overdue white list£¨20£©
	ICE_VDC_NC_HD_TRIGER_AND_OVERDUE_WHITELIST,		//offline_hard trigger+Overdue white list(21)
	ICE_VDC_NC_VIDEO_TRIGER_AND_OVERDUE_WHITELIST,	//offline_video trigger+Overdue white list£¨22£©
	ICE_VDC_NC_SOFT_TRIGER_AND_OVERDUE_WHITELIST,  	//offline_software trigger+Overdue white list£¨23£©

	ICE_VDC_ALARM_UNKOWN,
}ICE_VDC_ALARM_TYPE; 


//trigger type
typedef enum
{
	ICE_VDC_HD_TRIGGER,						
	ICE_VDC_VIDEO_TRIGGER, 					
	ICE_VDC_SOFT_TRIGGER,					
	ICE_VDC_TRIGGER_UNKOWN,
}ICE_VDC_TRIGGER_TYPE;

//!plate type
typedef enum
{
	ICE_VDC_PLATE_TEMP,			  
	ICE_VDC_PLATE_WHITELIST,		  
	ICE_VDC_PLATE_BLACKLIST,		 
	ICE_VDC_PLATE_OVERDUE_WHITELIST, 
	ICE_VDC_PLATE_UNKOWN,
}ICE_VDC_PLATE_TYPE; 

typedef struct
{
	ICE_VLPR_OUTPUT_S stPlateInfo;
	ICE_VDC_PLATE_TYPE s32PlateType; 
	ICE_U16 u32StartYear; 
	ICE_U8 u32StartMon;
	ICE_U8 u32StartDay;
	ICE_U16 u32EndYear; 
	ICE_U8 u32EndMon;
	ICE_U8 u32EndDay;
	ICE_SYSTEMTIME_S  stLiveCapTime;    					
	ICE_S32 u32Reserved[6];  
}ICE_VDC_CAR_INFO_S;


//typedef enum
//{
//	ICE_VDC_VEHICLE_TYPE_UNKOWN				= 0,			
//	ICE_VDC_VEHICLE_TYPE_NORMAL_CAR			= 1,			
//	ICE_VDC_VEHICLE_TYPE_MINIBUS			= 2,		
//	ICE_VDC_VEHICLE_TYPE_BUS				= 3,			
//	ICE_VDC_VEHICLE_TYPE_BOXTRUCK			= 4,			
//	ICE_VDC_VEHICLE_TYPE_TRUCK				= 5,			
//	ICE_VDC_VEHICLE_TYPE_NONMOTORIZED	    = 6,			
//}ICE_VDC_VEHICLETYPE_E;

typedef enum
{
	ICE_VDC_VEHICLE_TYPE_UNKOWN				= 0,			//!<  unkown
	ICE_VDC_VEHICLE_TYPE_NORMAL_CAR			= 1,			//!<  normal car
	ICE_VDC_VEHICLE_TYPE_MINIBUS			= 2,			//!<  mini bus
	ICE_VDC_VEHICLE_TYPE_BUS				= 3,			//!<  bus
	ICE_VDC_VEHICLE_TYPE_MEDIUMBUS			= 4,			//!<  medium bus
	ICE_VDC_VEHICLE_TYPE_PICK_UP_TRUCK		= 5,			//!<  pick up truck
	ICE_VDC_VEHICLE_TYPE_NONMOTORIZED	    = 6,			//!<  nonmotorized
	ICE_VDC_VEHICLE_TYPE_SUV				= 7,			//!<  SUV
	ICE_VDC_VEHICLE_TYPE_MPV				= 8,			//!<  MPV
	ICE_VDC_VEHICLE_TYPE_MINITRUCK			= 9,			//!<  mini truck
	ICE_VDC_VEHICLE_TYPE_PICKUPTRUCK		= 10,			//!<  pickup truck
	ICE_VDC_VEHICLE_TYPE_MEDIUMTRUCK		= 11,			//!<  medium truck
	ICE_VDC_VEHICLE_TYPE_HEAVYTRUCK			= 12,		//!<  heavy truck
}ICE_VDC_VEHICLETYPE_E; 


//! \ingroup group_vd
typedef struct 
{
	ICE_S32 s32EventCode;									//!< event code
	ICE_S32   s32LandId;									//!< land ID
#ifdef _WIN64
	ICE_CHAR  cFileName[120];  								//!< file name
#else
	ICE_CHAR  cFileName[124];  								//!< file name
#endif
	ICE_VBR_RESULT_S *pstVbrResult;							//!< VBR result
	ICE_VDC_ALARM_TYPE   s32AlarmType;						//!< alarm type
	ICE_SYSTEMTIME_S  stLiveCapTime;    					//!< cap time of real-time data
	ICE_U32  u32SerialNum;  								//!< vehicle¡¯s serial number   	
	ICE_U32  u32PlateWidth;  								//!< plate¡¯s real width
	ICE_U32  u32ExtSnapPixel;  								//!< the pixel height of the outer osd of the capture image	
	ICE_Phone_Mac_List* pPhoneMacList;						//!< mac list of recived terminal
#ifndef _WIN64
	ICE_CHAR  cPhoneMacListReserve[4];  					//!< reserve
#endif
	ICE_U32	 u32PictureHashID;								//!< hash ID of picture
	ICE_U32  u32Encrypt;									//!< Whether the license plate number is encrypted
	ICE_U8   u8PlateTea;									//!< The last byte of the license plate number Tea encrypted
	ICE_CHAR  cReserve[41];									//!< reserve
	ICE_S16 s16FeatureNum;									//!< The dimension of the characteristic code
	ICE_FLOAT pReserve;										//!< reserve
	ICE_U8 uReserve[2];										// !< reserve
	ICE_U8  u8FalsePlateFileter;							//!< Whether to filter fake license plates
	ICE_U8 u8FalsePlate;  									//!< Whether is fake plate
	ICE_S32 s32TripWireEventCode;							//!< Trip wire event code
	ICE_S32  s32VehicleIntensity;							//!< vehicle intensity
	ICE_CHAR cVehicleType[12];								//!< vehicle type
	ICE_VCR_VEHICLECOLOR_E enVehicleColor;					//!< vehicle color
	ICE_VDC_VEHICLETYPE_E s32VehicleType;					//!< vehicle type
	ICE_SYSTEMTIME_S  stCapTime;    						//!< capture time
	ICE_S32    s32HaveCloseUp;     							//!< whether has close up picture
	ICE_RECT_S stVehilceRect;	  							//!< vehicle¡¯s rect
	ICE_VDC_VERHICLE_DIR_E 	enDirect;         				//!< vehicle direction
	ICE_FLOAT 	fSpeed;         	                		//!< speed(km/h)
	ICE_CHAR 	cVehicleColor[32];							//!< vehicle color
	ICE_CHAR 	cPlateColor[32];							//!< plate color
	ICE_S32    s32HavePlate;       							//!< is has plate              						
	ICE_VLPR_OUTPUT_S stPlateInfo;							//!< plate info
	ICE_S16    s16PicWidth;     							//!< picture¡¯s width					   						
	ICE_S16    s16PicHeight;     							//!< picture¡¯s height
	ICE_S32   s32PicDataLen;								//!< picture¡¯s size
	ICE_S8    *ps8PictureData;     							//!< picture¡¯s data		
}ICE_VDC_PICTRUE_INFO_S; 



typedef struct 
{
	ICE_S32 s32EventCode;									//!< event code
	ICE_S32   s32LandId;									//!< land ID
#ifdef _WIN64
	ICE_CHAR  cFileName[120];  								//!< file name
#else
	ICE_CHAR  cFileName[124];  								//!< file name
#endif
	ICE_VBR_RESULT_S *pstVbrResult;							//!< VBR result
	ICE_VDC_ALARM_TYPE   s32AlarmType;						//!< alarm type
	ICE_SYSTEMTIME_S  stLiveCapTime;    					//!< cap time of real-time data
	ICE_U32  u32SerialNum;  								//!< vehicle¡¯s serial number   	
	ICE_U32  u32PlateWidth;  								//!< plate¡¯s real width
	ICE_U32  u32ExtSnapPixel;  								//!< the pixel height of the outer osd of the capture image	
	ICE_Phone_Mac_List* pPhoneMacList;						//!< mac list of recived terminal
#ifndef _WIN64
	ICE_CHAR  cPhoneMacListReserve[4];  					//!< reserve
#endif
	ICE_U32	 u32PictureHashID;								//!< hash ID of picture
	ICE_U32  u32Encrypt;									//!< Whether the license plate number is encrypted
	ICE_U8   u8PlateTea;									//!< The last byte of the license plate number Tea encrypted
	ICE_CHAR  cReserve[41];									//!< reserve
	ICE_S16 s16FeatureNum;									//!< The dimension of the characteristic code
	ICE_FLOAT pReserve;										//!< reserve
	ICE_U8 uReserve[2];										// !< reserve
	ICE_U8  u8FalsePlateFileter;							//!< Whether to filter fake license plates
	ICE_U8 u8FalsePlate;  									//!< Whether is fake plate
	ICE_S32 s32TripWireEventCode;							//!< Trip wire event code
	ICE_S32  s32VehicleIntensity;							//!< vehicle intensity
	ICE_CHAR cVehicleType[12];								//!< vehicle type
	ICE_VCR_VEHICLECOLOR_E enVehicleColor;					//!< vehicle color
	ICE_VDC_VEHICLETYPE_E s32VehicleType;					//!< vehicle type
	ICE_SYSTEMTIME_S  stCapTime;    						//!< capture time
	ICE_S32    s32HaveCloseUp;     							//!< whether has close up picture
	ICE_RECT_S stVehilceRect;	  							//!< vehicle¡¯s rect
	ICE_VDC_VERHICLE_DIR_E 	enDirect;         				//!< vehicle direction
	ICE_FLOAT 	fSpeed;         	                		//!< speed(km/h)
	ICE_CHAR 	cVehicleColor[32];							//!< vehicle color
	ICE_CHAR 	cPlateColor[32];							//!< plate color
	ICE_S32    s32HavePlate;       							//!< is has plate              						
	ICE_VLPR_OUTPUT_S stPlateInfo;							//!< plate info
	ICE_S16    s16PicWidth;     							//!< picture¡¯s width					   						
	ICE_S16    s16PicHeight;     							//!< picture¡¯s height
	ICE_S32   s32PicDataLen;								//!< picture¡¯s size
	ICE_S8    as8PictureData[1024*1024];     				//!< picture's data				   						
}ICE_VDC_PICTRUE_INFO_BUFFER_S;

typedef enum E_LprState
{
	LPRSTATE_OFFLINE,
	LPRSTATE_ONLINE
}E_LprState;

typedef struct T_PlateInfo
{
	char	plateNum[128];		
	char	plateColor[32];		
	int		flasePlate;			
	float	confidence;			
	ICE_PLATETYPE_E	plateType;	
	ICE_RECT_S	stPlateRect;	
	char	resv[256];			
}T_PlateInfo;

typedef struct T_VehicleInfo
{
	char	vehicleType[32];	
	char	vehicleColor[32];	
	char	vehicleDir[32];		
	char	logName[128];					
	char	subLogName[128];				
	char	productYearName[32];			
	char	resv[256];									
}T_VehicleInfo;

typedef struct T_LprResult 
{
	T_PlateInfo				plateInfo;		
	T_VehicleInfo			vehicleInfo;	
	E_LprState	lprState;					
	int		iHadPlate;
	char	triggerType[32];		
	char	plateState[32];			
	char	bwList[32];				
	T_TimeInfo		capTime;		
	char	resv[512];				
}T_LprResult;

#ifdef __cplusplus
}
#endif


#endif
	