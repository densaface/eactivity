// Koeff.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "Koeff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKoeff dialog


CKoeff::CKoeff(CWnd* pParent /*=NULL*/)
	: CDialog(CKoeff::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKoeff)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CKoeff::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKoeff)
	DDX_Control(pDX, IDC_COMBO1, combo_exact);
	DDX_Control(pDX, IDC_EDIT5, edit_koef);
	DDX_Control(pDX, IDC_EDIT3, edit_capt);
	DDX_Control(pDX, IDC_EDIT1, edit_exe);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKoeff, CDialog)
	//{{AFX_MSG_MAP(CKoeff)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelChangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKoeff message handlers

void CKoeff::OnOK() 
{
	char ch[2048];
	edit_exe.GetWindowText(ch, 2048);
	tmpRule.exe=ch;
	edit_capt.GetWindowText(ch, 2048);
	tmpRule.capt=ch;
	edit_koef.GetWindowText(ch, 2048);
	tmpRule.koef=(float)atof(ch);
	switch(combo_exact.GetCurSel())
	{
	case 0:
		if (combo_exact.IsWindowEnabled())
			 tmpRule.typeRule=1;
		else tmpRule.typeRule=0;
	    break;
	case 1:
		tmpRule.typeRule=2;
	    break;
	}
	CDialog::OnOK();
}

BOOL CKoeff::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1615));
	SetWindowText(str);
	str.LoadString(trif.GetIds(IDS_STRING1617));
	GetDlgItem(IDC_STATIC_coef)->SetWindowText(str);
	str.LoadString(trif.GetIds(IDS_STRING1619));
	GetDlgItem(IDC_STATIC_sovp)->SetWindowText(str);

	combo_exact.ResetContent();
	str.LoadString(trif.GetIds(IDS_STRING1621));
	combo_exact.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1623));
	combo_exact.AddString(str);

	edit_exe.SetWindowText(tmpRule.exe.c_str());
	edit_capt.SetWindowText(tmpRule.capt.c_str());
	char ch[300];
	sprintf_s(ch, "%0.2f", tmpRule.koef);
	edit_koef.SetWindowText(ch);
	switch(tmpRule.typeRule)
	{
	case 0:
		combo_exact.EnableWindow(false);
	case 1:
		combo_exact.SetCurSel(0);
		break;
	case 2:
		combo_exact.EnableWindow(true);
		edit_capt.EnableWindow(true);
		combo_exact.SetCurSel(1);
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKoeff::OnSelChangeCombo1() 
{
	if (combo_exact.GetCurSel())
		 edit_capt.EnableWindow(true);
	else edit_capt.EnableWindow(false);
}
