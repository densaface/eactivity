// OnlineAdviceModerate.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "OnlineAdviceModerate.h"


// COnlineAdviceModerate dialog

IMPLEMENT_DYNAMIC(COnlineAdviceModerate, CDialog)

COnlineAdviceModerate::COnlineAdviceModerate(CWnd* pParent /*=NULL*/)
	: CDialog(COnlineAdviceModerate::IDD, pParent)
{

}

COnlineAdviceModerate::~COnlineAdviceModerate()
{
}

void COnlineAdviceModerate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_mes);
	DDX_Control(pDX, IDC_SLIDER1, slider_rate1);
	DDX_Control(pDX, IDC_SLIDER3, slider_rate2);
	DDX_Control(pDX, IDC_SLIDER2, slider_rate3);
	DDX_Control(pDX, IDC_STATIC2, stat_rate_desc1);
	DDX_Control(pDX, IDC_STATIC3, stat_rate_desc2);
	DDX_Control(pDX, IDC_STATIC4, stat_rate_desc3);
}


BEGIN_MESSAGE_MAP(COnlineAdviceModerate, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &COnlineAdviceModerate::OnBnClickedVote)
	ON_BN_CLICKED(IDOK2, &COnlineAdviceModerate::OnBnClickedOk)
	ON_BN_CLICKED(IDOK3, &COnlineAdviceModerate::OnBnClickedOk3)
END_MESSAGE_MAP()

bool init = false;
BOOL COnlineAdviceModerate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	slider_rate1.SetRange(1, 6);
	slider_rate2.SetRange(1, 6);
	slider_rate3.SetRange(1, 6);
	slider_rate1.SetPos(6);
	slider_rate2.SetPos(6);
	slider_rate3.SetPos(6);
	curIndex = 0;
	UpdateControls();
	init = true;
	return TRUE;
}
void COnlineAdviceModerate::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)  
{
	CSliderCtrl* pSlider = reinterpret_cast<CSliderCtrl*>(pScrollBar);
	int sliderNum = -1;
	if (pSlider == &slider_rate1)  
		sliderNum = 1;
	else if (pSlider == &slider_rate2)  
		sliderNum = 2;
	else if (pSlider == &slider_rate3)  
		sliderNum = 3;
	// 	 switch(nSBCode)
	// 	 {
	// 	 case TB_LINEUP:  
	// 	 case TB_LINEDOWN:  
	// 	 case TB_PAGEUP:  
	// 	 case TB_PAGEDOWN:  
	// 	 case TB_THUMBPOSITION:  
	// 	 case TB_TOP:  
	// 	 case TB_BOTTOM:  
	// 	 case TB_THUMBTRACK:  
	// 	 case TB_ENDTRACK:  
	// 	 default:  
	// 		 break;
	// 	 
	CString str;
	switch (sliderNum)
	{
	case 1:
		if (slider_rate1.GetPos() < 6)
		{
			str.LoadString(trif.GetIds(IDS_STRING1775+2*slider_rate1.GetPos()));
		} else {
			str.LoadString(trif.GetIds(IDS_STRING1775));
		}
		stat_rate_desc1.SetWindowText(str);
		break;
	case 2:
		if (slider_rate2.GetPos() < 6)
		{
			str.LoadString(trif.GetIds(IDS_STRING1821+2*slider_rate2.GetPos()));
		} else {
			str.LoadString(trif.GetIds(IDS_STRING1821));
		}
		stat_rate_desc2.SetWindowText(str);
		break;
	case 3:
		if (slider_rate3.GetPos() < 6)
		{
			str.LoadString(trif.GetIds(IDS_STRING1833 + 2*slider_rate3.GetPos()));
		} else {
			str.LoadString(trif.GetIds(IDS_STRING1833));
		}
		stat_rate_desc3.SetWindowText(str);
		break;
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

//отправка голосования
void COnlineAdviceModerate::OnBnClickedVote()
{
	while (myRows->fields >= rate1.GetSize())
		rate1.Add(6);
	while (myRows->fields >= rate2.GetSize())
		rate2.Add(6);
	while (myRows->fields >= rate3.GetSize())
		rate3.Add(6);
	rate1[curIndex] = slider_rate1.GetPos();
	rate2[curIndex] = slider_rate2.GetPos();
	rate3[curIndex] = slider_rate3.GetPos();
	// проверка что хотя бы 2 оценки за изречение выставлены
	bool twoRatesSet = true;
	for (int ii=0; ii<myRows->fields; ii++)
	{
		if (rate1[ii] + rate2[ii] == 12 || rate1[ii] + rate3[ii] == 12 || rate2[ii] + rate3[ii] == 12)
		{
			twoRatesSet = false;
			break;
		}

	}
	if (!twoRatesSet)
	{
		AfxMessageBox(IDS_STRING1845);
		return;
	}
	OnOK();
	CDialog::OnOK();
}

void COnlineAdviceModerate::OnBnClickedOk()
{
	while (curIndex >= rate1.GetSize())
		rate1.Add(6);
	while (curIndex >= rate2.GetSize())
		rate2.Add(6);
	while (curIndex >= rate3.GetSize())
		rate3.Add(6);
	rate1[curIndex] = slider_rate1.GetPos();
	rate2[curIndex] = slider_rate2.GetPos();
	rate3[curIndex] = slider_rate3.GetPos();
	curIndex++;
	UpdateControls();
}

void COnlineAdviceModerate::UpdateControls()
{
	CString str;
	str.LoadString(trif.GetIds(IDS_STRING1819));
	char ch[512];
	sprintf_s(ch, str, curIndex, myRows->fields);
	edit_mes.SetWindowText(myRows[curIndex].row[1]._data.c_str());
	GetDlgItem(IDOK2) ->EnableWindow(curIndex != myRows->fields - 1);
	GetDlgItem(IDOK3)->EnableWindow(curIndex != 0);
	if (curIndex < rate1.GetSize())
		slider_rate1.SetPos(rate1[curIndex]);
	else slider_rate1.SetPos(6);
	if (curIndex < rate2.GetSize())
		slider_rate2.SetPos(rate2[curIndex]);
	else slider_rate2.SetPos(6);
	if (curIndex < rate3.GetSize())
		slider_rate3.SetPos(rate3[curIndex]);
	else slider_rate3.SetPos(6);
	if (!init)
		return;
	OnHScroll(0, 0, (CScrollBar *)&slider_rate1);
	OnHScroll(0, 0, (CScrollBar *)&slider_rate2);
	OnHScroll(0, 0, (CScrollBar *)&slider_rate3);
}

void COnlineAdviceModerate::OnBnClickedOk3()
{
	while (curIndex >= rate1.GetSize())
		rate1.Add(6);
	while (curIndex >= rate2.GetSize())
		rate2.Add(6);
	while (curIndex >= rate3.GetSize())
		rate3.Add(6);
	rate1[curIndex] = slider_rate1.GetPos();
	rate2[curIndex] = slider_rate2.GetPos();
	rate3[curIndex] = slider_rate3.GetPos();
	curIndex--;
	UpdateControls();
}