// ReportTwoPeriods.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "ReportTwoPeriods.h"


// CReportTwoPeriods dialog

IMPLEMENT_DYNAMIC(CReportTwoPeriods, CDialog)

CReportTwoPeriods::CReportTwoPeriods(CWnd* pParent /*=NULL*/)
	: CDialog(CReportTwoPeriods::IDD, pParent)
{

}

CReportTwoPeriods::~CReportTwoPeriods()
{
}

void CReportTwoPeriods::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO6, radio_useful_time);
	DDX_Control(pDX, IDC_COMBO2, combo_holiday);
	DDX_Control(pDX, IDC_CHECK2, check_skip_holidays);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, date3);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, date4);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, date1);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, date2);
	DDX_Control(pDX, IDC_LIST1, listDates1);
	DDX_Control(pDX, IDC_CHECK1, check_period2);
	DDX_Control(pDX, IDC_LIST6, listDates2);
}


BEGIN_MESSAGE_MAP(CReportTwoPeriods, CDialog)
	ON_BN_CLICKED(IDOK, &CReportTwoPeriods::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK2, &CReportTwoPeriods::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK1, &CReportTwoPeriods::OnBnClickedCheck1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER3, &CReportTwoPeriods::OnDtnDatetimechangeDatetimepicker3)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER4, &CReportTwoPeriods::OnDtnDatetimechangeDatetimepicker3)
	ON_BN_CLICKED(IDC_BUTTON1, &CReportTwoPeriods::OnBnClickedButton1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CReportTwoPeriods::OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, &CReportTwoPeriods::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON2, &CReportTwoPeriods::OnBnClickedButton2)
END_MESSAGE_MAP()


BOOL CReportTwoPeriods::OnInitDialog()
{
	CDialog::OnInitDialog();
	radio_useful_time.SetCheck(timeOrActions);
	combo_holiday.AddString("1.5");
	combo_holiday.AddString("2.5");
	combo_holiday.AddString("4");
	combo_holiday.SetCurSel(0);
	check_skip_holidays.SetCheck(TRUE);
	OnBnClickedCheck2();
	OnBnClickedCheck1();
	return TRUE;
}

void CReportTwoPeriods::OnBnClickedCheck2()
{
	if (check_skip_holidays.GetCheck())
	{
		combo_holiday.EnableWindow(TRUE);
	} else {
		combo_holiday.EnableWindow(FALSE);
	}
}

void CReportTwoPeriods::OnBnClickedCheck1()
{
	if (check_period2.GetCheck())
	{
		date3.EnableWindow(TRUE);
		date4.EnableWindow(TRUE);
		listDates2.EnableWindow(TRUE);
		if (listDates2.GetCount())
			GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	} else {
		date3.EnableWindow(FALSE);
		date4.EnableWindow(FALSE);
		listDates2.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	}
}

void CReportTwoPeriods::OnDtnDatetimechangeDatetimepicker3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	CTime timeTime1, timeTime2;
	DWORD dwResult1 = date1.GetTime(timeTime1);
	DWORD dwResult2 = date2.GetTime(timeTime2);
	if (dwResult1 != GDT_VALID)
	{
		return;
	}
	if (dwResult2 != GDT_VALID)
	{
		return;
	}
	if (timeTime1>timeTime2)
	{
		return;
	}
	listDates1.ResetContent();
	CString sDate;
	do
	{
		sDate.Format("%d_%02d_%02d", timeTime1.GetYear(), timeTime1.GetMonth(), 
			timeTime1.GetDay());
		listDates1.AddString(sDate);
		timeTime1 += 60*60*24;
	} while (timeTime1<=timeTime2);
	if (listDates1.GetCount())
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	*pResult = 0;
}

void CReportTwoPeriods::OnBnClickedButton1()
{
	int curSel=listDates1.GetCurSel();
	if (curSel<0) 
		return;
	listDates1.DeleteString(curSel);
	if (listDates1.GetCount())
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
}

void CReportTwoPeriods::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	CTime timeTime1, timeTime2;
	DWORD dwResult1 = date3.GetTime(timeTime1);
	DWORD dwResult2 = date4.GetTime(timeTime2);
	if (dwResult1 != GDT_VALID)
	{
		return;
	}
	if (dwResult2 != GDT_VALID)
	{
		return;
	}
	if (timeTime1>timeTime2)
	{
		return;
	}
	listDates2.ResetContent();
	CString sDate;
	do
	{
		sDate.Format("%d_%02d_%02d", timeTime1.GetYear(), timeTime1.GetMonth(), 
			timeTime1.GetDay());
		listDates2.AddString(sDate);
		timeTime1 += 60*60*24;
	} while (timeTime1<=timeTime2);
	if (listDates1.GetCount())
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);	
	*pResult = 0;
}

void CReportTwoPeriods::OnBnClickedOk()
{
	CString str;
	for (int ii=0; ii<listDates1.GetCount(); ii++)
	{
		listDates1.GetText(ii, str);
		saDates1.Add(str);
	}
	for (int ii=0; ii<listDates2.GetCount(); ii++)
	{
		listDates2.GetText(ii, str);
		saDates2.Add(str);
	}
	combo_holiday.GetWindowText(str);
	if (check_skip_holidays.GetCheck())
	{
		thresholdHoliday = atof(str);
	} else {
		thresholdHoliday = 0;
	}
	accentParameter = radio_useful_time.GetCheck();
	OnOK();
}


void CReportTwoPeriods::OnBnClickedButton2()
{
	int curSel=listDates2.GetCurSel();
	if (curSel<0) 
		return;
	listDates2.DeleteString(curSel);
	if (listDates2.GetCount())
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
}
