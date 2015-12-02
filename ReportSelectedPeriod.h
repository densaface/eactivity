#pragma once
#include "afxwin.h"
#include "statsfunc.h"
#include <string>
using namespace std;
#define DAY 10 //сколько символов в обозначении дн€ "2015_11_25"
#define MON 7  //сколько символов в обозначении мес€ца "2015_11"


// CReportSelectedPeriod dialog

class CReportSelectedPeriod : public CDialog
{
	DECLARE_DYNAMIC(CReportSelectedPeriod)
	virtual BOOL OnInitDialog();
	StatsFunc statsF;
	void AddToListOffers(CString newItem);

public:
	CReportSelectedPeriod(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReportSelectedPeriod();
	CStringArray saDates;//первый список дл€ сравнени€
	CStringArray saDates2;//второй список дл€ сравнени€
	string path_actuser;//папка где хран€тс€ файлы с активностью пользовател€

// Dialog Data
	enum { IDD = IDD_Report };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox listMainDates;
	CListBox listComparedDates;
	CComboBox comboMon;
	CListBox listOffers;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
