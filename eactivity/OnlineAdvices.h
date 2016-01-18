#pragma once

#include "externals/mySql/ConnWorkMySql.h"
#include "externals/XHTMLStatic.h"
#include "old_my_src/winwork.h"
#include "AddOnlineAdvice.h"
#include "afxwin.h"
#include <iostream>
#include <fstream>
#include "afxcmn.h"
using namespace std;

// COnlineAdvices dialog

class COnlineAdvices : public CDialog
{
	DECLARE_DYNAMIC(COnlineAdvices)
	CTrifle trif;
	ConnWorkMySql *mySql;
	BOOL isMessageShown(int id_mes);
	void ShowMessage(int id, string message, string owner_mes, 
		string user, int moderate_type, double rate, double rate1, double rate2, 
		double rate3/*, float rate4*/);
	int id_mes;//id отображаемого сообщения, под которым оно числится в таблице text_mes
	double dRate, dRate1, dRate2, dRate3;
	bool noVote;//опция обозначающая что голосовали раньше и требовать снова голосование не стоит
	string userSID;
	BOOL abnormalExit(CString textError);

public:
	COnlineAdvices(CWnd* pParent = NULL);   // standard constructor
	virtual ~COnlineAdvices();
	string path_actuser;

// Dialog Data
	enum { IDD = IDD_OnlineAdvice };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	CXHTMLStatic stat_rate;
	afx_msg void OnBnClickedCancel();
	CButton check_details;
	afx_msg void OnBnClickedCheck1();
	virtual void OnCancel();
	CSliderCtrl slider_rate;
	CSliderCtrl slider_rate1;
	CSliderCtrl slider_rate2;
	CSliderCtrl slider_rate3;
	afx_msg void OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic stat_rate_desc;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic stat_rate_desc1;
	CStatic stat_rate_desc2;
	CStatic stat_rate_desc3;
	afx_msg void OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit edit_message;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
