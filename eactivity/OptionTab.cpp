// OptionTab.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "OptionTab.h"


// COptionTab dialog

IMPLEMENT_DYNAMIC(COptionTab, CPropertyPage)

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
	
	int check_radio = AfxGetApp()->GetProfileInt("App", "RadioConstNorm", 1);
	radio_const_norm    .SetCheck( check_radio);
	radio_norm_last_days.SetCheck(!check_radio);
	return TRUE;
}

BOOL COptionTab::OnApply()
{
	CString str;
	edit_sleep_period.GetWindowText(str);
	if (atoi(str)<1)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1673));
		return FALSE;
	}
	AfxGetApp()->WriteProfileInt("App", "SleepPeriod", atoi(str));

	edit_holiday.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "UsefulTimeHoliday", str);

	AfxGetApp()->WriteProfileInt("App", "RadioConstNorm", radio_const_norm.GetCheck());
	return TRUE;
}

void COptionTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_sleep_period);
	DDX_Control(pDX, IDC_EDITHOLIDAY, edit_holiday);
	DDX_Control(pDX, IDC_RADIO1, radio_const_norm);
	DDX_Control(pDX, IDC_RADIO2, radio_norm_last_days);
}


BEGIN_MESSAGE_MAP(COptionTab, CPropertyPage)
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
	DDX_Control(pDX, IDC_CHECK1, check_bold);
	DDX_Control(pDX, IDC_CHECK3, check_hide_description);
	DDX_Control(pDX, IDC_STATIC_percent_hour, stat_hour_description);
	DDX_Control(pDX, IDC_STATIC_percent_day2, stat_day_description);
}


BEGIN_MESSAGE_MAP(COptionTab2, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK3, &COptionTab2::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK1, &COptionTab2::OnBnClickedCheck3)
	ON_EN_CHANGE(IDC_EDITHOLIDAY, &COptionTab2::OnBnClickedCheck3)
	ON_EN_CHANGE(IDC_EDIT1, &COptionTab2::OnBnClickedCheck3)
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
	regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.bold", 1);
	check_bold.SetCheck(regValue);
	regValue = AfxGetApp()->GetProfileInt("App", "InfoPanel.hidedescription", 0);
	check_hide_description.SetCheck(regValue);

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
	edit_size_font.GetWindowText(str);
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.sizefont", atoi(str));
	AfxGetApp()->WriteProfileInt("App", "InfoPanel.bold", check_bold.GetCheck());
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
		m_hWnd, 0, 100, true);
	return;
}

void COptionTab2::OnBnClickedCheck3()
{
	OnApplyFont();
}