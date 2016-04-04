#pragma once


// CNewProject dialog

class CNewProject : public CDialog
{
	DECLARE_DYNAMIC(CNewProject)

public:
	CNewProject(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewProject();
	CString nameProject;
	CString coefUseful;

// Dialog Data
	enum { IDD = IDD_ProjectNew };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
};
