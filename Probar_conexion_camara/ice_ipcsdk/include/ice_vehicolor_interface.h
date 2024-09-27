#ifndef ice_vehicolor_interface_h__
#define ice_vehicolor_interface_h__

/********************************************************************
Copyright (C), 1994-2016, icetech

fine name: 	ice_vehicolor_interface.h
Description:	Vehicle color identification header	
history	2016-6-3 14:00:36	 creat V1.0.001 
*********************************************************************/

#include "ice_base_type.h"

typedef enum
{
	ICE_VCR_VEHICLE_COLOR_UNKOWN 	= -1,	
	ICE_VCR_VEHICLE_COLOR_BLACK 	= 0,	 
	ICE_VCR_VEHICLE_COLOR_BLUE 		= 1,	

	ICE_VCR_VEHICLE_COLOR_GRAY 		= 2,	
	ICE_VCR_VEHICLE_COLOR_BROWN 	= 3,	
	ICE_VCR_VEHICLE_COLOR_GREEN 	= 4,	 
	ICE_VCR_VEHICLE_COLOR_NIGHTDARK	= 5,   	 
	ICE_VCR_VEHICLE_COLOR_PURPLE	= 6,	
	ICE_VCR_VEHICLE_COLOR_RED 		= 7,	 
	ICE_VCR_VEHICLE_COLOR_WHITE 	= 8,	
	ICE_VCR_VEHICLE_COLOR_YELLOW 	= 9,	
	
}ICE_VCR_VEHICLECOLOR_E;

typedef struct
{
	ICE_S8      eVehiColor;
	ICE_FLOAT   fScore;    

	ICE_S8      szLabelTotal[40];           //total label
	ICE_U32     iLabelIndex;               // label index
	ICE_U32     iReserved[4];             //reserve
}ICE_VCR_RESULT_S;


typedef struct
{
	char * strModelPath;              //cnn model path

	ICE_U32 iInputW;                   
	ICE_U32 iInuptH;                    
	ICE_U32  iReserved[4];             
}ICE_VCR_INPUTPARAM_S;

typedef struct
{
	ICE_RECT_S stRect;
	ICE_U32    iType;//0-from plate.1-from vehicle detection
	ICE_U32    iReserved[4];
}ICE_VCR_RTEX_S;



//////////////////////////////////////////////////////////////////////////
//vehicle brand recognization  interface
ICE_EXPORTS ICE_HANDLE ICE_VehiColorRegCreate();
ICE_EXPORTS ICE_STATUS_E ICE_VehiColorRegInit(ICE_HANDLE _hHandle, ICE_VCR_INPUTPARAM_S *_pstInputRaram);

ICE_EXPORTS ICE_STATUS_E ICE_VehiColorRegProcess(ICE_HANDLE hHandle,ICE_YUV422P_IMAGE_S * InputImageyuv, 
												 ICE_VCR_RTEX_S _stRectex, ICE_VCR_RESULT_S *pstRult);

ICE_EXPORTS ICE_STATUS_E ICE_VehiColorRegRelease(ICE_HANDLE hHandle);

ICE_EXPORTS ICE_STATUS_E  ICE_VehiColorReg_GetVersion(void   *_hHandle, char * Version);


#endif // ice_vehibrand_interface_h__
