// AlwaysTop.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "AlwaysTop.h"


// CAlwaysTop dialog

IMPLEMENT_DYNAMIC(CAlwaysTop, CDialog)

float WorkPeriod::getUsefulPar()
{
	switch (typeUsefulPar)
	{
	case 1:
		return (float)currentUsefulActs;
	case 2:
		return (float)currentUsefulTime/1000;
	case 3:
		return (float)(GetTickCount()-startProgressTime)/1000;
	}
	ASSERT(0);
	return 0;
}

CAlwaysTop::CAlwaysTop(CWnd* pParent /*=NULL*/)
	: CDialog(CAlwaysTop::IDD, pParent)
{
	RR=GG=0;
	workPeriod.maxUsefulPar = -1;
	workPeriod.typeUsefulPar = 0;
}

CAlwaysTop::~CAlwaysTop()
{
}

void CAlwaysTop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_percent_day, stat_day_adv);
	DDX_Control(pDX, IDC_STATIC_percent_hour2, stat_hour_adv);
	DDX_Control(pDX, IDC_STATIC_percent_hour, stat_hour_description);
	DDX_Control(pDX, IDC_STATIC_percent_day2, stat_day_description);
	DDX_Control(pDX, IDC_PROGRESS1, progress_useful);
	DDX_Control(pDX, IDC_STATICProgress, static_progress);
}


BEGIN_MESSAGE_MAP(CAlwaysTop, CDialog)
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CAlwaysTop::OnNMCustomdrawProgress1)
END_MESSAGE_MAP()

BOOL CAlwaysTop::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// установка окна в правый верхний угол (или в тот, в котором последний раз было положение)
	CRect rect_desktop, winInfo;
	::GetWindowRect(GetDesktopWindow()->m_hWnd, &rect_desktop);
	GetWindowRect(&winInfo);
	int left   = AfxGetApp()->GetProfileInt("App", "InfoPanelPosition.left", 
		rect_desktop.right - winInfo.Width());
	int right  = AfxGetApp()->GetProfileInt("App", "InfoPanelPosition.right", 
		rect_desktop.right);
	int top    = AfxGetApp()->GetProfileInt("App", "InfoPanelPosition.top", 80);
	int bottom = AfxGetApp()->GetProfileInt("App", "InfoPanelPosition.bottom", 
		80+winInfo.Height());
	if (left>rect_desktop.right-2 || left < 0+2 || top>rect_desktop.Height()-2 || top < 0+2)
		MoveWindow(rect_desktop.right - winInfo.Width(), 80, right-left, 
			bottom-top);
	else
		MoveWindow(left, top, winInfo.Width(), winInfo.Height());
	return FALSE;
}

void CAlwaysTop::SavePosition()
{
	if (!m_hWnd)
		return;
	CRect winInfo;
	GetWindowRect(&winInfo);
	AfxGetApp()->WriteProfileInt("App", "InfoPanelPosition.left", winInfo.left);
	AfxGetApp()->WriteProfileInt("App", "InfoPanelPosition.right", winInfo.right);
	AfxGetApp()->WriteProfileInt("App", "InfoPanelPosition.top", winInfo.top);
	AfxGetApp()->WriteProfileInt("App", "InfoPanelPosition.bottom", winInfo.bottom);
}

void CAlwaysTop::OnCancel()
{
	KillTimer(55556);
	ShowWindow(SW_HIDE);
	::SendMessageTimeout(AfxGetMainWnd()->GetSafeHwnd(), WM_INFO_CLOSE, 2, 2, 
		0, 5000, NULL);
	CDialog::OnCancel();
}

void CAlwaysTop::StartShow()
{
	if (!m_hWnd)
	{
		Create(IDD_ALWAYS_TOP);
	}
	SetTimer(55556, 200 ,0);
}

//стартовать показ прогресс бара с показом, сколько осталось до выполнения объема 
// полезного параметра
void CAlwaysTop::StartProgress(float UsefulActs, float UsefulTime, float UsualTime)
{
	switch (workPeriod.typeUsefulPar)
	{
	case 1:
		workPeriod.maxUsefulPar = UsefulActs;
		break;
	case 2:
		workPeriod.maxUsefulPar = UsefulTime/1000;
		break;
	case 3:
		workPeriod.maxUsefulPar = UsualTime/1000;
		break;
	default:
		ASSERT(0); // некорректное значение typeUsefulPar
	}
	workPeriod.currentUsefulTime = 0.0;
	workPeriod.currentUsefulActs = 0;
	workPeriod.pauses = 0;
	if (!m_hWnd)
		return; //инфопанель находится в скрытом виде
	progress_useful.SetRange(0, (short)workPeriod.maxUsefulPar);
	progress_useful.SetPos(0);
	progress_useful.ShowWindow(SW_SHOW);
	//SetTimer(33336, 500 ,0);
}

void CAlwaysTop::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==55556)
	{
		ShowWindow(SW_SHOWNA);
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED | WS_EX_TOPMOST);
	}
// 	else {
// 		progress_useful.SetPos((int)currentUsefulTime);
// 	}
	CDialog::OnTimer(nIDEvent);
}

CString CAlwaysTop::CalculateDayNorm(activ_hours &lastAverageHoursGraph,
	float sumUsefulSec, CString &static2, double coefNorm)
{
	double sumUsefulTimeBeforeCurrentHour=0;
	SYSTEMTIME st;
	GetLocalTime(&st);
	for (int ii=0; ii<curHour; ii++)
	{
		if (lastAverageHoursGraph.find(ii)!=lastAverageHoursGraph.end())
			sumUsefulTimeBeforeCurrentHour+=lastAverageHoursGraph[ii].usefulTime;
	}
	sumUsefulTimeBeforeCurrentHour += lastAverageHoursGraph[st.wHour].usefulTime/60*(st.wMinute+1);
	if (coefNorm>0.0)
		sumUsefulTimeBeforeCurrentHour = sumUsefulTimeBeforeCurrentHour/coefNorm;
	//если достигли четверти нормы в отставании, то присваиваем самый красный цвет и дальше делаем его темнее
	double lag = (sumUsefulTimeBeforeCurrentHour-sumUsefulSec)/
		(sumUsefulTimeBeforeCurrentHour + 1000); //1000 чтобы избежать деление на ноль
	double perc_coef = (sumUsefulSec-sumUsefulTimeBeforeCurrentHour)/1000;
	RR = GG = 0;
	if (perc_coef < 0)
	{
		RR=50+(int)(600*lag);
		if (RR>255)
			RR=255;
	} else {
		GG=50-(int)(200*lag);//lag отрицательный и может быть больше 1
		if (GG>255)
			GG=255;
	}
	char fmtSecs[100];
	char res[300];
	char fmtText[300];
	statsF.FormatSeconds(fmtSecs, (float)perc_coef);
	if (stat_day_adv.m_hWnd)
	{ //для инфопанели форматируем текст в уменьшенном размере
		statsF.ApplyFont((float)perc_coef, NULL, sizefont, bold, hidedescription, "", 
			stat_day_adv, stat_hour_adv, stat_day_description, stat_hour_description, 
			(workPeriod.typeUsefulPar>0), m_hWnd, RR, GG, resizeWins);
		if (workPeriod.typeUsefulPar)
		{
			progress_useful.SetPos((int)workPeriod.getUsefulPar());
			int secsRest;
			char chRestPar[100];
			switch (workPeriod.typeUsefulPar)
			{
			case 1:
				{
					CString patt;
					patt.LoadString(trif.GetIds(IDS_STRING1729));
					sprintf_s(chRestPar, patt, 
						(int)(workPeriod.maxUsefulPar-workPeriod.currentUsefulActs));
					break;
				}
			case 2:
				{
					secsRest = (int)(workPeriod.maxUsefulPar - 
						workPeriod.currentUsefulTime/1000);
					break;
				}
			case 3:
				{
					secsRest = (int)workPeriod.maxUsefulPar - 
						(GetTickCount()-workPeriod.startProgressTime)/1000;
					break;
				}
			}
			if (workPeriod.typeUsefulPar==2 || workPeriod.typeUsefulPar==3)
			{
				statsF.FormatSeconds(chRestPar, (float)secsRest);
			}
			CString description_rest_stat="";
			if (!hidedescription)
				description_rest_stat.LoadString(trif.GetIds(IDS_STRING1731));
			sprintf_s(fmtText, "%s%s%s<font SIZE=\"+%d\" COLOR=\"7,92,177\">%s</font>%s%s", 
				description_rest_stat, bold ? "<b>" : "", 
				hidedescription ? "<center>" : "",
				sizefont, 
				chRestPar,
				hidedescription ? "</center>" : "",
				bold ? "</b>" : "");
			static_progress.SetWindowText(fmtText);
		}
		if (isEndWork())
		{
			setEndWork();
		}
	}
	sprintf_s(res, "<b><CENTER><font COLOR=\"%d,%d,0\" size=\"+18\">%s%s</font></CENTER></b>", 
		RR, GG, perc_coef>=0 ? "+" : "", fmtSecs);
	if (stat_day_description.m_hWnd)
	{	//сокращенная форма записи для статика описания
		static2.LoadString(trif.GetIds(IDS_STRING1679+(perc_coef>=0 ? 0 : 2)));
		stat_day_description.SetWindowText(static2);
	}
	static2.LoadString(trif.GetIds(IDS_STRING1651+(perc_coef>=0 ? 0 : 2)));
	return res;
}

//отражаем в интерфейсе завершение рабочего промежутка времени
void CAlwaysTop::setEndWork()
{
	if (!m_hWnd)
		return;
	progress_useful.SetPos((int)workPeriod.maxUsefulPar);
	CString sBreak;
	char fmtText[300];
	sBreak.LoadString(trif.GetIds(IDS_STRING1735));
	sprintf_s(fmtText, "%s<center><font SIZE=\"+%d\" COLOR=\"0,255,0\">%s</font></center>%s", 
		bold ? "<b>" : "", 
		sizefont, 
		sBreak,
		bold ? "</b>" : "");
	static_progress.SetWindowText(fmtText);
}

bool CAlwaysTop::isEndWork()
{
	switch (workPeriod.typeUsefulPar)
	{
	case 0:
		return 0;
	case 1:
		return workPeriod.currentUsefulActs >= workPeriod.maxUsefulPar;
	case 2:
		return workPeriod.currentUsefulTime/1000 >= workPeriod.maxUsefulPar;
	case 3:
		return GetTickCount() >= workPeriod.startProgressTime + workPeriod.maxUsefulPar*1000;
	}
	ASSERT(0); // некорректное значение typeUsefulPar
	return 0;
}

CString CAlwaysTop::CalculateHourNorm(activ_hours &lastAverageHoursGraph,
	float usefulTimeForCurrentHour, CString &static2, double coefNorm)
{
	double perc_coef;
	SYSTEMTIME st;
	GetLocalTime(&st);
	if (lastAverageHoursGraph[st.wHour].usefulTime < 1000)
	{
		perc_coef=100; //избегаем деления на 0
	} else {
		perc_coef=usefulTimeForCurrentHour/lastAverageHoursGraph[st.wHour].usefulTime*
			60/(st.wMinute+1)*100-100;
		if (perc_coef>500) perc_coef=500;
	}
	double norm_current_hour = lastAverageHoursGraph[st.wHour].usefulTime;
	if (coefNorm > 0.0) 
	{
		norm_current_hour = norm_current_hour / coefNorm;
	}
	double lag=(norm_current_hour/60*(st.wMinute+1) - usefulTimeForCurrentHour)/
		(norm_current_hour/60*(st.wMinute+1));
	int rr=0, gg=0;
	if (perc_coef < 0)
	{
		rr=50+(int)(600*lag);
		if (rr>255)
			rr=255;
	} else {
		gg=50-(int)(200*lag);//lag отрицательный и может быть больше 1
		if (gg>255)
			gg=255;
		if (st.wMinute<20)
			gg=50;
	}
	char fmtSecs[100];
	char res[300];
	float secs = usefulTimeForCurrentHour/1000-
		(float)norm_current_hour/1000/60*(st.wMinute+1);
	statsF.FormatSeconds(fmtSecs, secs);
	if (stat_hour_adv.m_hWnd)
	{	//для инфопанели форматируем текст в уменьшенном размере
		statsF.ApplyFont(NULL, secs, sizefont, bold, hidedescription, "", 
			stat_day_adv, stat_hour_adv, stat_day_description, stat_hour_description, 
			(workPeriod.typeUsefulPar>0), m_hWnd, rr, gg, resizeWins);
		if (resizeWins) 
		{
			resizeWins = false;
			ResizeOtherWins();
			CRect rec_desk;//перерисовываем экран, чтобы артефакты ресайза убрать
			::GetWindowRect(GetDesktopWindow()->GetSafeHwnd(), rec_desk);
			::RedrawWindow(0, rec_desk, 0, RDW_FRAME|RDW_INVALIDATE|RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
		}
	}
	sprintf_s(res, "<b><CENTER><font COLOR=\"%d,%d,0\" size=\"+18\">%s%s</font></CENTER></b>", 
		rr, gg, perc_coef>=0 ? "+" : "", fmtSecs);
	if (stat_hour_description.m_hWnd)
	{	//сокращенная форма записи для статика описания
		static2.LoadString(trif.GetIds(IDS_STRING1675+(perc_coef>=0 ? 0 : 2)));
		stat_hour_description.SetWindowText(static2);
	}
	static2.LoadString(trif.GetIds(IDS_STRING1647+(perc_coef>=0 ? 0 : 2)));
	return res;
}

void CAlwaysTop::ResizeOtherWins()
{
	if (!workPeriod.typeUsefulPar)
		return;
	CRect hourRect;
	stat_hour_adv.GetWindowRect(hourRect);
	CRect statProgressRect;
	statProgressRect = hourRect;
	statProgressRect += CPoint(0, hourRect.Height());
	CRect progrRect;
	progress_useful.GetWindowRect(progrRect);
	CRect infoPanelRect;
	GetWindowRect(infoPanelRect);
	statProgressRect.left = infoPanelRect.left + 8;
	statProgressRect.right = infoPanelRect.right - 8;
	progrRect -= CPoint(0, progrRect.top - statProgressRect.bottom);
	int gap = 4;
	progrRect.left = infoPanelRect.left + gap;
	progrRect.right = infoPanelRect.right - gap;
	infoPanelRect.bottom = progrRect.bottom + gap;
	ScreenToClient(statProgressRect);		
	static_progress.MoveWindow(statProgressRect);
	ScreenToClient(progrRect);		
	progress_useful.MoveWindow(progrRect);
	progrRect.bottom+=1;
	MoveWindow(infoPanelRect);
}

void CAlwaysTop::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}
