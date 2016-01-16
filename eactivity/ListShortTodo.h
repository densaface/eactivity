#pragma once
#include "afxcmn.h"
#include "externals\ListCtrl\CGridListCtrlEx\CGridListCtrlEx.h"
#include "old_my_src/winwork.h"
#include "afxwin.h"
#include <iostream>
#include <fstream>
using namespace std;


// CListShortTodo dialog

class CListShortTodo : public CDialog
{
	DECLARE_DYNAMIC(CListShortTodo)
	CMenu menuTree;
	void LoadListTodo(bool interFace=true);

public:
	CListShortTodo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListShortTodo();
	CTrifle trif;
	string path_actuser;
	CUIntArray uniqNums;
	UINT GetUniqNum();

	// более подробные об€ъснени€ по работе класса
	// https://docs.google.com/document/d/1D93i7lIalJDyfmP_ZVkOAygviFBDpfx0g3Y_PT7Dtns/edit
	int GetSelectedGroup(int selRowAction, bool interFace=true);
	int SetPercentForNewGroup(int rowNewGroup);
	void SetPercentForNewAction(int rowNewGroup, int rowNewAction);
	int GetNoEmptyGroupCount();
	void percentDistribution(double delta, bool fromSpin = false);
	void normAllGroupsAndActions();
	void NormPercForOneGroup(int rowGroup, double newPercent, double oldPercent, int unChangedRow=-1);
	double getSumPercFromOneGroup(int rowGroup);
	bool IsRowGroup(int row);
	bool IsRowAction(int row, bool interFace=true);
	int getActionCountInGroup(int rowGroup);
	CString getRandomShortAction(CString& sGroup, CString& sLink, CString& sProg, UINT& uniq);
	CString findLastTimeMakingShortTodo(int uniqNum);
	CStringArray colomn0;
	CStringArray colomn1;
	CStringArray colomn2;
	CStringArray colomn3;
	CString getLink(int selRow, bool interFace=true);
	CString getProgram(int selRow, bool interFace=true);
	int getOften(int selRow, bool interFace, int& comboPeriod);
	DWORD getSecsFromOften(int durationPeriod, int typePeriod);
	CString CompilLinkAndProg(CString sLink, CString sProg, int howOften, int typePeriod=-1);

	enum { IDD = IDD_SHORTTODO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnContextAddnewitem();
	CGridListCtrlEx list_todo;
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMRClickList3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit edit_name;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnContext32796();
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit edit_percent;
	afx_msg void OnEnChangeEditPercent();
	afx_msg void OnContextDelete();
	afx_msg void OnEnChangeEdit2();
	CEdit edit_link;
	CEdit edit_start_program;
	afx_msg void OnEnChangeEdit4();
	CButton check_no_often;
	afx_msg void OnBnClickedCheck1();
	CEdit edit_how_often;
	CComboBox combo_often;
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEnChangeEditr18();
	afx_msg void OnBnClickedButton1();
};
