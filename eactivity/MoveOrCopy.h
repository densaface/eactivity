#pragma once

#define MOVERULE 5
#define COPYRULE 10

// CMoveOrCopy dialog

class CMoveOrCopy : public CDialog
{
	DECLARE_DYNAMIC(CMoveOrCopy)

public:
	CMoveOrCopy(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMoveOrCopy();
	int resultQuery;

// Dialog Data
	enum { IDD = IDD_RuleMoveOrCopy };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk3();
};
