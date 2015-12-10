// ReportOption.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "ReportOption.h"


// CReportOption dialog

IMPLEMENT_DYNAMIC(CReportOption, CDialog)

CReportOption::CReportOption(CWnd* pParent /*=NULL*/)
	: CDialog(CReportOption::IDD, pParent)
{

}

CReportOption::~CReportOption()
{
}

void CReportOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO22, radio_use_period);
	DDX_Control(pDX, IDC_RADIO5, radio_use_last_days);
	DDX_Control(pDX, IDC_RADIO3, radio_useful_time);
	DDX_Control(pDX, IDC_COMBO2, combo_holiday);
	DDX_Control(pDX, IDC_CHECK1, check_skip_holidays);
	DDX_Control(pDX, IDC_COMBO1, combo_last_days);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, date1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, date2);
}


BEGIN_MESSAGE_MAP(CReportOption, CDialog)
	ON_BN_CLICKED(IDOK, &CReportOption::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO5, &CReportOption::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO22, &CReportOption::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_CHECK1, &CReportOption::OnBnClickedCheck1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CReportOption::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, &CReportOption::OnDtnDatetimechangeDatetimepicker2)
END_MESSAGE_MAP()


BOOL CReportOption::OnInitDialog()
{
	CDialog::OnInitDialog();
	combo_last_days.AddString("5");
	combo_last_days.AddString("10");
	combo_last_days.AddString("20");
	combo_last_days.SetCurSel(0);
	radio_use_last_days.SetCheck(TRUE);
	OnBnClickedRadio1();
	radio_useful_time.SetCheck(timeOrActions);
	combo_holiday.AddString("1.5");
	combo_holiday.AddString("2.5");
	combo_holiday.AddString("4");
	combo_holiday.SetCurSel(0);
	check_skip_holidays.SetCheck(TRUE);
	OnBnClickedCheck1();
	return TRUE;
}

void CReportOption::OnBnClickedOk()
{
	CString str;
	combo_holiday.GetWindowText(str);
	if (check_skip_holidays.GetCheck())
	{
		thresholdHoliday = atof(str);
	} else {
		thresholdHoliday = 0;
	}
	accentParameter = radio_useful_time.GetCheck();
	if (radio_use_last_days.GetCheck())
	{
		combo_last_days.GetWindowText(str);
		useLastDays = atoi(str);
	} else {
		useLastDays=0;
		CTime timeTime1, timeTime2;
		DWORD dwResult1 = date1.GetTime(timeTime1);
		DWORD dwResult2 = date2.GetTime(timeTime2);
		if (dwResult1 != GDT_VALID)
		{
			AfxMessageBox(_T("Date1 not set!"));
			return;
		}
		if (dwResult2 != GDT_VALID)
		{
			AfxMessageBox(_T("Date2 not set!"));
			return;
		}
		if (timeTime1>timeTime2)
		{
			AfxMessageBox(_T("Date1 should be less than Date2!"));
			return;
		}
		CString sDate;
		do
		{
			sDate.Format("%d_%02d_%02d", timeTime1.GetYear(), timeTime1.GetMonth(), 
				timeTime1.GetDay());
			saDates.Add(sDate);
			timeTime1 += 60*60*24;
		} while (timeTime1<timeTime2);
	}

	OnOK();
}

void CReportOption::OnBnClickedRadio1()
{
	if (radio_use_last_days.GetCheck())
	{
		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(FALSE);
	} else {
		GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(TRUE);
	}
}
void CReportOption::OnBnClickedCheck1()
{
	if (check_skip_holidays.GetCheck())
	{
		combo_holiday.EnableWindow(TRUE);
	} else {
		combo_holiday.EnableWindow(FALSE);
	}
}

void CReportOption::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
// 	CTime timeTime;
// 	DWORD dwResult = date1.GetTime(timeTime);
// 	if (dwResult != GDT_VALID)
// 		return;
// 	COleDateTime dtMin = COleDateTime(timeTime.GetYear(), timeTime.GetMonth(), 
// 		timeTime.GetDay(), 0, 0, 0);
// 	COleDateTime dtMax = COleDateTime::GetCurrentTime();
// 	date2.SetRange(&dtMin, &dtMax);
	*pResult = 0;
}

void CReportOption::OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
// 	CTime timeTime;
// 	DWORD dwResult = date2.GetTime(timeTime);
// 	if (dwResult != GDT_VALID)
// 		return;
// 	COleDateTime dtMax = COleDateTime(timeTime.GetYear(), timeTime.GetMonth(), 
// 		timeTime.GetDay(), 0, 0, 0);
// 	COleDateTime dtMin;
// 	dtMin.SetStatus(COleDateTime::null);
// 	date2.SetRange(&dtMin, &dtMax);
	*pResult = 0;
}
