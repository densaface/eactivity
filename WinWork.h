#define CAPTUREBLT (DWORD)0x40000000

#define MODISUCCESS 1
#define OCRSUCCESSREPLAY 1
// WinWork.h: interface for the CWinWork class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_WINWORK_H__72813899_0ECA_4473_953E_CD1DA3400931__INCLUDED_)
#define AFX_WINWORK_H__72813899_0ECA_4473_953E_CD1DA3400931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "appendhead.h"

enum MiLANGUAGES 
{ miLANG_CHINESE_SIMPLIFIED = 2052,
miLANG_CHINESE_TRADITIONAL = 1028,
miLANG_CZECH = 5,
miLANG_DANISH = 6, 
miLANG_DUTCH = 19,
miLANG_ENGLISH = 9,
miLANG_FINNISH = 11,
miLANG_FRENCH = 12,
miLANG_GERMAN = 7,
miLANG_GREEK = 8, 
miLANG_HUNGARIAN = 14,
miLANG_ITALIAN = 16,
miLANG_JAPANESE = 17,
miLANG_KOREAN = 18,
miLANG_NORWEGIAN = 20,
miLANG_POLISH = 21,
miLANG_PORTUGUESE = 22,
miLANG_RUSSIAN = 25,
miLANG_SPANISH = 10,
miLANG_SWEDISH = 29,
miLANG_SYSDEFAULT = 2048,
miLANG_TURKISH = 31
};

enum TYPERECOG
{
	TYPE_OCR_MODI = 1,
	TYPE_CAPTCHA_BOT = 2
};

struct LaunchingApp
{//для контроля окна запущенного приложения
	DWORD dwProcessId;
	CString exe_Name;
	HWND hw_exe;
};

struct sForSearchWin 
{
	int begiMai, endMai;//начало и конец нумерации с найденными одинаковыми окнами
	int begiChi, endChi;//то же самое для дочерних окон

};

typedef  CArray  < LaunchingApp, int > MyLaunchingApp;

class CAppDlg;
class CWinWork;
class CTrifle;

//КЛАСС ДЛЯ РАБОТЫ С ВИНДОВЫМИ ОКНАМИ
class CWinWork  
{
	int GetCounPar(HWND whPar);
	//CWinWork* wwork;
public:
	CCpuUsage cpu;
	bool shif, ctrl, alt; //хранят текущее состояние клавиш для их отжатия, если они сами не отжались
	HANDLE hPause;
	HWND stopME;
	hwnd_Array hw_exe;
	CStringArray sa_exe;
	CUIntArray tormoz;
	//даем команду выхода из поиска
	bool stop_sear;
	//вышли из цикла поиска
	bool exit_cikl;
	int SpeedPlay;
	//int randVetv;
	//CString OutStr1;
	UINT PlaySmart(CStringArray &coms, int speed, 
		bool uvorot/*=true*/, HWND stopme/*=NULL*/, int UN/*=-1*/, CString pathSC);
	CString pathForScr;
	bool played;//закончилось ли воспроизв. Смартконтроля
	CTrifle trif;
	UINT StopSearch();
	CWinThread *ThreadSearchPix;
	bool zap_thread;
	UINT SearchKusok(CStringArray &COMS, HWND stopme, CString pathSC/*
	, CUIntArray &typeSear, 
			CUIntArray &xl, CUIntArray &xr, CUIntArray &yt, CUIntArray &yb*/
	);
	pBGR MyGetDibBits(CDC* hdcSrc, int nx, int ny);
	BOOL InvertRectLine(CDC *pDc, CPoint ptFrom, CPoint ptTo);
	UINT fi_coorx, fi_coory; //по каким координатам найдено пиксельное изображение
	int pix_sxx, pix_syy;//ширина и высота искомого прямоугольника
	UINT com_time; //время поиска
	float MinOtk; //минимальное отклонение от искомой картинки
	float ColPerPix;
	bool PictIsFi;
	int num_find_bmp;
	CString ForPlayAip;
	CString ProvPlayAip;

	//работы с COMS
	bool ComsToSC(CStringArray &coms, sSmartControl_tmp &SC, CString pathSC);
	bool ComsToMouse(CStringArray &coms, forMousePress &SC);
	bool ComsToKey(CStringArray &coms, forKeyPress &SC);
	bool SCToComs(sSmartControl_tmp &SC, CStringArray &coms);

//	bool KeyToComs(forKeyPress &key, CStringArray &coms);
	bool StrToCrects(CString &OBJs, MyCRectAr &CutRects, MyCRectAr &SaveRects, CStringArray &SaveBmps);
	bool KeysToMes(CString &keys, CUIntArray &Mess);
	bool CheckQueueMouse(SendStruct* curAct, Act &waitAct, int ii); //проверка действия при ожидании его 
		//прохождения через очередь

	//поправки при изменении позиции рамок Родительского окна
//	int glob_popravy;
//	int glob_popravx;
	int MainWinPoprx;
	int MainWinPopry;
	int ChaiWinPoprx;
	int ChaiWinPopry;
	void NulPopr();

//	CUIntArray arCorMousPos_mesx, arCorMousPos_mesy;//запасной массив координат мышки 
//	CUIntArray arCorMousBoundLR, arCorMousBoundTB, //запасной массив границ дочернего окна 
//		arMainBoundLR, arMainBoundTB;//и главного
// 	CUIntArray mouse_movx; //для возврата координат движений мышки
// 	CUIntArray mouse_movy; //для возврата координат движений мышки
	bool isMenu(CString str);
	byte CheckSizeWin(HWND par, HWND chi, int Main_l, int Main_t, int Chil_l, int Chil_t, int xx, int yy);
	bool CheckChildWin(CString MainWinCapt, CString MainClassName, BOOL MainHowChange, 
							 CString ChildIerarh, CString ChildWinCapt, CString ChildClassName, 
							 int xx, int yy, HWND &hwChild, bool razr_mes, HWND hwChildOrig=NULL);
	BOOL SetParentPosit(HWND hwMain, CString MainClassName, 
						int Main_l, int Main_t, int Main_r, int Main_b, 
						bool razr_dvig, int xx, int yy);
	bool CheckParentWin(Acti& MyAct, int tt, HWND hwMain);
	WinPla WindPlac;//массив положений окон для их восстановления после проигрывания
	WINPLA forWP;//для этого массива
	HWND GetPar(HWND hw);
	//более точное взятие дочернего окна из точки (hwnd-степень детализации)
	HWND MyWindowFromPoint(int x, int y, bool razr_mes, HWND hwnd=NULL);
	//пошаговое перемещение курсора
	//void MySetCursorPos(int x, int y);
//	CString ExtractCapt(CString str);

	DWORD GetPidFromExeStruct(CString exe);
	void AddToExeStruct(CString exe, DWORD pid);
	MyLaunchingApp sApp;
	CWinWork();
	BOOL RestoreWindowState(HWND hw);
	BOOL SaveWindowState(HWND hw);
	BOOL MySetForegroundWindow(HWND par, bool without_execute=false);
	bool rabTable;//если идет работа с рабочим столом, то в фокус не будет ничего выводиться

	//ПОИСКИ
	int GetBalsFrom(HWND hw, bool &norm_capt);
	void BalsAdd(HWND hw, int bals, bool norm_capt=false);
	void ChiBalsAdd(HWND hw_main, HWND hw_chi, int bals);
	mai_hwnd_Array mai_hw_reits;
	chi_hwnd_Array chi_hw_reits;
	int SearchWindows(Acti& MyAct, int tt, int bals_lim, int chi_lim, bool correct_capt, HWND mai=0, bool test=false);
	HWND FindMainWindow2(CString csMainWindowCapt, BOOL Slice, CString ClasName);
	HWND FindMainWindow3(CString csMainWindowCapt, BOOL Slice, CString ClasName);
	int EstPause;//размер паузы между действиями
	void UnKey(bool play=true);//отжатие шифта, контрола и альта
	virtual ~CWinWork();
//нажатие клавиатуры
	void PressKey(UINT code, HWND chil, HWND par, UINT mes, LPARAM lpar, bool KeyUp);
//функция проверки: надо ли нажимать клавишу через Post
	bool CodePost(UINT code);
//функция проверки: надо ли нажимать клавишу через keybd_event
	bool CodeKeyb(UINT code);
	HWND FindMainWindow(CString windowtext, BOOL Slice=true, CString ClasName="", int x=0, int y=0, DWORD pid=0);
	HWND Findhwnd(HWND hw, CString str, BOOL Slice=false, 
		BOOL ForClassname=false, BOOL cikle=false);
	HWND FindhwndIerarEx(HWND hw, CString ier, CString CapChi, CString ClaChi
		, BOOL Slice, BOOL ForClassname, BOOL cikle, 
		int id=0, int x=0, int y=0, bool recLog=false);
	HWND FindhwndIerar(HWND hw, CString ier, CString ClName,
		CString Capt, bool prover=true, bool debu=false);
	CString GetIerar(HWND whChi);
	BOOL IsFirWinInParent(HWND chi, HWND par);
	//взятие следующего окна
	HWND GetNextWin(HWND hw_prev);
	HWND GetNextMainWin(HWND hw_prev);
	HWND GetNextChild(HWND par, HWND hw_prev);
	//void MyLoadKeyboardLayout(CString lay);
	//void SetHinst(HINSTANCE hMyDll);
	BOOL Reboot(bool reboot, bool force);
};

#endif // !defined(AFX_WINWORK_H__72813899_0ECA_4473_953E_CD1DA3400931__INCLUDED_)
