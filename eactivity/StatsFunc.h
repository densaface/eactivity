#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include "afxwin.h"
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
	int sumActs;		// суммарное количество кликов/нажатий клавиатуры
	int usefulActs;		// клики/нажатия клавиатуры засчитанные как полезные
	int hour;
	float sumTime; //время, уделенное какой-либо программе, в мс 
	float usefulTime; //время, засчитанное как полезное с учетом пользовательских коэффициентов
};

//структура для хранения активности только по EXE (сокращенная форма Activity)
struct ActivityExe
{
	string exe;//поле дублирующее ключ справочника, 
	// нужно для сортировки при перегоне справочника в векторный массив
	int sumActs;
	int usefulActs;
	int hour;
	float sumTime; //время, уделенное программе, в мс
	float usefulTime;
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
	void SumMonStat(activ &aCurYear, string fname, float &sumTime, int &sumAct, int &usefulActs);
	void SumDayStat(activ &forLoad1, string fname, float &sumTime, int &sumActs, int &usefulActs);
	void LoadMonthFromStatDays(activ &forLoad1, string mon, float &sumTime, int &sumActs, int &usefulActs);
	void LoadYearFromStatMons(activ &aCurYear, string mon, float &sumTime, int &sumAct, int &usefulActs);
	//для шифровки личных данных пользователя
	DWORD dwResult;
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	DWORD cbBlob;
public:
	string path_actuser;//папка где хранятся файлы с активностью пользователя
	StatsFunc(void);
	~StatsFunc(void);
	void SaveDayEncryptedFormat(string fileName, activ& Activ);
	void SaveDayOldFormat (string fileName, activ& Activ);
	bool LoadFileDayCrypt(string fname, activ &forLoad1);
	bool LoadFileDayOld(string fname, activ &forLoad1);
	bool LoadFileMonth(string fname, activ &forLoad1, float &sumTime, float &sumUsefulTime, int &sumActs, int &usefulActs);
	void LoadYear(activ &aCurYear, string fname="");
	void LoadAllYears(activ &aCurYear);
	void FormatSeconds(char (&ch)[100], float secs); 
	void ApplyFont(float secs1, float secs2, int font_size, BOOL bold, BOOL hide_description,  
		CString faceFont, CXHTMLStatic &stat_day_adv, CXHTMLStatic &stat_hour_adv,
		CStatic &stat_day_description, CStatic &stat_hour_description, 
		bool showProgress, 
		HWND hwndParent, int RR, int GG, bool resizeWins = false);
	BOOL SendMailMessage(LPCTSTR szServer,
		UINT port, 
		LPCTSTR szFrom, 
		LPCTSTR szTo, 
		LPCTSTR szUser, 
		LPCTSTR szPas, 
		LPCTSTR szSubject, 
		CStringArray& saMessage);
	//методы шифровки перед сохранением статистики в файл
	string DecryptFromFileToStr(string fileName, int numSymbVer);
	bool EncryptStrToFile(string Str, string fileName, string ver);
	bool InitCrypt(CString keyFile);
	HCRYPTKEY hSessionKey;
	string Private(string text, int comboPrivateCurSel, float usefulTime);

};
