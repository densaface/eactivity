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
	int typeRule;//����� �� ����������� ���������
	//-1 - ������� ������ ������� � �� ����� ��� ��������������
	//0 - �� �����, 
	//1 - �����, 
	//2 - ��������� ���������� (��� ��������� ���������� ������ ������ �������� � find ������ "*")
	float koef;
};
typedef map<string, sRule,  less<string> > rulSpis;

//���������, ���������� ���������� � ������ ������, ������������� ������������� �������
struct structProject
{
	rulSpis lRuls;
	string nameList;
	string listFileName;
	string comment; //��������/����������� � �������
	double koef; //����������� ����������
};
//������ ������ �������������
typedef map<string, structProject,  less<string> > rulMacroList;

/////////////////////////////////////////////////////////////////////////////
// CKoeff dialog

class CKoeff : public CDialog
{
	CTrifle trif;
// Construction
public:
	CKoeff(CWnd* pParent = NULL);   // standard constructor
	rulMacroList macroRule; //���������, ���������� ������������ �������, ������� ����� ����������
	string oldNameProject;	//��� �������, ������� ���� ����������� ��� ������������� ������� 
							//		(���� ��� ������� �������������� �������, ���� ������� �������, 
							//		���� ������� �����)
	string oldRuleKey;
	rulMacroList allRules; //��� ��������� ���� ��������
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
