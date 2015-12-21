#include "old_my_src/winwork.h"
#pragma once


// CSetKoefManual dialog

class CSetKoefManual : public CDialog
{
	DECLARE_DYNAMIC(CSetKoefManual)

	CTrifle trif;
public:
	CSetKoefManual(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetKoefManual();
	CString sCaptNew, sExeNew, sExeOld;
	CStringArray sCaptOld;
	CString sComment;
	double dCoef;
	bool bMultiSel;
	bool bUnit;

// Dialog Data
	enum { IDD = IDD_SetKoefManual };

protected:
	CEdit	edit_comment;
	CEdit	edit_koef;
	CEdit	edit_capt;
	CEdit	edit_exe;
	CButton	check_unit;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckUnit();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
