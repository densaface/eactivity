#include "ppToolTip/PPTooltip.h"
#include "winwork.h"
#include "koeff.h"
#include "newmenu.h"
#include "ViewRules.h"
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "graph\mschart.h"
#include "graph\vcdatagrid.h"
#define WM_USER30 WM_USER + 30
using namespace std;

#if !defined(AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_)
#define AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEactivityDlg dialog
struct Activity
{
	HWND hwMain;
	HWND hwChil;
	string exe;
	string capt;
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

class CEactivityDlg : public CDialog
{
// Construction
	CNewMenu menu_cur_day;
//	CPPToolTip tool_tip;
	BOOL __SetHook__(BOOL fSet);
	BOOL hookload;//запущен хук или нет
	HINSTANCE hMyDll;
	HHOOK SetHookRec;
//	void OnSave();
	CString path_exe;
	bool WriteJournal(LPCTSTR lpszFormat, ...);
	void FormatSeconds(char (&ch)[100], float secs); 
	void SetToTray(int ResConst, bool modify=false);
	void DelIconTray();
	LRESULT OnIcon(WPARAM wp, LPARAM lp);
	HHOOK SetHook;
public:
	CEactivityDlg(CWnd* pParent = NULL);	// standard constructor
	void Exit();
	CTrifle trif;
	CWinWork wwork;
	CPPToolTip tool_tip;
	
	forExe exes;//справочник полных имен exe и коротких
	exeSpis exe_sprav; //справочник HWND окон и полных имен exe
	string GetExeFromHwnd(HWND hw) ;
	GetParSpis getParSpis; //справочник HWND дочерних окон и HWND родительских
	CEactivityDlg(CString path, CWnd* pParent = NULL);   // standard constructor
	void AddExeCaptToTable(string exe, activ &forLoad1, int &sumCapt);
	void CalculateUsefulTimeAndActs(activ &allActiv, activ_exe &exeActiv, activ_hours &activHours);
	int GetUsefulActsFromExe(string exe, activ &forLoad1);
	float GetTimeFromExe (string exe, activ &forLoad1);
	
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
	string curYear;
	activ aCurYear;	//статистика по МЕСЯЦАМ для текущего показа в ТЗПВ
	activ aCurMon;	//статистика по дням для текущего показа в ТЗПВ, 
		//подробности про aCurMon в описании UpdatePeriodTableViewByHours
	activ aSelMon;	//для выбранного показа по двойному клику
	string SelectedMon; //выбран не текущий месяц (какой-то прошедший)

	void SaveCurDay(bool smena=false);
	void LoadCurDay();
	bool LoadFileDay(string fname, activ &forLoad1);
	string curDayFileName;//фактически текущий день
	int curHour; //текущий час, смена проверяется каждые 5 сек
	
	void SaveCurMonth(bool smena=false);
	void LoadCurMonth();
	bool LoadFileMonth(string fname, activ &forLoad1, float &sumTime, int &sumActs, int &usefulActs);
	void LoadMonthFromStatDays(activ &forLoad1, string mon, float &sumTime, int &sumActs, int &usefulActs);
	void SumDayStat(activ &forLoad1, string fname, float &sumTime, int &sumActs, int &usefulActs);
	string curMonFileName;
	
	void SaveYear();
	void LoadYear();
	void LoadYearFromStatMons(string mon, float &sumTime, int &sumAct, int &usefulActs);
	void SumMonStat(string fname, float &sumTime, int &sumAct, int &usefulActs);
	
	rulSpis RULES;
	void SaveRules();
	void LoadRules();
	
	void UpdateTableExeCapt(activ &allActiv, activ_hours &activHours, 
		float &sumTime, float &sumUsefulTime, int &sumAct, 
		int &usefulActs, int onlyOneHour = -1);
	void UpdateExeCapt(activ_hours &activHours);
	void UpdatePeriodTableViewByHours(activ_hours &activHours);
	void UpdatePeriodTable(activ &CurView);
	rulSpis::iterator ownFind(string capt);
	string GetExeFromTable(int sel);
	string showAllCaptsForExe;//показывать все заголовки для определенного EXE
	void SizingWins();

// Dialog Data
	//{{AFX_DATA(CEactivityDlg)
	enum { IDD = IDD_EACTIVITY_DIALOG };
	CComboBox	combo_group;
	CSpinButtonCtrl	spin_edit;
	CEdit	edit_capts;
	CListCtrl	table_period;//таблица задания периода времени ТЗПВ
	CListCtrl	table_exe_capt;//таблица детализации
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
	afx_msg void OnOk2();
	afx_msg void OnSelchangeCombo_sort();
	afx_msg void OnDblclkListDays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboDownTable();
	afx_msg void OnDblclkListCurDay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnActivitySetKoef();
	afx_msg void OnRclickListCurDay(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnActivitySetkoefeExe();
	afx_msg void OnChangeEDITcapts();
	afx_msg void OnActivityShowAllCapts();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSave();
	CMSChart chart; //http://forums.codeguru.com/showthread.php?360451-C-MFC-MSChart - example
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_)
