//#include "externals/ppToolTip/PPTooltip.h"
#include "old_my_src/winwork.h"
#include "koeff.h"
#include "setkoefmanual.h"
#include "AddManualInput.h"
#include "ReportOption.h"
#include "ReportTwoPeriods.h"
#include "GoWorkUntilPause.h"
#include "externals\newmenu.h"
#include "Optiontab.h"
#include "TabOption.h"
#include "ViewRules.h"
#include "AlwaysTop.h"
#include "endwork.h"
#include "OnlineAdvices.h"
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "statsfunc.h"
#include "externals\graph\ChartCtrl.h"
#include "externals\graph\ChartLineSerie.h"
#include "externals\graph\ChartPointsSerie.h"
#include "externals\graph\ChartAxisLabel.h"
#include "externals\ListCtrl\CGridListCtrlEx\CGridListCtrlEx.h"
#include "ReportSelectedPeriod.h"
#include "RecalculationUsefulTime.h"
#include "afxwin.h"
#include "AddOnlineAdvice.h"
#define WM_USER30 WM_USER + 30
#define USEFULTIME 1
#define USEFULACTS 2
#define COLUMN_COMMENT 6
//						константы управляющие параметрами расчета полезного времени
#define ALLPROJECTS 2		//использовать все проекты для расчета
#define SELECTEDPROJECTS 3	//брать только выделенные в списке проекты

using namespace std;

#if !defined(AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_)
#define AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//структура, содержащая текущие координаты окон
struct windowsSize 
{
	windowsSize();
	bool moveBetweenTables;
	bool resizeBetweenTables;
	CPoint ptFirst, ptLast;
};

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
	double hoursNorm; //дневная норма рабочих часов, если 0, то берется среднее 
						//значение за последние 5 рабочих дней
	double coefIncNorm; //коэффициент превышения нормы за последние 5 дней 
						//(чтобы делить на него при нормировании средней нагрузки)

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
	void CalculateUsefulTimeAndActs(activ &allActiv, activ_exe &exeActiv, 
		activ_hours &activHours, int keyListProjects);
	int CalculateAverageUsefulParameter(int lastDays, activ_hours& averageHoursGraph, 
		double thresholdHoliday, double hoursNormLine=0.0);
	CString CompareTwoPeriodsOfDays(CStringArray& saDates1, CStringArray& saDates2, 
		int accentParameter, int MinusDays=0, double thresholdHoliday=0.0, 
		bool mailReport=false);
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
	string currentExeTableDate; //содержит период времени, который на данным момент отображается в 
						// таблице детализации
	activ aSelDayView;
	activ aCurYear;	//статистика по МЕСЯЦАМ для текущего показа в ТЗПВ
	activ aCurMon;	//статистика по дням для текущего показа в ТЗПВ, 
		//подробности про aCurMon в описании UpdatePeriodTableViewByHours
	activ aSelMon;	//для выбранного показа по двойному клику
	string SelectedMon; //выбран не текущий месяц (какой-то прошедший)
	activ_hours standardHoursForLastWeek; //средняя почасовая статистика за последнюю неделю
		// используется как норма почасового распределения, с которой будет сравниваться 
		// текущий день
		// в 25ом часе содержит суммарное усредненное значение за сутки
	void SetHourNormStandard(double NormHoursInDay); //устанавливает почасовое распределение
		// в случае если не достаточно дней для выборки

	void SaveCurDay(bool smena=false);
	void LoadCurDay();
	BOOL SendReportOfDayOnMail(string dateToday);
	string curDayFileName;//содержит дату текущего дня "activ_user_2015_11_26.a"
	BOOL ReplaceActivityRecord(activ &Activ, CString sExeOld, CString sExeNew, 
		CStringArray& sCaptOld, CString sCaptNew, 
		CString sComment, double dCoef, int selHour, CUIntArray& manualInput,
		bool bUnit=false);
	bool RemoveActivityRecord(activ &Activ, CStringArray &sExe, CStringArray &sCapt, 
		int selHour, CUIntArray &manualInput);
	void AddManualInput(activ &Activ, CString &sExe, CString &sCapt, 
		CString sComment, int selHour, float SumTime, float UsefulTime);

	void SaveCurMonth(bool smena=false);
	void SaveMonth(string strf, activ& aMon);
	void LoadCurMonth();
	string curMonFileName;
	
	void SaveYear();
	void SaveAllYear();
	
	void UpdateTableExeCapt(activ &allActiv, activ_hours &activHours, 
		float &sumTime, float &sumUsefulTime, double &sumAct, 
		double &usefulActs, int keyListProjects, int onlyOneHour = -1, 
		bool showInfoTable=true);
	void UpdateExeCapt(activ_hours &activHours, activ &aDay,
		int keyListProjects, bool showInfoTable=true, string noCurrentDay = "");
	void UpdatePeriodTableViewByHours(activ_hours &activHours, 
		bool showInfoTable=true, string noCurrentDay = "");
	void UpdatePeriodTable(activ &CurView);
	string GetExeFromTable(int sel);
	void endWork();
	string showAllCaptsForExe;//показывать все заголовки для определенного EXE
	void changeRule(rulMacroList &macroRule, rulMacroList &allRules);

	windowsSize WINs;
	CAlwaysTop* dialInfo;//диалоговое окно поверх всех с инфой
	CEndWork* dialEndWork;
	CViewRules RUL;

// Dialog Data
	//{{AFX_DATA(CEactivityDlg)
	enum { IDD = IDD_EACTIVITY_DIALOG };
	CComboBox	combo_group; //вид детализации в ТЗПВ: по часам, дням, месяцам
	CGridListCtrlEx	table_period;  //таблица задания периода времени (ТЗПВ)
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
	virtual void OnCancel();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRefresh();
	afx_msg void UpdateSort(int typeSort, bool onlyCheck=false);
	afx_msg void OnDblclkListDays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboDownTable();
	afx_msg void OnDblclkListCurDay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnActivitySetKoef();
	afx_msg void OnRclickTableExeCapt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickPeriodTable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnActivitySetkoefeExe();
	afx_msg void OnChangeEDITcapts();
	afx_msg void OnActivityShowAllCapts();
	afx_msg void OnActivityManualAdd();
	afx_msg void OnActivityFullManualAdd();
	afx_msg void OnDeleteRecordFromExeCapt();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CChartCtrl chart; //http://www.codeproject.com/Articles/14075/High-speed-Charting-Control
	CXHTMLStatic stat_day_adv;
	CXHTMLStatic stat_hour_adv;
	CXHTMLStatic stat_ExeCapt;
	CXHTMLStatic stat_periodTable;
	CButton radioTime;
	CButton radioActs;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnReportsUsefulParameterFromSelectedPeriod();
	CButton checkAutoUpdate;
	afx_msg void OnCompare2periods();
	afx_msg void OnCompareWithBest5Days();
	afx_msg void OnReportOnePeriod();
	afx_msg void OnMainMenuExit();
	afx_msg void OnReportTwoPeriods();
	afx_msg void OnSendTableOnMail();
	afx_msg void OnOptionsOptions();
	CButton check_infopanel;
	afx_msg void OnBnClickedCheckInfoPanel();
	afx_msg LRESULT OnCloseInfoPanel(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnOptionsEditshortactions();
	afx_msg void OnOptions32800();
	afx_msg void OnHistoryOnlineAdvices();
	afx_msg void OnHistoryShortTodo();
	afx_msg void SendStatOnMail();
	afx_msg void OnMenuHideCapt();
	afx_msg void OnEditCoef();
	afx_msg void OnSortByCommonTime();
	afx_msg void OnSortByUsefulTime();
	afx_msg void OnSortByActs();
	afx_msg void OnSortByUsefulActs();
	afx_msg void OnSortByExe();
	afx_msg void OnRecalculateUsefulTime();
	CListBox listProjects;
	afx_msg void OnLbnSelchangeList5();
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_)
