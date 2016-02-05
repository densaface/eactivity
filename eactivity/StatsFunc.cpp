#include "StatsFunc.h"

StatsFunc::StatsFunc(void)
{
}

StatsFunc::~StatsFunc(void)
{
}

void Activity::clearItem()
{
	hwMain=0;
	hwChil=0;
	exe="";
	capt="";
	comment="";
	sumActs=0;		// ��������� ���������� ������/������� ����������
	usefulActs=0;		// �����/������� ���������� ����������� ��� ��������
	hour=0;
	sumTime=0; //�����, ��������� �����-���� ���������, � �� 
	usefulTime=0; //�����, ����������� ��� �������� � ������ ���������������� �������������
}

void StatsFunc::FormatSeconds(char (&ch)[100], float secs) 
{
	int abs_secs=abs((int)secs);
	if (abs_secs < 1)
	{
		strcpy_s(ch, "-");
		return;
	}
	if (abs_secs>86400)
	{
		sprintf_s(ch, "%dd.%dh:%dm", (int)secs/86400, (abs_secs % 86400)/3600, (abs_secs % 3600)/60);
	} else 
		if (abs_secs>3600)
		{
			sprintf_s(ch, "%dh:%dm", (int)secs/3600, (abs_secs % 3600)/60);
		} else {
			if (abs_secs>60)
			{
				sprintf_s(ch, "%dm:%ds", (int)secs/60, abs_secs % 60);
			} else {
				sprintf_s(ch, "%ds", (int)secs);
			}
		}
}

bool StatsFunc::LoadFileMonth(string fname, activ &forLoad1, float &sumTime, float &sumUsefulTime, int &sumActs, int &sumUsefulActs)
{
	ifstream ifstr(fname.c_str());
	if (ifstr)
	{
		char ch[1024];
		ifstr.getline(ch, 100);

		Activity tmpForLoad;
		tmpForLoad.clearItem();
		while (ifstr)
		{
			string sdate;
			ifstr>>sdate;
			ifstr.get();
			ifstr>>tmpForLoad.sumActs;
			sumActs+=tmpForLoad.sumActs;
			ifstr.get();
			if (!ifstr)
				break;
			ifstr>>tmpForLoad.usefulActs;
			sumUsefulActs+=tmpForLoad.usefulActs;
			ifstr>>tmpForLoad.sumTime;
			sumTime+=tmpForLoad.sumTime;
			if (strcmp(ch, "ver=0.1")!=0) {
				//������ � ������ ������ �� ����������� �������� �����
				ifstr>>tmpForLoad.usefulTime;
				sumUsefulTime+=tmpForLoad.usefulTime;
			}
			forLoad1[sdate]=tmpForLoad;
			if (!ifstr)
				break;
		}
		ifstr.close();
	}
	LoadMonthFromStatDays(forLoad1, fname.substr(fname.length()-21, 18), sumTime, sumActs, sumUsefulActs);
	return true;
}

//���������� ������� ����������, ���� ��� �� ���� � ����� ���������� �� �����
void StatsFunc::LoadMonthFromStatDays(activ &forLoad1, string mon, float &sumTime, int &sumAct, int &sumUsefulActs) 
{
	WIN32_FIND_DATA FFData;
	string for_find=path_actuser+mon+"*.a";
	HANDLE hFind = FindFirstFile(for_find.c_str(), &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			SumDayStat(forLoad1, path_actuser+FFData.cFileName, sumTime, sumAct, sumUsefulActs);
		} while(FindNextFile(hFind, &FFData));
	}
}

//��������� ���� ���������� � �������� �������������, ������� �� ���� � ������� 
//		�������� ����� ����������
void StatsFunc::SumDayStat(activ &forLoad1, string fname, float &sumTime, 
						   int &sumAct, int &sumUsefulActs) 
{
	activ::iterator iter=forLoad1.find(fname.substr(fname.length()-12, 10));
	if (iter!=forLoad1.end())
		return; //��� ��������� ���������� �� ���������

	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return;
	Activity tmpActiv;
	tmpActiv.sumActs=0;
	tmpActiv.sumTime=0;
	tmpActiv.usefulTime=0;
	tmpActiv.usefulActs=0;
	tmpActiv.capt="";
	tmpActiv.exe="";
	tmpActiv.comment="";
	tmpActiv.hwChil=0;
	tmpActiv.hwMain=0;

	char ch[1024];
	ifstr.getline(ch, 1024);
	while (ifstr)
	{
		void* tmpint;
		ifstr>>tmpint;
		ifstr.get();
		ifstr>>tmpint;
		ifstr.get();
		if (!ifstr)
			break;
		int tmpint2;
		ifstr>>tmpint2;
		tmpActiv.sumActs+=tmpint2;
		ifstr.get();
		ifstr>>tmpint2;
		tmpActiv.usefulActs+=tmpint2;
		ifstr.get();
		ifstr>>tmpint2;
		tmpActiv.sumTime+=tmpint2;
		ifstr.get();
		ifstr.getline(ch, 1024);
		if (!ifstr)
			break;
	}
	ifstr.close();
	sumTime+=tmpActiv.sumTime;
	sumAct+=tmpActiv.sumActs;
	sumUsefulActs+=tmpActiv.usefulActs;
	forLoad1[fname.substr(fname.length()-12, 10)]=tmpActiv;
}

void StatsFunc::LoadAllYears(activ &aCurYear) 
{
	string strf=path_actuser+"activ_user_all_months.ayr";
	float sumTime=0, sumUsefulTime=0;
	int sumActs=0, sumUsefulActs=0;
	LoadFileMonth(strf, aCurYear, sumTime, sumUsefulTime, sumActs, sumUsefulActs);
	WIN32_FIND_DATA FFData;
	string filePattern = path_actuser+"activ_user_*.am";
	HANDLE hFind = FindFirstFile(filePattern.c_str(), &FFData);
	//���������� ��������� �� ����������, ����� ������� ������������
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			string foundFileDate = FFData.cFileName;
			if (foundFileDate.size()!=21)
				continue;
			foundFileDate = foundFileDate.substr(11, 7);
			if (aCurYear.find(foundFileDate)==aCurYear.end())
			{
				Activity tmpMonActiv;
				tmpMonActiv.clearItem();
				aCurYear[foundFileDate] = tmpMonActiv;
			}
		} while(FindNextFile(hFind, &FFData));
		FindClose(hFind);
	}
}

void StatsFunc::LoadYear(activ &aCurYear, string fname) 
{
	char date[28];
	SYSTEMTIME st;
	GetLocalTime(&st);
	GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "activ_user_yyyy", date, 26);
	strcat_s(date, ".ayr");
	curYear=date;

	float sumTime=0;
	int sumActs=0, sumUsefulActs=0;
	string strf=path_actuser+curYear;
	ifstream ifstr(fname == "" ? strf.c_str() : fname.c_str());
	if (ifstr)
	{
		char ch[1024];
		ifstr.getline(ch, 100);

		float ver;
		sscanf_s(ch, "ver=%f", &ver);

		Activity tmpForLoad;
		tmpForLoad.capt="";
		tmpForLoad.exe="";
		tmpForLoad.comment="";
		tmpForLoad.hwChil=0;
		tmpForLoad.hwMain=0;
		while (ifstr)
		{
			string sdate;
			ifstr>>sdate;
			ifstr.get();
			ifstr>>tmpForLoad.sumActs;
			sumActs+=tmpForLoad.sumActs;
			ifstr.get();
			if (!ifstr)
				break;
			ifstr>>tmpForLoad.usefulActs;
			sumUsefulActs+=tmpForLoad.usefulActs;
			ifstr>>tmpForLoad.sumTime;
			sumTime+=tmpForLoad.sumTime;
			if (ver>=0.2)
			{
				ifstr>>tmpForLoad.usefulTime;
			}
			aCurYear[sdate]=tmpForLoad;
			if (!ifstr)
				break;
		}
		ifstr.close();
	}
	LoadYearFromStatMons(aCurYear, curYear.substr(0, 15), sumTime, sumActs, sumUsefulActs);
}

//////////    ������� ���������� \\\\\\\\\\\\\\\\
//���������� �������� ����������, ���� ��� �� ���� � ����� ���������� �� ���
void StatsFunc::LoadYearFromStatMons(activ &aCurYear, string mon, float &sumTime, int &sumAct, int &sumUsefulActs) 
{
	WIN32_FIND_DATA FFData;
	string for_find=path_actuser+mon+"*.am";
	HANDLE hFind = FindFirstFile(for_find.c_str(), &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			SumMonStat(aCurYear, path_actuser+FFData.cFileName, sumTime, sumAct, sumUsefulActs);
		} while(FindNextFile(hFind, &FFData));
	}
}

void StatsFunc::SumMonStat(activ &aCurYear, string fname, float &sumTime, int &sumAct, int &sumUsefulActs) 
{
	activ::iterator iter=aCurYear.find(fname.substr(fname.length()-10, 7));
	if (iter!=aCurYear.end())
		return; //��� ��������� ���������� �� ���������

	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return;
	Activity tmpActiv;
	tmpActiv.sumActs=0;
	tmpActiv.sumTime=0;
	tmpActiv.usefulTime=0;
	tmpActiv.usefulActs=0;
	tmpActiv.capt="";
	tmpActiv.exe="";
	tmpActiv.comment="";
	tmpActiv.hwChil=0;
	tmpActiv.hwMain=0;

	char ch[1024];
	ifstr.getline(ch, 1024);
	while (ifstr)
	{
		int tmpint;
		string sdate;
		ifstr>>sdate;
		ifstr.get();
		if (!ifstr)
			break;
		ifstr>>tmpint;
		tmpActiv.sumActs+=tmpint;
		ifstr.get();
		if (!ifstr)
			break;
		ifstr>>tmpint;
		tmpActiv.usefulActs+=tmpint;
		ifstr>>tmpint;
		tmpActiv.sumTime+=tmpint;
		if (!ifstr)
			break;
	}
	ifstr.close();
	sumTime+=tmpActiv.sumTime;
	sumAct+=tmpActiv.sumActs;
	sumUsefulActs+=tmpActiv.usefulActs;
	aCurYear[fname.substr(fname.length()-10, 7)]=tmpActiv;
}

void StatsFunc::ApplyFont(float secs1, float secs2, int font_size, 
	BOOL bold, BOOL hide_description, 
	CString faceFont, CXHTMLStatic &stat_day_adv, CXHTMLStatic &stat_hour_adv,
	CStatic &stat_day_description, CStatic &stat_hour_description, 
	bool showProgress, 
	HWND hwndParent, int RR, int GG, bool resizeWins)
{
	char fmtSecs[100];
	char res[300];
	if (secs1!=NULL)
	{
		FormatSeconds(fmtSecs, secs1);
		sprintf_s(res, "%s<CENTER><font SIZE=\"+%d\" COLOR=\"%d,%d,0\" %s>%s%s</font></CENTER>%s", 
			bold ? "<b>" : "", font_size, 
			RR, GG, 
			//������������� ����� �� �������, ����� ���� ���������� 1 � 1 � ����������
			faceFont == "" ? "" : ("FACE=\"" + faceFont + "\""), 
			secs1 > 0 ? "+" : "", fmtSecs,
			bold ? "</b>" : "");
		stat_day_adv.SetWindowText(res);
	}
	if (secs2!=NULL)
	{
		FormatSeconds(fmtSecs, secs2);
		sprintf_s(res, "%s<CENTER><font SIZE=\"+%d\" COLOR=\"%d,%d,0\" %s>%s%s</font></CENTER>%s", 
			bold ? "<b>" : "", font_size, 
			RR, GG, 
			//������������� ����� �� �������, ����� ���� ���������� 1 � 1 � ����������
			faceFont == "" ? "" : ("FACE=\"" + faceFont + "\""), 
			secs2 > 0 ? "+" : "", fmtSecs,
			bold ? "</b>" : "");
		stat_hour_adv.SetWindowText(res);
	}
	if (!resizeWins)
		return;
	CString str;
	CRect hourRect, dayRect, dayDescRect, hourDescRect;
	stat_day_adv .GetWindowRect(dayRect);
	stat_hour_adv.GetWindowRect(hourRect);
	stat_day_description .GetWindowRect(dayDescRect);
	stat_hour_description.GetWindowRect(hourDescRect);
	CRect infoPanelRect;
	if (resizeWins && secs1==NULL)
	{	//�������� ������ ����������
		GetWindowRect(hwndParent, infoPanelRect);
		int newWidth  = (hide_description ? 80 : 140) + 
			(int)((hide_description ? 3.8 : 1.7)*font_size);
		int delta_x = (newWidth-infoPanelRect.Width())/2;
		int newHeight = (hide_description ? 60 : 100) + 
			(int)((hide_description ? 3 : 2.1)*font_size);
		int delta_y = (newHeight-infoPanelRect.Height())/2;
		infoPanelRect.right=infoPanelRect.left + newWidth;
		infoPanelRect.bottom=infoPanelRect.top + newHeight;// + (showProgress ? 50 : 0)
 		dayRect+=CPoint(delta_x, 0);
 		hourRect+=CPoint(delta_x, 0);
 		dayDescRect+=CPoint(delta_x, 0);
 		hourDescRect+=CPoint(delta_x, 0);
	}
	//������� ������� � ������ ������������� ������� ������
	double coef=1.1;
	if (font_size>5)
		coef = 1.2;
// 	switch (font_size)
// 	{
// 	case 2:
// 		coef = 1.5;
// 		break;
// 	case 6:
// 	case 3:
// 		coef = 1.4;
// 		break;
// 	}
	int gap = 0;//���������� ����� ����������
	dayRect.bottom = dayRect.top + 14 + (LONG)(coef*font_size);
	if (hide_description)
	{	//�������� ������� ��������
		dayRect.bottom = dayDescRect.top+dayRect.Height();
		dayRect.top = dayDescRect.top;
		hourRect.bottom = dayRect.bottom + gap + hourRect.Height();
		hourRect.top = dayRect.bottom + gap;
	} else {
		dayRect.bottom = dayDescRect.bottom+dayRect.Height()+4;
		dayRect.top = dayDescRect.bottom + gap;
		hourDescRect.bottom = dayRect.bottom + gap + hourDescRect.Height();
		hourDescRect.top = dayRect.bottom + gap;
		hourRect.bottom = dayRect.bottom + 2*gap + hourRect.Height() + hourDescRect.Height();
		hourRect.top = dayRect.bottom + 2*gap + hourDescRect.Height();
	}
	hourRect.bottom = hourRect.top + dayRect.Height();
	infoPanelRect.bottom = hourRect.bottom + 2;

	CPoint cp1=dayRect.TopLeft();
	CPoint cp2=dayRect.BottomRight();
	ScreenToClient(hwndParent, &cp1);
	ScreenToClient(hwndParent, &cp2);
	dayRect=CRect(cp1, cp2);
	stat_day_adv.MoveWindow(dayRect);

	cp1=hourDescRect.TopLeft();
	cp2=hourDescRect.BottomRight();
	ScreenToClient(hwndParent, &cp1);
	ScreenToClient(hwndParent, &cp2);
	hourDescRect=CRect(cp1, cp2);
	stat_hour_description.MoveWindow(hourDescRect);

	cp1=hourRect.TopLeft();
	cp2=hourRect.BottomRight();
	ScreenToClient(hwndParent, &cp1);
	ScreenToClient(hwndParent, &cp2);
	hourRect=CRect(cp1, cp2);
	stat_hour_adv.MoveWindow(hourRect);

	cp1=dayDescRect.TopLeft();
	cp2=dayDescRect.BottomRight();
	ScreenToClient(hwndParent, &cp1);
	ScreenToClient(hwndParent, &cp2);
	dayDescRect=CRect(cp1, cp2);
	stat_day_description.MoveWindow(dayDescRect);

	stat_hour_description.ShowWindow(hide_description ? SW_HIDE : SW_SHOW);
	stat_day_description .ShowWindow(hide_description ? SW_HIDE : SW_SHOW);

	if (resizeWins && secs1==NULL)
		MoveWindow(hwndParent, infoPanelRect.left, infoPanelRect.top, 
			infoPanelRect.Width(), infoPanelRect.Height(), FALSE);
}

BOOL StatsFunc::SendMailMessage(LPCTSTR szServer,
									UINT port, 
									LPCTSTR szFrom, 
									LPCTSTR szTo, 
									LPCTSTR szUser, 
									LPCTSTR szPas, 
									LPCTSTR szSubject, 
									CStringArray& saMessage)
{

	CSmtp mail;

	//#define test_gmail_tls

	bool bError = false;

	try
	{
#define test_gmail_ssl

#if defined(test_gmail_tls)
		mail.SetSMTPServer("smtp.gmail.com",587);
		mail.SetSecurityType(USE_TLS);
		mail.SetLogin(szUser);//"silencenotif@gmail.com"
		mail.SetPassword(szPas);//"yhfveus347tw272d%$"
		mail.SetSenderName("Silence Notif");
		mail.SetSenderMail(szUser);
		mail.SetReplyTo(szUser);
#elif defined(test_gmail_ssl)
		mail.SetSMTPServer("smtp.mail.ru",465);
		mail.SetSecurityType(USE_SSL);
		mail.SetLogin("denis_safonov_81@mail.ru");
		mail.SetPassword(szPas);
		mail.SetSenderName("ActivateMe");
		mail.SetSenderMail("denis_safonov_81@mail.ru");
		mail.SetReplyTo("denis_safonov_81@mail.ru");
#elif defined(test_hotmail_TLS)
		mail.SetSMTPServer("smtp.live.com",25);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_aol_tls)
		mail.SetSMTPServer("smtp.aol.com",587);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_yahoo_ssl)
		mail.SetSMTPServer("plus.smtp.mail.yahoo.com",465);
		mail.SetSecurityType(USE_SSL);
#endif
		CString str;
		//edit_theme.GetWindowText(str);
		mail.SetSubject(szSubject);
		//edit_to.GetWindowText(str);
		mail.AddRecipient(szTo);
		//	mail.AddRecipient("densaf.ace@gmail.com");
		//	mail.AddRecipient("dsafonov@parallels.com");
		mail.SetXPriority(XPRIORITY_NORMAL);
		mail.SetXMailer("The Bat! (v3.02) Professional");
		for (int ii=0; ii<saMessage.GetCount(); ii++)
		{
			mail.AddMsgLine(saMessage[ii]);
		}
		return mail.Send();
	}
	catch(ECSmtp e)
	{
		//	std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		AfxMessageBox(e.GetErrorText().c_str());
		//OnReport(e.GetErrorText().c_str());
		bError = true;
	}
	//if(!bError)
	//std::cout << "Mail was send successfully.\n";
	return !bError;
}