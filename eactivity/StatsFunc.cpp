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
	sumActs=0;		// суммарное количество кликов/нажатий клавиатуры
	usefulActs=0;		// клики/нажатия клавиатуры засчитанные как полезные
	hour=0;
	sumTime=0; //время, уделенное какой-либо программе, в мс 
	usefulTime=0; //время, засчитанное как полезное с учетом пользовательских коэффициентов
}

//форматирование милисекунд в строку с адекватным отображением времени
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

static BYTE PrivateKeyWithExponentOfOne[] =
{
	0x07, 0x02, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00,
	0x52, 0x53, 0x41, 0x32, 0x00, 0x02, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0xAB, 0xEF, 0xFA, 0xC6,
	0x7D, 0xE8, 0xDE, 0xFB, 0x68, 0x38, 0x09, 0x92,
	0xD9, 0x42, 0x7E, 0x6B, 0x89, 0x9E, 0x21, 0xD7,
	0x52, 0x1C, 0x99, 0x3C, 0x17, 0x48, 0x4E, 0x3A,
	0x44, 0x02, 0xF2, 0xFA, 0x74, 0x57, 0xDA, 0xE4,
	0xD3, 0xC0, 0x35, 0x67, 0xFA, 0x6E, 0xDF, 0x78,
	0x4C, 0x75, 0x35, 0x1C, 0xA0, 0x74, 0x49, 0xE3,
	0x20, 0x13, 0x71, 0x35, 0x65, 0xDF, 0x12, 0x20,
	0xF5, 0xF5, 0xF5, 0xC1, 0xED, 0x5C, 0x91, 0x36,
	0x75, 0xB0, 0xA9, 0x9C, 0x04, 0xDB, 0x0C, 0x8C,
	0xBF, 0x99, 0x75, 0x13, 0x7E, 0x87, 0x80, 0x4B,
	0x71, 0x94, 0xB8, 0x00, 0xA0, 0x7D, 0xB7, 0x53,
	0xDD, 0x20, 0x63, 0xEE, 0xF7, 0x83, 0x41, 0xFE,
	0x16, 0xA7, 0x6E, 0xDF, 0x21, 0x7D, 0x76, 0xC0,
	0x85, 0xD5, 0x65, 0x7F, 0x00, 0x23, 0x57, 0x45,
	0x52, 0x02, 0x9D, 0xEA, 0x69, 0xAC, 0x1F, 0xFD,
	0x3F, 0x8C, 0x4A, 0xD0,

	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	0x64, 0xD5, 0xAA, 0xB1,
	0xA6, 0x03, 0x18, 0x92, 0x03, 0xAA, 0x31, 0x2E,
	0x48, 0x4B, 0x65, 0x20, 0x99, 0xCD, 0xC6, 0x0C,
	0x15, 0x0C, 0xBF, 0x3E, 0xFF, 0x78, 0x95, 0x67,
	0xB1, 0x74, 0x5B, 0x60,

	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static BYTE pbBlob[] =
{
	0x01, 0x02, 0x00, 0x00, 0x01, 0x68, 0x00, 0x00, 
	0x00, 0xA4, 0x00, 0x00, 0x9E, 0x41, 0x62, 0x32, 
	0x35, 0x00, 0xBB, 0x2A, 0xAA, 0xCC, 0xE6, 0x81, 
	0x6A, 0x35, 0x38, 0x37, 0xF9, 0x5D, 0xAE, 0x59, 
	0x08, 0xDD, 0x56, 0x04, 0x96, 0x14, 0x29, 0x27, 
	0x5D, 0x17, 0xB1, 0xE5, 0x05, 0xA8, 0xB6, 0x22, 
	0x54, 0xC7, 0x1C, 0x4C, 0x17, 0xBC, 0xA8, 0x0F, 
	0xEE, 0xD4, 0x90, 0x16, 0xDA, 0xCE, 0x27, 0x7A, 
	0xF5, 0x13, 0x45, 0xCC, 0xCA, 0x6A, 0xD2, 0x02, 
	0xA1, 0x85, 0x02, 0x00, 
};
long file_length(const char* filename)
{
	FILE *fp;
	long fsize = 0;
	errno_t err;
	err = fopen_s(&fp, filename,"rb");
	if (err == 0) {
		fseek(fp,0L,SEEK_END);
		fsize = ftell(fp);
		fclose(fp);
	}
	return fsize;
}

#include <strsafe.h>
void ErrorExit(LPTSTR lpszFunction) 
{ 
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
	StringCchPrintf((LPTSTR)lpDisplayBuf, 
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"), 
		lpszFunction, dw, lpMsgBuf); 
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw); 
}

bool StatsFunc::InitCrypt(CString keyFile)
{
	dwResult= 0;
	hProv = 0;
	hKey = 0;
	hSessionKey = 0;
	cbBlob = 76;

	if (!CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, 0))
	{
		dwResult = GetLastError();
		if (dwResult == NTE_BAD_KEYSET)
		{
			if (!CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
			{
				dwResult = GetLastError();
				AfxMessageBox("Error [0x%x]: CryptAcquireContext() failed.");
				return false;
			}
		} else {
			dwResult = GetLastError();
			return false;
		}
	}

	if (false) { // pbBlob
		if (!CryptImportKey(hProv, pbBlob, cbBlob, 0, 0, &hSessionKey))
		{
			ErrorExit(TEXT("CryptImportKey"));
			//dwResult = GetLastError();
			//AfxMessageBox("Error [0x%x]: CryptImportKey() failed.");
			return false;
		}
	} else { 
		if (!CryptImportKey(hProv, PrivateKeyWithExponentOfOne, 
			sizeof(PrivateKeyWithExponentOfOne), 0, 0, &hKey))
		{
			dwResult = GetLastError();
			AfxMessageBox("Error CryptImportKey() failed.");
			return false;
		}

		if (!CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hSessionKey))
		{
			dwResult = GetLastError();
			AfxMessageBox("Error CryptGenKey() failed.");
			return false;
		}	
	}
	return true;
}

//загрузка детализации активности дня в шифрованном формате (ver>=0.5)
// пример одной порции записи
//291516	291516		- через табулятор хэндлы окон
//1	1	1014	1014	- время и действия (полезные и не полезные)
//0	C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe	- час, экзешник, заголовок через табуляторы
//	- комментарий
//3 перехода строки
//другая порция
// Зашифрованный файл полностью распаковывается в единственную строчку decriptStr и поскольку объем 
// в 40 кб в среднем является весомым, то операции перераспределения памяти внутри строки 
// (удаление символов в начале переменной) будут времязатратными, поэтому обход строчки идет с 
// помощью локальных поисков границ для каждого кванта данных и их преобразование из строчного в нужный. 
// Поиск границ идет методом чередования, от одной границы дальше по переменной и копирование этого 
// кусочка переменной между границами
bool StatsFunc::LoadFileDayCrypt(string fname, activ &forLoad1) 
{
	string decriptStr;
	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return false;
	if (forLoad1.size())
		forLoad1.clear();
	char ch[1024];
	ifstr.getline(ch, 100);
	float ver;
	sscanf_s(ch, "ver=%f", &ver);
	ifstr.close();
	//if (ver<0.5)
	//{ решено пока сделать без криптования загрузку выгрузку файлов, на некоторых версиях виндоуз оно глючит
		return LoadFileDayOld(fname, forLoad1);
	//}
	decriptStr = DecryptFromFileToStr(fname, strlen(ch));
	int fi1=-1, fi2=-1;
	for (;;)
	{
		Activity tmpForSave;
		ActivityExe tmpForSave2;
		tmpForSave.usefulTime=0;
		tmpForSave.hour=0;
		tmpForSave2.usefulTime=0;
		tmpForSave2.hour=0;

		fi1 = decriptStr.find('\t', fi2+1);
		if (fi1 == -1)
			break;
		//decriptStr.substr(0, fi1);
		sscanf_s(decriptStr.substr(fi2+1, fi1-fi2-1).c_str(), "%x", &tmpForSave.hwMain);

		fi2 = decriptStr.find('\n', fi1+1);
		if (fi2 == -1)
			break;
		sscanf_s(decriptStr.substr(fi1+1, fi2-fi1-1).c_str(), "%x", &tmpForSave.hwChil);

		fi1 = decriptStr.find('\t', fi2+1);
		tmpForSave.sumActs = atoi(decriptStr.substr(fi2+1, fi1-fi2-1).c_str());
		tmpForSave2.sumActs=tmpForSave.sumActs;

		fi2 = decriptStr.find('\t', fi1+1);
		tmpForSave.usefulActs = atoi(decriptStr.substr(fi1+1, fi2-fi1-1).c_str());
		tmpForSave2.usefulActs=tmpForSave.usefulActs;

		fi1 = decriptStr.find('\t', fi2+1);
		tmpForSave .sumTime = (float)atof(decriptStr.substr(fi2+1, fi1-fi2-1).c_str());
		tmpForSave2.sumTime = tmpForSave.sumTime;

		fi2 = decriptStr.find('\n', fi1+1);
		tmpForSave .usefulTime = (float)atof(decriptStr.substr(fi1+1, fi2-fi1-1).c_str());
		tmpForSave2.usefulTime = tmpForSave.usefulTime;

		bool manual_add=false;
		fi1 = decriptStr.find('\t', fi2+1);
		string sHour = decriptStr.substr(fi2+1, fi1-fi2-1).c_str();
		if (sHour.length() && sHour[0]=='m')
		{	//вырезаем первый символ - признак ручной вставки
			manual_add = true;
			CString sCh = sHour.substr(1).c_str();
			tmpForSave2.hour=tmpForSave.hour=atoi(sHour.substr(1).c_str());//sCh.Mid(1)
		} else {
			tmpForSave2.hour=tmpForSave.hour=atoi(sHour.c_str());
		}

		fi2 = decriptStr.find('\t', fi1+1);
		tmpForSave2.exe = tmpForSave.exe = decriptStr.substr(fi1+1, fi2-fi1-1);

		fi1 = decriptStr.find('\n', fi2+1);
		tmpForSave.capt = decriptStr.substr(fi2+1, fi1-fi2-1);

		fi2 = decriptStr.find('\n', fi1+1);
		tmpForSave.comment = decriptStr.substr(fi1+1, fi2-fi1-1);
		fi2 = decriptStr.find("\n\n", fi2+1)+1;

		if (manual_add)
			sprintf_s(ch, "m%d\t", tmpForSave.hour);
		else sprintf_s(ch, "%d\t", tmpForSave.hour);
		forLoad1[ch + tmpForSave.exe + '\t' + tmpForSave.capt] = tmpForSave;
	}
	return true;
}

//загрузка криптованного файла с эмейлами и извлечение их в массив saMails
bool StatsFunc::LoadFileMailsCrypt(string fname) 
{
	string decriptStr;
	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return false;
	char ch[1024];
	ifstr.getline(ch, 100);
	int ver;
	sscanf_s(ch, "ver=%d", &ver);
	ifstr.close();
	decriptStr = DecryptFromFileToStr(fname, strlen(ch));
	int fi1=-1, fi2=-1;
	for (;;)
	{
		CString login;
		CString pas;

		fi1 = decriptStr.find('\n', fi2+1);
		if (fi1 == -1)
			break;
		login = decriptStr.substr(fi2+1, fi1-fi2-1).c_str();

		fi2 = decriptStr.find('\n', fi1+1);
		if (fi2 == -1)
			break;
		pas = decriptStr.substr(fi1+1, fi2-fi1-1).c_str();

		fi1 = decriptStr.find('\n', fi2+1);
		fi2 = decriptStr.find('\n', fi1+1);
		fi1 = decriptStr.find('\n', fi2+1);
		saMails.Add(login);
		saMails.Add(pas);
	}
	return true;
}

//загрузка детализации активности дня в старом формате (ver<0.5)
bool StatsFunc::LoadFileDayOld(string fname, activ &forLoad1) 
{
	ifstream ifstr(fname.c_str());
	if (ifstr==NULL)
		return false;
	if (forLoad1.size())
		forLoad1.clear();
	char ch[1024];
	ifstr.getline(ch, 100);
	float ver;
	sscanf_s(ch, "ver=%f", &ver);
	for (;;)
	{
		Activity tmpForSave;
		ActivityExe tmpForSave2;
		tmpForSave.usefulTime=0;
		tmpForSave.hour=0;
		tmpForSave2.usefulTime=0;
		tmpForSave2.hour=0;
		void* tmpint;
		ifstr>>tmpint;
		tmpForSave.hwMain=(HWND)tmpint;
		ifstr.get();
		ifstr>>tmpint;
		tmpForSave.hwChil=(HWND)tmpint;
		ifstr.get();
		if (!ifstr)
			break;
		ifstr>>tmpForSave.sumActs;
		tmpForSave2.sumActs=tmpForSave.sumActs;
		ifstr.get();
		ifstr>>tmpForSave.usefulActs;
		tmpForSave2.usefulActs=tmpForSave.usefulActs;
		ifstr.get();
		ifstr>>tmpForSave.sumTime;
		tmpForSave2.sumTime=tmpForSave.sumTime;
		if (ver>=0.3)
		{
			ifstr.get();
			ifstr>>tmpForSave.usefulTime;
			tmpForSave2.usefulTime=tmpForSave.usefulTime;
		}
		ifstr.get();
		int tmpint2;
		bool manual_add=false;
		if (ver<0.2)
		{
			ifstr>>tmpint2;
		} else {
			ifstr.getline(ch, 1024, '\t');
			if (strlen(ch)>0 && ch[0]=='m')
			{	//вырезаем первый символ
				manual_add = true;
				CString sCh = ch;
				tmpForSave2.hour=tmpForSave.hour=atoi(sCh.Mid(1));
			} else {
				tmpForSave2.hour=tmpForSave.hour=atoi(ch);
			}
		}
		ifstr.getline(ch, 1024, '\t');
		tmpForSave2.exe=tmpForSave.exe=ch;
		if (ver>=0.4)
		{
			ifstr.getline(ch, 1024, '\t');
			tmpForSave.capt=ch;
			ifstr.getline(ch, 1024);
			tmpForSave.comment=ch;
		} else {
			ifstr.getline(ch, 1024);
			tmpForSave.capt=ch;
		}
		if (manual_add)
			sprintf_s(ch, "m%d\t", tmpForSave.hour);
		else sprintf_s(ch, "%d\t", tmpForSave.hour);
		forLoad1[ch + tmpForSave.exe + '\t' + tmpForSave.capt] = tmpForSave;
		if (!ifstr)
			break;
	}
	ifstr.close();
	return true;
}

bool StatsFunc::LoadFileMonth(string fname, activ &forLoad1, float &sumTime, 
	float &sumUsefulTime, double &sumActs, double &sumUsefulActs)
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
				//только в первой версии не сохранялось полезное время
				ifstr>>tmpForLoad.usefulTime;
				sumUsefulTime+=tmpForLoad.usefulTime;
			}
			forLoad1[sdate]=tmpForLoad;
			if (!ifstr)
				break;
		}
		ifstr.close();
	}
	LoadMonthFromStatDays(forLoad1, fname.substr(fname.length()-21, 18), 
		sumTime, sumActs, sumUsefulActs);
	return true;
}

//подгружаем дневные статистики, если они не были в общем сохранении за месяц
void StatsFunc::LoadMonthFromStatDays(activ &forLoad1, string mon, float &sumTime, 
									  double &sumAct, double &sumUsefulActs) 
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

//подгрузка дней статистики в месячное представление, которых не было в сводном 
//		месячном файле статистики
void StatsFunc::SumDayStat(activ &forLoad1, string fname, float &sumTime, 
						   double &sumAct, double &sumUsefulActs) 
{
	activ::iterator iter=forLoad1.find(fname.substr(fname.length()-12, 10));
	if (iter!=forLoad1.end())
		return; //уже имеющуюся статистику не обновляем

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
	double sumActs=0, sumUsefulActs=0;
	LoadFileMonth(strf, aCurYear, sumTime, sumUsefulTime, sumActs, sumUsefulActs);
	WIN32_FIND_DATA FFData;
	string filePattern = path_actuser+"activ_user_*.am";
	HANDLE hFind = FindFirstFile(filePattern.c_str(), &FFData);
	//подгружаем указатели на статистики, файлы которых присутствуют
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
	double sumActs=0, sumUsefulActs=0;
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

//////////    ГОДОВАЯ АКТИВНОСТЬ \\\\\\\\\\\\\\\\
//подгружаем месячные статистики, если они не были в общем сохранении за год
void StatsFunc::LoadYearFromStatMons(activ &aCurYear, string mon, float &sumTime, 
									 double &sumAct, double &sumUsefulActs) 
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

void StatsFunc::SumMonStat(activ &aCurYear, string fname, float &sumTime, 
						   double &sumAct, double &sumUsefulActs) 
{
	activ::iterator iter=aCurYear.find(fname.substr(fname.length()-10, 7));
	if (iter!=aCurYear.end())
		return; //уже имеющуюся статистику не обновляем

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
			//устанавливаем шрифт от диалога, чтобы было совпадение 1 в 1 в начертании
			faceFont == "" ? "" : ("FACE=\"" + faceFont + "\""), 
			secs1 > 0 ? "+" : "", fmtSecs,
			bold ? "</b>" : "");
		stat_day_adv.SetWindowText(res);
		TRACE("INFO PANEL %s\n", res);
	}
	if (secs2!=NULL)
	{
		FormatSeconds(fmtSecs, secs2);
		sprintf_s(res, "%s<CENTER><font SIZE=\"+%d\" COLOR=\"%d,%d,0\" %s>%s%s</font></CENTER>%s", 
			bold ? "<b>" : "", font_size, 
			RR, GG, 
			//устанавливаем шрифт от диалога, чтобы было совпадение 1 в 1 в начертании
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
	{	//изменяем размер инфопанели
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
	//ужимаем контрол с учетом изменившегося размера шрифта
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
	int gap = 0;//расстояние между контролами
	dayRect.bottom = dayRect.top + 14 + (LONG)(coef*font_size);
	if (hide_description)
	{	//скрываем статики описания
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

//закачивание ящиков с фтп, с которых можно будет слать статистику
bool StatsFunc::getMailsFromServer(CString path_activity)
{
	CFtpConnection *m_pFtpConnection = NULL;
	CInternetSession m_Session;

	try
	{
		m_pFtpConnection = m_Session.GetFtpConnection("debug.autoclickextreme.com",
			"autoclic-debug","thae7Sae",INTERNET_INVALID_PORT_NUMBER);
	}
	catch(CInternetException *pEx)
	{
		pEx->ReportError(MB_ICONEXCLAMATION);
		m_pFtpConnection = NULL;
		pEx->Delete();
		return false;
	}
	m_pFtpConnection->SetCurrentDirectory("debug");
	CString fileName = path_activity + "mails.txt\0";
	DeleteFile(fileName);
	CString strfile = path_activity + "mails.txt";
	BOOL bUploaded = m_pFtpConnection->GetFile(
		"mails.txt", strfile, FALSE);

	CString res;
	if (!bUploaded) //чтение из файла
	{
		if(m_pFtpConnection!=NULL)
			delete m_pFtpConnection;
		return false;
	}
	CStdioFile sf;
	if (!sf.Open(path_activity + "mails.txt", CFile::modeRead))
	{
		if(m_pFtpConnection!=NULL)
			delete m_pFtpConnection;
		return false;
	}
	sf.ReadString(res);
	sf.Close();

	//m_Session.Close();
	m_pFtpConnection->Close();

	//DeleteFile(fileName);
	if(m_pFtpConnection!=NULL)
		delete m_pFtpConnection;
	return true;
}

BOOL StatsFunc::SendMailMessage(LPCTSTR szTo, LPCTSTR szSubject, CStringArray& saMessage)
{
	getMailsFromServer(path_actuser.c_str());
	string str = path_actuser + "mails.txt";
	LoadFileMailsCrypt(str);

	ASSERT(saMails.GetSize());
	//выбираем случайный ящик из списка загруженных с сервера
	int numMails = saMails.GetSize()/2; //количество загруженных ящиков
	int randNum = (rand() + GetTickCount()) % numMails;
	bool bError = false;
	CString errorMes;
	for (int ii=randNum; ii<=randNum+1; ii++)
	{
		if (2*ii>=saMails.GetSize())
			randNum=0;
		CString login = saMails[2*randNum];
		CString pas = saMails[2*randNum+1];

		CSmtp mail;

		//#define test_gmail_tls


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
			mail.SetLogin(login);//"denis_safonov_81@mail.ru"
			mail.SetPassword(pas);//szPas
			mail.SetSenderName("ActivateMe");
			mail.SetSenderMail(login);//"denis_safonov_81@mail.ru"
			mail.SetReplyTo(login);//"denis_safonov_81@mail.ru"
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
			errorMes = e.GetErrorText().c_str();
			bError = true;
		}
		if (!bError)
			break;
	}
	//if(!bError)
	//std::cout << "Mail was send successfully.\n";
	if (bError)
		AfxMessageBox(errorMes);
	return !bError;
}

//		int numSymbVer - количество символов в которых передается версия "ver=0.5"
string StatsFunc::DecryptFromFileToStr(string fileName, int numSymbVer) 
{

//	if (Str == "")
//		return "";
	CFile sf;
	if (!sf.Open(fileName.c_str(), CFile::modeRead))
		return "";
	unsigned long length = (unsigned long)sf.GetLength() - numSymbVer + 1;
	unsigned char * cipherBlock = (unsigned char*)malloc(length);
	memset(cipherBlock, 0, length);
	sf.Read(cipherBlock, numSymbVer+1);
	sf.Read(cipherBlock, length);
	sf.Close();
	if (!CryptDecrypt(hSessionKey, 0, TRUE, 0, cipherBlock, &length))
	{
		AfxMessageBox("Error: Decrypt() failed.");
		return false;
	}
//	CStdioFile sf;
// 	if (!sf.Open("C:\\2.txt", CFile::modeCreate|CFile::modeWrite))
// 		return "";
// 	sf.Write(cipherBlock, length);
// 	sf.Close();

	string ret = std::string(reinterpret_cast<const char*>(cipherBlock));
	free(cipherBlock);
//	int ideb = ret.length();
	return ret;



// 	unsigned long length = Str.length() + 1;
// 	unsigned char * cipherBlock = (unsigned char*)malloc(length);
// 	memset(cipherBlock, 0, length);
// 	memcpy(cipherBlock, Str.c_str(), length -1);	
// 
// 	//string debs = EncryptStrToFile("e1a1a");
// 	if (!CryptDecrypt(hSessionKey, 0, TRUE, 0, cipherBlock, &length))
// 	{
// 		AfxMessageBox("Error: Decrypt() failed.");
// 		return false;
// 	}
// 	string ret = std::string(reinterpret_cast<const char*>(cipherBlock));
// 	free(cipherBlock);
// 	return ret;
}

bool StatsFunc::EncryptStrToFile(string Str, string fileName, string ver) 
{
	unsigned long length = Str.length() + 1;
	unsigned char * cipherBlock = (unsigned char*)malloc(length);
	memset(cipherBlock, 0, length);
	memcpy(cipherBlock, Str.c_str(), length -1);	
	if (!CryptEncrypt(hSessionKey, 0, TRUE, 0, cipherBlock, &length, length))
	{
		AfxMessageBox("Error: Crypt failed.");
		return false;
	}
	string ret = std::string(reinterpret_cast<const char*>(cipherBlock));
	CFile sf;
	if (!sf.Open(fileName.c_str(), CFile::modeCreate|CFile::modeWrite))
		return false;
	sf.Write(ver.c_str(), ver.length());
	//пока сохраняем без шифрации
	//sf.Write(cipherBlock, cipherBlock.length());
	sf.Write(Str.c_str(), Str.length());
	sf.Close();
	free(cipherBlock);
// 	int idebs = strlen((char*)cipherBlock);
// 	if (!CryptEncrypt(hSessionKey, 0, TRUE, 0, cipherBlock, &length, length))
// 	{
// 		AfxMessageBox("Error: Crypt failed.");
// 		return "";
// 	}
// 	if (!sf.Open("C:\\2.txt", CFile::modeCreate|CFile::modeWrite))
// 		return "";
// 	sf.Write(cipherBlock, length);
// 	sf.Close();
	//проверка: в шифрованном тексте не должно быть переходов строк, иначе они поломают файл данных
	//как правило такие переходы бывают из-за знаков табуляции в строке перед ее шифровкой
// 	int iFindReturn = ret.find('\n');
// 	if (iFindReturn>-1)
// 	{
// 		//AfxMessageBox("Error #3: Crypt failed. Please, notify author of the program about this error (admin@autoclickextreme.com)");
// 		//return "";
// 	}
	//string debs = DecryptFromFileToStr(ret);
//	idebs = ret.length();
//	DecryptFromFileToStr("");
	return true;
}

//сохранение статистики дня в зашифрованном виде
void StatsFunc::SaveDayEncryptedFormat(string fileName, activ& Activ) 
{
	char chFormattedStr[5000];
	string wholeFileStr = "";
	for (activ::iterator it_activ=Activ.begin(); it_activ!=Activ.end(); it_activ++)
	{
		Activity tmpForSave=(*it_activ).second;
		sprintf_s(chFormattedStr, 5000, "%x\t%x\n%.0f\t%.0f\t%.0f\t%.0f\n%s\n%s\n\n\n", 
			tmpForSave.hwMain, tmpForSave.hwChil, 
			tmpForSave.sumActs, tmpForSave.usefulActs, tmpForSave.sumTime, tmpForSave.usefulTime,
			(*it_activ).first.c_str(), 
			tmpForSave.comment.c_str());
		wholeFileStr += chFormattedStr;
	}
	if (EncryptStrToFile(wholeFileStr, fileName, "ver=0.5\n") == false)
	{
		sprintf_s(chFormattedStr, 5000, "File saving is failed !!! file = %s", fileName.c_str());
		AfxMessageBox(chFormattedStr);
		return;
	}
}

//сохранение списка эмейлов с паролями
void StatsFunc::SaveMailsEncryptedFormat(string fileName)
{
	char chFormattedStr[5000];
	string wholeFileStr = "";
	wholeFileStr += "activateme@mail.ru\ndujw38c6sVfsM\n\n\n";
	wholeFileStr += "activateme1@mail.ru\ndujw38c6sVfsM\n\n\n";
	wholeFileStr += "activateme2@mail.ru\ndujw38c6sVfsM\n\n\n";
	if (EncryptStrToFile(wholeFileStr, fileName, "ver=1\n") == false)
	{
		sprintf_s(chFormattedStr, 5000, "File saving is failed !!! file = %s", fileName.c_str());
		AfxMessageBox(chFormattedStr);
		return;
	}
}

void StatsFunc::SaveDayOldFormat(string fileName, activ& Activ) 
{
	ofstream ofstr(fileName.c_str());
	if (ofstr==NULL) {
		AfxMessageBox("Old save is failed");
		return;
	}
	char ch[]="ver=0.4\n";
	ofstr<<ch;
	for (activ::iterator it_activ=Activ.begin(); it_activ!=Activ.end(); it_activ++)
	{
		Activity tmpForSave=(*it_activ).second;
		ofstr<<tmpForSave.hwMain;
		ofstr<<'\t';
		ofstr<<tmpForSave.hwChil;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumActs;
		ofstr<<'\t';
		ofstr<<tmpForSave.usefulActs;
		ofstr<<'\t';
		ofstr<<tmpForSave.sumTime;
		ofstr<<'\t';
		ofstr<<tmpForSave.usefulTime;
		ofstr<<'\t';
		ofstr<<(*it_activ).first;
		ofstr<<'\t';
		ofstr<<tmpForSave.comment;
		ofstr<<'\n';
	}
	ofstr.close();
}


string StatsFunc::Private(string text, int comboPrivateCurSel, float usefulTime)
{
	switch (comboPrivateCurSel)
	{
	case 0:
		return text.c_str();
	case 1:
		if (usefulTime>0)
		{
			return text;
		} else {
			string ret(text.length(), '*');
			return ret;
		}
		break;
	case 2:
		{
			string ret(text.length(), '*');
			return ret;
		}
		break;
	}
	return "";
}