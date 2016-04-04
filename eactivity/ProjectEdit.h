#include "Koeff.h"
#pragma once


// CProjectEdit dialog

class CProjectEdit : public CDialog
{
	DECLARE_DYNAMIC(CProjectEdit)

public:
	CProjectEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjectEdit();
	structProject editedProj;

// Dialog Data
	enum { IDD = IDD_ProjectEdit };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
