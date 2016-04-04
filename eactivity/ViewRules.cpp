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
	DDX_Control(pDX, IDC_COMBO1, comboProjectsName);
	DDX_Control(pDX, IDC_EDIT2, edit_search);
}


BEGIN_MESSAGE_MAP(CViewRules, CDialog)
	//{{AFX_MSG_MAP(CViewRules)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkList3)
	ON_BN_CLICKED(IDC_BUTTON1, OnDelRul)
	ON_BN_CLICKED(IDC_BUTTON2, OnEditRule)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CViewRules::OnNewProject)
	ON_BN_CLICKED(IDC_BUTTON5, &CViewRules::OnEditProject)
	ON_EN_CHANGE(IDC_EDIT2, &CViewRules::OnEnChangeEditSearch)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CViewRules::OnCbnSelchangeCombo1)
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
	str.LoadString(trif.GetIds(IDS_STRING1915));
	list_rules.InsertColumn(2, str);//"Caption"
	str.LoadString(trif.GetIds(IDS_STRING1627));
	list_rules.InsertColumn(3, str);
	str.LoadString(trif.GetIds(IDS_STRING1913));
	list_rules.InsertColumn(4, str);//"Project"
	list_rules.SetColumnWidth(0,120);
	list_rules.SetColumnWidth(1,100);
	list_rules.SetColumnWidth(2,150);
	list_rules.SetColumnWidth(3,40);
	list_rules.SetColumnWidth(4,100);
	

	//список проектов, по умолчанию показываем правила для всех проектов
	str.LoadString(trif.GetIds(IDS_STRING1905));
	comboProjectsName.AddString(str);
	comboProjectsName.SetCurSel(0);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	for (rulMacroList::iterator indListRules=GlobalRules.begin(); 
		indListRules!=GlobalRules.end(); indListRules++)
	{
		comboProjectsName.AddString(indListRules->first.c_str());
	}
	OnEnChangeEditSearch();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewRules::OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnEditRule();
	*pResult = 0;
}

void CViewRules::OnDelRul() 
{
	POSITION pos=list_rules.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;
	if (AfxMessageBox(trif.GetIds(IDS_STRING1581), MB_YESNO)!=IDYES)
		return;

	string capt = list_rules.GetItemText(sel, 2);
	string exeCapt = list_rules.GetItemText(sel, 1);
	if (capt!="")
		exeCapt += '\t' + capt;
	CStringArray allProj;
	rulMacroList tmpRuleList = findRule(exeCapt, "", "", allProj);
	sRule tmpRule = tmpRuleList.begin()->second.lRuls.begin()->second;
	//имя проекта, которому принадлелажало найденное правило
	string oldNameProject = tmpRuleList.begin()->first; 
	//ключ, по которому было обращение к правилу
	string oldRulKey = tmpRuleList.begin()->second.lRuls.begin()->first;
	GlobalRules[oldNameProject].lRuls.erase(
		GlobalRules[oldNameProject].lRuls.find(oldRulKey));
	OnEnChangeEditSearch();
}


void CViewRules::OnEditRule() 
{
	POSITION pos=list_rules.GetFirstSelectedItemPosition();
	int sel=(int)pos-1;
	if (sel<0)
		return;

	string capt = list_rules.GetItemText(sel, 2);
	string exeCapt = list_rules.GetItemText(sel, 1);
	if (capt!="")
		exeCapt += '\t' + capt;
	CKoeff koef;
	CStringArray allProj;
	koef.macroRule = findRule(exeCapt, "", "", allProj);
	sRule tmpRule = koef.macroRule.begin()->second.lRuls.begin()->second;
	ASSERT(tmpRule.typeRule != -1);
	koef.isNewRule = false;
	//имя проекта, которому принадлелажало найденное правило
	string oldNameProject = koef.macroRule.begin()->first; 
	//ключ, по которому было обращение к правилу
	string oldRulKey = koef.macroRule.begin()->second.lRuls.begin()->first;
	koef.allRules = GlobalRules;

 	if (koef.DoModal()!=IDOK)
 		return;
	if (koef.moveOrCopy==MOVERULE)
		GlobalRules[oldNameProject].lRuls.erase(
			GlobalRules[oldNameProject].lRuls.find(oldRulKey));
	if (GlobalRules.find(koef.macroRule.begin()->first) == GlobalRules.end())
	{
		//при редактировании правила создали новый проект
		comboProjectsName.AddString(koef.macroRule.begin()->first.c_str());
		//comboProjectsName.SetCurSel(comboProjectsName.GetCount()-1);
	}
	if (GlobalRules.find(koef.macroRule.begin()->first) == GlobalRules.end())
	{	//новый проект
		GlobalRules[koef.macroRule.begin()->first] = koef.macroRule.begin()->second;
	} else {
		GlobalRules[koef.macroRule.begin()->first].lRuls[
			koef.macroRule.begin()->second.lRuls.begin()->first] = 
				koef.macroRule.begin()->second.lRuls.begin()->second;
	}
	OnEnChangeEditSearch();
}

//нажатие кнопки "Новый проект" - заведение нового файла коэффициентов
void CViewRules::OnNewProject()
{
	CNewProject dialNewProject;
	if (dialNewProject.DoModal()!=IDOK)
		return;
	comboProjectsName.AddString(dialNewProject.nameProject);
	structProject tmpList;
	tmpList.nameList = dialNewProject.nameProject;
	tmpList.listFileName = dialNewProject.nameProject + ".rls";
	tmpList.koef = atof(dialNewProject.coefUseful);
	GlobalRules[dialNewProject.nameProject.GetBuffer(1000)] = tmpList;
}

//нажатие кнопки "Редактировать" (проект) - изменение имени и 
//			сроков действия файла коэффициентов
void CViewRules::OnEditProject()
{
	CProjectEdit dialogEditProj;
	int sel = comboProjectsName.GetCurSel();
	CString str;
	comboProjectsName.GetLBText(sel, str);
	rulMacroList::iterator iterProj = GlobalRules.find(str.GetBuffer(1000));
	ASSERT(iterProj!=GlobalRules.end());
	dialogEditProj.editedProj = iterProj->second;
	if (dialogEditProj.DoModal()!=IDOK)
		return;
	iterProj->second.nameList = dialogEditProj.editedProj.nameList;
	iterProj->second.koef = dialogEditProj.editedProj.koef;
	iterProj->second.comment = dialogEditProj.editedProj.comment;
}

float CViewRules::GetUsefulTimeFromExe(string exe, activ &forLoad1) 
{
	float useful_time=0;
	for (activ::iterator ia=forLoad1.begin(); ia!=forLoad1.end(); ia++)
	{
		if ((*ia).second.exe==exe)
		{
			string ExeCapt=exe+'\t'+(*ia).second.capt;
			for (rulMacroList::iterator indListRules=GlobalRules.begin(); 
				indListRules!=GlobalRules.end(); indListRules++)
			{
				rulSpis::iterator iter=indListRules->second.lRuls.find(ExeCapt);
				if (iter==indListRules->second.lRuls.end())
					iter=partCaptFind(exe, (*ia).second.capt, indListRules->second.lRuls);
				if (iter==indListRules->second.lRuls.end())
					iter=indListRules->second.lRuls.find(exe);
				if (iter!=indListRules->second.lRuls.end())
				{
					(*ia).second.usefulTime = (*iter).second.koef * (*ia).second.sumTime;
					useful_time += ((*iter).second.koef * (*ia).second.sumTime);
				}
			}
		}
	}
	return useful_time;
}

double CViewRules::GetUsefulActsFromExe(string exe, activ &forLoad1) 
{
	double sumUsefulActs=0;
	for (activ::iterator ia=forLoad1.begin(); ia!=forLoad1.end(); ia++)
	{
		if ((*ia).second.exe==exe)
		{
			string ExeCapt=exe+'\t'+(*ia).second.capt;
			for (rulMacroList::iterator indListRules=GlobalRules.begin(); 
				indListRules!=GlobalRules.end(); indListRules++)
			{
				rulSpis::iterator iter=indListRules->second.lRuls.find(ExeCapt);
				if (iter==indListRules->second.lRuls.end())
					iter=partCaptFind(exe, (*ia).second.capt, indListRules->second.lRuls);
				if (iter==indListRules->second.lRuls.end())
					iter=indListRules->second.lRuls.find(exe);
				if (iter!=indListRules->second.lRuls.end())
				{
					(*ia).second.usefulActs=(int)((*iter).second.koef * (*ia).second.sumActs);
					sumUsefulActs+=(*ia).second.usefulActs;
				}
			}
		}
	}
	return sumUsefulActs;
}

//сохранение всех файлов коэффициентов
void CViewRules::SaveRules()
{
	//создание папки для правил в случае ее несуществования
	string pathRules = path_actuser+"rules\\";
	if (!trif.IsDirExist(pathRules.c_str()))
		if (!CreateDirectory(pathRules.c_str(), NULL))
		{
			CString str;
			str.LoadString(trif.GetIds(IDS_STRING1903));
			AfxMessageBox(str + pathRules.c_str());
			return;
		}

		for (rulMacroList::iterator indListRules=GlobalRules.begin(); 
			indListRules!=GlobalRules.end(); indListRules++)
		{
			string strf=pathRules+indListRules->second.listFileName;
			ofstream ofstr(strf.c_str());
			if (ofstr==NULL)
				return;
			string nameProj = indListRules->second.nameList;
			if (nameProj == "")
			{	//если имя проекта не задано, то берем его из имени файла
				nameProj = indListRules->second.listFileName.substr(0, 
					indListRules->second.listFileName.length()-4);
			}
			string verName = "ver=0.3\t" + nameProj + "\n";
			ofstr<<verName.c_str();
			ofstr<<indListRules->second.koef;
			ofstr<<"\n";
			trif.replaceAll(indListRules->second.comment, "\n", "\\n");
			ofstr<<indListRules->second.comment;
			ofstr<<"\n";
			for (rulSpis::iterator iter=indListRules->second.lRuls.begin(); 
				iter!=indListRules->second.lRuls.end(); iter++)
			{
				ofstr<<(*iter).second.koef;
				ofstr<<'\t';
				ofstr<<(*iter).second.typeRule;
				ofstr<<'\t';
				ofstr<<(*iter).second.exe;
				ofstr<<'\t';
				ofstr<<(*iter).second.capt;
				ofstr<<'\n';
			}
			ofstr.close();
		}
}

//загрузка единичного файла правил
void CViewRules::LoadRuleFile(CString fileName)
{
	structProject RULES;
	ifstream ifstr(fileName);
	if (ifstr==NULL)
		return;
	char ch[5024];
	ifstr.getline(ch, 100);
	double ver;
	string sVer = ch;
	ASSERT(sVer.substr(0, 4)=="ver=");
	ver = atof(sVer.substr(4).c_str());
	string sNameProj="";
	if (ver<0.11) //версия 0.1
	{
		RULES.koef = 1.0;
	}
	if (ver>0.1)
	{
		int fi = sVer.find('\t');
		ASSERT(fi>-1);
		sNameProj = sVer.substr(fi+1);
		int ideb = sNameProj.length();
		ideb = ideb;
	}
	if (ver>0.2)
	{
		ifstr.getline(ch, 100);
		RULES.koef = atof(ch);
		ifstr.getline(ch, 5000);
		RULES.comment = ch;
		trif.replaceAll(RULES.comment, "\\n", "\n");
	}
	if (sNameProj == "")
	{
		sNameProj = trif.ExtractFileName(fileName);// FFData.cFileName;
		//в качестве имя проекта берем имя файла без расширения
		sNameProj = sNameProj.substr(0, sNameProj.length()-4);
	}
	RULES.listFileName = trif.ExtractFileName(fileName);
	RULES.nameList = sNameProj;

	sRule tmpRule;
	while (ifstr)
	{
		ifstr>>tmpRule.koef;
		ifstr.get();
		ifstr>>tmpRule.typeRule;
		ifstr.get();
		if (!ifstr)
			break;
		ifstr.getline(ch, 1024, '\t');
		tmpRule.exe=ch;
		ifstr.getline(ch, 1024, '\n');
		tmpRule.capt=ch;
		string exeCapt;
		if (tmpRule.typeRule==0)
			exeCapt=tmpRule.exe;
		else exeCapt=tmpRule.exe+'\t'+tmpRule.capt;
		RULES.lRuls[exeCapt]=tmpRule;
		if (!ifstr)
			break;
	}
	ifstr.close();
	GlobalRules[sNameProj] = RULES;
}

void CViewRules::LoadRules() 
{
	string pathRules = path_actuser+"rules\\*.rls";

	WIN32_FIND_DATA FFData;
	HANDLE hFind = FindFirstFile(pathRules.c_str(), &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			string strf=path_actuser+"rules\\"+FFData.cFileName;
			LoadRuleFile(strf.c_str());
		} while(FindNextFile(hFind, &FFData));
		FindClose(hFind);
	} else {
		//старый формат правил
		string strf=path_actuser+"rules.rls";
		LoadRuleFile(strf.c_str());
	}
}

//поиск по правилам подходящего по заголовку или экзешнику
//		CStringArray saListProjs - список проектов, для которого должен быть поиск 
//			по правилам
// возвращает rulMacroList, содержащее всего один список правил, в котором единственное подходящее правило
//		если это пустое правило (type =-1) то подходящее правило не найдено, 
rulMacroList CViewRules::findRule(string ExeCapt, string exe, string capt,
	CStringArray &saListProjs) 
{

	rulMacroList retRule;
	sRule tmpRule; 
	structProject tmpListRules;
	for (rulMacroList::iterator indListRules=GlobalRules.begin(); 
		indListRules!=GlobalRules.end(); indListRules++)
	{
		bool skipProj=true;
		for (int ii=0; ii<saListProjs.GetSize(); ii++)
		{
			if (saListProjs[ii]==indListRules->second.nameList.c_str()) 
			{
				skipProj = false;
				break;
			}
		}
		//пустой список проектов означает команду использовать все заголовки
		if (saListProjs.GetSize()>0 && skipProj)
			continue;

// 		tormoz[0]+=::GetCurrentTime()-oldtick;
// 		oldtick=::GetCurrentTime();

		rulSpis::iterator iter = indListRules->second.lRuls.begin();
		if (ExeCapt!="")
			iter = indListRules->second.lRuls.find(ExeCapt);

// 		tormoz[1]+=::GetCurrentTime()-oldtick;
// 		oldtick=::GetCurrentTime();

		if (capt != "" && iter == indListRules->second.lRuls.end())
			iter = partCaptFind(exe, capt, indListRules->second.lRuls);

// 		tormoz[2]+=::GetCurrentTime()-oldtick;
// 		oldtick=::GetCurrentTime();

		if (exe != "" && iter == indListRules->second.lRuls.end())
			iter = indListRules->second.lRuls.find(exe);

// 		tormoz[3]+=::GetCurrentTime()-oldtick;
// 		oldtick=::GetCurrentTime();

		if (iter != indListRules->second.lRuls.end())
		{
			//tmpRule = iter->second;
			tmpListRules.lRuls[iter->first] = iter->second;
			tmpListRules.nameList = indListRules->first;
			tmpListRules.koef = indListRules->second.koef;
			retRule[indListRules->first] = tmpListRules;
			break;
		}

	}
	if (!retRule.size())
	{	//подходящее правило не найдено, добавляем пустое
		tmpListRules.lRuls[""] = tmpRule;
		retRule[""] = tmpListRules;
	}

	return retRule;
}

//частичный поиск по заголовку
rulSpis::iterator CViewRules::partCaptFind(string exe, string capt, rulSpis &RULES) 
{
	ASSERT(exe!="");
	for (rulSpis::iterator iter=RULES.begin(); iter!=RULES.end(); iter++)
	{
		if (iter->second.typeRule!=2)
			continue;
		if (exe!=iter->second.exe)
			continue;
		int fi=capt.find(iter->second.capt);
		if (fi>-1)
			return iter;
	}
	return RULES.end();
}

//быстрый поиск
void CViewRules::OnEnChangeEditSearch()
{
	CString str;
	int ii=0;
	int countAllRules = 0;
	int countShownRules = 0;
	list_rules.DeleteAllItems();
	saKeys.RemoveAll();
	saKeysProjs.RemoveAll();
	CString searchText;
	edit_search.GetWindowText(searchText);
	searchText.MakeLower();
	ASSERT(comboProjectsName.GetCurSel()!=-1);
	for (rulMacroList::iterator indListRules=GlobalRules.begin(); 
		indListRules!=GlobalRules.end(); indListRules++)
	{
		if (comboProjectsName.GetCurSel()!=0)
		{
			comboProjectsName.GetLBText(comboProjectsName.GetCurSel(), str);
			if (str != indListRules->first.c_str())
				continue; //комбо выбора проекта, отсеиваем неподходящие проекты
		}
		for (rulSpis::iterator iter=indListRules->second.lRuls.begin(); 
			iter!=indListRules->second.lRuls.end(); iter++)
		{
			countAllRules++;
			//быстрым поиском отсекаем те заголовки и экзешники, которые 
			//			не содержат текста поиска
			if (searchText!="")
			{
				string low_exe = (*iter).second.exe;
				string low_capt = (*iter).second.capt;
				for(unsigned int i = 0; i < low_exe.length(); ++i) {
					low_exe[i] = tolower(low_exe[i]);
				}
				for(unsigned int i = 0; i < low_capt.length(); ++i) {
					low_capt[i] = tolower(low_capt[i]);
				}

				if (low_exe .find(searchText)==-1 && 
					low_capt.find(searchText)==-1)
					continue;
			}
			countShownRules++;
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
			saKeys     .Add(iter        ->first.c_str());
			saKeysProjs.Add(indListRules->first.c_str());
			list_rules.SetItemText(ii, 1, (*iter).second.exe.c_str());
			list_rules.SetItemText(ii, 2, (*iter).second.capt.c_str());
			//имя проекта
			list_rules.SetItemText(ii, 4, indListRules->first.c_str());
			char ch[100];
			sprintf_s(ch, "%0.2f", (*iter).second.koef);
			list_rules.SetItemText(ii, 3, ch);
			ii++;
		}
	}

	//показываем числов выведенных правил
	str.LoadString(trif.GetIds(IDS_STRING1919));
	char ch[1024];
	sprintf_s(ch, str, countShownRules, countAllRules);
	GetDlgItem(IDC_RulesCountStatic)->SetWindowText(ch);
}

void CViewRules::OnCbnSelchangeCombo1()
{
	GetDlgItem(IDC_BUTTON5)->EnableWindow(comboProjectsName.GetCurSel()!=0);
	OnEnChangeEditSearch();
}
