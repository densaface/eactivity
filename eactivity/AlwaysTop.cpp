// AlwaysTop.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "AlwaysTop.h"


// CAlwaysTop dialog

IMPLEMENT_DYNAMIC(CAlwaysTop, CDialog)

CAlwaysTop::CAlwaysTop(CWnd* pParent /*=NULL*/)
	: CDialog(CAlwaysTop::IDD, pParent)
{
	RR=GG=0;
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
}


BEGIN_MESSAGE_MAP(CAlwaysTop, CDialog)
	ON_WM_TIMER()
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

void CAlwaysTop::OnTimer(UINT nIDEvent) 
{
	ShowWindow(SW_SHOWNA);
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED | WS_EX_TOPMOST);
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
	statsF.FormatSeconds(fmtSecs, (float)perc_coef);
	if (stat_day_adv.m_hWnd)
	{ //для инфопанели форматируем текст в уменьшенном размере
		statsF.ApplyFont((float)perc_coef, NULL, sizefont, bold, hidedescription, "", 
			stat_day_adv, stat_hour_adv, stat_day_description, stat_hour_description, 
			m_hWnd, RR, GG, resizeWins);
// 		sprintf_s(res, "<b><CENTER><font COLOR=\"%d,%d,0\" size=\"+10\">%s%s</font></CENTER></b>", 
// 			RR, GG, perc_coef>=0 ? "+" : "", fmtSecs);
// 		stat_day_adv.SetWindowText(res);
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
			m_hWnd, rr, gg, resizeWins);
		if (resizeWins)
			resizeWins = false;
//		sprintf_s(res, "<b><CENTER><font COLOR=\"%d,%d,0\" size=\"+10\">%s%s</font></CENTER></b>", 
//			rr, gg, perc_coef>=0 ? "+" : "", fmtSecs);
//		stat_hour_adv.SetWindowText(res);
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