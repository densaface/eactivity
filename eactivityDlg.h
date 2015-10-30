#include "ppToolTip/PPTooltip.h"
#include "winwork.h"
#include "koeff.h"
#include "newmenu.h"
#include "ViewRules.h"
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
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
	int num_acts;
	int points;
	float sumTime;
	float usefulTime;
};

//структура для хранения активности только по EXE
struct Activity2
{
	string exe;
	int num_acts;
	int points;
	float sumTime;
	float usefulTime;
};

typedef map<string, Activity, less<string> > activ;
typedef map<string, Activity2, less<string> > activ2;
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
	int GetPointsFromExe(string exe, activ &forLoad1);
	float GetTimeFromExe (string exe, activ &forLoad1);
	
	void AddToExeCapt(char *capt, string &exe, HWND HChil, HWND hwMain, int num_acts, float sumTime);
	void AddToOnlyExe(string &exe, int num_acts, float sumTime);
	void AnalActivUser(SendStruct* curAct);
	UINT forTimeNoActiv;
	CPoint cpNoActiv;//позиция мыши при неактивности пользователя
	CCpuUsage cpu;
	string path_actuser;//папка где хранятся файлы с активностью пользователя

	//** понять почему используются 2 векторного массива вместо одного
	//для текущего дня
	activ ACTIV;	//группировка активности ПО EXE И ЗАГОЛОВКУ
	activ2 Activ2;	//группировка активности по exe
	//для выделенного дня (** проверить может ли для выбранного месяца)
	activ aSelDayView;	//группировку активности ПО EXE И ЗАГОЛОВКУ
	activ2 aSelDayView_exe;	//группировку активности по exe

	void SaveCurDay(bool smena=false);
	void LoadCurDay();
	bool LoadFileDay(string fname, activ &forLoad1, activ2 &forLoad2);
	void SumDayStatForCurDay(); //активность текущего дня обновляется в подневном представлении
	string curDayFileName;//фактически текущий день
	
	void SaveCurMonth(bool smena=false);
	void LoadCurMonth();
	bool LoadFileMonth(string fname, activ &forLoad1, float &sumTime, int &sumActs, int &sumPoints);
	void LoadMonthFromStatDays(activ &forLoad1, string mon, float &sumTime, int &sumActs, int &sumPoints);
	void SumDayStat(activ &forLoad1, string fname, float &sumTime, int &sumActs, int &sumPoints);
	string curMonFileName;
	activ aCurMon;	//статистика по дням для текущего показа в нижней таблице
	activ aSelMonView;	//для выбранного показа по двойному клику
	bool SelDayOrCurDay;
	
	void SaveYear();
	void LoadYear();
	void LoadYearFromStatMons(string mon, float &sumTime, int &sumAct, int &sumPoints);
	void SumMonStat(string fname, float &sumTime, int &sumAct, int &sumPoints);
	string curYear;
	activ aCurYear;	//статистика по МЕСЯЦАМ для текущего показа в нижней таблице
	bool SelMonOrCurMon;
	
	rulSpis RULES;
	void SaveRules();
	void LoadRules();
	
	void UpdateTopTable(activ &forLoad1, activ2 &forLoad2, 
		float &sumTime, float &sumUsefulTime, int &sumAct, int &sumPoints);
	void UpdatePoints();
	void OutPutDownTable(activ &CurView);
	rulSpis::iterator ownFind(string capt);
	string GetExeFromTable(int sel);
	string showAllCaptsForExe;//показывать все заголовки для определенного EXE
	void SizingWins();

// Dialog Data
	//{{AFX_DATA(CEactivityDlg)
	enum { IDD = IDD_EACTIVITY_DIALOG };
	CComboBox	combo_grup;
	CSpinButtonCtrl	spin_edit;
	CEdit	edit_capts;
	CListCtrl	list_days;
	CComboBox	combo_sort;
	CListCtrl	top_table;
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EACTIVITYDLG_H__5590C786_91A0_410F_93C3_2740B59FA6EF__INCLUDED_)
