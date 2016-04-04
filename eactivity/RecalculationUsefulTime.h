#pragma once


// CRecalculationUsefulTime dialog

class CRecalculationUsefulTime : public CDialog
{
	DECLARE_DYNAMIC(CRecalculationUsefulTime)

public:
	CRecalculationUsefulTime(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRecalculationUsefulTime();
	int countDaysReculc;

// Dialog Data
	enum { IDD = IDD_Recalculation };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
