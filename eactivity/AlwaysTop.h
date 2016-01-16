#pragma once
#include "afxwin.h"
#include "externals/XHTMLStatic.h"
#include "statsfunc.h"
#include "old_my_src/Trifle1.h"
#include "afxcmn.h"

#define WM_INFO_CLOSE WM_USER + 6

struct PreWorkPeriod 
{
	float firstUsefulTime;
	float currentUsefulTime;
};

struct WorkPeriod 
{
	float currentUsefulTime;
	int   currentUsefulActs;
	float firstUsefulTime;
	int   firstUsefulActs;
	DWORD startProgressTime;
	float maxUsefulPar;
	int typeUsefulPar;  //1 - �������� �������� - ���-�� �������� ��������, 
	//2 - �������� �������� - �������� �����
	//3 - �������� �������� - ������� �����
	//0 - �� ���������� ����������� (������� ���������� �� �������)
	float getUsefulPar();
	int pauses;		//���������� ����
	bool paused;		//������� �����
	CString textMes; //��������� ��������� ��� ��������
	BOOL shortTodo; //���������� �� �������� ���� ��� ��������
	BOOL onlineAdvice; //���������� ���� �� ������ ������ �������
	int typeShowBreak; //����� ������� ���������� ������ ��������: 
								//������������ � ����������, 
								//���������� �� ����� ��������� ����� 
								//��� ����� ��������� ������ ������������
};

class CAlwaysTop : public CDialog
{
	DECLARE_DYNAMIC(CAlwaysTop)

	StatsFunc statsF; //������� ������ �� ����������� �������� � ��������� ����
	CTrifle trif;
	void ResizeOtherWins();
public:
	CAlwaysTop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAlwaysTop();
	void StartShow();
	void StartProgress(float UsefulActs, float UsefulTime, float UsualTime);
	int curHour; //������� ���, ����� ����������� ������ 5 ���
	UINT RR, GG;//���� ������� ���������� � ������� ���
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
	PreWorkPeriod preWork;
	bool ShowWarnMessageBox;

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
