#pragma once


// CReportOption dialog

class CReportOption : public CDialog
{
	DECLARE_DYNAMIC(CReportOption)

public:
	CReportOption(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReportOption();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
