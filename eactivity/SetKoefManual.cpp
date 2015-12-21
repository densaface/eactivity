// SetKoefManual.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "SetKoefManual.h"


// CSetKoefManual dialog

IMPLEMENT_DYNAMIC(CSetKoefManual, CDialog)

CSetKoefManual::CSetKoefManual(CWnd* pParent /*=NULL*/)
	: CDialog(CSetKoefManual::IDD, pParent)
{

}

CSetKoefManual::~CSetKoefManual()
{
}

void CSetKoefManual::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT5, edit_koef);
	DDX_Control(pDX, IDC_EDIT7, edit_comment);
	DDX_Control(pDX, IDC_EDIT3, edit_capt);
	DDX_Control(pDX, IDC_EDIT1, edit_exe);
	DDX_Control(pDX, IDC_CHECKUNIT, check_unit);
}


BEGIN_MESSAGE_MAP(CSetKoefManual, CDialog)
	ON_BN_CLICKED(IDOK, &CSetKoefManual::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECKUNIT, &CSetKoefManual::OnBnClickedCheckUnit)
END_MESSAGE_MAP()

BOOL CSetKoefManual::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1693));
	SetWindowText(str);
	str.LoadString(trif.GetIds(IDS_STRING1617));
	GetDlgItem(IDC_STATIC_coef)->SetWindowText(str);

	edit_exe.SetWindowText(sExeOld);
	edit_capt.SetWindowText(sCaptOld[0]);
	char ch[300];
	sprintf_s(ch, "%0.2f", 1.0);
	edit_koef.SetWindowText(ch);
	edit_comment.SetWindowText(sComment);

	if (!bMultiSel)
	{
		check_unit.EnableWindow(false);
		check_unit.ShowWindow(SW_HIDE);
	} else {
		edit_capt .EnableWindow(false);
	}
	return TRUE;
}

void CSetKoefManual::OnBnClickedOk()
{
	char ch[2048];
	edit_comment.GetWindowText(ch, 2048);
	sComment=ch;
	if (sComment.Find("\t")>-1)
	{
		AfxMessageBox("Комментарий не должен содержать знаки табуляции");
		sComment="";
		return;
	}
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1701));
	if (sComment=="")
		sComment = str;
	edit_exe.GetWindowText(ch, 2048);
	sExeNew=ch;
	edit_capt.GetWindowText(ch, 2048);
	sCaptNew=ch;
	edit_koef.GetWindowText(ch, 2048);
	dCoef=atof(ch);
	bUnit = check_unit.GetCheck() ? true : false;
	CDialog::OnOK();
}

void CSetKoefManual::OnBnClickedCheckUnit()
{
	if (check_unit.GetCheck())
	{
		edit_capt.EnableWindow(true);
	} else {
		edit_capt.EnableWindow(false);
	}
}
