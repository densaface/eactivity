// eactivity.h : main header file for the EACTIVITY application
//

#if !defined(AFX_EACTIVITY_H__AAEBAB2A_4FFA_4DF6_A65E_0DCF3F860779__INCLUDED_)
#define AFX_EACTIVITY_H__AAEBAB2A_4FFA_4DF6_A65E_0DCF3F860779__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEactivityApp:
// See eactivity.cpp for the implementation of this class
//

class CEactivityApp : public CWinApp
{
public:
	CEactivityApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEactivityApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEactivityApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EACTIVITY_H__AAEBAB2A_4FFA_4DF6_A65E_0DCF3F860779__INCLUDED_)
