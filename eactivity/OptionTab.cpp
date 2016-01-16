// OptionTab.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "OptionTab.h"


// COptionTab dialog

IMPLEMENT_DYNAMIC(COptionTab, CPropertyPage)

void COptionTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_sleep_period);
	DDX_Control(pDX, IDC_EDITHOLIDAY, edit_holiday);
	DDX_Control(pDX, IDC_EDIT2, edit_hour_norm);
	DDX_Control(pDX, IDC_EDIT4, edit_hour_begin);
	DDX_Control(pDX, IDC_EDIT6, edit_hour_end);
	DDX_Control(pDX, IDC_RADIO1, radio_const_norm);
	DDX_Control(pDX, IDC_RADIO2, radio_norm_last_days);
	DDX_Control(pDX, IDC_CHECK4, check_show_legend);
}

COptionTab::COptionTab(const char* lpszTitle, UINT nIconID)
: CPropertyPage(COptionTab::IDD),
m_nIconID(nIconID),
m_hIcon(NULL)
{
	if( NULL != m_nIconID )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIconTab;
	}
}

COptionTab::~COptionTab()
{
}

BOOL COptionTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CString str;
	int regValue = AfxGetApp()->GetProfileInt("App", "SleepPeriod", 30);
	str.Format("%d", regValue);
	edit_sleep_period.SetWindowText(str);
	str = AfxGetApp()->GetProfileString("App", "UsefulTimeHoliday", "1.5");
	edit_holiday.SetWindowText(str);
	regValue = AfxGetApp()->GetProfileInt("App", "ShowLegend", 1);
	check_show_legend.SetCheck(regValue);
	
	int check_radio = AfxGetApp()->GetProfileInt("App", "RadioConstNorm", 1);
	radio_const_norm    .SetCheck( check_radio);
	radio_norm_last_days.SetCheck(!check_radio);
	str = AfxGetApp()->GetProfileString("App", "HoursNorm", "4.0");
	edit_hour_norm.SetWindowText(str);
	str = AfxGetApp()->GetProfileString("App", "HourWorkBegin", "9");
	edit_hour_begin.SetWindowText(str);
	str = AfxGetApp()->GetProfileString("App", "HourWorkEnd", "18");
	edit_hour_end.SetWindowText(str);
	OnBnClickedRadio1();
	return TRUE;
}

BOOL COptionTab::OnApply()
{
	CString str, strHourWorkBegin, strHourWorkEnd;
	edit_sleep_period.GetWindowText(str);
	if (atoi(str)<1)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1673));
		return FALSE;
	}
	edit_hour_begin.GetWindowText(strHourWorkBegin);
	edit_hour_end.GetWindowText(strHourWorkEnd);
	if (atoi(strHourWorkBegin)>=atoi(strHourWorkEnd))
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1683));
		return FALSE;
	}

	AfxGetApp()->WriteProfileInt("App", "SleepPeriod", atoi(str));

	edit_holiday.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "UsefulTimeHoliday", str);

	AfxGetApp()->WriteProfileInt("App", "RadioConstNorm", radio_const_norm.GetCheck());
	AfxGetApp()->WriteProfileInt("App", "ShowLegend", check_show_legend.GetCheck());

	edit_hour_norm.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "HoursNorm", str);
	AfxGetApp()->WriteProfileString("App", "HourWorkBegin", strHourWorkBegin);
	AfxGetApp()->WriteProfileString("App", "HourWorkEnd", strHourWorkEnd);

	return TRUE;
}

void COptionTab::OnBnClickedRadio1()
{
	BOOL radio_check = radio_const_norm.GetCheck();
	edit_hour_norm.EnableWindow(radio_check);
	edit_hour_begin.EnableWindow(radio_check);
	edit_hour_end.EnableWindow(radio_check);
}

BEGIN_MESSAGE_MAP(COptionTab, CPropertyPage)
	ON_BN_CLICKED(IDC_RADIO1, &COptionTab::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &COptionTab::OnBnClickedRadio1)
END_MESSAGE_MAP()
// OptionTab.cpp : implementation file
//


IMPLEMENT_DYNAMIC(COptionTab2, CPropertyPage)

COptionTab2::COptionTab2(const char* lpszTitle, UINT nIconID)
: CPropertyPage(COptionTab2::IDD),
m_nIconID(nIconID),
m_hIcon(NULL)
{
	if( NULL != m_nIconID )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIconTab;
	}
	faceFont = "";
}
COptionTab2::~COptionTab2()
{
}

void COptionTab2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_percent_day, stat_day_adv);
	DDX_Control(pDX, IDC_STATIC_percent_hour2, stat_hour_adv);
	DDX_Control(pDX, IDC_EDITHOLIDAY, edit_size_font);
	DDX_Control(pDX, IDC_EDIT1, edit_frequpdate);
	DDX_Control(pDX, IDC_EDITHOLIDAY2, edit_autostart_break);
	DDX_Control(pDX, IDC_EDITHOLIDAY3, edit_work_period);
	DDX_Control(pDX, IDC_CHECK1, check_bold);
	DDX_Control(pDX, IDC_CHECK4, check_auto_break);
	DDX_Control(pDX, IDC_CHECK3, check_hide_description);
	DDX_Control(pDX, IDC_STATIC_percent_hour, stat_hour_description);
	DDX_Control(pDX, IDC_STATIC_percent_day2, stat_day_description);
}


BEGIN_MESSAGE_MAP(COptionTab2, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK3, &COptionTab2::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK1, &COptionTab2::OnBnClickedCheck3)
	ON_EN_CHANGE(IDC_EDITHOLIDAY, &COptionTab2::OnBnClickedCheck3)
	ON_EN_CHANGE(IDC_EDIT1, &COptionTab2::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &COptionTab2::OnBnClickedCheck4)
END_MESSAGE_MAP()

BOOL COptionTab2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CString str;
	int regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.sizefont", 10);
	str.Format("%d", regValue);
	edit_size_font.SetWindowText(str);

	regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.frequpdate", 5);
	str.Format("%d", regValue);
	edit_frequpdate.SetWindowText(str);

	regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.autostart_break", 2);
	str.Format("%d", regValue);
	edit_autostart_break.SetWindowText(str);

	regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.work_period", 45);
	str.Format("%d", regValue);
	edit_work_period.SetWindowText(str);

	regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.bold", 1);
	check_bold.SetCheck(regValue);
	regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.hidedescription", 0);
	check_hide_description.SetCheck(regValue);
	regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.auto_break", 1);
	check_auto_break.SetCheck(regValue);

	str.LoadString(trif.GetIds(IDS_STRING1675));
	stat_hour_description.SetWindowText(str);
	str.LoadString(trif.GetIds(IDS_STRING1679));
	stat_day_description .SetWindowText(str);

	OnApplyFont();
	return TRUE;
}

BOOL COptionTab2::OnApply()
{
	CString str;
	edit_frequpdate.GetWindowText(str);
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.frequpdate", atoi(str));

	edit_work_period.GetWindowText(str);
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.work_period", atoi(str));

	edit_autostart_break.GetWindowText(str);
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.autostart_break", atoi(str));

	edit_size_font.GetWindowText(str);
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.sizefont", atoi(str));
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.bold", check_bold.GetCheck());
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.auto_break", 
		check_auto_break.GetCheck());
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.hidedescription", 
		check_hide_description.GetCheck());

	return TRUE;
}

void COptionTab2::OnApplyFont()
{
	CString edit_size;
	edit_size_font.GetWindowText(edit_size);

	statsF.ApplyFont(3238, 541, atoi(edit_size), 
		check_bold.GetCheck(), check_hide_description.GetCheck(), faceFont,
		stat_day_adv, stat_hour_adv, stat_day_description, stat_hour_description, 
		false, m_hWnd, 0, 100, true);
	return;
}

void COptionTab2::OnBnClickedCheck3()
{
	OnApplyFont();
}
// OptionTab.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "OptionTab.h"


// COptionTabMail dialog

IMPLEMENT_DYNAMIC(COptionTabMail, CPropertyPage)

COptionTabMail::COptionTabMail(const char* lpszTitle, UINT nIconID)
: CPropertyPage(COptionTabMail::IDD),
m_nIconID(nIconID),
m_hIcon(NULL)
{
	if( NULL != m_nIconID )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIconTab;
	}
}

COptionTabMail::~COptionTabMail()
{
}

void COptionTabMail::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT5, edit_email);
	DDX_Control(pDX, IDC_CHECK1, check_email);
}


BEGIN_MESSAGE_MAP(COptionTabMail, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &COptionTabMail::OnTestMail)
	ON_BN_CLICKED(IDC_CHECK1, &COptionTabMail::OnBnClickedCheckEmail)
END_MESSAGE_MAP()

BOOL COptionTabMail::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CString str;
	int regValue = AfxGetApp()->GetProfileInt("App", "email.enable", 0);
	check_email.SetCheck(regValue);
	edit_email.SetWindowText(AfxGetApp()->GetProfileString("App", "email.to", ""));
	OnBnClickedCheckEmail();
	return TRUE;
}

BOOL COptionTabMail::OnApply()
{
	CString str;
	edit_email.GetWindowText(str);
	if (check_email.GetCheck() && str.Find("@")==-1)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1687));
		return FALSE;
	}
	AfxGetApp()->WriteProfileString("App", "email.to", str);
	AfxGetApp()->WriteProfileInt("App", "email.enable", check_email.GetCheck());

	return TRUE;
}

void COptionTabMail::OnTestMail() 
{
	CStringArray saMessage;
	CString str;
	edit_email.GetWindowText(str);
	statsF.SendMailMessage("smtp.gmail.com", 587, "silencenotif@gmail.com", 
		str, str, "GhjcajhyZ88", 
		"Test from ActivateMe", saMessage);
}

void COptionTabMail::OnBnClickedCheckEmail()
{
	BOOL email_check = check_email.GetCheck();
	edit_email.EnableWindow(email_check);
}

void COptionTab2::OnBnClickedCheck4()
{
	BOOL bCheck = check_auto_break.GetCheck();
	edit_autostart_break.EnableWindow(bCheck);
	edit_work_period.EnableWindow(bCheck);
}
