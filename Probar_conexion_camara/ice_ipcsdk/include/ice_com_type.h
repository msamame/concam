/*! \file ice_com_type.h
\brief ice_com_type.h document.
*/
#ifndef _ICE_COM_TYPE_H_
#define _ICE_COM_TYPE_H_

#include "ice_base_type.h"

//! \defgroup group_communication Communication protocol

#ifdef __cplusplus
extern "C"
{
#endif


#define ICE_BUF_SIZE_CONTROL	(64-32)
#define ICE_BUF_SIZE_EVENT		(64-32)
#define ICE_BUF_SIZE_VPRO		(16*1024-32)
#define ICE_BUF_SIZE_CONFIG		(128*1024-32)

#define ICE_BUFLEN_PACKET	(1024*512)

#define ICE_EVENT_ID_SLAVE_MIN	0x00000000
#define ICE_EVENT_ID_SLAVE_MAX	0xFFFFFFFF

#define ICE_BUF_SIZE_FRAME		(1920*1080*2 + 128)


//! \ingroup group_communication
//! General Operation Data
typedef struct 
{
	ICE_U32	u32Size;							//!<  Packet length
	ICE_U32	u32Type;							//!<  type
	ICE_U32	u32Status;							//!<  status
	ICE_U32	u32Channel;							//!<  channel number
	ICE_U32	u32Time;							//!<  time
	ICE_U32	u32Date;							//!<  date
	ICE_U32	u32Id;								//!<  id
	ICE_U32	u32Level;							//!<  level
} ICE_OPER_DATA_S;


#define MAX_OSD_TEXT 64
#define MAX_CUSTOM_OSD_LINE_NUM 6

#define MAX_OSD_TEXT_SFM 32
#define MAX_CUSTOM_OSD_LINE_NUM_SFM 4

typedef struct
{        
	//video     
	ICE_U32 u32OSDLocationVideo;                     //stack position(0:top left, 1:top right, 2:bottom left, 3:bottom right, 4:top center, 5:bottom center)
	ICE_U32 u32ColorVideo;                           //color(format as:0x00bbggrr)
	ICE_U32 u32DateVideo;                            // Whether or not to stack date and time (1:stack 0:does not stack)         
	ICE_U32 u32License;                              // Whether to stack authorization information (1:stack 0:does not stack)  
	ICE_U32 u32CustomVideo;                          // Whether to stack custom information (1:stack 0:does not stack)      
	char szCustomVideo[MAX_OSD_TEXT];                //reserve  
	//jpeg       
	ICE_U32 u32OSDLocationJpeg;                      // stack position(0:top left, 1:top right, 2:bottom left, 3:bottom right, 4:top center, 5:bottom center)   
	ICE_U32 u32ColorJpeg;                            // color(format as:0x00bbggrr)
	ICE_U32 u32DateJpeg;                             // Whether or not to stack date and time (1:stack 0:does not stack)          
	ICE_U32 u32Algo;                                 // Whether or not to stack algorithm information (1:stack 0:does not stack)          
	ICE_U32 u32DeviceID;                             //reserver   
	char szDeviceID[MAX_OSD_TEXT];                   // reserver 
	ICE_U32 u32DeviceName;                           // reserver      
	char szDeviceName[MAX_OSD_TEXT];                 // reserver 
	ICE_U32 u32CamreaLocation;                       // reserver 
	char szCamreaLocation[MAX_OSD_TEXT];             // reserver 
	ICE_U32 u32SubLocation;                          // reserver      
	char szSubLocation[MAX_OSD_TEXT];                // reserver 
	ICE_U32 u32ShowDirection;                        // reserver  
	ICE_U32 u32CameraDirection;                      // reserver 
	ICE_U32 u32CustomJpeg;                           // Whether to stack custom information (1:stack 0:does not stack)   
	ICE_U32 u32ItemDisplayMode;                      // Picture information display mode, 0:multi-line display, 1:single-line display       
	ICE_U32 u32DateMode;                             // Date display mode, 0:XXXX /xx/xx 1: DD day, mm month, YYYY year
	ICE_U32 u32BgColor;                              // OSD background color, 0:background full transparent, 1:background black       
	ICE_U32 u32FontSize;                             // Font size, 0: small, 1: medium 2: large  
	ICE_U32 u32ExpandMode;								// Expansion mode, 0: no expansion, 1: image expansion, 2: image under expansion  
	char szCustomJpeg[MAX_OSD_TEXT - 20];                       //reserve               
	char szCustomVideo6[MAX_CUSTOM_OSD_LINE_NUM * MAX_OSD_TEXT];// Video custom information 
	//(note: 83 camera video custom information, up to 4 lines, each line 32 bytes (including newline); 
	//82 the camera supports 6 lines of 64 bytes per line (including newline characters); Use "\r\n
	char szCustomJpeg6[MAX_CUSTOM_OSD_LINE_NUM * MAX_OSD_TEXT]; // Image custom information 
	//(note: 83 camera video custom information, up to 4 lines, each line 32 bytes (including newline); 
	//82 the camera supports 6 lines of 64 bytes per line (including newline characters); Use "\r\n" 
} ICE_OSDAttr_S;


#define MAX_USEABLE_UART_CNT 2  //Maximum number of configurable serial ports

//Camera forced offline parameter structure
typedef struct {
	int force_offline_enable; //1:Set the camera to offline 0��Set the camera to online
	int reserved[15];
}Force_camera_offline_cfg_param;

typedef struct

{
	int uartEn;						// Whether the serial port is enabled.0:disable 1:enable
	int uartWorkMode;				//Serial port working mode, 0: license plate protocol, 1: transparent serial port
	int baudRate;					// baudRate 0:1200、1:2400、2:4800、3:9600、4:19200、5:38400、6:115200
	int dataBits;      				//databit
	int parity;						// parity,0:none、1:odd、2:even、3:mark、4:space 
	int stopBits;       			//stopBits,0:1、1:2 
	int flowControl;    			//flow control,0:none、1:hardware,[2:Xon/Xoff(82 camera)],[2:Xon(83 camera),3��Xoff(83 camera)]
	int LEDControlCardType;			// LED Control Card Type
	int LEDBusinessType;		 	// LED Business Type .0:mode1,1:mode2
	int u32UartProcOneReSendCnt;	// Retransmission times [0~3]
	char screen_mode;            	// Screen display mode, 1 screen display, 2 passthrough
	char as32Reserved[7]; 			//reserve
}ice_uart;


typedef struct
{
	ice_uart uart_param[MAX_USEABLE_UART_CNT];// Multiple serial port arrays
	int as32Reserved[10];                     //reserve
}ICE_UART_PARAM;


typedef struct
{
	int mode;					//0:unconnected connection, 1:real-time operation, 2:unconnected switching or non-operation
	int match;					// White list similar match, range (60%-100%), default: 80%
	int black_mode;				// Blacklist associated gate mode, 0:unassociated gate, 1:open gate
	int black_match;			// Blacklist similarity match, range (60%-100%), default: 80%
	int temp_mode;				// Temporary vehicle associated road brake mode, 0:does not open the gate, 1:opens the gate
	int ignoreHZ_flag;			// Ignore Chinese symbols, 0:does not ignore, 1:ignores
	int allow_unmatch_chars_cnt;// The number of mismatched characters ranges [0 ~3]
	int new_version;			//  new or old WhiteList flag, 1:new, 0:old.
	int Jing_mode;				// The police car model
	int Army_mode;				// Military vehicles model 
	int Antifake_mode;			//Anti-false license plate mode. 0:normally open the gate, 1:not open the gate (offline mode)
	int NewEnergy_mode;			//new energy license plate mode. 0 is not related to gate opening, 1 is related to gate opening
	int EmergencyMode; //Emergency license plate mode. 0 is not related to the opening of the gate, 1 is related to the opening of the gate
	char reserved[80]; 
} WhiteList_Param;

//Zoom adjustment parameter structure
typedef struct _IPC_AF_ZOOM
{
	ICE_U8 num;          //1:zoom,2:focus
	ICE_U8 direction;    //1:zoom in, 2:zoom out
	ICE_U8  speed;       //speed:0-1;0:stop,1: operate
	ICE_U8 reserved[20]; //reserve
}ICE_IPC_AF_ZOOM;

//Offline voice broadcast parameters 
typedef struct
{
	ICE_U32 u32Mode;				//Broadcast mode. 0:no broadcast, 1:broadcast (original welcome/bon voyage), 2:broadcast + match white list
	ICE_U32 u32Broadcast_order;		//Broadcast order. 0:not broadcast license plate. 1:last broadcast license plate 
									//2:first broadcast license plate and then broadcast other information
	ICE_U32 u32Reserved[15];		//reserve           
} OfflineAoParam;

//get camera version
typedef struct
{
	char szAppVersion[128];   // Camera software version information
	char szAlgoVersion[256];  // Camera algorithm information
	int szIsEnc;              // Whether the camera is encrypted. 0 not encryption, 1 encryption
	char szAppTime[16];       // Release time
	char szReserved[1024];    //reserve
} ICE_CameraInfo;


/**********************************offline multicast configuration************************************************/
typedef struct
{
	ICE_U8	ucEnabled;      //1:enable 0:disable
	ICE_U16	usOfflinePort;  //multicast port
	ICE_U32	uiIP;			//multicast ip
	ICE_U8	aucReserved[10];
}ICE_OFFLINE_MULTICAST_CONFIG;
/******************************offline multicast configuration*************************************************/


/******************************LED screen information*************************************************/
#define MAX_LED_CONTENT   64     //Maximum number of characters per line
#define MAX_LED_COUNT     4      //Maximum number of screens

typedef enum
{
	LED_SCREEN_1 = 0,    //plate protocol
	LED_SCREEN_2,        // Transparent serial port
	LED_SCREEN_3,        // LED screen control
	LED_SCREEN_4,        //mix mode
	LED_SCREEN_5,        // plate protocol
	LED_SCREEN_6,        // plate protocol
	LED_SCREEN_7,        // plate protocol
	LED_SCREEN_8,        //rs232 wifi probe protocol
	LED_SCREEN_9,        // plate protocol
	LED_SCREEN_10,       // plate protocol
	LED_SCREEN_11,
	LED_SCREEN_12,
	LED_SCREEN_13,
	LED_SCREEN_14,
	LED_SCREEN_15,
	LED_SCREEN_16,
	LED_SCREEN_17, 
	/*************** The new protocol supports offline billing ***************************/
	LED_SCREEN_18,    // plate protocol
	LED_SCREEN_19, 
	LED_SCREEN_20, 
	LED_SCREEN_21, 
	LED_SCREEN_22, 
	LED_SCREEN_23,
	LED_SCREEN_MAX
}E_LedScreenType;

typedef enum
{
	COLOR_TYPE_RED =0, 
	COLOR_TYPE_GREEN,   
	COLOR_TYPE_YELLO,   
	COLOR_TYPE_BLUE ,   
	COLOR_TYPE_WHITE,   
	COLOR_TYPE_BLACK,   
	COLOR_TYPE_OTHER,  
	COLOR_TYPE_YELLOW_GREEN, 
	COLOR_TYPE_ALL,      
}E_ColorType;//color type

typedef enum
{
	LED_SUB_MOD_VEH_PLATE=0,					// License plate display 
	LED_SUB_MOD_VEH_WELCOME,					//Welcome message display 
	LED_SUB_MOD_VEH_PAY,						// Parking pay display
	LED_SUB_MOD_VEH_TIME,					// Parking time display
	LED_SUB_MOD_VEH_PERIOD,					// Monthly lease validity period display
	LED_SUB_MOD_TIME,							//time display
	LED_SUB_MOD_VEH_LEFT,					//display of remaining parking Spaces
	LED_SUB_MOD_CUSTOM,						//custom content display
	LED_SUB_MOD_MAX,
}E_SubLedMode;

typedef struct
{
	ICE_U8   ucContentEnable;				//Enable customization. 0:disable,1:enable
	ICE_U8   ucTimeEnable;					//Whether to enable time. 0:disable,1:enable
	ICE_U8   ucInterval;						//time interval.unit:s
	ICE_U8   aucContent[MAX_LED_CONTENT];	// Custom character
	ICE_U8   ucColor;							//color, 0:red, 1:green,2:yellow
	ICE_U8   ucLeftVehEnable;				// Whether to enable  the remaining parking space. 0:disable,1:enable
	ICE_U8   aucReserved[9];					//reserve
}T_SubLedSetup;   //idle display

typedef struct
{
	ICE_U8   ucContentEnable;				// Enable customization. 0:disable,1:enable
	ICE_U8   ucVehTypeEnable;				// whether to display vehicle type. 0:disable,1:enable
	ICE_U8   ucPlateEnable;					//whether to display license plate. 0:disable,1:enable
	ICE_U8   ucLeftDaysEnable;				// Whether to display the remaining days. 0:disable,1:enable
	ICE_U8   ucParkPay;						// Whether to display parking charge information. 0:disable,1:enable
	ICE_U8   ucParkLastTime;					// Whether to display the parking time. 0:disable,1:enable
	ICE_U8   ucTmpCardColor;					// Temporary car color. 0:red, 1:green,2:yellow
	ICE_U8   ucMonthCardColor;				//color of car with monthly pass. 0:red, 1:green,2:yellow
	ICE_U8   aucContent[MAX_LED_CONTENT];	// Custom character
	ICE_U8   aucReserved[10];				//reserve
}T_M_SubLedSetup;  //busy display

typedef struct
{
	ICE_U8   ucContentEnable;              // Enable customization. 0:disable,1:enable
	ICE_U8   ucVehTypeEnable;              // whether to display vehicle type. 0:disable,1:enable
	ICE_U8   ucPlateEnable;                //whether to display license plate. 0:disable,1:enable
	ICE_U8   ucLeftDaysEnable;             // Whether to display the remaining days. 0:disable,1:enable
	ICE_U8   ucParkPay;                   // Whether to display parking charge information. 0:disable,1:enable 
	ICE_U8   ucParkLastTime;               // Whether to display the parking time. 0:disable,1:enable
	ICE_U8   ucWelorByeEnable;             // Whether to broadcast welcome/farewell words 0 do not broadcast 1 broadcast
	ICE_U8   aucWelorByeContent[MAX_LED_CONTENT]; // Farewell words
	ICE_U8   aucSelfContent[MAX_LED_CONTENT];     //Custom character
	ICE_U8   aucReserved[10];                     //reserve
}T_M_AudioLedSetup;  // voice broadcast content when busy


typedef struct  
{
	E_LedScreenType    sreenType;							// screen protocol type
	ICE_U32            screenMode;							//screen mode
	ICE_U32            cameraType;							//camera type ,1: entrance 2:exit
	ICE_U8             ucAudioEnable;						// whether voice broadcast

	ICE_U8             ucReserved[3];						//reserve
	T_SubLedSetup      atSubLedInIdle[MAX_LED_COUNT];		//entrance idle
	T_M_SubLedSetup   atSubLedInBusy[MAX_LED_COUNT];		//entrance busy
	T_M_AudioLedSetup atSubLedInBusyAudio;					//voice broadcast content when the entrance is busy
	T_SubLedSetup      atSubLedOutIdle[MAX_LED_COUNT];		//exit idle
	T_M_SubLedSetup   atSubLedOutBusy[MAX_LED_COUNT];		//exit busy
	T_M_AudioLedSetup atSubLedOutBusyAudio;					// voice broadcast content when the exit is busy
	ICE_U32            uc485ctrlEnable;						//485 control whether enable,1:enable,0:disable
	ICE_U32            ucLeftVehPlace;						// number of parking Spaces remaining


	ICE_U16			   FK_password;							//FK password
	ICE_U8             ucFKEncipherment;					//whether FK protocol is encrypt
	ICE_U8             aucReserved[89];						//reserve
}ICE_OFFLINE_LED_CONFIG;

/******************************************LED screen information******************************************************/



/********************************Offline billing rules********************************************************/
#define MAX_PAY_ITEM           2      //The largest type of paid policy
#define MAX_TIMESECTION_NUM    3      //Maximum policy group
#define MAX_PARTTIME_SET_NUM   40     //Maximum time setting group

typedef enum
{
	PAY_MODE_UNKNOW = 0,
	PAY_MODE_ONTIME,		//Billing on time
	PAY_MODE_TIMES,			//Billing on times
	PAY_MODE_TIME_SECTION,	//Billing on time segment
	PAY_MODE_PARTTIME,		//Billing by hour
	PAY_MODE_MAX
}E_PayMode;   //billing type

typedef enum
{
	STRATEGY_TYPE_UNKNOW = 0,
	STRATEGY_TYPE_NOPAY,	//free
	STRATEGY_TYPE_CYCLE,	//Charge per cycle
	STRATEGY_TYPE_BYTIME,	//Charge for hours
	STRATEGY_TYPE_MAX
}E_StrategyType;  //A billing strategy for less than one cycle

typedef struct
{
	ICE_U8	ucEnable;			//whether to enable.1:enable,0:disable
	ICE_U16	usCyclePay;			//Periodic charge amount
	ICE_U16	usStartPay;			//Start amount
	ICE_U16	usFreeTime;			// free time
	ICE_U16	usCycleTime;		//Billing cycle
	ICE_U16	usStartTime;		//start time
	ICE_U16	usTotalPreDay;		// max pay
	ICE_U8	aucReserved[10];	//reserve
}T_OnTimePay;  //Billing on time

typedef struct
{
	ICE_U8	ucEnable;			//whether to enable.1:enable,0:disable
	ICE_U8	ucMaxTime;			//max times
	ICE_U16	usPayOne;			//One-time charge amount
	ICE_U16	usFreeTime;			//free time
	ICE_U16	usFreeStartTime;	//Free start time, in minutes
	ICE_U16	usFreeEndTime;		//Free end time, in minutes
	ICE_U8	aucReserved[10];	//reserve
}T_TimesPay; //Billing on times

typedef struct
{
	ICE_U8	ucEnable;
	ICE_U16	usCyclePay;				//Periodic charge amount
	ICE_U16	usStartPay;				//start pay
	ICE_U16	usFreeTime;				//free time
	ICE_U16	usCycleTime;			//Billing cycle
	ICE_U16	usStartTime;			//start time
	ICE_U16	usTotalPreDay;			//Time limit amount
	ICE_U16	usSectionStartTime;		//The beginning of a period, in minutes
	ICE_U16	usSectionEndTime;		//The end of a period, in minutes
	ICE_U8	aucReserved[10];		//reserve
}T_TimeSectionPay;	//Billing on times

typedef struct  
{
   ICE_U16  parkTime;	//parking time
   ICE_U16  usPay;		//pay
}SetionSet;

typedef struct 
{
	ICE_U16		usCyclePayMax;		//Period maximum charge amount
	ICE_U16		usFreeTime;			//free time
	SetionSet   usPartTime[MAX_PARTTIME_SET_NUM]; //Time set
	ICE_U8		aucReserved[10];	//reserve
}T_PartTimesPay;


typedef struct 
{
	ICE_U32           offEnable;		//Offline enablement. 0:offline enablement, 1:forces enablement, 2:not to enable
	ICE_U32		      ExtranceRule;     //Opening configuration, entrance temporary car. 0:does not open, 1:opens 
	ICE_U32			  ExitRule;		    //Opening configuration, exit temporary car. 0:does not open, 1:opens 

	E_PayMode		  ucRuleMode; 		//binding mode
	E_StrategyType	  ucStrategyType;	//binding strategy
	ICE_U16			  usTimeLength;		//Under billable time cycle

	T_OnTimePay       atOnTimePay[MAX_PAY_ITEM]; //billing on time, small car:atOnTimePay[0], big car:atOnTimePay[1] 
	T_TimesPay		  atTimesPay[MAX_PAY_ITEM];  //billing on times, small car:atTimesPay[0], big car:atTimesPay[1] 
	T_TimeSectionPay  atTimeSectionPay[MAX_PAY_ITEM*MAX_TIMESECTION_NUM];  //Billing on time segment, small car:0,1,2, big car:3,4,5
    T_PartTimesPay    atPartTimePay;             //Billing by hour

	ICE_U8			  aucReserved[30];
}ICE_OFFLINE_CHARGE_RULE;
/********************************Offline billing rules********************************************************/

typedef struct  
{
	ICE_S8 szDeviceType[32];		//device type
	ICE_S8 szDeviceMac[16];			//MAC address
	ICE_S8 szDeviceVersion[256];	//device version
	ICE_S8 szReserve[128];
}ICE_DEVICE_PARAM;



typedef struct tagT_ProductInfo
{
	ICE_S8 ProductModel[128];
	ICE_S8 HardwareModel[128];
} T_ProductInfo;

typedef struct
{
	int alarm_in_type_sec; 		// Alarm input 2 alarm type, 0 normally open, 1 normally closed
	int which_for_hardtriger; 	// Which alarm input is selected for ground sensor signal . 0 is group 1, 1 is group 2.
	int alarm_in_type_third; 	// Alarm input 3 alarm type, 0 normally open, 1 normally closed
	int alarm_in_type_fourth; 	// Alarm input 4 alarm type, 0 normally open, 1 normally closed
	int related_talkbacks;  		// Whether or not to associate with speech intercom USES the relationship with and to determine the associated items 
	//(currently only IO2 IO3 IO4 is supported)  
	int u32Researve[17];			//reserve
}ALARM_IN_EXT;


#define NETADDR_LEN (64)
typedef struct 
{
	ICE_S8 talk_status;  //0: Successful intercom connection, return IP. -1: already in intercom, return intercom IP
	ICE_U8 link_netaddr[NETADDR_LEN];//IP
	ICE_U8 reserved[48];
}ICE_TALK_INFO;

typedef struct
{
	unsigned char ucUID[32];		//UID
	unsigned char ucReserved[32];	//reserve
}UID_PARAM;

typedef struct T_OsdInfoCfg{
	ICE_S32	iEnable;	
	ICE_S32 iLocation;	
	ICE_S32 iType;		
	char acCustomInfo[MAX_OSD_TEXT];
	char acResrv[64];
}T_OsdInfoCfg;

typedef struct T_SnapOsdCfg{
	ICE_S32 ibgColorMode;	
	ICE_S32 iDateMode;		
	ICE_S32 iFontSize;		
	ICE_S32 iLineMode;		
	T_OsdInfoCfg tOsdInfoCfg[MAX_CUSTOM_OSD_LINE_NUM];
	char acResrv[128];
}T_SnapOsdCfg;

typedef struct {
	ICE_S32 mac_list_size;  //  list number
	ICE_S8 phone_mac_list[100][18];
	ICE_S8 reserved[50*18];
} ICE_Phone_Mac_List;
typedef struct
{
	ICE_U32 u32Expline;			
	ICE_S32 s32AGain;			
	ICE_S32 s32DGain;			

	ICE_U32 u32Mode;			

	ICE_U32 u32DayBegin;		
	ICE_U32 u32DayEnd;			
	ICE_U32 u32DayExplineMin;	
	ICE_U32 u32DayExplineMax;	
	ICE_S32 s32DayAGainMin;		
	ICE_S32 s32DayAGainMax;		
	ICE_S32 s32DayDGainMin;		
	ICE_S32 s32DayDGainMax;		

	ICE_U32 u32NightBegin;		
	ICE_U32 u32NightEnd;		
	ICE_U32 u32NightExplineMin;	
	ICE_U32 u32NightExplineMax;
	ICE_S32 s32NightAGainMin;	
	ICE_S32 s32NightAGainMax;	
	ICE_S32 s32NightDGainMin;	
	ICE_S32 s32NightDGainMax;	

	ICE_U32 u32OtherExplineMin;	
	ICE_U32 u32Focus;			
	ICE_S32 s32Height;			
	ICE_S32 s32HeightAlgo;		
	ICE_S32 s32Distance;		
	ICE_S32 s32DistAlgo;		

	ICE_U32 u32LightMode;		
	ICE_U32 u32ColorMode;		

	ICE_U32 u32AlgoWidth;
	ICE_U32 u32AlgoHeight;

} ICE_ExpAttr_S;

typedef struct T_LprParam
{
	ICE_S32 iNeedPic;			
	ICE_U8 aucReserved[256];    
}T_LprParam;

typedef struct T_TimeInfo{
	ICE_S32 iYear;   
	ICE_S32 iMon;    
	ICE_S32 iDay;    
	ICE_S32 iHour;  
	ICE_S32 iMin;   
	ICE_S32 iSec;   
}T_TimeInfo;

#ifdef __cplusplus
}
#endif


#endif // __ICE_COM_H__


