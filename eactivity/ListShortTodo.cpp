// ListShortTodo.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "ListShortTodo.h"


// CListShortTodo dialog

IMPLEMENT_DYNAMIC(CListShortTodo, CDialog)

CListShortTodo::CListShortTodo(CWnd* pParent /*=NULL*/)
	: CDialog(CListShortTodo::IDD, pParent)
{

}

CListShortTodo::~CListShortTodo()
{
}

void CListShortTodo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, list_todo);
	DDX_Control(pDX, IDC_EDIT1, edit_name);
	DDX_Control(pDX, IDC_EDITr17, edit_percent);
	DDX_Control(pDX, IDC_EDIT2, edit_link);
	DDX_Control(pDX, IDC_EDIT4, edit_start_program);
	DDX_Control(pDX, IDC_CHECK1, check_no_often);
	DDX_Control(pDX, IDC_EDITr18, edit_how_often);
	DDX_Control(pDX, IDC_COMBO2, combo_often);
}


BEGIN_MESSAGE_MAP(CListShortTodo, CDialog)
	ON_COMMAND(ID_CONTEXT_ADDNEWITEM, &CListShortTodo::OnContextAddnewitem)
	ON_BN_CLICKED(IDOK, &CListShortTodo::OnBnClickedOk)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &CListShortTodo::OnNMRClickList3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CListShortTodo::OnLvnItemchangedList3)
	ON_EN_CHANGE(IDC_EDIT1, &CListShortTodo::OnEnChangeEdit1)
	ON_COMMAND(ID_CONTEXT_32796, &CListShortTodo::OnContext32796)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CListShortTodo::OnDeltaposSpin2)
	ON_EN_CHANGE(IDC_EDITr17, &CListShortTodo::OnEnChangeEditPercent)
	ON_COMMAND(ID_CONTEXT_32798, &CListShortTodo::OnContextDelete)
	ON_EN_CHANGE(IDC_EDIT2, &CListShortTodo::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, &CListShortTodo::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_CHECK1, &CListShortTodo::OnBnClickedCheck1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CListShortTodo::OnDeltaposSpin3)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CListShortTodo::OnCbnSelchangeCombo2)
	ON_EN_CHANGE(IDC_EDITr18, &CListShortTodo::OnEnChangeEditr18)
	ON_BN_CLICKED(IDC_BUTTON1, &CListShortTodo::OnBnClickedButton1)
END_MESSAGE_MAP()

bool initDialog = false;
BOOL CListShortTodo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	menuTree.LoadMenu(IDR_CONTEXT_TREE_SHOURT_TODO);

	list_todo.SetExtendedStyle(LVS_EX_GRIDLINES | 
		LVS_EX_FULLROWSELECT | list_todo.GetExtendedStyle());
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1703));
	list_todo.InsertColumn(0, str);
	list_todo.SetColumnWidth(0,90);
	str.LoadString(trif.GetIds(IDS_STRING1709));
	list_todo.InsertColumn(1, str);
	list_todo.SetColumnWidth(1,110);
	str.LoadString(trif.GetIds(IDS_STRING1705));
	list_todo.InsertColumn(2, str);
	list_todo.SetColumnWidth(2,80);
	str.LoadString(trif.GetIds(IDS_STRING1707));
	list_todo.InsertColumn(3, str);
	list_todo.SetColumnWidth(3,150);
	list_todo.exeCapt=false;
	list_todo.EnableToolTips(FALSE);
	LoadListTodo();
	if (list_todo.GetItemCount())
		list_todo.SetItemState(0, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);

	str.LoadString(trif.GetIds(IDS_STRING1739));
	combo_often.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1741));
	combo_often.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1743));
	combo_often.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1745));
	combo_often.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1747));
	combo_often.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1749));
	combo_often.AddString(str);
	combo_often.SetCurSel(AfxGetApp()->GetProfileInt("App", "combo_often.cursel", 1));
	edit_how_often.SetWindowText(AfxGetApp()->GetProfileString("App", "edit_often.text", "2"));
	initDialog = true;
	//normAllGroupsAndActions();
	return TRUE;
}

UINT CListShortTodo::GetUniqNum()
{
	UINT maxN = 1;
	for (int ii=0; ii<uniqNums.GetSize(); ii++)
	{
		if (uniqNums[ii] > maxN)
			maxN = uniqNums[ii];
	}
	return maxN+1;
}

void CListShortTodo::OnBnClickedOk()
{
	string strf = path_actuser + "listtodo.txt";
	ofstream ofstr(strf.c_str());
	if (ofstr==NULL)
		return;
	char ch[]="ver=0.3\n";
	ofstr<<ch;
	for (int ii=0; ii<list_todo.GetItemCount(); ii++)
	{
		ofstr<<list_todo.GetItemText(ii, 0);
		ofstr<<'\t';
		ofstr<<list_todo.GetItemText(ii, 1);
		ofstr<<'\t';
		ofstr<<list_todo.GetItemText(ii, 2);
		ofstr<<'\t';
		ofstr<<list_todo.GetItemText(ii, 3);
		ofstr<<'\t';
		ofstr<<uniqNums[ii];
		ofstr<<'\n';
	}
	ofstr.close();
	AfxGetApp()->WriteProfileInt("App", "combo_often.cursel", combo_often.GetCurSel());
	CString str;
	edit_how_often.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "edit_often.text", str);

	OnOK();
}

void CListShortTodo::LoadListTodo(bool interFace)
{
	string strf = path_actuser + "listtodo.txt";
	ifstream ifstr(strf.c_str());
	if (ifstr==NULL)
		return;
	char ch[1024];
	ifstr.getline(ch, 100);
	float ver;
	sscanf_s(ch, "ver=%f", &ver);
	for (;;)
	{
		ifstr.getline(ch, 1024, '\t');
		int row;
		if (interFace)
		{
			row = list_todo.InsertItem(list_todo.GetItemCount(), ch);
		} else {
			row = colomn0.GetSize();
			colomn0.InsertAt(colomn0.GetSize(), ch);
		}
		uniqNums.InsertAt(row, GetUniqNum());
		ifstr.getline(ch, 1024, '\t');
		if (!ifstr)
		{
			if (interFace && list_todo.GetItemText(row, 0) == "")
				list_todo.DeleteItem(row);//удаляем пустые строки
			if (!interFace && colomn0[row] == "")
				colomn0.RemoveAt(row);
			break;
		}
		if (interFace)
		{
			list_todo.SetItemText(row, 1, ch);
		} else {
			colomn1.InsertAt(row, ch);
		}
		if (!ifstr)
		{
			if (interFace && list_todo.GetItemText(row, 0) == "" && 
				list_todo.GetItemText(row, 1) == "")
				list_todo.DeleteItem(row);//удаляем пустые строки
			if (!interFace && colomn0[row] == "" && colomn1[row] == "")
				colomn0.RemoveAt(row);
			break;
		}
		ifstr.getline(ch, 1024, '\t');
		if (!IsRowAction(row, interFace))
			ch[0] = '\0'; //стираем ch, чтобы в группах не было никаких процентов
		if (ch[0]=='-')
		{	//отрицательные числа превращаем в 0
			if (interFace)
				list_todo.SetItemText(row, 2, "0.00");
			else
				colomn2.InsertAt(row, "0.00");
		} else {
			if (interFace)
				list_todo.SetItemText(row, 2, ch);
			else 
				colomn2.InsertAt(row, ch);
		}
		ifstr.getline(ch, 1024, ver>0.2 ? '\t' : '\n');
		interFace ? list_todo.SetItemText(row, 3, ch) : colomn3.InsertAt(row, ch);
		if (ver>0.2)
		{
			ifstr.getline(ch, 1024, '\n');
			uniqNums[row] = atoi(ch);
		}
		if (interFace && list_todo.GetItemText(row, 0) == "" && 
			list_todo.GetItemText(row, 1) == "")
			list_todo.DeleteItem(row);//удаляем пустые строки
		if (!interFace && colomn0[row] == "" && colomn1[row] == "")
			colomn0.RemoveAt(row);
		if (!ifstr)
			break;
	}
	ifstr.close();
}

void CListShortTodo::OnNMRClickList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CPoint point;
	GetCursorPos(&point);
	menuTree.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, 
		point.x, point.y, this);
	*pResult = 0;
}

//смена строчки в фокусе в списке дел
void CListShortTodo::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if (pNMLV->uNewState != 3)
		return;//реагируем только на выбор новой строчки
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel==-1)
		return;
	CString str = list_todo.GetItemText(sel, 0);
	BOOL bAction = str=="";
	if (str=="")
	{
		str = list_todo.GetItemText(sel, 1);
	}
	edit_link.EnableWindow(bAction);
	edit_start_program.EnableWindow(bAction);

	edit_name.SetWindowText(str);
	edit_name.SetSel(0, -1);
	CString debs = list_todo.GetItemText(sel, 2);
	edit_percent.SetWindowText(list_todo.GetItemText(sel, 2));
	edit_name.SetActiveWindow();

	str = getLink(sel);
	edit_link.SetWindowText(str);

	if (bAction)
	{
		int selComboPeriod;
		int durationPeriod = getOften(sel, true, selComboPeriod);
		if (durationPeriod>-1)
		{
			char chOften[100];
			sprintf_s(chOften, "%d", durationPeriod);
			combo_often.SetCurSel(selComboPeriod);
			edit_how_often.SetWindowText(chOften);
			check_no_often.SetCheck(TRUE);
		} else {
			check_no_often.SetCheck(FALSE);
			edit_how_often.SetWindowText("1");
		}
	} else {
		check_no_often.SetCheck(FALSE);
	}
	check_no_often.EnableWindow(bAction);
	edit_percent.EnableWindow(bAction);
	GetDlgItem(IDC_SPIN2)->EnableWindow(bAction);
	OnBnClickedCheck1();

	str = getProgram(sel);
	edit_start_program.SetWindowText(str);
	*pResult = 0;
}

void CListShortTodo::OnEnChangeEdit1()
{
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel==-1)
		return;
	CString str;
	int i1, i2;
	edit_name.GetSel(i1, i2);
	edit_name.GetWindowText(str);
	if (str!="")
	{
		if (list_todo.GetItemText(sel, 0)!="")
			list_todo.SetItemText(sel, 0, str);
		if (list_todo.GetItemText(sel, 1)!="")
			list_todo.SetItemText(sel, 1, str);
	}
	edit_name.SetSel(i1, i2, TRUE);
}

//меню: добавление новой группы
void CListShortTodo::OnContextAddnewitem()
{
	CString str;
	str.LoadString(IDS_STRING1711);
	int row = list_todo.InsertItem(list_todo.GetItemCount(), str);
	uniqNums.InsertAt(row, GetUniqNum());
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel!=-1)
		list_todo.SetItemState(sel, 0, LVIS_FOCUSED|LVIS_SELECTED);
	list_todo.SelectRow(row, true);
}

//меню: Добавить новое действие в выбранную группу списка
void CListShortTodo::OnContext32796()
{
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel==-1)
		return;
	int selGroup = GetSelectedGroup(sel);
	int row = list_todo.InsertItem(sel+1, "");
	uniqNums.InsertAt(row, GetUniqNum());
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1713));
	list_todo.SetItemText(row, 1, str);
	SetPercentForNewAction(selGroup, row);
	list_todo.SetItemState(sel, 0, LVIS_FOCUSED|LVIS_SELECTED);
	list_todo.SetItemState(row, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
}

//обход строк таблицы начиная с выбранного элемента вверх до именования группы
int CListShortTodo::GetSelectedGroup(int selRowAction, bool interFace)
{
	for (int ii=selRowAction; ii>=0; ii--)
	{
		if (interFace)
		{
			if (list_todo.GetItemText(ii, 0)!="")
				return ii;
		} else {
			if (colomn0[ii]!="")
				return ii;
		}
	}
	return -1;
}

//отъятие процентов вероятности у других групп для создаваемой новой группы
int CListShortTodo::SetPercentForNewGroup(int rowNewGroup)
{
	int groupCount=GetNoEmptyGroupCount();
	double percentNewGroup = 100.0/groupCount;
	char ch[500];
	sprintf_s(ch, "%0.2f", percentNewGroup);
	double oldPercent = atof(list_todo.GetItemText(rowNewGroup, 2));
	list_todo.SetItemText(rowNewGroup, 2, ch);
	//если действие единичное для группы, то присваиваем ему все проценты группы
	if ( rowNewGroup+2 < list_todo.GetItemCount() && list_todo.GetItemText(rowNewGroup+1, 1)!="" && 
		list_todo.GetItemText(rowNewGroup+2, 0)!="")
	{
		list_todo.SetItemText(rowNewGroup+1, 2, ch);
	} else {
		if ( rowNewGroup+2 == list_todo.GetItemCount() && list_todo.GetItemText(rowNewGroup+1, 1)!="")
		{
			list_todo.SetItemText(rowNewGroup+1, 2, ch);
		} else {
			NormPercForOneGroup(rowNewGroup, percentNewGroup, oldPercent);
		}
	} 
	// уменьшаем проценты других групп
	for (int ii=0; ii<list_todo.GetItemCount(); ii++)
	{
		if (ii==rowNewGroup)
			continue;
		if (list_todo.GetItemText(ii, 0) != "")
		{
			double oldPercent = atof(list_todo.GetItemText(ii, 2));
			double newPercent = oldPercent - percentNewGroup * oldPercent/100;
			sprintf_s(ch, "%0.2f", percentNewGroup);
			list_todo.SetItemText(ii, 2, ch);
			NormPercForOneGroup(ii, newPercent, oldPercent);
		}
	}
	return true;
}

//для нового действия начисляем проценты, нормируем другие действия в группе
void CListShortTodo::SetPercentForNewAction(int rowNewGroup, int rowNewAction)
{
	//считаем сколько действий в группе
	int NumActs=0;
	for (int ii=rowNewGroup+1; ii<list_todo.GetItemCount(); ii++)
	{
		if (list_todo.GetItemText(ii, 0) != "")
			break;
		if (list_todo.GetItemText(ii, 1) != "")
			NumActs++;
	}
	double groupPercent = atof(list_todo.GetItemText(rowNewGroup, 2));
	char ch[500];
	sprintf_s(ch, "%0.2f", groupPercent/NumActs);
	list_todo.SetItemText(rowNewAction, 2, ch);
	NormPercForOneGroup(rowNewGroup, groupPercent, groupPercent, rowNewAction);
	return;
}

//количество групп, в которых есть хотя бы одно короткое действие
int CListShortTodo::GetNoEmptyGroupCount()
{
	int groupCount=0;
	bool previousRowIsGroup=false;
	for (int ii=0; ii<list_todo.GetItemCount(); ii++)
	{
		if (list_todo.GetItemText(ii, 1) != "" && previousRowIsGroup)
			groupCount++;
		if (list_todo.GetItemText(ii, 0) != "")
		{
			previousRowIsGroup=true;
		} else {
			previousRowIsGroup=false;
		}
	}
	return groupCount;
}

bool changedViaSpin = false;
void CListShortTodo::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	changedViaSpin=true;
	percentDistribution((double)pNMUpDown->iDelta, true);
	changedViaSpin=false;
	*pResult = 0;
}

//распределение процентов между НЕ пустыми группами
void CListShortTodo::percentDistribution(double delta, bool fromSpin)
{
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel==-1)
		return;
	if (IsRowGroup(sel) && !getActionCountInGroup(sel))
		return;//для пустых групп запрещаем изменять проценты
	double oldPercent = atof(list_todo.GetItemText(sel, 2));
	double newPercent = oldPercent - delta;
	if (fromSpin)
	{	//при изменении через спин в первый раз округляем старое значение, чтобы новое получилось 
		//		круглым процентом, как бы добранным из старого дробного
		if ((int)(oldPercent * 100) % 100 != 0)
		{
			oldPercent = (int)oldPercent;
			if (delta > 0)
				 newPercent = oldPercent;
			else newPercent = oldPercent - delta;
		}
	}
	if (newPercent<0)
		return; //отрицательные проценты недопустимы
	char ch[500];
	sprintf_s(ch, "%0.2f", newPercent);
	list_todo.SetItemText(sel, 2, ch);
	edit_percent.SetWindowText(ch);
	//отключил автоматическое перенормирование процентов в группе и в других действиях
		//на практике это никакого удобства не добавляет, только запутывает
// 	if (IsRowGroup(sel))
// 		NormPercForOneGroup(sel, newPercent, oldPercent);
// 	if (IsRowAction(sel))
// 	{
// 		int rowGroup = GetSelectedGroup(sel);
// 		double groupPercent = atof(list_todo.GetItemText(rowGroup, 2));
// 		NormPercForOneGroup(rowGroup, groupPercent, groupPercent, sel);
// 	}
}

//Является ли строчка группой
bool CListShortTodo::IsRowGroup(int row)
{
	return list_todo.GetItemText(row, 0) != "";
}

//является ли строчка элементарным действием
bool CListShortTodo::IsRowAction(int row, bool interFace)
{
	return (interFace ? list_todo.GetItemText(row, 1) != "" : colomn1[row] != "");
}

int CListShortTodo::getActionCountInGroup(int rowGroup)
{
	int numActions=0;
	for (int ii=rowGroup+1; ii<list_todo.GetItemCount(); ii++)
	{
		if (IsRowGroup(ii))
			break;
		if (IsRowAction(ii))
			numActions++;
	}
	return numActions;
}

void CListShortTodo::OnEnChangeEditPercent() 
{
	if (changedViaSpin)
		return;
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel == -1)
		return;
	if (IsRowGroup(sel) && !getActionCountInGroup(sel))
		return;//для пустых групп запрещаем изменять проценты
	CString str;
	int i1, i2;
	edit_percent.GetSel(i1, i2);
	edit_percent.GetWindowText(str);
	double oldPercent = atof(list_todo.GetItemText(sel, 2));
	double newPercent = atof(str);
	if (newPercent<0)
		return; //отрицательные проценты недопустимы
	if (oldPercent != newPercent)
		percentDistribution(oldPercent - newPercent);
	edit_percent.GetSel(i1, i2);
}

//меню: удаление элементарного действия или целой группы
void CListShortTodo::OnContextDelete()
{
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel == -1)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1715));
		return;
	}
	CString str;
	if (list_todo.GetItemText(sel, 0)!="")
	{	// удаление группы
		if (AfxMessageBox(trif.GetIds(IDS_STRING1717), MB_YESNO)!=IDYES)
			return;
		list_todo.DeleteItem(sel);
		if (sel==list_todo.GetItemCount())
			return;
		//удаляем элементы группы
		while (list_todo.GetItemText(sel, 1)!="")
		{
			list_todo.DeleteItem(sel);
			if (sel==list_todo.GetItemCount())
				return;
		}
		//normAllGroupsAndActions();
	}
	if (list_todo.GetItemText(sel, 1)!="")
	{	// удаление элементарного действия
		if (AfxMessageBox(trif.GetIds(IDS_STRING1719), MB_YESNO)!=IDYES)
			return;
		int selGroup = GetSelectedGroup(sel);
		list_todo.DeleteItem(sel);
		double groupPerc = atof(list_todo.GetItemText(selGroup, 2));
		NormPercForOneGroup(selGroup, groupPerc, groupPerc);
	}
}

//запрашиваем сумму процентов по группе
double CListShortTodo::getSumPercFromOneGroup(int rowGroup)
{
	double sumPercForGroup=0.0;
	for (int jj=rowGroup+1; jj<list_todo.GetItemCount(); jj++)
	{
		if (list_todo.GetItemText(jj, 0)!="")
			break;
		sumPercForGroup += atof(list_todo.GetItemText(jj, 2));
	}
	return sumPercForGroup;
}

//нормирование всех групп и элементов на 100%
void CListShortTodo::normAllGroupsAndActions()
{
	//удаляем проценты у пустых групп
	for (int ii=0; ii<list_todo.GetItemCount()-1; ii++)
	{
		if (list_todo.GetItemText(ii, 0)!="" && getSumPercFromOneGroup(ii)==0.00)
			list_todo.SetItemText(ii, 2, "0.00");
	}
	if (list_todo.GetItemText(list_todo.GetItemCount()-1, 0)!="")
		list_todo.SetItemText(list_todo.GetItemCount()-1, 2, "0.00");
	//подсчитываем количество процентов в группах
	double sumPercents = 0.0;
	for (int ii=0; ii<list_todo.GetItemCount(); ii++)
	{
		if (list_todo.GetItemText(ii, 0)!="")
			sumPercents += atof(list_todo.GetItemText(ii, 2));
	}
	if (sumPercents==100.0 || sumPercents==0.00)
		return;
	double deltaPerc = 100.0 - sumPercents;
	int counGroups = GetNoEmptyGroupCount();
	//раздаем проценты не пустым группам
	for (int ii=0; ii<list_todo.GetItemCount(); ii++)
	{
		if (list_todo.GetItemText(ii, 0)!="" && ii<list_todo.GetItemCount()-1 &&
			list_todo.GetItemText(ii+1, 1) != "")
		{
			double oldPercent = atof(list_todo.GetItemText(ii, 2));
			double newPercent = oldPercent + deltaPerc*oldPercent/sumPercents;
			char ch[100];
			sprintf_s(ch, "%0.2f", newPercent);
			list_todo.SetItemText(ii, 2, ch);
			NormPercForOneGroup(ii, newPercent, oldPercent);
		}
	}
}

//нормирование процентов внутри одной группы
//	int unChangedRow - не изменяемая строка, нормировать все другие только
void CListShortTodo::NormPercForOneGroup(int rowGroup, double newPercent, double oldPercent, int unChangedRow)
{
	//удаляем проценты у пустых групп
// 	for (int ii=0; ii<list_todo.GetItemCount()-1; ii++)
// 	{
// 		if (list_todo.GetItemText(ii, 0)!="" && getSumPercFromOneGroup(ii)==0.00)
// 			list_todo.SetItemText(ii, 2, "0.00");
// 	}
// 	if (list_todo.GetItemText(list_todo.GetItemCount()-1, 0)!="")
// 		list_todo.SetItemText(list_todo.GetItemCount()-1, 2, "0.00");

	//считаем новую сумму процентов по группе
	double deltaPercGroup = newPercent - oldPercent;
	double sumPercForGroup = getSumPercFromOneGroup(rowGroup);
	deltaPercGroup = newPercent-sumPercForGroup;
	for (int jj=rowGroup+1; jj<list_todo.GetItemCount(); jj++)
	{
		if (list_todo.GetItemText(jj, 0)!="")
		{
			rowGroup = jj-1;
			break;
		}
		if (unChangedRow>-1 && unChangedRow==jj)
			continue;
		double oldPercentEl = atof(list_todo.GetItemText(jj, 2));
		double newPercentEl = 0.0;
		int actionCount = getActionCountInGroup(rowGroup);
		if (unChangedRow==-1)
		{
			newPercentEl = oldPercentEl + deltaPercGroup/actionCount;
			//newPercentEl = oldPercentEl + deltaPercGroup*oldPercentEl/(100-oldPercentEl);
		} else {
			if (actionCount>1)
				newPercentEl = oldPercentEl + deltaPercGroup/(actionCount-1);
// 			if (oldPercent!=oldPercentEl)
// 				newPercentEl = oldPercentEl + deltaPercGroup*oldPercentEl/(oldPercent-oldPercentEl);
// 			else 
// 			{//если действие содержит в себе весь процент группы, то от него и отнимаем всю дельту
// 				newPercentEl = oldPercentEl + deltaPercGroup;
// 			}
		}
		char ch[100];
		sprintf_s(ch, "%0.2f", newPercentEl);
		list_todo.SetItemText(jj, 2, ch);
	}
}

//возвращает в секундах промежуток времени из задания периода частоты короткого действия
DWORD CListShortTodo::getSecsFromOften(int durationPeriod, int typePeriod)
{
	switch (typePeriod)
	{
	case 0:
		return durationPeriod*60;
	case 1:
		return durationPeriod*3600;
	case 2:
		return durationPeriod*3600*24;
	case 3:
		return durationPeriod*3600*24*7;
	case 4:
		return durationPeriod*3600*24*30;
	case 5:
		return durationPeriod*3600*24*365;
	}
	ASSERT(0);//некорректный typePeriod
	return 0;
}

CString CListShortTodo::getRandomShortAction(CString& sGroup, CString& sLink, CString& sProg, UINT& uniq)
{
	LoadListTodo(false);
	CUIntArray hoax;
	int sumPercents = 0;
	for (int ii=0; ii<colomn2.GetSize(); ii++)
	{
		if (colomn1[ii]!="")
		{
			int typePeriod;
			int durationPeriod = getOften(ii, false, typePeriod);
			if (durationPeriod==-1)
			{
				hoax.Add((int)(atof(colomn2[ii])*100));
				sumPercents += hoax[hoax.GetSize()-1];
				continue;
			}
			CString lastDate = findLastTimeMakingShortTodo(uniqNums[ii]);
			if (lastDate == "")
			{
				hoax.Add((int)(atof(colomn2[ii])*100));
				sumPercents += hoax[hoax.GetSize()-1];
				continue;
			}
			CTime ctLastDate = CTime(atoi(lastDate.Left(4)), atoi(lastDate.Mid(5)), 
				atoi(lastDate.Mid(8)), atoi(lastDate.Mid(14)), atoi(lastDate.Mid(17)), 0, 0);
			if (ctLastDate.GetTime() + getSecsFromOften(durationPeriod, typePeriod) < 
				CTime::GetCurrentTime().GetTime())
			{//условие не чаще определенного периода времени выполнено
				hoax.Add((int)(atof(colomn2[ii])*100));
				sumPercents += hoax[hoax.GetSize()-1];
				continue;
			}
		}
		hoax.Add(0);//для соответствия индексов hoax индексам colomn1
	}
	DWORD luckyNumb = (GetTickCount() + rand()) % sumPercents;
	int luckyIndex = -1;
	int counter=0;
	for (int ii=0; ii<hoax.GetSize(); ii++)
	{
		if (colomn1[ii]!="")
		{
			counter += hoax[ii];
			if ((DWORD)counter >= luckyNumb)
			{
				luckyIndex = ii;
				break;
			}
		}
	}
	sGroup= colomn0[GetSelectedGroup(luckyIndex, false)];
	sLink = getLink   (luckyIndex, false);
	sProg = getProgram(luckyIndex, false);
	uniq = uniqNums[luckyIndex];
	return colomn1[luckyIndex];
}

CString CListShortTodo::findLastTimeMakingShortTodo(int uniqNum)
{
	string fileName = path_actuser + "journal_short_todo.txt";
	ifstream ifstr(fileName.c_str());
	if (ifstr==NULL)
		return "";
	char ch[1024];
	string str;
	char patt[] = "(uniq=%d)";
	char for_find[100];
	sprintf_s(for_find, patt, uniqNum);
	string res;
	for (;;)
	{
		ifstr.getline(ch, 1024, '\n');
		str = ch;
		if (str.find(for_find)!=std::string::npos)
			res = str;
		if (!ifstr)
			break;
	}
	return res.substr(0, 19).c_str();
}


void CListShortTodo::OnEnChangeEdit2()
{
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel == -1)
		return;
	CString sProg = getProgram(sel);
	CString sLink;
	edit_link.GetWindowText(sLink);
	int typePeriod;
	int durationPeriod = getOften(sel, true, typePeriod);
	list_todo.SetItemText(sel, 3, CompilLinkAndProg(sLink, sProg, durationPeriod, typePeriod));
}

void CListShortTodo::OnEnChangeEdit4()
{
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel == -1)
		return;
	CString sLink = getLink(sel);
	CString sProg;
	edit_start_program.GetWindowText(sProg);
	int typePeriod;
	int durationPeriod = getOften(sel, true, typePeriod);
	list_todo.SetItemText(sel, 3, CompilLinkAndProg(sLink, sProg, durationPeriod, typePeriod));
}

//компоновка результирующей строки, в которой будет содержаться информация какие программы и веб линки
//должны запускаться и не чаще какого периода времени должан выполняться задача
CString CListShortTodo::CompilLinkAndProg(CString sLink, CString sProg, int howOften, int typePeriod)
{
	char ch[9000];
	CString res="";
	if (sLink!="")
	{
		sprintf_s(ch, "StartInBrowser(\"%s\");", sLink);
		res = ch;
	}
	if (sProg!="")
	{
		if (res!="")
			res += " ";
		sprintf_s(ch, "StartProgram(\"%s\");", sProg);
		res += ch;
	}
	if (typePeriod!=-1 && howOften!=-1)
	{
		if (res!="")
			res += " ";
		CString strTypePeriod="";
		strTypePeriod.LoadString(IDS_STRING1740+2*typePeriod);
		sprintf_s(ch, "MaxOften(\"%d %s\");", howOften, strTypePeriod);
		res += ch;
	}
	return res;
}

CString CListShortTodo::getLink(int selRow, bool interFace)
{
	CString str;
	if (interFace)
		str = list_todo.GetItemText(selRow, 3);
	else 
		str = colomn3[selRow];
	int fi = str.Find("StartInBrowser(\"");
	if (fi>-1)
		return str.Mid(fi+16, str.Find('\"', fi+17)-fi-16);
	return "";
}

// из подстроки MaxOften("60 min."); парсить как часто можно делать короткое дело
int CListShortTodo::getOften(int selRow, bool interFace, int& comboPeriod)
{
	CString str;
	if (interFace)
		str = list_todo.GetItemText(selRow, 3);
	else 
		str = colomn3[selRow];
	int fi = str.Find("MaxOften(\"");

	if (fi>-1)
		str =str.Mid(fi+10, str.Find('\"', fi+11)-fi-10);
	else 
		return -1;
	int durationPeriod = atoi(str);
	comboPeriod = -1;
	if (str.Find("min.")>-1)
		comboPeriod = 0;
	if (str.Find("hour(s)")>-1)
		comboPeriod = 1;
	if (str.Find("day(s)")>-1)
		comboPeriod = 2;
	if (str.Find("week(s)")>-1)
		comboPeriod = 3;
	if (str.Find("month(s)")>-1)
		comboPeriod = 4;
	if (str.Find("year(s)")>-1)
		comboPeriod = 5;
	if (comboPeriod==-1)
		return -1;
	return durationPeriod;
}

CString CListShortTodo::getProgram(int selRow, bool interFace)
{
	CString str;
	if (interFace)
		str = list_todo.GetItemText(selRow, 3);
	else 
		str = colomn3[selRow];
	int fi = str.Find("StartProgram(\"");
	if (fi>-1)
		return str.Mid(fi+14, str.Find('\"', fi+15)-fi-14);
	return "";
}
void CListShortTodo::OnBnClickedCheck1()
{
	BOOL bCheck = check_no_often.GetCheck();
	edit_how_often.EnableWindow(bCheck);
	combo_often.EnableWindow(bCheck);
	GetDlgItem(IDC_SPIN3)->EnableWindow(bCheck);
	if (bCheck)
	{
		OnCbnSelchangeCombo2();
	} else {//удаляем контроль
		int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
		if (sel == -1)
			return;
		CString sLink = getLink(sel);
		CString sProg = getProgram(sel);
		list_todo.SetItemText(sel, 3, CompilLinkAndProg(sLink, sProg, -1, -1));
	}
}

void CListShortTodo::OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel == -1)
		return;
	CString str;
	edit_how_often.GetWindowText(str);
	char ch[100];
	int newValue = atoi(str)-pNMUpDown->iDelta;
	if (newValue < 1)
		return;
	sprintf_s(ch, "%d", atoi(str)-pNMUpDown->iDelta);
	edit_how_often.SetWindowText(ch);
	*pResult = 0;
}

void CListShortTodo::OnCbnSelchangeCombo2()
{
	if (!initDialog)
		return;
	if (!check_no_often.GetCheck())
		return;
	int sel = (int)list_todo.GetFirstSelectedItemPosition()-1;
	if (sel == -1)
		return;
	CString sLink = getLink(sel);
	CString sProg = getProgram(sel);
	CString str;
	edit_how_often.GetWindowText(str);
	if (atoi(str)<1)
		return;
	list_todo.SetItemText(sel, 3, CompilLinkAndProg(sLink, sProg, atoi(str), combo_often.GetCurSel()));
}

void CListShortTodo::OnEnChangeEditr18()
{
	OnCbnSelchangeCombo2();
}

void CListShortTodo::OnBnClickedButton1()
{
	CUIntArray hoax;
	float sumPercents = 0.0;
	for (int ii=0; ii<list_todo.GetItemCount(); ii++)
	{
		if (IsRowAction(ii))
		{
			hoax.Add((int)(atof(list_todo.GetItemText(ii, 2))*100));
			sumPercents += hoax[hoax.GetSize()-1];
		} else {
			hoax.Add(0);
		}
	}
	float coefNorm = sumPercents/10000; //Коэффициент нормирования
	char ch[100];
	for (int ii=0; ii<list_todo.GetItemCount(); ii++)
	{
		if (!IsRowAction(ii))
			continue;
		sprintf_s(ch, "%0.2f", atof(list_todo.GetItemText(ii, 2))/coefNorm);
		list_todo.SetItemText(ii, 2, ch);
	}
}
