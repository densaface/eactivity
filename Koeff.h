#include "winwork.h"
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#if !defined(AFX_KOEFF_H__23B0459C_E209_4E0C_9AA6_F5C0AC7EBBB1__INCLUDED_)
#define AFX_KOEFF_H__23B0459C_E209_4E0C_9AA6_F5C0AC7EBBB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Koeff.h : header file
//
struct sRule //: public std::binary_function<std::string, std::string, bool>
{
// 	bool operator()(const std::string &s1, const std::string &s2) const
// 	{
// 		bool res;//для отладки
// 		if (s2[0]=='*') //включение частичного поиска
// 		{
// 			res=(s1==s2.substr(1, s2.length()-1));
// 			if (!res)
// 				return false;
// 			res=s1.find(s2.substr(1, s2.length()-1))==-1;
// 			return res;
// 		}
// 		res=(strcmp(s1.c_str(), s2.c_str())<0);
// 		return res;
// 	}
	string exe;
	string capt;
	int typeRule;//будет ли учитываться заголовок
	//0 - не будет, 
	//1 - будет, 
	//2 - частичное совпадение (для включения частичного поиска первым символом в find делать "*")
	float koef;
};

typedef map<string, sRule,  less<string> > rulSpis;

/////////////////////////////////////////////////////////////////////////////
// CKoeff dialog

class CKoeff : public CDialog
{
	CTrifle trif;
// Construction
public:
	CKoeff(CWnd* pParent = NULL);   // standard constructor
	sRule tmpRule;
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KOEFF_H__23B0459C_E209_4E0C_9AA6_F5C0AC7EBBB1__INCLUDED_)
