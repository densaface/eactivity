// AddManualInput.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "AddManualInput.h"


// CAddManualInput dialog

IMPLEMENT_DYNAMIC(CAddManualInput, CDialog)

CAddManualInput::CAddManualInput(CWnd* pParent /*=NULL*/)
	: CDialog(CAddManualInput::IDD, pParent)
{

}

CAddManualInput::~CAddManualInput()
{
}

void CAddManualInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, edit_comment);
	DDX_Control(pDX, IDC_EDIT3, edit_capt);
	DDX_Control(pDX, IDC_EDIT1, edit_exe);
	DDX_Control(pDX, IDC_EDIT8, edit_useful_time);
	DDX_Control(pDX, IDC_EDIT5, edit_sum_time);
	DDX_Control(pDX, IDC_COMBO1, combo_time1);
	DDX_Control(pDX, IDC_COMBO2, combo_time2);
}


BEGIN_MESSAGE_MAP(CAddManualInput, CDialog)
	ON_BN_CLICKED(IDOK, &CAddManualInput::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CAddManualInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1693));
	SetWindowText(str);
	sExe = str;
	sCapt = sCapt;
	edit_exe.SetWindowText(sExe);
	edit_capt.SetWindowText(sCapt);

	str.LoadString(trif.GetIds(IDS_STRING1695));
	combo_time1.AddString(str);
	combo_time2.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1697));
	combo_time1.AddString(str);
	combo_time2.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1699));
	combo_time1.AddString(str);
	combo_time2.AddString(str);
	combo_time1.SetCurSel(2);
	combo_time2.SetCurSel(2);
	edit_sum_time.SetWindowText("1");
	edit_useful_time.SetWindowText("1");
	return TRUE;
}
void CAddManualInput::OnBnClickedOk()
{
	CString str;
	edit_sum_time.GetWindowText(str);
	switch (combo_time1.GetCurSel())
	{
	case 0:
		SumTime = (float)atof(str)*1000;
		break;
	case 1:
		SumTime = (float)atof(str)*60*1000;
		break;
	case 2:
		SumTime = (float)atof(str)*3600*1000;
		break;
	}
	edit_useful_time.GetWindowText(str);
	switch (combo_time2.GetCurSel())
	{
	case 0:
		UsefullTime = (float)atof(str)*1000;
		break;
	case 1:
		UsefullTime = (float)atof(str)*60*1000;
		break;
	case 2:
		UsefullTime = (float)atof(str)*3600*1000;
		break;
	}

	char ch[2048];
	edit_comment.GetWindowText(ch, 2048);
	sComment=ch;
	if (sComment.Find("\t")>-1)
	{
		AfxMessageBox("Комментарий не должен содержать знаки табуляции");
		sComment="";
		return;
	}
	if (sComment=="")
		sComment = "Manual Input";
	edit_exe.GetWindowText(ch, 2048);
	sExe=ch;
	edit_capt.GetWindowText(ch, 2048);
	sCapt=ch;
	OnOK();
}
