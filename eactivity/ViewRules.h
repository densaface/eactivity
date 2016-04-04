#include "Koeff.h"
#include "statsfunc.h"
#include "afxwin.h"
#include "NewProject.h"
#include "ProjectEdit.h"

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
	//rulSpis rules;
	string path_actuser;
	CStringArray saKeys; //массив ключей к правилам, для однозначной идентификации при их удалении, 
	//		редактировании
	CStringArray saKeysProjs; //массив ключей к проектам, для однозначной идентификации при их удалении, 
	//		редактировании

// 	CUIntArray tormoz;
// 	UINT oldtick;
// 	UINT oldtick2;

	//список правил отдельно от списков активностей
	//при изменении какого-нибудь правила будет перетряхиваться вся статистика и для тех элементов, 
	//для которых подходит правило пересчитываться useful acts (полезные действия)

	//правило будет состоять из заголовка (ввести потом "*" в качестве замены любой группы символов)
	//из обязательного экзешника

	//приоритет правил: если есть правило с экзешником и конкретным заголовком, то оно наверху, после не считается
	//либо применяется правило с конкретным экзешником, если таковое есть
	rulMacroList GlobalRules;
	void SaveRules();
	void LoadRules();
	void LoadRuleFile(CString fileName);
	rulMacroList findRule(string ExeCapt, string exe, string capt, 
		CStringArray &saListProjs);
	rulSpis::iterator partCaptFind(string exe, string capt, rulSpis &RULES);
	float GetUsefulTimeFromExe (string exe, activ &forLoad1);
	double GetUsefulActsFromExe(string exe, activ &forLoad1);
	//rulSpis RULES;


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
	afx_msg void OnNewProject();
	afx_msg void OnEditProject();
	CComboBox comboProjectsName;
	afx_msg void OnEnChangeEditSearch();
	CEdit edit_search;
	afx_msg void OnCbnSelchangeCombo1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWRULES_H__79F7CC84_06F3_49A9_B517_417362299C4F__INCLUDED_)
