// ProjectEdit.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "ProjectEdit.h"


// CProjectEdit dialog

IMPLEMENT_DYNAMIC(CProjectEdit, CDialog)

CProjectEdit::CProjectEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectEdit::IDD, pParent)
{

}

CProjectEdit::~CProjectEdit()
{
}

void CProjectEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProjectEdit, CDialog)
	ON_BN_CLICKED(IDOK, &CProjectEdit::OnBnClickedOk)
END_MESSAGE_MAP()


// CProjectEdit message handlers
BOOL CProjectEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_EDIT1)->SetWindowText(editedProj.nameList.c_str());
	char ch[1024];
	sprintf_s(ch, "%.2f", editedProj.koef);
	GetDlgItem(IDC_EDIT2)->SetWindowText(ch);
	GetDlgItem(IDC_EDIT3)->SetWindowText(editedProj.comment.c_str());
	return TRUE;
}

void CProjectEdit::OnBnClickedOk()
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	editedProj.nameList = str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	editedProj.koef = atof(str);
	GetDlgItem(IDC_EDIT3)->GetWindowText(str);
	editedProj.comment = str;
	OnOK();
}
