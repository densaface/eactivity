#pragma once
#include "afxwin.h"
#include "old_my_src/winwork.h"
#include "ListShortTodo.h"

// CGoWorkUntilPause dialog

class CGoWorkUntilPause : public CDialog
{
	DECLARE_DYNAMIC(CGoWorkUntilPause)
	CTrifle trif;
public:
	CGoWorkUntilPause(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGoWorkUntilPause();
	int typeUsefulPar;
	float UsefulActs;
	float UsefulTime;
	float UsualTime;
	string path_actuser;
	CString textMes;
	BOOL shortTodo;
	int typeShowBreak;

// Dialog Data
	enum { IDD = IDD_START_WORK_UNTIL_PAUSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	CEdit edit_usefulacts;
	CButton radio_usefulacts;
	CButton radio_usefultime;
	CEdit edit_usefultime;
	afx_msg void OnBnClickedRadio1();
	CComboBox combo_type_time;
	afx_msg void OnBnClickedButton1();
	CButton check_text_mes;
	CEdit edit_text_mes;
	CButton check_short_todo;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnEnChangeEdit1();
	CButton radio_usual_time;
	CEdit edit_usualtime;
	CComboBox combo_show_break;
};
