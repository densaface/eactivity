// TabOption.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "TabOption.h"
#include "externals/options/HighColorTab.hpp"

// CTabOption

IMPLEMENT_DYNAMIC(CTabOption, CPropertySheet)

CTabOption::CTabOption(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CTabOption::CTabOption(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CTabOption::~CTabOption()
{
}


BEGIN_MESSAGE_MAP(CTabOption, CPropertySheet)
END_MESSAGE_MAP()

BOOL CTabOption::OnInitDialog()
{
	CPropertySheet::OnInitDialog();
	HighColorTab::UpdateImageList( *this );
	return TRUE;
}

// CTabOption message handlers
