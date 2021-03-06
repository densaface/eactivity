#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include "afxwin.h"
#include "afxinet.h"
#include <fstream>
#include "externals/XHTMLStatic.h"
#include "externals/openssl-0.9.8l/CSmtp.h"
#include <wincrypt.h>
#pragma once
using namespace std;

struct Activity
{
	void clearItem();
	HWND hwMain;
	HWND hwChil;
	string exe;
	string capt;
	string comment;
	double sumActs;		// ��������� ���������� ������/������� ����������
	double usefulActs;		// �����/������� ���������� ����������� ��� ��������
	int hour;
	float sumTime; //�����, ��������� �����-���� ���������, � �� 
	float usefulTime; //�����, ����������� ��� �������� � ������ ���������������� �������������
	string appliedRul; //������ �� ��������� �������
	string appliedProj; //��� ������������ ��� ������ �������
};

//��������� ��� �������� ���������� ������ �� EXE (����������� ����� Activity)
struct ActivityExe
{
	string exe;//���� ����������� ���� �����������, 
	// ����� ��� ���������� ��� �������� ����������� � ��������� ������
	double sumActs;
	double usefulActs;
	int hour;
	float sumTime; //�����, ��������� ���������, � ��
	float usefulTime;
	string appliedRul; //������ �� ��������� �������
	string appliedProj; //��� ������������ ��� ������ �������
};

typedef map<string, Activity, less<string> > activ;
typedef map<string, ActivityExe, less<string> > activ_exe;
typedef map<int, ActivityExe, less<int> > activ_hours;
typedef map<string, string, less<string> > forExe;
typedef map<HWND, string, less<HWND> > exeSpis;
typedef map<HWND, HWND, less<HWND> > GetParSpis;
class StatsFunc
{
	string curYear;
	void SumMonStat(activ &aCurYear, string fname, float &sumTime, 
		double &sumAct, double &usefulActs);
	void SumDayStat(activ &forLoad1, string fname, float &sumTime, 
		double &sumActs, double &usefulActs);
	void LoadMonthFromStatDays(activ &forLoad1, string mon, float &sumTime, 
		double &sumActs, double &usefulActs);
	void LoadYearFromStatMons(activ &aCurYear, string mon, float &sumTime, 
		double &sumAct, double &usefulActs);
	//��� �������� ������ ������ ������������
	DWORD dwResult;
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	DWORD cbBlob;
public:
	string path_actuser;//����� ��� �������� ����� � ����������� ������������
	StatsFunc(void);
	~StatsFunc(void);
	void SaveDayEncryptedFormat(string fileName, activ& Activ);
	void SaveMailsEncryptedFormat(string fileName);
	void SaveDayOldFormat (string fileName, activ& Activ);
	bool LoadFileDayCrypt(string fname, activ &forLoad1);
	bool LoadFileMailsCrypt(string fname);
	bool LoadFileDayOld(string fname, activ &forLoad1);
	bool LoadFileMonth(string fname, activ &forLoad1, float &sumTime, 
		float &sumUsefulTime, double &sumActs, double &usefulActs);
	void LoadYear(activ &aCurYear, string fname="");
	void LoadAllYears(activ &aCurYear);
	void FormatSeconds(char (&ch)[100], float secs); 
	void ApplyFont(float secs1, float secs2, int font_size, BOOL bold, BOOL hide_description,  
		CString faceFont, CXHTMLStatic &stat_day_adv, CXHTMLStatic &stat_hour_adv,
		CStatic &stat_day_description, CStatic &stat_hour_description, 
		bool showProgress, 
		HWND hwndParent, int RR, int GG, bool resizeWins = false);
	BOOL SendMailMessage(LPCTSTR szTo, LPCTSTR szSubject, CStringArray& saMessage);
	CStringArray saMails; //����� � ������ ��� �������� �� �����
	bool getMailsFromServer(CString path_activity);
	//������ �������� ����� ����������� ���������� � ����
	string DecryptFromFileToStr(string fileName, int numSymbVer);
	bool EncryptStrToFile(string Str, string fileName, string ver);
	bool InitCrypt(CString keyFile);
	HCRYPTKEY hSessionKey;
	string Private(string text, int comboPrivateCurSel, float usefulTime);

};
