#pragma once
#include "afxwin.h"
#include "old_my_src/winwork.h"
#include "externals/mySql/ConnWorkMySql.h"
#include "OnlineAdviceModerate.h"


#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib")

// CAddOnlineAdvice dialog

class CAddOnlineAdvice : public CDialog
{
	DECLARE_DYNAMIC(CAddOnlineAdvice)
	CTrifle trif;
	ConnWorkMySql *mySql;
	string userSID;
	string getUserSID(); //https://social.msdn.microsoft.com/Forums/vstudio/en-US/6b23fff0-773b-4065-bc3f-d88ce6c81eb0/get-user-sid-in-unmanaged-c?forum=vcgeneral
	void isEnableSend();

public:
	CAddOnlineAdvice(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddOnlineAdvice();
	string path_actuser;

// Dialog Data
	enum { IDD = IDD_OnlineAdviceAdd };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit5();
	CEdit edit_nickname;
	CEdit edit_advice;
	CEdit edit_left_symbols;
	CEdit edit_author;
	afx_msg void OnEnChangeEdit3();
};
