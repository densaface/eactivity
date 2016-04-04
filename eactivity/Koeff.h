#include "old_my_src/winwork.h"
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "afxwin.h"
#include "NewProject.h"
#include "MoveOrCopy.h"
using namespace std;

#if !defined(AFX_KOEFF_H__23B0459C_E209_4E0C_9AA6_F5C0AC7EBBB1__INCLUDED_)
#define AFX_KOEFF_H__23B0459C_E209_4E0C_9AA6_F5C0AC7EBBB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Koeff.h : header file
//
struct sRule
{
	sRule();
	string exe;
	string capt;
	int typeRule;//будет ли учитываться заголовок
	//-1 - правило только создано и не может еще использоваться
	//0 - не будет, 
	//1 - будет, 
	//2 - частичное совпадение (для включения частичного поиска первым символом в find делать "*")
	float koef;
};
typedef map<string, sRule,  less<string> > rulSpis;

//структура, содержащая информацию о списке правил, принадлежащих определенному проекту
struct structProject
{
	rulSpis lRuls;
	string nameList;
	string listFileName;
	string comment; //Описание/комментарий к проекту
	double koef; //коэффициент полезности
};
//список файлов коэффициентов
typedef map<string, structProject,  less<string> > rulMacroList;

/////////////////////////////////////////////////////////////////////////////
// CKoeff dialog

class CKoeff : public CDialog
{
	CTrifle trif;
// Construction
public:
	CKoeff(CWnd* pParent = NULL);   // standard constructor
	rulMacroList macroRule; //структура, содержащая единственное правило, которое будет изменяться
	string oldNameProject;	//имя проекта, которое было установлено при инициализации диалога 
							//		(либо имя проекта редактируемого правила, либо первого проекта, 
							//		если правило новое)
	string oldRuleKey;
	rulMacroList allRules; //для получения имен проектов
	bool isNewRule;
	int moveOrCopy;
// 	CString exe;
// 	CString capt;
// 	CString koef;
// 	int typeExact;

// Dialog Data
	//{{AFX_DATA(CKoeff)
	enum { IDD = IDD_SetKoef };
	CComboBox	combo_exact;
	CEdit	edit_koef;
	CEdit	edit_capt;
	CEdit	edit_exe;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKoeff)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKoeff)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CComboBox comboProjectsName;
	afx_msg void OnCbnSelchangeCombo2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KOEFF_H__23B0459C_E209_4E0C_9AA6_F5C0AC7EBBB1__INCLUDED_)
