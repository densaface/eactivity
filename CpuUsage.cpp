#include "stdafx.h"
#include <atlbase.h>	// for CRegKey use
#include "CpuUsage.h"

/*for WinXP
#include <psapi.h>
#pragma comment(lib,"psapi.lib") 
//*///for WinXP

#pragma pack(push,8)
#include "PerfCounters.h"
#pragma pack(pop)

#define SYSTEM_OBJECT_INDEX					2		// 'System' object
#define PROCESS_OBJECT_INDEX				230		// 'Process' object
#define PROCESSOR_OBJECT_INDEX				238		// 'Processor' object
#define TOTAL_PROCESSOR_TIME_COUNTER_INDEX	240		// '% Total processor time' counter (valid in WinNT under 'System' object)
#define PROCESSOR_TIME_COUNTER_INDEX		6		// '% processor time' counter (for Win2K/XP)

///////////////////////////////////////////////////////////////////
//
//		GetCpuUsage uses the performance counters to retrieve the
//		system cpu usage.
//		The cpu usage counter is of type PERF_100NSEC_TIMER_INV
//		which as the following calculation:
//
//		Element		Value 
//		=======		===========
//		X			CounterData 
//		Y			100NsTime 
//		Data Size	8 Bytes
//		Time base	100Ns
//		Calculation 100*(1-(X1-X0)/(Y1-Y0)) 
//
//      where the denominator (Y) represents the total elapsed time of the 
//      sample interval and the numerator (X) represents the time during 
//      the interval when the monitored components were inactive.
//
//
//		Note:
//		====
//		On windows NT, cpu usage counter is '% Total processor time'
//		under 'System' object. However, in Win2K/XP Microsoft moved
//		that counter to '% processor time' under '_Total' instance
//		of 'Processor' object.
//		Read 'INFO: Percent Total Performance Counter Changes on Windows 2000'
//		Q259390 in MSDN.
//
///////////////////////////////////////////////////////////////////

typedef enum
{
	WINNT,	WIN2K_XP, WIN9X, UNKNOWN
}PLATFORM;

PLATFORM GetPlatform()
{
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (!GetVersionEx(&osvi))
		return UNKNOWN;
	switch (osvi.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		return WIN9X;
	case VER_PLATFORM_WIN32_NT:
		if (osvi.dwMajorVersion == 4)
			return WINNT;
		else
			return WIN2K_XP;
	}
	return UNKNOWN;
}

CCpuUsage::CCpuUsage()
{
	m_bFirstTime = true;
	m_lnOldValue = 0;
	memset(&m_OldPerfTime100nSec, 0, sizeof(m_OldPerfTime100nSec));
}

CCpuUsage::~CCpuUsage()
{
}

//������ ����� ����������� ���������� (��� XP)
CString CCpuUsage::GetAppNameFromHandle(HWND hnd)
{
	DWORD pid;
	DWORD	dw=GetWindowThreadProcessId((HWND)hnd, &pid);
	//GetModuleFileName((HMODULE)pid, mes, 100);

	HANDLE  hProc;
	char    szProcessName [1024];
	CString res=szProcessName;
	//HMODULE ahMod [100];//for win98
	//DWORD   dwNeeded;//for win98

	hProc = OpenProcess (PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,
	FALSE, pid); // PID ������ ���� �������� ��� DWORD
	if (hProc)
	{
		return "";	//for win98
	/*for WinXP
		if (EnumProcessModules (hProc, ahMod, sizeof(ahMod), &dwNeeded))
		{
			if (GetModuleFileNameEx(hProc, ahMod[0], szProcessName,
				sizeof(szProcessName)))
			{
				//<success>
			} else {
				CloseHandle (hProc); //<failure>
				return "";				
			}
		}
		CloseHandle (hProc);
	//*///for WinXP
	}
	if (res==szProcessName){
		return "";
	} else {
		return szProcessName;
	}
}

#include "tlhelp32.h"
	//������ ����� ���������� �� ������ ��� ���� (������ � ����� ���� ��������)
string CCpuUsage::GetAppNameFromHandle2(HWND hw)
{
	DWORD pid;
	DWORD dw=GetWindowThreadProcessId(hw, &pid);
	if (dw==NULL)
	{
		return "";
	}
	return ListProcessModules(pid);
}

string CCpuUsage::ListProcessModules(DWORD dwPID)
{
  HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
  MODULEENTRY32 me32;

  // Take a snapshot of all modules in the specified process.
  hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID );
  if( hModuleSnap == INVALID_HANDLE_VALUE )
  {
    //printError( "CreateToolhelp32Snapshot (of modules)" );
    return "INVALID_HANDLE_VALUE";
  }

  // Set the size of the structure before using it.
  me32.dwSize = sizeof( MODULEENTRY32 );

  // Retrieve information about the first module,
  // and exit if unsuccessful
  if( !Module32First( hModuleSnap, &me32 ) )
  {
    //printError( "Module32First" );  // Show cause of failure
    CloseHandle( hModuleSnap );     // Must clean up the snapshot object!
    return "Module32First";
  }

  // Now walk the module list of the process,
  // and display information about each module
  do
  {
	  if (me32.th32ProcessID==dwPID)
	  {
			//CString str=me32.szExePath;
			//AfxMessageBox(str);
			//str+=me32.szModule;
			//AfxMessageBox(str);
			CloseHandle( hModuleSnap );
			return me32.szExePath;
	  }

  } while( Module32Next( hModuleSnap, &me32 ) );

  CloseHandle( hModuleSnap );
  return( "TRUE" );
}

//������ �������� ����� ����� ��� Win98
int CCpuUsage::GetCpuUsage2()
{
	HKEY hKey = NULL;
	LONG lRes = RegOpenKeyEx(HKEY_DYN_DATA, "PerfStats\\StatData", 0, KEY_QUERY_VALUE, &hKey);
	if (lRes == ERROR_SUCCESS)
	{
		DWORD dwValue=0;
		DWORD dwType = NULL;
		DWORD dwCount = sizeof(DWORD);
		//long dwCount = sizeof(DWORD);
		CString str;//(setting);
		LONG lRes = RegQueryValueEx(hKey, _T("KERNEL\\CPUUsage"), NULL, &dwType,
			(LPBYTE)&dwValue, &dwCount);
		//LONG lRes = RegQueryValue(hKey, _T("KERNEL\\CPUUsage"), str.GetBuffer(3), &dwCount);
		if (lRes){
			return -1;
			//m_Test.SetWindowText("-1");
		} else {
			return (int)dwValue;
			//str.Format("%d", (int)dwValue);
			//m_Test.SetWindowText(str);
		}
	} else {
		return -1;
	}
}	

// BOOL CCpuUsage::EnablePerformaceCounters(BOOL bEnable)
// {
// 	if (GetPlatform() != WIN2K_XP)
// 		return TRUE;
// 
// 	CRegKey regKey;
// 	if (regKey.Open(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\PerfOS\\Performance") != ERROR_SUCCESS)
// 		return FALSE;
// 
// 	regKey.SetValue(!bEnable, "Disable Performance Counters");
// 	regKey.Close();
// 
// 	if (regKey.Open(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\PerfProc\\Performance") != ERROR_SUCCESS)
// 		return FALSE;
// 
// 	regKey.SetValue(!bEnable, "Disable Performance Counters");
// 	regKey.Close();
// 
// 	return TRUE;
// }

//
//	GetCpuUsage returns the system-wide cpu usage.
//	Since we calculate the cpu usage by two samplings, the first
//	call to GetCpuUsage() returns 0 and keeps the values for the next
//	sampling.
//  Read the comment at the beginning of this file for the formula.
//
// int CCpuUsage::GetCpuUsage()
// {
// 	static PLATFORM Platform = GetPlatform();
// 
// 	if (m_bFirstTime)
// 		EnablePerformaceCounters();
// 	
// 	// Cpu usage counter is 8 byte length.
// 	CPerfCounters<LONGLONG> PerfCounters;
// 	char szInstance[256] = {0};
// 
// //		Note:
// //		====
// //		On windows NT, cpu usage counter is '% Total processor time'
// //		under 'System' object. However, in Win2K/XP Microsoft moved
// //		that counter to '% processor time' under '_Total' instance
// //		of 'Processor' object.
// //		Read 'INFO: Percent Total Performance Counter Changes on Windows 2000'
// //		Q259390 in MSDN.
// 
// 	DWORD dwObjectIndex;
// 	DWORD dwCpuUsageIndex;
// 	switch (Platform)
// 	{
// 	case WINNT:
// 		dwObjectIndex = SYSTEM_OBJECT_INDEX;
// 		dwCpuUsageIndex = TOTAL_PROCESSOR_TIME_COUNTER_INDEX;
// 		break;
// 	case WIN2K_XP:
// 		dwObjectIndex = PROCESSOR_OBJECT_INDEX;
// 		dwCpuUsageIndex = PROCESSOR_TIME_COUNTER_INDEX;
// 		strcpy(szInstance,"_Total");
// 		break;
// 	default:
// 		return -1;
// 	}
// 
// 	int				CpuUsage = 0;
// 	LONGLONG		lnNewValue = 0;
// 	PPERF_DATA_BLOCK pPerfData = NULL;
// 	LARGE_INTEGER	NewPerfTime100nSec = {0};
// 
// 	lnNewValue = PerfCounters.GetCounterValue(&pPerfData, dwObjectIndex, dwCpuUsageIndex, szInstance);
// 	NewPerfTime100nSec = pPerfData->PerfTime100nSec;
// 
// 	if (m_bFirstTime)
// 	{
// 		m_bFirstTime = false;
// 		m_lnOldValue = lnNewValue;
// 		m_OldPerfTime100nSec = NewPerfTime100nSec;
// 		return 0;
// 	}
// 
// 	LONGLONG lnValueDelta = lnNewValue - m_lnOldValue;
// 	double DeltaPerfTime100nSec = (double)NewPerfTime100nSec.QuadPart - (double)m_OldPerfTime100nSec.QuadPart;
// 
// 	m_lnOldValue = lnNewValue;
// 	m_OldPerfTime100nSec = NewPerfTime100nSec;
// 
// 	double a = (double)lnValueDelta / DeltaPerfTime100nSec;
// 
// 	double f = (1.0 - a) * 100.0;
// 	CpuUsage = (int)(f + 0.5);	// rounding the result
// 	if (CpuUsage < 0)
// 		return 0;
// 	return CpuUsage;
// }

// int CCpuUsage::GetCpuUsage(LPCTSTR pProcessName)
// {
// 	static PLATFORM Platform = GetPlatform();
// 	
// 	if (m_bFirstTime)
// 		EnablePerformaceCounters();
// 
// 	// Cpu usage counter is 8 byte length.
// 	CPerfCounters<LONGLONG> PerfCounters;
// 	char szInstance[256] = {0};
// 
// 
// 	DWORD dwObjectIndex = PROCESS_OBJECT_INDEX;
// 	DWORD dwCpuUsageIndex = PROCESSOR_TIME_COUNTER_INDEX;
// 	strcpy(szInstance,pProcessName);
// 
// 	int				CpuUsage = 0;
// 	LONGLONG		lnNewValue = 0;
// 	PPERF_DATA_BLOCK pPerfData = NULL;
// 	LARGE_INTEGER	NewPerfTime100nSec = {0};
// 
// 	lnNewValue = PerfCounters.GetCounterValue(&pPerfData, dwObjectIndex, dwCpuUsageIndex, szInstance);
// 	NewPerfTime100nSec = pPerfData->PerfTime100nSec;
// 
// 	if (m_bFirstTime)
// 	{
// 		m_bFirstTime = false;
// 		m_lnOldValue = lnNewValue;
// 		m_OldPerfTime100nSec = NewPerfTime100nSec;
// 		return 0;
// 	}
// 
// 	LONGLONG lnValueDelta = lnNewValue - m_lnOldValue;
// 	double DeltaPerfTime100nSec = (double)NewPerfTime100nSec.QuadPart - (double)m_OldPerfTime100nSec.QuadPart;
// 
// 	m_lnOldValue = lnNewValue;
// 	m_OldPerfTime100nSec = NewPerfTime100nSec;
// 
// 	double a = (double)lnValueDelta / DeltaPerfTime100nSec;
// 
// 	CpuUsage = (int) (a*100);
// 	if (CpuUsage < 0)
// 		return 0;
// 	return CpuUsage;
// }
// 
// 
// int CCpuUsage::GetCpuUsage(DWORD dwProcessID)
// {
// 	static PLATFORM Platform = GetPlatform();
// 	
// 	if (m_bFirstTime)
// 		EnablePerformaceCounters();
// 
// 	// Cpu usage counter is 8 byte length.
// 	CPerfCounters<LONGLONG> PerfCounters;
// 
// 
// 	DWORD dwObjectIndex = PROCESS_OBJECT_INDEX;
// 	DWORD dwCpuUsageIndex = PROCESSOR_TIME_COUNTER_INDEX;
// 
// 	int				CpuUsage = 0;
// 	LONGLONG		lnNewValue = 0;
// 	PPERF_DATA_BLOCK pPerfData = NULL;
// 	LARGE_INTEGER	NewPerfTime100nSec = {0};
// 
// 	lnNewValue = PerfCounters.GetCounterValueForProcessID(&pPerfData, dwObjectIndex, dwCpuUsageIndex, dwProcessID);
// 	NewPerfTime100nSec = pPerfData->PerfTime100nSec;
// 
// 	if (m_bFirstTime)
// 	{
// 		m_bFirstTime = false;
// 		m_lnOldValue = lnNewValue;
// 		m_OldPerfTime100nSec = NewPerfTime100nSec;
// 		return 0;
// 	}
// 
// 	LONGLONG lnValueDelta = lnNewValue - m_lnOldValue;
// 	double DeltaPerfTime100nSec = (double)NewPerfTime100nSec.QuadPart - (double)m_OldPerfTime100nSec.QuadPart;
// 
// 	m_lnOldValue = lnNewValue;
// 	m_OldPerfTime100nSec = NewPerfTime100nSec;
// 
// 	double a = (double)lnValueDelta / DeltaPerfTime100nSec;
// 
// 	CpuUsage = (int) (a*100);
// 	if (CpuUsage < 0)
// 		return 0;
// 	return CpuUsage;
// }

