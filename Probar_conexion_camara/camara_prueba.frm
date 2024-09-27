VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "mswinsck.ocx"
Object = "{396F7AC0-A0DD-11D3-93EC-00C0DFE7442A}#1.0#0"; "vbalIml6.ocx"
Object = "{6BF52A50-394A-11D3-B153-00C04F79FAA6}#1.0#0"; "wmp.dll"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form camara_prueba 
   Caption         =   "Form2"
   ClientHeight    =   7590
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   13845
   LinkTopic       =   "Form2"
   ScaleHeight     =   7590
   ScaleWidth      =   13845
   StartUpPosition =   2  'CenterScreen
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   5160
      Top             =   1920
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock Winsock1 
      Left            =   840
      Top             =   2400
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin vbalIml6.vbalImageList vbalImageList1 
      Left            =   4440
      Top             =   1080
      _ExtentX        =   953
      _ExtentY        =   953
   End
   Begin VB.TextBox Text4 
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   7.5
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2175
      Left            =   6960
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   10
      Top             =   5040
      Width           =   5775
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Ulink"
      Enabled         =   0   'False
      Height          =   375
      Left            =   3840
      TabIndex        =   9
      Top             =   3360
      Width           =   1200
   End
   Begin VB.TextBox Text3 
      Height          =   270
      Left            =   2640
      TabIndex        =   8
      Text            =   "8000"
      Top             =   600
      Width           =   1575
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Link"
      Height          =   375
      Left            =   2520
      TabIndex        =   7
      Top             =   3360
      Width           =   1200
   End
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   600
      TabIndex        =   6
      Text            =   "123456"
      Top             =   1080
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Abrir puerta1"
      Height          =   375
      Left            =   2040
      TabIndex        =   5
      Top             =   1440
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Conertar Cámara"
      Height          =   375
      Left            =   360
      TabIndex        =   4
      Top             =   1440
      Width           =   1455
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   600
      TabIndex        =   3
      Text            =   "192.168.0.100"
      Top             =   600
      Width           =   1935
   End
   Begin VB.PictureBox Picture1 
      Height          =   4695
      Left            =   6960
      ScaleHeight     =   4635
      ScaleWidth      =   6315
      TabIndex        =   0
      Top             =   240
      Width           =   6375
   End
   Begin WMPLibCtl.WindowsMediaPlayer WindowsMediaPlayer1 
      Height          =   2895
      Left            =   840
      TabIndex        =   11
      Top             =   3960
      Width           =   3615
      URL             =   ""
      rate            =   1
      balance         =   0
      currentPosition =   0
      defaultFrame    =   ""
      playCount       =   1
      autoStart       =   -1  'True
      currentMarker   =   0
      invokeURLs      =   -1  'True
      baseURL         =   ""
      volume          =   50
      mute            =   0   'False
      uiMode          =   "full"
      stretchToFit    =   0   'False
      windowlessVideo =   0   'False
      enabled         =   -1  'True
      enableContextMenu=   -1  'True
      fullScreen      =   0   'False
      SAMIStyle       =   ""
      SAMILang        =   ""
      SAMIFilename    =   ""
      captioningID    =   ""
      enableErrorDialogs=   0   'False
      _cx             =   6376
      _cy             =   5106
   End
   Begin VB.Label Label2 
      BorderStyle     =   1  'Fixed Single
      Caption         =   "192.168.0.100"
      Height          =   390
      Left            =   600
      TabIndex        =   2
      Top             =   120
      Width           =   1935
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Ip"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   390
      Left            =   360
      TabIndex        =   1
      Top             =   120
      Width           =   210
   End
End
Attribute VB_Name = "camara_prueba"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Dim ret As Integer
Dim pUid As Variant
pUid = Array("192.168.0.100", "192.168.0.101", "192.168.0.102", "192.168.0.103")
'MsgBox (pUid(0))
'pUid(0) = ICE_IPCSDK_OpenDevice(Text1.Text)
'ret = ICE_IPCSDK_StartStream(pUid(0), 1, w_pic)
'ret = ICE_IPCSDK_OpenDevice(Text1.Text)
'videoHwnd = Picture1.hWnd
'ret = ICE_IPCSDK_OpenPreview(Text1.Text, 1, 1, videoHwnd, 0, 0)
'ret = ICE_IPCSDK_Open(Text1.Text, 1, 554, 8117, 8080, 1, 0, 0, 0, 0)
'pUid(0) = ICE_IPCSDK_OpenDevice_Passwd(Text1.Text, Text2.Text)
'ret = ICE_IPCSDK_Open_Passwd(Text1.Text, Text2.Text, 1, 554, 8117, 8080, 1, 0, 0, 0, 0)
ret = ICE_IPCSDK_StopStream(pUid(0))
MsgBox (ret)

If ret = 0 Then
   MsgBox ("La camara no conectó...")
   Else
      MsgBox ("La camara conectada...")
End If
End Sub
Private Sub Command2_Click()
Dim wpuerta, wstatus As Variant
wpuerta = Array(0, 1, 2, 3)
wstatus = Array(0, 1)
wpuerta(0) = ICE_IPCSDK_OpenGate(wpuerta(0))
If wpuerta(0) = 0 Then
   MsgBox ("La puerta no se abrió...")
   Else
   MsgBox ("La puerta abierta...")
End If
End Sub
Private Sub Command3_Click()
    Winsock1.Close
    Winsock1.RemoteHost = (Me.Text1.Text)
    Winsock1.RemotePort = CLng(Me.Text3.Text)
   'Winsock1.Listen
    Winsock1.Connect
    Me.Command4.Enabled = False
End Sub
Private Sub Command4_Click()
    Me.Winsock1.Close
    Me.Command3.Enabled = True
End Sub
Private Sub Form_Load()
Dim i As Long
'i = SetDllDirectory("D:\tmp\VB\demo-dll\bin")
'Dim szDevs As String * 256
'ret1 = ICE_IPCSDK_SearchDev(szDevs)
'Text1.Text = szDevs
'videoHwnd = Picture1.Picture
'ICE_IPCSDK_Init
End Sub

Private Sub Winsock1_Close()
    Me.Command4.Enabled = True
End Sub
Private Sub Winsock1_Connect()
     Me.Command4.Enabled = Winsock1.State = sckConnected
     Command3.Enabled = Not Command4.Enabled
End Sub
Private Sub Winsock1_ConnectionRequest(ByVal requestID As Long)
 ' requestID = 1
Winsock1.Close
Winsock1.Accept requestID
End Sub
Private Sub Winsock1_DataArrival(ByVal bytesTotal As Long)
Dim strdata() As Byte
Dim i, j, L As Integer
Dim s1 As String
Dim Command, rstring As String
     
rstring = ""
i = Winsock1.BytesReceived
ReDim strdata(i)
    
Winsock1.GetData strdata, vbByte, i
    
'======================================
If Not CheckReturnCommand(rstring) Then
   Exit Sub
End If
'=======================================
Addlog "Rec:  ", rstring
Text4.Text = Text4.Text + rstring
End Sub
