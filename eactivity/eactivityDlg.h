//#include "externals/ppToolTip/PPTooltip.h"
#include "old_my_src/winwork.h"
#include "koeff.h"
#include "ReportOption.h"
#include "ReportTwoPeriods.h"
#include "externals\newmenu.h"
//#include "Option1.h"
#include "Optiontab.h"
#include "TabOption.h"
#include "ViewRules.h"
#include "AlwaysTop.h"
#include "externals/openssl-0.9.8l/CSmtp.h"
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>
//#include "externals/XHTMLStatic.h"
#include "statsfunc.h"
#include "externals\graph\ChartCtrl.h"
#include "externals\graph\ChartLineSerie.h"
#include "externals\graph\ChartPointsSerie.h"
#include "externals\graph\ChartAxisLabel.h"
#include "externals\ListCtrl\CGridListCtrlEx\CGridListCtrlEx.h"
#include "ReportSelectedPeriod.h"
#include "afxwin.h"
#define WM_USER30 WM_USER + 30
#define USEFULTIME 1
#define USEFULACTS 2
using namespace std;

#if !defined(AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_)
#define AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEactivityDlg dialog

class CEactivityDlg : public CDialog
{
// Construction
	CNewMenu MainMenu;
	CNewMenu menuExeCapt;
	CNewMenu menuTablePeriod;
	BOOL __SetHook__(BOOL fSet);
	BOOL hookload;//запущен хук или нет
	HINSTANCE hMyDll;
	HHOOK SetHookRec;
//	void OnSave();
	CString path_exe;
	bool WriteJournal(LPCTSTR lpszFormat, ...);
	void SetToTray(int ResConst, bool modify=false);
	void DelIconTray();
	LRESULT OnIcon(WPARAM wp, LPARAM lp);
	HHOOK SetHook;
	StatsFunc statsF; //функции работы со статистикой вынесены в отдельный файл
	UINT sleepPeriod;
	double usefulTimeHoliday;

public:
	CEactivityDlg(CWnd* pParent = NULL);	// standard constructor
	void Exit();
	CTrifle trif;
	CWinWork wwork;
//	CPPToolTip tool_tip;
	
	forExe exes;//справочник полных имен exe и коротких
	exeSpis exe_sprav; //справочник HWND окон и полных имен exe
	string GetExeFromHwnd(HWND hw) ;
	GetParSpis getParSpis; //справочник HWND дочерних окон и HWND родительских
	CEactivityDlg(CString path, CWnd* pParent = NULL);   // standard constructor
	void AddExeCaptToTable(string exe, activ &forLoad1, int &sumCapt);
	void CalculateUsefulTimeAndActs(activ &allActiv, activ_exe &exeActiv, activ_hours &activHours);
	int GetUsefulActsFromExe(string exe, activ &forLoad1);
	float GetTimeFromExe (string exe, activ &forLoad1);
	void CalculateAverageUsefulParameter(int lastDays, double thresholdHoliday);
	CString CompareTwoPeriodsOfDays(CStringArray& saDates1, CStringArray& saDates2, 
		int accentParameter, int MinusDays=0, double thresholdHoliday=0.0);
	void CompareTwoPeriodsOfMons(CStringArray& saDates1, CStringArray& saDates2);

	void AddToExeCapt(char *capt, string &exe, HWND HChil, HWND hwMain, int sumActs, float sumTime);
//	void AddToOnlyExe(string &exe, int sumActs, float sumTime);
	void AnalActivUser(SendStruct* curAct);
	UINT forTimeNoActiv;
	CPoint cpNoActiv;//позиция мыши при неактивности пользователя
	CCpuUsage cpu;
	string path_actuser;//папка где хранятся файлы с активностью пользователя

	//для текущего дня
	activ ActivToday;	//группировка активности ПО EXE И ЗАГОЛОВКУ
	//для выделенного дня (не сегодняшнего)
	string SelectedDay; // содержит дату не текущего дня в формате 2015_11_23
	activ aSelDayView;
	activ aCurYear;	//статистика по МЕСЯЦАМ для текущего показа в ТЗПВ
	activ aCurMon;	//статистика по дням для текущего показа в ТЗПВ, 
		//подробности про aCurMon в описании UpdatePeriodTableViewByHours
	activ aSelMon;	//для выбранного показа по двойному клику
	string SelectedMon; //выбран не текущий месяц (какой-то прошедший)
	activ_hours lastAverageHoursGraph; //средняя почасовая статистика за последнюю неделю
		//в 25ом часе содержит суммарное усредненное значение за сутки

	void SaveCurDay(bool smena=false);
	void LoadCurDay();
	void SendReportOfDayOnMail(string dateToday);
	BOOL SendMailMessage(LPCTSTR szServer,
		UINT port, 
		LPCTSTR szFrom, 
		LPCTSTR szTo, 
		LPCTSTR szUser, 
		LPCTSTR szPas, 
		LPCTSTR szSubject, 
		LPCTSTR szMessage);

	bool LoadFileDay(string fname, activ &forLoad1);
	string curDayFileName;//содержит дату текущего дня "activ_user_2015_11_26.a"
	
	void SaveCurMonth(bool smena=false);
	void LoadCurMonth();
	string curMonFileName;
	
	void SaveYear();
	
	rulSpis RULES;
	void SaveRules();
	void LoadRules();
	
	void UpdateTableExeCapt(activ &allActiv, activ_hours &activHours, 
		float &sumTime, float &sumUsefulTime, int &sumAct, 
		int &usefulActs, int onlyOneHour = -1, bool showInfoTable=true);
	void UpdateExeCapt(activ_hours &activHours, bool showInfoTable=true);
	void UpdatePeriodTableViewByHours(activ_hours &activHours, bool showInfoTable=true);
	void UpdatePeriodTable(activ &CurView);
	rulSpis::iterator ownFind(string capt);
	string GetExeFromTable(int sel);
	string showAllCaptsForExe;//показывать все заголовки для определенного EXE
	void SizingWins();
	CAlwaysTop* dialInfo;//диалоговое окно поверх всех с инфой

// Dialog Data
	//{{AFX_DATA(CEactivityDlg)
	enum { IDD = IDD_EACTIVITY_DIALOG };
	CComboBox	combo_group;
	CSpinButtonCtrl	spin_edit;
	CEdit	edit_capts;
	CGridListCtrlEx	table_period;//таблица задания периода времени ТЗПВ
	CGridListCtrlEx	table_exe_capt;//таблица детализации
	CComboBox	combo_sort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEactivityDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEactivityDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRefresh();
	afx_msg void OnSelchangeCombo_sort();
	afx_msg void OnDblclkListDays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboDownTable();
	afx_msg void OnDblclkListCurDay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnActivitySetKoef();
	afx_msg void OnRclickTableExeCapt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickPeriodTable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnActivitySetkoefeExe();
	afx_msg void OnChangeEDITcapts();
	afx_msg void OnActivityShowAllCapts();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSave();
	CChartCtrl chart; //http://www.codeproject.com/Articles/14075/High-speed-Charting-Control - example
	CXHTMLStatic stat_day_adv;
	CXHTMLStatic stat_hour_adv;
	CXHTMLStatic stat_ExeCapt;
	CXHTMLStatic stat_periodTable;
	afx_msg void OnReportsUsefulActionsFromLast5WorkingDays();
	CButton radioTime;
	CButton radioActs;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnReportsUsefulParameterFromSelectedPeriod();
	CButton checkAutoUpdate;
	afx_msg void OnCompare2periods();
	afx_msg void OnCompareWithBest5Days();
	afx_msg void OnReportOnePeriod();
	afx_msg void OnReportTwoPeriods();
	afx_msg void OnOptionsOptions();
	CButton check_infopanel;
	afx_msg void OnBnClickedCheckInfoPanel();
	afx_msg LRESULT OnCloseInfoPanel(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_)
