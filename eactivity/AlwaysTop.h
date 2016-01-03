#pragma once
#include "afxwin.h"
#include "externals/XHTMLStatic.h"
#include "statsfunc.h"
#include "old_my_src/Trifle1.h"
#include "afxcmn.h"

#define WM_INFO_CLOSE WM_USER + 6

struct WorkPeriod 
{
	float currentUsefulTime;
	int   currentUsefulActs;
	float firstUsefulTime;
	int   firstUsefulActs;
	DWORD startProgressTime;
	float maxUsefulPar;
	int typeUsefulPar;  //1 - полезный параметр - кол-во полезных действий, 
	//2 - полезный параметр - полезное время
	//2 - полезный параметр - обычное время
	//0 - не показывать прогрессбар
	float getUsefulPar();
	int pauses;		//количество пауз
	bool paused;		//признак паузы
	CString textMes; //текстовое сообщение для перерыва
	BOOL shortTodo; //предлагать ли короткое дело для перерыва
	int typeShowBreak;
};

class CAlwaysTop : public CDialog
{
	DECLARE_DYNAMIC(CAlwaysTop)

	StatsFunc statsF; //функции работы со статистикой вынесены в отдельный файл
	CTrifle trif;
	void ResizeOtherWins();
public:
	CAlwaysTop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAlwaysTop();
	void StartShow();
	void StartProgress(float UsefulActs, float UsefulTime, float UsualTime);
	int curHour; //текущий час, смена проверяется каждые 5 сек
	UINT RR, GG;//цвет статика отставания в текущем дне
	CString CalculateDayNorm(activ_hours &lastAverageHoursGraph,
		float sumUsefulSec, CString &static2, double coefNorm);
	CString CalculateHourNorm(activ_hours &lastAverageHoursGraph,
		float usefulTimeForCurrentHour, CString &static2, double coefNorm);
	void SavePosition();
	BOOL bold;
	BOOL hidedescription;
	bool resizeWins;
	int sizefont;
	int frequpdate;
	bool isEndWork();
	void setEndWork();
	WorkPeriod workPeriod;

// Dialog Data
	enum { IDD = IDD_ALWAYS_TOP };

	virtual void OnCancel();
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CXHTMLStatic stat_day_adv;
	CXHTMLStatic stat_hour_adv;
	CXHTMLStatic static_progress;
	CStatic stat_hour_description;
	CStatic stat_day_description;
	CProgressCtrl progress_useful;
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
};
