// eactivityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "eactivityDlg.h"

#define WM_MYICONNOTIFY		WM_USER+2

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BYHOURS 0
#define BYDAYS 1
#define BYMONTHS 2

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEactivityDlg dialog

CEactivityDlg::CEactivityDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEactivityDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEactivityDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	path_actuser="";//** ������� �����
	showAllCaptsForExe="";
	SelectedMon="";
	SelectedDay="";
	forTimeNoActiv=GetTickCount();	
}

void CEactivityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEactivityDlg)
	DDX_Control(pDX, IDC_COMBO2, combo_group);
	DDX_Control(pDX, IDC_SPIN2, spin_edit);
	DDX_Control(pDX, IDC_EDITr17, edit_capts);
	DDX_Control(pDX, IDC_LIST3, table_period);
	DDX_Control(pDX, IDC_COMBO1, combo_sort);
	DDX_Control(pDX, IDC_LIST2, table_exe_capt);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHARTCTRL, chart);
	DDX_Control(pDX, IDC_STATIC_percent_day, stat_day_adv);
	DDX_Control(pDX, IDC_STATIC_percent_hour2, stat_hour_adv);
	DDX_Control(pDX, IDC_STATIC_curday, stat_ExeCapt);
	DDX_Control(pDX, IDC_STATIC_cur_mon, stat_periodTable);
	DDX_Control(pDX, IDC_RADIO1, radioTime);
	DDX_Control(pDX, IDC_RADIO2, radioActs);
	DDX_Control(pDX, IDC_CHECK1, checkAutoUpdate);
}

BEGIN_MESSAGE_MAP(CEactivityDlg, CDialog)
	//{{AFX_MSG_MAP(CEactivityDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo_sort)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkListDays)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeComboDownTable)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK2, OnOk2)
	ON_WM_TIMER()
	ON_WM_COPYDATA()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkListCurDay)
	ON_COMMAND(ID_ACTIVITY_SETKOEF, OnActivitySetKoef)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickTableExeCapt)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, OnRclickPeriodTable)
	ON_COMMAND(ID_ACTIVITY_SETKOEFEXE, OnActivitySetkoefeExe)
	ON_EN_CHANGE(IDC_EDITr17, OnChangeEDITcapts)
	ON_COMMAND(ID_ACTIVITY_EXE, OnActivityShowAllCapts)
	ON_MESSAGE(WM_MYICONNOTIFY,OnIcon)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CEactivityDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEactivityDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CEactivityDlg::OnSave)
	ON_COMMAND(ID_REPORTS_USEFULACTIONSFROMLAST5WORKINGDAYS, &CEactivityDlg::OnReportsUsefulActionsFromLast5WorkingDays)
	ON_BN_CLICKED(IDC_RADIO1, &CEactivityDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CEactivityDlg::OnBnClickedRadio1)
	ON_COMMAND(ID_REPORTS_USEFULPARAMETERFROMSELECTEDPERIOD, &CEactivityDlg::OnReportsUsefulParameterFromSelectedPeriod)
	ON_COMMAND(ID_Compare2Periods, &CEactivityDlg::OnCompare2periods)
	ON_COMMAND(ID_IDR_32783, &CEactivityDlg::OnCompareWithBest5Days)
	ON_COMMAND(ID_REPORTS_32784, &CEactivityDlg::OnReportOnePeriod)
	ON_COMMAND(ID_REPORTS_32785, &CEactivityDlg::OnReportTwoPeriods)
END_MESSAGE_MAP()

//�������� �� ������ � ����
LRESULT CEactivityDlg::OnIcon(WPARAM wp, LPARAM lp)
{
	if (lp==515 || lp==514) //�������� ���
	{
		BOOL IsVisible=IsWindowVisible();
		if(IsVisible)
		{
			ShowWindow(SW_HIDE);
		} else {
			SetForegroundWindow();
			ShowWindow(SW_RESTORE);
			ShowWindow(SW_SHOW);
		}
	}
	return 1;
}

BOOL CEactivityDlg::OnInitDialog()
{
	WriteJournal("OnInitDialog 0\n");
	CDialog::OnInitDialog();
	RR=GG=0;
	SetToTray(IDR_MAINFRAME);
	if (trif.GetNumLan()==1)
		MainMenu.LoadMenu(IDR_MAIN_MENU_RU);
	else
		MainMenu.LoadMenu(IDR_MAIN_MENU);
	SetMenu(&MainMenu);
	SetHook=0;
	SYSTEMTIME st;
	GetLocalTime(&st);
	curHour=st.wHour;

	chart.CreateStandardAxis(CChartCtrl::BottomAxis);
	chart.CreateStandardAxis(CChartCtrl::LeftAxis);
	chart.GetLeftAxis()->SetAutomatic(true);
	chart.GetBottomAxis()->SetAutomatic(true);

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if (trif.GetNumLan()==1)
	{
		menuExeCapt.LoadMenu(IDR_CONTEXT_EXECAPT_RU);
		menuTablePeriod.LoadMenu(IDR_CONTEXT_TABLEPERIOD_RU);
	} else {
		menuExeCapt.LoadMenu(IDR_CONTEXT_EXECAPT_RU);
		menuTablePeriod.LoadMenu(IDR_CONTEXT_TABLEPERIOD_RU);
	}
	if (AfxGetApp()->GetProfileInt("App", "AccentParameter", 1))
		radioTime.SetCheck(1);
	else radioActs.SetCheck(1);
	char ch[300];
//	tool_tip.Create(this, TTS_ALWAYSTIP);
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1583));
//	tool_tip.AddTool(GetDlgItem(IDC_EDITr17), str);
//	tool_tip.AddTool(GetDlgItem(IDC_SPIN2), str);
	spin_edit.SetBuddy(&edit_capts);
	spin_edit.SetRange(0,9999);

	//list_activ.SetStile(LVS_REPORT | LVS_OWNERDRAWFIXED /*|LVS_EDITLABELS*/);
	table_exe_capt.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | table_exe_capt.GetExtendedStyle());
	table_exe_capt.InsertColumn(0, "exe");
	table_exe_capt.InsertColumn(1, "Caption");
	table_exe_capt.InsertColumn(2, "useful time");
	table_exe_capt.InsertColumn(3, "total time");
	table_exe_capt.InsertColumn(4, "useful acts");
	table_exe_capt.InsertColumn(5, "total acts");
	table_exe_capt.InsertColumn(6, "full exe");
	table_exe_capt.SetColumnWidth(0,80);
	table_exe_capt.SetColumnWidth(1,200);
	table_exe_capt.SetColumnWidth(2,80);
	table_exe_capt.SetColumnWidth(3,80);
	table_exe_capt.SetColumnWidth(4,60);
	table_exe_capt.SetColumnWidth(5,60);
	table_exe_capt.SetColumnWidth(6,0);
	table_exe_capt.exeCapt=true;
	table_exe_capt.EnableToolTips(FALSE);

	combo_sort.ResetContent();
	str.LoadString(trif.GetIds(IDS_STRING1599));
	combo_sort.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1601));
	combo_sort.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1603));
	combo_sort.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1605));
	combo_sort.AddString(str);
	combo_sort.SetCurSel(AfxGetApp()->GetProfileInt("App", "type_sort_activ", 0));

	combo_group.ResetContent();
	str.LoadString(trif.GetIds(IDS_STRING1635));
	combo_group.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1607));
	combo_group.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1609));
	combo_group.AddString(str);
	//�� ��������� ������ �� ������� ��������, ����� ����� ��������� ������� ����������
	combo_group.SetCurSel(0);//AfxGetApp()->GetProfileInt("App", "type_group_activ", 0)

	str.LoadString(trif.GetIds(IDS_STRING1613));
	GetDlgItem(IDC_BUTTON1)->SetWindowText(str);

	table_period.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | table_period.GetExtendedStyle());
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		str.LoadString(trif.GetIds(IDS_STRING1639));
		break;
	case BYDAYS:
		str.LoadString(trif.GetIds(IDS_STRING1641));
		break;
	case BYMONTHS:
		str.LoadString(trif.GetIds(IDS_STRING1643));
		break;
	}
	table_period.InsertColumn(0, str);
	table_period.InsertColumn(1, "useful time");
	table_period.InsertColumn(2, "total time");
	table_period.InsertColumn(3, "useful acts");
	table_period.InsertColumn(4, "total acts");
	table_period.InsertColumn(5, "comment");
	table_period.SetColumnWidth(0,80);
	table_period.SetColumnWidth(1,80);
	table_period.SetColumnWidth(2,80);
	table_period.SetColumnWidth(3,80);
	table_period.SetColumnWidth(4,100);
	table_period.SetColumnWidth(5,80);
	table_period.EnableToolTips(FALSE);

	path_exe=cpu.GetAppNameFromHandle2(GetSafeHwnd()).c_str();
	path_exe=path_exe.Left(path_exe.ReverseFind('\\'));
	path_actuser = path_exe+"\\activity\\";
	if (!trif.IsDirExist(path_actuser.c_str()))
	{
		CreateDirectory(path_actuser.c_str(), NULL);
	}
	statsF.path_actuser=path_actuser;

	LoadRules();
	WriteJournal("On Init Dialog 1");
	LoadCurDay();
	SelectedDay="";
	activ_hours activHours;
	UpdateExeCapt(activHours);

	LoadCurMonth();
	statsF.LoadYear(aCurYear);
	sprintf_s(ch, "%d", AfxGetApp()->GetProfileInt("App", "CounShowCapt", 4));
	edit_capts.SetWindowText(ch);
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		UpdatePeriodTableViewByHours(activHours);
		break;
	case BYDAYS:
		UpdatePeriodTable(aCurMon);
		break;
	case BYMONTHS:
		UpdatePeriodTable(aCurYear);
		break;
	}

	SetTimer(1500, 500, 0);
	SetTimer(2500, 5000, 0);
	SetTimer(3564, 5*60*1000, 0); //�������������� ������ 5 �����
	checkAutoUpdate.SetCheck(true);
	CalculateAverageUsefulParameter(5);//����� ������ ������ ������� ����������� �� ���
#ifndef _DEBUG
#endif
	hMyDll=NULL;
	__SetHook__(TRUE);
	WriteJournal("dialog initialization success");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

SetHookFromDll mySetHookFromDll=NULL; 
MyFreeLib myFreeLib=NULL; 
BOOL CEactivityDlg::__SetHook__(BOOL fSet)
{
#ifdef _DEBUG
	if (fSet)
	{
		return 1;
	} else {
		fSet=fSet;
	}
#endif

	HWND hw_dll64=0;
	static int counloadlib=0;
#ifdef LOG 
	char ch[1024]; sprintf_s(ch, "SetHook =%d At=%d", fSet, At); trif.RecordLog(ch);  
#endif
	::ClipCursor(0);
	if (fSet)
	{
		if (!hMyDll)
		{
			counloadlib++;
			if (counloadlib>1)
			{
				AfxMessageBox("counloadlib>1!");
			}

			if (trif.Is64BitOS())
			{
				char ch_capt_start64[512];
				sprintf_s(ch_capt_start64, "start_dll64_for_eactivity (%p)", GetSafeHwnd());
				if (!hw_dll64)
					hw_dll64=::FindWindow("#32770", ch_capt_start64);
				if (!hw_dll64 || !IsWindow(hw_dll64))
				{
					CString sShelEx=path_exe+"\\start_dll64.exe";
					SetCurrentDirectory(sShelEx.Left(sShelEx.ReverseFind('\\')));
					char ch_cmd[2048];
					sprintf_s(ch_cmd, "path_exe=\""+path_exe+"\\\" hwnd=%p", GetSafeHwnd());
					ShellExecute(0, NULL, sShelEx, ch_cmd, NULL, SW_HIDE);
					Sleep(1000);
					hw_dll64=::FindWindow("#32770", ch_capt_start64);
					while (!hw_dll64 && GetTickCount()<600000) //���� 10 ����� �� ������ �������
					{
						hw_dll64=::FindWindow("#32770", ch_capt_start64);
						if (hw_dll64 && ::IsWindow(hw_dll64))
							break;
						Sleep(1000);
					}
					if (!hw_dll64 || !::IsWindow(hw_dll64))
					{
						AfxMessageBox("start_dll error (FindWindow)");
					}
				}
			}
			hMyDll = ::LoadLibrary(path_exe+"\\auxiliar.dll");
			if (!hMyDll)
			{
				AfxMessageBox("Error of library loading \n" + path_exe + "\\auxiliar.dll" );
				return FALSE;
			} else {
				mySetHookFromDll=(SetHookFromDll)::GetProcAddress(hMyDll,"SetHookFromDll");
				myFreeLib=(MyFreeLib)::GetProcAddress(hMyDll,"MyFreeLib");
				if (!SetHook)
				{
					if (trif.Is64BitOS())
					{
						if (hw_dll64) 
						{
							char ch_own[100];
							sprintf_s(ch_own, "hwnd=%p", GetSafeHwnd());
							SetHook=(HHOOK)::SendMessageTimeout(hw_dll64, WM_USER30, 1, 
								(LPARAM)GetSafeHwnd(), 0, 2000, NULL);
						} else {
							//CurRec.LoSR.SendError("", "start_dll error (AutoText)", 4, "Lounch_dll error (AutoText). Send this message at admin@autoclickextreme.com");
						}
					}
					SetHook=(HHOOK) mySetHookFromDll(true, hMyDll, 5, GetSafeHwnd());
				}
				if (!SetHook)
				{
					WriteJournal("!!! SetHook is false !!!");
				}
#ifdef LOG 
				char debc[1024]; sprintf_s(debc, "mySetHookFromDll=%x", mySetHookFromDll); trif.RecordLog(debc);  
#endif
			}
		}
	} else {
		int glstErr=0;
		if (hMyDll)
		{
			glstErr = mySetHookFromDll(false, hMyDll, 0, 0);
			if (trif.Is64BitOS())
			{
				if (glstErr)
				{
					LPVOID lpMsgBuf;
					FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
						FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL, glstErr,  MAKELANGID(LANG_NEUTRAL,
						SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL
						);
				}
				char ch_capt_start64[512];
				sprintf_s(ch_capt_start64, "start_dll64_for_eactivity (%p)", GetSafeHwnd());
				if (!hw_dll64)
					hw_dll64=::FindWindow("#32770", ch_capt_start64);
				if (hw_dll64) 
				{
					glstErr=((int)::SendMessageTimeout(hw_dll64, WM_USER30, 0, 0, 0, 2000, NULL));
				} else {
					AfxMessageBox("start_dll error (sethook). start_dll error (sethook). Send this message at admin@autoclickextreme.com");
				}
			}
			if (glstErr)
			{
				LPVOID lpMsgBuf;
				FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
					FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL, glstErr,  MAKELANGID(LANG_NEUTRAL,
					SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL
					);
			}
			SetHookRec = NULL;
		}

		if (hMyDll)
		{
#ifdef LOG 
			trif.RecordLog("SetHook FreeLibrary");  
#endif
			counloadlib--;
			if (!FreeLibrary(hMyDll))
			{
				AfxMessageBox("lib not free (#2)!!!");
			}
			// ��������������� ��������� start_dll64 �������������� ����������� � 
				//������� 5 ��� ����� �������� eactivity
// 			if (trif.Is64BitOS())
// 			{
// 				char ch_capt_start64[512];
// 				sprintf_s(ch_capt_start64, "start_dll64_for_eactivity (%p)", GetSafeHwnd());
// 				if (!hw_dll64)
// 					hw_dll64=::FindWindow("#32770", ch_capt_start64);
// 				if (!hw_dll64)
// 				{
// 					CString sShelEx=path_exe+"\\start_dll64.exe";
// 					SetCurrentDirectory(sShelEx.Left(sShelEx.ReverseFind('\\')));
// 					ShellExecute(0, NULL, sShelEx, "Close", NULL, SW_HIDE);
// 				}
// 			}
			hMyDll=0;
		}
	}

#ifdef LOG 
	trif.RecordLog("SetHook return TRUE");  
#endif
	return TRUE;
}

DWORD oldtime=0;
SendStruct* curAct;//=new SendStruct();
BOOL CEactivityDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCD) 
{
#ifdef LOG 
	char deb[1024];
	sprintf_s(deb, "OnCopyData ������ size=%d", sizeof(pCD));
	trif.RecordLog(deb);
#endif
	curAct=(SendStruct*)pCD->lpData;
#ifdef LOG 
	if (curAct->baTypeAct<6 || curAct->baTypeAct>9) 
	{
		int debi1=curAct->message;
		int debi2=curAct->baTypeAct;
		//		sprintf_s(deb, "OnCopyData TypeAct=%d", debi2);
		//		else 
		sprintf_s(deb, "OnCopyData TypeAct=%d message=%d", debi2, debi1);
		trif.RecordLog(deb);
	}
#endif
	TRACE("OnCopyData curAct->baTypeAct=%d \n", curAct->baTypeAct);
	if (curAct->baTypeAct>=6 && curAct->baTypeAct<=9)
		AnalActivUser(curAct);
	if (curAct->message==222222)
	{	//��������� ��������� ������ 
		CString str=AfxGetApp()->GetProfileString("App", "ComLine");// curAct->csMainWindowCapt;
#ifdef LOG 
		trif.RecordLog("OnCopyData ��������� ��������� ������ ="+str);
#endif
		str.Remove('\"');
		str.TrimRight('\"');
		str.MakeLower();
		bool razr_foreg=true;
		if (!str.IsEmpty())
		{
			bool complayaip=false, complayPL=false;
			str.TrimRight(" ");
			str.TrimLeft(" ");
			if (str.Left(5)=="-save")
			{
			} else {
			}

		}
		return CDialog::OnCopyData(pWnd, pCD);
	}
#ifdef LOG 
	sprintf_s(deb, "OnCopyData switch (baTypeAct=%d)", (curAct->baTypeAct));
	trif.RecordLog(deb);
#endif

#ifdef LOG 
	if (curAct->baTypeAct<6 || curAct->baTypeAct>8) 
		trif.RecordLog("OnCopyData ��������� �����");
#endif
	return CDialog::OnCopyData(pWnd, pCD);
}

void CEactivityDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CEactivityDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEactivityDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEactivityDlg::OnOk2() 
{
	activ_hours activHours;
	UpdateExeCapt(activHours);
	//���������� ����
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		UpdatePeriodTableViewByHours(activHours);
		break;
	case BYDAYS:
		UpdatePeriodTable(SelectedMon == "" ? aCurMon : aSelMon);
		break;
	case BYMONTHS:
		UpdatePeriodTable(aCurYear);
		break;
	}
}

bool CompareActs(Activity Activity_1, Activity Activity_2)
{
	return Activity_1.sumActs>Activity_2.sumActs;
}
bool CompareTimes(Activity Activity_1, Activity Activity_2)
{
	return Activity_1.sumTime>Activity_2.sumTime;
}
bool CompareUsefulActs(Activity Activity_1, Activity Activity_2)
{
	return Activity_1.usefulActs>Activity_2.usefulActs;
}

bool CompareActs2(ActivityExe Activity_1, ActivityExe Activity_2)
{
	return Activity_1.sumActs>Activity_2.sumActs;
}
bool CompareTimes2(ActivityExe Activity_1, ActivityExe Activity_2)
{
	return Activity_1.sumTime>Activity_2.sumTime;
}
bool CompareUsefulActs2(ActivityExe Activity_1, ActivityExe Activity_2)
{
	return Activity_1.usefulActs>Activity_2.usefulActs;
}

// UpdateTopTable - ���������� ������� �����������
// 	int &sumTime //��������� ����� ��� ����� ���/�����������
//		��� ����������� https://docs.google.com/document/d/1zG2kZiDdtXNvLGwjBw66F6RK8lBxK4HoGTgBFA48PGg/edit
//	int onlyOneHour - �� ��������� -1, ���� ������� ������ �����, �� ��������� 
//		���������� ������ ��� ���������� ����, ����� ��� ����� ��������� �����
//	activ_hours activHours; //����� ���������� � ���������� �� �����
void CEactivityDlg::UpdateTableExeCapt(activ &allActiv, activ_hours &activHours, 
					float &sumTime, float &sumUsefulTime, int &sumAct, 
					int &sumUsefulActs, int onlyOneHour) 
{
	//������� ���������� � ������ ��� ��������� �� �����
	activ activSumHours;
	if (onlyOneHour!=-1)
		onlyOneHour=onlyOneHour;
	for (activ::iterator ia=allActiv.begin(); ia!=allActiv.end(); ia++)
	{
		string exeCapt = ia->first;
		if (onlyOneHour>-1 && atoi(exeCapt.c_str())!=onlyOneHour)
			continue; //����������� ���������� ������ ��� ���������� ����, ������ ���� ���������
		exeCapt.erase(0, exeCapt.find('\t')+1); //������� ���
		activ::iterator iter=activSumHours.find(exeCapt);
		if (iter==activSumHours.end())
		{
			activSumHours[exeCapt]=ia->second;
		} else {
			(*iter).second.usefulActs +=ia->second.usefulActs;
			(*iter).second.sumActs    +=ia->second.sumActs;
			(*iter).second.sumTime    +=ia->second.sumTime;
			(*iter).second.usefulTime +=ia->second.usefulTime;
		}
	}
	// ����������� ������� ����������� ����� �������, ������������ ������� ����������� ����������
	activ_exe activExe; 
	CalculateUsefulTimeAndActs(onlyOneHour == -1 ? allActiv : activSumHours, activExe, activHours);

	//������������ ������� �������� - ����� (��� ���������)
	vector <ActivityExe> vect_for_sort;
	for (activ_exe::iterator ia=activExe.begin(); ia!=activExe.end(); ia++)
	{
		if (showAllCaptsForExe.length() && showAllCaptsForExe!=(*ia).second.exe)
			continue;
//		(*ia).second.usefulActs     = GetUsefulActsFromExe((*ia).second.exe, activSumHours);
//		(*ia).second.usefulTime = GetTimeFromExe ((*ia).second.exe, activSumHours);
		sumUsefulTime += (*ia).second.usefulTime;
		sumUsefulActs += (*ia).second.usefulActs;
		vect_for_sort.push_back((*ia).second);
	}
	switch(combo_sort.GetCurSel())
	{
	case 0:
		break;
	case 1:
		sort(vect_for_sort.begin(), vect_for_sort.end(), CompareUsefulActs2);
		break;
	case 2:
		sort(vect_for_sort.begin(), vect_for_sort.end(), CompareTimes2);
		break;
	case 3:
		sort(vect_for_sort.begin(), vect_for_sort.end(), CompareActs2);
		break;
	}

	table_exe_capt.DeleteAllItems();
	for (vector<ActivityExe>::iterator iv=vect_for_sort.begin(); iv!=vect_for_sort.end(); ++iv)
	{
		string shortExe;
		forExe::iterator iter=exes.find((*iv).exe);
		if (iter==exes.end())
		{
			int fi=(*iv).exe.rfind('\\')+1;
			shortExe=(*iv).exe.substr(fi, (*iv).exe.length()-fi);
			exes[(*iv).exe]=shortExe;
		} else {
			shortExe=(*iter).second;
		}
		int ii=table_exe_capt.InsertItem(table_exe_capt.GetItemCount(), shortExe.c_str());
	
//		����������� ������ ���������������� �������
		char ch[100];
		float sec=(*iv).sumTime/1000;
		FormatSeconds(ch, sec);
		table_exe_capt.SetItemText(ii, 3, ch);
		sumTime+=(*iv).sumTime;

		//����������� ��������� �������
		sec=(*iv).usefulTime/1000;
		FormatSeconds(ch, sec);
		//sprintf_s(ch, "%d", (int)((*iv).sumTime/1000));
		table_exe_capt.SetItemText(ii, 2, ch);
		//sumTime+=(*iv).sumTime;

		sprintf_s(ch, "%d", (*iv).sumActs);
		table_exe_capt.SetItemText(ii, 5, ch);
		sumAct+=(*iv).sumActs;

		sprintf_s(ch, "%d", (*iv).usefulActs);
		table_exe_capt.SetItemText(ii, 4, (*iv).usefulActs ? ch : "-");
		table_exe_capt.SetItemText(ii, 6, (*iv).exe.c_str());

		//����� �� ��������� ������� �������� ���� ������ ������� ����������� � ������� ���������
		int sumCapts=0;
		AddExeCaptToTable((*iv).exe, activSumHours, sumCapts);
		CString str;
		str.LoadString(trif.GetIds(IDS_STRING1589));
		if (trif.GetNumLan()==1)
			 sprintf_s(ch, str, sumCapts, trif.getEnd(sumCapts).c_str());
		else sprintf_s(ch, str, sumCapts);
		table_exe_capt.SetItemText(ii, 1, ch);
	}
}

rulSpis::iterator CEactivityDlg::ownFind(string capt) 
{
	for (rulSpis::iterator iter=RULES.begin(); iter!=RULES.end(); iter++)
	{
		if ((*iter).second.typeRule!=2)
			continue;
		int ideb=capt.find((*iter).second.capt);
		if (ideb>-1)
			return iter;
	}
	return RULES.end();
}

float CEactivityDlg::GetTimeFromExe(string exe, activ &forLoad1) 
{
	float useful_time=0;
	for (activ::iterator ia=forLoad1.begin(); ia!=forLoad1.end(); ia++)
	{
		if ((*ia).second.exe==exe)
		{
			string ExeCapt=exe+'\t'+(*ia).second.capt;
			rulSpis::iterator iter=RULES.find(ExeCapt);
			if (iter==RULES.end())
				iter=ownFind((*ia).second.capt);
			if (iter==RULES.end())
				iter=RULES.find(exe);
			if (iter!=RULES.end())
			{
				(*ia).second.usefulTime = (*iter).second.koef * (*ia).second.sumTime;
				useful_time += ((*iter).second.koef * (*ia).second.sumTime);
			}
		}
	}
	return useful_time;
}

int CEactivityDlg::GetUsefulActsFromExe(string exe, activ &forLoad1) 
{
	int sumUsefulActs=0;
	for (activ::iterator ia=forLoad1.begin(); ia!=forLoad1.end(); ia++)
	{
		if ((*ia).second.exe==exe)
		{
			string ExeCapt=exe+'\t'+(*ia).second.capt;
			rulSpis::iterator iter=RULES.find(ExeCapt);
			if (iter==RULES.end())
				iter=ownFind((*ia).second.capt);
			if (iter==RULES.end())
				iter=RULES.find(exe);
			if (iter!=RULES.end())
			{
				(*ia).second.usefulActs=(int)((*iter).second.koef * (*ia).second.sumActs);
				sumUsefulActs+=(*ia).second.usefulActs;
			}
		}
	}
	return sumUsefulActs;
}

//CalculateUsefulTimeAndActs - �������� ��� ����� ������� �������� �������� � ��������� �������
//		&exeActiv - ������ �� ������ ����������, ���������� ��� � ������������ ������
//		&activHours - ������ ���������� ��� ���������� ����������� � ���������� �� �����
//			� 25�� ��� ����� ����������� ������������ ��������� ����������
//	������������ �������� - ����� ���������� ��������� �������
void CEactivityDlg::CalculateUsefulTimeAndActs(activ &allActiv, activ_exe &exeActiv, 
											   activ_hours &activHours) 
{
	// ��� ������ ������ ����������� �� ������������������ ���������� ���������������� ������������,
	//		��������� �������� ����� � �������� � ���������� ������� � ���������� �� ����������
	ActivityExe hour25;
	hour25.sumActs=0; hour25.sumTime=0; hour25.usefulActs=0; hour25.usefulTime=0;
	for (activ::iterator ia=allActiv.begin(); ia!=allActiv.end(); ia++)
	{
		string ExeCapt=(*ia).second.exe+'\t'+(*ia).second.capt;
		rulSpis::iterator iter=RULES.find(ExeCapt);
		if (iter==RULES.end())
			iter=ownFind((*ia).second.capt);
		if (iter==RULES.end())
			iter=RULES.find((*ia).second.exe);
		int   usefulActs = 0;
		float usefulTime = 0.0;

		if (iter!=RULES.end())
		{ //������� �������, ��������� �������� ����� � ��������
			usefulActs =  (int)((*iter).second.koef * (*ia).second.sumActs);
			usefulTime =       ((*iter).second.koef * (*ia).second.sumTime);

		}
		(*ia).second.usefulActs = usefulActs;
		(*ia).second.usefulTime = usefulTime;

		// ���������� ����� ������� ��� ��������� ������������ � ����������� ����������� ����������
		activ_exe::iterator iterExe = exeActiv.find((*ia).second.exe);
		if (iterExe == exeActiv.end())
		{
			ActivityExe exeElement;
			exeElement.exe = (*ia).second.exe;
			exeElement.usefulActs = usefulActs;
			exeElement.usefulTime = usefulTime;
			exeElement.sumActs    = (*ia).second.sumActs;
			exeElement.sumTime    = (*ia).second.sumTime;
			exeActiv[(*ia).second.exe] = exeElement;
		} else {
			(*iterExe).second.usefulActs += usefulActs;
			(*iterExe).second.usefulTime += usefulTime;
			(*iterExe).second.sumActs    += (*ia).second.sumActs;
			(*iterExe).second.sumTime    += (*ia).second.sumTime;
		}

		//��������� ���������� ���������� � ��������� ���������
		activ_hours::iterator iterHour = activHours.find((*ia).second.hour);
		if (iterHour == activHours.end())
		{
			ActivityExe hourElement;
			hourElement.usefulActs = usefulActs;
			hourElement.usefulTime = usefulTime;
			hourElement.sumActs    = (*ia).second.sumActs;
			hourElement.sumTime    = (*ia).second.sumTime;
			activHours[(*ia).second.hour] = hourElement;
		} else {
			(*iterHour).second.usefulActs += usefulActs;
			(*iterHour).second.usefulTime += usefulTime;
			(*iterHour).second.sumActs    += (*ia).second.sumActs;
			(*iterHour).second.sumTime    += (*ia).second.sumTime;
		}
		hour25.usefulTime+=usefulTime;
		hour25.usefulActs+=usefulActs;
		hour25.sumTime+=(*ia).second.sumTime;
		hour25.sumActs+=(*ia).second.sumActs;
	}
	activHours[25]=hour25;//��������� ���������� �� ����������� �����������
}

// AddExeCaptToTable	������������ ������� ����� ��������� ������� �� ���������
void CEactivityDlg::AddExeCaptToTable(string exe, activ &forLoad1, int &sumCapt) 
{
	vector <Activity> vect_for_sort;
	for (activ::iterator ia=forLoad1.begin(); ia!=forLoad1.end(); ia++)
	{
		if ((*ia).second.exe==exe)
		{
			sumCapt++;
			vect_for_sort.push_back((*ia).second);
		}
	}
	switch(combo_sort.GetCurSel())
	{
	case 0:
		break;
	case 1:
		sort(vect_for_sort.begin(), vect_for_sort.end(), CompareUsefulActs);
		break;
	case 2:
		sort(vect_for_sort.begin(), vect_for_sort.end(), CompareTimes);
		break;
	case 3:
		sort(vect_for_sort.begin(), vect_for_sort.end(), CompareActs);
		break;
	}

	int coun=0; 
	CString str;
	edit_capts.GetWindowText(str);
	int MaxCoun=atoi(str);
	for (vector<Activity>::iterator iv=vect_for_sort.begin(); iv!=vect_for_sort.end(); ++iv)
	{
		if (!showAllCaptsForExe.length() && coun==MaxCoun)
			break;
		int ii=table_exe_capt.InsertItem(table_exe_capt.GetItemCount(), "");
		
		table_exe_capt.SetItemText(ii, 1, (*iv).capt.c_str());

		char ch[100];
		float sec=(*iv).sumTime/1000;
		FormatSeconds(ch, sec);
		table_exe_capt.SetItemText(ii, 3, ch);
		sec=(*iv).usefulTime/1000;
		FormatSeconds(ch, sec);
		table_exe_capt.SetItemText(ii, 2, sec ? ch : "-");

		sprintf_s(ch, "%d", (*iv).sumActs);
		table_exe_capt.SetItemText(ii, 5, ch);
		sprintf_s(ch, "%d", (*iv).usefulActs);
		table_exe_capt.SetItemText(ii, 4, (*iv).usefulActs ? ch : "-" );
		coun++;
	}
}

__int64 oldtimeAnAct=0; CPoint oldPoint;
void CEactivityDlg::AnalActivUser(SendStruct* curAct) 
{
	if (curAct->baTypeAct==8)
	{
		TRACE("AnalActivUser ������� �� �������\n");
		return; //������� �� �������
	}
	if (curAct->dw_time==oldtimeAnAct)
	{
		TRACE("AnalActivUser ����������� ������ �������� �� �������\n");
		return;	//����������� ������ ��������
	}
	oldtimeAnAct=curAct->dw_time;
	if (curAct->baTypeAct==9)
	{
		CPoint po;	
		GetCursorPos(&po);
		if (po==oldPoint)
		{
			oldPoint=po;	
			TRACE("AnalActivUser ��������� ���� � ����������� ������������ �� ��������� � �����������\n");
			return;	
		}
		oldPoint=po;	
	}
	if (!IsWindow((HWND)curAct->HChil))
	{
		TRACE("AnalActivUser ��������� �������� � ����������� �������� �����\n");
		return;
	}
	forTimeNoActiv=GetTickCount();//����� ������� ������������

	HWND hwMain;//����� �������� ����� �� ������ "����-��������"
	GetParSpis::iterator it_parHwnd=getParSpis.find((HWND)curAct->HChil);
	if (it_parHwnd==getParSpis.end())
	{
		hwMain=wwork.GetPar((HWND)curAct->HChil);
		getParSpis[(HWND)curAct->HChil]=hwMain;
	} else {
		hwMain=(*it_parHwnd).second;
	}

	string exe;
	exeSpis::iterator it_exe=exe_sprav.find(hwMain);
	if (it_exe==exe_sprav.end())
	{
		exe=cpu.GetAppNameFromHandle2(hwMain);
		if (trif.Is64BitOS() && exe=="INVALID_HANDLE_VALUE")
		{
			//AfxGetMainWnd()->SendMessage(WM_USER31, 1);
			char ch_capt_start64[512];
			sprintf_s(ch_capt_start64, "start_dll64_for_eactivity (%p)", GetSafeHwnd());
			HWND hwDll64=::FindWindow("#32770", ch_capt_start64);
			::SendMessageTimeout(hwDll64, WM_USER+35, (UINT)hwMain, 0, 0, 3000, NULL);
			HKEY hkey;
			LONG retval = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\TwoTeaPots\\start_dll64\\App"), 
				0, KEY_QUERY_VALUE, &hkey);
			if (retval == ERROR_SUCCESS) 
			{
				DWORD dwSize3;
				RegQueryValueEx(hkey, "GetExe", NULL, NULL, NULL, &dwSize3);
				if (dwSize3)
				{
					char* ESSTyp = new char[dwSize3];
					RegQueryValueEx(hkey, "GetExe", NULL, NULL, (LPBYTE) ESSTyp, &dwSize3);
					exe=ESSTyp;
					delete[] ESSTyp;
				}
				RegCloseKey(hkey);
			}
		}
		exe_sprav[hwMain]=exe;
	} else {
		exe=(*it_exe).second;
	}
	char capt[100];
	::GetWindowText(hwMain, capt, 100);
	AddToExeCapt(capt, exe, (HWND)curAct->HChil, hwMain, 1, 0);
}

void CEactivityDlg::AddToExeCapt(char *capt, string &exe, HWND HChil, HWND hwMain, 
								 int sumActs, float sumTime) 
{
	char chi[512];
	sprintf_s(chi, "%d\t", curHour);
	string exeCapt = chi + exe + '\t' + capt;
	activ::iterator it_activ = ActivToday.find(exeCapt);
	if (it_activ==ActivToday.end())
	{
		Activity new_zap;
		new_zap.sumActs=sumActs;
		new_zap.usefulActs=0;
		new_zap.sumTime=sumTime;
		new_zap.usefulTime=0;
		new_zap.hour=curHour;
		new_zap.capt=capt;
		new_zap.exe=exe;
		new_zap.hwChil=HChil;
		new_zap.hwMain=hwMain;
		ActivToday[exeCapt]=new_zap;
//		TRACE("AddToExeCapt �������� ����� ������ sumTime=%.2f ��� %s\n", sumTime, exeCapt.c_str());
	} else {
		(*it_activ).second.sumActs += sumActs;
		(*it_activ).second.sumTime  += sumTime;
//		TRACE("AddToExeCapt �������� ������������ ������ sumTime=%.2f ��� %s\n", (*it_activ).second.sumTime, exeCapt.c_str());
	}
}

string CEactivityDlg::GetExeFromHwnd(HWND hw) 
{
	string res;
	exeSpis::iterator it_exe=exe_sprav.find(hw);
	if (it_exe==exe_sprav.end())
	{
		res=cpu.GetAppNameFromHandle2(hw);
		if (trif.Is64BitOS() && res=="INVALID_HANDLE_VALUE")
		{
			char ch_capt_start64[512];
			sprintf_s(ch_capt_start64, "start_dll64_for_eactivity (%p)", GetSafeHwnd());
			HWND hwDll64=::FindWindow("#32770", ch_capt_start64);
			::SendMessageTimeout(hwDll64, WM_USER+35, (UINT)hw, 0, 0, 3000, NULL);
			HKEY hkey;
			LONG retval = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\TwoTeaPots\\start_dll64\\App"), 
				0, KEY_QUERY_VALUE, &hkey);
			if (retval == ERROR_SUCCESS) 
			{
				DWORD dwSize3;
				RegQueryValueEx(hkey, "GetExe", NULL, NULL, NULL, &dwSize3);
				if (dwSize3)
				{
					char* ESSTyp = new char[dwSize3];
					RegQueryValueEx(hkey, "GetExe", NULL, NULL, (LPBYTE) ESSTyp, &dwSize3);
					res=ESSTyp;
					delete[] ESSTyp;
				}
				RegCloseKey(hkey);
			}
		}
		exe_sprav[hw]=res;
	} else
		return (*it_exe).second;
	return res;
}

void CEactivityDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1500:
		{	//������������ ������� ���������� ���� � ������
			HWND hw=::GetForegroundWindow();
			if (!IsWindow(hw))
				return;
			static UINT curTime=GetTickCount();	

			HWND hwMain;//����� �������� ����� �� ������ "����-��������"
			GetParSpis::iterator it_parHwnd=getParSpis.find(hw);
			if (it_parHwnd==getParSpis.end())
			{
				hwMain=wwork.GetPar(hw);
				getParSpis[hw]=hwMain;
			} else {
				hwMain=(*it_parHwnd).second;
			}
			

			//���� ��������� � ������ ��� ���������� ������������, �� �������� ������������
			CPoint cpCursor;
			GetCursorPos(&cpCursor);
			if (cpCursor!=cpNoActiv)
			{
				forTimeNoActiv=GetTickCount();
				cpNoActiv=cpCursor;
			} else
			if (GetTickCount()-forTimeNoActiv>30000)
			{
				curTime=GetTickCount();
				break;
			}

			string str_exe=GetExeFromHwnd(hwMain);

			char capt[100];
			::GetWindowText(hwMain, capt, 100);
			AddToExeCapt(capt, str_exe, hw, hwMain, 0, (float)(GetTickCount()-curTime));
			curTime=GetTickCount();
			static bool perekl=1;//������������� � eactivity - ��������� ����������, ����� ���
			if (hwMain == AfxGetMainWnd()->m_hWnd || 
				::GetWindow(hwMain, GW_OWNER) == AfxGetMainWnd()->m_hWnd)
			{
				if (perekl)
				{
					perekl=false;
					if (checkAutoUpdate.GetCheck())
						OnOk2(); //�������������� ������
				}
			} else perekl=true;
		}
		break;
	case 2500:
		{
			char date[27];
			SYSTEMTIME st;
			GetLocalTime(&st);
			GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy_MM_dd.a", date, 25);
			if (strcmp(date, curDayFileName.c_str())!=0)
			{
				SaveCurDay(true);//��������� �� ����� ����
				curDayFileName=date;
			}
			GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy_MM.am", date, 25);
			if (strcmp(date, curMonFileName.c_str())!=0)
			{
				SaveCurMonth(true);//��������� �� ����� �����
				curMonFileName=date;
			}
			curHour=st.wHour;
		}
	    break;
	case 3564: //�������������� ������ 5 �����
		{
			SaveCurDay();
			SaveCurMonth();
			SaveYear();
			SaveRules();
			__SetHook__(FALSE);//������������ ����, ����� �������� ��� ���������
			__SetHook__(TRUE);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CEactivityDlg::LoadCurMonth() 
{
	char date[27];
	SYSTEMTIME st;
	GetLocalTime(&st);
	GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy_MM.am", date, 25);
	curMonFileName=date;

	float sumTime=0, sumUsefulTime=0;
	int sumActs=0, sumUsefulActs=0;
	string strf=path_actuser+curMonFileName;
	WriteJournal("LoadCurMonth from %s", strf);
	statsF.LoadFileMonth(strf, aCurMon, sumTime, sumUsefulTime, sumActs, sumUsefulActs);
}

// UpdatePeriodTableViewByHours - ����� ��������� ���������� � ���� � 
//				��������� ���������� � ������� ����
//		��� ���������� ���������� ���������� ��� �������� aCurMon ��� �������� aSelMon ������:
//				- ��� �������� ��������� ����������� ���������� � ������� LoadFileMonth
//					�� �����, ��������, activ_user_2015_11.am
//				- ���������� SaveCurMonth ���������� � ���� �������, ��� ������, 
//					� ��� ����� �������� ������ � �������
//				- �������� ��� �������� ��������� � SumDayStatForCurDay (������ ����� ����� ��������)
//				- �������� � ���� ������� UpdatePeriodTableViewByHours ���������� � ��� aCurMon � aSelMon
//					������ ��� ��� ��������� ���������������� ������������� ����� ���������� 
//					�������� ����� � �������� ��������, ������� �������� ����� �� ������
//				- �������� ���������� � ���� ������� (������ ��������): ��� ������� ����� �� ���� 
//					OnDblclkListDays � ��� ��������� ����� ���� OnSelchangeComboDownTable.
void CEactivityDlg::UpdatePeriodTableViewByHours(activ_hours &activHours) 
{
	int ii=0;
	char fmtSecs[100];
	string date;
	if (SelectedDay!="")
	{
		// ����� ��������� ��� ���������� ���� � ������� ������ �������� ��� ������ ���� �����������
		date = SelectedDay;
	} else {
		// ���� ������������ ���
		date=curDayFileName.substr(curDayFileName.length()-12, 10);
	}
	table_period.DeleteAllItems();
	float sumUsefulSec=0, sumSec=0;
	int sumActs=0, sumUsefulActs=0;
	float usefulTimeForCurrentHour=0;

//	�������� ������ � �������� ���������
	chart.RemoveAllSeries(); //������ ���������� ������
	chart.CreateStandardAxis(CChartCtrl::BottomAxis);
	chart.GetBottomAxis()->GetLabel()->SetText("Hour");
	chart.GetLeftAxis()->GetLabel()->SetText(radioTime.GetCheck() ? "Minutes" : "Actions");
	chart.GetBottomAxis()->SetAutomatic(true);
	CChartLineSerie* pLineCurrentDay = chart.CreateLineSerie();
	pLineCurrentDay->SetWidth(2);
	CChartPointsSerie* pPntsCurrentDay = chart.CreatePointsSerie();
	pPntsCurrentDay->SetPointType(CChartPointsSerie::ptTriangle);
	pPntsCurrentDay->SetPointSize(11,11);
	pPntsCurrentDay->SetColor(pLineCurrentDay->GetColor());
	CChartLineSerie* pLineAverage;
	CChartPointsSerie* pPntsAverage;
	if (lastAverageHoursGraph.size()>2)
	{
		pLineAverage = chart.CreateLineSerie();
		pLineAverage->SetWidth(3);
		pPntsAverage = chart.CreatePointsSerie();
		pPntsAverage->SetPointType(CChartPointsSerie::ptEllipse);
		pPntsAverage->SetPointSize(10,10);
		pPntsAverage->SetColor(pLineAverage->GetColor());
	}

	for (int ii = 0; ii<24; ii++)
	{
		float sumTime=0;
		float usefulTime=0;
		int sumActsHour=0;
		int usefulActs=0;
		for (activ_hours::iterator iter=activHours.begin(); iter!=activHours.end(); iter++)
		{
			if ((*iter).first!=ii)
				continue;
			usefulTime  += (*iter).second.usefulTime;
			sumTime     += (*iter).second.sumTime;
			sumActsHour += (*iter).second.sumActs;
			usefulActs  += (*iter).second.usefulActs;
		}
		char ch_ii[10];
		sprintf_s(ch_ii, "%d", ii);
		if (sumTime>0.0 || sumActsHour>0)
		{
			char ch[100];
			int row = table_period.GetItemCount();
			row = table_period.InsertItem(0, ch_ii);

			float sec = usefulTime/1000;
			if (table_period.max1==-1 || (table_period.max1!=-1 && sec > table_period.max1v))
			{ //���������� ������ ������ � ������� ��� ����������� ������������� ����
				if (table_period.max1!=-1)
				{
					table_period.max2 = table_period.max1; 
					table_period.max2v= table_period.max1v;
				}
				table_period.max1 = row; 
				table_period.max1v= sec;
			} else {
				//������ ������
				if (table_period.max2==-1 || (table_period.max2!=-1 && sec > table_period.max2v))
				{
					table_period.max2 = row; 
					table_period.max2v= sec;
				}
			}
			FormatSeconds(ch, sec);
			table_period.SetItemText(row, 1, ch);
			double chartValue = radioTime.GetCheck() ? sec/60 : usefulActs;
			pLineCurrentDay->AddPoint(ii, chartValue);
			pPntsCurrentDay->AddPoint(ii, chartValue);
			if (lastAverageHoursGraph.size()>2)
			{
				if (lastAverageHoursGraph.find(ii)!=lastAverageHoursGraph.end())
					chartValue = radioTime.GetCheck() ? lastAverageHoursGraph[ii].usefulTime/60/1000 : 
						lastAverageHoursGraph[ii].usefulActs;
				else chartValue = 0;
				pLineAverage->AddPoint(ii, chartValue);
				pPntsAverage->AddPoint(ii, chartValue);
			}
			if (ii==curHour)
				usefulTimeForCurrentHour=usefulTime;

			sec = sumTime/1000;
			FormatSeconds(ch, sec);
			table_period.SetItemText(row, 2, ch);
			sprintf_s(ch, "%d", usefulActs);
			table_period.SetItemText(row, 3, ch);
			sprintf_s(ch, "%d", sumActsHour);
			table_period.SetItemText(row, 4, ch);

			sumUsefulSec += usefulTime;
			sumSec       += sumTime;
			sumActs      += sumActsHour;
			sumUsefulActs    += usefulActs;
		} else {
			if ((SelectedDay == "" && ii <= curHour) || SelectedDay!="")
			{	//� ������������� ����� ������������ ��� ������� ����� �� ������
				pLineCurrentDay->AddPoint(ii, 0);
				pPntsCurrentDay->AddPoint(ii, 0);
			}
			if (lastAverageHoursGraph.size()>2)
			{
				double chartValue;
				if (lastAverageHoursGraph.find(ii)!=lastAverageHoursGraph.end())
					chartValue = radioTime.GetCheck() ? (lastAverageHoursGraph[ii].usefulTime/60/1000) :
						lastAverageHoursGraph[ii].usefulActs;
				else chartValue = 0;
				pLineAverage->AddPoint(ii, chartValue);
				pPntsAverage->AddPoint(ii, chartValue);
			}
		}
	}
	if (combo_group.GetCurSel()<BYMONTHS)
		table_period.InsertItem(0, "..");//��� �������� �� ������� ����
	CString str;
	char ch2[100];
	char ch3[100];
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		str.LoadString(trif.GetIds(SelectedDay!="" ? IDS_STRING1595 : IDS_STRING1637));
		ASSERT(date.length()==10);
		//��������� ���������� ��� ���� ���, ����������� �������� ����������
		if (date.length()==10)
		{
			if (SelectedMon=="")
			{
				aCurMon[date].usefulTime=sumUsefulSec;
				aCurMon[date].sumTime=sumSec;
				aCurMon[date].sumActs=sumActs;
				aCurMon[date].usefulActs=sumUsefulActs;
			} else {
				aSelMon[date].usefulTime=sumUsefulSec;
				aSelMon[date].sumTime=sumSec;
				aSelMon[date].sumActs=sumActs;
				aSelMon[date].usefulActs=sumUsefulActs;
			}
		}
		break;
	default:
		//������ ���� ������ ��������� ������������� ��� ���� �������
		AfxMessageBox("Wrong view period");
	}

	chart.RefreshCtrl();

	FormatSeconds(ch2, sumSec/1000);
	FormatSeconds(ch3, sumUsefulSec/1000);
	char statText[300];
	if (SelectedMon!="" || SelectedDay!="")
	{
		sprintf_s(statText, str, date.c_str(),
			ch3, ch2, sumUsefulActs, sumActs);
	} else {
		sprintf_s(statText, str, ch3, ch2, sumUsefulActs, sumActs);
	}
	stat_periodTable.SetWindowText(statText);

	
	if (lastAverageHoursGraph.size()>2 && SelectedDay=="")
	{//��������� ������� ����������� ����� ��� �������� ����
		double perc_coef;
		SYSTEMTIME st;
		GetLocalTime(&st);
		st.wHour;
		if (lastAverageHoursGraph[st.wHour].usefulTime < 1000)
		{
			perc_coef=100; //�������� ������� �� 0
		} else {
			perc_coef=usefulTimeForCurrentHour/lastAverageHoursGraph[st.wHour].usefulTime*
				60/(st.wMinute+1)*100-100;
			if (perc_coef>500) perc_coef=500;
		}
		double lag=(lastAverageHoursGraph[st.wHour].usefulTime/
			60*(st.wMinute+1) - usefulTimeForCurrentHour)/(lastAverageHoursGraph[st.wHour].usefulTime/
			60*(st.wMinute+1));
		int rr=0, gg=0;
		if (perc_coef < 0)
		{
			rr=50+(int)(600*lag);
			if (rr>255)
				rr=255;
		} else {
			gg=50-(int)(200*lag);//lag ������������� � ����� ���� ������ 1
			if (gg>255)
				gg=255;
			if (st.wMinute<20)
				gg=50;
		}
		char res[300];
		FormatSeconds(fmtSecs, usefulTimeForCurrentHour/1000-
			lastAverageHoursGraph[st.wHour].usefulTime/1000/60*(st.wMinute+1));
		sprintf_s(res, "<b><CENTER><font COLOR=\"%d,%d,0\" size=\"+18\">%s%s</font></CENTER></b>", 
			rr, gg, perc_coef>=0 ? "+" : "", fmtSecs);
		stat_hour_adv.SetWindowText(res);
		str.LoadString(trif.GetIds(IDS_STRING1647+(perc_coef>=0 ? 0 : 2)));
		GetDlgItem(IDC_STATIC_percent_hour)->SetWindowText(str);

		//��������� ����������� ����� ��� ������� �����
		double sumUsefulTimeBeforeCurrentHour=0;
		for (int ii=0; ii<curHour; ii++)
		{
			if (lastAverageHoursGraph.find(ii)!=lastAverageHoursGraph.end())
				sumUsefulTimeBeforeCurrentHour+=lastAverageHoursGraph[ii].usefulTime;
		}
		sumUsefulTimeBeforeCurrentHour += lastAverageHoursGraph[st.wHour].usefulTime/60*(st.wMinute+1);
		//���� �������� �������� ����� � ����������, �� ����������� ����� ������� ���� � ������ ������ ��� ������
		lag=(sumUsefulTimeBeforeCurrentHour-sumUsefulSec)/
				   (sumUsefulTimeBeforeCurrentHour + 1000); //1000 ����� �������� ������� �� ����
		perc_coef=(sumUsefulSec-sumUsefulTimeBeforeCurrentHour)/1000;
		RR=GG=0;
		if (perc_coef < 0)
		{
			RR=50+(int)(600*lag);
			if (RR>255)
				RR=255;
		} else {
			GG=50-(int)(200*lag);//lag ������������� � ����� ���� ������ 1
			if (GG>255)
				GG=255;
		}
		FormatSeconds(fmtSecs, (float)perc_coef);
		sprintf_s(res, "<b><CENTER><font COLOR=\"%d,%d,0\" size=\"+18\">%s%s</font></CENTER></b>", 
			RR, GG, perc_coef>=0 ? "+" : "", fmtSecs);
		stat_day_adv.SetWindowText(res);
		str.LoadString(trif.GetIds(IDS_STRING1651+(perc_coef>=0 ? 0 : 2)));
		GetDlgItem(IDC_STATIC_percent_day2)->SetWindowText(str);
	}
}

// ����� ���������� � ���� � ��������� ���������� � ������� ����
void CEactivityDlg::UpdatePeriodTable(activ &CurView) 
{
	int ii=0;
	char ch[200];
	char ch_secs[100];
	table_period.DeleteAllItems();
	float sumUsefulSec=0, sumSec=0;
	int sumActs=0, sumUsefulActs=0;
//�������� ������ � �������� ���������
	chart.GetLeftAxis()->GetLabel()->SetText(radioTime.GetCheck() ? "Hours" : "Actions");
	chart.RemoveAllSeries(); //������ ���������� ������
	CChartDateTimeAxis* axis;
	if (combo_group.GetCurSel() == BYDAYS)
	{
		chart.CreateStandardAxis(CChartCtrl::BottomAxis);
		chart.GetBottomAxis()->SetAutomatic(true);
		chart.GetBottomAxis()->GetLabel()->SetText("Day");
	} else {
		axis = chart.CreateDateTimeAxis(CChartCtrl::BottomAxis);
		chart.GetBottomAxis()->GetLabel()->SetText("Month");
		axis->SetDiscrete(true);
//		axis->SetTickIncrement(false,CChartDateTimeAxis::tiMonth,1);
		axis->SetTickLabelFormat(false, _T("%b %Y"));
		//axis->SetTickIncrement(false, CChartDateTimeAxis::tiMonth, 1);
		chart.GetBottomAxis()->SetAutomatic(true);
	}
	CChartLineSerie* pLineMonth = chart.CreateLineSerie();
	pLineMonth->SetWidth(2);
	CChartPointsSerie* pPntsMonth;
	pPntsMonth = chart.CreatePointsSerie();
	pPntsMonth->SetPointType(CChartPointsSerie::ptTriangle);
	pPntsMonth->SetPointSize(11,11);
	pPntsMonth->SetColor(pLineMonth->GetColor());

	string sToday = curDayFileName.substr(curDayFileName.length()-12, 10);
	for (activ::iterator iter=CurView.begin(); iter!=CurView.end(); iter++)
	{
		int row = table_period.GetItemCount();
		row = table_period.InsertItem(0, (*iter).first.c_str());
		float sec=(*iter).second.usefulTime/1000;
		if ((*iter).first == sToday)
		{	//������������ ����������� ���� ��� �� ������ ��� � � �������
			table_period.SetTextColor(row, RGB(RR,GG,0));
			TRACE("UpdatePeriodTable SetTextColor row=%d color=%d\n", row, RGB(RR,GG,0));
		}
		if (table_period.max1==-1 || (table_period.max1!=-1 && sec > table_period.max1v))
		{ //���������� ������ ������ � ������� ��� ����������� ������������� ����
			if (table_period.max1!=-1)
			{
				table_period.max2 = table_period.max1; 
				table_period.max2v= table_period.max1v;
			}
			table_period.max1 = row; 
			table_period.max1v= sec;
		} else {
			//������ ������
			if (table_period.max2==-1 || (table_period.max2!=-1 && sec > table_period.max2v))
			{
				table_period.max2 = row; 
				table_period.max2v= sec;
			}
		}
		if (table_period.min1==-1 || (table_period.min1!=-1 && sec < table_period.min1v))
		{ //���������� ������ ������� � ������� ��� ����������� ������������� ����
			if (table_period.min1!=-1)
			{
				table_period.min2 = table_period.min1; 
				table_period.min2v= table_period.min1v;
			}
			table_period.min1 = row; 
			table_period.min1v= sec;
		} else {
			//������ �������
			if (table_period.min2==-1 || (table_period.min2!=-1 && sec < table_period.min2v))
			{
				table_period.min2 = row; 
				table_period.min2v= sec;
			}
		}
		sumUsefulSec+=sec;
		FormatSeconds(ch_secs, sec);
		table_period.SetItemText(row, 1, ch_secs);
		double chartValue = radioTime.GetCheck() ? sec/3600 : (*iter).second.usefulActs;

		int chart_index = table_period.GetItemCount();

		if (combo_group.GetCurSel() == BYDAYS)
		{
			pLineMonth->AddPoint(chart_index, chartValue);
			pPntsMonth->AddPoint(chart_index, chartValue);
		} else {
			CString mon = (*iter).first.c_str();
			COleDateTime odDate(atoi(mon.Left(4)), atoi(mon.Right(2)), 
				1, 0, 0, 0);
			pLineMonth->AddPoint(odDate, chartValue);
			pPntsMonth->AddPoint(odDate, chartValue);
		}

		sec=(*iter).second.sumTime/1000;
		sumSec+=sec;
		FormatSeconds(ch_secs, sec);
		table_period.SetItemText(row, 2, ch_secs);
		sprintf_s(ch_secs, "%d", (*iter).second.sumActs);
		sumActs+=(*iter).second.sumActs;
		table_period.SetItemText(row, 4, ch_secs);
		sprintf_s(ch_secs, "%d", (*iter).second.usefulActs);
		sumUsefulActs+=(*iter).second.usefulActs;
		table_period.SetItemText(row, 3, ch_secs);
	}

	double Min;
	double Max;
	if (combo_group.GetCurSel() != BYDAYS)
	{
		axis->GetMinMax(Min, Max);
		//������������ � ���������� ���������� �� ������ ������� ����� ����������
//		chart.GetBottomAxis()->SetAutomatic(false);
//		axis->SetDiscrete(true);
//		axis->SetTickIncrement(false, CChartDateTimeAxis::tiMonth,1);
		axis->SetMinMax(0.9999*Min, 1.0001*Max);
	}
	chart.RefreshCtrl();

	if (combo_group.GetCurSel()<BYMONTHS)
		table_period.InsertItem(0, "..");//��� �������� �� ������� ����
	CString str;
	char ch2[100];
	char ch3[100];
	string date;
	if (SelectedMon!="")
		date=table_period.GetItemCount() ? table_period.GetItemText(1, 0).Left(7) : "";
	else date=curMonFileName.substr(11, 7);
	switch (combo_group.GetCurSel())
	{
	case BYDAYS:
		str.LoadString(trif.GetIds(SelectedMon!="" ? IDS_STRING1595 : IDS_STRING1591));
		ASSERT(date.length()==7);
		//��������� ���������� ��� ���� ������, ����������� �������� ����������
		aCurYear[date].usefulTime=sumUsefulSec*1000;
		aCurYear[date].sumTime=sumSec*1000;
		aCurYear[date].sumActs=sumActs;
		aCurYear[date].usefulActs=sumUsefulActs;
		break;
	case BYMONTHS:
		str.LoadString(trif.GetIds(IDS_STRING1593));
		break;
	default:
		//���������� ������������� �� ������ ����
		AfxMessageBox("Wrong view period");
	}
	FormatSeconds(ch2, sumSec);
	FormatSeconds(ch3, sumUsefulSec);
	if (SelectedMon!="")
	{
		sprintf_s(ch, str, date.c_str(),
			ch3, ch2, sumUsefulActs, sumActs);
	} else {
		sprintf_s(ch, str, ch3, ch2, sumUsefulActs, sumActs);
	}
	stat_periodTable.SetWindowText(ch);
}


void CEactivityDlg::FormatSeconds(char (&ch)[100], float secs) 
{
	int abs_secs=abs((int)secs);
	if (abs_secs < 1)
	{
		strcpy_s(ch, "-");
		return;
	}
	if (abs_secs>86400)
	{
		sprintf_s(ch, "%dd.%dh:%dm", (int)secs/86400, (abs_secs % 86400)/3600, (abs_secs % 3600)/60);
	} else 
		if (abs_secs>3600)
		{
			sprintf_s(ch, "%dh:%dm", (int)secs/3600, (abs_secs % 3600)/60);
		} else {
			if (abs_secs>60)
			{
				sprintf_s(ch, "%dm:%ds", (int)secs/60, abs_secs % 60);
			} else {
				sprintf_s(ch, "%ds", (int)secs);
			}
		}
}

void CEactivityDlg::SizingWins()
{
	CRect rect, main;
	GetWindowRect(&main);
	ScreenToClient(main);
	int mainHei=main.Height();
	if (mainHei<50)
		return;
	
	GetDlgItem(IDOK)->GetWindowRect(&rect);
	ScreenToClient(rect);
	rect+=CPoint(0, main.bottom-rect.bottom-15);
	GetDlgItem(IDOK)->MoveWindow(rect);

	GetDlgItem(IDC_BUTTON1)->GetWindowRect(&rect);
	ScreenToClient(rect);
	rect+=CPoint(0, main.bottom-rect.bottom-15);
	GetDlgItem(IDC_BUTTON1)->MoveWindow(rect);

	main.bottom=rect.top;//�������� �� ������ ����� (��������, ������������� ������������)
	GetDlgItem(IDC_LIST3)->GetWindowRect(&rect);
	ScreenToClient(rect);
	rect.top=main.bottom-mainHei/4-25;	
	rect.bottom=main.bottom-6;
	rect.right=main.right-15;
	GetDlgItem(IDC_LIST3)->MoveWindow(rect);
 
	main=rect;//�������� �� ������ ���� ������ ����������
	stat_periodTable.GetWindowRect(&rect);
	ScreenToClient(rect);
	rect+=CPoint(0, main.top-rect.bottom-6);
	stat_periodTable.MoveWindow(rect);

	GetDlgItem(IDC_COMBO2)->GetWindowRect(&rect);
	ScreenToClient(rect);
	rect+=CPoint(0, main.top-rect.bottom-6);
	GetDlgItem(IDC_COMBO2)->MoveWindow(rect);

	main.bottom=rect.top;//�������� �� ����� (������������ �� ����/�������)
	GetDlgItem(IDC_LIST2)->GetWindowRect(&rect);
	ScreenToClient(rect);
	rect.bottom=main.bottom-6;
	rect.right=main.right;
	GetDlgItem(IDC_LIST2)->MoveWindow(rect);
}

void CEactivityDlg::Exit() 
{
	SaveCurDay();
	SaveCurMonth();
	SaveYear();
	SaveRules();
	char ch[100];
	edit_capts.GetWindowText(ch, 100);
	AfxGetApp()->WriteProfileInt("App", "CounShowCapt", atoi(ch));
	AfxGetApp()->WriteProfileInt("App", "type_sort_activ", combo_sort.GetCurSel());
	AfxGetApp()->WriteProfileInt("App", "type_group_activ", combo_group.GetCurSel());
	AfxGetApp()->WriteProfileInt("App", "AccentParameter", radioTime.GetCheck());
	__SetHook__(FALSE);
	DelIconTray();
}

bool CEactivityDlg::LoadFileDay(string fname, activ &forLoad1) 
{
	WriteJournal("LoadFileDay from %s", fname.c_str());
	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return false;
	if (forLoad1.size())
		forLoad1.clear();
	char ch[1024];
	ifstr.getline(ch, 100);
	float ver;
	sscanf_s(ch, "ver=%f", &ver);
	for (;;)
	{
		Activity tmpForSave;
		ActivityExe tmpForSave2;
		tmpForSave.usefulTime=0;
		tmpForSave.hour=0;
		tmpForSave2.usefulTime=0;
		tmpForSave2.hour=0;
		void* tmpint;
		ifstr>>tmpint;
		tmpForSave.hwMain=(HWND)tmpint;
		ifstr.get();
		ifstr>>tmpint;
		tmpForSave.hwChil=(HWND)tmpint;
		ifstr.get();
		if (!ifstr)
			break;
		ifstr>>tmpForSave.sumActs;
		tmpForSave2.sumActs=tmpForSave.sumActs;
		ifstr.get();
		ifstr>>tmpForSave.usefulActs;
		tmpForSave2.usefulActs=tmpForSave.usefulActs;
		ifstr.get();
		ifstr>>tmpForSave.sumTime;
		tmpForSave2.sumTime=tmpForSave.sumTime;
		ifstr.get();
		int tmpint2;
		if (ver<0.2)
		{
			ifstr>>tmpint2;
		} else {
			ifstr.getline(ch, 1024, '\t');
			tmpForSave2.hour=tmpForSave.hour=atoi(ch);
		}
		ifstr.getline(ch, 1024, '\t');
		tmpForSave2.exe=tmpForSave.exe=ch;
		ifstr.getline(ch, 1024);
		tmpForSave.capt=ch;
		sprintf_s(ch, "%d\t", tmpForSave.hour);
		forLoad1[ch + tmpForSave.exe + '\t' + tmpForSave.capt] = tmpForSave;
		if (!ifstr)
			break;
	}
	ifstr.close();
	return true;
}

void CEactivityDlg::LoadCurDay() 
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char date[26];
	GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy_MM_dd.a", date, 25);
	curDayFileName=date;

	string strf=path_actuser+curDayFileName;
	//WriteJournal("LoadCurDay from %s", strf.c_str());
	LoadFileDay(strf, ActivToday);
}

void CEactivityDlg::SaveRules()
{
	string strf=path_actuser+"rules.rls";
	ofstream ofstr(strf.c_str());
	if (ofstr==NULL)
		return;
	char ch[]="ver=0.1\n";
	ofstr<<ch;
	for (rulSpis::iterator iter=RULES.begin(); iter!=RULES.end(); iter++)
	{
		ofstr<<(*iter).second.koef;
		ofstr<<'\t';
		ofstr<<(*iter).second.typeRule;
		ofstr<<'\t';
		ofstr<<(*iter).second.exe;
		ofstr<<'\t';
		ofstr<<(*iter).second.capt;
		ofstr<<'\n';
	}
	ofstr.close();
}
void CEactivityDlg::LoadRules() 
{
	string strf=path_actuser+"rules.rls";
	ifstream ifstr(strf.c_str());
	if (ifstr==NULL)
		return;
	char ch[1024];
	ifstr.getline(ch, 100);
	
	sRule tmpRule;
	while (ifstr)
	{
		ifstr>>tmpRule.koef;
		ifstr.get();
		ifstr>>tmpRule.typeRule;
		ifstr.get();
		if (!ifstr)
			break;
		ifstr.getline(ch, 1024, '\t');
		tmpRule.exe=ch;
		ifstr.getline(ch, 1024, '\n');
		tmpRule.capt=ch;
		string exeCapt;
		if (tmpRule.typeRule==0)
			 exeCapt=tmpRule.exe;
		else exeCapt=tmpRule.exe+'\t'+tmpRule.capt;
		RULES[exeCapt]=tmpRule;
		if (!ifstr)
			break;
	}
	ifstr.close();
}

void CEactivityDlg::SaveCurMonth(bool smena)
{
	char date[27];

	if (smena)
	{
		strcpy_s(date, curMonFileName.c_str());
		curMonFileName=date;
	} else {
		SYSTEMTIME st;
		GetLocalTime(&st);
		GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy_MM.am", date, 25);
	}


	string strf=path_actuser+date;
	ofstream ofstr(strf.c_str());
	if (ofstr==NULL)
		return;
	char ch[]="ver=0.2\n";
	ofstr<<ch;
	for (activ::iterator it_activ=aCurMon.begin(); it_activ!=aCurMon.end(); it_activ++)
	{
		Activity tmpForSave=(*it_activ).second;
		ofstr<<(*it_activ).first;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumActs;
		ofstr<<'\t';
		ofstr<<tmpForSave.usefulActs;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumTime;
		ofstr<<'\t';
		ofstr<<tmpForSave.usefulTime;
		ofstr<<'\n';
	}
	ofstr.close();
	if (smena)
	{
		aCurMon.clear();
	}
}

void CEactivityDlg::SaveYear()
{
	char date[28];
	SYSTEMTIME st;
	GetLocalTime(&st);
	GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy", date, 26);
	strcat_s(date, ".ayr");
	
	string strf=path_actuser+date;
	ofstream ofstr(strf.c_str());
	if (ofstr==NULL)
		return;
	char ch[]="ver=0.2\n";
	ofstr<<ch;
	for (activ::iterator it_activ=aCurYear.begin(); it_activ!=aCurYear.end(); it_activ++)
	{
		Activity tmpForSave=(*it_activ).second;
		ofstr<<(*it_activ).first;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumActs;
		ofstr<<'\t';
		ofstr<<tmpForSave.usefulActs;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumTime;
		ofstr<<'\t';
		ofstr<<tmpForSave.usefulTime;
		ofstr<<'\n';
	}
	ofstr.close();
}
void CEactivityDlg::SaveCurDay(bool smena) 
{
	char date[27];
	if (smena)
	{
		strcpy_s(date, curDayFileName.c_str());
	} else {
		SYSTEMTIME st;
		GetLocalTime(&st);
		GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy_MM_dd.a", date, 25);
	}

	string strf=path_actuser+date;
	ofstream ofstr(strf.c_str());
	WriteJournal("Save to file file = %s", strf.c_str());
	if (ofstr==NULL) {
		WriteJournal("!!! Save is failed !!! file = %s", strf.c_str());
		return;
	}
	char ch[]="ver=0.2\n";
	ofstr<<ch;
	for (activ::iterator it_activ=ActivToday.begin(); it_activ!=ActivToday.end(); it_activ++)
 	{
		Activity tmpForSave=(*it_activ).second;
		ofstr<<tmpForSave.hwMain;
		ofstr<<'\t';
		ofstr<<tmpForSave.hwChil;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumActs;
		ofstr<<'\t';
		ofstr<<tmpForSave.usefulActs;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumTime;
		ofstr<<'\t';
		ofstr<<(*it_activ).first;
		ofstr<<'\n';
	}
	ofstr.close();
	if (smena)
	{
		SendReportOfDayOnMail(curDayFileName.substr(curDayFileName.length()-12, 10));
		ActivToday.clear();
	}

}

void CEactivityDlg::SendReportOfDayOnMail(string dateToday) 
{
	CStringArray saDates;
	saDates.Add(dateToday.c_str());
	CStringArray saDates2;
	CTime ct=CTime::GetCurrentTime();
	ct-=60*60*24*7;
	while (ct.GetDayOfWeek()!=2)
	{
		ct-=60*60*24;
	}
	CString date;
	for (int ii=1; ii<=7; ii++)
	{
		date.Format("%d_%02d_%02d", ct.GetYear(), ct.GetMonth(), ct.GetDay());
		saDates2.Add(date);
		ct+=60*60*24;
	}
	CString res = CompareTwoPeriodsOfDays(saDates, saDates2, radioTime.GetCheck(), 2);
	if (res!="")
		SendMailMessage("smtp.gmail.com", 587, "silencenotif@gmail.com", 
		"densaf.ace@gmail.com", "densaf.ace@gmail.com", "GhjcajhyZ88", res, "TablePeriod");
}

BOOL CEactivityDlg::SendMailMessage(LPCTSTR szServer,
								   UINT port, 
								   LPCTSTR szFrom, 
								   LPCTSTR szTo, 
								   LPCTSTR szUser, 
								   LPCTSTR szPas, 
								   LPCTSTR szSubject, 
								   LPCTSTR szMessage)
{

	CSmtp mail;

//#define test_gmail_tls

	bool bError = false;

	try
	{
#define test_gmail_ssl

#if defined(test_gmail_tls)
		mail.SetSMTPServer("smtp.gmail.com",587);
		mail.SetSecurityType(USE_TLS);
		mail.SetLogin(szUser);//"silencenotif@gmail.com"
		mail.SetPassword(szPas);//"yhfveus347tw272d%$"
		mail.SetSenderName("Silence Notif");
		mail.SetSenderMail(szUser);
		mail.SetReplyTo(szUser);
#elif defined(test_gmail_ssl)
		mail.SetSMTPServer("smtp.mail.ru",465);
		mail.SetSecurityType(USE_SSL);
		mail.SetLogin("denis_safonov_81@mail.ru");
		mail.SetPassword("djfGNurnvusmv63^");
		mail.SetSenderName("denis_safonov");
		mail.SetSenderMail("denis_safonov_81@mail.ru");
		mail.SetReplyTo("denis_safonov_81@mail.ru");
#elif defined(test_hotmail_TLS)
		mail.SetSMTPServer("smtp.live.com",25);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_aol_tls)
		mail.SetSMTPServer("smtp.aol.com",587);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_yahoo_ssl)
		mail.SetSMTPServer("plus.smtp.mail.yahoo.com",465);
		mail.SetSecurityType(USE_SSL);
#endif
		CString str;
		//edit_theme.GetWindowText(str);
		mail.SetSubject(szSubject);
		//edit_to.GetWindowText(str);
		mail.AddRecipient("densaf.ace@gmail.com");
		//	mail.AddRecipient("densaf.ace@gmail.com");
		//	mail.AddRecipient("dsafonov@parallels.com");
		mail.SetXPriority(XPRIORITY_NORMAL);
		mail.SetXMailer("The Bat! (v3.02) Professional");
// 		mail.AddMsgLine("Hello,");
// 		mail.AddMsgLine("");
// 		mail.AddMsgLine("...");
// 		mail.AddMsgLine("How are you today?");
// 		mail.AddMsgLine("");
// 		mail.AddMsgLine("Regards");
//		mail.ModMsgLine(5,"regards");
//		mail.DelMsgLine(2);
		for (int ii=1; ii<table_period.GetItemCount(); ii++)
		{
			mail.AddMsgLine(table_period.GetItemText(ii, 0));
		}

		//mail.AddAttachment("../test1.jpg");
		//mail.AddAttachment("c:\\test2.exe");
		//mail.AddAttachment("c:\\test3.txt");
		return mail.Send();
	}
	catch(ECSmtp e)
	{
		//	std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		AfxMessageBox(e.GetErrorText().c_str());
		//OnReport(e.GetErrorText().c_str());
		bError = true;
	}
	//if(!bError)
	//std::cout << "Mail was send successfully.\n";
	return !bError;
}

void CEactivityDlg::OnSave() 
{
	CViewRules ruls;
	ruls.rules=RULES;
	if (ruls.DoModal()!=IDOK)
		return;
	RULES=ruls.rules;
	activ_hours activHours;
	UpdateExeCapt(activHours);
}

void CEactivityDlg::OnSelchangeCombo_sort() 
{
	activ_hours activHours;
	UpdateExeCapt(activHours);
}

// � UpdateExeCapt ����������� ���������� ������� �����������, ������� � ��������� ����� ����
void CEactivityDlg::UpdateExeCapt(activ_hours &activHours) 
{
	char ch[300];
	POSITION pos=table_period.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	float sumTime=0, sumUsefulTime=0;
	int sumActs=0, sumUsefulActs=0;
	int hour=-1;
	string date;//��� ������ ������� ��������� ����������� �� ����������, ��������� ��������:
				//"today", "2015_11_23", "16h"

	if (sel>-1 && combo_group.GetCurSel()==BYHOURS)
	{
		date = table_period.GetItemText(sel, 0)+"h.";
		hour = atoi(date.c_str());
	} else {
		date = SelectedDay=="" ? curDayFileName.substr(curDayFileName.length()-12, 10) : SelectedDay;
	}
	UpdateTableExeCapt(SelectedDay == "" ? ActivToday : aSelDayView, activHours, 
		sumTime, sumUsefulTime, sumActs, sumUsefulActs, hour);
	//��������� � ���� ������
	float sec=sumTime/1000;
	char chComTime[100];
	FormatSeconds(chComTime, sec);
	sec=sumUsefulTime/1000;
	char chUsefulTime[100];
	FormatSeconds(chUsefulTime, sec);

	if (SelectedDay=="")
	{
		if (table_period.GetItemCount() && table_period.GetItemText(0, 0) == date.c_str())
		{	//���� � ���� ������ ������� ���� ����������� ����, �� ��������� ��� ������
			table_period.SetItemText(0, 1, chUsefulTime);
			sprintf_s(ch, "%d", sumActs);
			table_period.SetItemText(0, 2, chComTime);
			sprintf_s(ch, "%d", sumActs);
			table_period.SetItemText(0, 4, ch);
			sprintf_s(ch, "%d", sumUsefulActs);
			table_period.SetItemText(0, 3, ch);
		}
	} else {
		if (sel>-1)
		{
			table_period.SetItemText(sel, 2, chComTime);
			table_period.SetItemText(sel, 1, chUsefulTime);
			sprintf_s(ch, "%d", sumActs);
			table_period.SetItemText(sel, 4, ch);
			sprintf_s(ch, "%d", sumUsefulActs);
			table_period.SetItemText(sel, 3, ch);
		}
	}

	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1571));
	if (showAllCaptsForExe.length())
	{	// ���������� ��� ������������� ���������
		string exekav="\""+exes[showAllCaptsForExe]+"\"";
		sprintf_s(ch, str, exekav.c_str(), chUsefulTime, chComTime, sumUsefulActs, sumActs);
	} else { 
		if (sel>0 && combo_group.GetCurSel()==BYHOURS)
		{	//���������� ��� ���������� ����
			sprintf_s(ch, str, date.c_str(), chUsefulTime, chComTime, sumUsefulActs, sumActs);
		} else { //���������� ��� �����
			if (SelectedDay == "")
			{	//��� ������������ ���
				str.LoadString(trif.GetIds(IDS_STRING1575));
				sprintf_s(ch, str, chUsefulTime, chComTime, sumUsefulActs, sumActs);
			} else {	//��� ��������� �����
				sprintf_s(ch, str, date.c_str(), chUsefulTime, chComTime, sumUsefulActs, sumActs);
			}
		}
	}
	stat_ExeCapt.SetWindowText(ch);
}

// ������� ���� � ���� ��������� ���������� ��� ���������� ����, ���, ������
void CEactivityDlg::OnDblclkListDays(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos=table_period.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	string date=table_period.GetItemText(sel, 0);
	if (date=="..")
	{
		combo_group.SetCurSel(combo_group.GetCurSel()+1);
		OnSelchangeComboDownTable();
		return;
	}
	string fname;
	activ_hours activHours;
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		UpdateExeCapt(activHours);
		break;
	case BYDAYS:
		fname=path_actuser+"activ_user_"+date+".a";
		if  ("activ_user_"+date+".a"==curDayFileName)
		{
			SelectedDay="";
			UpdateExeCapt(activHours);
			combo_group.SetCurSel(0);
			UpdatePeriodTableViewByHours(activHours);
			return;
		}
		if (!LoadFileDay(fname, aSelDayView))
		{
			AfxMessageBox(trif.GetIds(IDS_STRING1573));
			return;
		}
		SelectedDay=date;
		UpdateExeCapt(activHours);
		combo_group.SetCurSel(0);
		UpdatePeriodTableViewByHours(activHours);
		break;
	case BYMONTHS:
		fname=path_actuser+"activ_user_"+date+".am";
		combo_group.SetCurSel(1);
		if  ("activ_user_"+date+".am"==curMonFileName)
		{
			SelectedMon="";
			UpdatePeriodTable(aCurMon);
			return;
		}
		float sumTime=0, sumUsefulTime=0;
		int sumActs=0, sumUsefulActs=0;
		if (!statsF.LoadFileMonth(fname, aSelMon, sumTime, sumUsefulTime, sumActs, sumUsefulActs))
		{
			AfxMessageBox(trif.GetIds(IDS_STRING1573));
			return;
		}
		SelectedMon=date;
		UpdatePeriodTable(aSelMon);
		break;
	}
	*pResult = 0;
}

void CEactivityDlg::OnActivitySetKoef() 
{	//����: ���������� ����������� ��� ��������� � exe
	POSITION pos=table_exe_capt.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	CKoeff koef;
	koef.tmpRule.exe=GetExeFromTable(sel).c_str();
	koef.tmpRule.capt=table_exe_capt.GetItemText(sel, 1);
	//���� ��������� ������� � ����� �� ���� �����������
	string exeCapt=koef.tmpRule.exe+'\t'+koef.tmpRule.capt;
	rulSpis::iterator pRule_tmp=RULES.find(exeCapt);
	if (pRule_tmp==RULES.end())
		pRule_tmp=ownFind(koef.tmpRule.capt);
	if (pRule_tmp==RULES.end())
	{
		koef.tmpRule.koef=1.00;
		koef.tmpRule.typeRule=1;
	} else {
		koef.tmpRule=(*pRule_tmp).second;
	}
	WriteJournal("ID_ACTIVITY_SETKOEF capt=%s", koef.tmpRule.capt.c_str());
	if (koef.DoModal()!=IDOK)
		return;
	if (pRule_tmp==RULES.end()) //������� ����� �������
	{
		RULES[koef.tmpRule.exe+"\t"+koef.tmpRule.capt]=koef.tmpRule;
	} else {
		if (koef.tmpRule.typeRule==2 && exeCapt!=koef.tmpRule.exe+'\t'+koef.tmpRule.capt)
		{
			RULES.erase(pRule_tmp);
			RULES[koef.tmpRule.exe+'\t'+koef.tmpRule.capt]=koef.tmpRule;
		} else {
			(*pRule_tmp).second.koef=koef.tmpRule.koef;
			(*pRule_tmp).second.capt=koef.tmpRule.capt;
			(*pRule_tmp).second.typeRule=koef.tmpRule.typeRule;
		}
	}
	activ_hours activHours;
	UpdateExeCapt(activHours);
}

//��������� ������ � ����
void CEactivityDlg::SetToTray(int ResConst, bool modify)
{
	NOTIFYICONDATA nf;
	nf.cbSize= sizeof(NOTIFYICONDATA);
	nf.hWnd = m_hWnd;
	nf.uID = 0;

	nf.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nf.uCallbackMessage = WM_MYICONNOTIFY;
	strcpy_s(nf.szTip,"AutoClickExtreme");

	HICON hIcon;//IDR_MAINFRAME
	hIcon=AfxGetApp()->LoadIcon(ResConst);
	nf.hIcon = hIcon;
	if (modify){//��� �������
		Shell_NotifyIcon(NIM_MODIFY,&nf);
	} else {//��� ������� �����
		Shell_NotifyIcon(NIM_ADD,&nf);
	}
}

//�������� ������ �� ����
void CEactivityDlg::DelIconTray()
{
	NOTIFYICONDATA nf;
	nf.hWnd = m_hWnd;
	nf.uID = NULL;
	nf.uFlags = NIF_ICON;
	nf.uCallbackMessage = NULL;
	nf.hIcon = NULL;
	Shell_NotifyIcon(NIM_DELETE,&nf);
}

string CEactivityDlg::GetExeFromTable(int sel) 
{
	for (int ii=sel; sel>=0; sel--)
	{	//���� ����� �� ������� ���� �� ��������� �� ��� ���������
		string exe=table_exe_capt.GetItemText(sel, 6);
		if (exe.length())
			return exe;
	}
	return "";
}

void CEactivityDlg::OnRclickTableExeCapt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos=table_exe_capt.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	if (table_exe_capt.GetItemText(sel, 0).GetLength())
	{
		menuExeCapt.EnableMenuItem(ID_ACTIVITY_SETKOEF, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		menuExeCapt.EnableMenuItem(ID_ACTIVITY_SETKOEFEXE, MF_BYCOMMAND | MF_ENABLED );
	} else {
		menuExeCapt.EnableMenuItem(ID_ACTIVITY_SETKOEFEXE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		menuExeCapt.EnableMenuItem(ID_ACTIVITY_SETKOEF, MF_BYCOMMAND | MF_ENABLED );
	}

	CPoint po;
	GetCursorPos(&po);
	menuExeCapt.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, po.x, po.y, this);
	*pResult = 0;
}

void CEactivityDlg::OnRclickPeriodTable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos=table_period.GetFirstSelectedItemPosition();
	int sel=(int)pos;
	if (!sel)
	{
		menuTablePeriod.EnableMenuItem(ID_Compare2Periods, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		menuTablePeriod.EnableMenuItem(ID_IDR_32783, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	} else {
		CString str;
		str=table_period.GetItemText(sel-1, 0);
		if (str.GetLength() < 7)
			menuTablePeriod.EnableMenuItem(ID_Compare2Periods, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		else {
			if (str.GetLength() == 7)
				menuTablePeriod.EnableMenuItem(ID_IDR_32783, MF_BYCOMMAND | MF_ENABLED );
			menuTablePeriod.EnableMenuItem(ID_Compare2Periods, MF_BYCOMMAND | MF_ENABLED );
		}
	}

	CPoint po;
	GetCursorPos(&po);
	menuTablePeriod.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, po.x, po.y, this);
	*pResult = 0;
}

//������ ������ �������� �� ������� �����������
//��� ��������� ������-������ ������� ����� ��������������� ��� ���������� � ��� ��� ���������, 
//��� ������� �������� ������� ��������������� useful acts (�������� ��������)

//������� ����� �������� �� ��������� (������ ����� "*" � �������� ������ ����� ������ ��������)
	//�� ������������� ���������

//��������� ������: ���� ���� ������� � ���������� � ���������� ����������, �� ��� �������, ����� �� ���������
	//���� ����������� ������� � ���������� ����������, ���� ������� ����

void CEactivityDlg::OnActivitySetkoefeExe() 
{	//����: ��������� ������������ ��� ����� exe
	POSITION pos=table_exe_capt.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	CKoeff koef;
	koef.tmpRule.exe=GetExeFromTable(sel).c_str();
	koef.tmpRule.capt="";
	//���� ��������� ������� � ����� �� ���� �����������
	string exe=koef.tmpRule.exe;
	rulSpis::iterator pRule_tmp=RULES.find(exe);
	if (pRule_tmp==RULES.end())
	{
		koef.tmpRule.typeRule=0;
		koef.tmpRule.koef=1.00;
	} else {
		koef.tmpRule=(*pRule_tmp).second;
	}
	if (koef.DoModal()!=IDOK)
		return;
	if (pRule_tmp==RULES.end()) 
	{//������� ����� �������
		RULES[koef.tmpRule.exe]=koef.tmpRule;
	} else {
		(*pRule_tmp).second.koef=koef.tmpRule.koef;
	}
	activ_hours activHours;
	UpdateExeCapt(activHours);
}

BOOL CEactivityDlg::PreTranslateMessage(MSG* pMsg) 
{
//	if (pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST)
//		tool_tip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CEactivityDlg::OnChangeEDITcapts() 
{
	activ_hours activHours;
	UpdateExeCapt(activHours);
}

void CEactivityDlg::OnActivityShowAllCapts() 
{
	CString str;
	if (!showAllCaptsForExe.length())
	{
		POSITION pos=table_exe_capt.GetFirstSelectedItemPosition();
		int sel=(int)pos-1;
		if (sel<0)
			return;
		showAllCaptsForExe=GetExeFromTable(sel).c_str();
		str.LoadString(trif.GetIds(IDS_STRING1587));
	} else {
		showAllCaptsForExe="";
		str.LoadString(trif.GetIds(IDS_STRING1585));
	}
	menuExeCapt.ModifyODMenu(str, ID_ACTIVITY_EXE);
	activ_hours activHours;
	UpdateExeCapt(activHours);
}

void CEactivityDlg::OnDblclkListCurDay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnActivityShowAllCapts();
	*pResult = 0;
}

// OnSelchangeComboDownTable ���������� ��� ������ ����� ������ � ����� ���� ������� 
//			����������� ������ � ����
void CEactivityDlg::OnSelchangeComboDownTable() 
{
	if (combo_group.GetCurSel()>0)
		SelectedMon="";
	LVCOLUMN lvCol;
	::ZeroMemory((void *)&lvCol, sizeof(LVCOLUMN));
	lvCol.mask=LVCF_TEXT;
	table_period.GetColumn(0,&lvCol);
	CString str;
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		{
			activ_hours activHours;
			str.LoadString(trif.GetIds(IDS_STRING1639));
			UpdateExeCapt(activHours);
			UpdatePeriodTableViewByHours(activHours);
		}
		break;
	case BYDAYS:
		str.LoadString(trif.GetIds(IDS_STRING1641));
		UpdatePeriodTable(aCurMon);
		break;
	case BYMONTHS:
		str.LoadString(trif.GetIds(IDS_STRING1643));
		UpdatePeriodTable(aCurYear);
		break;
	}
	lvCol.pszText = str.GetBuffer(100);
	table_period.SetColumn(0,&lvCol);
}

void CEactivityDlg::OnBnClickedOk()
{
	OnOk2();
//	COLORREF text = RGB(0,255,0);
//	table_period.OnDisplayCellColor(2,2, text, text);
}

bool CEactivityDlg::WriteJournal(LPCTSTR lpszFormat, ...)
{
	va_list argList;
	char postfix[1024];
	va_start(argList, lpszFormat);
	vsprintf_s(postfix, lpszFormat, argList);
	va_end(argList);

	CTime ct=CTime::GetCurrentTime();
	char ch[1024];
	sprintf_s(ch, "\n%02d.%02d.%02d\t%02d:%02d:%02d %s", 
		ct.GetYear(), ct.GetMonth(), ct.GetDay(),
		ct.GetHour(), ct.GetMinute(), ct.GetSecond(), postfix);
	CStdioFile sfLog;
	if (!sfLog.Open(path_exe+"\\Journal.txt", CFile::modeWrite))
	{
		if (!sfLog.Open(path_exe+"\\Journal.txt", CFile::modeWrite|CFile::modeCreate)){
			return false;
		}   
	}
	sfLog.SeekToEnd();
	sfLog.WriteString(ch);
	sfLog.Close();
	return true;
}

void CEactivityDlg::OnBnClickedCancel()
{
	Exit();
	OnOK();
	OnCancel();
}

//������� �������� ��������� �������/�������� �� ��������� 7 ���� ��� ������ 
//		(������� ������� � lastDays) c ��������� �� �����
void CEactivityDlg::CalculateAverageUsefulParameter(int lastDays, double thresholdHoliday)
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	// ���� ������������ ���
	string date=curDayFileName.substr(curDayFileName.length()-12, 10);
	int day = atoi(date.substr(date.length()-2, 2).c_str())-1;
	int skippedDays=0;//������� ���� �� ������� ���������
	string yearMon = date.substr(0, 7);
	int sumHandledDays=0;//���������� ������������ ������� ����
	ActivityExe alldays; //��������� ���������� �� ���� ����, ����� ����� �������� ����������� �� ����
	alldays.sumActs=0; alldays.sumTime=0; alldays.usefulActs=0; alldays.usefulTime=0;
	table_period.DeleteAllItems();
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1669));
	stat_periodTable.SetWindowText(str);
	char ch[100];
	if (!day)
	{	//��� ������� ����� ����� ��������� � ���������� �����
		int mon = atoi(yearMon.substr(yearMon.length()-2, 2).c_str());
		mon--;
		sprintf_s(ch, "%s_%d", yearMon.substr(0, 4).c_str(), mon);
		yearMon = ch;
		day=31;
	}
	while (day>0)
	{
		char fname[2048];
		sprintf_s(fname, "%sactiv_user_%s_%02d.a", path_actuser.c_str(), yearMon.c_str(), day);
		activ aDayActiv;
		if (!LoadFileDay(fname, aDayActiv))
		{
			skippedDays++;
			if (skippedDays>15)
			{
				AfxMessageBox(trif.GetIds(IDS_STRING1645));
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
				return;
			}
			day--;//��������� � ���������� ����������� ���
			if (!day)
			{
				int mon = atoi(yearMon.substr(yearMon.length()-2, 2).c_str());
				mon--;
				sprintf_s(ch, "%s_%d", yearMon.substr(0, 4).c_str(), mon);
				yearMon = ch;
				day=31;
			}
			continue;
		}
		activ_exe activExe; 
		activ_hours activHours;
		activ_hours activHours2;
		sprintf_s(ch, "%s_%02d", yearMon.c_str(), day);
		int row=table_period.InsertItem(0, ch);
		CalculateUsefulTimeAndActs(aDayActiv, activExe, activHours);
		activHours2=activHours;
		if (activHours[25].usefulTime>thresholdHoliday*3600*1000)
		{ //���� ��������� ������� ������ 2�� �����, �� ������� ���� ���� ������� � ����� ���������� �� ����
			sumHandledDays++;
			// ��������� ��������� ���������� activHours � ��������� lastAverageHoursGraph
			for (activ_hours::iterator iter=activHours.begin(); iter!=activHours.end(); iter++)
			{
				activ_hours::iterator iterHour = lastAverageHoursGraph.find((*iter).first);
				if (iterHour == lastAverageHoursGraph.end())
				{
					ActivityExe hourElement;
					hourElement.usefulActs = (*iter).second.usefulActs;
					hourElement.usefulTime = (*iter).second.usefulTime;
					hourElement.sumActs    = (*iter).second.sumActs;
					hourElement.sumTime    = (*iter).second.sumTime;
					lastAverageHoursGraph[(*iter).first] = hourElement;
				} else {
					(*iterHour).second.usefulActs += (*iter).second.usefulActs;
					(*iterHour).second.usefulTime += (*iter).second.usefulTime;
					(*iterHour).second.sumActs    += (*iter).second.sumActs;
					(*iterHour).second.sumTime    += (*iter).second.sumTime;
				}
			}
			alldays.sumActs+=activHours[25].sumActs; alldays.sumTime+=activHours[25].sumTime; 
			alldays.usefulActs+=activHours[25].usefulActs; alldays.usefulTime+=activHours[25].usefulTime;
		} else {
			table_period.SetItemText(row, 5, "Holiday!");
		}
		float sec = activHours[25].usefulTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = activHours[25].sumTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", activHours[25].usefulActs);
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", activHours[25].sumActs);
		table_period.SetItemText(row, 4, ch);

		if (lastDays==sumHandledDays)
			break;//���������� ����������� ��� ������� ���������� ����
		day--;//��������� � ���������� ����������� ���
		if (!day)
		{
			int mon = atoi(yearMon.substr(yearMon.length()-2, 2).c_str());
			mon--;
			sprintf_s(ch, "%s_%02d", yearMon.substr(0, 4).c_str(), mon);
			yearMon = ch;
			day=31;
		}
	}
	int row=table_period.InsertItem(0, "Average");
	float sec = alldays.usefulTime/1000/sumHandledDays;
	FormatSeconds(ch, sec);
	table_period.SetItemText(row, 1, ch);
	sec = alldays.sumTime/1000/sumHandledDays;
	FormatSeconds(ch, sec);
	table_period.SetItemText(row, 2, ch);
	sprintf_s(ch, "%d", alldays.usefulActs/sumHandledDays);
	table_period.SetItemText(row, 3, ch);
	sprintf_s(ch, "%d", alldays.sumActs/sumHandledDays);
	table_period.SetItemText(row, 4, ch);
	table_period.InsertItem(0, "..");

	//���������� �������
	chart.GetLeftAxis()->GetLabel()->SetText(radioTime.GetCheck() ? "Minutes" : "Actions");
	chart.RemoveAllSeries(); //������ ���������� ������
	chart.CreateStandardAxis(CChartCtrl::BottomAxis);
	chart.GetBottomAxis()->GetLabel()->SetText("Hour");
	chart.GetBottomAxis()->SetAutomatic(true);
	CChartLineSerie* pLineAverage = chart.CreateLineSerie();
	pLineAverage->SetWidth(2);
	CChartPointsSerie* pPntsAverage;
	pPntsAverage = chart.CreatePointsSerie();
	pPntsAverage->SetPointType(CChartPointsSerie::ptTriangle);
	pPntsAverage->SetPointSize(11,11);
	pPntsAverage->SetColor(pLineAverage->GetColor());
	for (activ_hours::iterator iter=lastAverageHoursGraph.begin(); iter!=lastAverageHoursGraph.end(); iter++)
	{
		//��������� ����� � ��������� ����������
		(*iter).second.usefulTime = (*iter).second.usefulTime / sumHandledDays;
		(*iter).second.usefulActs = (*iter).second.usefulActs / sumHandledDays;
		if (iter->first==25)
			continue;
		double chartValue = radioTime.GetCheck() ? (*iter).second.usefulTime/60/1000 : 
			(*iter).second.usefulActs;
		pLineAverage->AddPoint(iter->first, chartValue);
		pPntsAverage->AddPoint(iter->first, chartValue);
	}
	chart.RefreshCtrl();
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

//������� � ��������� �������� ��������� �������/�������� ���� ����������� ������� 
//		�� ������� �������� 2 ����� � ���������� ����������
// int MinusDays - ������� ������ ���� �� ��������� �� ������ ������ ��� (��������� ��������)
CString CEactivityDlg::CompareTwoPeriodsOfDays(CStringArray& saDates1, CStringArray& saDates2, 
						int accentParameter, int MinusDays, double thresholdHoliday)
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	checkAutoUpdate.SetCheck(false);//��������� �������������� ����������
	ActivityExe firstPeriod; //��������� ���������� �� ������� �������, ����� ����� �������� ����������� �� ����
	firstPeriod.sumActs=0; firstPeriod.sumTime=0; firstPeriod.usefulActs=0; firstPeriod.usefulTime=0;
	ActivityExe secondPeriod; //��������� ���������� �� ������� �������, ����� ����� �������� ����������� �� ����
	secondPeriod.sumActs=0; secondPeriod.sumTime=0; secondPeriod.usefulActs=0; secondPeriod.usefulTime=0;

	//�������� ������ � �������� ���������
	CChartLineSerie   *pLinePeriod1, *pLinePeriod2;
	CChartPointsSerie *pPntsPeriod1, *pPntsPeriod2;
	chart.RemoveAllSeries(); //������ ���������� ������
	CChartDateTimeAxis* axis1 = chart.CreateDateTimeAxis(CChartCtrl::BottomAxis);
	axis1->SetTickLabelFormat(false, _T("%d %b"));
	chart.GetBottomAxis()->SetAutomatic(true);
	chart.GetLeftAxis()->SetAutomatic(true);
	chart.GetBottomAxis()->GetLabel()->SetText("Day");

	CChartDateTimeAxis* axis2;
	if (saDates2.GetSize())
	{
		axis2 = chart.CreateDateTimeAxis(CChartCtrl::TopAxis);
		axis2->SetTickLabelFormat(false, _T("%d %b"));
		chart.GetTopAxis()->SetAutomatic(true);
	}

	chart.GetLeftAxis()->GetLabel()->SetText(accentParameter ? "Hours" : "Actions");
	pLinePeriod1 = chart.CreateLineSerie();
	pLinePeriod1->SetWidth(2);
	pPntsPeriod1 = chart.CreatePointsSerie();
	pPntsPeriod1->SetPointType(CChartPointsSerie::ptTriangle);
	pPntsPeriod1->SetPointSize(11,11);
	pPntsPeriod1->SetColor(pLinePeriod1->GetColor());

	if (saDates2.GetSize())
	{
		pLinePeriod2 = chart.CreateLineSerie(1);
		pLinePeriod2->SetWidth(2);
		pPntsPeriod2 = chart.CreatePointsSerie(1);
		pPntsPeriod2->SetPointType(CChartPointsSerie::ptEllipse);
		pPntsPeriod2->SetPointSize(10,10);
		pPntsPeriod2->SetColor(pLinePeriod2->GetColor());
	}

	CString str; 
	table_period.DeleteAllItems();
	str.LoadString(trif.GetIds(IDS_STRING1667));
	stat_periodTable.SetWindowText(str);
	char ch[100];float sec;
	int handled1=0;
	for (int ii=0; ii<saDates1.GetSize(); ii++)
	{
		char fname[2048];
		sprintf_s(fname, "%sactiv_user_%s.a", path_actuser.c_str(), saDates1[ii]);
		activ aDayActiv;
			if (!LoadFileDay(fname, aDayActiv))
		{
			CString str;
			str.LoadString(trif.GetIds(IDS_STRING1655));
			AfxMessageBox(str + saDates1[ii]);
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			return "";
		}
		activ_exe activExe; 
		activ_hours activHours;
		int row=table_period.InsertItem(0, saDates1[ii]);
		CalculateUsefulTimeAndActs(aDayActiv, activExe, activHours);
		if (activHours[25].usefulTime>thresholdHoliday*3600*1000)
		{
			handled1++;
			// ��������� ��������� ���������� activHours � ��������� lastAverageHoursGraph
			for (activ_hours::iterator iter=activHours.begin(); iter!=activHours.end(); iter++)
			{
				activ_hours::iterator iterHour = lastAverageHoursGraph.find((*iter).first);
				if (iterHour == lastAverageHoursGraph.end())
				{
								ActivityExe hourElement;
					hourElement.usefulActs = (*iter).second.usefulActs;
					hourElement.usefulTime = (*iter).second.usefulTime;
					hourElement.sumActs    = (*iter).second.sumActs;
					hourElement.sumTime    = (*iter).second.sumTime;
					lastAverageHoursGraph[(*iter).first] = hourElement;
				} else {
					(*iterHour).second.usefulActs += (*iter).second.usefulActs;
					(*iterHour).second.usefulTime += (*iter).second.usefulTime;
					(*iterHour).second.sumActs    += (*iter).second.sumActs;
					(*iterHour).second.sumTime    += (*iter).second.sumTime;
						}
			}
			firstPeriod.sumActs+=activHours[25].sumActs; firstPeriod.sumTime+=activHours[25].sumTime; 
			firstPeriod.usefulActs+=activHours[25].usefulActs; firstPeriod.usefulTime+=activHours[25].usefulTime;
		} else {
			table_period.SetItemText(row, 5, "Holiday!");
		}

		double chartValue = accentParameter ? activHours[25].usefulTime/60/60/1000 : activHours[25].usefulActs;
		COleDateTime oleDate(atoi(saDates1[ii].Left(4)), atoi(saDates1[ii].Mid(5)), 
			atoi(saDates1[ii].Right(2)), 0, 0, 0);
		pLinePeriod1->AddPoint(oleDate, chartValue);
		pPntsPeriod1->AddPoint(oleDate, chartValue);
		chart.RefreshCtrl();

		float sec = activHours[25].usefulTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = activHours[25].sumTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", activHours[25].usefulActs);
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", activHours[25].sumActs);
		table_period.SetItemText(row, 4, ch);

	}
	int row;
	if (saDates1.GetSize()>1 && handled1>0)
	{	// ��� ����� ���� �� ����� ������ �������� �������
		str.LoadString(trif.GetIds(IDS_STRING1657));//�������
		int row=table_period.InsertItem(0, str);
		float sec = firstPeriod.usefulTime/1000/handled1;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = firstPeriod.sumTime/1000/handled1;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", firstPeriod.usefulActs/handled1);
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", firstPeriod.sumActs/handled1);
		table_period.SetItemText(row, 4, ch);

		str.LoadString(trif.GetIds(IDS_STRING1671));//�����
		row=table_period.InsertItem(0, str);
		sec = firstPeriod.usefulTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = firstPeriod.sumTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", firstPeriod.usefulActs);
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", firstPeriod.sumActs);
		table_period.SetItemText(row, 4, ch);
	}
	table_period.InsertItem(table_period.GetItemCount(), "");

	ActivityExe min1, min2;//��� ������ ����� �������������� ���� (��������)
	int indexMin1, indexMin2;
	int rowAddSecondPeriod = table_period.GetItemCount();
	int handled2=0;
	for (int ii=0; ii<saDates2.GetSize(); ii++)
	{
		char fname[2048];
		sprintf_s(fname, "%sactiv_user_%s.a", path_actuser.c_str(), saDates2[ii]);
		activ aDayActiv;
		if (!LoadFileDay(fname, aDayActiv))
		{
			CString str;
			str.LoadString(trif.GetIds(IDS_STRING1655));
			AfxMessageBox(str + saDates2[ii]);
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			return "";
		}
		activ_exe activExe; 
		activ_hours activHours;
		int row=table_period.InsertItem(rowAddSecondPeriod, saDates2[ii]);
		CalculateUsefulTimeAndActs(aDayActiv, activExe, activHours);
		if (activHours[25].usefulTime>thresholdHoliday*3600*1000)
		{
			handled2++;
			// ��������� ��������� ���������� activHours � ��������� lastAverageHoursGraph
			for (activ_hours::iterator iter=activHours.begin(); iter!=activHours.end(); iter++)
			{
				activ_hours::iterator iterHour = lastAverageHoursGraph.find((*iter).first);
				if (iterHour == lastAverageHoursGraph.end())
				{
					ActivityExe hourElement;
					hourElement.usefulActs = (*iter).second.usefulActs;
					hourElement.usefulTime = (*iter).second.usefulTime;
					hourElement.sumActs    = (*iter).second.sumActs;
					hourElement.sumTime    = (*iter).second.sumTime;
					lastAverageHoursGraph[(*iter).first] = hourElement;
				} else {
					(*iterHour).second.usefulActs += (*iter).second.usefulActs;
					(*iterHour).second.usefulTime += (*iter).second.usefulTime;
					(*iterHour).second.sumActs    += (*iter).second.sumActs;
					(*iterHour).second.sumTime    += (*iter).second.sumTime;
				}
			}
		} else {
			table_period.SetItemText(row, 5, "Holiday!");
		}
		secondPeriod.sumActs+=activHours[25].sumActs; secondPeriod.sumTime+=activHours[25].sumTime; 
		secondPeriod.usefulActs+=activHours[25].usefulActs; secondPeriod.usefulTime+=activHours[25].usefulTime;

		if (saDates2.GetSize()>1) //�� ������ ������� ���� ����� �� �����
		{
			//��������� 2 ���������� ������������� ���������
			double accentValue = accentParameter ? activHours[25].usefulTime : activHours[25].usefulActs;
			if (ii==0)
			{
				min1=min2=activHours[25];
				indexMin1=indexMin2=0;
			} else {
				if (accentParameter ? (accentValue < min1.usefulTime) : (accentValue < min1.usefulActs))
				{
					min2 = min1; indexMin2 = indexMin1;
					min1 = activHours[25]; indexMin1 = ii;
				} else if (accentParameter ? min2.usefulTime : min2.usefulActs) {
					min2 = activHours[25]; indexMin2 = ii;
				}
			}
			double chartValue = accentParameter ? activHours[25].usefulTime/60/60/1000 : activHours[25].usefulActs;
			COleDateTime oleDate(atoi(saDates2[ii].Left(4)), atoi(saDates2[ii].Mid(5)), 
				atoi(saDates2[ii].Right(2)), 0, 0, 0);
			pLinePeriod2->AddPoint(oleDate, chartValue);
			pPntsPeriod2->AddPoint(oleDate, chartValue);
			chart.RefreshCtrl();
		}

		float sec = activHours[25].usefulTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = activHours[25].sumTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", activHours[25].usefulActs);
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", activHours[25].sumActs);
		table_period.SetItemText(row, 4, ch);

	}
	if (MinusDays==2)
	{
		secondPeriod.usefulTime -= min1.usefulTime;
		secondPeriod.usefulActs -= min1.usefulActs;
		secondPeriod.sumActs    -= min1.sumActs;
		secondPeriod.sumTime    -= min1.sumTime;
		secondPeriod.usefulTime -= min2.usefulTime;
		secondPeriod.usefulActs -= min2.usefulActs;
		secondPeriod.sumActs    -= min2.sumActs;
		secondPeriod.sumTime    -= min2.sumTime;
		//�������� ���� ������ ��������� �������
		for (int ii=0; ii < table_period.GetItemCount(); ii++)
		{
			str = table_period.GetItemText(ii, 0);
			if (str==saDates2[indexMin1] || str==saDates2[indexMin2])
			{
				table_period.DeleteItem(ii);
				ii--;
			}
		}
	}
	CString theme;
	if (saDates2.GetSize() && handled2 > 0)
	{   //������� ��� ������� ���������� �������
		str.LoadString(trif.GetIds(IDS_STRING1657));
		row=table_period.InsertItem(rowAddSecondPeriod, str);
		sec = secondPeriod.usefulTime/1000/(handled2 - MinusDays);
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = secondPeriod.sumTime/1000/(handled2 - MinusDays);
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", secondPeriod.usefulActs/(handled2 - MinusDays));
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", secondPeriod.sumActs/(handled2 - MinusDays));
		table_period.SetItemText(row, 4, ch);

		str.LoadString(trif.GetIds(IDS_STRING1671)); //�����
		row=table_period.InsertItem(rowAddSecondPeriod, str);
		sec = secondPeriod.usefulTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = secondPeriod.sumTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", secondPeriod.usefulActs);
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", secondPeriod.sumActs);
		table_period.SetItemText(row, 4, ch);

		str.LoadString(trif.GetIds(IDS_STRING1659));//�������
		row = table_period.InsertItem(0, str);
		double grow = (firstPeriod.usefulTime/saDates1.GetSize())/(secondPeriod.usefulTime/
			(handled2 - MinusDays))*100.0 - 100.0;
		sprintf_s(ch, "%.2f%%", grow);
		theme.Format("%s %s ��������� ������� � %.2f%% �������� ��������", str, ch, 
			((double)firstPeriod.usefulActs/saDates1.GetSize())/((double)secondPeriod.usefulActs/
			(handled2 - MinusDays))*100.0 - 100.0);
		table_period.SetItemText(row, 1, ch);
		grow = (firstPeriod.sumTime/saDates1.GetSize())/(secondPeriod.sumTime/
			(handled2 - MinusDays))*100.0 - 100.0;
		sprintf_s(ch, "%.2f%%", grow);
		table_period.SetItemText(row, 2, ch);
		grow = ((double)firstPeriod.usefulActs/saDates1.GetSize())/((double)secondPeriod.usefulActs/
			(handled2 - MinusDays))*100.0 - 100.0;
		sprintf_s(ch, "%.2f%%", grow);
		table_period.SetItemText(row, 3, ch);
		grow = ((double)firstPeriod.sumActs/saDates1.GetSize())/((double)secondPeriod.sumActs/
			(handled2 - MinusDays))*100.0 - 100.0;
		sprintf_s(ch, "%.2f%%", grow);
		table_period.SetItemText(row, 4, ch);
	}

	table_period.InsertItem(0, "..");

	double Min;
	double Max;
	axis1->GetMinMax(Min, Max);
	axis1->SetMinMax(0.99999*Min, 1.00001*Max);
	chart.RefreshCtrl();

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return theme;
}

//������� � ��������� �������� ��������� �������/�������� ���� ����������� ������� 
//		�� ������� �������� 2 ����� � ���������� ����������
void CEactivityDlg::CompareTwoPeriodsOfMons(CStringArray& saDates1, CStringArray& saDates2)
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	checkAutoUpdate.SetCheck(false);//��������� �������������� ����������
	ActivityExe firstPeriod; //��������� ���������� �� ������� �������, ����� ����� �������� ����������� �� ����
	firstPeriod.sumActs=0; firstPeriod.sumTime=0; firstPeriod.usefulActs=0; firstPeriod.usefulTime=0;
	ActivityExe secondPeriod; //��������� ���������� �� ������� �������, ����� ����� �������� ����������� �� ����
	secondPeriod.sumActs=0; secondPeriod.sumTime=0; secondPeriod.usefulActs=0; secondPeriod.usefulTime=0;

	//�������� ������ � �������� ���������
	CChartLineSerie   *pLinePeriod1, *pLinePeriod2;
	CChartPointsSerie *pPntsPeriod1, *pPntsPeriod2;
	chart.RemoveAllSeries(); //������ ���������� ������
	CChartDateTimeAxis* axis1 = chart.CreateDateTimeAxis(CChartCtrl::BottomAxis);
	axis1->SetTickLabelFormat(false, _T("%b %Y"));
	chart.GetBottomAxis()->SetAutomatic(true);
	chart.GetLeftAxis()->SetAutomatic(true);
	chart.GetBottomAxis()->GetLabel()->SetText("Month");

	chart.GetLeftAxis()->GetLabel()->SetText(radioTime.GetCheck() ? "Hours" : "Actions");
	pLinePeriod1 = chart.CreateLineSerie();
	pLinePeriod1->SetWidth(2);
	pPntsPeriod1 = chart.CreatePointsSerie();
	pPntsPeriod1->SetPointType(CChartPointsSerie::ptTriangle);
	pPntsPeriod1->SetPointSize(11,11);
	pPntsPeriod1->SetColor(pLinePeriod1->GetColor());

	CChartDateTimeAxis* axis2;
	if (saDates2.GetSize())
	{
		axis2 = chart.CreateDateTimeAxis(CChartCtrl::TopAxis);
		axis2->SetTickLabelFormat(false, _T("%b %Y"));
		chart.GetTopAxis()->SetAutomatic(true);
		pLinePeriod2 = chart.CreateLineSerie(1);
		pLinePeriod2->SetWidth(2);
		pPntsPeriod2 = chart.CreatePointsSerie(1);
		pPntsPeriod2->SetPointType(CChartPointsSerie::ptEllipse);
		pPntsPeriod2->SetPointSize(10,10);
		pPntsPeriod2->SetColor(pLinePeriod2->GetColor());
	}

	table_period.DeleteAllItems();
	char ch[100];
	for (int ii=0; ii<saDates1.GetSize(); ii++)
	{
		char fname[2048];
		sprintf_s(fname, "%sactiv_user_%s.am", path_actuser.c_str(), saDates1[ii]);
		activ aDayActiv;
		float monTime=0; float monUsefulTime=0; int monActs=0; int monUsefulActs=0;
		if (!statsF.LoadFileMonth(fname, aDayActiv, monTime, monUsefulTime, monActs, monUsefulActs))
		{
			CString str;
			str.LoadString(trif.GetIds(IDS_STRING1665));//�� ������� ��������� ���������� ��� ���
			AfxMessageBox(str + saDates1[ii]);
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			return;
		}
		int row=table_period.InsertItem(0, saDates1[ii]);

		double chartValue = radioTime.GetCheck() ? monUsefulTime/60/60/1000 : monUsefulActs;
		COleDateTime oleDate(atoi(saDates1[ii].Left(4)), atoi(saDates1[ii].Mid(5)), 
			1, 0, 0, 0);
		pLinePeriod1->AddPoint(oleDate, chartValue);
		pPntsPeriod1->AddPoint(oleDate, chartValue);
		chart.RefreshCtrl();
		char ch_ii[100];
		sprintf_s(ch_ii, "%s/%s", saDates1[ii], saDates1[ii]);

 		firstPeriod.sumActs+=monActs; firstPeriod.sumTime+=monTime; 
 		firstPeriod.usefulActs+=monUsefulActs; firstPeriod.usefulTime+=monUsefulTime;
		float sec =monUsefulTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = monTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", monUsefulActs);
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", monActs);
		table_period.SetItemText(row, 4, ch);

	}
	CString str; 
	str.LoadString(trif.GetIds(IDS_STRING1657));//�������
	int row=table_period.InsertItem(0, str);
	float sec = firstPeriod.usefulTime/1000/saDates1.GetSize();
	FormatSeconds(ch, sec);
	table_period.SetItemText(row, 1, ch);
	sec = firstPeriod.sumTime/1000/saDates1.GetSize();
	FormatSeconds(ch, sec);
	table_period.SetItemText(row, 2, ch);
	sprintf_s(ch, "%d", firstPeriod.usefulActs/saDates1.GetSize());
	table_period.SetItemText(row, 3, ch);
	sprintf_s(ch, "%d", firstPeriod.sumActs/saDates1.GetSize());
	table_period.SetItemText(row, 4, ch);
	table_period.InsertItem(0, "");

	for (int ii=0; ii<saDates2.GetSize(); ii++)
	{
		char fname[2048];
		sprintf_s(fname, "%sactiv_user_%s.am", path_actuser.c_str(), saDates2[ii]);
		activ aDayActiv;
		float monTime=0; float monUsefulTime=0; int monActs=0; int monUsefulActs=0;
		if (!statsF.LoadFileMonth(fname, aDayActiv, monTime, monUsefulTime, monActs, monUsefulActs))
		{
			CString str;
			str.LoadString(trif.GetIds(IDS_STRING1665));
			AfxMessageBox(str + saDates2[ii]);
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			return;
		}
		int row=table_period.InsertItem(0, saDates2[ii]);

		double chartValue = radioTime.GetCheck() ? monUsefulTime/60/60/1000 : monUsefulActs;
		COleDateTime oleDate(atoi(saDates2[ii].Left(4)), atoi(saDates2[ii].Mid(5)), 
			1, 0, 0, 0);
		pLinePeriod2->AddPoint(oleDate, chartValue);
		pPntsPeriod2->AddPoint(oleDate, chartValue);
		chart.RefreshCtrl();

		secondPeriod.sumActs+=monActs; secondPeriod.sumTime+=monTime; 
		secondPeriod.usefulActs+=monUsefulActs; secondPeriod.usefulTime+=monUsefulTime;
		float sec =monUsefulTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 1, ch);
		sec = monTime/1000;
		FormatSeconds(ch, sec);
		table_period.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", monUsefulActs);
		table_period.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", monActs);
		table_period.SetItemText(row, 4, ch);
	}
	str.LoadString(trif.GetIds(IDS_STRING1657));//�������
	row=table_period.InsertItem(0, str);
	sec = secondPeriod.usefulTime/1000/saDates2.GetSize();
	FormatSeconds(ch, sec);
	table_period.SetItemText(row, 1, ch);
	sec = secondPeriod.sumTime/1000/saDates2.GetSize();
	FormatSeconds(ch, sec);
	table_period.SetItemText(row, 2, ch);
	sprintf_s(ch, "%d", secondPeriod.usefulActs/saDates2.GetSize());
	table_period.SetItemText(row, 3, ch);
	sprintf_s(ch, "%d", secondPeriod.sumActs/saDates2.GetSize());
	table_period.SetItemText(row, 4, ch);

	str.LoadString(trif.GetIds(IDS_STRING1659));//�������
	row = table_period.InsertItem(0, str);
	double grow = (firstPeriod.usefulTime/saDates1.GetSize())/(secondPeriod.usefulTime/saDates2.GetSize())*100.0 - 100.0;
	sprintf_s(ch, "%.2f%%", grow);
	table_period.SetItemText(row, 1, ch);
	grow = (firstPeriod.sumTime/saDates1.GetSize())/(secondPeriod.sumTime/saDates2.GetSize())*100.0 - 100.0;
	sprintf_s(ch, "%.2f%%", grow);
	table_period.SetItemText(row, 2, ch);
	grow = ((double)firstPeriod.usefulActs/saDates1.GetSize())/((double)secondPeriod.usefulActs/saDates2.GetSize())*100.0 - 100.0;
	sprintf_s(ch, "%.2f%%", grow);
	table_period.SetItemText(row, 3, ch);
	grow = ((double)firstPeriod.sumActs/saDates1.GetSize())/((double)secondPeriod.sumActs/saDates2.GetSize())*100.0 - 100.0;
	sprintf_s(ch, "%.2f%%", grow);
	table_period.SetItemText(row, 4, ch);

	table_period.InsertItem(0, "..");

	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

void CEactivityDlg::OnReportsUsefulActionsFromLast5WorkingDays()
{
	CalculateAverageUsefulParameter(5);
}

void CEactivityDlg::OnBnClickedRadio1()
{
	OnOk2();
}

void CEactivityDlg::OnReportsUsefulParameterFromSelectedPeriod()
{
	CReportSelectedPeriod report;
	report.path_actuser=path_actuser;
	POSITION pos = table_period.GetFirstSelectedItemPosition();
	if (!pos)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1663));
		return;
	}
	CString date = table_period.GetItemText((int)pos-1, 0);
	while (pos)
	{
		int nextItem = table_period.GetNextSelectedItem(pos);
		TRACE(_T("Item %d was selected!\n"), nextItem);
		date = table_period.GetItemText(nextItem, 0);
		report.saDates.Add(date);
	}
	if (report.DoModal()!=IDOK)
		return;
	if (!report.saDates.GetSize() || !report.saDates2.GetSize())
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1661));
		return;
	}
	switch (report.saDates[0].GetLength())
	{
	case DAY:
		CompareTwoPeriodsOfDays(report.saDates, report.saDates2, radioTime.GetCheck());
		break;
	case MON:
		CompareTwoPeriodsOfMons(report.saDates, report.saDates2);
		break;
	}
}

void CEactivityDlg::OnCompare2periods()
{
	OnReportsUsefulParameterFromSelectedPeriod();
}

void CEactivityDlg::OnCompareWithBest5Days()
{
	POSITION pos = table_period.GetFirstSelectedItemPosition();
	if (!pos)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1663));
		return;
	}
	CString date = table_period.GetItemText((int)pos-1, 0);
	CStringArray saDates;
	while (pos)
	{
		int nextItem = table_period.GetNextSelectedItem(pos);
		TRACE(_T("Item %d was selected!\n"), nextItem);
		date = table_period.GetItemText(nextItem, 0);
		saDates.Add(date);
	}

	CStringArray saDates2;
	CTime ct=CTime::GetCurrentTime();
	ct-=60*60*24*7;
	while (ct.GetDayOfWeek()!=2)
	{
		ct-=60*60*24;
	}
	for (int ii=1; ii<=7; ii++)
	{
		date.Format("%d_%02d_%02d", ct.GetYear(), ct.GetMonth(), ct.GetDay());
		saDates2.Add(date);
		ct+=60*60*24;
	}
	CString res = CompareTwoPeriodsOfDays(saDates, saDates2, radioTime.GetCheck(), 2);
//	if (res!="")
//		SendMailMessage("smtp.gmail.com", 587, "silencenotif@gmail.com", 
//			"densaf.ace@gmail.com", "densaf.ace@gmail.com", "GhjcajhyZ88", res, "TablePeriod");

}

void CEactivityDlg::OnReportOnePeriod()
{
	CReportOption dialogReport;
	dialogReport.timeOrActions = radioTime.GetCheck();
	if (dialogReport.DoModal()!=IDOK)
		return;
	checkAutoUpdate.SetCheck(false);//��������� �������������� ����������
	if (dialogReport.useLastDays>0)
	{
		CalculateAverageUsefulParameter(dialogReport.useLastDays, 
			dialogReport.thresholdHoliday);
	} else {
		CStringArray emptyDates;
		CompareTwoPeriodsOfDays(dialogReport.saDates, emptyDates, 
			dialogReport.accentParameter);
	}
}


void CEactivityDlg::OnReportTwoPeriods()
{
	CReportTwoPeriods dialogReport;
	dialogReport.timeOrActions = radioTime.GetCheck();
	if (dialogReport.DoModal()!=IDOK)
		return;
	checkAutoUpdate.SetCheck(false);//��������� �������������� ����������
	CompareTwoPeriodsOfDays(dialogReport.saDates1, dialogReport.saDates2, 
		dialogReport.accentParameter, 0, dialogReport.thresholdHoliday);

}