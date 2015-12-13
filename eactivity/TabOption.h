#pragma once



// CTabOption

class CTabOption : public CPropertySheet
{
	DECLARE_DYNAMIC(CTabOption)

public:
	CTabOption(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTabOption(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CTabOption();
	virtual BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
};


