// ReportSelectedPeriod.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "ReportSelectedPeriod.h"


// CReportSelectedPeriod dialog

IMPLEMENT_DYNAMIC(CReportSelectedPeriod, CDialog)

CReportSelectedPeriod::CReportSelectedPeriod(CWnd* pParent /*=NULL*/)
	: CDialog(CReportSelectedPeriod::IDD, pParent)
{

}

CReportSelectedPeriod::~CReportSelectedPeriod()
{
}

void CReportSelectedPeriod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listMainDates);
	DDX_Control(pDX, IDC_LIST5, listComparedDates);
	DDX_Control(pDX, IDC_COMBO1, comboMon);
	DDX_Control(pDX, IDC_LIST4, listOffers);
}


BEGIN_MESSAGE_MAP(CReportSelectedPeriod, CDialog)
	ON_BN_CLICKED(IDOK, &CReportSelectedPeriod::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CReportSelectedPeriod::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CReportSelectedPeriod::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CReportSelectedPeriod::OnBnClickedButton2)
END_MESSAGE_MAP()


// CReportSelectedPeriod message handlers
BOOL CReportSelectedPeriod::OnInitDialog()
{
	CDialog::OnInitDialog();
	for (int ii=0; ii<saDates.GetSize(); ii++)
	{
		CString debs=saDates[ii];
		listMainDates.AddString(saDates[ii]);
	}

	//ищем статистики за год и загружаем все мясяцы в комбо выбора месяца
	WIN32_FIND_DATA FFData;
	HANDLE hFind = FindFirstFile((path_actuser+"activ_user_*.ayr").c_str(), &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			CString Path=FFData.cFileName;
			if(((FFData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				!=FILE_ATTRIBUTE_DIRECTORY) && Path!="." && Path!="..")
			{
				string date2 = path_actuser+FFData.cFileName;
				activ aYear;
				statsF.LoadYear(aYear, date2);
				for (activ::iterator iter=aYear.begin(); iter!=aYear.end(); iter++)
				{
					if (!saDates.GetSize())
						break;
					switch (saDates[0].GetLength())
					{
					case DAY:
						comboMon.AddString(iter->first.c_str());
						break;
					case MON:
						AddToListOffers(iter->first.c_str());
						break;
					}
				}
			}		
		}
		while(FindNextFile(hFind, &FFData));
		FindClose(hFind);
	}
	if (saDates.GetSize())
	{
		switch (saDates[0].GetLength())
		{
		case DAY:
			{
				for (int ii=0; ii<comboMon.GetCount(); ii++)
				{
					CString str;
					comboMon.GetLBText(ii, str);
					if (saDates[0].Find(str)>-1)
					{
						comboMon.SetCurSel(ii);
						OnCbnSelchangeCombo1();
						break;
					}
				}
			}
			break;
		case MON:
			comboMon.EnableWindow(FALSE);
			break;
		}
	}
	return TRUE;
}

//добавление в лист предложений, чтобы не дублировалось в главном списке для сравнения
void CReportSelectedPeriod::AddToListOffers(CString newItem)
{
	BOOL itemExist = FALSE;
	for (int ii=0; ii<listComparedDates.GetCount(); ii++)
	{
		CString str;
		listComparedDates.GetText(ii, str);
		if (str == newItem)
		{
			itemExist = TRUE;
			break;
		}
	}
	for (int ii=0; ii<listMainDates.GetCount(); ii++)
	{
		CString str;
		listMainDates.GetText(ii, str);
		if (str == newItem)
		{
			itemExist = TRUE;
			break;
		}
	}
	if (!itemExist)
		listOffers.AddString(newItem);
}

void CReportSelectedPeriod::OnBnClickedOk()
{
	for (int ii=0; ii<listComparedDates.GetCount(); ii++)
	{
		CString str;
		listComparedDates.GetText(ii, str);
		saDates2.Add(str);
	}
	OnOK();
}

//ищем статистики за выбранный месяц и подгружаем все найденные дни в лист предложений
void CReportSelectedPeriod::OnCbnSelchangeCombo1()
{
	CString str;
	int ii = comboMon.GetCurSel();
	if (ii==-1) return;
	comboMon.GetLBText(ii, str);
	WIN32_FIND_DATA FFData;
	CString patter = (path_actuser+"activ_user_").c_str();
	patter += str + "*.a";
	HANDLE hFind = FindFirstFile(patter, &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		listOffers.ResetContent();
		do 
		{
			CString Path=FFData.cFileName;
			if(((FFData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				!=FILE_ATTRIBUTE_DIRECTORY) && Path!="." && Path!="..")
			{
				string date2 = path_actuser+FFData.cFileName;
				string date3 = date2.substr(date2.length()-12, 10);
				AddToListOffers(date3.c_str());
			}		
		}
		while(FindNextFile(hFind, &FFData));
		FindClose(hFind);
	}
}

//кнопка добавления промежутков времени во второй список сравнения
void CReportSelectedPeriod::OnBnClickedButton1()
{
//	int count = listOffers.GetSelCount();
	int *lp = new int[1025];
	int count2 = listOffers.GetSelItems(1024, lp);
	for(int ii = 0; ii < count2; ii++)
	{
		CString str;
		listOffers.GetText(lp[ii], str);
		listComparedDates.AddString(str);
	}
	for(int ii = count2-1; ii >= 0; ii--)
	{
		listOffers.DeleteString(lp[ii]);
		if (ii == 0)
			GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
}

void CReportSelectedPeriod::OnBnClickedButton2()
{
	int *lp = new int[1025];
	int count2 = listComparedDates.GetSelItems(1024, lp);
	for(int ii = 0; ii < count2; ii++)
	{
		CString str;
		listComparedDates.GetText(lp[ii], str);
		listOffers.AddString(str);
	}
	for(int ii = count2-1; ii >= 0; ii--)
	{
		listComparedDates.DeleteString(lp[ii]);
	}
}
