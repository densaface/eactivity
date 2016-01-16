#pragma once
#include "externals/mySql/ConnWorkMySql.h"
#include "old_my_src/winwork.h"
#include "afxwin.h"
#include "afxcmn.h"


// COnlineAdviceModerate dialog

class COnlineAdviceModerate : public CDialog
{
	DECLARE_DYNAMIC(COnlineAdviceModerate)
	int curIndex;
	CTrifle trif;
	void UpdateControls();

public:
	COnlineAdviceModerate(CWnd* pParent = NULL);   // standard constructor
	virtual ~COnlineAdviceModerate();
	CUIntArray rate1;
	CUIntArray rate2;
	CUIntArray rate3;
	mysql_row *myRows;

// Dialog Data
	enum { IDD = IDD_OnlineAdviceModerate };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedVote();
	CEdit edit_mes;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk3();
	CSliderCtrl slider_rate1;
	CSliderCtrl slider_rate2;
	CSliderCtrl slider_rate3;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CStatic stat_rate_desc1;
	CStatic stat_rate_desc2;
public:
	CStatic stat_rate_desc3;
};
