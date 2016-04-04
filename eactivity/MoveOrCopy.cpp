// MoveOrCopy.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "MoveOrCopy.h"


// CMoveOrCopy dialog

IMPLEMENT_DYNAMIC(CMoveOrCopy, CDialog)

CMoveOrCopy::CMoveOrCopy(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveOrCopy::IDD, pParent)
{

}

CMoveOrCopy::~CMoveOrCopy()
{
}

void CMoveOrCopy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMoveOrCopy, CDialog)
	ON_BN_CLICKED(IDOK, &CMoveOrCopy::OnBnClickedOk)
	ON_BN_CLICKED(IDOK3, &CMoveOrCopy::OnBnClickedOk3)
END_MESSAGE_MAP()


// CMoveOrCopy message handlers

void CMoveOrCopy::OnBnClickedOk()
{
	resultQuery = MOVERULE;
	OnOK();
}

void CMoveOrCopy::OnBnClickedOk3()
{
	resultQuery = COPYRULE;
	OnOK();
}
