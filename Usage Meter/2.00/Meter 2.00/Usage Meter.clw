; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "usage meter.h"
LastPage=0

ClassCount=5
Class1=CAboutDlg
Class2=CMainDlg
Class3=CUsageMeterApp

ResourceCount=4
Resource1=IDD_BEEP_DLG
Resource2=IDD_USAGEMETER_DIALOG
Class4=CDlgBeepSetting
Resource3=IDD_ABOUTBOX
Class5=CDlgPath
Resource4=IDD_DIALOG_PATH

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MainDlg.cpp
ImplementationFile=MainDlg.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:CMainDlg]
Type=0
BaseClass=CDialog
HeaderFile=MainDlg.h
ImplementationFile=MainDlg.cpp
LastObject=CMainDlg
Filter=D
VirtualFilter=dWC

[CLS:CUsageMeterApp]
Type=0
BaseClass=CWinApp
HeaderFile=Usage Meter.h
ImplementationFile=Usage Meter.cpp
LastObject=CUsageMeterApp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDB_ABOUT,static,1342177294
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_USAGEMETER_DIALOG]
Type=1
Class=CMainDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_TAB,SysTabControl32,1342177280
Control3=IDC_WIN_LIST,SysListView32,1350631565
Control4=IDC_INT_LIST,SysListView32,1350631565
Control5=IDC_STATIC,static,1342177287
Control6=IDC_STATUS,static,1342308352
Control7=ID_FILE_VIEWER,button,1342242816
Control8=ID_BEEP_SET,button,1342242816

[CLS:CDlgBeepSetting]
Type=0
HeaderFile=DlgBeepSetting.h
ImplementationFile=DlgBeepSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgBeepSetting
VirtualFilter=dWC

[DLG:IDD_BEEP_DLG]
Type=1
Class=CDlgBeepSetting
ControlCount=19
Control1=EDIT_INT_FREE,edit,1350639617
Control2=EDIT_INT__DUR,edit,1350639617
Control3=EDIT_INT_INTER,edit,1350639617
Control4=CHK_INT_BEEP,button,1342242819
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_TEST_BEEP,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_TAB_BEEP,SysTabControl32,1342177280
Control10=IDC_STATIC_FRAM,static,1342308364
Control11=EDIT_WIN_FREE,edit,1350639617
Control12=EDIT_WIN__DUR,edit,1350639617
Control13=EDIT_WIN_INTER,edit,1350639617
Control14=CHK_WIN_BEEP,button,1342242819
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_PATH]
Type=1
Class=CDlgPath
ControlCount=5
Control1=IDC_EDIT_PATH,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC_MSG,static,1342308352
Control5=IDC_STATIC,static,1342308352

[CLS:CDlgPath]
Type=0
HeaderFile=DlgPath.h
ImplementationFile=DlgPath.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgPath
VirtualFilter=dWC

