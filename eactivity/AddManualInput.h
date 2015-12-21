#include "old_my_src/winwork.h"
#pragma once


// CAddManualInput dialog

class CAddManualInput : public CDialog
{
	DECLARE_DYNAMIC(CAddManualInput)
	CTrifle trif;

public:
	CAddManualInput(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddManualInput();
	CString sExe;
	CString sCapt;
	CString sComment;
	float SumTime;
	float UsefullTime;

// Dialog Data
	enum { IDD = IDD_SetKoefManual1 };

protected:
	CEdit	edit_comment;
	CEdit	edit_capt;
	CEdit	edit_exe;
	CEdit	edit_sum_time;
	CEdit	edit_useful_time;
	CComboBox combo_time1;
	CComboBox combo_time2;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
