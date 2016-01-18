// OnlineAdvices.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "OnlineAdvices.h"
//#include "externals/sqlite/sqlitetchar.h"
//#include "externals/sqlite/sha512/sha512_helper.h"


// COnlineAdvices dialog

IMPLEMENT_DYNAMIC(COnlineAdvices, CDialog)

COnlineAdvices::COnlineAdvices(CWnd* pParent /*=NULL*/)
	: CDialog(COnlineAdvices::IDD, pParent)
{
	dRate = -1;
}

COnlineAdvices::~COnlineAdvices()
{
}

void COnlineAdvices::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_rate, stat_rate);
	DDX_Control(pDX, IDC_CHECK1, check_details);
	DDX_Control(pDX, IDC_SLIDER4, slider_rate);
	DDX_Control(pDX, IDC_SLIDER1, slider_rate1);
	DDX_Control(pDX, IDC_SLIDER3, slider_rate2);
	DDX_Control(pDX, IDC_SLIDER2, slider_rate3);
	DDX_Control(pDX, IDC_STATIC1, stat_rate_desc);
	DDX_Control(pDX, IDC_STATIC2, stat_rate_desc1);
	DDX_Control(pDX, IDC_STATIC3, stat_rate_desc2);
	DDX_Control(pDX, IDC_STATIC4, stat_rate_desc3);
	DDX_Control(pDX, IDC_EDIT1, edit_message);
}


BEGIN_MESSAGE_MAP(COnlineAdvices, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &COnlineAdvices::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &COnlineAdvices::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COnlineAdvices::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &COnlineAdvices::OnBnClickedCheck1)
	ON_WM_HSCROLL()
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, &COnlineAdvices::OnNMCustomdrawSlider4)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &COnlineAdvices::OnNMCustomdrawSlider1)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &COnlineAdvices::OnNMCustomdrawSlider3)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &COnlineAdvices::OnNMCustomdrawSlider2)
	ON_BN_CLICKED(IDC_BUTTON2, &COnlineAdvices::OnBnClickedButton2)
END_MESSAGE_MAP()

//если все сообщения показывались раньше, то снова берется с самой высокой 
//	оценкой и записывается в журнал как показанное во второй раз
BOOL COnlineAdvices::OnInitDialog() 
{
	CDialog::OnInitDialog();
	slider_rate .SetRange(1,6);
	slider_rate1.SetRange(1,6);
	slider_rate2.SetRange(1,6);
	slider_rate3.SetRange(1,6);
	slider_rate .SetPos(6);
	slider_rate1.SetPos(6);
	slider_rate2.SetPos(6);
	slider_rate3.SetPos(6);
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1763));
	string ip = trif.getSqlIp(path_actuser.c_str());
	if (ip == "")
	{
		abnormalExit("get_sql_ip_error!");
		return FALSE;
	}
	mySql = new ConnWorkMySql(ip, "eactivity_user", "djgvyetgjdbu", 
		"eactivity_text_messages", 3306);
	if (mySql->connectError)
	{
		abnormalExit("sql_connect_error!");
		return FALSE;
	}
//	mySql = new ConnWorkMySql("localhost", "eactivity_user", "djgvyetgjdbu", 
//		"eactivity_text_messages", 3306);
	mysql_row *myRows;
	mySql->query("SET NAMES \'cp1251\'");
	myRows = mySql->fetch(mySql->query(
		"SELECT * FROM text_mes WHERE moderate_type = 1 ORDER BY rate DESC;"));
	int minShown = 9999999; int index_min=0;
	bool shown = false;
	for (int ii = 0; ii < myRows->fields; ii++)
	{
		int shwnCount = isMessageShown(atoi(myRows[ii].row[0]._data.c_str()));
		if (!shwnCount)
		{
			ShowMessage(atoi(myRows[ii].row[0]._data.c_str()), 
				myRows[ii].row[1]._data, 
				myRows[ii].row[2]._data, 
				myRows[ii].row[3]._data, 
				atoi(myRows[ii].row[4]._data.c_str()), 
				atof(myRows[ii].row[5]._data.c_str()), 
				atof(myRows[ii].row[6]._data.c_str()), 
				atof(myRows[ii].row[7]._data.c_str()), 
				atof(myRows[ii].row[8]._data.c_str())
				/*, atof(myRows[ii].row[8]._data.c_str())*/);
			shown = true;
			break;
		} else {
			if (shwnCount < minShown)
			{
				minShown = shwnCount; index_min = ii;
			}
		}
	}
	//если все сообщения уже показаны, то показываем сообщение, которое 
			//меньше других показывалось
	if (!shown)
	{
		ShowMessage(atoi(myRows[index_min].row[0]._data.c_str()), 
			myRows[index_min].row[1]._data, 
			myRows[index_min].row[2]._data, 
			myRows[index_min].row[3]._data, 
			atoi(myRows[index_min].row[4]._data.c_str()), 
			atof(myRows[index_min].row[5]._data.c_str()), 
			atof(myRows[index_min].row[6]._data.c_str()), 
			atof(myRows[index_min].row[7]._data.c_str()), 
			atof(myRows[index_min].row[8]._data.c_str())
			/*, atof(myRows[ii].row[8]._data.c_str())*/);
	}
	char ch[2048];
	CAddOnlineAdvice dialAddAdvice;
	userSID = dialAddAdvice.getUserSID();
	noVote = false;
	if (userSID.length())
	{
		sprintf_s(ch, "SELECT * FROM rates WHERE id = %d AND user_sid = '%s';", id_mes, userSID.c_str());
		myRows = mySql->fetch(mySql->query(ch));
		if (myRows && myRows->fields>0)
			noVote = true;
	}
	if (noVote)
	{	//отменяем голосование - уже раньше за это выражение голосовали
		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SLIDER4)->ShowWindow(SW_HIDE);
	}
	delete myRows;
	return TRUE;
}

// экстренный выход из диалога
BOOL COnlineAdvices::abnormalExit(CString textError) 
{
	CStdioFile sfLog;
	string fileName = path_actuser + "journal_online_advices.txt";
	if (sfLog.Open(fileName.c_str(), CFile::modeWrite) ||
		sfLog.Open(fileName.c_str(), CFile::modeWrite|CFile::modeCreate))
	{
		sfLog.SeekToEnd();
		CTime ct=CTime::GetCurrentTime();
		char ch[1024];
		sprintf_s(ch, "%02d.%02d.%02d    %02d:%02d:%02d\t %s\n", 
			ct.GetYear(), ct.GetMonth(), ct.GetDay(),
			ct.GetHour(), ct.GetMinute(), ct.GetSecond(), textError);
		sfLog.WriteString(ch);
		sfLog.Close();
	}
	CDialog::OnCancel();
	return TRUE;
}

void COnlineAdvices::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)  
{
	 CSliderCtrl* pSlider = reinterpret_cast<CSliderCtrl*>(pScrollBar);
	 int sliderNum = -1;
	 if (pSlider == &slider_rate)  
		 sliderNum = 0;
	 else if (pSlider == &slider_rate1)  
		 sliderNum = 1;
	 else if (pSlider == &slider_rate2)  
		 sliderNum = 2;
	 else if (pSlider == &slider_rate3)  
		 sliderNum = 3;
// 	 switch(nSBCode)
// 	 {
// 	 case TB_LINEUP:  
// 	 case TB_LINEDOWN:  
// 	 case TB_PAGEUP:  
// 	 case TB_PAGEDOWN:  
// 	 case TB_THUMBPOSITION:  
// 	 case TB_TOP:  
// 	 case TB_BOTTOM:  
// 	 case TB_THUMBTRACK:  
// 	 case TB_ENDTRACK:  
// 	 default:  
// 		 break;
// 	 
	 CString str;
	 char ch[1024];
	 switch (sliderNum)
	 {
	  	 case 0:  
			 str.LoadString(trif.GetIds(IDS_STRING1761));
			 sprintf_s(ch, str, slider_rate.GetPos());
			 str = ch;
			 if (slider_rate.GetPos() == 6)
				 str.Replace("(6)", "(?)");
			 stat_rate_desc.SetWindowText(str);
			break;
		case 1:
			if (slider_rate1.GetPos() < 6)
			{
				str.LoadString(trif.GetIds(IDS_STRING1763+2*slider_rate1.GetPos()));
			} else {
				str.LoadString(trif.GetIds(IDS_STRING1763));
			}
			stat_rate_desc1.SetWindowText(str);
			break;
		case 2:
			if (slider_rate2.GetPos() < 6)
			{
				str.LoadString(trif.GetIds(IDS_STRING1775+2*slider_rate2.GetPos()));
			} else {
				str.LoadString(trif.GetIds(IDS_STRING1775));
			}
			stat_rate_desc2.SetWindowText(str);
			break;
		case 3:
			if (slider_rate3.GetPos() < 6)
			{
				str.LoadString(trif.GetIds(IDS_STRING1787 + 2*slider_rate3.GetPos()));
			} else {
				str.LoadString(trif.GetIds(IDS_STRING1787));
			}
			stat_rate_desc3.SetWindowText(str);
			break;
	 }
	 CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void COnlineAdvices::OnBnClickedButton1()
{
	CAddOnlineAdvice dialAddAdvice;
	dialAddAdvice.path_actuser = path_actuser;
	dialAddAdvice.DoModal();
}

//Проверка: показывалось ли сообщение ранее (присутствует в 
	//журнале показанных сообщений)
BOOL COnlineAdvices::isMessageShown(int id_mes)
{
	string fileName = path_actuser + "journal_online_advices.txt";
	ifstream ifstr(fileName.c_str());
	if (ifstr==NULL)
		return FALSE;
	char ch[1024];
	string str;
	char patt[] = "(id_mes = %d";
	char for_find[100];
	sprintf_s(for_find, patt, id_mes);
	int res=0;
	for (;;)
	{
		ifstr.getline(ch, 1024, '\n');
		str = ch;
		if (str.find(for_find)!=std::string::npos)
		{
			res++;
		}
		if (!ifstr)
		{
			ifstr.close();
			return res;
		}
	}
	ifstr.close();
	return res;
}

void COnlineAdvices::ShowMessage(int id, string message, string owner_mes, 
		string user, int moderate_type, double rate, double rate1, double rate2, 
		double rate3/*, float rate4*/)
{
	LOGFONT lf;
	CFont* old = edit_message.GetFont();
	old->GetLogFont(&lf);
	CFont newfont;
	newfont.CreateFont(lf.lfHeight+30, 0, lf.lfEscapement,  lf.lfOrientation, 
		lf.lfWeight, lf.lfItalic, lf.lfUnderline,
		lf.lfStrikeOut, lf.lfCharSet, lf.lfOutPrecision, 
		lf.lfClipPrecision,  lf.lfQuality, lf.lfPitchAndFamily, lf.lfFaceName); 
	edit_message.SetFont(&newfont);
	char ch[5000];
	CString patMes;
	patMes.LoadString(trif.GetIds(IDS_STRING1849));
	sprintf_s(ch, patMes, message.c_str(), owner_mes.c_str(), user.c_str());
	edit_message.SetWindowText(ch);

	id_mes = id;
	dRate  = rate; 
	dRate1 = rate1;
	dRate2 = rate2;
	dRate3 = rate3;

	CStdioFile sfLog;
	string fileName = path_actuser + "journal_online_advices.txt";
	if (!sfLog.Open(fileName.c_str(), CFile::modeWrite))
		if (!sfLog.Open(fileName.c_str(), CFile::modeWrite|CFile::modeCreate))
			return;
	sfLog.SeekToEnd();
	CTime ct=CTime::GetCurrentTime();
	sprintf_s(ch, "%02d.%02d.%02d    %02d:%02d:%02d\t %s (id_mes = %d, user = %s, owner = %s, rate = %0.2f)\n", 
		ct.GetYear(), ct.GetMonth(), ct.GetDay(),
		ct.GetHour(), ct.GetMinute(), ct.GetSecond(), 
		message.c_str(), id, user.c_str(), owner_mes.c_str(), dRate);
	sfLog.WriteString(ch);
	sfLog.Close();

	OnBnClickedCheck1();
}

void COnlineAdvices::OnBnClickedOk()
{
	OnOK();
}

void COnlineAdvices::OnCancel()
{
	CDialog::OnCancel();
}

void COnlineAdvices::OnBnClickedCancel()
{
	if (!noVote && slider_rate .GetPos()==6 && slider_rate1.GetPos()==6 && 
		slider_rate2.GetPos()==6 && slider_rate3.GetPos()==6)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1799));
		return;
	}
	char ch[4096];
	sprintf_s(ch, 
		"insert into rates (id, rate, rate1, rate2, rate3, rate4, user_sid) values (%d,'%d','%d','%d','%d','%d','%s');",
		id_mes, slider_rate.GetPos(), slider_rate1.GetPos(), slider_rate2.GetPos(), slider_rate3.GetPos(), 0, userSID.c_str());
	CString strReq = ch;
	strReq.Replace("'6'", "NULL"); //6-ка - это отсуствие голоса и для более 
									//точного вычисления среднего ставим оценку NULL
	string sReq = strReq;
	mySql->query(sReq);
	OnCancel();
	CDialog::OnCancel();
}

void COnlineAdvices::OnBnClickedCheck1()
{
	if (dRate==-1)
		return;
	char ch_mes[5000];
	CString sRate;
	if (dRate==0 && dRate1==0 && dRate2==0 && dRate3==0)
	{
		stat_rate.ShowWindow(SW_HIDE);
		check_details.ShowWindow(SW_HIDE);
	}
	if (check_details.GetCheck())
	{
		sRate.LoadString(trif.GetIds(IDS_STRING1757));
		sprintf_s(ch_mes, sRate, dRate, dRate1, dRate2, dRate3);
		stat_rate.SetWindowText(ch_mes);
	} else {
		sRate.LoadString(trif.GetIds(IDS_STRING1759));
		sprintf_s(ch_mes, sRate, dRate);
		stat_rate.SetWindowText(ch_mes);
	}
}

void COnlineAdvices::OnNMCustomdrawSlider4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1761));
	char ch[1024];
	sprintf_s(ch, str, slider_rate.GetPos());
	str = ch;
	if (slider_rate.GetPos() == 6)
		str.Replace("(6)", "(?)");
	stat_rate_desc.SetWindowText(str);
	*pResult = 0;
}

void COnlineAdvices::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString str;
	if (slider_rate1.GetPos() < 6)
	{
		str.LoadString(trif.GetIds(IDS_STRING1763+2*slider_rate1.GetPos()));
	} else {
		str.LoadString(trif.GetIds(IDS_STRING1763));
	}
	stat_rate_desc1.SetWindowText(str);
	*pResult = 0;
}

void COnlineAdvices::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString str;
	if (slider_rate2.GetPos() < 6)
	{
		str.LoadString(trif.GetIds(IDS_STRING1775+2*slider_rate2.GetPos()));
	} else {
		str.LoadString(trif.GetIds(IDS_STRING1775));
	}
	stat_rate_desc2.SetWindowText(str);
	*pResult = 0;
}

void COnlineAdvices::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	CString str;
	if (slider_rate3.GetPos() < 6)
	{
		str.LoadString(trif.GetIds(IDS_STRING1787 + 2*slider_rate3.GetPos()));
	} else {
		str.LoadString(trif.GetIds(IDS_STRING1787));
	}
	stat_rate_desc3.SetWindowText(str);
	*pResult = 0;
}

void COnlineAdvices::OnBnClickedButton2()
{
	string fileName = path_actuser + "journal_online_advices.txt";
	ShellExecute(0,"open", "notepad.exe", fileName.c_str(), NULL,SW_MAXIMIZE); 
}
