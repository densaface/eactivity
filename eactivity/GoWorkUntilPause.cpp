// GoWorkUntilPause.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "GoWorkUntilPause.h"


// CGoWorkUntilPause dialog

IMPLEMENT_DYNAMIC(CGoWorkUntilPause, CDialog)

CGoWorkUntilPause::CGoWorkUntilPause(CWnd* pParent /*=NULL*/)
	: CDialog(CGoWorkUntilPause::IDD, pParent)
{
	typeUsefulPar=0;
	typeShowBreak = -1;
}

CGoWorkUntilPause::~CGoWorkUntilPause()
{
}

void CGoWorkUntilPause::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT5, edit_usefulacts);
	DDX_Control(pDX, IDC_RADIO1, radio_usefulacts);
	DDX_Control(pDX, IDC_RADIO2, radio_usefultime);
	DDX_Control(pDX, IDC_RADIO3, radio_usual_time);
	DDX_Control(pDX, IDC_EDIT8, edit_usefultime);
	DDX_Control(pDX, IDC_COMBO2, combo_type_time);
	DDX_Control(pDX, IDC_CHECK2, check_text_mes);
	DDX_Control(pDX, IDC_EDIT1, edit_text_mes);
	DDX_Control(pDX, IDC_CHECK3, check_short_todo);
	DDX_Control(pDX, IDC_EDIT9, edit_usualtime);
	DDX_Control(pDX, IDC_COMBO1, combo_show_break);
}


BEGIN_MESSAGE_MAP(CGoWorkUntilPause, CDialog)
	ON_BN_CLICKED(IDOK, &CGoWorkUntilPause::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CGoWorkUntilPause::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGoWorkUntilPause::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CGoWorkUntilPause::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON1, &CGoWorkUntilPause::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK2, &CGoWorkUntilPause::OnBnClickedCheck2)
	ON_EN_CHANGE(IDC_EDIT1, &CGoWorkUntilPause::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CGoWorkUntilPause message handlers
BOOL CGoWorkUntilPause::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int radio_last_pos = AfxGetApp()->GetProfileInt("App", "PauseRadioUsefulPar", 1);
	switch (radio_last_pos)
	{
	case 1:
		radio_usefulacts.SetCheck(1);
		radio_usefultime.SetCheck(0);
		radio_usual_time.SetCheck(0);
		break;
	case 2:
		radio_usefulacts.SetCheck(0);
		radio_usefultime.SetCheck(1);
		radio_usual_time.SetCheck(0);
		break;
	case 3:
		radio_usefulacts.SetCheck(0);
		radio_usefultime.SetCheck(0);
		radio_usual_time.SetCheck(1);
		break;
	}

	CString regValue = AfxGetApp()->GetProfileString("App", "EditUsefulActsBeforePause", "800");
	edit_usefulacts.SetWindowText(regValue);

	regValue = AfxGetApp()->GetProfileString("App", "TextMes", "");
	edit_text_mes.SetWindowText(regValue);
	check_short_todo.SetCheck(AfxGetApp()->GetProfileInt("App", "check_short_todo", 1));

	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1695));
	combo_type_time.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1697));
	combo_type_time.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1699));
	combo_type_time.AddString(str);
	int iRegValue = AfxGetApp()->GetProfileInt("App", "EditUsefulTimeTimeType", -1);
	if (iRegValue == -1)
	{
		edit_usefultime.SetWindowText("45");
		combo_type_time.SetCurSel(1);
	} else {
		combo_type_time.SetCurSel(iRegValue);
		regValue = AfxGetApp()->GetProfileString("App", "EditUsefulTimeBeforePause", "45");
		edit_usefultime.SetWindowText(regValue);
		regValue = AfxGetApp()->GetProfileString("App", "EditUsualTimeBeforePause", "45");
		edit_usualtime.SetWindowText(regValue);
	}
	OnBnClickedRadio1();

	str.LoadString(trif.GetIds(IDS_STRING1751));
	combo_show_break.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1753));
	combo_show_break.AddString(str);
	str.LoadString(trif.GetIds(IDS_STRING1755));
	combo_show_break.AddString(str);
	combo_show_break.SetCurSel(AfxGetApp()->GetProfileInt("App", "TypeShowBreak", 0));
	combo_show_break.SetDroppedWidth(350);

	return FALSE;
}
void CGoWorkUntilPause::OnBnClickedOk()
{
	CString str;
	if (radio_usefulacts.GetCheck())
	{	//отсчитываем полезные действия
		edit_usefulacts.GetWindowText(str);
		UsefulActs = (float)atof(str);
		UsefulTime = UsualTime = -1;
		typeUsefulPar = 1;
	} else {
		if (radio_usefultime.GetCheck())
		{	//полезное время
			edit_usefultime.GetWindowText(str);
			switch (combo_type_time.GetCurSel())
			{
			case 0:
				UsefulTime = (float)atof(str)*1000;
				break;
			case 1:
				UsefulTime = (float)atof(str)*60*1000;
				break;
			case 2:
				UsefulTime = (float)atof(str)*3600*1000;
				break;
			}
			UsefulActs = UsualTime = -1;
			typeUsefulPar = 2;
		} else {//обычное время
			edit_usualtime.GetWindowText(str);
			switch (combo_type_time.GetCurSel())
			{
			case 0:
				UsualTime = (float)atof(str)*1000;
				break;
			case 1:
				UsualTime = (float)atof(str)*60*1000;
				break;
			case 2:
				UsualTime = (float)atof(str)*3600*1000;
				break;
			}
			UsefulActs = UsefulTime = -1;
			typeUsefulPar = 3;
		}
	}
	AfxGetApp()->WriteProfileInt("App", "PauseRadioUsefulPar", typeUsefulPar);
	AfxGetApp()->WriteProfileInt("App", "EditUsefulTimeTimeType", combo_type_time.GetCurSel());
	AfxGetApp()->WriteProfileInt("App", "TypeShowBreak", combo_show_break.GetCurSel());
	typeShowBreak = combo_show_break.GetCurSel();

	edit_usefultime.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "EditUsefulTimeBeforePause", str);
	edit_usualtime.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "EditUsualTimeBeforePause", str);
	edit_usefulacts.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "EditUsefulActsBeforePause", str);

	edit_text_mes.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "TextMes", str);
	AfxGetApp()->WriteProfileInt("App", "check_short_todo", check_short_todo.GetCheck());

	textMes = "";
	if (check_text_mes.GetCheck())
	{
		edit_text_mes.GetWindowText(textMes);
	}
	shortTodo = check_short_todo.GetCheck();
	OnOK();
}

void CGoWorkUntilPause::OnBnClickedRadio1()
{
	edit_usefulacts.EnableWindow(radio_usefulacts.GetCheck());
	edit_usefultime.EnableWindow(radio_usefultime.GetCheck());
	edit_usualtime .EnableWindow(radio_usual_time.GetCheck());
}

void CGoWorkUntilPause::OnBnClickedButton1()
{
	CListShortTodo dialShortTodo;
	dialShortTodo.path_actuser = path_actuser;
	dialShortTodo.DoModal();
}
void CGoWorkUntilPause::OnBnClickedCheck2()
{
	if (!check_text_mes.GetCheck())
		edit_text_mes.SetWindowText("");
}

void CGoWorkUntilPause::OnEnChangeEdit1()
{
	CString str;
	edit_text_mes.GetWindowText(str);
	check_text_mes.SetCheck(str!="");
}
