// NewProject.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "NewProject.h"


// CNewProject dialog

IMPLEMENT_DYNAMIC(CNewProject, CDialog)

CNewProject::CNewProject(CWnd* pParent /*=NULL*/)
	: CDialog(CNewProject::IDD, pParent)
{

}

CNewProject::~CNewProject()
{
}

void CNewProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewProject, CDialog)
	ON_BN_CLICKED(IDOK, &CNewProject::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CNewProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_EDIT2)->SetWindowText("1.00");
	return TRUE;
}

void CNewProject::OnBnClickedOk()
{
	GetDlgItem(IDC_EDIT1)->GetWindowText(nameProject);
	GetDlgItem(IDC_EDIT2)->GetWindowText(coefUseful);
	OnOK();
}
