#include "Koeff.h"

#if !defined(AFX_VIEWRULES_H__79F7CC84_06F3_49A9_B517_417362299C4F__INCLUDED_)
#define AFX_VIEWRULES_H__79F7CC84_06F3_49A9_B517_417362299C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewRules.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewRules dialog

class CViewRules : public CDialog
{
// Construction
		CTrifle trif;
public:
	CViewRules(CWnd* pParent = NULL);   // standard constructor
	rulSpis rules;

// Dialog Data
	//{{AFX_DATA(CViewRules)
	enum { IDD = IDD_Rules };
	CListCtrl	list_rules;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewRules)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewRules)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelRul();
	afx_msg void OnEditRule();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWRULES_H__79F7CC84_06F3_49A9_B517_417362299C4F__INCLUDED_)
