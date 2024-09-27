Attribute VB_Name = "camara"
'Public Declare Function SetDllDirectory Lib "Kernel32" Alias "SetDllDirectoryA" (ByVal path As String) As LongPrivate
Public Declare Sub ICE_IPCSDK_Init Lib "ice_ipcsdk.dll" ()
Public Declare Sub ICE_IPCSDK_SearchDev Lib "ice_ipcsdk.dll" (ByVal szDevs As String)
Public Declare Function ICE_IPCSDK_OpenDevice Lib "ice_ipcsdk.dll" (ByVal pcIp As String)
Public Declare Function ICE_IPCSDK_StartStream Lib "ice_ipcsdk.dll" (pcIp, dato, wpicture)

'------- Para la camara
'Public Declare Function ICE_IPCSDK_OnPlate Lib "ice_ipcsdk.dll" (ByVal pvParam As Byte, ByVal pcIp As String, ByVal ptLprResult As String, ByVal pFullPicData As Byte, ByVal fullPicLen As Integer, ByVal pPlatePicData As Byte, ByVal platePiclen As Integer, ByVal u32Reserved1 As Integer, ByVal u32Reserved2 As Integer) As Byte
''Public Declare Function ICE_IPCSDK_OpenPreview Lib "ice_ipcsdk.dll" (ByVal IpCam As String, ByVal wByte1 As Byte, ByVal wByte2 As Byte, ByVal wPicture As Integer, ICE_IPCSDK_OnPlate, ByVal IntPtr As Integer) As Integer
Public Declare Function ICE_IPCSDK_OpenPreview Lib "ice_ipcsdk.dll" (ByVal pcIp As String, ByVal u8OverTCP As Byte, ByVal u8MainStream As Byte, ByVal hWnd As Integer, onPlate, ByVal pvPlateParam As Integer) As Integer

'Public Declare Function ICE_IPCSDK_OpenPreview Lib "ice_ipcsdk.dll" (pcIp As String, u8OverTCP As Byte, u8MainStream As Byte, hWnd As Integer, onPlate, pvPlateParam As Byte) As Byte
Public Declare Function ICE_IPCSDK_Open Lib "ice_ipcsdk.dll" (pcIp As String, u8OverTCP As Byte, u16RTSPPort As Integer, u16ICEPort As Integer, u16OnvifPort As Integer, u8MainStream As Byte, pfOnStream As Integer, pvStreamParam As Variant, pfOnFrame As Integer, pvFrameParam As Variant) As Integer
'Public Declare Function ICE_IPCSDK_OpenGate Lib "ice_ipcsdk.dll" (ByVal puerta As Variant) As Integer

'Public Declare Function ICE_IPCSDK_EndTalk Lib "ice_ipcsdk.dll" (ByVal pcIpc As Variant)
Public Declare Function ICE_IPCSDK_StopStream Lib "ice_ipcsdk.dll" (ByVal pcIpc As Variant)
Public Declare Function ICE_IPCSDK_OpenDevice_Passwd Lib "ice_ipcsdk.dll" (ByVal pcIp As String, ByVal pasw As String) As Integer
Public Declare Function ICE_IPCSDK_Open_Passwd Lib "ice_ipcsdk.dll" (pcIp As String, pasw As String, u8OverTCP As Byte, u16RTSPPort As Integer, u16ICEPort As Integer, u16OnvifPort As Integer, u8MainStream As Byte, pfOnStream As Integer, pvStreamParam As Variant, pfOnFrame As Integer, pvFrameParam As Variant) As Integer
'Private Declare Sub ICE_IPCSDK_OpenDevice Lib "ice_ipcsdk.dll" (ByVal pcIp As String)

'Public Declare Function ICE_IPCSDK_Init Lib "ice_ipcsdk.dll" ()

'Public Declare Function ICE_IPCSDK_Open Lib "ice_ipcsdk.dll" ()
'Public Declare Function ICE_IPCSDK_OpenDeviceEx Lib "ice_ipcsdk.dll" (pcIp, cons, pic) As Integer
