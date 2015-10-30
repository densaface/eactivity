#ifndef _CPUUSAGE_H
#define _CPUUSAGE_H

//#include <windows.h>
#include "stdafx.h"
#include <string>
using namespace std;


class CCpuUsage
{
public:
	CCpuUsage();
	string ListProcessModules(DWORD dwPID);
	virtual ~CCpuUsage();

// Methods
	//������ �������� ����� ����� ��� WinXP
//	int GetCpuUsage();
	//������ �������� ����� ����� ��� Win98
	int GetCpuUsage2();
//	int GetCpuUsage(LPCTSTR pProcessName);
//	int GetCpuUsage(DWORD dwProcessID);

	//������ ����� ���������� �� ������ ��� ���� (������ � ����� ���� ��������)
	string GetAppNameFromHandle2(HWND hw);
	//������ ����� ����������� ���������� (��� XP)
	CString GetAppNameFromHandle(HWND hnd);

//	BOOL EnablePerformaceCounters(BOOL bEnable = TRUE);

// Attributes
private:
	bool			m_bFirstTime;
	LONGLONG		m_lnOldValue ;
	LARGE_INTEGER	m_OldPerfTime100nSec;
};


#endif