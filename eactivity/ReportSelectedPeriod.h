#pragma once
#include "afxwin.h"
#include "statsfunc.h"
#include <string>
using namespace std;
#define DAY 10 //������� �������� � ����������� ��� "2015_11_25"
#define MON 7  //������� �������� � ����������� ������ "2015_11"


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
	CStringArray saDates;//������ ������ ��� ���������
	CStringArray saDates2;//������ ������ ��� ���������
	string path_actuser;//����� ��� �������� ����� � ����������� ������������

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
