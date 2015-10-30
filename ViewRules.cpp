// ViewRules.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "ViewRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewRules dialog


CViewRules::CViewRules(CWnd* pParent /*=NULL*/)
	: CDialog(CViewRules::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewRules)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewRules::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewRules)
	DDX_Control(pDX, IDC_LIST3, list_rules);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewRules, CDialog)
	//{{AFX_MSG_MAP(CViewRules)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkList3)
	ON_BN_CLICKED(IDC_BUTTON1, OnDelRul)
	ON_BN_CLICKED(IDC_BUTTON2, OnEditRule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewRules message handlers

BOOL CViewRules::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1629));
	SetWindowText(str);
	
	list_rules.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | list_rules.GetExtendedStyle());
	str.LoadString(trif.GetIds(IDS_STRING1625));
	list_rules.InsertColumn(0, str);
	list_rules.InsertColumn(1, "Exe");
	list_rules.InsertColumn(2, "Caption");
	str.LoadString(trif.GetIds(IDS_STRING1627));
	list_rules.InsertColumn(3, str);
	list_rules.SetColumnWidth(0,120);
	list_rules.SetColumnWidth(1,100);
	list_rules.SetColumnWidth(2,150);
	list_rules.SetColumnWidth(3,80);
	

	int ii=0;
	for (rulSpis::iterator iter=rules.begin(); iter!=rules.end(); iter++)
	{
		//string debs=tmpForSave.exe;
		switch((*iter).second.typeRule)
		{
		case 0:
			str.LoadString(trif.GetIds(IDS_STRING1579));
			break;
		case 1:
			str.LoadString(trif.GetIds(IDS_STRING1577));
			break;
		case 2:
			str.LoadString(trif.GetIds(IDS_STRING1597));
			break;
		}
		list_rules.InsertItem(ii, str);
		list_rules.SetItemText(ii, 1, (*iter).second.exe.c_str());
		list_rules.SetItemText(ii, 2, (*iter).second.capt.c_str());
		char ch[100];
		sprintf_s(ch, "%0.2f", (*iter).second.koef);
		list_rules.SetItemText(ii, 3, ch);
		ii++;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewRules::OnDelRul() 
{
	POSITION pos=list_rules.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	if (AfxMessageBox(trif.GetIds(IDS_STRING1581), MB_YESNO)!=IDYES)
		return;
	rulSpis::iterator pRule_tmp=rules.begin();
	for (int ii=0; ii<sel; ii++)
		pRule_tmp++;

// 	string exe=(*pRule_tmp).second.exe;
// 	if ((*pRule_tmp).second.typeRule!=0)
// 		exe+='\t'+(*pRule_tmp).second.capt;
// 	rulSpis::iterator pRule_tmp=rules.find(exe);
// 	if (pRule_tmp==rules.end())
// 		return;
	rules.erase(pRule_tmp);
	list_rules.DeleteItem(sel);
}

void CViewRules::OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnEditRule();
	*pResult = 0;
}

void CViewRules::OnEditRule() 
{
	POSITION pos=list_rules.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	rulSpis::iterator pRule_tmp=rules.begin();
	for (int ii=0; ii<sel; ii++)
		pRule_tmp++;
	
	CKoeff koef;
	koef.tmpRule=(*pRule_tmp).second;
	string capt=koef.tmpRule.capt;
	// 		.exe=list_rules.GetItemText(sel, 1).GetBuffer(2048);
	// 	koef.tmpRule.capt=list_rules.GetItemText(sel, 2).GetBuffer(2048);
	// 	koef.tmpRule.koef=atof(list_rules.GetItemText(sel, 3).GetBuffer(100));
	// 	koef.tmpRule.typeRule=0;
	// 	CString strtext=list_rules.GetItemText(sel, 0);
	CString str1, str2, str3;
	str1.LoadString(trif.GetIds(IDS_STRING1579));
	str2.LoadString(trif.GetIds(IDS_STRING1577));
	str3.LoadString(trif.GetIds(IDS_STRING1597));
	// 	if (strtext==str2)
	// 		koef.tmpRule.typeRule=1;
	// 	else 
	// 		if (strtext==str3)
	// 			koef.tmpRule.typeRule=2;
	
	//ищем связанное правило и берем из него коэффициент
	string exe=koef.tmpRule.exe;
	if (koef.DoModal()!=IDOK)
		return;
	//	rulSpis::iterator pRule_tmp=rules.find(exe);
	if (pRule_tmp==rules.end()) //создаем новое правило
	{
		AfxMessageBox("Rule Error");
		// 		rules[koef.tmpRule.exe]=koef.tmpRule;
		// 		pRule_tmp=rules.find(koef.tmpRule.exe);
		// 		pRule_tmp--;//привязываем правило к соответствующему элементу
	} else {
		if (koef.tmpRule.typeRule==2 && capt!=koef.tmpRule.capt)
		{	//изменился заголовок частичного поиска, значит стираем старое правило и вставляем его как новое
			rules.erase(koef.tmpRule.exe+'\t'+capt);
			rules[koef.tmpRule.exe+'\t'+koef.tmpRule.capt]=koef.tmpRule;
			list_rules.SetItemText(sel, 2, koef.tmpRule.capt.c_str());
		} else {
			(*pRule_tmp).second.koef=koef.tmpRule.koef;
			char ch[100];
			sprintf_s(ch, "%0.2f", koef.tmpRule.koef);
			list_rules.SetItemText(sel, 3, ch);
			(*pRule_tmp).second.capt=koef.tmpRule.capt;
			list_rules.SetItemText(sel, 2, koef.tmpRule.capt.c_str());
			(*pRule_tmp).second.typeRule=koef.tmpRule.typeRule;
		}
		switch(koef.tmpRule.typeRule)
		{
		case 0:
			list_rules.SetItemText(sel, 0, str1);
			break;
		case 1:
			list_rules.SetItemText(sel, 0, str2);
			break;
		case 2:
			list_rules.SetItemText(sel, 0, str3);
			break;
		}
	}
}
