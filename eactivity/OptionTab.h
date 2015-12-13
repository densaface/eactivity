#include "old_my_src/Trifle1.h"
#include "externals/XHTMLStatic.h"
#include "statsfunc.h"
#include "old_my_src/Trifle1.h"

#pragma once


// COptionTab dialog

class COptionTab : public CPropertyPage
{
	DECLARE_DYNAMIC(COptionTab)
	CTrifle trif;
public:
	COptionTab(const char* lpszTitle, UINT nIconID);
	virtual ~COptionTab();

// Dialog Data
	enum { IDD = IDD_OptionTab };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnApply();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	UINT m_nIconID;
	HICON m_hIcon;
public:
	CComboBox combo_sleep_period;
	CEdit edit_sleep_period;
	CEdit edit_holiday;
};
#pragma once

// COptionTab2 dialog
class COptionTab2 : public CPropertyPage
{
	DECLARE_DYNAMIC(COptionTab2)
	StatsFunc statsF; //������� ������ �� ����������� �������� � ��������� ����
	CTrifle trif;
public:
	COptionTab2(const char* lpszTitle, UINT nIconID);
	CString faceFont;
	virtual ~COptionTab2();

// Dialog Data
	enum { IDD = IDD_OptionTab2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CXHTMLStatic stat_day_adv;
	CXHTMLStatic stat_hour_adv;
	CStatic stat_hour_description;
	CStatic stat_day_description;
	CEdit edit_size_font;
	CEdit edit_frequpdate;
	CButton check_bold;
	CButton check_hide_description;

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();
private:
	UINT m_nIconID;
	HICON m_hIcon;
public:
	afx_msg void OnApplyFont();
	afx_msg void OnBnClickedCheck3();
};