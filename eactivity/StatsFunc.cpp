#include "StatsFunc.h"

StatsFunc::StatsFunc(void)
{
}

StatsFunc::~StatsFunc(void)
{
}

bool StatsFunc::LoadFileMonth(string fname, activ &forLoad1, float &sumTime, float &sumUsefulTime, int &sumActs, int &sumUsefulActs)
{
	ifstream ifstr(fname.c_str());
	if (ifstr)
	{
		char ch[1024];
		ifstr.getline(ch, 100);

		Activity tmpForLoad;
		tmpForLoad.capt="";
		tmpForLoad.exe="";
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
			if (strcmp(ch, "ver=0.1")!=0) {
				//только в первой версии не сохран€лось полезное врем€
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

//подгружаем дневные статистики, если они не были в общем сохранении за мес€ц
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

void StatsFunc::SumDayStat(activ &forLoad1, string fname, float &sumTime, int &sumAct, int &sumUsefulActs) 
{
	activ::iterator iter=forLoad1.find(fname.substr(fname.length()-12, 10));
	if (iter!=forLoad1.end())
		return; //уже имеющуюс€ статистику не обновл€ем

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

//////////    √ќƒќ¬јя ј “»¬Ќќ—“№ \\\\\\\\\\\\\\\\
//подгружаем мес€чные статистики, если они не были в общем сохранении за год
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
		return; //уже имеющуюс€ статистику не обновл€ем

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