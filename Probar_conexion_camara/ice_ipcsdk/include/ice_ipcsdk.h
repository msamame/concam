#ifndef  ICE_IPCSDK__H_
#define  ICE_IPCSDK__H_

#include "ice_com_type.h"
#include "ice_base_type.h"
#include "ice_vdc_result.h"
#include <time.h>

//#define ICE_IPCSDK_TYPE _stdcall 
#define ICE_IPCSDK_TYPE _cdecl   

#ifdef ICE_IPCSDK_EXPORTS
#define ICE_IPCSDK_API __declspec(dllexport) 
#else
#define ICE_IPCSDK_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
*  @brief  Stream callback interface, SDK will callback this interface when there is data on the network 
*  @param  [OUT] pvParam			callback context
*  @param  [OUT] u8PayloadType		Payload of the type defined above
*  @param  [OUT] u32Timestamp		timestamp
*  @param  [OUT] pvData				Address of data received
*  @param  [OUT] s32Len				Length of data received
*/
typedef void (__stdcall * ICE_IPCSDK_OnStream)(void *pvParam, 
	ICE_U8 u8PayloadType, ICE_U32 u32Timestamp, 
	void *pvData, ICE_S32 s32Len);


/**
*  @brief  The image frame callback interface, which is called back by the SDK when an image is decoded
*  @param  [OUT] pvParam		callback context 
*  @param  [OUT] u32Timestamp	timestamp 
*  @param  [OUT] pu8Data		An array of image data addresses for y, u, and v, respectively
*  @param  [OUT] s32Linesize	An array of the length of each scan row, storing the length of each scan of y, u, and v, respectively
*  @param  [OUT] s32Width		image width
*  @param  [OUT] s32Height		image height
*  @param  [OUT] rawdata		raw data
*  @param  [OUT] rawlen			length of raw data
*/
typedef void (__stdcall * ICE_IPCSDK_OnFrame)(
	void *pvParam, ICE_U32 u32Timestamp, 
	ICE_U8 *pu8Data[], ICE_S32 s32Linesize[], 
	ICE_S32 s32Width, ICE_S32 s32Height, 
	ICE_U8 *rawdata, ICE_S32 rawlen);

/**
*  @brief  Global initialization
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Init();
/**
*  @brief  Global release
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Fini();

/**
*  @brief  Connect camera
*  @param  [IN] pcIP				camera ip
*  @param  [IN] u8OverTCP			Whether TCP mode is used (1 is used, 0 is not used)
*  @param  [IN] u16RTSPPort			rtsp port(554)
*  @param  [IN] u16ICEPort			The port corresponding to the private protocol(8117)
*  @param  [IN] u16OnvifPort		onvif port(8080)
*  @param  [IN] u8MainStream		Whether to request main stream (1 main stream, 0 substream)
*  @param  [IN] pfOnStream			Network stream callback address, can be NULL
*  @param  [IN] pvStreamParam		Network stream callback context
*  @param  [IN] pfOnFrame			The image frame callback address, which can be NULL, only makes sense if the u8ReqType contains REQ_TYPE_H264.
*  @param  [IN] pvFrameParam		Image frame callback context
*  @return SDK handle (return null if connection unsuccessful)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_Open(const ICE_CHAR *pcIP, ICE_U8 u8OverTCP, 
	ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, ICE_U16 u16OnvifPort, ICE_U8 u8MainStream, 
	ICE_IPCSDK_OnStream pfOnStream, void *pvStreamParam, 
	ICE_IPCSDK_OnFrame pfOnFrame, void *pvFrameParam);

/**
*  @brief  Connect camera
*  @param  [IN] pcIP				camera ip
*  @param  [IN] pcPasswd			password
*  @param  [IN] u8OverTCP			Whether TCP mode is used (1 is used, 0 is not used)
*  @param  [IN] u16RTSPPort			rtsp port(554)
*  @param  [IN] u16ICEPort			The port corresponding to the private protocol(8117)
*  @param  [IN] u16OnvifPort		onvif port(8080)
*  @param  [IN] u8MainStream		Whether to request main stream (1 main stream, 0 substream)
*  @param  [IN] pfOnStream			Network stream callback address, can be NULL
*  @param  [IN] pvStreamParam		Network stream callback context
*  @param  [IN] pfOnFrame			The image frame callback address, which can be NULL, only makes sense if the u8ReqType contains REQ_TYPE_H264.
*  @param  [IN] pvFrameParam		Image frame callback context
*  @return SDK handle (return null if connection unsuccessful)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_Open_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
	ICE_U8 u8OverTCP, ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
	ICE_U16 u16OnvifPort, ICE_U8 u8MainStream, 
	ICE_IPCSDK_OnStream pfOnStream, void *pvStreamParam, 
	ICE_IPCSDK_OnFrame pfOnFrame, void *pvFrameParam);
/**
*  @brief  Plate recognition data callback interface
*  @param  [OUT] pvParam                 callback context
*  @param  [OUT] pcIP                    camera ip
*/
typedef void (__stdcall * ICE_IPCSDK_OnPlate)(void *pvParam, const char *pcIp, T_LprResult *ptLprResult, const char *pFullPicData, int fullPicLen,
											  const char *pPlatePicData, int platePiclen, ICE_U32 u32Reserved1, ICE_U32 u32Reserved2);

/**
*  @brief  False license plate callback interface
*  @param  [OUT] pvParam                 callback context
*  @param  [OUT] pcIP                    camera ip
*  @param  [OUT] pcPicData               full picture data
*  @param  [OUT] u32PicLen               length of full picture data
*  @param  [OUT] strPlateNum			 plate number
*  @param  [OUT] u32CapTime				 capture time
*  @param  [OUT] strVehLogName           Car name
*  @param  [OUT] strResrv1				 reserve
*  @param  [OUT] u32VehType				 vehicle type
*  @param  [OUT] u32Resrv2				 reserve
*  @param  [OUT] u32ResultHigh           License plate identification data structure (ICE_VDC_PICTRUE_INFO_S) pointer high 8 bits
*  @param  [OUT] u32ResultLow            License plate identification data structure (ICE_VDC_PICTRUE_INFO_S) pointer low 8 bits
*/
typedef void (__stdcall * ICE_IPCSDK_OnFlasePlate)(void *pvParam, const ICE_CHAR *pcIP, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *strResrv1, ICE_U32 u32Resrv1, 
	ICE_CHAR *strResrv2, ICE_CHAR *strResrv3, ICE_U32 u32Resrv2, ICE_U32 u32Resrv3, ICE_U32 u32ResultHigh, ICE_U32 u32ResultLow);

/**
*  @brief  Connection with video streaming
*  @param  [IN] pcIP                    camera¡¯s ip
*  @param  [IN] u8OverTCP               Whether to use TCP mode£¨1:use tcp 0:don¡¯t use tcp, use udp£©
*  @param  [IN] u8MainStream            Whether the request main stream£¨0:substream 1:main stream  2:binocular second substream 3: binocular second main stream£©
*  @param  [IN] hWnd                    the window handle of preview the video
*  @param  [IN] pfOnPlate               Snap data callback
*  @param  [IN] pvPlateParam            The snap data callback context
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview(const ICE_CHAR *pcIP, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  P2P connection with video streaming
*  @param  [IN] pcDeveloperID			developer¡¯s ID
*  @param  [IN] pcKey					developer¡¯s Key
*  @param  [IN] pcSN					camera¡¯s SN
*  @param  [IN] u8OverTCP               Whether to use TCP mode£¨1:use tcp 0:don¡¯t use tcp,use udp£©
*  @param  [IN] u8MainStream            Whether the request main stream£¨1:main stream  0:substream 2:binocular second substream 3: binocular second main stream£©
*  @param  [IN] hWnd                    the window handle of preview the video
*  @param  [IN] pfOnPlate               Snap data callback
*  @param  [IN] pvPlateParam            The snap data callback context
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_P2P(const ICE_CHAR *pcDeveloperID, 
													 const ICE_CHAR *pcKey, 
													 const ICE_CHAR *pcSN, 
													 ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
													 ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  Connection with video streaming
*  @param  [IN] pcIP                    camera¡¯s ip
*  @param  [IN] pcPasswd                password
*  @param  [IN] u8OverTCP               Whether to use TCP mode£¨1:use tcp 0:don¡¯t use tcp, use udp£©
*  @param  [IN] u8MainStream            Whether the request main stream£¨0:substream 1:main stream  2:binocular second substream 3: binocular second main stream£©
*  @param  [IN] hWnd                    the window handle of preview the video
*  @param  [IN] pfOnPlate               Snap data callback
*  @param  [IN] pvPlateParam            The snap data callback context
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  P2P connection with video streaming
*  @param  [IN] pcDeveloperID			developer¡¯s ID
*  @param  [IN] pcKey					developer¡¯s Key
*  @param  [IN] pcSN					camera¡¯s SN
*  @param  [IN] pcPasswd				password
*  @param  [IN] u8OverTCP               Whether to use TCP mode£¨1:use tcp 0:don¡¯t use tcp,use udp£©
*  @param  [IN] u8MainStream            Whether the request main stream£¨1:main stream  0:substream 2:binocular second substream 3: binocular second main stream£©
*  @param  [IN] hWnd                    the window handle of preview the video
*  @param  [IN] pfOnPlate               Snap data callback
*  @param  [IN] pvPlateParam            The snap data callback context
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_Passwd_P2P(const ICE_CHAR *pcDeveloperID, 
															const ICE_CHAR *pcKey, 
															const ICE_CHAR *pcSN,
															const ICE_CHAR *pcPasswd, 
															ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
														    ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  Connect with video extension interface
*  @param  [IN] pcIP                    camera¡¯s ip
*  @param  [IN] u8OverTCP               Whether to use TCP mode£¨1:use tcp 0:don¡¯t use tcp, use udp£©
*  @param  [IN] u8MainStream            Whether the request main stream£¨0:substream 1:main stream  2:binocular second substream 3: binocular second main stream£©
*  @param  [IN] hWnd                    the window handle of preview the video
*  @param  [IN] pfOnPlate               Snap data callback
*  @param  [IN] pvPlateParam            The snap data callback context
*  @param  [IN] u16RTSPPort				rtsp port(554)
*  @param  [IN] u16ICEPort              The port corresponding to the private protocol(8117)
*  @param  [IN] u16OnvifPort			onvif port(8080)
*  @param  [IN] u16EvtpPort            evtp port(8200)
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreviewExt(const ICE_CHAR *pcIP, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
	ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
	ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort);

/**
*  @brief  Connect with video extension interface
*  @param  [IN] pcIP                    camera¡¯s ip
*  @param  [IN] pcPasswd				password
*  @param  [IN] u8OverTCP               Whether to use TCP mode£¨1:use tcp 0:don¡¯t use tcp, use udp£©
*  @param  [IN] u8MainStream            Whether the request main stream£¨0:substream 1:main stream  2:binocular second substream 3: binocular second main stream£©
*  @param  [IN] hWnd                    the window handle of preview the video
*  @param  [IN] pfOnPlate               Snap data callback
*  @param  [IN] pvPlateParam            The snap data callback context
*  @param  [IN] u16RTSPPort				rtsp port(554)
*  @param  [IN] u16ICEPort              The port corresponding to the private protocol(8117)
*  @param  [IN] u16OnvifPort			onvif port(8080)
*  @param  [IN] u16EvtpPort            evtp port(8200)
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreviewExt_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
	ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
	ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort);

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreviewExt_Passwd_P2P(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
														   ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
														   ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
														   ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
														   ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort,
														   const ICE_CHAR *pcSN,  
														   ICE_U16 u16ProxyPort23,
														   ICE_U16 u16ProxyPort69,
														   ICE_U16 u16ProxyPort80,
														   ICE_U16 u16ProxyPort8000,
														   ICE_U16 u16ProxyPort8300,
														   ICE_U16 u16ProxyPort8227);
/**
*  @brief  Connection without video streaming
*  @param  [IN] pcIP      ip address
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice(const ICE_CHAR *pcIP);

/**
*  @brief  P2P connected devices without video streaming
*  @param  [IN] pcDeveloperID  Developer's ID
*  @param  [IN] pcKey         Developer's Key
*  @param  [IN] pcSN		  Camera¡¯s SN
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN);

/**
*  @brief  Connection without video streaming
*  @param  [IN] pcIP      ip address
*  @param  [IN] pcPasswd  password
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd);

/**
*  @brief  P2P connected devices without video streaming
*  @param  [IN] pcDeveloperID	Developer's ID
*  @param  [IN] pcKey			Developer's Key
*  @param  [IN] pcSN			Camera¡¯s SN
*  @param  [IN] pcPasswd		password		
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_Passwd_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN, const ICE_CHAR *pcPasswd);

/**
*  @brief  £¨1£©	Connect to video stream only, not evtp (do not report identification data)
*  @param  [IN] pcIP	        camera ip
*  @param  [IN] u8MainStream    Whether to request main stream (1 main stream, 0 substream)
*  @param  [IN] hWnd            the window handle of preview the video
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDeviceEx(const ICE_CHAR *pcIP, ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  £¨1£©	Connect to video stream only, not evtp (do not report identification data)
*  @param  [IN] pcDeveloperID   developer ID
*  @param  [IN] pcKey           developer key
*  @param  [IN] pcSN            camera SN
*  @param  [IN] u8MainStream    Whether to request main stream (1 main stream, 0 substream)
*  @param  [IN] hWnd            the window handle of preview the video
*  @return SDK handle(If the connection is unsuccessful, the return value is null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDeviceEx_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN, 
																	  ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  start video
*  @param  [IN] hSDK          SDK handle
*  @param  [IN] u8MainStream  whether is main stream.1:main stream 0:subStream
*  @param  [IN] hWnd          window handle of video playeback
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartStream(ICE_HANDLE hSDK, 
	ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  stop video
*  @param  [IN] hSDK          SDK handle
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_StopStream(ICE_HANDLE hSDK);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetVideoWnd(ICE_HANDLE hSDK, ICE_U32 hWnd);

/**
*  @brief  Set stream data callback
*  @param  [IN] hSDK			SDK handle
*  @param  [IN] pfOnStream		Stream callback interface, SDK will callback this interface when there is data on the network
*  @param  [IN] pvParam			callback context
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetDataCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnStream pfOnStream, void *pvParam);

/**
*  @brief  Software Trigger extension
*  @param  [IN] hSDK          SDK handle 
*  @return 0:fail 1 success 2:Identification in progress  3:Algorithm not started
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TriggerExt(ICE_HANDLE hSDK);

/**
*  @brief  image frame callback
*  @param  [OUT] pvParam              callback context
*  @param  [OUT] u32Timestamp		  timestamp
*  @param  [OUT] pu8DataY             Array of image data, store y
*  @param  [OUT] pu8DataU             Array of image data, store u
*  @param  [OUT] pu8DataV             Array of image data, store v
*  @param  [OUT] s32LinesizeY         An array of the length of each scan row, storing the length of each scan of Y
*  @param  [OUT] s32LinesizeU         An array of the length of each scan row, storing the length of each scan of U
*  @param  [OUT] s32LinesizeV         An array of the length of each scan row, storing the length of each scan of V
*  @param  [OUT] s32Width             Image width
*  @param  [OUT] s32Height            Image Height
*/
typedef void (__stdcall * ICE_IPCSDK_OnFrame_Planar)(
	void *pvParam, ICE_U32 u32Timestamp, 
	ICE_U8 *pu8DataY, ICE_U8 *pu8DataU, ICE_U8 *pu8DataV, 
	ICE_S32 s32LinesizeY, ICE_S32 s32LinesizeU, ICE_S32 s32LinesizeV, 
	ICE_S32 s32Width, ICE_S32 s32Height);

/**
*  @brief  set image frame callback
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] pfOnFrame      image frame callback address
*  @param  [IN] pvParam        callback context
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetFrameCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnFrame_Planar pfOnFrame, void *pvParam);

/**
*  @brief  Set the plate recognition event callback
*  @param  [IN] hSDK            SDK handle
*  @param  [IN] pfOnPlate       the plate recognition event callback
*  @param  [IN] pvParam         callback context
*¡¡@return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetPlateCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvParam);

/**
*  @brief  Set fake license plate callback
*  @param  [IN] hSDK            SDK handle
*  @param  [IN] pfOnFlasePlate  callback
*  @param  [IN] pvParam         callback context
*¡¡@return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetFlasePlateCallback(ICE_HANDLE hSDK,
	ICE_IPCSDK_OnFlasePlate pfOnFlasePlate, void *pvParam);

/**
*  @brief  disconnect
*  @param  [IN] hSDK    SDK handle
*  return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Close(ICE_HANDLE hSDK);

/**
*  @brief  synchronization time
*  @param  [IN] hSDK		SDK handle
*  @param  [IN] u16Year		year
*  @param  [IN] u8Month		month
*  @param  [IN] u8Day		day
*  @param  [IN] u8Hour		hour
*  @param  [IN] u8Min		minute
*  @param  [IN] u8Sec		second
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SyncTime(ICE_HANDLE hSDK, 
	ICE_U16 u16Year, ICE_U8 u8Month, ICE_U8 u8Day, 
	ICE_U8 u8Hour, ICE_U8 u8Min, ICE_U8 u8Sec = 0);

/**
*  @brief  Get camera time
*  @param  [IN] hSDK			SDK handle
*  @param  [OUT] devtime		time structure
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSyncTime(ICE_HANDLE hSDK, tm* devtime);

/**
*  @brief  Get the camera network configuration
*  @param  [IN]  hSDK             SDK handle
*  @param  [OUT] pu32IP           camera IP address
*  @param  [OUT] pu32Mask         camera mask
*  @param  [OUT] pu32Gateway      camera gateway
*¡¡@return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetIPAddr(ICE_HANDLE hSDK, 
	ICE_U32 *pu32IP, ICE_U32 *pu32Mask, ICE_U32 *pu32Gateway);

/**
*  @brief   Set the camera network configuration
*  @param  [IN]  hSDK            SDK handle
*  @param  [IN] pu32IP           camera IP address
*  @param  [IN] pu32Mask         camera mask
*  @param  [IN] pu32Gateway      camera gateway
*¡¡@return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetIPAddr(ICE_HANDLE hSDK, 
	ICE_U32 u32IP, ICE_U32 u32Mask, ICE_U32 u32Gateway);

/**
*  @brief  Get alarm out configuration
*  @param  [IN]   hSDK				SDK handle
*  @param  [IN] u32Index			IO index(0::IO1, 1:IO2, 2:IO3, 3:IO4)
*  @param  [OUT] pu32IdleState		IO state(0:normally open, 1:normally closed)
*  @param  [OUT] pu32DelayTime		Time of switching state (-1 represents non-recovery.unit: s, value: -1,1-10)
*  @param  [OUT] pu32Reserve		reserve
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAlarmOutConfig(
	ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 *pu32IdleState, 
	ICE_U32 *pu32DelayTime, ICE_U32 *pu32Reserve);

/**
*  @brief  Set alarm out configuration
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] u32Index	IO 		index(0::IO1, 1:IO2, 2:IO3, 3:IO4)
*  @param  [IN] u32IdleState		IO state(0:normally open, 1:normally closed)
*  @param  [IN] u32DelayTime		Time of switching state (-1 represents non-recovery.unit: s, value: -1,1-10)
*  @param  [IN] u32Reserve			reserve
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAlarmOutConfig(
	ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 u32IdleState, 
	ICE_U32 u32DelayTime, ICE_U32 u32Reserve);

/**
*  @brief  reboot
*  @param  [IN] hSDK SDK handle
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Reboot(ICE_HANDLE hSDK);

/**
*  @brief  Get osd stack configuration
*  @param  [IN] hSDK             SDK handle
*  @param  [IN] pstOSDAttr       OSD structure(ICE_OSDAttr_S)
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOSDCfg(ICE_HANDLE hSDK, ICE_OSDAttr_S *pstOSDAttr);

/**
*  @brief  Set osd stack configuration
*  @param  [IN] hSDK             SDK handle
*  @param  [IN] pstOSDAttr       OSD structure(ICE_OSDAttr_S)
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOSDCfg(ICE_HANDLE hSDK, const ICE_OSDAttr_S *pstOSDAttr);

/**
*  @brief  Open gate
*  @param  [IN] hSDK  SDK handle
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_OpenGate(ICE_HANDLE hSDK);

/**
*  @brief  Control gate(alarmout)
*  @param  [IN] hSDK            SDK handle
*  @param  [IN] u32Index        u32Index IO index(0: IO1: IO2: IO3: IO4)
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ControlAlarmOut(ICE_HANDLE hSDK, ICE_U32 u32Index);

/**
*  @brief  Start intercom
*  @param  [IN] hSDK	SDK handle
*  @return 1 success, 0 fail, 2 intercom is occupied
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BeginTalk(ICE_HANDLE hSDK);

/**
*  @brief  Start intercom
*  @param  [IN] hSDK			SDK handle
*  @param  [OUT] stTalkInfo		intercom info structure
*  @param  [IN] nResvr1			reserve
*  @param  [IN] nResvr2			reserve
*  @return 1 success, 0 fail, 2 intercom is occupied
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BeginTalk_Ex(ICE_HANDLE hSDK, ICE_TALK_INFO *stTalkInfo, ICE_U32 nResvr1, ICE_U32 nResvr2);

/**
*  @brief  Reject intercom
*  @param  [IN] hSDK  SDK handle
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_RefuseTalk(ICE_HANDLE hSDK);

/**
*  @brief  ignore talk
*  @param  [IN] hSDK  SDK handle
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_IgnoreTalk(ICE_HANDLE hSDK);

/**
*  @brief  Over intercom
*  @param  [IN] hSDK  SDK handle
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_EndTalk(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_IsTalking(ICE_HANDLE hSDK);

/**
*  @brief  Get serial port configuration
*  @param  [IN]  hSDK             SDK handle
*  @param  [OUT] pstUARTCfg       serial port configuration(ICE_UART_PARAM)
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetUARTCfg(ICE_HANDLE hSDK, ICE_UART_PARAM *pstUARTCfg);

/**
*  @brief  Set serial port configuration
*  @param  [IN]  hSDK            SDK handle
*  @param  [IN] pstUARTCfg       serial port configuration(ICE_UART_PARAM)
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetUARTCfg(ICE_HANDLE hSDK, const ICE_UART_PARAM *pstUARTCfg);

/*  @brief  Set the black and white list parameters 
*   @Note:
*Off-line association: when the camera is off the network, the front-end camera can only match the white-list association and open the gate.
*This mode is mainly used for whitelist which is done by platform in the case of network connection and by camera in the case of offline.
*Real-time work: no judgment network or network state, both by the front camera white list of association matching and open gate work.
*  @param  [IN]  hSDK        SDK handle
*  @param  [IN] whiteList   black and white list parameters
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetNewWhiteListParam(ICE_HANDLE hSDK, WhiteList_Param* whiteList);

/*  @brief  Get the black and white list parameters
*   @Note:
*Off-line association: when the camera is off the network, the front-end camera can only match the white-list association and open the gate.
*This mode is mainly used for whitelist which is done by platform in the case of network connection and by camera in the case of offline.
*Real-time work: no judgment network or network state, both by the front camera white list of association matching and open gate work.
*  @param  [IN]  hSDK        SDK handle
*  @param  [OUT] whiteList   black and white list parameters
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetNewWhiteListParam(ICE_HANDLE hSDK,  WhiteList_Param* whiteList);

/**
*  @brief  get device status
*  @param  [IN] hSDK      sdk handle
*  @return 0 offline 1 online
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetStatus(ICE_HANDLE hSDK);

/**
*  @brief  Capture image
*  @param  [IN]  hSDK            SDK handle
*  @param  [IN]  pcPicData       The buffer address of the captured image
*  @param  [IN]  u32PicSize      The buffer size of the captured image
*  @param  [OUT] pu32PicLen      The real size of the captured image
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Capture(ICE_HANDLE hSDK, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicSize, ICE_U32 *pu32PicLen);

/**
*  @brief  Capture image and save the image
*  @param  [IN]  hSDK            SDK handle
*  @param  [IN]  filepath        Image path
*  @return 1 success 0 capture is fail
-2 The filename of the saved file is incorrect and does not contain "." (for example: "001.jpg")
-3 The filename of the saved file is not correct. The filename should be similar to "001.jpg" (for example, "001.jpg")
-4 The file path is not the correct path
-5 The save path character cannot be found (for example, only CDEF disk, but saved in H disk)
-6 The file path was not created successfully
-7 One frame of cached image data is empty
-8 Failed to create JPEG compressed file

*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Capture_BZ(ICE_HANDLE hSDK, ICE_CHAR *filepath);

/**
*  @brief  Transparent serial port receives events (rs485)
*  @param  [OUT] pvParam      callback context
*  @param  [OUT] pcIP         camera ip
*  @param  [OUT] pcData       serial data
*  @param  [OUT] u32Len       length of serial data
*/
typedef void (__stdcall * ICE_IPCSDK_OnSerialPort)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  Set transparent serial port receives events(rs485)
*  @param  [IN] hSDK                   SDK handle
*  @param  [IN] pfOnSerialPort         callback event
*  @param  [IN] pvSerialPortParam      callback context
*  @return void 
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  Transparent serial port receives events(rs232)
*  @param  [OUT] pvParam      callback context
*  @param  [OUT] pcIP         camera ip
*  @param  [OUT] pcData       serial data
*  @param  [OUT] u32Len       length of serial data
*/
typedef void (__stdcall * ICE_IPCSDK_OnSerialPort_RS232)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  Set transparent serial port receives events(rs232)
*  @param  [IN] hSDK                   SDK handle
*  @param  [IN] pfOnSerialPort         callback event
*  @param  [IN] pvSerialPortParam      callback context
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack_RS232(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort_RS232 pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  Send transparent serial port data(rs485)
*  @param  [IN] hSDK      SDK handle
*  @param  [IN] pcData    Serial data
*  @param  [IN] u32Len    length of serial data
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TransSerialPort(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  Send transparent serial port data(rs232)
*  @param  [IN] hSDK      SDK handle
*  @param  [IN] pcData    Serial data
*  @param  [IN] u32Len    length of serial data
*  @return 0 fail, 1 success 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TransSerialPort_RS232(ICE_HANDLE hSDK, 
	ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  Get the number of black and white lists
*          Note: this interface is called to allocate memory before the whitelist item is retrieved.
*  @param  [IN]  hSDK         SDK handle
*  @param  [OUT] pu32Count    Total number of list items
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListGetCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  Gets the black and white list item
*  @param  [IN] hSDK             SDK handle
*  @param  [IN] s32Index         index of list which need to get
*  @param  [OUT] pcNumber        plate number
*  @param  [OUT] pcDateBegin     begin data(format is yyyy/MM/dd)
*  @param  [OUT] pcDateEnd       end data(format is yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     begin time(format is HH:mm:ss)
*  @param  [OUT] pcTimeEnd       end time(format is HH:mm:ss)
*  @param  [OUT] pcType          type('W' white list /'B' black list)
*  @param  [OUT] pcRsrv2         remark
*  @param  [OUT] pcRsrv3         reserve
*  @param  [OUT] pcRsrv4         reserve
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListGetItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcType, ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  Edit B & W list item
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			index of list which need to get
*  @param  [IN] pcNumber			plate number
*  @param  [IN] pcDateBegin			begin data(format is yyyy/MM/dd)
*  @param  [IN] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [IN] pcTimeBegin			begin time(format is HH:mm:ss)
*  @param  [IN] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [IN] pcType				type('W':whitelist/'B':blacklist)
*  @param  [IN] pcRmark				remark
*  @param  [IN] pcRsrv2				reserve
*  @param  [IN] pcRsrv3				reserve
*  @param  [IN] pcRsrv4				reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListEditItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, const ICE_CHAR* pcType, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  Add B & W list item
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			index of list which need to get
*  @param  [IN] pcNumber			plate number
*  @param  [IN] pcDateBegin			begin data(format is yyyy/MM/dd)
*  @param  [IN] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [IN] pcTimeBegin			begin time(format is HH:mm:ss)
*  @param  [IN] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [IN] pcType				type('W':whitelist/'B':blacklist)
*  @param  [IN] pcRmark				remark
*  @param  [IN] pcRsrv2				reserve
*  @param  [IN] pcRsrv3				reserve
*  @param  [IN] pcRsrv4				reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListInsertItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, const ICE_CHAR* pcType, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  Delete a B & W list item
*  @param  [IN] hSDK              SDk handle
*  @param  [IN] pcNumber          plate number which need to delete
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDeleteItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  Delete all B & W list item
*  @param  [IN] hSDK              SDk handle
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDelAllItems_ByNumber(ICE_HANDLE hSDK);

/**
*  @brief  Find a black and white list item
*  @param  [IN] hSDK             SDK handle
*  @param  [IN] s32Index         plate number of list which need to find
*  @param  [OUT] pcNumber        plate number
*  @param  [OUT] pcDateBegin     begin data(format is yyyy/MM/dd)
*  @param  [OUT] pcDateEnd       end data(format is yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     begin time(format is HH:mm:ss)
*  @param  [OUT] pcTimeEnd       end time(format is HH:mm:ss)
*  @param  [OUT] pcType          type('W' white list /'B' black list)
*  @param  [OUT] pcRemark        remark
*  @param  [OUT] pcRsrv2         reserve
*  @param  [OUT] pcRsrv3         reserve
*  @param  [OUT] pcRsrv4         reserve
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListFindItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, ICE_CHAR* pcType, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  off-line continuation event callback
*  @param  [OUT] pvParam               callback context
*  @param  [OUT] pcIP                  camera¡¯s ip
*  @param  [OUT] u32CapTime            capture time
*  @param  [OUT] pcNumber              plate number
*  @param  [OUT] pcColor               plate color
*  @param  [OUT] pcPicData             full picture¡¯s data
*  @param  [OUT] u32PicLen             length of full picture¡¯s data
*  @param  [OUT] pcCloseUpPicData      plate picture¡¯s data
*  @param  [OUT] u32CloseUpPicLen      length of plate picture¡¯s data
*  @param  [OUT] s16PlatePosLeft       The top left abscissa of the license plate area
*  @param  [OUT] s16PlatePosTop        The top left ordinate of the license plate area
*  @param  [OUT] s16PlatePosRight      The lower right abscissa of the license plate area
*  @param  [OUT] s16PlatePosBottom     The lower right ordinate of the license plate area
*  @param  [OUT] fPlateConfidence      The score of the license plate								   
*  @param  [OUT] u32VehicleColor       vehicle color
*  @param  [OUT] u32PlateType          plate type
*  @param  [OUT] u32VehicleDir         vehicle¡¯s direction
*  @param  [OUT] u32AlarmType          vehicle¡¯s direction
*  @param  [OUT] u32Reserved1          reserve param
*  @param  [OUT] u32Reserved2          reserve param
*  @param  [OUT] u32Reserved3          reserve param
*  @param  [OUT] u32Reserved4          reserve param
*/
typedef void (__stdcall * ICE_IPCSDK_OnPastPlate)(void *pvParam, const ICE_CHAR *pcIP, 
	ICE_U32 u32CapTime, const ICE_CHAR *pcNumber, const ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *pcCloseUpPicData, ICE_U32 u32CloseUpPicLen, 
	ICE_S16 s16PlatePosLeft, ICE_S16 s16PlatePosTop, ICE_S16 s16PlatePosRight, ICE_S16 s16PlatePosBottom, 
	ICE_FLOAT fPlateConfidence, ICE_U32 u32VehicleColor, ICE_U32 u32PlateType, ICE_U32 u32VehicleDir, 
	ICE_U32 u32AlarmType, ICE_U32 u32Reserved1, ICE_U32 u32Reserved2, ICE_U32 u32Reserved3, ICE_U32 u32Reserved4);

/**
*  @brief  Set the off-line continuation event callback
*  @param  [IN] hSDK               SDK handle
*  @param  [IN] pfOnPastPlate      off-line continuation event callback
*  @param  [IN] pvPastPlateParam   callback context
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetPastPlateCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnPastPlate pfOnPastPlate, void *pvPastPlateParam);

/**
*  @brief  device event callback
*  @param  [OUT] pvParam             callback context
*  @param  [OUT] pvHandle			sdk handle
*  @param  [OUT] pcIP                camera ip
*  @param  [OUT] u32EventType        Event type 0: offline 1: online 
*  @param  [OUT] u32EventData1       reserve parameter
*  @param  [OUT] u32EventData2       reserve parameter
*  @param  [OUT] u32EventData3       reserve parameter
*  @param  [OUT] u32EventData4       reserve parameter
*/
typedef void (__stdcall * ICE_IPCSDK_OnDeviceEvent)(void *pvParam, void *pvHandle, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32EventData1, ICE_U32 u32EventData2, ICE_U32 u32EventData3, ICE_U32 u32EventData4);

/**
*  @brief  Set device event callback
*  @param  [IN] hSDK                         SDK handle
*  @param  [IN] pfOnDeviceEvent              device event callback
*  @param  [IN] pvDeviceEventParam           callback context
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetDeviceEventCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnDeviceEvent pfOnDeviceEvent, void *pvDeviceEventParam);

/**
*  @brief  Get the camera MAC address
*  @param  [IN] hSDK                  SDK handle
*  @param  [OUT] szDevID              MAC address
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDevID(ICE_HANDLE hSDK, ICE_CHAR* szDevID);

/**
*  @brief  Begin record
*  @param  [IN] hSDK                 SDK handle
*  @param  [IN] pcFileName           file name of video
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartRecord(ICE_HANDLE hSDK, const ICE_CHAR *pcFileName);

/**
*  @brief  stop record
*  @param  [IN] hSDK                 SDK handle
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_StopRecord(ICE_HANDLE hSDK);

/**
 *  @brief  Write user data
 *  @param  [IN] hSDK       SDK handle
 *  @parame [IN] pcData     data that needs to be written
 *  @return 1 success,0 fail
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WriteUserData(ICE_HANDLE hSDK, const char* pcData);

/**
 *  @brief  Read user data
 *  @param  [IN] hSDK       SDK handle
 *  @param  [OUT] szData    user data of read out 
 *  @param  [IN]  nSize     The maximum length of data read out, i.e. the size of user data allocation
 *  @return 1 success, 0 fail
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ReadUserData(ICE_HANDLE hSDK, char* pcData, int nSize);

/**
*  @brief  Write binary data
*  @param  [IN] hSDK        SDK handle
*  @param  [IN] pcData      data that needs to be written
*  @param  [IN] nOffset     The offset of the data  data that needs to be written
*  @param  [IN] nLen        the length of the data that needs to be written
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WriteUserData_Binary(
	ICE_HANDLE hSDK, const char* pcData, ICE_U32 nOffset, ICE_U32 nLen);

/**
*  @brief  Read binary data
*  @param  [IN] hSDK        SDK handle
*  @param  [OUT] pcData     user data of read out
*  @param  [IN] nSize       The maximum length of data read out, i.e. the size of user data allocation
*  @param  [IN] nOffset     The offset of the data being read
*  @param  [OUT] nLen       The length of data that needs to be read
*  @return -1 fail, >=0 success(Represents the string length)
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ReadUserData_Binary(
	ICE_HANDLE hSDK, char* pcData, ICE_U32 nSize, ICE_U32 nOffset, ICE_U32 nLen);

/**
*  @brief  Get total number of white list (excluding blacklist)
*  @param  [IN] hSDK              SDK handle
*  @param  [OUT] pu32Count        total number of white list
*  @param 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetWhiteCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  Get white list items (excluding blacklist)
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			index of list which need to get
*  @param  [OUT] pcNumber			plate number
*  @param  [OUT] pcDateBegin		begin data(format is yyyy/MM/dd)
*  @param  [OUT] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin		begin time(format is HH:mm:ss)
*  @param  [OUT] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [OUT] pcRmark			remark
*  @param  [OUT] pcRsrv2			reserve
*  @param  [OUT] pcRsrv3			reserve
*  @param  [OUT] pcRsrv4			reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetWhiteItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  Edit whitelist items (excluding blacklist)
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			index of list which need to get
*  @param  [IN] pcNumber			plate number
*  @param  [IN] pcDateBegin			begin data(format is yyyy/MM/dd)
*  @param  [IN] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [IN] pcTimeBegin			begin time(format is HH:mm:ss)
*  @param  [IN] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [IN] pcRmark				remark
*  @param  [IN] pcRsrv2				reserve
*  @param  [IN] pcRsrv3				reserve
*  @param  [IN] pcRsrv4				reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EditWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  Add whitelist items (excluding blacklist)
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			index of list which need to get
*  @param  [IN] pcNumber			plate number
*  @param  [IN] pcDateBegin			begin data(format is yyyy/MM/dd)
*  @param  [IN] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [IN] pcTimeBegin			begin time(format is HH:mm:ss)
*  @param  [IN] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [IN] pcRmark				remark
*  @param  [IN] pcRsrv2				reserve
*  @param  [IN] pcRsrv3				reserve
*  @param  [IN] pcRsrv4				reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_InsertWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief get total number of black list
*  @param  [IN]  hSDK            SDK handle
*  @param  [OUT] pu32Count       total number of black list
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetBlackCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  Get black list items (excluding whitelist)
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			index of list which need to get
*  @param  [OUT] pcNumber			plate number
*  @param  [OUT] pcDateBegin		begin data(format is yyyy/MM/dd)
*  @param  [OUT] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin		begin time(format is HH:mm:ss)
*  @param  [OUT] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [OUT] pcRmark			remark
*  @param  [IN] pcRsrv2				reserve
*  @param  [OUT] pcRsrv3			reserve
*  @param  [OUT] pcRsrv4			reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetBlackItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  Edit blacklist items (excluding whitelist)
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			index of list which need to get
*  @param  [IN] pcNumber			plate number
*  @param  [IN] pcDateBegin			begin data(format is yyyy/MM/dd)
*  @param  [IN] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [IN] pcTimeBegin			begin time(format is HH:mm:ss)
*  @param  [IN] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [IN] pcRmark				remark
*  @param  [IN] pcRsrv2				reserve
*  @param  [IN] pcRsrv3				reserve
*  @param  [IN] pcRsrv4				reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EditBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  Add blacklist items (excluding whitelist)
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			index of list which need to get
*  @param  [IN] pcNumber			plate number
*  @param  [IN] pcDateBegin			begin data(format is yyyy/MM/dd)
*  @param  [IN] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [IN] pcTimeBegin			begin time(format is HH:mm:ss)
*  @param  [IN] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [IN] pcRmark				remark
*  @param  [IN] pcRsrv2				reserve
*  @param  [IN] pcRsrv3				reserve
*  @param  [IN] pcRsrv4				reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_InsertBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  Delete all whitelist items (excluding blacklist)
*  @param  [IN] hSDK             SDK handle
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DelAllWhiteItems(ICE_HANDLE hSDK);

/**
*  @brief  Delete all blacklist items (excluding whitelist)
*  @param  [IN] hSDK             SDK handle
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DelAllBlackItems(ICE_HANDLE hSDK);

/**
*  @brief  Delete a white list item (excluding blacklist)
*  @param  [IN] hSDK             SDK handle
*  @param  [IN] pcNumber		 plate number which need to delete
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DeleteWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  find a whitelist items (excluding blacklist)
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			plate number of list which need to get
*  @param  [OUT] pcNumber			plate number
*  @param  [OUT] pcDateBegin		begin data(format is yyyy/MM/dd)
*  @param  [OUT] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin		begin time(format is HH:mm:ss)
*  @param  [OUT] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [OUT] pcRmark			remark
*  @param  [OUT] pcRsrv2			reserve
*  @param  [OUT] pcRsrv3			reserve
*  @param  [OUT] pcRsrv4			reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_FindWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  Delete a blacklist item (excluding white list)
*  @param  [IN] hSDK             SDK handle
*  @param  [IN] pcNumber		 plate number which need to delete
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DeleteBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  find a blacklist items (excluding whitelist)
*  @param  [IN]  hSDK				SDK handle
*  @param  [IN] s32Index			plate number of list which need to get
*  @param  [OUT] pcNumber			plate number
*  @param  [OUT] pcDateBegin		begin data(format is yyyy/MM/dd)
*  @param  [OUT] pcDateEnd			end date(format is yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin		begin time(format is HH:mm:ss)
*  @param  [OUT] pcTimeEnd			end time(format is HH:mm:ss)
*  @param  [OUT] pcRmark			remark
*  @param  [OUT] pcRsrv2			reserve
*  @param  [OUT] pcRsrv3			reserve
*  @param  [OUT] pcRsrv4			reserve
*  @return 1 success,0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_FindBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  Voice broadcast by index number (unicast)
*  @param  [IN] hSDK       SDK handle
*  @param  [IN] nIndex     voice file index
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Broadcast(ICE_HANDLE hSDK, ICE_U16 nIndex);

/**
*  @brief  Set priority city
*  @param  [IN] hSDK         SDK handle
*  @param  [IN] u32Index     The index number of the priority city
*  @return 1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetCity(ICE_HANDLE hSDK, ICE_U32 u32Index);

/**
*  @brief  Voice multicast by index number
*  @param  [IN] hSDK        SDK handle
*  @param  [IN] pcIndex     A string containing a speech sequence number
							Note: the middle can be used; \t \n or space separate;such as: 1 2 3 4 OR 1,2,3,4
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BroadcastGroup(ICE_HANDLE hSDK, const ICE_CHAR* pcIndex);

/**
*  @brief  Search device
*  @param  [IN] szDevs       String of device MAC address and IP address
*							   String of device MAC address and IP address,format is:mac ip\r\n  such as:
*							   00-00-00-00-00-00 192.168.55.150\r\n
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SearchDev(char* szDevs);

/**
*  @brief  Get DNS configuration
*  @param  [IN] hSDK		SDK handle
*  @param  [OUT] pu32DNS	preferred DNS
*  @param  [OUT] pu32DNS2	alternate DNS
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDNSAddr(ICE_HANDLE hSDK, ICE_U32 *pu32DNS, ICE_U32 *pu32DNS2);

/**
*  @brief  Set DNS configuration
*  @param  [IN] hSDK		SDK handle
*  @param  [IN] pu32DNS	preferred DNS
*  @param  [IN] pu32DNS2	alternate DNS
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDNSAddr(ICE_HANDLE hSDK, ICE_U32 u32DNS, ICE_U32 u32DNS2);

/**
*  @brief  log configuration
*  @param  [IN] openLog     Log enabled or not
*  @param  [IN] logPath     Log path, default is D:\
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_LogConfig(int openLog, char *logPath);

/**  
*  @brief  Feature code comparison
*  @param  [IN] _pfResFeat1     The 1st characteristic code to be compared
*  @param  [IN] _iFeat1Len      The 1st characteristic code¡¯s length. Now you need to enter 20
*  @param  [IN] _pfReaFeat2     The 2st characteristic code to be compared
*  @param  [IN] _iFeat2Len      The 2st characteristic code¡¯s length .Now you need to enter 20
*  @return  Matching degree, range: 0-1, the larger the value, the better the match
*/
ICE_IPCSDK_API ICE_FLOAT ICE_IPCSDK_TYPE ICE_IPCSDK_VBR_CompareFeat(ICE_FLOAT *_pfResFeat1, ICE_U32 _iFeat1Len,
												   ICE_FLOAT *_pfReaFeat2, ICE_U32 _iFeat2Len);

/**
*  @brief  Get offline voice broadcast configuration
*  @param  [IN] hSDK          SDK handle
*  @param  [OUT] pstParam      Offline voice broadcast parameters
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineAoParam(ICE_HANDLE hSDK, OfflineAoParam *pstParam);

/**
*  @brief  Set offline voice broadcast configuration
*  @param  [IN] hSDK          SDK handle
*  @param  [IN] pstParam      Offline voice broadcast parameters
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineAoParam(ICE_HANDLE hSDK, const OfflineAoParam *pstParam);

/**
*  @brief  broadcast by filename (unicast)
*  @param  [IN] hSDK        SDK handle
*  @param  [IN] pcName      file name of the voice broadcast
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Broadcast_ByName(ICE_HANDLE hSDK, const ICE_CHAR* pcName);

/**
*  @brief  Voice multicast by filename
*  @param  [IN] hSDK        SDK handle
*  @param  [IN] pcName      A string containing the name of the voice file
							Note: the middle can be used; \t \n or space separate; Such as: 1 2 3 4 OR 1,2,3,4
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BroadcastGroup_ByName(ICE_HANDLE hSDK, const ICE_CHAR* pcName);

/**
*  @brief  Get IO state
*  @param  [IN] hSDK				SDK handle
*  @param  [IN] u32Index		 	IO serial number£¨0: IO1 1:IO2 2:IO3 3:IO4£©
*  @param  [OUT] pu32IOState		IO state (0: data available 1: no data available)
*  @param  [OUT] pu32Reserve1	reserve
*  @param  [OUT] pu32Reserve2	reserve  
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetIOState(ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 *pu32IOState, 
												ICE_U32 *pu32Reserve1, ICE_U32 *pu32Reserve2);

/**
*  @brief  Get camera forces offline configuration
*  @param  [IN] hSDK        SDK handle
*  @param  [OUT] pcName     Camera forced offline parameter structure
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetForceCareraOfflineParam(ICE_HANDLE hSDK, Force_camera_offline_cfg_param *pstParam);

/**
*  @brief  Set camera forces offline configuration
*  @param  [IN] hSDK       SDK handle
*  @param  [IN] pcName     Camera forced offline parameter structure
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetForceCareraOfflineParam(ICE_HANDLE hSDK, const Force_camera_offline_cfg_param *pstParam);

/**
*  @brief  Camera upgrade
*  @param  [IN] hSDK        SDK handle
*  @param  [IN] szFilePath     The path of the upgraded file
*  @return	0 The upgrade failed due to network reasons
			1 successful upgrade
			2 insufficient Flash space
			3 check failure
			4 the timeout
			5 the file does not exist
			6 File operation failed
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Update(ICE_HANDLE hSDK, const ICE_CHAR *szFilePath);

/**
*  @brief  set encryption on and off
*  @param  [IN] hSDK        SDK handle
*  @param  [IN] ucEncId     Whether encrypted (unencrypted if 0, encrypted if others)
*  @param  [IN] szPwd       camera¡¯s password
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EnableEnc(ICE_HANDLE hSDK, 
	ICE_U32 u32EncId, const char *szPwd);

/**
*  @brief  Modify camera¡¯s password
*  @param  [IN] hSDK        SDK handle 
*  @param  [IN] szOldPwd    Camera¡¯s old password
*  @param  [IN] szNewPwd    Camera¡¯s new password
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ModifyEncPwd(ICE_HANDLE hSDK, 
	const char *szOldPwd, const char *szNewPwd);

/**
*  @brief  Set camera¡¯s password
*  @param  [IN] hSDK        SDK handle
*  @param  [IN] szPwd       camera¡¯s password`
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDecPwd(ICE_HANDLE hSDK, const char *szPwd);


/**
*  @brief  Get the camera version information
*  @param  [IN] hSDK				SDK handle
*  @param  [IN] pstSysVersion       camera version information structure
*  @return 0 fail 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetCameraInfo(ICE_HANDLE hSDK, ICE_CameraInfo *pstCameraInfo);

/**
*  @brief  Set custom validation information
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] old_lics       Old custom check information (note: this parameter is empty when set for the first time)
*  @param  [IN] new_lics       New custom calibration information
*  @return 0 fail, 1 success 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLicense(ICE_HANDLE hSDK, char *old_lics, char *new_lics);

/**
*  @brief  Validates custom information
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] license        Custom information for validation
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CheckLicense(ICE_HANDLE hSDK, char *license);

/**
*  @brief  Set identify area configuration
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] nLeft          Identify the left coordinate point of the region (take the upper left corner as the origin of coordinates)
*  @param  [IN] nBottom        Identify the bottom coordinate point of the region (take the upper left corner as the origin of coordinates)
*  @param  [IN] nRight         Identify the right coordinate point of the region (take the upper left corner as the origin of coordinates)
*  @param  [IN] nTop           Identify the top coordinate point of the region (take the upper left corner as the origin of coordinates)
*  @param  [IN] nWidth         At what resolution are the coordinates obtained, represent the width (for example, at 1280*720, the width is 1280)
*  @param  [IN] nHeight        At what resolution are the coordinates obtained, represent the height (for example, at 1280*720, the height is 720)
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLoop(ICE_HANDLE hSDK, ICE_U32 nLeft, ICE_U32 nBottom, 
	ICE_U32 nRight, ICE_U32 nTop, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  Get identify area configuration
*  @param  [IN] hSDK            SDK handle
*  @param  [OUT] nLeft          Identify the left coordinate point of the region (take the upper left corner as the origin of coordinates)
*  @param  [OUT] nBottom        Identify the bottom coordinate point of the region (take the upper left corner as the origin of coordinates)
*  @param  [OUT] nRight         Identify the right coordinate point of the region (take the upper left corner as the origin of coordinates)
*  @param  [OUT] nTop           Identify the top coordinate point of the region (take the upper left corner as the origin of coordinates)
*  @param  [OUT] nWidth         At what resolution are the coordinates obtained, represent the width (for example, at 1280*720, the width is 1280)
*  @param  [OUT] nHeight        At what resolution are the coordinates obtained, represent the height (for example, at 1280*720, the height is 720)
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLoop(ICE_HANDLE hSDK, ICE_U32 *nLeft, ICE_U32 *nBottom, 
	ICE_U32 *nRight, ICE_U32 *nTop, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  Set trigger mode configuration
*  @param  [IN] hSDK			SDK handle
*  @param  [IN] u32TriggerMode	trigger mode(0: coil trigger 1: video trigger 2: mixed trigger)
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTriggerMode(ICE_HANDLE hSDK, ICE_U32 u32TriggerMode);

/**
*  @brief  Get trigger mode configuration
*  @param  [IN] hSDK			SDK handle
*  @param  [OUT] u32TriggerMode trigger mode(0: coil trigger 1: video trigger 2: mixed trigger)
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTriggerMode(ICE_HANDLE hSDK, ICE_U32 *pu32TriggerMode);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDrawLoop(ICE_HANDLE hSDK, int nEnableDraw);


/*
*  @brief  Set LED screen information
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] ledConfig      LED screen information structure
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLedCreen_Config(ICE_HANDLE hSDK,ICE_OFFLINE_LED_CONFIG* ledConfig);

/*
*  @brief  Get LED screen information
*  @param  [IN] hSDK           SDK handle
*  @param  [OUT] ledConfig     LED screen information structure
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLedCreen_Config(ICE_HANDLE hSDK, ICE_OFFLINE_LED_CONFIG* ledConfig);

/*
*  @brief  Set billing rule configuration information
*  @param  [IN] hSDK           SDK handle
*  @param  [IN]charRule        Offline billing rule structure
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineCharge_Rule(ICE_HANDLE hSDK, ICE_OFFLINE_CHARGE_RULE* charRule);

/*
*  @brief  Get billing rule configuration information
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] charRule       Offline billing rule structure
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineCharge_Rule(ICE_HANDLE hSDK, ICE_OFFLINE_CHARGE_RULE* charRule);


/*
*  @brief  Set offline multicast configuration
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] multiCast      offline multicast configuration structure
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineMulticast_Config(ICE_HANDLE hSDK, ICE_OFFLINE_MULTICAST_CONFIG* multiCast);

/*
*  @brief  Get offline multicast configuration
*  @param  [IN] hSDK           SDK handle
*  @param  [OUT] multiCast     offline multicast configuration structure
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineMulticast_Config(ICE_HANDLE hSDK, ICE_OFFLINE_MULTICAST_CONFIG* multiCast);

/*
*  @brief  Get vehicle information on the scene
*  @param  [IN] hSDK				 SDK handle
*  @param  [OUT] pcVehicleInfo       buffer address of vehicle information on the scene
*  @param  [IN] u32PicSize			 size of buffer address of vehicle information on the scene
*  @param  [OUT] pu32PicLen	         actual length of vehicle information on the scene
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getOfflineVehicleInfo(ICE_HANDLE hSDK, ICE_CHAR * pcVehicleInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  Get vehicle information on the scene of the specified license plate number
*  @param  [IN] hSDK				 SDK handle
*  @param  [IN] pcPlateNumber		 The license plate number to check
*  @param  [OUT] pcVehicleInfo       buffer address of vehicle information on the scene 
*  @param  [IN] u32PicSize			 size of buffer address of vehicle information on the scene
*  @param  [OUT] pu32PicLen	         actual length of vehicle information on the scene
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getOfflineVehicleInfo_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR *pcPlateNumber, 
																 ICE_CHAR * pcVehicleInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  Get all offline billing data(Does not contain data for which offline billing is 0)
*  @param  [IN] hSDK				 SDK handle
*  @param  [OUT] pcVehicleInfo       Offline billing data buffer address
*  @param  [IN] u32PicSize			 Size of offline billing data buffer address
*  @param  [OUT] pu32PicLen	         actual length of offline billing data
*  @return  1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  Get all offline billing data (including data with offline billing of 0)
*  @param  [IN] hSDK				 SDK handle
*  @param  [OUT] pcVehicleInfo       Offline billing data buffer address
*  @param  [IN] u32PicSize			 Size of offline billing data buffer address
*  @param  [OUT] pu32PicLen	         actual length of offline billing data
*  @return  1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getAllPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/**
*  @brief  IO state change event callback
*  @param  [OUT] pvParam 		callback context
*  @param  [OUT] pcIP			camera ip
*  @param  [OUT] u32EventType 	event type 0:IO change
*  @param  [OUT] u32IOData1		When the event type is 0, it means IO1¡¯s state
*  @param  [OUT] u32IOData2		When the event type is 0, it means IO2¡¯s state
*  @param  [OUT] u32IOData3		When the event type is 0, it means IO3¡¯s state
*  @param  [OUT] u32IOData4		When the event type is 0, it means IO4¡¯s state
*/
typedef void (__stdcall * ICE_IPCSDK_OnIOEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32IOData1, ICE_U32 u32IOData2, ICE_U32 u32IOData3, ICE_U32 u32IOData4);

/**
*  @brief  Set the IO state change event callback
*  @param  [IN] hSDK                     SDK handle
*  @param  [IN] pfOnIOEvent              IO state change event callback
*  @param  [IN] pvIOEventParam           callback context
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetIOEventCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnIOEvent pfOnIOEvent, void *pvIOEventParam);

/**
*  @brief  Set vehicle identification parameters
*  @param  [IN] hSDK							SDK handle
*  @param  [IN] s32FilterByPlate				Whether to filter unlicensed vehicles (1: filter, do not output unlicensed vehicles; 0: filter, output unlicensed vehicles)
*  @param  [IN] s32EnableNoPlateVehicleBrand    Whether to support the recognition of unlicensed vehicles(1:support 0:don¡¯t support)
*  @param  [IN] s32EnableNoPlateVehicleBrand    Whether to support the recognition of licensed vehicles(1:support 0:don¡¯t support)
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetVehicleBrand(ICE_HANDLE hSDK, ICE_S32 s32FilterByPlate, 
	ICE_S32 s32EnableNoPlateVehicleBrand, ICE_S32 s32EnableVehicleBrand);

/**
*  @brief  Get vehicle identification parameters
*  @param  [IN] hSDK							SDK handle
*  @param  [OUT] s32FilterByPlate				Whether to filter unlicensed vehicles (1: filter, do not output unlicensed vehicles; 0: filter, output unlicensed vehicles)
*  @param  [OUT] s32EnableNoPlateVehicleBrand   Whether to support the recognition of unlicensed vehicles(1:support 0:don¡¯t support)
*  @param  [OUT] s32EnableNoPlateVehicleBrand   Whether to support the recognition of licensed vehicles(1:support 0:don¡¯t support)
*  @return  1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetVehicleBrand(ICE_HANDLE hSDK, ICE_S32 *ps32FilterByPlate, 
	ICE_S32 *ps32EnableNoPlateVehicleBrand, ICE_S32 *ps32EnableVehicleBrand);

/*
*  @brief  Get the offline billing information of local
*  @param  [IN] hSDK				 SDK handle
*  @param  [OUT] pcVehicleInfo       Offline billing data buffer address
*  @param  [IN] u32PicSize			 Size of offline billing data buffer address
*  @param  [OUT] pu32PicLen	         actual length of offline billing data
*  @return   1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getLocalPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  Get device parameter
*  @param  [IN] hSDK				 SDK handle
*  @param  [OUT] stDeviceParam       device parameter structure
*  @return   1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDeviceParam(ICE_HANDLE hSDK, ICE_DEVICE_PARAM *stDeviceParam);

/*
*  @brief  Get the camera type£¨82/83£©
*  @param  [IN] hSDK				SDK handle
*  @param  [OUT] pu32DevType		camera type(1 represent 82; 2 represent 83)
*  @return  1 success 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDeviceType(ICE_HANDLE hSDK, ICE_U32 *pu32DevType);

/*
*  @brief  Broadcast wav files
*  @param  [IN] hSDK	  SDK handle
*  @param  [IN] pcData    memory address of wav data
*  @param  [IN] u32Len    length of wav data
*  @return 1 success, 0 fail
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BroadcastWav(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len);

/*
*  @brief  Bulk import of black and white list, support for CSV only
*  @param  [IN] hSDK	  SDK handle
*  @param  [IN] pFileName Black and white list file path, support for CSV files only
*  @param  [IN] s32Type   Operation type 0: import and append, 1: import and override
*  @return  0 The upgrade failed due to network reasons
			1 successful upgrade
			2 insufficient Flash space
			3 check failure
			4 the timeout
			5 the file does not exist
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UpdateWhiteListBatch(ICE_HANDLE hSDK, ICE_CHAR *szFilePath, ICE_S32 s32Type);

/*
*  @brief  Get additional alarm input parameters
*  @param  [IN] hSDK           SDK handle
*  @param  [OUT] pstParam      alarm input parameters
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAlarmInExt(ICE_HANDLE hSDK, ALARM_IN_EXT *pstParam);

/*
*  @brief  Set additional alarm input parameters
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] pstParam       alarm input parameters  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAlarmInExt(ICE_HANDLE hSDK, ALARM_IN_EXT *pstParam);


/**
*  @brief  Camera intercom state change callback event
*  @param  [OUT] pvParam            callback context
*  @param  [OUT] pcIP               camera ip
*  @param  [OUT] u32EventType       Event type, 
									0: ordinary non-intercom state 
									1: trigger intercom 
									2: intercom in progress (the intercom initiated by the camera end has been connected to a client connected to the camera end) 
									3: the intercom initiated by the camera end is rejected by a management end 
									4: intercom interrupt
*  @param  [OUT] pcTalkIp			Camera IP, when the event type is 2, represents the IP of the management end connected to the camera end; 
									When the event type is 3, it indicates that the IP of the management side is refusing to talk to the camera
*  @param  [OUT] u32Reserve1		reserve 
*  @param  [OUT] u32Reserve2        reserve 
*  @param  [OUT] u32Reserve3        reserve
*  @param  [OUT] u32Reserve4        reserve
*/
typedef void (__stdcall * ICE_IPCSDK_OnTalkEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, const ICE_CHAR *pcTalkIp, 
											   ICE_U32 u32Reserve1, ICE_U32 u32Reserve2, ICE_U32 u32Reserve3, ICE_U32 u32Reserve4);

/**
*  @brief  Set the camera intercom state change callback event
*  @param  [IN] hSDK                     SDK handle
*  @param  [IN] pfOnIOEvent              camera intercom state change callback event
*  @param  [IN] pvIOEventParam           callback context
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetTalkEventCallBack(ICE_HANDLE hSDK, ICE_IPCSDK_OnTalkEvent pfOnTalkEvent, void *pvTalkEventParam);

/**
*  @brief  Get irregular quadrilateral identification region
*  @param  [IN]  hSDK                     SDK handle
*  @param  [OUT] stVLoopRect              Irregular recognition region structure
*  @param  [IN]  nWidth					  At what resolution are the coordinates obtained, represent the width (for example, at 1280*720, the width is 1280)
*  @param  [IN]  nHeight				  At what resolution are the coordinates obtained, represent the height (for example, at 1280*720, the height is 720)
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetQuadRangle(ICE_HANDLE hSDK, ICE_QUADRANGLE_S *stVLoopRect, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  Set irregular quadrilateral identification region
*  @param  [IN]  hSDK                     SDK handle
*  @param  [IN]  stVLoopRect              Irregular recognition region structure
*  @param  [IN]  nWidth					  At what resolution are the coordinates obtained, represent the width (for example, at 1280*720, the width is 1280)
*  @param  [IN]  nHeight				  At what resolution are the coordinates obtained, represent the height (for example, at 1280*720, the height is 720)
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetQuadRangle(ICE_HANDLE hSDK, const ICE_QUADRANGLE_S *stVLoopRect, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  Get camera UID information
*  @param  [IN]   hSDK                     SDK handle
*  @param  [OUT]  pstParam				   UID information structure
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetUID(ICE_HANDLE hSDK, UID_PARAM *pstParam);

/**
*  @brief  Connect evtp ( Evtp represents the event distribution protocol, 
			and all license plate recognition events must be connected to this protocol before data can be reported)
*  @param  [IN] hSDK			SDK handle
*  @param  [IN] pcPasswd		Connection password (if the password is null, it is unencrypted connection; if not, it is encrypted connection)
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartEvtp(ICE_HANDLE hSDK, const ICE_CHAR* pcPasswd);

/**
*  @brief  Disconnect evtp
*  @param  [IN] hSDK			SDK handle
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StopEvtp(ICE_HANDLE hSDK);

/**
*  @brief  Zoom control
*  @param  [IN] hSDK			SDK handle
*  @param  [IN] pstParam		Zoom adjustment parameter structure
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAFZoom(ICE_HANDLE hSDK, const ICE_IPC_AF_ZOOM *pstParam);

/**
*  @brief  Get lens type
*  @param  [IN] hSDK			SDK handle
*  @param  [IN] pu32LensType	lens type, 1: Fixed focus, 2:zoom
*  @return 0 fail, 1 success
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLensType(ICE_HANDLE hSDK, ICE_U32 *pu32LensType);

/**
*  @brief  S=Get snap image osd overlay configuration
*  @param  [IN] hSDK			SDK handle
*  @param  [OUT] pstParam	    snap image osd overlay configuration structure
*  @return	0 fail
			1 success
			2 Camera version not supported
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSnapOsdCfg(ICE_HANDLE hSDK, T_SnapOsdCfg *pstParam);

/**
*  @brief  Set snap image osd overlay configuration
*  @param  [IN] hSDK			SDK handle
*  @param  [IN] pstParam	    snap image osd overlay configuration structure
*  @return	0 fail
			1 success
			2 Camera version not supported
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSnapOsdCfg(ICE_HANDLE hSDK, const T_SnapOsdCfg *pstParam);

/*
*  @brief  Set the exposure parameters
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] pstParam	   exposure parameters structure
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetExpAttr(ICE_HANDLE hSDK, const ICE_ExpAttr_S *pstParam);

/*
*  @brief  Get the exposure parameters
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] pstParam       exposure parameters structure
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetExpAttr(ICE_HANDLE hSDK, ICE_ExpAttr_S *pstParam);

/*
*  @brief  Set the offline charging screen display serial port
*  @param  [IN] hSDK           SDK handle
*  @param  [IN] pstUARTCfg     Serial structure
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOffline_UART(ICE_HANDLE hSDK, const ICE_UART_PARAM *pstUARTCfg);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_RegLprResult(ICE_HANDLE hSDK, int iNeedPic, int iReserve);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UnregLprResult(ICE_HANDLE hSDK);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_RegSerialPortEvent(ICE_HANDLE hSDK, ICE_U32 uiChannel);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UnregSerialPortEvent(ICE_HANDLE hSDK);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_RegIOEvent(ICE_HANDLE hSDK);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UnregIOEvent(ICE_HANDLE hSDK);

#ifdef __cplusplus
}
#endif

#endif