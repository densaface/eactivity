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
	moveOrCopy = MOVERULE;
}

sRule::sRule()
{
	typeRule = -1;
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
	DDX_Control(pDX, IDC_COMBO2, comboProjectsName);
}


BEGIN_MESSAGE_MAP(CKoeff, CDialog)
	//{{AFX_MSG_MAP(CKoeff)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelChangeCombo1)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO2, &CKoeff::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKoeff message handlers
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
	if (isNewRule)
		str.LoadString(trif.GetIds(IDS_STRING1911));
	else
		str.LoadString(trif.GetIds(IDS_STRING1909));
	SetWindowText(str);

	sRule rule = macroRule.begin()->second.lRuls.begin()->second;
	edit_exe.SetWindowText(rule.exe.c_str());
	edit_capt.SetWindowText(rule.capt.c_str());
	char ch[300];
	sprintf_s(ch, "%0.2f", rule.koef);
	edit_koef.SetWindowText(ch);
	switch(rule.typeRule)
	{
	case 0:
		combo_exact.EnableWindow(false);
		break;
	case 1:
		combo_exact.SetCurSel(0);
		break;
	case 2:
		combo_exact.EnableWindow(true);
		edit_capt.EnableWindow(true);
		combo_exact.SetCurSel(1);
		break;
	}

	oldNameProject = macroRule.begin()->first;
	oldRuleKey = macroRule[oldNameProject].lRuls.begin()->first;

	for (rulMacroList::iterator indListRules=allRules.begin(); 
		indListRules!=allRules.end(); indListRules++)
	{
		int indRow;
		if (indListRules->second.nameList=="")
			indRow = comboProjectsName.AddString(indListRules->first.c_str());
		else 
			indRow = comboProjectsName.AddString(indListRules->second.nameList.c_str());
		if (oldNameProject == indListRules->first)
			comboProjectsName.SetCurSel(indRow);
	}
	str.LoadString(trif.GetIds(IDS_STRING1907));
	comboProjectsName.AddString(str);
	if (isNewRule)
	{
		comboProjectsName.SetCurSel(0);
		comboProjectsName.GetLBText(0, str);
		oldNameProject = str;
	}
	return TRUE;
}

void CKoeff::OnOK() 
{
	char ch[2048];
	sRule rule = macroRule.begin()->second.lRuls.begin()->second;
	edit_exe.GetWindowText(ch, 2048);
	rule.exe=ch;
	edit_capt.GetWindowText(ch, 2048);
	rule.capt=ch;
	edit_koef.GetWindowText(ch, 2048);
	rule.koef=(float)atof(ch);
	switch(combo_exact.GetCurSel())
	{
	case 0:
		if (combo_exact.IsWindowEnabled())
			 rule.typeRule=1;
		else rule.typeRule=0;
	    break;
	case 1:
		rule.typeRule=2;
	    break;
	}
	string exeCapt = rule.exe;
	if (rule.capt!="")
		exeCapt += "\t"+rule.capt;

	//сохраняем имя проекта
	CString newProjectName;
	ASSERT(comboProjectsName.GetCurSel()!=-1);
	comboProjectsName.GetLBText(comboProjectsName.GetCurSel(), newProjectName);
	if (oldRuleKey != exeCapt)
		macroRule.begin()->second.lRuls.erase(macroRule.begin()->second.lRuls.begin());
	structProject tmpListRules = macroRule.begin()->second;
	// для нового правила также как и для старого должны стереть в macroRule 
	//			прежнее правило (для нового оно было с пустым ключом)
	macroRule.erase(macroRule.begin());
	tmpListRules.lRuls[exeCapt]=rule;
	macroRule[newProjectName.GetBuffer(1024)] = tmpListRules;
// 	if (oldNameProject.c_str() == newProjectName)
// 	{	//проект не поменялся
// 		macroRule[oldNameProject].lRuls[exeCapt]=rule;
// 	} else {
// 	}
	CDialog::OnOK();
}

void CKoeff::OnSelChangeCombo1() 
{
	if (combo_exact.GetCurSel())
		 edit_capt.EnableWindow(true);
	else edit_capt.EnableWindow(false);
}

//изменяем правилу проект, которому оно принадлежит
void CKoeff::OnCbnSelchangeCombo2()
{
	int sel = comboProjectsName.GetCurSel();
	CString newNameProj;
	comboProjectsName.GetLBText(sel, newNameProj);
	if (!isNewRule && newNameProj!=macroRule.begin()->first.c_str())
	{
		CMoveOrCopy dialMes;
		if (dialMes.DoModal()!=IDOK)
		{
			//отказались и от перемещения и от копирования правила:
			//		возвращаем прежнее название проекта
			for (int ii=0; ii<comboProjectsName.GetCount(); ii++)
			{
				CString proj;
				comboProjectsName.GetLBText(ii, proj);
				if (proj==oldNameProject.c_str())
				{
					comboProjectsName.SetCurSel(ii);
					return;
				}
			}
			ASSERT(false); //не найдено старое имя проекта
		}
		moveOrCopy = dialMes.resultQuery;
	}
	if (sel==comboProjectsName.GetCount()-1)
	{
		CNewProject dialNewProject;
		if (dialNewProject.DoModal()!=IDOK)
			return;
		comboProjectsName.InsertString(sel, dialNewProject.nameProject);
		comboProjectsName.SetCurSel(sel);

		//переключаемся на новый проект
		structProject tmpList;
		tmpList.nameList = dialNewProject.nameProject;
		tmpList.listFileName = dialNewProject.nameProject + ".rls";
		tmpList.koef = atof(dialNewProject.coefUseful);
		tmpList.lRuls = macroRule[macroRule.begin()->first].lRuls;
		if (moveOrCopy==MOVERULE || isNewRule)
			macroRule.erase(macroRule.begin());
		macroRule[dialNewProject.nameProject.GetBuffer(1000)] = tmpList;
	} else {
		//перекидываем правило в другой проект
		structProject tmpList;
		tmpList.nameList = newNameProj;
		tmpList.listFileName = newNameProj + ".rls";
		tmpList.lRuls = macroRule[macroRule.begin()->first].lRuls;
		for (rulMacroList::iterator indListRules=allRules.begin(); 
			indListRules!=allRules.end(); indListRules++)
		{
			if (newNameProj == indListRules->first.c_str())
			{
				tmpList.koef = indListRules->second.koef;
				break;
			}
		}
		if (moveOrCopy==MOVERULE)
			macroRule.erase(macroRule.begin());
		macroRule[newNameProj.GetBuffer(1000)] = tmpList;
	}
}
