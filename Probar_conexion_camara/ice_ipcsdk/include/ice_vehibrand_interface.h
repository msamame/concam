#ifndef ice_vehibrand_interface_h__
#define ice_vehibrand_interface_h__

#include "ice_base_type.h"

#define VBR_RES_TOPN 10               //Number of results returned

typedef struct
{
	ICE_S8 szLogName[20];             //Brand
	ICE_S8 szSubLogName[20];          //Sub brand
	ICE_S8 szProductYearName[20];     //product year

	ICE_S8 szLabelTotal[40];           //total label
	ICE_U32 iLabelIndex;               //total label index
	ICE_FLOAT fScore;                  //Confidence
	ICE_FLOAT fResFeature[VBR_RES_TOPN*2];
	ICE_U32  iReserved[4];             //reserve
}ICE_VBR_RESULT_S;
#endif // ice_vehibrand_interface_h__
