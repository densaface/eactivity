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

bool inited_pPage5=false;

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
	SelMonOrCurMon=false;
	SelDayOrCurDay=false;
	forTimeNoActiv=GetTickCount();	
}

void CEactivityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEactivityDlg)
	DDX_Control(pDX, IDC_COMBO2, combo_group);
	DDX_Control(pDX, IDC_SPIN2, spin_edit);
	DDX_Control(pDX, IDC_EDITr17, edit_capts);
	DDX_Control(pDX, IDC_LIST3, list_days);
	DDX_Control(pDX, IDC_COMBO1, combo_sort);
	DDX_Control(pDX, IDC_LIST2, top_table);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MSCHART1, chart);
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
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickListCurDay)
	ON_COMMAND(ID_ACTIVITY_SETKOEFEXE, OnActivitySetkoefeExe)
	ON_EN_CHANGE(IDC_EDITr17, OnChangeEDITcapts)
	ON_COMMAND(ID_ACTIVITY_EXE, OnActivityShowAllCapts)
	ON_MESSAGE(WM_MYICONNOTIFY,OnIcon)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CEactivityDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CEactivityDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CEactivityDlg::OnSave)
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
	TRACE(_T("__SetHook__(%d)\n"), 0);
	CDialog::OnInitDialog();
	SetToTray(IDR_MAINFRAME);

	SetHook=0;
	char date[10];
	SYSTEMTIME st;
	GetLocalTime(&st);
	GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "hh", date, 2);
	curHour=st.wHour;

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if (trif.GetNumLan()==1)
	{
		menu_cur_day.LoadMenu(IDR_Activity_RU);
	} else {
//		menu_cur_day.LoadMenu(IDR_Activity_EN);
		menu_cur_day.LoadMenu(IDR_Activity_RU);
	}
	char ch[300];
	sprintf_s(ch, "%d", AfxGetApp()->GetProfileInt("App", "CounShowCapt", 2));
	edit_capts.SetWindowText(ch);
	tool_tip.Create(this, TTS_ALWAYSTIP);
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1583));
	tool_tip.AddTool(GetDlgItem(IDC_EDITr17), str);
	tool_tip.AddTool(GetDlgItem(IDC_SPIN2), str);
	spin_edit.SetBuddy(&edit_capts);
	spin_edit.SetRange(0,9999);

	//list_activ.SetStile(LVS_REPORT | LVS_OWNERDRAWFIXED /*|LVS_EDITLABELS*/);
	top_table.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | top_table.GetExtendedStyle());
	top_table.InsertColumn(0, "exe");
	top_table.InsertColumn(1, "Caption");
	top_table.InsertColumn(2, "useful time");
	top_table.InsertColumn(3, "total time");
	top_table.InsertColumn(4, "acts");
	top_table.InsertColumn(5, "points");
	top_table.InsertColumn(6, "full exe");
	top_table.SetColumnWidth(0,80);
	top_table.SetColumnWidth(1,200);
	top_table.SetColumnWidth(2,80);
	top_table.SetColumnWidth(3,80);
	top_table.SetColumnWidth(4,60);
	top_table.SetColumnWidth(5,60);
	top_table.SetColumnWidth(6,0);

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
	combo_group.SetCurSel(AfxGetApp()->GetProfileInt("App", "type_group_activ", 0));

	str.LoadString(trif.GetIds(IDS_STRING1613));
	GetDlgItem(IDC_BUTTON1)->SetWindowText(str);

	list_days.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | list_days.GetExtendedStyle());
	list_days.InsertColumn(0, "date");
	list_days.InsertColumn(1, "useful time");
	list_days.InsertColumn(2, "total time");
	list_days.InsertColumn(3, "acts");
	list_days.InsertColumn(4, "points");
	list_days.SetColumnWidth(0,80);
	list_days.SetColumnWidth(1,80);
	list_days.SetColumnWidth(2,80);
	list_days.SetColumnWidth(3,80);
	list_days.SetColumnWidth(4,100);

	path_exe=cpu.GetAppNameFromHandle2(GetSafeHwnd()).c_str();
	path_exe=path_exe.Left(path_exe.ReverseFind('\\'));
	path_actuser = path_exe+"\\activity\\";
	if (!trif.IsDirExist(path_actuser.c_str()))
	{
		CreateDirectory(path_actuser.c_str(), NULL);
	}

	LoadRules();
	LoadCurDay();
	SelDayOrCurDay=false;
	UpdatePoints();
//	SumDayStatForCurDay();

	LoadCurMonth();
	LoadYear();
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		UpdateDownTableViewByHours(SelDayOrCurDay ? aSelDayViewExe : ActivExeToday);
		break;
	case BYDAYS:
		UpdateDownTable(aCurMon);
		break;
	case BYMONTHS:
		UpdateDownTable(aCurYear);
		break;
	}

#ifndef _DEBUG
	SetTimer(1500, 500, 0);
	SetTimer(2500, 5000, 0);
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
	SelDayOrCurDay=false;
	UpdatePoints();
}

bool CompareActs(Activity Activity_1, Activity Activity_2)
{
	return Activity_1.num_acts>Activity_2.num_acts;
}
bool CompareTimes(Activity Activity_1, Activity Activity_2)
{
	return Activity_1.sumTime>Activity_2.sumTime;
}
bool ComparePoints(Activity Activity_1, Activity Activity_2)
{
	return Activity_1.points>Activity_2.points;
}

bool CompareActs2(ActivityExe Activity_1, ActivityExe Activity_2)
{
	return Activity_1.num_acts>Activity_2.num_acts;
}
bool CompareTimes2(ActivityExe Activity_1, ActivityExe Activity_2)
{
	return Activity_1.sumTime>Activity_2.sumTime;
}
bool ComparePoints2(ActivityExe Activity_1, ActivityExe Activity_2)
{
	return Activity_1.points>Activity_2.points;
}

// UpdateTopTable - ���������� ������� �������
// 	int &sumTime //��������� ����� ��� ����� ���/�����������
//	��� ����������� https://docs.google.com/document/d/1zG2kZiDdtXNvLGwjBw66F6RK8lBxK4HoGTgBFA48PGg/edit
// int onlyOneHour - �� ��������� -1, ���� ������� ������ �����, �� ��������� 
//		���������� ������ ��� ���������� ����, ����� ��� ����� ��������� �����
void CEactivityDlg::UpdateTopTable(activ &forLoad1, activ_exe &forLoad2, 
					float &sumTime, float &sumUsefulTime, int &sumAct, 
					int &sumPoints, int onlyOneHour) 
{
	//������� ���������� � ������ ��� ��������� �� �����
	activ activSumHours;
	activ_exe activExeSumHours;
	for (activ::iterator ia=forLoad1.begin(); ia!=forLoad1.end(); ia++)
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
			(*iter).second.points     +=ia->second.points;
			(*iter).second.num_acts   +=ia->second.num_acts;
			(*iter).second.sumTime    +=ia->second.sumTime;
			(*iter).second.usefulTime +=ia->second.usefulTime;
		}
	}
	for (activ_exe::iterator ia=forLoad2.begin(); ia!=forLoad2.end(); ia++)
	{
		string exe = ia->first;
		if (onlyOneHour>-1 && atoi(exe.c_str())!=onlyOneHour)
			continue; //����������� ���������� ������ ��� ���������� ����, ������ ���� ���������
		(*ia).second.points     = GetPointsFromExe((*ia).second.exe, activSumHours);
		(*ia).second.usefulTime = GetTimeFromExe ((*ia).second.exe, activSumHours);
		exe.erase(0, exe.find('\t')+1); //������� ���
		activ_exe::iterator iter=activExeSumHours.find(exe);
		if (iter==activExeSumHours.end())
		{
			activExeSumHours[exe]=ia->second;
		} else {
			(*iter).second.points     +=ia->second.points;
			(*iter).second.num_acts   +=ia->second.num_acts;
			(*iter).second.sumTime    +=ia->second.sumTime;
			(*iter).second.usefulTime +=ia->second.usefulTime;
		}
	}

	//������������ ������� �������� - ����� (��� ���������)
	vector <ActivityExe> vect_sort_points;
	for (activ_exe::iterator ia=activExeSumHours.begin(); ia!=activExeSumHours.end(); ia++)
	{
		if (showAllCaptsForExe.length() && showAllCaptsForExe!=(*ia).second.exe)
			continue;
		(*ia).second.points     = GetPointsFromExe((*ia).second.exe, activSumHours);
		(*ia).second.usefulTime = GetTimeFromExe ((*ia).second.exe, activSumHours);
		sumUsefulTime += (*ia).second.usefulTime;
		sumPoints+=(*ia).second.points;
		vect_sort_points.push_back((*ia).second);
	}
	switch(combo_sort.GetCurSel())
	{
	case 0:
		break;
	case 1:
		sort(vect_sort_points.begin(), vect_sort_points.end(), ComparePoints2);
		break;
	case 2:
		sort(vect_sort_points.begin(), vect_sort_points.end(), CompareTimes2);
		break;
	case 3:
		sort(vect_sort_points.begin(), vect_sort_points.end(), CompareActs2);
		break;
	}

	top_table.DeleteAllItems();
	for (vector<ActivityExe>::iterator iv=vect_sort_points.begin(); iv!=vect_sort_points.end(); ++iv)
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
		int ii=top_table.InsertItem(top_table.GetItemCount(), shortExe.c_str());
	
//		����������� ������ ���������������� �������
		char ch[100];
		float sec=(*iv).sumTime/1000;
		FormatSeconds(ch, sec);
		top_table.SetItemText(ii, 3, ch);
		sumTime+=(*iv).sumTime;

		//����������� ��������� �������
		sec=(*iv).usefulTime/1000;
		FormatSeconds(ch, sec);
		//sprintf_s(ch, "%d", (int)((*iv).sumTime/1000));
		top_table.SetItemText(ii, 2, ch);
		//sumTime+=(*iv).sumTime;

		sprintf_s(ch, "%d", (*iv).num_acts);
		top_table.SetItemText(ii, 4, ch);
		sumAct+=(*iv).num_acts;

		sprintf_s(ch, "%d", (*iv).points);
		top_table.SetItemText(ii, 5, (*iv).points ? ch : "-");

		top_table.SetItemText(ii, 6, (*iv).exe.c_str());

		//����� �� ��������� ������� �������� ���� ������ ������� ����������� � ������� ���������
		int sumCapts=0;
		AddExeCaptToTable((*iv).exe, activSumHours, sumCapts);
		CString str;
		str.LoadString(trif.GetIds(IDS_STRING1589));
		if (trif.GetNumLan()==1)
			 sprintf_s(ch, str, sumCapts, trif.getEnd(sumCapts).c_str());
		else sprintf_s(ch, str, sumCapts);
		top_table.SetItemText(ii, 1, ch);
	}
}

rulSpis::iterator CEactivityDlg::ownFind(string capt) 
{
	for (rulSpis::iterator iter=RULES.begin(); iter!=RULES.end(); iter++)
	{
		if ((*iter).second.typeRule!=2)
			continue;
		//string debs=(*iter).second.capt;
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

int CEactivityDlg::GetPointsFromExe(string exe, activ &forLoad1) 
{
	int sumpoints=0;
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
				(*ia).second.points=(int)((*iter).second.koef * (*ia).second.num_acts);
				sumpoints+=(*ia).second.points;
			}
		}
	}
	return sumpoints;
}

// AddExeCaptToTable
//	������������ ������� ����� ��������� ������� �� ���������
void CEactivityDlg::AddExeCaptToTable(string exe, activ &forLoad1, int &sumCapt) 
{
	vector <Activity> vect_sort_points;
	//__SetHook__(FALSE);
	//TRACE("AddExeCaptToTable %s \n", exe.c_str());
	for (activ::iterator ia=forLoad1.begin(); ia!=forLoad1.end(); ia++)
	{
		if ((*ia).second.exe==exe)
		{
			sumCapt++;
			vect_sort_points.push_back((*ia).second);
		}
	}
	switch(combo_sort.GetCurSel())
	{
	case 0:
		break;
	case 1:
		sort(vect_sort_points.begin(), vect_sort_points.end(), ComparePoints);
		break;
	case 2:
		sort(vect_sort_points.begin(), vect_sort_points.end(), CompareTimes);
		break;
	case 3:
		sort(vect_sort_points.begin(), vect_sort_points.end(), CompareActs);
		break;
	}

	int coun=0; 
	CString str;
	edit_capts.GetWindowText(str);
	int MaxCoun=atoi(str);
	for (vector<Activity>::iterator iv=vect_sort_points.begin(); iv!=vect_sort_points.end(); ++iv)
	{
		if (!showAllCaptsForExe.length() && coun==MaxCoun)
			break;
		int ii=top_table.InsertItem(top_table.GetItemCount(), "");
		
		top_table.SetItemText(ii, 1, (*iv).capt.c_str());

		char ch[100];
		float sec=(*iv).sumTime/1000;
		FormatSeconds(ch, sec);
		top_table.SetItemText(ii, 3, ch);
		sec=(*iv).usefulTime/1000;
		FormatSeconds(ch, sec);
		top_table.SetItemText(ii, 2, sec ? ch : "-");

		sprintf_s(ch, "%d", (*iv).num_acts);
		top_table.SetItemText(ii, 4, ch);
		sprintf_s(ch, "%d", (*iv).points);
		top_table.SetItemText(ii, 5, (*iv).points ? ch : "-" );
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
	//���������� � ������� �� ���������
	AddToOnlyExe(exe, 1, 0);
}

void CEactivityDlg::AddToExeCapt(char *capt, string &exe, HWND HChil, HWND hwMain, 
								 int num_acts, float sumTime) 
{
	char chi[512];
	sprintf_s(chi, "%d\t", curHour);
	string exeCapt = chi + exe + '\t' + capt;
	activ::iterator it_activ = ActivToday.find(exeCapt);
	if (it_activ==ActivToday.end())
	{
		Activity new_zap;
		new_zap.num_acts=num_acts;
		new_zap.points=0;
		new_zap.sumTime=sumTime;
		new_zap.usefulTime=0;
		new_zap.hour=curHour;
		new_zap.capt=capt;
		new_zap.exe=exe;
		new_zap.hwChil=HChil;
		new_zap.hwMain=hwMain;
		ActivToday[exeCapt]=new_zap;
		TRACE("AddToExeCapt �������� ����� ������ sumTime=%.2f ��� %s\n", sumTime, exeCapt.c_str());
	} else {
		(*it_activ).second.num_acts += num_acts;
		(*it_activ).second.sumTime  += sumTime;
		TRACE("AddToExeCapt �������� ������������ ������ sumTime=%.2f ��� %s\n", (*it_activ).second.sumTime, exeCapt.c_str());
	}
}

void CEactivityDlg::AddToOnlyExe(string &exe, int num_acts, float sumTime) 
{
	activ_exe::iterator iter=ActivExeToday.find(exe);
	if (iter==ActivExeToday.end())
	{
		ActivityExe new_zap;
		new_zap.num_acts=num_acts;
		new_zap.points=0;
		new_zap.sumTime=sumTime;
		new_zap.usefulTime=0;
		new_zap.hour=curHour;
		new_zap.exe=exe;
		ActivExeToday[exe]=new_zap;
	} else {
		(*iter).second.num_acts+=num_acts;
		(*iter).second.sumTime+=sumTime;
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
			AddToOnlyExe(str_exe, 0, (float)(GetTickCount()-curTime));
			curTime=GetTickCount();
			static bool perekl=1;//������������� � eactivity - ��������� ����������, ����� ���
			if (hwMain==AfxGetMainWnd()->m_hWnd)
			{
				if (perekl)
				{
					perekl=false;
					SelDayOrCurDay=false;
					UpdatePoints();
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
	}
	CDialog::OnTimer(nIDEvent);
}

// ��������, ���� �� �� ��� �� ��������, �� ������� � ��������� �������
// SumDayStatForCurDay - ������� ������������ ���������� �� ����� �������� ��� � ������ ����������� 
//			� �������� � ������� �������� ���, ���������� ��� ������� ����������
//		*** ����� �� ����� �� ������ ��� ���������� ���������� �� ��� ?
// void CEactivityDlg::SumDayStatForCurDay() 
// {
// 	string skey=curDayFileName.substr(curDayFileName.length()-12, 10);
// 	activ::iterator iter=aCurMon.find(skey);
// 	Activity tmpActiv;
// 	tmpActiv.num_acts=0;
// 	tmpActiv.sumTime=0;
// 	tmpActiv.usefulTime=0;
// 	tmpActiv.points=0;
// 	for (activ_exe::iterator ia=ActivExeToday.begin(); ia!=ActivExeToday.end(); ia++)
// 	{
// 		tmpActiv.points     += ((*ia).second.points);
// 		tmpActiv.num_acts   += ((*ia).second.num_acts);
// 		tmpActiv.sumTime    += ((*ia).second.sumTime);
// 		tmpActiv.usefulTime += ((*ia).second.usefulTime);
// 	}
// 	aCurMon[skey]=tmpActiv;
// }
void CEactivityDlg::SumDayStat(activ &forLoad1, string fname, float &sumTime, int &sumAct, int &sumPoints) 
{
	activ::iterator iter=forLoad1.find(fname.substr(fname.length()-12, 10));
	if (iter!=forLoad1.end())
		return; //��� ��������� ���������� �� ���������

	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return;
	Activity tmpActiv;
	tmpActiv.num_acts=0;
	tmpActiv.sumTime=0;
	tmpActiv.usefulTime=0;
	tmpActiv.points=0;
	tmpActiv.capt="";
	tmpActiv.exe="";
	tmpActiv.hwChil=0;
	tmpActiv.hwMain=0;

	char ch[1024];
	ifstr.getline(ch, 1024);
	while (ifstr)
	{
		void* tmpint;
		ifstr>>tmpint;
		ifstr.get();
		ifstr>>tmpint;
		ifstr.get();
		if (!ifstr)
			break;
		int tmpint2;
		ifstr>>tmpint2;
		tmpActiv.num_acts+=tmpint2;
		ifstr.get();
		ifstr>>tmpint2;
		tmpActiv.points+=tmpint2;
		ifstr.get();
		ifstr>>tmpint2;
		tmpActiv.sumTime+=tmpint2;
		ifstr.get();
		ifstr.getline(ch, 1024);
		if (!ifstr)
			break;
	}
	ifstr.close();
	sumTime+=tmpActiv.sumTime;
	sumAct+=tmpActiv.num_acts;
	sumPoints+=tmpActiv.points;
	forLoad1[fname.substr(fname.length()-12, 10)]=tmpActiv;
}

//���������� ������� ����������, ���� ��� �� ���� � ����� ���������� �� �����
void CEactivityDlg::LoadMonthFromStatDays(activ &forLoad1, string mon, float &sumTime, int &sumAct, int &sumPoints) 
{
	WIN32_FIND_DATA FFData;
	string for_find=path_actuser+mon+"*.a";
	HANDLE hFind = FindFirstFile(for_find.c_str(), &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			SumDayStat(forLoad1, path_actuser+FFData.cFileName, sumTime, sumAct, sumPoints);
		} while(FindNextFile(hFind, &FFData));
	}
}

bool CEactivityDlg::LoadFileMonth(string fname, activ &forLoad1, float &sumTime, int &sumActs, int &sumPoints)
{
	ifstream ifstr(fname.c_str());
	if (ifstr)
	{
		char ch[1024];
		ifstr.getline(ch, 100);
		
		Activity tmpForLoad;
		tmpForLoad.capt="";
		tmpForLoad.exe="";
		tmpForLoad.hwChil=0;
		tmpForLoad.hwMain=0;
		while (ifstr)
		{
			string sdate;
			ifstr>>sdate;
			ifstr.get();
			ifstr>>tmpForLoad.num_acts;
			sumActs+=tmpForLoad.num_acts;
			ifstr.get();
			if (!ifstr)
				break;
			ifstr>>tmpForLoad.points;
			sumPoints+=tmpForLoad.points;
			ifstr>>tmpForLoad.sumTime;
			sumTime+=tmpForLoad.sumTime;
			if (strcmp(ch, "ver=0.1")!=0) {
				//������ � ������ ������ �� ����������� �������� �����
				ifstr>>tmpForLoad.usefulTime;
			}
			forLoad1[sdate]=tmpForLoad;
			if (!ifstr)
				break;
		}
		ifstr.close();
	}
	LoadMonthFromStatDays(forLoad1, fname.substr(fname.length()-21, 18), sumTime, sumActs, sumPoints);
	return true;
}
void CEactivityDlg::LoadCurMonth() 
{
	char date[27];
	SYSTEMTIME st;
	GetLocalTime(&st);
	GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy_MM.am", date, 25);
	curMonFileName=date;

	float sumTime=0;
	int sumActs=0, sumPoints=0;
	string strf=path_actuser+curMonFileName;
	WriteJournal("LoadCurMonth from %s", strf);
	LoadFileMonth(strf, aCurMon, sumTime, sumActs, sumPoints);
}

// UpdateDownTableViewByHours - ����� ��������� ���������� � ������ ������� � 
//				��������� ���������� � ������ �������
//		��� ���������� ���������� ���������� ��� �������� aCurMon ��� �������� aSelMon ������:
//				- ��� �������� ��������� ����������� ���������� � ������� LoadFileMonth
//					�� �����, ��������, activ_user_2015_11.am
//				- ���������� SaveCurMonth ���������� � ���� �������, ��� ������, 
//					� ��� ����� �������� ������ � �������
//				- �������� ��� �������� ��������� � SumDayStatForCurDay (������ ����� ����� ��������)
//				- �������� � ���� ������� UpdateDownTableViewByHours ���������� � ��� aCurMon � aSelMon
//					������ ��� ��� ��������� ���������������� ������������� ����� ���������� 
//					�������� ����� � �������� ��������, ������� �������� ����� �� ������
//				- �������� ���������� � ���� ������� (������ ��������): ��� ������� ����� �� ������ 
//					������� � ��� ��������� ������� �����.
void CEactivityDlg::UpdateDownTableViewByHours(activ_exe &CurView) 
{
	int ii=0;
	char ch[100];
	string date;
	if (SelDayOrCurDay)
	{
		POSITION pos=list_days.GetFirstSelectedItemPosition();
		int sel=(int)pos-1;
		// ����� ��������� ��� ���������� ���� � ������� ������ �������� ��� ������ ���� �����������
		date = list_days.GetItemText(sel, 0);
	} else {
		// ���� ������������ ���
		date=curDayFileName.substr(curDayFileName.length()-12, 10);
	}
	list_days.DeleteAllItems();
	float sumUsefulSec=0, sumSec=0;
	int sumActs=0, sumPoints=0;
	for (int ii = 0; ii<24; ii++)
	{
		float sumTime=0;
		float usefulTime=0;
		int num_acts=0;
		int points=0;
		for (activ_exe::iterator iter=CurView.begin(); iter!=CurView.end(); iter++)
		{
			if ((*iter).second.hour!=ii)
				continue;
			usefulTime += (*iter).second.usefulTime;
			sumTime    += (*iter).second.sumTime;
			num_acts   += (*iter).second.num_acts;
			points     += (*iter).second.points;
		}
		if (sumTime>0.0 || num_acts>0)
		{
			char ch[100];
			int row = list_days.GetItemCount();
			sprintf_s(ch, "%d", ii);
			row = list_days.InsertItem(0, ch);

			float sec = usefulTime/1000;
			FormatSeconds(ch, sec);
			list_days.SetItemText(row, 1, ch);

			sec = sumTime/1000;
			FormatSeconds(ch, sec);
			list_days.SetItemText(row, 2, ch);

			sprintf_s(ch, "%d", num_acts);
			list_days.SetItemText(row, 3, ch);
			sprintf_s(ch, "%d", points);
			list_days.SetItemText(row, 4, ch);

			sumUsefulSec += usefulTime;
			sumSec       += sumTime;
			sumActs      += num_acts;
			sumPoints    += points;
		}
	}
	if (combo_group.GetCurSel()<BYMONTHS)
		list_days.InsertItem(0, "..");//��� �������� �� ������� ����
	CString str;
	char ch2[100];
	char ch3[100];
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		str.LoadString(trif.GetIds(SelDayOrCurDay ? IDS_STRING1595 : IDS_STRING1637));
		ASSERT(date.length()==10);
		//��������� ���������� ��� ���� ���, ����������� �������� ����������
		if (date.length()==10)
		{
			if (SelMonOrCurMon)
			{
				aSelMon[date].usefulTime=sumUsefulSec;
				aSelMon[date].sumTime=sumSec;
				aSelMon[date].num_acts=sumActs;
				aSelMon[date].points=sumPoints;
			} else {
				aCurMon[date].usefulTime=sumUsefulSec;
				aCurMon[date].sumTime=sumSec;
				aCurMon[date].num_acts=sumActs;
				aCurMon[date].points=sumPoints;
			}
		}
		break;
	default:
		//������ ���� ������ ��������� ������������� ��� ���� �������
		AfxMessageBox("Wrong view period");
	}
	FormatSeconds(ch2, sumSec/1000);
	FormatSeconds(ch3, sumUsefulSec/1000);
	if (SelMonOrCurMon || SelDayOrCurDay)
	{
		sprintf_s(ch, str, date.c_str(),
			ch3, ch2, sumActs, sumPoints);
	} else {
		sprintf_s(ch, str, ch3, ch2, sumActs, sumPoints);
	}
	GetDlgItem(IDC_STATIC_cur_mon)->SetWindowText(ch);
}

// ����� ���������� � ������ ������� � ��������� ���������� � ������ �������
void CEactivityDlg::UpdateDownTable(activ &CurView) 
{
	int ii=0;
	char ch[100];
	list_days.DeleteAllItems();
	float sumUsefulSec=0, sumSec=0;
	int sumActs=0, sumPoints=0;
	for (activ::iterator iter=CurView.begin(); iter!=CurView.end(); iter++)
	{
		int row = list_days.GetItemCount();
		row = list_days.InsertItem(0, (*iter).first.c_str());
		float sec=(*iter).second.usefulTime/1000;
		sumUsefulSec+=sec;
		FormatSeconds(ch, sec);
		list_days.SetItemText(row, 1, ch);
		sec=(*iter).second.sumTime/1000;
		sumSec+=sec;
		FormatSeconds(ch, sec);
		list_days.SetItemText(row, 2, ch);
		sprintf_s(ch, "%d", (*iter).second.num_acts);
		sumActs+=(*iter).second.num_acts;
		list_days.SetItemText(row, 3, ch);
		sprintf_s(ch, "%d", (*iter).second.points);
		sumPoints+=(*iter).second.points;
		list_days.SetItemText(row, 4, ch);
	}
	if (combo_group.GetCurSel()<BYMONTHS)
		list_days.InsertItem(0, "..");//��� �������� �� ������� ����
	CString str;
	char ch2[100];
	char ch3[100];
	string date;
	if (SelMonOrCurMon)
		date=list_days.GetItemCount() ? list_days.GetItemText(1, 0).Left(7) : "";
	else date=curMonFileName.substr(11, 7);
	switch (combo_group.GetCurSel())
	{
	case BYDAYS:
		str.LoadString(trif.GetIds(SelMonOrCurMon ? IDS_STRING1595 : IDS_STRING1591));
		ASSERT(date.length()==7);
		//��������� ���������� ��� ���� ������, ����������� �������� ����������
		aCurYear[date].usefulTime=sumUsefulSec*1000;
		aCurYear[date].sumTime=sumSec*1000;
		aCurYear[date].num_acts=sumActs;
		aCurYear[date].points=sumPoints;
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
	if (SelMonOrCurMon)
	{
		sprintf_s(ch, str, date.c_str(),
			ch3, ch2, sumActs, sumPoints);
	} else {
		sprintf_s(ch, str, ch3, ch2, sumActs, sumPoints);
	}
	GetDlgItem(IDC_STATIC_cur_mon)->SetWindowText(ch);
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
	//AfxMessageBox(ch);
}


//////////    ������� ���������� \\\\\\\\\\\\\\\\
//���������� �������� ����������, ���� ��� �� ���� � ����� ���������� �� ���
void CEactivityDlg::LoadYearFromStatMons(string mon, float &sumTime, int &sumAct, int &sumPoints) 
{
	WIN32_FIND_DATA FFData;
	string for_find=path_actuser+mon+"*.am";
	HANDLE hFind = FindFirstFile(for_find.c_str(), &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			SumMonStat(path_actuser+FFData.cFileName, sumTime, sumAct, sumPoints);
		} while(FindNextFile(hFind, &FFData));
	}
}
void CEactivityDlg::SumMonStat(string fname, float &sumTime, int &sumAct, int &sumPoints) 
{
	activ::iterator iter=aCurYear.find(fname.substr(fname.length()-10, 7));
	if (iter!=aCurYear.end())
		return; //��� ��������� ���������� �� ���������
	
	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return;
	Activity tmpActiv;
	tmpActiv.num_acts=0;
	tmpActiv.sumTime=0;
	tmpActiv.usefulTime=0;
	tmpActiv.points=0;
	tmpActiv.capt="";
	tmpActiv.exe="";
	tmpActiv.hwChil=0;
	tmpActiv.hwMain=0;
	
	char ch[1024];
	ifstr.getline(ch, 1024);
	while (ifstr)
	{
		int tmpint;
		string sdate;
		ifstr>>sdate;
		ifstr.get();
		if (!ifstr)
			break;
		ifstr>>tmpint;
		tmpActiv.num_acts+=tmpint;
		ifstr.get();
		if (!ifstr)
			break;
		ifstr>>tmpint;
		tmpActiv.points+=tmpint;
		ifstr>>tmpint;
		tmpActiv.sumTime+=tmpint;
		if (!ifstr)
			break;
	}
	ifstr.close();
	sumTime+=tmpActiv.sumTime;
	sumAct+=tmpActiv.num_acts;
	sumPoints+=tmpActiv.points;
	aCurYear[fname.substr(fname.length()-10, 7)]=tmpActiv;
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
	GetDlgItem(IDC_STATIC_cur_mon)->GetWindowRect(&rect);
	ScreenToClient(rect);
	rect+=CPoint(0, main.top-rect.bottom-6);
	GetDlgItem(IDC_STATIC_cur_mon)->MoveWindow(rect);

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
	__SetHook__(FALSE);
	DelIconTray();
}

bool CEactivityDlg::LoadFileDay(string fname, activ &forLoad1, activ_exe &forLoad2) 
{
	WriteJournal("LoadFileDay from %s", fname);
	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return false;
	forLoad1.clear();
	forLoad2.clear();
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
		ifstr>>tmpForSave.num_acts;
		tmpForSave2.num_acts=tmpForSave.num_acts;
		ifstr.get();
		ifstr>>tmpForSave.points;
		tmpForSave2.points=tmpForSave.points;
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
		//_itoa_s(, ch, 10);
		forLoad1[ch + tmpForSave.exe + '\t' + tmpForSave.capt] = tmpForSave;
		activ_exe::iterator iter = forLoad2.find(ch  + tmpForSave.exe);
		if (iter==forLoad2.end())
			forLoad2[ch + tmpForSave.exe]=tmpForSave2;
		else {
			(*iter).second.points+=tmpForSave.points;
			(*iter).second.num_acts+=tmpForSave.num_acts;
			(*iter).second.sumTime+=tmpForSave.sumTime;
		}
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
	WriteJournal("LoadCurDay from %s", strf);
	LoadFileDay(strf, ActivToday, ActivExeToday);
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
		ofstr<<tmpForSave.num_acts;
		ofstr<<'\t';
		ofstr<<tmpForSave.points;
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
		ofstr<<tmpForSave.num_acts;
		ofstr<<'\t';
		ofstr<<tmpForSave.points;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumTime;
		ofstr<<'\t';
		ofstr<<tmpForSave.usefulTime;
		ofstr<<'\n';
	}
	ofstr.close();
}
void CEactivityDlg::LoadYear() 
{
	char date[28];
	SYSTEMTIME st;
	GetLocalTime(&st);
	GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy", date, 26);
	strcat_s(date, ".ayr");
	curYear=date;
	
	float sumTime=0;
	int sumActs=0, sumPoints=0;
	string strf=path_actuser+curYear;
	ifstream ifstr(strf.c_str());
	if (ifstr)
	{
		char ch[1024];
		ifstr.getline(ch, 100);
		
		float ver;
		sscanf_s(ch, "ver=%f", &ver);

		Activity tmpForLoad;
		tmpForLoad.capt="";
		tmpForLoad.exe="";
		tmpForLoad.hwChil=0;
		tmpForLoad.hwMain=0;
		while (ifstr)
		{
			string sdate;
			ifstr>>sdate;
			ifstr.get();
			ifstr>>tmpForLoad.num_acts;
			sumActs+=tmpForLoad.num_acts;
			ifstr.get();
			if (!ifstr)
				break;
			ifstr>>tmpForLoad.points;
			sumPoints+=tmpForLoad.points;
			ifstr>>tmpForLoad.sumTime;
			sumTime+=tmpForLoad.sumTime;
			aCurYear[sdate]=tmpForLoad;
			if (ver>=0.2)
			{
				ifstr>>tmpForLoad.usefulTime;
			}
			aCurYear[sdate]=tmpForLoad;
			if (!ifstr)
				break;
		}
		ifstr.close();
	}
	LoadYearFromStatMons(curYear.substr(0, 15), sumTime, sumActs, sumPoints);
}

void CEactivityDlg::SaveCurDay(bool smena) 
{
	char date[27];
	//__SetHook__(FALSE);

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
		ofstr<<tmpForSave.num_acts;
		ofstr<<'\t';
		ofstr<<tmpForSave.points;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumTime;
		ofstr<<'\t';
		ofstr<<(*it_activ).first;
		ofstr<<'\n';
	}
	ofstr.close();
	if (smena)
	{
		ActivToday.clear();
		ActivExeToday.clear();
	}

}
void CEactivityDlg::OnSave() 
{
	CViewRules ruls;
	ruls.rules=RULES;
	if (ruls.DoModal()!=IDOK)
		return;
	RULES=ruls.rules;
	UpdatePoints();
}

void CEactivityDlg::OnSelchangeCombo_sort() 
{
	UpdatePoints();
}

// � UpdatePoints ����������� ���������� ������� �������, �������� ������� � ��������� ����� ���������
void CEactivityDlg::UpdatePoints() 
{
	char ch[300];
	if (SelDayOrCurDay)
	{
		POSITION pos=list_days.GetFirstSelectedItemPosition();
		int sel=(int)pos-1;
		if (sel<0)
			return;
		string date=list_days.GetItemText(sel, 0);

		float sumTime=0, sumUsefulTime=0; 
		int sumActs=0, sumPoints=0;
		if (sel>-1 && combo_group.GetCurSel()==BYHOURS)
		{
			int hour = atoi(list_days.GetItemText(sel, 0));
			UpdateTopTable(aSelDayView, aSelDayViewExe, sumTime, sumUsefulTime, sumActs, sumPoints, hour);
		} else 
			UpdateTopTable(aSelDayView, aSelDayViewExe, sumTime, sumUsefulTime, sumActs, sumPoints);
// 		if (combo_group.GetCurSel()==BYDAYS)
// 		{
// 			if (SelMonOrCurMon)
// 			{
// 				aSelMon[date].usefulTime=sumUsefulTime;
// 				aSelMon[date].sumTime=sumTime;
// 				aSelMon[date].num_acts=sumActs;
// 				aSelMon[date].points=sumPoints;
// 			} else {
// 				aCurMon[date].usefulTime=sumUsefulTime;
// 				aCurMon[date].sumTime=sumTime;
// 				aCurMon[date].num_acts=sumActs;
// 				aCurMon[date].points=sumPoints;
// 			}
// 		}
		
		//��������� � ������ ������� ������
		float sec=sumTime/1000;
		char ch2[100];
		FormatSeconds(ch2, sec);
		list_days.SetItemText(sel, 2, ch2);

		sec=sumUsefulTime/1000;
		char ch3[100];
		FormatSeconds(ch3, sec);
		list_days.SetItemText(sel, 1, ch3);
		sprintf_s(ch, "%d", sumActs);
		list_days.SetItemText(sel, 3, ch);
		sprintf_s(ch, "%d", sumPoints);
		list_days.SetItemText(sel, 4, ch);

		CString str;
		str.LoadString(trif.GetIds(IDS_STRING1571));

		if (!showAllCaptsForExe.length())
		{
			sprintf_s(ch, str, date.c_str(), ch3, ch2, sumActs, sumPoints);
		} else {
			string exekav="\""+exes[showAllCaptsForExe]+"\"";
			sprintf_s(ch, str, exekav.c_str(), ch3, ch2, sumActs, sumPoints);
		}
		GetDlgItem(IDC_STATIC_curday)->SetWindowText(ch);
	} else {
		// ��� �������
		float sumTime=0, sumUsefulTime=0;
		int sumActs=0, sumPoints=0;
		POSITION pos=list_days.GetFirstSelectedItemPosition();
		int sel=(int)pos-1;
		if (sel>-1 && combo_group.GetCurSel()==BYHOURS)
		{
			int hour = atoi(list_days.GetItemText(sel, 0));
			UpdateTopTable(ActivToday, ActivExeToday, sumTime, sumUsefulTime, sumActs, sumPoints, hour);
		} else 
			UpdateTopTable(ActivToday, ActivExeToday, sumTime, sumUsefulTime, sumActs, sumPoints);
		string skey=curDayFileName.substr(curDayFileName.length()-12, 10);
// 		if (combo_group.GetCurSel()==BYDAYS)
// 		{
// 			if (SelMonOrCurMon)
// 			{
// 				aSelMon[skey].usefulTime=sumUsefulTime;
// 				aSelMon[skey].sumTime=sumTime;
// 				aSelMon[skey].num_acts=sumActs;
// 				aSelMon[skey].points=sumPoints;
// 			} else {
// 				aCurMon[skey].usefulTime=sumUsefulTime;
// 				aCurMon[skey].sumTime=sumTime;
// 				aCurMon[skey].num_acts=sumActs;
// 				aCurMon[skey].points=sumPoints;
// 			}
// 		}
		
		//��������� � ������ ������� ������
		char ch2[100];
		float sec=sumTime/1000;
		FormatSeconds(ch2, sec);
		char ch3[100];
		sec=sumUsefulTime/1000;
		FormatSeconds(ch3, sec);
//		if (sel>-1 && combo_group.GetCurSel()==BYHOURS)
//		{
		if (list_days.GetItemCount() && list_days.GetItemText(0, 0)==skey.c_str())
		{
			list_days.SetItemText(0, 1, ch3);
			sprintf_s(ch, "%d", sumActs);
			list_days.SetItemText(0, 2, ch2);
			sprintf_s(ch, "%d", sumActs);
			list_days.SetItemText(0, 3, ch);
			sprintf_s(ch, "%d", sumPoints);
			list_days.SetItemText(0, 4, ch);
		}
		CString str;
		if (!showAllCaptsForExe.length())
		{
			if (sel>0 && combo_group.GetCurSel()==BYHOURS)
			{
				str.LoadString(trif.GetIds(IDS_STRING1571));
				sprintf_s(ch, str, "selected hour", ch3, ch2, sumActs, sumPoints);
			} else {
				str.LoadString(trif.GetIds(IDS_STRING1575));
				sprintf_s(ch, str, ch3, ch2, sumActs, sumPoints);
			}
		} else {
			str.LoadString(trif.GetIds(IDS_STRING1571));
			string exekav="\""+exes[showAllCaptsForExe]+"\"";
			sprintf_s(ch, str, exekav.c_str(), ch3, ch2, sumActs, sumPoints);
		}
		GetDlgItem(IDC_STATIC_curday)->SetWindowText(ch);
	}
}

// ������� ���� � ������ ������� ��������� ���������� ��� ���������� ����, ���, ������
void CEactivityDlg::OnDblclkListDays(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos=list_days.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	string date=list_days.GetItemText(sel, 0);
	if (date=="..")
	{
		combo_group.SetCurSel(combo_group.GetCurSel()+1);
		OnSelchangeComboDownTable();
		return;
	}
	string fname;
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		UpdatePoints();
		//UpdateDownTableViewByHours(SelDayOrCurDay ? aSelDayView : ActivToday);
		break;
	case BYDAYS:
		fname=path_actuser+"activ_user_"+date+".a";
		if  ("activ_user_"+date+".a"==curDayFileName)
		{
			SelDayOrCurDay=false;
			UpdatePoints();
			combo_group.SetCurSel(0);
			UpdateDownTableViewByHours(ActivExeToday);
			return;
		}
		if (!LoadFileDay(fname, aSelDayView, aSelDayViewExe))
		{
			AfxMessageBox(trif.GetIds(IDS_STRING1573));
			return;
		}
		SelDayOrCurDay=true;
		UpdatePoints();
		combo_group.SetCurSel(0);
		UpdateDownTableViewByHours(aSelDayViewExe);
		break;
	case BYMONTHS:
		fname=path_actuser+"activ_user_"+date+".am";
		combo_group.SetCurSel(1);
		if  ("activ_user_"+date+".am"==curMonFileName)
		{
			SelMonOrCurMon=false;
			//UpdatePoints();
			UpdateDownTable(aCurMon);
//			OnSelchangeComboDownTable();
			return;
		}
		float sumTime=0;
		int sumActs=0, sumPoints=0;
		if (!LoadFileMonth(fname, aSelMon, sumTime, sumActs, sumPoints))
		{
			AfxMessageBox(trif.GetIds(IDS_STRING1573));
			return;
		}
		SelMonOrCurMon=true;
		//UpdatePoints();
		UpdateDownTable(aSelMon);
//		UpdateDownTable(aCurYear);
		break;
	}
	*pResult = 0;
}

void CEactivityDlg::OnActivitySetKoef() 
{	//����: ���������� ����������� ��� ��������� � exe
	POSITION pos=top_table.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	CKoeff koef;
	koef.tmpRule.exe=GetExeFromTable(sel).c_str();
	koef.tmpRule.capt=top_table.GetItemText(sel, 1);
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
	UpdatePoints();
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
		string exe=top_table.GetItemText(sel, 6);
		if (exe.length())
			return exe;
	}
	return "";
}

void CEactivityDlg::OnRclickListCurDay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos=top_table.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	if (top_table.GetItemText(sel, 0).GetLength())
	{
		menu_cur_day.EnableMenuItem(ID_ACTIVITY_SETKOEF, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		menu_cur_day.EnableMenuItem(ID_ACTIVITY_SETKOEFEXE, MF_BYCOMMAND | MF_ENABLED );
	} else {
		menu_cur_day.EnableMenuItem(ID_ACTIVITY_SETKOEFEXE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		menu_cur_day.EnableMenuItem(ID_ACTIVITY_SETKOEF, MF_BYCOMMAND | MF_ENABLED );
	}

	CPoint po;
	GetCursorPos(&po);
	menu_cur_day.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, po.x, po.y, this);
	*pResult = 0;
}

//** ��������� � ��������������� ��������������
//������ ������ �������� �� ������� �����������
//��� ��������� ������-������ ������� ����� ��������������� ��� ���������� � ��� ��� ���������, 
//��� ������� �������� ������� ��������������� points (�������� ��������)

//������� ����� �������� �� ��������� (������ ����� "*" � �������� ������ ����� ������ ��������)
	//�� ������������� ���������

//��������� ������: ���� ���� ������� � ���������� � ���������� ����������, �� ��� �������, ����� �� ���������
	//���� ����������� ������� � ���������� ����������, ���� ������� ����

void CEactivityDlg::OnActivitySetkoefeExe() 
{	//����: ��������� ������������ ��� ����� exe
	POSITION pos=top_table.GetFirstSelectedItemPosition();
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
	UpdatePoints();
}

BOOL CEactivityDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST)
		tool_tip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CEactivityDlg::OnChangeEDITcapts() 
{
	if (inited_pPage5)
		UpdatePoints();
}

void CEactivityDlg::OnActivityShowAllCapts() 
{
	CString str;
	if (!showAllCaptsForExe.length())
	{
		POSITION pos=top_table.GetFirstSelectedItemPosition();
		int sel=(int)pos-1;
		if (sel<0)
			return;
		showAllCaptsForExe=GetExeFromTable(sel).c_str();
		str.LoadString(trif.GetIds(IDS_STRING1587));
	} else {
		showAllCaptsForExe="";
		str.LoadString(trif.GetIds(IDS_STRING1585));
	}
	menu_cur_day.ModifyODMenu(str, ID_ACTIVITY_EXE);
	UpdatePoints();
}

void CEactivityDlg::OnDblclkListCurDay(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnActivityShowAllCapts();
	*pResult = 0;
}

// OnSelchangeComboDownTable ���������� ��� ������ ����� ������ � ������ ����� ������� 
//			����������� ������ � ������ �������
void CEactivityDlg::OnSelchangeComboDownTable() 
{
	if (combo_group.GetCurSel()>0)
		SelMonOrCurMon=false;
	switch (combo_group.GetCurSel())
	{
	case BYHOURS:
		UpdateDownTableViewByHours(SelDayOrCurDay ? aSelDayViewExe : ActivExeToday);
		break;
	case BYDAYS:
		UpdateDownTable(aCurMon);
		break;
	case BYMONTHS:
		UpdateDownTable(aCurYear);
		break;
	}
}

void CEactivityDlg::OnBnClickedOk()
{
// 	COleSafeArray saRet;
// 	DWORD numElements[] = {360, 4}; 
// 	saRet.Create(VT_R8, 2, numElements);
// 	long index[2] = { 0 , 0 };
// 	double value = 0;
// 	double vx = 0;
// 	for(long i = 0; i < 360; i++)
// 	{
// 		// curve 1
// 		index[1] = 0;
// 		vx = i;
// 		saRet.PutElement(index, &vx);
// 		index[1] = 1;
// 		value = sin(i * 0.35);
// 		saRet.PutElement(index, &value);
// 		// curve 2
// 		index[1] = 2;
// 		saRet.PutElement(index, &vx);
// 		index[1] = 3;
// 		value = - sin(i * 0.35);
// 		saRet.PutElement(index, &value);
// 		index[0]++;
// 	}
// //	chart.set put_ChartData(saRet.Detach());
//	chart.SetTitleText ("mschart example by ");
	chart.GetDataGrid().SetData(1, 1, rand () * 100 / RAND_MAX, 0); 
	chart.GetDataGrid().SetData(1, 2, rand () * 100 / RAND_MAX, 0); 
	chart.GetDataGrid().SetData(1, 3, rand () * 100 / RAND_MAX, 0); 
	chart.GetDataGrid().SetData(2, 1, rand () * 100 / RAND_MAX, 0); 
	chart.GetDataGrid().SetData(2, 2, rand () * 100 / RAND_MAX, 0); 
	chart.GetDataGrid().SetData(2, 3, rand () * 100 / RAND_MAX, 0); 
//	chart.GetDataGrid().SetData(1, 1, rand () * 100 / RAND_MAX, 0); 
//	chart.GetDataGrid().SetData(1, 1, rand () * 100 / RAND_MAX, 0); 
//	Exit();
//	OnOK();
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

