#pragma once
#include "afxwin.h"


// CReportTwoPeriods dialog

class CReportTwoPeriods : public CDialog
{
	DECLARE_DYNAMIC(CReportTwoPeriods)

public:
	CReportTwoPeriods(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReportTwoPeriods();
	int timeOrActions;
	CStringArray saDates1, saDates2;
	double thresholdHoliday;
	int accentParameter;

// Dialog Data
	enum { IDD = IDD_ReportTwoPeriods };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	CComboBox combo_holiday;
	CButton radio_useful_time;
	CButton check_skip_holidays;
	CDateTimeCtrl date1;
	CDateTimeCtrl date2;
	CDateTimeCtrl date3;
	CDateTimeCtrl date4;
	afx_msg void OnDtnDatetimechangeDatetimepicker3(NMHDR *pNMHDR, LRESULT *pResult);
	CListBox listDates1;
	afx_msg void OnBnClickedButton1();
	CButton check_period2;
	CListBox listDates2;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
};
