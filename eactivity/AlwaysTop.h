#pragma once
#include "afxwin.h"
#include "externals/XHTMLStatic.h"
#include "statsfunc.h"
#include "old_my_src/Trifle1.h"

#define WM_INFO_CLOSE WM_USER + 6

// CAlwaysTop dialog

class CAlwaysTop : public CDialog
{
	DECLARE_DYNAMIC(CAlwaysTop)

	StatsFunc statsF; //функции работы со статистикой вынесены в отдельный файл
	CTrifle trif;
public:
	CAlwaysTop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAlwaysTop();
	void StartShow();
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

// Dialog Data
	enum { IDD = IDD_ALWAYS_TOP };

	virtual void OnCancel();
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CXHTMLStatic stat_day_adv;
	CXHTMLStatic stat_hour_adv;
	CStatic stat_hour_description;
	CStatic stat_day_description;
};
