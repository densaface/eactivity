// EndWork.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "EndWork.h"


// CEndWork dialog

IMPLEMENT_DYNAMIC(CEndWork, CDialog)

CEndWork::CEndWork(CWnd* pParent /*=NULL*/)
	: CDialog(CEndWork::IDD, pParent)
{
	sLink="";
	sProg="";
}

CEndWork::~CEndWork()
{
}

void CEndWork::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UsefulActs, stat_usefulacts);
	DDX_Control(pDX, IDC_UsefulTime, stat_usefultime);
	DDX_Control(pDX, IDC_SummonTime, stat_summon_time);
	DDX_Control(pDX, IDC_PercTime, stat_percent_time);
	DDX_Control(pDX, IDC_ResActs, stat_res_acts);
	DDX_Control(pDX, IDC_Pauses, stat_pauses);
	DDX_Control(pDX, IDC_COMBO1, combo_pause);
	DDX_Control(pDX, IDC_PROGRESS1, progressTimePause);
	DDX_Control(pDX, IDC_TIME_PAUSE, static_time_pause);
	DDX_Control(pDX, IDC_SHORTTODO, stat_short_todo);
	DDX_Control(pDX, IDC_STATICdesc1, stat_desc1);
	DDX_Control(pDX, IDC_CHECK1, check_show_stat);
}


BEGIN_MESSAGE_MAP(CEndWork, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CEndWork::OnCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CEndWork::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CEndWork::OnBnClickedCheck1)
	ON_BN_CLICKED(IDCANCEL, &CEndWork::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CEndWork::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CEndWork::OnBnClickedButton2)
	ON_CBN_EDITCHANGE(IDC_COMBO1, &CEndWork::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CEndWork::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, &CEndWork::OnBnClickedButton4)
END_MESSAGE_MAP()

BOOL CEndWork::OnInitDialog() 
{
	CDialog::OnInitDialog();
	startPause = GetTickCount();
	highLight = false; //подсветили программу, когда перерыв кончился
	char ch[100];
	statF.FormatSeconds(ch, usefulTime/1000);
	char formattedText[512];
	sprintf_s(formattedText, "<b><CENTER><font COLOR=\"7,92,177\" size=\"+4\">%s</font></CENTER></b>", ch);
	stat_usefultime.SetWindowText(formattedText);
	sprintf_s(formattedText, "<b><CENTER><font COLOR=\"7,92,177\" size=\"+4\">%d</font></CENTER></b>", usefulActs);
	stat_usefulacts.SetWindowText(formattedText);
	statF.FormatSeconds(ch, summonTime/(float)1000.0);
	sprintf_s(formattedText, "<b><CENTER><font COLOR=\"7,92,177\" size=\"+4\">%s</font></CENTER></b>", ch);
	stat_summon_time.SetWindowText(formattedText);
	if (summonTime!=0)
	{
		sprintf_s(formattedText, 
			"<b><CENTER><font COLOR=\"7,92,177\" size=\"+4\">%0.2f</font></CENTER></b>", 
			100*usefulTime/summonTime);
		stat_percent_time.SetWindowText(formattedText);
	} else {
		stat_percent_time.SetWindowText(
			"<b><CENTER><font COLOR=\"7,92,177\" size=\"+4\">--</font></CENTER></b>");
	}
	if (summonTime!=0)
	{
		sprintf_s(formattedText, 
			"<b><CENTER><font COLOR=\"7,92,177\" size=\"+4\">%0.2f</font></CENTER></b>", 
			1000*usefulActs/usefulTime);
		stat_res_acts.SetWindowText(formattedText);
	} else {
		stat_res_acts.SetWindowText(
			"<b><CENTER><font COLOR=\"7,92,177\" size=\"+4\">--</font></CENTER></b>");
	}
	sprintf_s(formattedText, 
		"<b><CENTER><font COLOR=\"7,92,177\" size=\"+4\">%d</font></CENTER></b>", 
		pauseCount);
	stat_pauses.SetWindowText(formattedText);
	if (summonTime >= 5*60*1000)
		WriteStatisticWorkPeriod();

	check_show_stat.SetCheck(AfxGetApp()->GetProfileInt("App", "EndWorkPause.showStat", 0));
	OnBnClickedCheck1();

	combo_pause.AddString("5");
	combo_pause.AddString("10");
	combo_pause.AddString("15");
	combo_pause.AddString("20");
	combo_pause.AddString("30");
	int iPause   = AfxGetApp()->GetProfileInt("App", "EndWorkPause.minutes", 15);
	sprintf_s(ch, "%d", iPause);
	combo_pause.SetWindowText(ch);
	OnCbnSelchangeCombo();
	progressTimePause.SetPos(0);
	SetTimer(115, 1000, 0);

	if (shortTodo)
	{
		Competition();
	} else {
		stat_desc1.ShowWindow(SW_HIDE);
		stat_short_todo.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	}
	if (textMes!="")
		AfxMessageBox(textMes);
	SetForegroundWindow();
	return TRUE;
}

void CEndWork::Competition()
{
	CListShortTodo* shortAction = new CListShortTodo; 
	shortAction->path_actuser = path_actuser;
	sLink = sProg = "";
	sAction = shortAction->getRandomShortAction(sGroup, sLink, sProg, uniq);
	CString strDate = shortAction->findLastTimeMakingShortTodo(uniq);
	char ch[5000];
	CString sPattern;
	sPattern.LoadString(trif.GetIds(IDS_STRING1727));
	if (strDate!="")
	{
		CString sPatDateShortTodo;
		sPatDateShortTodo.LoadString(trif.GetIds(IDS_STRING1737));
		strDate = sPatDateShortTodo + "<b>" + strDate + "</b>";
	}
	sprintf_s(ch, sPattern, sAction, sGroup, strDate);
	stat_short_todo.SetWindowText(ch);
	if (sLink=="" && sProg=="")
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	else 
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	delete shortAction;
}

void CEndWork::OnCancel()
{
	CString str;
	if (shortTodo && GetDlgItem(IDC_BUTTON2)->IsWindowEnabled())
	{
		if (AfxMessageBox(trif.GetIds(IDS_STRING1733), MB_YESNO) != IDYES)
			return;
	}
	combo_pause.GetWindowText(str);
	AfxGetApp()->WriteProfileInt("App", "EndWorkPause.minutes", atoi(str));
	AfxGetApp()->WriteProfileInt("App", "EndWorkPause.showStat", check_show_stat.GetCheck());
	CDialog::OnOK();
	DestroyWindow();
}

void CEndWork::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==115)
	{
		int pauseSeconds = (GetTickCount() - startPause)/1000;
		progressTimePause.SetPos(pauseSeconds);
		char ch[100];
		int nLower, nUpper;
		progressTimePause.GetRange(nLower, nUpper);
		statF.FormatSeconds(ch, (float)(nUpper-pauseSeconds));
		if (!highLight && nUpper-pauseSeconds < 0)
		{
			highLight=true;
			SetForegroundWindow();
		}
		if (nUpper-pauseSeconds>0)
		{
			highLight=false;//чтобы заново подсветить программу если поменяли перерыв
			static_time_pause.SetWindowText(ch);
		} else {
			char chFmt[300];
			sprintf_s(chFmt, "<b><font COLOR=\"255,0,0\" size=\"+0\">%s</font></b>", ch);
			static_time_pause.SetWindowText(chFmt);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CEndWork::OnBnClickedButton1()
{
	if (sLink!="" || sProg!="")
	{
		CString mes="";
		CString str;
		if (sLink!="")
		{
			str.LoadString(trif.GetIds(IDS_STRING1721));
			mes += str + sLink + "\n";
		}
		if (sProg!="")
		{
			str.LoadString(trif.GetIds(IDS_STRING1723));
			mes += str + sProg + "\n";
		}
		str.LoadString(trif.GetIds(IDS_STRING1725));
		mes += str;
		if (AfxMessageBox(mes, MB_YESNO)!=IDYES)
			return;
	}
	if (sLink!="")
		ShellExecute( 0,"open",sLink,NULL,NULL,SW_MAXIMIZE); 
	if (sProg!="")
		ShellExecute(0, NULL, sProg, NULL, NULL, SW_HIDE);
}

void CEndWork::OnBnClickedCheck1()
{
	int iShow = check_show_stat.GetCheck() ? SW_SHOW : SW_HIDE;
	stat_usefulacts.ShowWindow(iShow);
	stat_usefultime.ShowWindow(iShow);
	stat_summon_time.ShowWindow(iShow);
	stat_percent_time.ShowWindow(iShow);
	stat_res_acts.ShowWindow(iShow);
	stat_pauses.ShowWindow(iShow);
	GetDlgItem(IDC_STATIC1)->ShowWindow(iShow);
	GetDlgItem(IDC_STATIC2)->ShowWindow(iShow);
	GetDlgItem(IDC_STATIC3)->ShowWindow(iShow);
	GetDlgItem(IDC_STATIC4)->ShowWindow(iShow);
	GetDlgItem(IDC_STATIC5)->ShowWindow(iShow);
	GetDlgItem(IDC_STATIC6)->ShowWindow(iShow);
}

void CEndWork::OnBnClickedCancel()
{
	CDialog::OnCancel();
	DestroyWindow();
}

void CEndWork::OnBnClickedButton3()
{
	Competition();
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}

void CEndWork::WriteStatisticWorkPeriod()
{
	CStdioFile sfLog;
	string fileName = path_actuser + "journal_short_todo.txt";
	if (!sfLog.Open(fileName.c_str(), CFile::modeWrite))
		if (!sfLog.Open(fileName.c_str(), CFile::modeWrite|CFile::modeCreate))
			return;
	sfLog.SeekToEnd();
	char formattedText[512];
	CTime ct=CTime::GetCurrentTime();
	sprintf_s(formattedText, "\n%02d.%02d.%02d\t%02d:%02d:%02d\n", 
		ct.GetYear(), ct.GetMonth(), ct.GetDay(),
		ct.GetHour(), ct.GetMinute(), ct.GetSecond());
	sfLog.WriteString(formattedText);
	sprintf_s(formattedText, "Useful time = %d seconds\n", (int)usefulTime/1000);
	sfLog.WriteString(formattedText);
	sprintf_s(formattedText, "Useful acts = %d\n", usefulActs);
	sfLog.WriteString(formattedText);
	sprintf_s(formattedText, "Entire time = %d seconds\n", (int)summonTime/1000.0);
	sfLog.WriteString(formattedText);
	if (summonTime!=0)
	{
		sprintf_s(formattedText, "Useful time percentage = %0.2f\n", 100*usefulTime/summonTime);
		sfLog.WriteString(formattedText);
	} else {
		sfLog.WriteString("Useful time percentage = --\n");
	}
	if (summonTime!=0)
	{
		sprintf_s(formattedText, "Action per unit time = %0.2f\n", 1000*usefulActs/usefulTime);
		sfLog.WriteString(formattedText);
	} else {
		sfLog.WriteString("Action per unit time = --\n");
	}
	sprintf_s(formattedText, "Breaks number = %d\n", pauseCount);
	sfLog.WriteString(formattedText);
	sfLog.Close();
}

//записываем в журнал коротких дел выполненное дело и его уникальный номер
void CEndWork::OnBnClickedButton2()
{
	CStdioFile sfLog;
	string fileName = path_actuser + "journal_short_todo.txt";
	if (!sfLog.Open(fileName.c_str(), CFile::modeWrite))
		if (!sfLog.Open(fileName.c_str(), CFile::modeWrite|CFile::modeCreate))
			return;
	sfLog.SeekToEnd();
	char ch[1024];
	CTime ct=CTime::GetCurrentTime();
	sprintf_s(ch, "\n%02d.%02d.%02d    %02d:%02d:%02d\t%s (Group: %s) (uniq=%d) - done", 
		ct.GetYear(), ct.GetMonth(), ct.GetDay(),
		ct.GetHour(), ct.GetMinute(), ct.GetSecond(), sAction, sGroup, uniq);
	sfLog.WriteString(ch);
	sfLog.Close();
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
}

void CEndWork::OnCbnSelchangeCombo()
{
	CString str;
	combo_pause.GetWindowText(str);
	progressTimePause.SetRange(0, atoi(str)*60);
	int nLower, nUpper;
	progressTimePause.GetRange(nLower, nUpper);
	nUpper = nUpper;
}


void CEndWork::OnCbnSelchangeCombo1()
{
	CString str;
	int iSel = combo_pause.GetCurSel();
	if (iSel == -1)
		return;
	combo_pause.GetLBText(iSel, str);
	combo_pause.SetWindowText(str);
	OnCbnSelchangeCombo();
}


void CEndWork::OnBnClickedButton4()
{
	CListShortTodo dialShortTodo;
	dialShortTodo.path_actuser = path_actuser;
	dialShortTodo.DoModal();
}
