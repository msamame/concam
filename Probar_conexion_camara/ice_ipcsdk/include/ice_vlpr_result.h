/*! \file ice_vlpr_result.h
\brief ice_vlpr_result.h document.
*/
#ifndef __ICE_VLPR_RESULT_H__
#define __ICE_VLPR_RESULT_H__

#include "ice_base_type.h"

#ifdef __cplusplus
extern "C"
{
#endif



//-------------------------------------------
// Character type definition            		 
//-------------------------------------------

//! Character type definition
typedef enum 
{
	ICE_CHARTYPE_CHARACTER			= 0,	
	ICE_CHARTYPE_ONLYDIGITAL		= 1,	
	ICE_CHARTYPE_ONLYALPHABET		= 2,	

	ICE_HANZI_CHINA					= 3,	
	ICE_HANZI_BEIJING				= 4,	
	ICE_HANZI_SHANGHAI				= 5,	
	ICE_HANZI_TIANJIN				= 6,
	ICE_HANZI_CHONGQING				= 7,	
	ICE_HANZI_HEILONGJIANG			= 8,	
	ICE_HANZI_JILIN					= 9,	
	ICE_HANZI_LIAONING				= 10,	
	ICE_HANZI_NEIMENG				= 11,	
	ICE_HANZI_HEBEI					= 12,	
	ICE_HANZI_SHANDONG				= 13,	
	ICE_HANZI_SHANXI				= 14,
	ICE_HANZI_ANHUI					= 15,
	ICE_HANZI_JIANGSU				= 16,	
	ICE_HANZI_ZHEJIANG				= 17,	
	ICE_HANZI_FUJIAN				= 18,	
	ICE_HANZI_GUANGDONG				= 19,	
	ICE_HANZI_HENAN					= 20,	
	ICE_HANZI_JIANGXI				= 21,
	ICE_HANZI_HUNAN					= 22,	
	ICE_HANZI_HUBEI					= 23,
	ICE_HANZI_GUANGXI				= 24,	
	ICE_HANZI_HAINAN				= 25,	
	ICE_HANZI_YUNNAN				= 26,	
	ICE_HANZI_GUIZHOU				= 27,
	ICE_HANZI_SICHUAN				= 28,	
	ICE_HANZI_XIAN					= 29,	
	ICE_HANZI_GANSU					= 30,	
	ICE_HANZI_NINGXIA				= 31,	
	ICE_HANZI_QINGHAI				= 32,
	ICE_HANZI_XIZANG				= 33,	
	ICE_HANZI_XINJIANG				= 34	
}ICE_VLPR_CHARTYPE_E;	

//-------------------------------------------------------
// License plate type definition   									 
//-------------------------------------------------------

//! License plate type definition
typedef enum 

{
	ICE_PLATE_UNCERTAIN         = 0,          //!< unkown
	ICE_PLATE_BLUE              = 1,          //!< blue plate 
	ICE_PLATE_YELLOW            = 2,          //!< yellow plate 
	ICE_PLATE_POLICE            = 4,          //!< police
	ICE_PLATE_WUJING            = 8,          //!< army 
	ICE_PLATE_DBYELLOW          = 16,         //!< double yellow plate 
	ICE_PLATE_MOTOR             = 32,         //!< motor
	ICE_PLATE_INSTRUCTIONCAR    = 64,         //!< instruction
	ICE_PLATE_MILITARY          = 128,        //!< military 
	ICE_PLATE_PERSONAL          = 256,        //!< personal plate 
	ICE_PLATE_GANGAO            = 512,        //!< gangao plate 
	ICE_PLATE_EMBASSY           = 1024,       //!< embassy car
	ICE_PLATE_NONGLARE          = 2048,       //!< nonalare
	ICE_PLATE_AVIATION          = 4096,       //!< aviation
	ICE_PLATE_NEWENERGY         = 8192,       //!< new energy
	ICE_PLATE_NEWENERGYBIG      = 0x00004000, //!< new energy bug car
	ICE_PLATE_WHITE_TWOTWO      = 0x10000001, //!< 2+2 model
	ICE_PLATE_WHITE_TWOTHR      = 0x10000002, //!< 2+3 model
	ICE_PLATE_WHITE_THRTWO      = 0x10000004, //!< 3+2 model
	ICE_PLATE_WHITE_THRTHR      = 0x10000008, //!< 3+3 model
	ICE_PLATE_WHITE_THRFOR      = 0x10000010, //!< 3+4 model
	ICE_PLATE_BLACK_THRTWO      = 0x10000020, //!< 3+2 model
	ICE_PLATE_BLACK_TWOTHR      = 0x10000040, //!< 2+3 model
	ICE_PLATE_BLACK_THRTHR      = 0x10000080, //!< 3+3 model
	ICE_PLATE_BLACK_TWOFOR      = 0x10000100, //!< 2+4 model
	ICE_PLATE_BLACK_FORTWO      = 0x10000200, //!< 4+2 model
	ICE_PLATE_BLACK_THRFOR      = 0x10000400, //!< 3+4 model
}ICE_PLATETYPE_E;


//-------------------------------------------------------
// License plate color definition
//-------------------------------------------------------

// License plate color definition
typedef enum
{
	ICE_PLATE_COLOR_UNKNOWN		= 0,	
	ICE_PLATE_COLOR_BLUE		= 1,
	ICE_PLATE_COLOR_YELLOW		= 2,	
	ICE_PLATE_COLOR_WHITE		= 3,	
	ICE_PLATE_COLOR_BLACK		= 4,	
	ICE_PLATE_COLOR_GREEN		= 5,	
	ICE_PLATE_COLOR_GREENBLACK	= 6,	
	ICE_PLATE_COLOR_GREENYELLOW	= 7		
}ICE_PLATECOLOR_E;

typedef enum
{
	ICE_VEHICLE_COLOR_UNKOWN= 0,		
	ICE_VEHICLE_COLOR_RED = 1,			
	ICE_VEHICLE_COLOR_GREEN = 2,		
	ICE_VEHICLE_COLOR_BLUE = 3,			
	ICE_VEHICLE_COLOR_YELLOW = 4,		
	ICE_VEHICLE_COLOR_WHITE = 5,		
	ICE_VEHICLE_COLOR_GRAY = 6,			
	ICE_VEHICLE_COLOR_BLACK = 7,		
	ICE_VEHICLE_COLOR_PURPLE=8,			
	ICE_VEHICLE_COLOR_BROWN=9,			
	ICE_VEHICLE_COLOR_PINK=10			
}ICE_VEHICLECOLOR_E;

//----------------------------------------------
// Definition of license plate recognition output structure
//----------------------------------------------

#define ICE_VLPR_PLATE_CHAR_NUM		10								//!<  License plate characters  
#define ICE_VLPR_PLATE_BUFLEN		16                              //!<  License plate maximum 

typedef struct
{
	ICE_U16 s16leftopx;            //!< letf x
	ICE_U16 s16leftopy;            //!< letf y
	ICE_U16 s16rigtopx;             //!< top y
	ICE_U16 s16rigtopy;             //!< top y
	ICE_U16 s16lefbotmx;           //!< right x
	ICE_U16 s16lefbotmy;           //!< right x
	ICE_U16 s16rigbotmx;          //!< bottom y
	ICE_U16 s16rigbotmy;          //!< bottom y
} ICE_RECT_4P_S;

//! \ingroup group_vlpr
//! License plate recognition output structure
typedef struct 
{                                                                       //!<  Number of license plate characters;
	ICE_S8				as8PlateNum[ICE_VLPR_PLATE_BUFLEN];				//!<  number plate
	ICE_RECT_S			stPlateRect;									//!<  License plate rectangle
	ICE_S32             s32PlateContrast;								//!<  License plate contrast                                                        
	ICE_S8				astReserve0[40];								//!<  reserve
	ICE_FLOAT           aflPlateCharConfid[ICE_VLPR_PLATE_CHAR_NUM];	//!<  License plate character confidence
	ICE_FLOAT			flConfidence;									//!<  License plate confidence
	ICE_S32				s32PlateIntensity;								//!<  License plate brightness
	ICE_PLATECOLOR_E    ePlateColor;									//!<  License plate color
	ICE_PLATETYPE_E		ePlateType;										//!<  License plate type
	ICE_VEHICLECOLOR_E	eVehicleColor;									//!<  the color of car

	ICE_FLOAT			flPlateAngleH;									//!<  License plate horizontal tilt angle
	ICE_FLOAT			flPlateAngleV;									//!<  License plate vertical tilt angle
	ICE_U8				u8PlateColorRate;								//!<  Degree of color matching;
	ICE_S8				s8CharNum;
	ICE_RECT_4P_S		stRealPlateRect;								//
	ICE_S8				astReserve;										//!<  reserve
	ICE_S8              sPlateFmt;										//!<  0:default  100:UTF8 101:BIG5 102:GBK
	ICE_U32             u32FrameId;
}ICE_VLPR_OUTPUT_S;


//----------------------------------------------
// Definition of license plate recognition processing result
//----------------------------------------------

#define ICE_VLPR_MAX_OUTPUT_NUM		16							//!< max number of license plates 

//! \ingroup group_vlpr
//! License plate recognition algorithm processing results
typedef struct 
{
	ICE_S32				s32NumOutput;							//!< Number of output results  
	ICE_VLPR_OUTPUT_S	astOutput[ICE_VLPR_MAX_OUTPUT_NUM];		//!< Multiple output results
}ICE_VLPR_RULT_S;


#ifdef __cplusplus
}
#endif


#endif
