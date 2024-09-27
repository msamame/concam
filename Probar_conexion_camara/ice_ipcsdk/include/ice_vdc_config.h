/*! \file ice_vdc_config.h
\brief ice_vdc_config.h document.
*/

#ifndef __ICE_VDC_CONFIG_H__
#define __ICE_VDC_CONFIG_H__

#include "ice_base_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

//! \ingroup group_vd
//! Advanced parameter definition of entrance and exit lanes
typedef struct 
{
	ICE_S32 s32AdaptiveThreshOnOff;					//!<  Adaptive threshold switch (1: on 0: off default: off)							
	ICE_S32 s32DayTriggerThresh;					//!<  Day Trigger Threshold (Range: 1-100 Default: 25)													
	ICE_S32 s32NightTriggerThresh;					//!<  Night trigger threshold (Range: 1-100 Default: 50)												
	ICE_S32 s32TriggerSensitivity;					//!<  Trigger sensitivity (Range: 1-100 Default: 10)													
	ICE_S32 s32FilterByPlate;						//!<  No license plate filter switch (1: on 0: off default: on)													
	ICE_S32 s32TrigerInterval;						//!<  Unlicensed vehicle trigger interval (Range: 10-500 Default: 50)
	ICE_S32 s32DetectDoubleDirectOnOff;				//!<  Detect two-way vehicle switch (2: Support two-way vehicles and output direction information 1: Support two-way vehicles but do not output direction information 0: Only output one-way vehicles)
	ICE_S32 s32EnableSamePlateCar;					//!<  Allow same vehicle switch (1: on 0: off default: off)
	ICE_S32 s32SamePlateCarOutputTime;				//!<  Same vehicle output interval (range: 1-3600 default: 30 units: seconds)
	ICE_S32 s32EnableNonMotorizedVehicles;			//!<  Turn on the non-motor vehicle detection switch (1: on 0: off default: off)
	ICE_S32 s32FilterNonMotorizedVehicles;			//!<  Whether to filter non-motor vehicles (1: on 0: off default: off)
	ICE_S32 s32EnableVehicleBrand;					//!<  Support car identification (licensed car)
	ICE_S32 s32FilterNoiseChar;						//!<  Enable character interference filtering (1: on 0: off default: off)
	ICE_S32 s32NoiseCharLprThresh;					//!<  Characters interfere with the upper threshold of the license plate (15-28 default: 20)
	ICE_S32 s32EnableNoPlateVehicleBrand;			//!< Support unlicensed car model identification (1: On 0: Off Default: Off)
	ICE_S32 s32EnableEqualPlateCar;     //!<  Repeat output switch outside the same vehicle output interval (1: On 0: Off)                        
	ICE_S32 u32Reserved[5];       //!<  reserve                          
    																					
}ICE_VDC_ADV_PARAM_S;

//! \ingroup group_vdc
typedef enum 
{
	ICE_VDC_VERHICLE_DIR_HEAD			 = 0,				 			
	ICE_VDC_VERHICLE_DIR_TAIL			 = 1,					
	ICE_VDC_VERHICLE_DIR_HEAD_AND_TAIL	 = 2				
}ICE_VDC_VERHICLE_DIR_E;

//! \ingroup group_vdc
typedef enum 
{
	ICE_VDC_TRIGER_MODE_HDWARE				= 0,							
	ICE_VDC_TRIGER_MODE_VIDEO				= 1,							
	ICE_VDC_TRIGER_MODE_HDWARE_AND_VIDEO	= 2						
}ICE_VDC_TRIGER_MODE_E;

//! \ingroup group_vdc
typedef enum 
{
	ICE_VDC_INSTALL_POS_DRIVER_SIDE					= 0,				
	ICE_VDC_INSTALL_POS_DRIVER_REVERSE_SIDE			= 1							
}ICE_VDC_INSTALL_POS_E;

//! \ingroup group_vd
typedef struct 
{																						
	ICE_VDC_VERHICLE_DIR_E enVehiceleDirection;				//!<  Vehicle direction (default: front)										
	ICE_RECT_S astLoop;				 						//!<  Virtual coil (recognition area)																				
	ICE_VDC_ADV_PARAM_S stAdvParam;							//!<  Advanced parameters
	ICE_VDC_TRIGER_MODE_E enTrigerMode;						//!<  Trigger mode

	ICE_S32 s32QuqdrangleEnable;							//!<  Enable virtual coil polygon recognition area
	ICE_S32 s32TripWiresEnable;								//!<  Trip enable flag
	ICE_LINE_S stTripWiresLane;								//!<  Trip
	ICE_LINE_S stTripWiresLane2;							//!<  Upper tripwire in bidirectional mode
	ICE_S32 s32OnekeyConfigEnable;							//!<  Turn on one-click debugging  

	ICE_S32 u32Reserved[8];                        		//!<  reserve   																					
	//ICE_S32 u32Reserved[15];                        		    																					
}ICE_VDC_LANE_S;

typedef struct 
{
	ICE_S32 s32MinPlateWidth;      //!<  Min license plate width            
	ICE_S32 s32MaxPlateWidth;      //!<  Max license plate width
	ICE_QUADRANGLE_S stVLoopRect;     //!<  Virtual coil quadrangular area
	ICE_S32  s32AntiFakeEn;                         //!<License plate anti-counterfeiting function is enabled 1 enabled 0 not enabled 
	ICE_S8 s8Smoothflag;       //!< Smoothing parameters; for license plate cameras;
	ICE_S8 s8PlateNoColor;             //!< License plate color invalid switch: 1 invalid 0 valid (default)
	ICE_S8 s8VehiAttributeCodeOn;     //!< Unlicensed car feature code switch: 1 valid 0 invalid (default)
	// s32AntiFakeEn 1 s8FalsePlateFilter 1 
	//s32AntiFakeEn 1 s8FalsePlateFilter  0 
	ICE_S8    s8FalsePlateFilter;                  //False license plate filtering
	ICE_S8    s8VirtualPlate;     //Unlicensed car virtual license plate output setting, 0 does not output output
	ICE_S8    s8AntiFakeArea;                     //Anti-counterfeiting range 0 All cars 1 Whitelist
	ICE_S8    s8Reserved2[6];     //reserve
	//ICE_CHAR cPriorCity[32];       //!<  Priority city (not currently used, can be used as a polygon area)            
	ICE_S32 s32PlateConfidThrld;     //!<  License plate credibility threshold (-28-28), default: 15    
	ICE_FLOAT fPlateAngle;       //!<  License plate tilt angle, default: 0
	ICE_S32 s32PlateTypeSp;       //!<  Support license plate type 0 All are enabled by default;
	ICE_S32 s32CarColorOn;       //!<  Body color is enabled; 0 is not enabled
	ICE_S32 s32PriorCityType;      //!<  Priority city type
	ICE_S32 s32PriorArmyPlate;      //!<  Army license first
	ICE_VDC_INSTALL_POS_E enCameraInstallPos;  //!<  Camera installation location (default: driver side)
	ICE_S32 s32EnableOnePlateSameChars;    //!<  Support 1 license plate repeating characters (for example: Jing N11111) 0 not enabled 1 start, default: 0 (default: 0)
	ICE_S32 s32EnableOneCarMultiPlates;    //!<  Supports 1 car with multiple licenses 0 Not enabled 1 Started, default: 0
	ICE_S32 s32EnableWJChineseChar;     //!<  Support Armed Police Chinese Character Output 0 Disabled 1 Started, Default: 0
	ICE_S32 u32Reserved[7];                         //!<  reserve              
}ICE_VDC_PLATE_CONFIG_S;

//! \ingroup group_vd
//! Entry and exit parameter definition
typedef struct  
{
	ICE_VDC_LANE_S astLane;				 						 //!<  Lane parameters		  						  
	ICE_VDC_PLATE_CONFIG_S stPlateParam;						 //!<  License plate parameters		  						  	  
	ICE_S32 s32Width;											 //!<  Configure the reference image width		  						  	  
	ICE_S32 s32Height;											 //!<  Configure the reference image height
	ICE_S32 as32Reserved[8];              						 //!<  reserve 											  
}ICE_VDC_PARAM_S;

#ifdef __cplusplus
}
#endif


#endif// __ICE_VDC_CONFIG_H__
