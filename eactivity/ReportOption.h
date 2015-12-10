#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CReportOption dialog

class CReportOption : public CDialog
{
	DECLARE_DYNAMIC(CReportOption)

public:
	CReportOption(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReportOption();
	BOOL timeOrActions;
	double thresholdHoliday;
	int useLastDays;
	CStringArray saDates;
	int accentParameter;

// Dialog Data
	enum { IDD = IDD_ReportOption };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio1();
	CButton radio_use_period;
	CButton radio_use_last_days;
	CButton radio_useful_time;
	afx_msg void OnBnClickedCheck1();
	CComboBox combo_holiday;
	CButton check_skip_holidays;
	CComboBox combo_last_days;
	CDateTimeCtrl date1;
	CDateTimeCtrl date2;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult);
};
