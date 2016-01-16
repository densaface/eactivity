#pragma once
#include "StatsFunc.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "ListShortTodo.h"

// CEndWork dialog

class CEndWork : public CDialog
{
	DECLARE_DYNAMIC(CEndWork)
	StatsFunc statF;
	CTrifle trif;
	void Competition();
	CString getRandomShortAction(CString& sGroup, CString& sLink, CString& sProg, UINT& uniq);
	bool WriteJournal(LPCTSTR lpszFormat, ...);
	DWORD startPause;
public:
	string path_actuser;
	CEndWork(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEndWork();
	float usefulTime;
	int   usefulActs;
	int   summonTime;
	int   pauseCount;
	CString sAction;
	CString sGroup;
	CString sLink;
	CString sProg;
	UINT uniq;
	CString textMes;
	BOOL shortTodo;
	BOOL onlineAdvice;
	bool highLight;

// Dialog Data
	enum { IDD = IDD_END_WORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnBnClickedOk();
	void WriteStatisticWorkPeriod();
	CXHTMLStatic stat_usefulacts;
	CXHTMLStatic stat_usefultime;

	DECLARE_MESSAGE_MAP()
	CXHTMLStatic stat_summon_time;
	CXHTMLStatic stat_percent_time;
	CXHTMLStatic stat_res_acts;
	CXHTMLStatic stat_pauses;
	afx_msg void OnTimer(UINT nIDEvent);
	CComboBox combo_pause;
	CProgressCtrl progressTimePause;
	CXHTMLStatic static_time_pause;
	afx_msg void OnBnClickedButton1();
	CXHTMLStatic stat_short_todo;
	CStatic stat_desc1;
	CButton check_show_stat;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton4();
};
