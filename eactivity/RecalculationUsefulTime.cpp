// RecalculationUsefulTime.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "RecalculationUsefulTime.h"


// CRecalculationUsefulTime dialog

IMPLEMENT_DYNAMIC(CRecalculationUsefulTime, CDialog)

CRecalculationUsefulTime::CRecalculationUsefulTime(CWnd* pParent /*=NULL*/)
	: CDialog(CRecalculationUsefulTime::IDD, pParent)
{

}

CRecalculationUsefulTime::~CRecalculationUsefulTime()
{
}

void CRecalculationUsefulTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecalculationUsefulTime, CDialog)
	ON_BN_CLICKED(IDOK, &CRecalculationUsefulTime::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CRecalculationUsefulTime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_EDIT1)->SetWindowText("30");
	return TRUE;
}

void CRecalculationUsefulTime::OnBnClickedOk()
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	countDaysReculc = atoi(str);
	OnOK();
}
