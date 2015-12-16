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
	afx_msg void OnBnClickedRadio1();

	DECLARE_MESSAGE_MAP()

private:
	UINT m_nIconID;
	HICON m_hIcon;
protected:
	CComboBox combo_sleep_period;
	CButton radio_const_norm;
	CButton radio_norm_last_days;
	CEdit edit_sleep_period;
	CEdit edit_holiday;
	CEdit edit_hour_norm;
	CEdit edit_hour_begin;
	CEdit edit_hour_end;
};
#pragma once

// COptionTab2 dialog
class COptionTab2 : public CPropertyPage
{
	DECLARE_DYNAMIC(COptionTab2)
	StatsFunc statsF; //функции работы со статистикой вынесены в отдельный файл
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
#pragma once


// COptionTabMail dialog

class COptionTabMail : public CPropertyPage
{
	DECLARE_DYNAMIC(COptionTabMail)

	StatsFunc statsF;
	CTrifle trif;
	UINT m_nIconID;
	HICON m_hIcon;
public:
	COptionTabMail(const char* lpszTitle, UINT nIconID);
	virtual ~COptionTabMail();

// Dialog Data
	enum { IDD = IDD_OptionTabMail };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnTestMail();
	virtual BOOL OnInitDialog();
	virtual BOOL OnApply();
	afx_msg void OnBnClickedCheckEmail();

	CEdit edit_email;
	CButton check_email;
};
