// ReportOption.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "ReportOption.h"


// CReportOption dialog

IMPLEMENT_DYNAMIC(CReportOption, CDialog)

CReportOption::CReportOption(CWnd* pParent /*=NULL*/)
	: CDialog(CReportOption::IDD, pParent)
{

}

CReportOption::~CReportOption()
{
}

void CReportOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReportOption, CDialog)
	ON_BN_CLICKED(IDOK, &CReportOption::OnBnClickedOk)
END_MESSAGE_MAP()


// CReportOption message handlers

void CReportOption::OnBnClickedOk()
{
	OnOK();
}
