#include "../stdafx.h"
#include "WinWork.h"
#include <AFXINET.H> 
#include <winuser.h>
#include <windows.h>
#include <afxcoll.h>

#define WM_USER23 WM_USER + 23
#define WM_USER32 WM_USER + 32
#define WM_USER33 WM_USER + 33
#define WM_USER34 WM_USER + 34

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW

#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinWork::CWinWork()
{
	SpeedPlay=0;
	zap_thread=0;
	ColPerPix=100.0;
}
//extern CAppDlg* Appdlg;

CWinWork::~CWinWork()
{
//	delete trif;
}

//отжатие шифта, контрола и альта
void CWinWork::UnKey(bool play/*=true*/)
{
	if (play)
	{
		if (HIWORD(GetKeyState(MK_LBUTTON))){
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}
		if (HIWORD(GetKeyState(MK_RBUTTON))){
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		}
	}
	if (HIWORD(GetKeyState(VK_MENU))){
		//if (EstPause) Sleep(EstPause);
		////trif.RecordLog("11____________________________ отжатие");
			keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
			keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); 
		//if (EstPause) Sleep(EstPause);
	}
	if (HIWORD(GetKeyState(VK_CONTROL))){
		//if (EstPause) Sleep(EstPause);
		////trif.RecordLog("12____________________________ отжатие");
			keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); 
		//if (EstPause) Sleep(EstPause);
	}
	if (HIWORD(GetKeyState(VK_SHIFT))){
		//if (EstPause) Sleep(EstPause);
		////trif.RecordLog("13____________________________ отжатие");
			keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); 
		//if (EstPause) Sleep(EstPause);
	}
	if (HIWORD(GetKeyState(VK_END))){
		//if (EstPause) Sleep(EstPause);
		////trif.RecordLog("14____________________________ отжатие");
			keybd_event(VK_END, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
			keybd_event(VK_END, 0, KEYEVENTF_KEYUP, 0); 
		//if (EstPause) Sleep(EstPause);
	}

}

//нажатие клавиатуры
void CWinWork::PressKey(UINT code, HWND chil, HWND par, UINT mes, LPARAM lpar, bool KeyUp)
{
//	Sleep(500);
// 	CString deb;
//	deb.Format("par=%x chil=%x", par, chil);
	////trif.RecordLog(deb);
	//контроль нажатий и отжатий шифта и пр.
	if (code!=VK_SHIFT && code!=VK_CONTROL && code!=VK_MENU)
	{
		if (shif && !HIWORD(GetKeyState(VK_SHIFT)))
		{
			AfxGetMainWnd()->SendMessage(WM_USER34, 5);//logz
			keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY|0, 0); 
		}
		if (ctrl && !HIWORD(GetKeyState(VK_CONTROL)))
		{
			AfxGetMainWnd()->SendMessage(WM_USER34, 6);//logz
			keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY|0, 0); 
		}
		if (alt && !HIWORD(GetKeyState(VK_MENU)))
		{
			AfxGetMainWnd()->SendMessage(WM_USER34, 7);//logz
			keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY|0, 0); 
		}
		if (!shif && HIWORD(GetKeyState(VK_SHIFT)))
		{
			AfxGetMainWnd()->SendMessage(WM_USER34, 8);//logz
			keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
		}
		if (!ctrl && HIWORD(GetKeyState(VK_CONTROL)))
		{
			AfxGetMainWnd()->SendMessage(WM_USER34, 9);//logz
			keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
		}
		if (!alt && HIWORD(GetKeyState(VK_MENU)))
		{
			AfxGetMainWnd()->SendMessage(WM_USER34, 10);//logz
			keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
		}
	} else {
		if (code==VK_SHIFT)
			if (KeyUp)
				 shif=false;
			else shif=true;
		if (code==VK_CONTROL)
			if (KeyUp)
				ctrl=false;
			else ctrl=true;
		if (code==VK_MENU)
			if (KeyUp)
				alt=false;
			else alt=true;
	}
	//EstPause=5;


	if (!chil && !par)
	{//случай неважного действия (просто отжимаем клавишу)
		//trif.RecordLog("HIWORD="+trif.IntToStr(HIWORD(GetKeyState(code)))+"code="+trif.IntToStr(code));
		if (/*HIWORD(GetKeyState(code)) && */KeyUp)
		{
			if (EstPause && AfxGetMainWnd()->SendMessage(WM_USER34, 100)!=6) 
				WaitForSingleObject(hPause, EstPause/2);
				//Sleep(EstPause/2);
			if (KeyUp)
			{
				AfxGetMainWnd()->SendMessage(WM_USER34, 11, code);//logz
				keybd_event(code, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
			} else {
				AfxGetMainWnd()->SendMessage(WM_USER34, 12, code);//logz
				keybd_event(code, 0, KEYEVENTF_EXTENDEDKEY|0, 0); 
			}
			if (EstPause && AfxGetMainWnd()->SendMessage(WM_USER34, 100)!=6) 
				WaitForSingleObject(hPause, EstPause/2);
		}
		return;
	}
	if (!CodeKeyb(code) || (KeyUp && code==VK_MENU /*отжатие Alt*/))
	{ 
		if (EstPause && AfxGetMainWnd()->SendMessage(WM_USER34, 100)!=6) 
			WaitForSingleObject(hPause, EstPause/2);
		if (CodePost(code))
		{
			if (KeyUp && code==VK_MENU)
			{
				//if (HIWORD(GetKeyState(VK_MENU))) закоментил проверку отжатости, так как если не послать отжатие, 
				//то будет считаться, что нажатия клики не поступают в очередь сообщений, 
				//поэтому пусть будет отжатие даже при отжатой клавише Alt
				{
					AfxGetMainWnd()->SendMessage(WM_USER34, 10);//logz
					keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
					if (EstPause && AfxGetMainWnd()->SendMessage(WM_USER34, 100)!=6) 
						WaitForSingleObject(hPause, EstPause/2);
					return;
				}
			} else {
				//if (code!=VK_APPS)
				if (!KeyUp && (code==VK_END || code==VK_APPS)){//нажатие на VK_END может не сработать
					if (EstPause && AfxGetMainWnd()->SendMessage(WM_USER34, 100)!=6) 
						WaitForSingleObject(hPause, EstPause/2);
					if (!HIWORD(GetKeyState(code)))
					{
						AfxGetMainWnd()->SendMessage(WM_USER34, 12, code);//logz
						keybd_event(code, 0, KEYEVENTF_EXTENDEDKEY|0, 0); 
						return;
					}
				} else {
					AfxGetMainWnd()->SendMessage(WM_USER34, 13, code);//logz
					PostMessage(chil, mes, code, lpar);//основные сообщения
				}
			}
		} else {
			AfxGetMainWnd()->SendMessage(WM_USER34, 14, code);//logz
			SendMessage(chil, mes, code, lpar);
		}
		if (EstPause && AfxGetMainWnd()->SendMessage(WM_USER34, 100)!=6) 
			WaitForSingleObject(hPause, EstPause/2);
	} else {
		if (EstPause && AfxGetMainWnd()->SendMessage(WM_USER34, 100)!=6) 
			WaitForSingleObject(hPause, EstPause/2);
		if (KeyUp)
		{
			if (code==VK_SNAPSHOT)
			{
				AfxGetMainWnd()->SendMessage(WM_USER34, 15);//logz
				keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_EXTENDEDKEY|0, 0); 
			}
			AfxGetMainWnd()->SendMessage(WM_USER34, 11, code);//logz
			keybd_event(code, 0, KEYEVENTF_EXTENDEDKEY|KEYEVENTF_KEYUP, 0); 
		} else {
			AfxGetMainWnd()->SendMessage(WM_USER34, 12, code);//logz
			keybd_event(code, 0, KEYEVENTF_EXTENDEDKEY|0, 0); 
		}
		if (EstPause && AfxGetMainWnd()->SendMessage(WM_USER34, 100)!=6) 
			WaitForSingleObject(hPause, EstPause/2);
	}
}

//функция проверки: надо ли нажимать клавишу через Post
bool CWinWork::CodePost(UINT code)
{
	switch (code){
	case VK_MENU:
		{
			return true;
			break;
		}
	case 67:
		{
			return true;
			break;
		}
	case VK_TAB:
		{
			return true;
			break;
		}
	case VK_F1:
		{
			return true;
			break;
		}
	case VK_F2:
		{
			return true;
			break;
		}
	case VK_F3:
		{
			return true;
			break;
		}
	case VK_F4:
		{
			return true;
			break;
		}
	case VK_F5:
		{
			return true;
			break;
		}
	case VK_F6:
		{
			return true;
			break;
		}
	case VK_F7:
		{
			return true;
			break;
		}
	case VK_F8:
		{
			return true;
			break;
		}
	case VK_F9:
		{
			return true;
			break;
		}
	case VK_F10:
		{
			return true;
			break;
		}
	case VK_F11:
		{
			return true;
			break;
		}
	case VK_F12:
		{
			return true;
			break;
		}
	case VK_F13:
		{
			return true;
			break;
		}
	case VK_F14:
		{
			return true;
			break;
		}
	case VK_F15:
		{
			return true;
			break;
		}
	case VK_F16:
		{
			return true;
			break;
		}
	case VK_F17:
		{
			return true;
			break;
		}
	case VK_F18:
		{
			return true;
			break;
		}
	case VK_F19:
		{
			return true;
			break;
		}
	case VK_F20:
		{
			return true;
			break;
		}
	case VK_F21:
		{
			return true;
			break;
		}
	case VK_F22:
		{
			return true;
			break;
		}
	case VK_F23:
		{
			return true;
			break;
		}
	case VK_F24:
		{
			return true;
			break;
		}
	case VK_RIGHT:
		{
			return true;
			break;
		}
	case VK_LEFT:
		{
			return true;
			break;
		}
	case VK_DOWN:
		{
			return true;
			break;
		}
	case VK_UP:
		{
			return true;
			break;
		}
	}
	return true;//**временно - потом надо ввести перехват SendMessage
}

//функция проверки: надо ли нажимать клавишу через keybd_event
bool CWinWork::CodeKeyb(UINT code)
{
			return true;
	switch (code){
	case VK_CONTROL:
		{
			return true;
			break;
		}
	case VK_TAB:
		{
			return true;
			break;
		}
	case VK_MENU:
		{
			return true;
			break;
		}
	case VK_SHIFT:
		{
			return true;
			break;
		}
	}
	return false;
}

//поиск дочернего окна с известным заголовком, либо куском заголовка
//ForClassname - осуществлять ли поиск по классу
HWND CWinWork::Findhwnd(HWND hw, CString str, BOOL Slice, BOOL ForClassname, BOOL cikle)
{
	HWND child, par, child2;
	char wintext[512];
	CString capt;
	child = GetWindow(hw,GW_CHILD);
	par = child;
	while (str!=wintext){
		//GetNextWindow(
		if (child)
		if (!ForClassname){
			GetWindowText(child, wintext, GetWindowTextLength(child)+1);
			if (wintext==str) return child;
			capt=wintext;
			if (Slice)
				if (capt.Find(str, 0)>-1)
					return child;
		} else {
			GetClassName(child, wintext, 100);
			if (wintext==str){
				/*CString mes;
				mes.Format("(%X)", child);
				mes+=str;
				Sleep(500);*/
				//Appdlg->MyAfxMessageBox(mes);
				return child;
			}
		}
		child = GetWindow(par, GW_CHILD);
		if (child) {par=child;
		} else {
			child = GetNextWindow(par, GW_HWNDNEXT);
			if (child)
				par=child;
			while (!child) {
				child = GetParent(par);
				if (!child) return 0;
				if (child==hw) {
					if (cikle) return 0;
					child=GetNextWindow(hw, GW_HWNDPREV);
					while (child){
						if (hw==GetParent(child)){
							child2=Findhwnd(child, str, Slice, ForClassname, 1);
							if (child2)
								return child2;
						}
						child=GetNextWindow(child, GW_HWNDPREV);
					}
					child=GetNextWindow(hw, GW_HWNDNEXT);
					while (child){
						if (hw==GetParent(child)){
							child2=Findhwnd(child, str, Slice, ForClassname, 1);
							if (child2)
								return child2;
						}
						child=GetNextWindow(child, GW_HWNDNEXT);
					}
					return 0;
				}
				par=child;
				child = GetNextWindow(par, GW_HWNDNEXT);
				if (child)
					par=child;
			}
		}
	}
return 0;
}

BOOL CWinWork::IsFirWinInParent(HWND chi, HWND par){
	HWND chi2=::GetWindow(par, GW_CHILD);
	if (chi2==chi){
		return 1;
	}
	while (chi2=::GetNextWindow(chi2, GW_HWNDNEXT)){
		if (chi2==chi){
			return 1;
		}
	}
	return 0;
}

	//вычисление иерархии
CString CWinWork::GetIerar(HWND whChi)
{
	int counTree=0;
	CString res;
	while (::GetNextWindow(whChi, GW_HWNDPREV)){
		whChi=::GetNextWindow(whChi, GW_HWNDPREV);
		counTree++;
	}
	res.Format("%d))", counTree);
	whChi=::GetParent(whChi);
	while (whChi){
		if (!::GetParent(whChi)) break;
		if (!IsFirWinInParent(whChi, ::GetParent(whChi))){
			counTree=0;
			HWND chi=::GetNextWindow(whChi, GW_HWNDNEXT);
			if (chi) counTree++;
			if (::GetParent(whChi)!=chi)
				while (chi=::GetNextWindow(chi, GW_HWNDNEXT)){
					if (::GetParent(whChi)==chi){
						counTree++;
						break;
					}
					counTree++;
				}
			if (::GetParent(whChi)==chi){
					//res.Format("N%d:"+res, counTree);
				}
		} else {
			res.Format("%d:"+res, GetCounPar(whChi));
		}
		whChi=::GetParent(whChi);
	}
	res="(("+res;
	return res;
}

int CWinWork::GetCounPar(HWND whPar){
	int counTree=0;
	whPar=GetNextWindow(whPar, GW_HWNDPREV);
	if (whPar) counTree++;
	while (whPar=GetNextWindow(whPar, GW_HWNDPREV))
		counTree++;
	return counTree;
}

//поиск дочернего окна с "гибкой" иерархией - слеплен из готовых кусков, поэтому все можно сделать изящнее
//ForClassname - осуществлять ли поиск по классу
//int x, int y - центр искомого окна, ищется окно с центром наиболее близким к данному центру
//bool reclog - разрешение на запись в лог
HWND CWinWork::FindhwndIerarEx(HWND hw, CString ier, CString CapChi, CString ClaChi
				, BOOL Slice, BOOL ForClassname, BOOL cikle, int id, int x, int y, bool recLog)
{
	HWND child, par, child2,
	child_cen=0;//сюда будет запоминаться окно более близкое по центру
	CRect rec; int l_2=0, l_2_old=0;
	//if (recLog){ CString deb; deb.Format("x=%d y=%d hw=%x_"+ier+CapChi+ClaChi, x, y, hw); trif.RecordLog(deb);}
	char wintext[512];
	CString capt;
	int ier2=0;
	int i_ier=ier.Remove(':');
	child = GetWindow(hw,GW_CHILD);
	if (hw==(HWND)0x0ee00130)
		capt=capt;
	par = child;
	while (1==1/*CapChi!=wintext*/){
		//GetNextWindow(
		if (child)
		if (!ForClassname){
			GetWindowText(child, wintext, GetWindowTextLength(child)+1);
			if (wintext==CapChi && i_ier==ier2 && (GetDlgCtrlID(child)==id || id==0)){
				if (x==0 && y==0){
					return child;
				} else {
					::GetWindowRect(child, &rec);
					l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
						+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
		//CString deb; deb.Format("l_2=%d child=%x",l_2, child); trif.RecordLog(deb);
					if (l_2<l_2_old || l_2_old==0){
						l_2_old=l_2;
						child_cen=child;
						if (l_2_old==0) return child_cen;
					}
				}
			}
			capt=wintext;
			if (Slice)
				if (capt.Find(CapChi, 0)>-1 && i_ier==ier2 && 
					(GetDlgCtrlID(child)==id || id==0)){
					if (x==0 && y==0){
						return child;
					} else {
						::GetWindowRect(child, &rec);
						l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
							+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
		//CString deb; deb.Format("l_2=%d child=%x",l_2, child); trif.RecordLog(deb);
						if (l_2<l_2_old || l_2_old==0){
							l_2_old=l_2;
							child_cen=child;
							if (l_2_old==0) return child_cen;
						}
					}
				}
		} else {
			GetClassName(child, wintext, 100);
			if (wintext==ClaChi && i_ier==ier2 && (GetDlgCtrlID(child)==id || id==0)){
				if (x==0 && y==0){
					return child;
				} else {
					::GetWindowRect(child, &rec);
					l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
						+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
		//CString deb; deb.Format("l_2=%d child=%x",l_2, child); trif.RecordLog(deb);
					if (l_2<l_2_old || l_2_old==0){
						l_2_old=l_2;
						child_cen=child;
						if (l_2_old==0) return child_cen;
					}
				}
			}
		}
		child = GetWindow(par, GW_CHILD);
		if (child) {
			par=child;
			ier2++;
		} else {
			child = GetNextWindow(par, GW_HWNDNEXT);
			if (child)
				par=child;
			while (!child) {
				child = GetParent(par);//поднятие на уровень вверх
				ier2--;
				if (!child){
		//CString deb; deb.Format("1 return child_cen l_2=%d child=%x ",l_2, child); trif.RecordLog(deb);
					return child_cen;
				}
				if (child==hw) {
					if (cikle){ 
		//CString deb; deb.Format("2 return child_cen l_2=%d child=%x ",l_2, child); trif.RecordLog(deb);
						return child_cen;
					}
					child=GetNextWindow(hw, GW_HWNDPREV);
					while (child){
						if (hw==GetParent(child)){
							child2=Findhwnd(child, CapChi, Slice, ForClassname, 1);
							if (child2 && i_ier==ier2 && (GetDlgCtrlID(child2)==id || id==0))
								if (x==0 && y==0){
									return child2;
								} else {
									::GetWindowRect(child2, &rec);
									l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
										+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
		//CString deb; deb.Format("l_2=%d child=%x ",l_2, child); trif.RecordLog(deb);
									if (l_2<l_2_old || l_2_old==0){
										l_2_old=l_2;
										child_cen=child2;
										if (l_2_old==0) return child_cen;
									}
								}
						}
						child=GetNextWindow(child, GW_HWNDPREV);
					}
					child=GetNextWindow(hw, GW_HWNDNEXT);
					while (child){
						if (hw==GetParent(child)){
							child2=Findhwnd(child, CapChi, Slice, ForClassname, 1);
							if (child2 && i_ier==ier2 && (GetDlgCtrlID(child2)==id || id==0))
								if (x==0 && y==0){
									return child2;
								} else {
									::GetWindowRect(child2, &rec);
									l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
										+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
		//CString deb; deb.Format("l_2=%d child=%x",l_2, child); trif.RecordLog(deb);
									if (l_2<l_2_old || l_2_old==0){
										l_2_old=l_2;
										child_cen=child2;
									}
								}
						}
						child=GetNextWindow(child, GW_HWNDNEXT);
					}
		//CString deb; deb.Format("4 return child_cen l_2=%d child=%x ",l_2, child_cen); trif.RecordLog(deb);
					return child_cen;
				}
				par=child;
				child = GetNextWindow(par, GW_HWNDNEXT);
				if (child)
					par=child;
			}
		}
	}
	if (child)
	if (!ForClassname){
		GetWindowText(child, wintext, GetWindowTextLength(child)+1);
		if (wintext==CapChi && i_ier==ier2 && (GetDlgCtrlID(child)==id || id==0)){
			if (x==0 && y==0){
				return child;
			} else {
				::GetWindowRect(child, &rec);
				l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
					+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
	//CString deb; deb.Format("l_2=%d child=%x",l_2, child); trif.RecordLog(deb);
				if (l_2<l_2_old || l_2_old==0){
					l_2_old=l_2;
					child_cen=child;
					if (l_2_old==0) return child_cen;
				}
			}
		}
		capt=wintext;
		if (Slice)
			if (capt.Find(CapChi, 0)>-1 && i_ier==ier2 && 
				(GetDlgCtrlID(child)==id || id==0)){
				if (x==0 && y==0){
					return child;
				} else {
					::GetWindowRect(child, &rec);
					l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
						+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
	//CString deb; deb.Format("l_2=%d child=%x",l_2, child); trif.RecordLog(deb);
					if (l_2<l_2_old || l_2_old==0){
						l_2_old=l_2;
						child_cen=child;
						if (l_2_old==0) return child_cen;
					}
				}
			}
	} else {
		GetClassName(child, wintext, 100);
		if (wintext==ClaChi && i_ier==ier2 && (GetDlgCtrlID(child)==id || id==0)){
			if (x==0 && y==0){
				return child;
			} else {
				::GetWindowRect(child, &rec);
				l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
					+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
	//CString deb; deb.Format("l_2=%d child=%x",l_2, child); trif.RecordLog(deb);
				if (l_2<l_2_old || l_2_old==0){
					l_2_old=l_2;
					child_cen=child;
					if (l_2_old==0) return child_cen;
				}
			}
		}
	}
		//CString deb; deb.Format("return return child_cen l_2=%d child=%x ",l_2, child); trif.RecordLog(deb);
	if (x==0 && y==0){
		return child;
	} else {
		return child_cen;
	}
}

//если prover=false, то окно не проверяется на совпадение имени кл. и им. окна
HWND CWinWork::FindhwndIerar(HWND hw, CString ier, CString ClName,
		CString Capt, bool prover, bool debu)
{
	HWND child;
	char wintext[512];
	CString capt;
	int colprohod;
	child=hw;
	if (ier.Find("((")==0)
		ier.Delete(0, 2);
	else return 0; 
	while (ier!=""){
		if (ier[0]=='N'){
			ier.Delete(0,1);
			colprohod=atoi(ier);
			if (colprohod>0)
				for (int ii=0; ii<colprohod; ii++)
					child=GetNextWindow(child, GW_HWNDPREV);
				if (!child) return 0;
		} else {
			colprohod=atoi(ier);
			if ((colprohod>0)||(ier[0]=='0'))
			{
				child=GetWindow(child, GW_CHILD);
				
				#ifdef LOG 
				if (debu) {	char deb[1024]; sprintf(deb, "child= %X", child); trif.RecordLog(deb);  }
				#endif
				for (int ii=1; ii<=colprohod; ii++)
				{
					child=GetNextWindow(child, GW_HWNDNEXT);				
					#ifdef LOG 
					if (debu){ char deb[1024]; sprintf(deb, "child= %X", child); trif.RecordLog(deb); }	
					#endif
				}
				if (!child)
				{			
					#ifdef LOG 
					if (debu){	char deb[1024]; sprintf(deb, "child= %X", child); trif.RecordLog(deb);	}
					#endif
					return 0;
				}
			}
		}
		if (ier.Find(':')>-1)
			ier.Delete(0, ier.Find(':')+1);
		else {
			ier="";
			break;
		}
	}
	if (!prover) return child;
	GetWindowText(child, wintext, 512);
	capt=wintext;
// 	if (SliceCapt)
// 	{//если кусочный поиск заголовка, то разр. не обр. внимания на пустой заголовок
// 		if (capt.Find(Capt)==-1 && !Capt.IsEmpty()) return 0;
// 	} else 
		if (capt!=Capt) return 0;
	GetClassName(child, wintext, 100);
	if (ClName!=wintext) return 0;
	else return child;
	return child;
}

//заполнение структуры для контроля окна запущенного приложения
void CWinWork::AddToExeStruct(CString exe, DWORD pid)
{
	int si=sApp.GetSize();
	sApp.SetSize(si+1);
	sApp[si].dwProcessId=pid;
	sApp[si].exe_Name=exe;
}

//извлечение pid по экзешнику
DWORD CWinWork::GetPidFromExeStruct(CString exe)
{
	if (sApp.GetSize()>0){
		for (int ex=0; ex<sApp.GetSize(); ex++)
		{
			if (sApp[ex].exe_Name==exe)
				return sApp[ex].dwProcessId;
		}
	}
	return 0;
}

//pid - идентификатор процесса, который мог быть запущен через CreateProcess
HWND CWinWork::FindMainWindow(CString csMainWindowCapt, BOOL Slice, CString ClasName, 
							  int x, int y, DWORD pid)
{
	HWND MainHw=::FindWindow(ClasName, csMainWindowCapt);
	if (pid!=0){
		DWORD pid2;
		DWORD dw=GetWindowThreadProcessId(MainHw, &pid2);
		if (dw!=NULL && pid2==pid){
			#ifdef LOG 
trif.RecordLog("pid==pid2 return MainHw");  
#endif
			return MainHw;
		}
	}
	HWND main_cen=0;//сюда будет запоминаться окно более близкое по центру
	CRect rec; int l_2=0, l_2_old=0;
	if ( (!MainHw && Slice )|| (x!=0 || y!=0))
	{
		HWND cur;
		//char cap[512];
		CString Capt;
		cur=::GetWindow(::GetDesktopWindow(), GW_CHILD);
		if (pid!=0){
			DWORD pid2;
			DWORD dw=GetWindowThreadProcessId(cur, &pid2);
			if (dw!=NULL && pid2==pid){
				#ifdef LOG 
trif.RecordLog("pid==pid2 return cur");  
#endif
				return cur;
			}
		}
		while (cur)
		{
			::GetWindowText(cur, Capt.GetBuffer(1024), 1024);
			//CString deb; deb.Format("while cur=%x capt=%s class=%s", cur, Capt, trif.MyGetClassName(cur)); trif.RecordLog(deb);
			if (Capt.Find(csMainWindowCapt)>-1){
				if (ClasName.GetLength()>10){
					if (trif.MyGetClassName(cur).Find(ClasName.Left(ClasName.GetLength()/2))>-1){
						if (x==0 && y==0 && pid==0){
							return cur;
						} else {
							::GetWindowRect(cur, &rec);
							l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
								+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
							#ifdef LOG 
char deb[1024]; sprintf(deb, "l_2=%d cur=%x",l_2, cur); trif.RecordLog(deb);  
#endif
							if (l_2<l_2_old || l_2_old==0){
								l_2_old=l_2;
								main_cen=cur;
								if (l_2_old==0 && pid==0) return main_cen;
							}
						}
					}
				}
				if (ClasName.GetLength()==0){
					if (x==0 && y==0 && pid==0){
						return cur;
					} else {
						::GetWindowRect(cur, &rec);
						l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
							+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
						#ifdef LOG 
char deb[1024]; sprintf(deb, "l_2=%d cur=%x",l_2, cur); trif.RecordLog(deb);  
#endif
						if (l_2<l_2_old || l_2_old==0){
							l_2_old=l_2;
							main_cen=cur;
							if (l_2_old==0 && pid==0) return main_cen;
						}
					}
				}
				if (trif.MyGetClassName(cur)==ClasName){
					if (x==0 && y==0 && pid==0){
						return cur;
					} else {
						::GetWindowRect(cur, &rec);
						l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
							+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
						#ifdef LOG 
char deb[1024]; sprintf(deb, "l_2=%d cur=%x",l_2, cur); trif.RecordLog(deb);  
#endif
						if (l_2<l_2_old || l_2_old==0){
							l_2_old=l_2;
							main_cen=cur;
							if (l_2_old==0 && pid==0) return main_cen;
						}
					}
				}
			}
			cur=::GetWindow(cur, GW_HWNDNEXT);
			if (pid!=0){
				DWORD pid2;
				DWORD dw=GetWindowThreadProcessId(cur, &pid2);
				if (dw!=NULL && pid2==pid){
					#ifdef LOG 
trif.RecordLog("pid==pid2 return cur");  
#endif
					return cur;
				}
			}
		}
	} else {
		if (pid==0)
		{
			#ifdef LOG 
trif.RecordLog("return FindMainWindow : pid==0");  
#endif
			return MainHw;
		}
	}
	if ((x!=0 || y!=0) && main_cen){
		if (pid==0)
		{
			#ifdef LOG 
trif.RecordLog("return main_cen");  
#endif
			return main_cen;
		}
	}
	#ifdef LOG 
trif.RecordLog("FindMainWindow - ничего не нашли");  
#endif
	return 0;
}

//поиск главного окна (в окнах верхнего уровня ищется окно по куску заголовка)
HWND CWinWork::FindMainWindow2(CString csMainWindowCapt, BOOL Slice, CString ClasName)
{
	HWND MainHw=::FindWindow(ClasName, csMainWindowCapt);
	if ((!MainHw)&&(Slice))
	{
		HWND cur;
		char cap[512];
		CString Capt;
		cur=::GetDesktopWindow();
		cur=::GetWindow(cur, GW_CHILD);
		while (cur)
		{
			::GetWindowText(cur, cap, 512);
			Capt=cap;
			if (Capt.Find(csMainWindowCapt)>-1)
				return cur;
			cur=::GetWindow(cur, GW_HWNDNEXT);
		}
	} else {
		return MainHw;
	}
	return 0;
}
//поиск окна AutoClickExtreme (в окнах верхнего уровня ищется окно по куску заголовка)
HWND CWinWork::FindMainWindow3(CString csMainWindowCapt, BOOL Slice, CString ClasName)
{
	HWND MainHw=::FindWindow(ClasName, csMainWindowCapt);
	if ((!MainHw)&&(Slice))
	{
		HWND cur;
		char cap[512];
		CString Capt;
		cur=::GetDesktopWindow();
		cur=::GetWindow(cur, GW_CHILD);
		while (cur)
		{
			::GetWindowText(cur, cap, 512);
			Capt=cap;
			if (Capt.Find(csMainWindowCapt)==0)
			{
				::GetClassName(cur, cap, 512);
				if (strcmp(cap, "#32770")==0)
				{
					return cur;
				}
			}
			cur=::GetWindow(cur, GW_HWNDNEXT);
		}
	} else {
		return MainHw;
	}
	return 0;
}
//установка главного окна на передний план
//without_execute - установка без исключений, как в случае работы с рабочим столом
BOOL CWinWork::MySetForegroundWindow(HWND par, bool without_execute)
{
	if (rabTable && !without_execute)
	{
		#ifdef LOG 
		trif.RecordLog("экстренный выход из MySetForegroundWindow");  
		#endif
		return true;
	}
	#ifdef LOG 
	char deb[1024]; sprintf(deb, "MySetForegroundWindow=%x class2=%s", par, trif.MyGetClassName(par)); trif.RecordLog(deb);  
	#endif
	return trif.BringWindowToForeground(par);
}

int lim_bals_deb=400;
bool deb_podt=false;//после сообщения о добавлении баллов разрешаем 
//поясняющее сообщение о причине добавления
void CWinWork::ChiBalsAdd(HWND hw_main, HWND hw_chi, int bals)
{
	for (int ii=0; ii<chi_hw_reits.GetSize(); ii++)
	{
		if (chi_hw_reits[ii].main_hw==hw_main && 
			chi_hw_reits[ii].chi_hw==hw_chi) 
		{
			chi_hw_reits[ii].bals=chi_hw_reits[ii].bals+bals;
			if (bals>lim_bals_deb)
			{
				deb_podt=1;
#ifdef LOG 
	char deb[1024]; sprintf(deb, "даем дочернему %x родителя %x +%d баллов, теперь=%d", hw_chi, hw_main, bals, chi_hw_reits[ii].bals);	trif.RecordLog(deb);  
#endif
			}
			return;
		}
	}
	int ind=chi_hw_reits.GetSize();
	chi_hw_reits.SetSize(ind+1);
	chi_hw_reits[ind].main_hw=hw_main;
	chi_hw_reits[ind].chi_hw=hw_chi;
	chi_hw_reits[ind].bals=bals;
	if (bals>lim_bals_deb){
		deb_podt=1;
		#ifdef LOG 
		char deb[1024]; sprintf(deb, "даем дочернему %x родителя %x +%d баллов, теперь=%d", hw_chi, hw_main, bals, chi_hw_reits[ind].bals);	trif.RecordLog(deb);  
		#endif
	}
}
int CWinWork::GetBalsFrom(HWND hw, bool &norm_capt)
{
	for (int ii=0; ii<mai_hw_reits.GetSize(); ii++)
	{
		if (mai_hw_reits[ii].hw==hw) 
		{
			norm_capt=mai_hw_reits[ii].norm_capt;
			return mai_hw_reits[ii].bals;
		}
	}
	norm_capt=false;
	return 0;
}
void CWinWork::BalsAdd(HWND hw, int bals, bool norm_capt)
{
	for (int ii=0; ii<mai_hw_reits.GetSize(); ii++)
	{
		if (mai_hw_reits[ii].hw==hw) 
		{
			mai_hw_reits[ii].bals=mai_hw_reits[ii].bals+bals;
			if (norm_capt)
				mai_hw_reits[ii].norm_capt=true;
			if (bals>lim_bals_deb || hw==(HWND)0x40378)
			{
				deb_podt=1;
#ifdef LOG 
char deb[1024];sprintf(deb, "даем %x +%d баллов, теперь=%d", hw, bals, mai_hw_reits[ii].bals);	trif.RecordLog(deb); 
#endif
			}
			return;
		}
	}
	int ind=mai_hw_reits.GetSize();
	mai_hw_reits.SetSize(ind+1);
	mai_hw_reits[ind].hw=hw;
	mai_hw_reits[ind].bals=bals;
	mai_hw_reits[ind].norm_capt=norm_capt;
	if (bals>lim_bals_deb)
	{
		deb_podt=1;
		#ifdef LOG 
		char deb[1024]; sprintf(deb, "даем %x +%d баллов, теперь=%d", hw, bals, mai_hw_reits[ind].bals);	trif.RecordLog(deb);  
		#endif
	}
}
//поиск родительского и дочернего окна
//если не найдено гл. окно возвращается 2
//  дочернее - 1
//  все найдены - 0
//bool test - поиск ведем в тестовом режиме, чтобы показать 
//пользователю за что и какому окну сколько балов начислено
int CWinWork::SearchWindows(Acti& MyAct, int tt, 
	int bals_lim, int chi_lim, bool correct_capt, 
	HWND mai/*=0*/, bool test/*=false*/)
{

	#ifdef LOG 
	CUIntArray tormoz;
	tormoz.Add(0);
	tormoz.Add(0);
	tormoz.Add(0);
	tormoz.Add(0);
	UINT oldtick=GetTickCount();
	UINT oldtick2=GetTickCount();
	#endif

	CStringArray tstWins;
	mai_hwnd_Array tstHwnds;
	CUIntArray tstBals;
	//таблица соответствия для экзешников
	static UINT last_time_tab=GetTickCount();
	if (GetTickCount()-last_time_tab>600000)
	{
		hw_exe.RemoveAll();
		sa_exe.RemoveAll();
		last_time_tab=GetTickCount();
	}
	mai_hw_reits.RemoveAll();
	if (mai)
	{
		BalsAdd(mai, 100, 1);
// 		if (test)
// 		{
// 			int exist=-1;
// 			for (int tst=0; tst<tstHwnds.GetSize(); tst++)
// 			{
// 				if (mai==tstHwnds[tst])
// 				{
// 					exist=tst;
// 					break;
//				}
// 			}
// 			if (exist==-1)
// 			{
// 				exist=tstHwnds.Add(mai);
// 				tstWins.Add();
// 			}
// 		}
	} else {

		//разрешаем дальнейший поиск по экзешнику
		if (!MyAct[tt].W.Mai.bSearExe && MyAct[tt].W.Mai.bHowCha!=1 && MyAct[tt].W.Mai.bHowCha!=4 && !correct_capt)
		{
			#ifdef LOG 
			trif.RecordLog("разрешаем в дальнейшем поиск по экзешнику Appdlg->SaveEnable(true)");  
			#endif
			AfxGetMainWnd()->SendMessage(WM_USER32, 40, tt);//saRecChanges.Add(recChange);
			AfxGetMainWnd()->SendMessage(WM_USER32, 31);//SaveEnable(true);
			MyAct[tt].W.Mai.bSearExe=true;
		}
		//если поиск по экзешнику разрешен то увеличиваем прибавку баллов
		int ExeAdd=20;
		if (MyAct[tt].W.Mai.bSearExe)
			ExeAdd=20+25;

		bool capt_normal=false;
		HWND next=0;
		CString str2, str1;
		while (next=GetNextMainWin(next))
		{
			#ifdef LOG
			bool debb=false;
 			if (next==(HWND)0x5a1502)
 				next=next;
			CString chdeb;
			::GetClassName(next, chdeb.GetBuffer(20), 20);
			if (chdeb=="#32768")
			{
//				::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USER+31, 1, 0);
				debb=true;
			}
			oldtick=::GetCurrentTime();
			#endif
			capt_normal=false;
			str1=MyAct[tt].W.Name_exe;
			int fir=str1.ReverseFind('\\');
			if (fir==-1)
			{
				fir=str1.ReverseFind('/');
			}
			if (fir!=-1)
			{
				str1=str1.Right(str1.GetLength()-fir-1);
			}
			str1.MakeLower();
			#ifdef LOG 
			tormoz[0]+=::GetCurrentTime()-oldtick;
			oldtick=::GetCurrentTime();
			#endif
			//ищем в имеющемся массиве exe и хэндлов нужный нам exe
			bool exist=false;
			for (int ii=0; ii<hw_exe.GetSize(); ii++)
			{//**** отладчик показывает размер массива 613
				if (hw_exe[ii]==next)
				{
					exist=true;
					str2=sa_exe[ii];
					break;
				}
			}
			if (!exist)
			{
				str2=cpu.GetAppNameFromHandle2(next).c_str();
				fir=str2.ReverseFind('\\');
				if (fir==-1)
				{
					fir=str2.ReverseFind('/');
				}
				if (fir!=-1)
				{
					str2=str2.Right(str2.GetLength()-fir-1);
				} else {
					if (str2.Find("\\??\\")==0)
						str2.Delete(0, 4);
				}
				str2.MakeLower();
				//добавляем соответствие exe окну в массив
				int ind=hw_exe.GetSize();
				hw_exe.SetSize(ind+1);
				sa_exe.SetSize(ind+1);
				hw_exe[ind]=next;
				sa_exe[ind]=str2;
			}
			if (str2==str1)
			{
				if (MyAct[tt].W.Mai.bSearExe)
					capt_normal=true;//если разрешен поиск по экзешнику, 
					//то его нахождение приравнивается к нахождению окна 
					//с правильным заголовком
				BalsAdd(next, ExeAdd, capt_normal);
				if (deb_podt)
				{
					#ifdef LOG 
					trif.RecordLog("Правильный экзешник у окна="+MyAct[tt].W.Name_exe);  
					#endif
					deb_podt=0;
				}
			}
			#ifdef LOG 
			tormoz[1]+=::GetCurrentTime()-oldtick;
			oldtick=::GetCurrentTime();
			#endif

			CString real_capt;
			CString real_clas;
			int leng_capt=GetWindowTextLength(next);
			if (leng_capt)
				GetWindowText(next, real_capt.GetBuffer(leng_capt+1), leng_capt+1);
			else (real_capt="");
			
			GetClassName(next, real_clas.GetBuffer(1024), 1024);
// 			if (debb)
// 				debb=debb;
			CString fi_capt=MyAct[tt].W.Mai.csWinCapt;
			CString fi_clas=MyAct[tt].W.Mai.csClaName;
			if (fi_capt.GetLength()>5 && fi_capt==real_capt)
			{
				capt_normal=true;
				BalsAdd(next, fi_capt.GetLength()+15, true); 
				if (deb_podt)
				{
					#ifdef LOG 
					trif.RecordLog("заголовок полностью подходит");  
					#endif
					deb_podt=0;
				}
			} else {
				if (fi_capt.GetLength()<=5 && fi_capt==real_capt)
				{
					capt_normal=true;
					BalsAdd(next, fi_capt.GetLength()+15, true); 
					if (deb_podt){
						#ifdef LOG 
						trif.RecordLog("заголовок длиной меньше 5 символов полностью подходит");  
						#endif
						deb_podt=0;
					}
				} else
				if (fi_capt.GetLength()>5 && MyAct[tt].W.Mai.bHowCha!=1 && MyAct[tt].W.Mai.bHowCha!=4
					|| (fi_capt.GetLength()>5 && MyAct[tt].W.Mai.bHowCha==4 && !correct_capt))
				{	//ИЩЕМ ЗАГОЛОВОК СЛЕВА
					bool finded=false;
					bool isSmislFind=1;//есть ли смысл обрезать или может сразу не будет искаться
					if (real_capt.Find(fi_capt.Left(5))==-1)
						isSmislFind=false;
					
					while (fi_capt.GetLength()>5 && isSmislFind)
					{
						fi_capt.Delete(fi_capt.GetLength()-1);
						if (real_capt.Find(fi_capt)>-1)
						{
							capt_normal=true;
							BalsAdd(next, fi_capt.GetLength(), true);
							if (deb_podt){
								#ifdef LOG 
								trif.RecordLog("заголовок СЛЕВА подходит");  
								#endif
								deb_podt=0;
							}
							finded=true;
							break;
						}
					}
					if (!finded && MyAct[tt].W.Mai.bHowCha>=2 && MyAct[tt].W.Mai.bHowCha!=4)
					{
						//ИЩЕМ ЗАГОЛОВОК СПРАВА
						if (real_capt.Find(fi_capt.Right(5))==-1)
						{
							isSmislFind=false;
						} else {isSmislFind=1;}
						while (fi_capt.GetLength()>5 && isSmislFind)
						{
							capt_normal=true;
							fi_capt.Delete(0);
							if (real_capt.Find(fi_capt)>-1)
							{
								BalsAdd(next, fi_capt.GetLength()-2, true);
								if (deb_podt)
								{
									#ifdef LOG 
									trif.RecordLog("заголовок СПРАВА подходит");  
									#endif
									deb_podt=0;
								}
								finded=true;
								break;
							}
						}
					}
				}
				//int debii=MyAct[tt].W.Mai.bHowCha;
			}
			if (fi_clas.GetLength()>0)
			{
				if (fi_clas==real_clas)
				{
					BalsAdd(next, 2*fi_clas.GetLength());
					if (deb_podt){
						#ifdef LOG 
						trif.RecordLog("имя класса родителя совпадает");  
						#endif
						deb_podt=0;
					}
				} else {
					if (fi_clas.GetLength()>5)
					{
						bool finded=false;
						bool isSmislFind=1;//есть ли смысл обрезать или может сразу не будет искаться
						if (real_clas.Find(fi_clas.Left(5))==-1)
							isSmislFind=false;
						//изменяем имя класса справа
						while (isSmislFind && fi_clas.GetLength()>5)
						{
							fi_clas.Delete(fi_clas.GetLength()-1);
							if (real_clas.Find(fi_clas)>-1)
							{
								capt_normal=true;
								BalsAdd(next, fi_clas.GetLength(), true);
								if (deb_podt)
								{
									#ifdef LOG 
									trif.RecordLog("имя класса справа подходит");  
									#endif
									deb_podt=0;
								}
								finded=true;
								break;
							}
						}
						if (!finded)
						{
							if (real_clas.Find(fi_clas.Right(5))==-1)
							{
								isSmislFind=false;
							} else {isSmislFind=1;}
							//изменяем имя класса слева
							while (fi_clas.GetLength()>5 && isSmislFind)
							{
								capt_normal=true;
								fi_clas.Delete(0);
								if (real_clas.Find(fi_clas)>-1)
								{
									BalsAdd(next, fi_clas.GetLength()-2, true);
									if (deb_podt)
									{
										#ifdef LOG 
										trif.RecordLog("имя класса слева подходит");  
										#endif
										deb_podt=0;
									}
									finded=true;
									break;
								}
							}
						}
					}
				}
			}
			//в районе квадрата 300 на 300 пикселей награждаем окна баллами
			CRect rec;
			::GetWindowRect(next, &rec);
			int x=(MyAct[tt].W.saWindows.Main_r+MyAct[tt].W.saWindows.Main_l)/2;
			int y=(MyAct[tt].W.saWindows.Main_b+MyAct[tt].W.saWindows.Main_t)/2;
			//квадрат гипотенузы
			int l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
				+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
			//10 баллов максимум за близость к центру окна
			int bals=(int)(90000-l_2)/18000;
			if (bals>0){
				BalsAdd(next, bals);
				if (deb_podt){
					//sprintf(deb, "l_2=%d (90000-l_2)=%d", l_2, (90000-l_2));
					//trif.RecordLog(deb);
					#ifdef LOG 
					trif.RecordLog("близость к центру координат границ родителя");  
					#endif
					deb_podt=0;
				}
			}
		}
	}
//	HWND chi;
	chi_hw_reits.RemoveAll();
	if (MyAct[tt].W.Chi.ierarh!="((_))")
	{
// 		#ifdef LOG 
// 		char deb[1024]; sprintf(deb, "ищем дочернее, родителей = %d", mai_hw_reits.GetSize());	trif.RecordLog(deb);  
// 		#endif
		for (int ii=0; ii<mai_hw_reits.GetSize(); ii++)
		{
			//ищем все дочерние окна с подходящим классом и 
			//потом дополнительно награждаем их баллами при 
			//совпадении других параметров
			if (mai_hw_reits[ii].hw==GetDesktopWindow())
				continue;
			HWND next=0;
 #ifdef LOG 
			HWND debhw=mai_hw_reits[ii].hw;
			if (debhw==(HWND)0x5a1502)
			{
				debhw=debhw;
				int debi=mai_hw_reits[ii].bals;
			}
#endif
			while (next=GetNextChild(mai_hw_reits[ii].hw, next))
			{
				CString wintext;
				int sum_bal=0;
				GetClassName(next, wintext.GetBuffer(1024), 1024);
				if (wintext==MyAct[tt].W.Chi.csClaName)
					sum_bal+=MyAct[tt].W.Chi.csClaName.GetLength()+4;
				else if (MyAct[tt].W.Chi.csClaName.GetLength()>4 && 
					(wintext.Find(MyAct[tt].W.Chi.csClaName.Right(4))>-1 || 
					 wintext.Find(MyAct[tt].W.Chi.csClaName.Left (4))>-1))
					sum_bal+=4;
				else if (wintext.GetLength()>4 && 
					(MyAct[tt].W.Chi.csClaName.Find(wintext.Right(4))>-1 || 
					 MyAct[tt].W.Chi.csClaName.Find(wintext.Left (4))>-1))
					sum_bal+=4;
				else continue;
// 				if (!sum_bal)
// 				{
// 					CString deb=MyAct[tt].W.Chi.csClaName;
// 					continue;
// 				}
				//GetWindowText(next, wintext, 512);
				if (wintext==MyAct[tt].W.Chi.csWinCapt)
					sum_bal+=4;
				if (GetIerar(next)==MyAct[tt].W.Chi.ierarh)
					sum_bal+=3;
				if (::GetWindowLong(next, GWL_EXSTYLE)==MyAct[tt].W.Chi.exSty)
					sum_bal+=3;
				if (::GetWindowLong(next, GWL_STYLE)==MyAct[tt].W.Chi.Styl)
					sum_bal+=3;
				if (GetDlgCtrlID(next)==MyAct[tt].W.Chi.id && MyAct[tt].W.Chi.id)
					sum_bal+=8;
				if (IsWindowEnabled(next) && MyAct[tt].W.Chi.bEnable)
					sum_bal+=4;
				if (!IsWindowEnabled(next) && !MyAct[tt].W.Chi.bEnable)
					sum_bal+=4;
				if (sum_bal>3)
				{
					CRect rec;
					::GetWindowRect(next, &rec);
					int x=(MyAct[tt].W.saWindows.Chil_r+MyAct[tt].W.saWindows.Chil_l)/2;
					int y=(MyAct[tt].W.saWindows.Chil_b+MyAct[tt].W.saWindows.Chil_t)/2;
					int l_2=((rec.right+rec.left)/2-x)*((rec.right+rec.left)/2-x)
						+((rec.bottom+rec.top)/2-y)*((rec.bottom+rec.top)/2-y);
					int bals=(int)(90000-l_2)/30000;
					if (bals<0) bals=0;
					sum_bal+=bals;
				}
				if (sum_bal)
				{
					ChiBalsAdd(mai_hw_reits[ii].hw, next, sum_bal);
				}
			}

		//сначала ищется окошко с тем же заголовком, классом, иерархией, 
		//если не находится - 
		//заголовок отбрасывается, опять не находит - гибкая иерархия

// 			chi=FindhwndIerar(mai_hw_reits[ii].hw, MyAct[tt].W.Chi.ierarh,
// 				MyAct[tt].W.Chi.csClaName, MyAct[tt].W.Chi.csWinCapt, false);
// 			if (chi)
// 			{
// 				ChiBalsAdd(mai_hw_reits[ii].hw, chi, 45);
// 				if (deb_podt){
// 					trif.RecordLog("нашли дочернее по иерархии, заголовку и классу");
// 					deb_podt=0;
// 				}
// 			}
// 			//корректировка дочернего окна (не строгий заголовок)
// 			if (!chi){
// 				chi=FindhwndIerar(mai_hw_reits[ii].hw, MyAct[tt].W.Chi.ierarh,
// 					MyAct[tt].W.Chi.csClaName, "", true);
// 				if (chi)
// 				{
// 					ChiBalsAdd(mai_hw_reits[ii].hw, chi, 40);
// 					if (deb_podt){
// 						trif.RecordLog("нашли дочернее по иерархии, нестрогому заголовку и классу");
// 						deb_podt=0;
// 					}
// 				}
// 			}
// 			//**** сделать отдельно награду за совпадение стилей в виде баллов
// 
// 		//поиск окна с самым близким центром (раньше было на последнем месте, 
// 			//но строгая иерархия может 
// 			//быть ненадежной, если на самом деле она будет гибкой 
// 			//и подставит неправильное окно
// 			//как в случае с Тотал Коммандер - подставляет по иерархии левую панель
// 			// файлов, хотя нужно найти правую
// 			HWND chiHw=FindhwndIerarEx(mai_hw_reits[ii].hw, MyAct[tt].W.Chi.ierarh,
// 				MyAct[tt].W.Chi.csWinCapt, MyAct[tt].W.Chi.csClaName, true, true
// 				, false, 0, (MyAct[tt].W.saWindows.Chil_r+MyAct[tt].W.saWindows.Chil_l)/2,
// 				(MyAct[tt].W.saWindows.Chil_b+MyAct[tt].W.saWindows.Chil_t)/2, true);
// 			if (chiHw && chiHw!=chi)
// 			{
// 				//ПОБЕЖДАЕТ ТОТ У КОГО СТИЛИ ПРАВИЛЬНЕЕ
// 				//if (MyAct[tt].W.Chi.exSty || ){
// 				//if (!chiHw) chi=chiHw;
// 				LONG ExSty1=::GetWindowLong(chi, GWL_EXSTYLE);
// 				//LONG ExSty2=::GetWindowLong(chiHw, GWL_EXSTYLE);
// 				LONG Sty1=::GetWindowLong(chi, GWL_STYLE);
// 				//LONG Sty2=::GetWindowLong(chiHw, GWL_STYLE);
// 				if ((Sty1!=MyAct[tt].W.Chi.Styl || ExSty1!=MyAct[tt].W.Chi.exSty) &&
// 					(::GetWindowLong(chiHw, GWL_STYLE)==MyAct[tt].W.Chi.Styl && 
// 					 ::GetWindowLong(chiHw, GWL_EXSTYLE)==MyAct[tt].W.Chi.exSty))
// 				{
// 					chi=chiHw;
// 					ChiBalsAdd(mai_hw_reits[ii].hw, chi, 50);
// 					if (deb_podt)
// 					{
// 						sprintf(deb, "c центром имеет более правильные стили, поэтому дочернее=%x", chi); trif.RecordLog(deb);
// 						deb_podt=0;
// 					}
// 				}
// 			}
// 			//не строгая иерархия, и пытаемся использовать идентификатор
// 			if (!chi)
// 			{
// 				chi=FindhwndIerarEx(mai_hw_reits[ii].hw, MyAct[tt].W.Chi.ierarh,
// 					MyAct[tt].W.Chi.csWinCapt, MyAct[tt].W.Chi.csClaName, true, true
// 					, false, MyAct[tt].W.Chi.id);			//когда иерархия окна меняется:
// 				if (chi)
// 				{
// 					ChiBalsAdd(mai_hw_reits[ii].hw, chi, 15);
// 					if (deb_podt){
// 						trif.RecordLog("нашли дочернее по нестрогой иерархии и идентификатору");
// 						deb_podt=0;
// 					}
// 				}
// 			}
 		}
		//когда иерархия окна меняется:
		//поиск другого родителя - помогает, при csClaName=SysListView32 и 
		//csWinCapt=FolderView
		if ((MyAct[tt].W.Chi.csClaName.GetLength()>9 ||
			MyAct[tt].W.Chi.csWinCapt.GetLength()>11) && 
			MyAct[tt].W.Chi.csClaName=="SysListView32")
		{
			HWND desk=::GetDesktopWindow();
			desk=::GetWindow(desk, GW_CHILD);
			while (desk)
			{
				HWND hw=FindhwndIerar(desk, MyAct[tt].W.Chi.ierarh,
					MyAct[tt].W.Chi.csClaName, MyAct[tt].W.Chi.csWinCapt);
				if (hw)
				{
					//CString mes="Редкий случай";
					//Appdlg->MyAfxMessageBox(mes);
					if (MyAct[tt].W.Mai.csWinCapt!=
						trif.MyGetWindowText(desk) &&
						(MyAct[tt].W.Mai.bHowCha==1 || MyAct[tt].W.Mai.bHowCha==4)) break;
					#ifdef LOG 
					trif.RecordLog("когда иерархия окна меняется");  
					#endif
					BalsAdd(desk, 10);
					if (deb_podt)
					{
						#ifdef LOG 
						trif.RecordLog("поиск дочернего с привязкой к рабочему столу");  
						#endif
						deb_podt=0;
					}
					ChiBalsAdd(desk, hw, 15);
					if (deb_podt)
					{
						#ifdef LOG 
						char deb[1024]; sprintf(deb, "поиск дочернего с привязкой к рабочему столу=%x", hw); trif.RecordLog(deb);  
						#endif
						deb_podt=0;
					}
// 							MyAct[tt].W.Mai.csWinCapt=trif.MyGetWindowText(desk);
// 							MyAct[tt].W.Mai.csClaName=trif.MyGetClassName(desk);
					break;
				}
				desk=::GetWindow(desk, GW_HWNDNEXT);
			}
		}
	}
	int Mult=0; int sum_i=-1;
	if (MyAct[tt].W.Chi.ierarh=="((_))")
	{
// 		#ifdef LOG 
// 		char deb[1024]; sprintf(deb, "выбор окна с высоким баллом bals_lim=%d проверка правильности заголовка= %d", bals_lim, correct_capt);	trif.RecordLog(deb); 
// 		#endif
		for (int ii=0; ii<mai_hw_reits.GetSize(); ii++)
		{
 			#ifdef LOG 
			int debi=mai_hw_reits[ii].bals;
			HWND debhw=mai_hw_reits[ii].hw;
			debhw=debhw;
//			char deb[1024];
// 			sprintf(deb, "перебор найденных окон (%d): %x = %d баллов правильный заголовок=%d", ii, mai_hw_reits[ii].hw, mai_hw_reits[ii].bals, mai_hw_reits[ii].norm_capt);	trif.RecordLog(deb); 
 			#endif
			if (mai_hw_reits[ii].bals>bals_lim)
			{ 
				int tmp=mai_hw_reits[ii].bals;
				bool podhodit=true;
				if (correct_capt && !mai_hw_reits[ii].norm_capt)
					podhodit=false;
				if (tmp>Mult && podhodit)
				{
					Mult=tmp;
					sum_i=ii;
				}
			}
		}
		if (Mult)
		{
			MyAct[tt].W.Mai.hwnd=mai_hw_reits[sum_i].hw;
			MyAct[tt].W.Chi.hwnd=mai_hw_reits[sum_i].hw;
			#ifdef LOG 
			char deb[1024]; sprintf(deb, "макс. баллов (%d) набрал родитель=дочернее=%x", mai_hw_reits[sum_i].bals, mai_hw_reits[sum_i].hw);	trif.RecordLog(deb); 
//			sprintf(deb, "tormoz[0]=%d tormoz[1]=%d общее время=%d", tormoz[0], tormoz[1], (GetTickCount()-oldtick2)); trif.RecordLog(deb);
			#endif
			return 0;
		} else {
			if (sum_i==-1) return 1;
			if (mai_hw_reits[sum_i].bals<10) 
				return 1;
			else return 2;
		}
	} else {
// 		#ifdef LOG 
// 		char deb[1024]; sprintf(deb, "выбор окна с высоким баллом bals_lim=%d chi_lim=%d проверка правильности заголовка= %d", bals_lim, chi_lim, correct_capt);	trif.RecordLog(deb); 
// 		#endif
		for (int ii=0; ii<chi_hw_reits.GetSize(); ii++)
		{
			bool bnorm_capt;
			//HWND debhx=chi_hw_reits[ii].main_hw;
			int Main_bals=GetBalsFrom(chi_hw_reits[ii].main_hw, bnorm_capt);
// 			#ifdef LOG 
// 			sprintf(deb, "перебор найденных окон (%d): %x = %d баллов доч. %x=%d правильный заголовок=%d", ii, chi_hw_reits[ii].main_hw, Main_bals, chi_hw_reits[ii].chi_hw, chi_hw_reits[ii].bals, bnorm_capt);	trif.RecordLog(deb); 
// 			#endif
			bool podhodit=true;
			HWND debhw=(HWND)chi_hw_reits[ii].main_hw;
			if (correct_capt && !bnorm_capt)
				podhodit=false;
			if (Main_bals>=bals_lim && 
				chi_hw_reits[ii].bals>=chi_lim && podhodit)
			{
				int tmp=Main_bals*chi_hw_reits[ii].bals;
				if (tmp>Mult)
				{
					Mult=tmp;
					sum_i=ii;
				}
			}
		}
		if (Mult)
		{
			MyAct[tt].W.Mai.hwnd=chi_hw_reits[sum_i].main_hw;
			MyAct[tt].W.Chi.hwnd=chi_hw_reits[sum_i].chi_hw;
			#ifdef LOG 
//			char deb[1024]; sprintf(deb, "tormoz[0]=%d tormoz[1]=%d общее время=%d", tormoz[0], tormoz[1], (GetTickCount()-oldtick2)); trif.RecordLog(deb);
			#endif
			return 0;
		} else {
			if (sum_i==-1) return 1;
			bool tmp;
			if (GetBalsFrom(chi_hw_reits[sum_i].main_hw, tmp)<bals_lim) 
				return 1;
			else return 2;
		}
	}
return 1;
}

bool CWinWork::CheckQueueMouse(SendStruct* curAct, Act &waitAct, int ii)
{
#ifdef LOG 
	char deb[2048];
	sprintf(deb, "CheckQueueMouse кликнули mes=%d ждали mes=%d; номер клика в действии ii=%d", 
		(int)(curAct->message), (int)(waitAct.MK.updown[ii]), (int)(ii)); trif.RecordLog(deb);
#endif
	if (curAct->baTypeAct!=1)
	{
		return false;
	}
	//некоторое послабление для мыши при ее отжатии, 
	//(все равно слежение за шифтом и контролом идет отдельно)
	//14.06.2011 - главное, чтобы нажатие и отжатие совпадали, 
	// прицедент: в MyTimer клик по заголовку не Воспроизводился (системный клик по заголовку)
	// дальнейшее тотальное закоментирование связано с этой проблемой, т.е. все нижние случае входят сюда
	if (trif.UpOrDown((UINT)curAct->message) == trif.UpOrDown(waitAct.MK.updown[ii]))
	{
		return true;
	}

// 	if (curAct->message==WM_LBUTTONDOWN)
// 	if (curAct->message==waitAct.MK.updown[ii] &&
// 		curAct->wpar==waitAct.MK.keys[ii])
// 	{
// 		return true;
// 	}
// 	//при кликах мышью иногда в wpar записывается эта мышь, иногда нет
// 	if (trif.UpOrDown((UINT)curAct->message) == trif.UpOrDown(waitAct.MK.updown[ii]) &&
// 		curAct->wpar!=waitAct.MK.keys[ii])
// 	{
// 		UINT cwp=(UINT)curAct->wpar, mwp=waitAct.MK.keys[ii];
// 		if (curAct->message==WM_LBUTTONDOWN ||
// 			curAct->message==WM_LBUTTONDBLCLK ||
// 			curAct->message==WM_LBUTTONUP)
// 		{
// 			if (cwp>mwp) { mwp=mwp|MK_LBUTTON;} else 
// 				if (cwp<mwp) { cwp=cwp|MK_LBUTTON;}
// 				if (cwp==mwp){
// 					return true;
// 				}
// 		}
// 		if (curAct->message==WM_RBUTTONDOWN ||
// 			curAct->message==WM_RBUTTONDBLCLK ||
// 			curAct->message==WM_RBUTTONUP)
// 		{
// 			if (cwp>mwp) { mwp=mwp|MK_RBUTTON;} else 
// 				if (cwp<mwp) { cwp=cwp|MK_RBUTTON;}
// 				if (cwp==mwp){
// 					return true;
// 				}
// 		}
// 		if (curAct->message==WM_MBUTTONDOWN ||
// 			curAct->message==WM_MBUTTONDBLCLK ||
// 			curAct->message==WM_MBUTTONUP)
// 		{
// 			if (cwp>mwp) { mwp=mwp|MK_MBUTTON;} else 
// 				if (cwp<mwp) { cwp=cwp|MK_MBUTTON;}
// 				if (cwp==mwp){
// 					return true;
// 				}
// 		}
// 	}

// 	//вместо одинарного клика согласны принять и двойной
// 	if ((curAct->message==WM_LBUTTONDBLCLK 
// 		&& waitAct.MK.updown[ii]==WM_LBUTTONDOWN) ||
// 		(curAct->message==WM_RBUTTONDBLCLK 
// 		&& waitAct.MK.updown[ii]==WM_RBUTTONDOWN) ||
// 		(curAct->message==WM_MBUTTONDBLCLK 
// 		&& waitAct.MK.updown[ii]==WM_MBUTTONDOWN))
// 	{
// 		return true;
// 	} 
		
	if (!waitAct.MK.QueueWait && 
		trif.UpOrDown(waitAct.MK.updown[ii]))
	{	//проверка для действия, которого можно без ожидания очереди пропускать (в принципе такое невозможно)
		if (!HIWORD(GetKeyState(waitAct.MK.keys[ii])))
		{
			return true;
		}
	}
	return false;
}

//проверка наличия дочернего окна под курсором + возврат хэндла этого окна
bool CWinWork::CheckChildWin(CString MainWinCapt, CString MainClassName, BOOL MainHowChange, 
							 CString ChildIerarh, CString ChildWinCapt, CString ChildClassName, 
							 int xx, int yy, HWND &hwChild, bool razr_mes, HWND hwChildOrig)
{
	//trif.RecordLog("CheckChildWin - заход в функцию");//deb
	hwChild=MyWindowFromPoint(xx+MainWinPoprx+ChaiWinPoprx, 
							yy+MainWinPopry+ChaiWinPopry, razr_mes, hwChildOrig);
	if (!hwChild)
	{
		#ifdef LOG 
		trif.RecordLog("Под курсором нет окна");  
		#endif
		return false;
	}
	#ifdef LOG 
	char deb[1024]; sprintf(deb, "CheckChildWin под курсором x=%d y=%d окно %x имя класса="+trif.MyGetClassName(hwChild), xx, yy, hwChild); trif.RecordLog(deb);  
	#endif
	CString fi_clas=ChildClassName;
	CString real_clas;
	GetClassName(hwChild, real_clas.GetBuffer(1024), 1024);

	if (/*trif.MyGetWindowText(chiHW)==MyAct[tt].W.Chi.csWinCapt)&&*/
		fi_clas==real_clas)
	{
		#ifdef LOG 
		trif.RecordLog("CheckChildWin=true Имена классов под курсором совпадают");  
		#endif
		return true;
	} else {
		if (fi_clas.GetLength()>0)
		{
			if (fi_clas.GetLength()>5)
			{
				bool finded=false;
				bool isSmislFind=1;//есть ли смысл обрезать или может сразу не будет искаться
				if (real_clas.Find(fi_clas.Left(5))==-1)
					isSmislFind=false;
				//изменяем имя класса справа
				while (isSmislFind && fi_clas.GetLength()>5)
				{
					fi_clas.Delete(fi_clas.GetLength()-1);
					if (real_clas.Find(fi_clas)>-1)
					{
#ifdef LOG 
						trif.RecordLog("CheckChildWin=true Имена классов под курсором частично совпадают (справа)");  
#endif
						return true;
					}
				}
				if (!finded)
				{
					if (real_clas.Find(fi_clas.Right(5))==-1)
					{
						isSmislFind=false;
					} else {
						isSmislFind=1;
					}
					//изменяем имя класса слева
					while (fi_clas.GetLength()>5 && isSmislFind)
					{
						fi_clas.Delete(0);
						if (real_clas.Find(fi_clas)>-1)
						{
#ifdef LOG 
							trif.RecordLog("CheckChildWin=true Имена классов под курсором частично совпадают (слева)");  
#endif
							return true;
						}
					}
				}
			}
		}
	}
	if (MainHowChange==2)
	{
		if ((trif.MyGetWindowText(hwChild).Find(ChildWinCapt)>-1)&&
			(trif.MyGetClassName(hwChild)==ChildClassName))
		{
			#ifdef LOG 
			trif.RecordLog("CheckChildWin=true Имена классов под курсором совпадают + кусок заголовка совпадает");  
			#endif
			return true;
		}
		if (ChildIerarh=="((_))")
			if ((trif.MyGetWindowText(hwChild).Find(MainWinCapt)>-1)&&
				(trif.MyGetClassName(hwChild)==MainClassName))
			{
				#ifdef LOG 
				trif.RecordLog("CheckChildWin=true Имена классов под курсором совпадают + кусок заголовка совпадает (родитель=дочь)");  
				#endif
				return true;
			}
	}
	#ifdef LOG 
	trif.RecordLog("CheckChildWin=false (не то под курсором)!");  
	#endif
	return false;
}

bool CWinWork::isMenu(CString str)
{
	if (str=="#32768")
		return true;
	return false;
}

//установка родительского окна в старое положение
BOOL CWinWork::SetParentPosit(HWND hwMain, CString MainClassName, 
							  int Main_l, int Main_t, int Main_r, int Main_b, 
							  bool razr_dvig, int xx, int yy)
{
	if (!hwMain)
		return false;
	BOOL bo=false;
	if (razr_dvig && !isMenu(MainClassName))
	{
		bo=::MoveWindow(hwMain, Main_l, Main_t,
			Main_r-Main_l,
			Main_b-Main_t, true);
		#ifdef LOG 
		char deb[1024]; sprintf(deb, "SetParentPosit MoveWindow=%d", bo); trif.RecordLog(deb);  
		#endif
	}		
	CRect crWin;
	int bo2;
	bo2=::GetWindowRect(hwMain, &crWin);
		#ifdef LOG 
			char deb[1024]; sprintf(deb, "SetParentPosit GetWindowRect(%x) crWin.left=%d старое.left=%d glob_popravx=%d", hwMain, crWin.left, Main_l, MainWinPoprx); trif.RecordLog(deb);  
		#endif
	int poprav1=crWin.left-(Main_l+MainWinPoprx);
	int poprav2=crWin.top -(Main_t+MainWinPopry);
	if (bo2)
	{
		//проверка нахождения в рамке данного окна с пом. GetPar(getwindowfrompoint)
		int xx1=xx+poprav1, 
			yy1=yy+poprav2,
			//xx2=crWin.left + (crWin.right-crWin.left)/2,
			//yy2=crWin.top + (crWin.bottom-crWin.top)/2;
			xx2=crWin.right-1,
			yy2=crWin.bottom-1;
		if (GetPar(::WindowFromPoint(CPoint(xx2, 
			yy2)))!=hwMain && MyWindowFromPoint(xx1, 
			yy1, false, hwMain)!=hwMain)
		{
			if (crWin.left==Main_l)
			if (crWin.top==Main_t)
			if (crWin.bottom==Main_b)
			if (crWin.right==Main_r)
				return true;
			#ifdef LOG 
			char deb[1024]; sprintf(deb, "!!! SetParentPosit курсор мыши не будет попадать в новое место родительского окна новое.верх=%d лево=%d низ=%d старое.верх=%d низ=%d окно под новым местом=%x требуемое окно=%x MyWindowFromPoint=%x координаты нового клика x=%d y=%d старого клика x=%d y=%d", 
				crWin.top, crWin.left, crWin.bottom, Main_t, Main_b, GetPar(::WindowFromPoint(CPoint(crWin.left+1, crWin.top+1))), hwMain, MyWindowFromPoint(xx1, yy1, false, hwMain), xx1, yy1, xx, yy); trif.RecordLog(deb);  
			#endif

			//запись в лог
			//****
// 				sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d !!! SetParentPosit курсор мыши не будет попадать в новое место родительского окна новое.верх=%d лево=%d низ=%d старое.верх=%d низ=%d окно под новым местом=%x требуемое окно=%x MyWindowFromPoint=%x координаты нового клика x=%d y=%d старого клика x=%d y=%d\n", 
// 					(GetTickCount()-Appdlg->CurRec.LastLog), crWin.top, crWin.left, crWin.bottom, Main_t, Main_b, GetPar(::WindowFromPoint(CPoint(crWin.left+1, crWin.top+1))), hwMain, MyWindowFromPoint(xx1, yy1, false, hwMain), xx1, yy1, MyAct[tt].MOUS.xx[0], MyAct[tt].MOUS.yy[0]);
// 				Appdlg->CurRec.LastLog=GetTickCount();
// 				Appdlg->CurRec.indl++;
// 				if (Appdlg->CurRec.indl>90)
// 					Appdlg->CurRec.SaveLogz();
			return false;
		}
		if ( ( (poprav1!=0 || poprav2!=0) && 
			//чтобы новая координата клика не была отрицательной
			xx+poprav1>0 &&
			//и чтобы вписывалась в границы смещенного окна
			xx+poprav1<=crWin.right &&
			xx+poprav1>=crWin.left ) && 
			//чтобы новая координата клика не была отрицательной
			(yy+poprav2>0 &&
			//и чтобы вписывалась в границы смещенного окна
			yy+poprav2<=crWin.bottom &&
			yy+poprav2>=crWin.top))
		{
// 				arCorMousPos_mesx.Add(tt);//резервируем данные
// 				arCorMousPos_mesx.Add(xx[0]);
// 				arCorMousBoundLR.Add(Chil_l);
// 				arCorMousBoundLR.Add(Chil_r);
// 				arMainBoundLR.Add(tt);
// 				arMainBoundLR.Add(Main_l);
// 				arMainBoundLR.Add(Main_r);
// 				xx[0]+=poprav1;
			MainWinPoprx=poprav1;
			//корректировка границ гл. и доч. окна
// 				Chil_l+=poprav1;
// 				Chil_r+=poprav1;
// 				Main_l=crWin.left;
// 				Main_r=crWin.right;
			#ifdef LOG 
			char deb[1024]; sprintf(deb, "SetParentPosit корректировка MainWinPoprx: теперь главное.слева=%d раньше Main.слева=%d MainWinPoprx=%d",
				crWin.left, Main_l, MainWinPoprx); trif.RecordLog(deb);  
			#endif
			//запись в лог
			//****
// 				sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d SetParentPosit корректировка границ по х: теперь главное.слева=%d дочернее.слева=%d glob_popravx=%d\n", 
// 					(GetTickCount()-Appdlg->CurRec.LastLog), tt, Main_l, Chil_l, glob_popravx);
// 				Appdlg->CurRec.LastLog=GetTickCount();
// 				Appdlg->CurRec.indl++;
// 				if (Appdlg->CurRec.indl>90)
// 					Appdlg->CurRec.SaveLogz();
// 			if (tt>0)
// 			{//изменение координат и для "мертвых" действий
// 				if (MyAct[tt-1].Wpar(MyAct[tt]))
// 				{
// // 						arCorMousPos_mesx.Add(tt-1);//резервируем данные
// // 						arCorMousPos_mesx.Add(MyAct[tt-1].MOUS.xx[0]);
// // 						arCorMousBoundLR.Add(MyAct[tt-1].W.saWindows.Chil_l);
// // 						arCorMousBoundLR.Add(MyAct[tt-1].W.saWindows.Chil_r);
// // 						MyAct[tt-1].MOUS.xx[0]+=poprav1;
// // 						//корректировка границ и доч. окна
// // 						MyAct[tt-1].W.saWindows.Chil_l+=poprav1;
// // 						MyAct[tt-1].W.saWindows.Chil_r+=poprav1;
// // 						arMainBoundTB.Add(tt-1);
// // 						arMainBoundTB.Add(MyAct[tt-1].W.saWindows.Main_t);
// // 						arMainBoundTB.Add(MyAct[tt-1].W.saWindows.Main_b);
// // 						MyAct[tt-1].W.saWindows.Main_l=crWin.left;
// // 						MyAct[tt-1].W.saWindows.Main_r=crWin.right;
// 					#ifdef LOG 
// 					char deb[1024]; sprintf(deb, "SetParentPosit Изменение координат клика и для \"мертвых\" действий x=%d poprav=%d hwMain=%x GetWindowText=%s", 
// 						xx[0], poprav1, hwMain, trif.MyGetWindowText(hwMain)); trif.RecordLog(deb);  
// 					#endif
// 					//запись в лог
// 					//****
// // 						sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d SetParentPosit Изменение координат клика и для \"мертвых\" действий x=%d poprav=%d hwMain=%x GetWindowText=%s\n", 
// // 								(GetTickCount()-Appdlg->CurRec.LastLog), xx[0], poprav1, hwMain, trif.MyGetWindowText(hwMain));
// // 						Appdlg->CurRec.LastLog=GetTickCount();
// // 						Appdlg->CurRec.indl++;
// // 						if (Appdlg->CurRec.indl>90)
// // 						Appdlg->CurRec.SaveLogz();
// 				}
// 			}
			MainWinPopry=poprav2;
			//подготовка к поимке клюка перескока
			#ifdef LOG 
			deb[1024]; sprintf(deb, "SetParentPosit Изменение MainWinPopry=%d hwMain=%x теперь Main.top=%d раньше top=%d GetWindowText=%s", 
				MainWinPopry, hwMain, crWin.top, Main_t, trif.MyGetWindowText(hwMain)); trif.RecordLog(deb);  
			#endif

			AfxGetMainWnd()->SendMessage(WM_USER33, 1);

// 			arCorMousPos_mesy.Add(tt);//резервируем данные
// 			arCorMousPos_mesy.Add(yy[0]);
// 			arCorMousBoundTB.Add(Chil_t);
// 			arCorMousBoundTB.Add(Chil_b);
// //			yy[0]+=poprav2;
// 			//корректировка границ и доч. окна
// 			Chil_t+=poprav2;
// 			Chil_b+=poprav2;
// 			arMainBoundTB.Add(tt);
// 			arMainBoundTB.Add(Main_t);
// 			arMainBoundTB.Add(Main_b);
// 			Main_t=crWin.top;
// 			Main_b=crWin.bottom;
// 			if (tt>0)
// 			{//изменение координат и для "мертвых" действий
// 				if (MyAct[tt-1].Wpar(MyAct[tt]))
// 				{
// 					arCorMousPos_mesy.Add(tt-1);//резервируем данные
// 					arCorMousPos_mesy.Add(MyAct[tt-1].MOUS.yy[0]);
// 					arCorMousBoundTB.Add(MyAct[tt-1].W.saWindows.Chil_t);
// 					arCorMousBoundTB.Add(MyAct[tt-1].W.saWindows.Chil_b);
// 					MyAct[tt-1].MOUS.yy[0]+=poprav2;
// 					//корректировка границ и доч. окна
// 					MyAct[tt-1].W.saWindows.Chil_t+=poprav2;
// 					MyAct[tt-1].W.saWindows.Chil_b+=poprav2;
// 					arMainBoundTB.Add(tt-1);
// 					arMainBoundTB.Add(MyAct[tt-1].W.saWindows.Main_t);
// 					arMainBoundTB.Add(MyAct[tt-1].W.saWindows.Main_b);
// 					MyAct[tt-1].W.saWindows.Main_t=crWin.top;
// 					MyAct[tt-1].W.saWindows.Main_b=crWin.bottom;
// 				}
// 			}
		} else {
			//чисто отладочные сообщения
#ifdef LOG 
			char deb[950];
			deb[0]='\0';
			if ((int)xx+poprav1<0)
			{
				sprintf(deb, "SetParentPosit новая координата клика отрицательна по горизонт. poprav1=%d MOUS.xx[0]=%d", poprav1, xx); //trif.RecordLog(deb);
			}
			if (!(xx+poprav1<=crWin.right &&
				  xx+poprav1>=crWin.left))
			{
				sprintf(deb, "SetParentPosit новая координата клика не вписываетс в границы смещенного окна по горизонт. poprav1=%d MOUS.xx[0]=%d новое.right=%d новое.left=%d", poprav1, xx, crWin.right, crWin.left);
			}
			if ((int)yy+poprav2<0)
			{
				sprintf(deb, "SetParentPosit новая координата клика отрицательна по вертикали. poprav2=%d MOUS.yy[0]=%d", poprav2, yy); 
			}
			if (!(yy+poprav2<=crWin.bottom &&
				  yy+poprav2>=crWin.top))
			{
				sprintf(deb, "SetParentPosit новая координата клика не вписываетс в границы смещенного окна по вертикали. poprav2=%d MOUS.yy[0]=%d новое.bottom=%d новое.top=%d", poprav1, xx, crWin.bottom, crWin.top);
			}  
			trif.RecordLog(deb);
#endif
			//запись в лог
			//****
// 				if (strlen(deb))
// 				sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d %s\n", 
// 					(GetTickCount()-Appdlg->CurRec.LastLog), deb);
// 				Appdlg->CurRec.LastLog=GetTickCount();
// 				Appdlg->CurRec.indl++;
// 				if (Appdlg->CurRec.indl>90)
// 					Appdlg->CurRec.SaveLogz();
			//^^^^^ чисто отладочные сообщения ^^^^^
		}
		bo=true;
	}
// 		char deb[1024];
// 		sprintf(deb, "__bo=%d SetParentPosit Main_l=%d Main_t=%d Main_r=%d Main_b=%d MOUS.xx[0]=%d MOUS.yy[0]=%d hwMain=%x bo2=%d poprav=%d crWin.left=%d crWin.right=%d", bo, Main_l, Main_t, Main_r, Main_b, xx, yy, hwMain, bo2, poprav1, crWin.left, crWin.right);trif.RecordLog(deb);
	if (isMenu(MainClassName))
		return true;
	return bo;
}
//более точное взятие дочернего окна из точки (hwnd-степень детализации)
HWND CWinWork::MyWindowFromPoint(int x, int y, bool razr_mes, HWND hwnd)
{
	CPoint cPo=CPoint(x,y);
	//5 строчек м. оптимизировать 
	if (!::WindowFromPoint(CPoint(x,y))){
		return 0;
	}
	HWND par=GetPar(::WindowFromPoint(CPoint(x,y)));
	if (!par)
	{
		//****
		//Appdlg->MyAfxMessageBox("Error №1");
		return 0;
	}
	if (par==hwnd)
		return hwnd;
	if (!ScreenToClient(par, &cPo))
	{
		//DWORD dw=GetLastError();
		LPVOID lpMsgBuf;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(),  MAKELANGID(LANG_NEUTRAL,
			SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL
			);
		//****
		//Appdlg->MyAfxMessageBox((char*)lpMsgBuf);
	}
	HWND hw;
	if (ChildWindowFromPoint(par, cPo))
	{
		hw=ChildWindowFromPoint(par, cPo);
		if (hw==hwnd)
			return hwnd;
	} else {
		return par;
	}
	cPo=CPoint(x,y);
	ScreenToClient(hw, &cPo);
	while (ChildWindowFromPoint(hw, cPo)!=hw)
	{
		hw=ChildWindowFromPoint(hw, cPo);
		if (hw==hwnd)
			return hwnd;
		cPo=CPoint(x,y);
		ScreenToClient(hw, &cPo);
	}
	return hw;
}

//проверка родительского окна на вшивость: совпадение заголовка и имени класса
bool CWinWork::CheckParentWin(Acti& MyAct, int tt, HWND hwMain)
{
// 	if (MyAct[tt].W.Slice)
// 	{
// 		if ((trif.MyGetWindowText(hwMain).Find(MyAct[tt].W.Mai.csWinCapt)>-1)&&
// 			(trif.MyGetClassName(hwMain)==MyAct[tt].W.Mai.csClaName))
// 			return true;
// 	} else {
		if ((trif.MyGetWindowText(hwMain)==MyAct[tt].W.Mai.csWinCapt)&&
			(trif.MyGetClassName(hwMain)==MyAct[tt].W.Mai.csClaName))
			return true;
//	}
	return false;
}

//взятие родительского окна
HWND CWinWork::GetPar(HWND hw)
{
	if (hw==::GetDesktopWindow())
		return hw;
	while (::GetParent(hw))
	{
		if (::GetWindow(hw, GW_HWNDFIRST)==::GetWindow(GetDesktopWindow(), GW_CHILD)) 
			break;
		if (IsFirWinInParent(hw, ::GetParent(hw))){
			hw=::GetParent(hw);
		} else {
			return 0;
		}
		//dw=GetLastError();
	}
	return hw;
// 	if (hw==GetDesktopWindow())
// 		return hw;
// 	while ((::GetParent(hw))){
// 		if (::GetWindow(hw, GW_HWNDFIRST)==GetWindow(GetDesktopWindow(), GW_CHILD)) 
// 			break;
// 		hw=::GetParent(hw);
// 	}
// 	return hw;
}

//проверка размеров окошек + корректировка курсора мыши относительно 
//верх. лев. угла дочернего окна
//0 - все прошло нормально
//1 - прошло с корректировкой
//2 - корректировка требует повтора действия (чтобы в фокус вывести)
byte CWinWork::CheckSizeWin(HWND par, HWND chi, int Main_l, int Main_t, int Chil_l, int Chil_t, int xx, int yy)
{
	CRect rect_m, rect_c;
	int razn1=0, razn2=0;
	::GetWindowRect(par, &rect_m);
	::GetWindowRect(chi, &rect_c);
	//()
	razn1=(rect_c.left-rect_m.left)-(Chil_l-Main_l);
	razn2=(rect_c.left-rect_m.left)-(Chil_l-Main_l);
	if (razn1)
	{
		//запись в лог
		//****
// 		sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d CheckSizeWin старый клик x=%d child=%x новая граница слева=%d старая=%d поправка по горизонтали=%d\n", 
// 			(GetTickCount()-Appdlg->CurRec.LastLog), MyAct[tt].MOUS.xx[0], chi, rect1.left, Chil_l, razn1);
// 		Appdlg->CurRec.LastLog=GetTickCount();
// 		Appdlg->CurRec.indl++;
// 		if (Appdlg->CurRec.indl>90)
// 			Appdlg->CurRec.SaveLogz();
	}
	if (razn2)
	{
		//запись в лог
		//****
// 		sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d CheckSizeWin старый клик y=%d child=%x новая граница вверху=%d старая=%d поправка по вертикали=%d\n", 
// 			(GetTickCount()-Appdlg->CurRec.LastLog), MyAct[tt].MOUS.yy[0], chi, rect1.top, Chil_t, razn2);
// 		Appdlg->CurRec.LastLog=GetTickCount();
// 		Appdlg->CurRec.indl++;
// 		if (Appdlg->CurRec.indl>90)
// 			Appdlg->CurRec.SaveLogz();
	}
#ifdef LOG 
	if (razn1)
	{
		char deb[1024];sprintf(deb, "CheckSizeWin старый клик x=%d child=%x новая граница слева=%d старая=%d поправка по горизонтали=%d",
			xx, chi, rect_c.left, Chil_l, razn1); trif.RecordLog(deb);  
	}
	if (razn2)
	{
		char deb[1024]; sprintf(deb, "CheckSizeWin старый клик y=%d child=%x новая граница вверху=%d старая=%d поправка по вертикали=%d", 
			yy, chi, rect_c.top, Chil_t, razn2); trif.RecordLog(deb);  
	}
#endif
	//проверка совпадения границ окошка с хэндлом видимой области
	//снял жесткость проверки
	if (GetPar(::WindowFromPoint(CPoint(xx+razn1+MainWinPoprx, 
										yy+razn2+MainWinPopry)))!=par &&
		GetPar(MyWindowFromPoint(xx+razn1+MainWinPoprx, 
								 yy+razn2+MainWinPopry, false, chi))!=par)
	{
		//запись в лог
		//****
// 		sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d !!! CheckSizeWin несовпадение найденного родителя с родителем окошка под курсором GetPar(WindowFromPoint=%x)=%x par=%x GetPar(MyWindowFromPoint=%x)=%x\n", 
// 			(GetTickCount()-Appdlg->CurRec.LastLog), ::WindowFromPoint(CPoint(MyAct[tt].MOUS.xx[0]+razn1, MyAct[tt].MOUS.yy[0]+razn2)), GetPar(::WindowFromPoint(CPoint(MyAct[tt].MOUS.xx[0]+razn1, MyAct[tt].MOUS.yy[0]+razn2))), par, MyWindowFromPoint(MyAct[tt].MOUS.xx[0]+razn1, MyAct[tt].MOUS.yy[0]+razn2, false, chi), GetPar(MyWindowFromPoint(MyAct[tt].MOUS.xx[0]+razn1, MyAct[tt].MOUS.yy[0]+razn2, false, chi)));
// 		Appdlg->CurRec.LastLog=GetTickCount();
// 		Appdlg->CurRec.indl++;
// 		if (Appdlg->CurRec.indl>90)
// 			Appdlg->CurRec.SaveLogz();

		#ifdef LOG 
		char deb[1024]; sprintf(deb, "!!! CheckSizeWin несовпадение найденного родителя с родителем окошка под курсором GetPar(WindowFromPoint=%x)=%x par=%x GetPar(MyWindowFromPoint=%x)=%x", ::WindowFromPoint(CPoint(xx+razn1, yy+razn2)), GetPar(::WindowFromPoint(CPoint(xx+razn1, yy+razn2))), par, MyWindowFromPoint(xx+razn1, yy+razn2, false, chi), GetPar(MyWindowFromPoint(xx+razn1, yy+razn2, false, chi))); trif.RecordLog(deb);  
		#endif

		//закоментировал 2010.05.16 в борьбе с невыводом в фокус окошка меню
		//сначала пробуем разрешить быстрый вывод в фокус окна
		//if (!MyAct[tt].RazrFocus)
		//{
			//MyAct[tt].RazrFocus=true;
			//return 2;
		//}
		return 0;
	}
	//если разница меняется, то происходит корректировка
	//причем координаты нажатия добжны быть >0
	if (((razn1 || razn2) && xx+MainWinPoprx+razn1>=0) &&
							(yy+MainWinPopry+razn2>=0))
	{
		//проверка попадания в диапазон кнопки по х
		if (xx+MainWinPoprx+razn1>rect_c.right ||
			xx+MainWinPoprx+razn1<rect_c.left)
		{
			//такая ситуация чревато заведомо неправильными коорд. клика
			//****
// 			sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d !!! CheckSizeWin координаты нового клика за границами дочери (горизонталь)\n", 
// 				(GetTickCount()-Appdlg->CurRec.LastLog));
// 			Appdlg->CurRec.LastLog=GetTickCount();
// 			Appdlg->CurRec.indl++;
// 			if (Appdlg->CurRec.indl>90)
// 				Appdlg->CurRec.SaveLogz();

				#ifdef LOG 
					trif.RecordLog("!!! CheckSizeWin координаты нового клика за границами дочери (горизонталь)");  
				#endif
			return 0;
		}
		//проверка попадания в диапазон кнопки по у
		if (yy+razn2+MainWinPopry<rect_c.top ||
			yy+razn2+MainWinPopry>rect_c.bottom)
		{
			//****
// 			sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d !!! CheckSizeWin координаты нового клика за границами дочери (вертикаль)\n", 
// 				(GetTickCount()-Appdlg->CurRec.LastLog));
// 			Appdlg->CurRec.LastLog=GetTickCount();
// 			Appdlg->CurRec.indl++;
// 			if (Appdlg->CurRec.indl>90)
// 				Appdlg->CurRec.SaveLogz();
			#ifdef LOG 
			trif.RecordLog("!!! CheckSizeWin координаты нового клика за границами дочерн (вертикаль)");  
			#endif
				return 0;
		}
		//изменяем координату по х
		//if (MyAct[tt].baTypeAct==1 && (rect1.right< xx )){
		#ifdef LOG 
		trif.RecordLog("CheckSizeWin изменяем координату по х на "+trif.IntToStr(razn1));  
		#endif
// 		arCorMousPos_mesx.Add(tt);//резервируем данные
// 		arCorMousPos_mesx.Add(xx);
// 		arCorMousBoundLR.Add(Chil_l);
// 		arCorMousBoundLR.Add(Chil_r);

		//ДЛЯ ОТЛАДКИ
		//****
// 		sprintf(Appdlg->CurRec.logz[Appdlg->CurRec.indl], "%4d CheckSizeWin корректировка границ: дочернее.слева=%d glob_popravx=%d\n", 
// 			(GetTickCount()-Appdlg->CurRec.LastLog), Chil_l, glob_popravx);
// 		Appdlg->CurRec.LastLog=GetTickCount();
// 		Appdlg->CurRec.indl++;
// 		if (Appdlg->CurRec.indl>90)
// 			Appdlg->CurRec.SaveLogz();
		#ifdef LOG 
		char deb[1024]; sprintf(deb, "CheckSizeWin корректировка границ: дочернее.слева=%d ChaiWinPopry=%d", 
			Chil_l, ChaiWinPopry); trif.RecordLog(deb);
			sprintf(deb, "CheckSizeWin Chil_l = %d", Chil_l); trif.RecordLog(deb);  
		#endif
//		xx+=razn1;
		ChaiWinPoprx=razn1;
		ChaiWinPopry=razn2;
		AfxGetMainWnd()->SendMessage(WM_USER33, 2);

		//изменяем координату по у
		#ifdef LOG 
		trif.RecordLog("CheckSizeWin изменяем координату по у на "+trif.IntToStr(razn2));  
		#endif
	}
	return 0;
}

//выделение из строки заголовка без всяких служебных пометок
// CString CWinWork::ExtractCapt(CString str)
// {
// 	if (str.Find("**focus**", 0)==0)
// 	{
// 		str.Delete(0, 10);
// 	}
// 	if (str.Find("**posit**")==0)
// 		str.Delete(0, 11);
// 	return str;
// }

BOOL CWinWork::SaveWindowState(HWND hw)
{
	WINDOWPLACEMENT wp;
	wp.length = sizeof (WINDOWPLACEMENT);
	GetWindowPlacement(hw, &wp);
	DWORD dwStyle = ::GetWindowLong(hw, GWL_STYLE);		
	if (!(dwStyle & WS_VISIBLE)){
		wp.showCmd=SW_HIDE;
	}
	BOOL bResult = TRUE;
	CWinApp* pApp = AfxGetApp();
	if ((!pApp->WriteProfileInt("Win", "flags",	wp.flags)) || 
		(!pApp->WriteProfileInt("Win", "showCmd", wp.showCmd)) || 
		(!pApp->WriteProfileInt("Win", "x1", wp.rcNormalPosition.left)) ||
		(!pApp->WriteProfileInt("Win", "y1", wp.rcNormalPosition.top)) || 
		(!pApp->WriteProfileInt("Win", "x2", wp.rcNormalPosition.right)) ||
		(!pApp->WriteProfileInt("Win", "y2", wp.rcNormalPosition.bottom)))
		bResult = FALSE;
	return bResult;
}

BOOL CWinWork::RestoreWindowState(HWND hw)
{
	WINDOWPLACEMENT wp;
	CRect rMain;
	::GetWindowRect(hw, rMain);
	wp.length=sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(hw, &wp);
	CWinApp* pApp=AfxGetApp();
	wp.flags=pApp->GetProfileInt("Win", "flags",-1);
	wp.showCmd = pApp->GetProfileInt ("Win", "showCmd", -1);
	wp.rcNormalPosition.left=pApp->GetProfileInt(
		"Win", "x1", -1);
	wp.rcNormalPosition.top=pApp->GetProfileInt(
		"Win", "y1", -1);
	wp.rcNormalPosition.right=
		//wp.rcNormalPosition.left+rMain.Width();
		pApp->GetProfileInt("Win", "x2", -1);
	if (wp.rcNormalPosition.right-wp.rcNormalPosition.left<50)
		wp.rcNormalPosition.right=wp.rcNormalPosition.left+rMain.Width();
	wp.rcNormalPosition.bottom=//wp.rcNormalPosition.top+rMain.Height();
		pApp->GetProfileInt("Win", "y2", -1);
	if (wp.rcNormalPosition.bottom-wp.rcNormalPosition.top<50)
		wp.rcNormalPosition.bottom=wp.rcNormalPosition.top+rMain.Height();
	if (wp.rcNormalPosition.left<0)
		return FALSE;
	if (wp.rcNormalPosition.top<0)
		return FALSE;
	if ((wp.flags != -1) && (wp.showCmd != -1) &&
		(wp.rcNormalPosition.left != -1) &&
		(wp.rcNormalPosition.top  != -1) /*
		&&
				(wp.rcNormalPosition.right != -1) &&
				(wp.rcNormalPosition.bottom != -1)*/
		) 
	{
		if ((wp.rcNormalPosition.left <=
			(::GetSystemMetrics(SM_CXSCREEN) -
			::GetSystemMetrics(SM_CXICON))) &&
			(wp.rcNormalPosition.top <=
			(::GetSystemMetrics(SM_CYSCREEN) -
			::GetSystemMetrics(SM_CYICON))))
		{
			SetWindowPlacement (hw, &wp);
			AfxGetMainWnd()->SetTimer(534, 0, 0);

			if (wp.showCmd==SW_HIDE){
				AfxGetMainWnd()->SetTimer(536, 0, 0);
			}
			return TRUE;
		}
	}
	return FALSE;
}

//перебор окон - взятие следующего окна (посмотреть, где можно встроить этот алгоритм
//вместо навороченных неоптимизированных мест в этом файле
//список получается как линейный, для всего перебора достаточно сделать
//	while (next=GetNextWin(next)) {...}

HWND CWinWork::GetNextWin(HWND hw_prev)
{
	if (!hw_prev)
		return GetDesktopWindow();
	HWND par, next;
	next = GetWindow(hw_prev,GW_CHILD);
	if (next) return next;
	next = GetNextWindow(hw_prev, GW_HWNDNEXT);
	if (next) return next;
	par=hw_prev;
	while (!next) {
		par = GetParent(par);
		next=GetNextWindow(par, GW_HWNDNEXT);
	}
	if (next) return next;
	return 0;
}
// HWND CWinWork::GetNextChild2(HWND parent, HWND hw_prev)
// {
// }
//взятие следующего дочернего в пределах одного родителя
//hw_prev - с какого дочернего начинать 
HWND CWinWork::GetNextChild(HWND parent, HWND hw_prev)
{
	if (!parent)
	{
		return 0;
	}
	if (!hw_prev)
	{
		return GetWindow(parent,GW_CHILD);
	}
	HWND par, next;
	next = GetWindow(hw_prev,GW_CHILD);
	if (next)
	{
		return next;
	}
	next = GetNextWindow(hw_prev, GW_HWNDNEXT);
	if (next)
	{
		return next;
	}
	par=hw_prev;
	while (!next) 
	{
		par = GetParent(par);
		if (par==parent)
		{
			return 0;
		}
		if (!par)
		{
			return 0;
		}
		next=GetNextWindow(par, GW_HWNDNEXT);
	}
	if (next==parent)
	{
		return 0;
	}
	return next;
}
HWND CWinWork::GetNextMainWin(HWND hw_prev)
{
	if (!hw_prev)
		return GetDesktopWindow();
//	HWND par, next;
	if (hw_prev==GetDesktopWindow())
		return GetWindow(hw_prev,GW_CHILD);
	return  GetWindow(hw_prev,GW_HWNDNEXT);
// 	if (next) return next;
// 	return 0;
}

CWinWork* this2;
pBGR CWinWork::MyGetDibBits(CDC* hdcSrc, int nx, int ny)
{
	//HBITMAP hBmpSrc;
	CDC BufferDC;
	CBitmap BufferBitmap, *OldBitmap;

	BufferDC.CreateCompatibleDC ( hdcSrc );
	BufferBitmap.CreateCompatibleBitmap ( hdcSrc, nx, ny );
	OldBitmap=BufferDC.SelectObject ( &BufferBitmap );
	BufferDC.FillSolidRect ( 0, 0, nx, ny, 0 );
	BufferDC.BitBlt ( 0, 0, nx, ny, hdcSrc, 0, 0, SRCCOPY|CAPTUREBLT );
	BufferDC.SelectObject ( OldBitmap );


	BITMAPINFO bi;
	BOOL bRes;
	pBGR buf;

	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = nx;
	bi.bmiHeader.biHeight = - ny;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = nx * 4 * ny;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;
	
	buf = (pBGR) malloc(nx * 4 * ny);
	bRes = GetDIBits(hdcSrc->m_hDC, HBITMAP(BufferBitmap), 0, ny, buf, &bi, DIB_RGB_COLORS);
	if (!bRes) {
		free(buf);
		buf = 0;
	}
	BufferBitmap.DeleteObject();
	return buf;
}


sSmartControl_tmp gSC;
// CUIntArray gtypeSear, gSC.xl, gSC.xr, gSC.yt, gSC.yb;
// CUIntArray gSC.clickx, gSC.clicky, gSC.typeClick, gSC.Rx, gSC.Ry;


// UINT ParallelSearch(LPVOID pParam)
// {
// //	char ch[1024];
// 	#ifdef LOG 
// 	this2->trif.RecordLog("ParallelSearch");  
// 	#endif
// 	UINT begin_time=GetTickCount(), cictime=0;
// 	int Max_sovp=0, sovp=0, vhod=0;
// 	CDC *pDesktopDC;
// 	HDC tmpDC, tmpDC2;
// 	tmpDC =::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 	tmpDC2=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 	CDC *pDesktopDC33=CDC::FromHandle(tmpDC);
// 	CDC *pDesktopDC2=CDC::FromHandle (tmpDC2);
// 	CDC DCFromFile;
// 	//CDibExt e_dib1;
// 	//CDibExt e_dib2;
// 	MyBitAr bit;
// 	BITMAP m_bmInfo2;
// 	CBitmap *pOldBmp;
// 	if (file_kusok_bmp.GetSize()<2)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("return 0 file_kusok_bmp.GetSize()<2");  
// 		#endif
// 		this2->zap_thread=false;
// 		return 0;
// 	}
// 	bit.SetSize(file_kusok_bmp.GetSize()-1);
// 	bool loadedbmp=false;
// 	int nonLoadBit=0;//для учета незагруженных картинок
// 	for (int i_bmp=1; i_bmp<file_kusok_bmp.GetSize(); i_bmp++)
// 	{
// 		//загружаем битмапы из файла
// 		if (!file_kusok_bmp[i_bmp].IsEmpty())
// 		if (!bit[i_bmp-1-nonLoadBit].Attach(LoadImage(0, file_kusok_bmp[i_bmp] ,
// 			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)))
// 		{
// 			#ifdef LOG 
// 			char deb[1024];
// 			sprintf(deb, "не загружена картинка bit[%d-1-%d].Attach", i_bmp, nonLoadBit);
// 			this2->trif.RecordLog(deb);  
// 			#endif
// 			bit.RemoveAt(i_bmp-1-nonLoadBit);
// 			nonLoadBit++;
// 		} else {
// 			loadedbmp=true;
// 		}
// 	}
// 	if (!loadedbmp)
// 	{
// 		this2->zap_thread=false;
// 		return 0;
// 	}
// 	HDC desk_cdc= ::GetDC(::GetDesktopWindow());
// 	//HDC desk_cdc2=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 	if (!desk_cdc)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("Повторно GetDCEx");  
// 		#endif
// 		Sleep(10);
// 		//desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 		desk_cdc=::GetDC(GetDesktopWindow());
// 	}
// 	if (!desk_cdc)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("!!!НЕудача GetDCEx - выходим");  
// 		#endif
// 		this2->zap_thread=false;
// 		return 0;
// 	}
// 	//берем рабочий стол
// 	pDesktopDC = CDC::FromHandle (desk_cdc);
// 	if (!pDesktopDC)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("повторно CDC::FromHandle");  
// 		#endif
// 		Sleep(10);
// 		pDesktopDC = CDC::FromHandle(desk_cdc);
// 	}
// 	if (!pDesktopDC)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("повторно CDC::FromHandle");  
// 		#endif
// 		Sleep(10);
// 		pDesktopDC = CDC::FromHandle(desk_cdc);
// 	}
// 	if (!pDesktopDC)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("!!!НЕудача CDC::FromHandle");  
// 		#endif
// 		this2->zap_thread=false;
// 		return 0;
// 	}
// 
// 	//создаем совместимый с ним контекст для файла
// 	if (!DCFromFile.CreateCompatibleDC(pDesktopDC))
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("облом DCFromFile.CreateCompatibleDC");  
// 		#endif
// 		ReleaseDC(0, pDesktopDC->m_hDC);
// 		this2->zap_thread=false;
// 		return 0;
// 	}
// 	CRect rec_desk;
// 	pBGR bgr_desk=NULL;
// 	//bool need_del_desk=false;
// 	::GetWindowRect(pDesktopDC->GetWindow()->GetSafeHwnd(), rec_desk);
// 	UINT oldtim=GetCurrentTime();
// 	UINT oldtim2=GetCurrentTime();
// 	#ifdef LOG 
// 	this2->trif.RecordLog("перед for (int ps=0; ; ps++)");  
// 	#endif
// 	for (int ps=0; ; ps++)
// 	{
// 		pBGR bgr_pix=NULL;
// 		int cur_picter;
// 		if (this2->randVetv)
// 		{
// 			cur_picter = (rand()+GetTickCount()) % bit.GetSize();
// 		} else {
// 			cur_picter = ps % (bit.GetSize());
// 		}
// 		if (!(ps % (bit.GetSize())))
// 		{
// 			if (ps)
// 			{
// 				ReleaseDC(0, pDesktopDC->m_hDC);
// 				delete bgr_desk;
// 				bgr_desk=NULL;
// 			}
// 			if (this2->stop_sear && ps)
// 			{
// 				if (bgr_pix)
// 				{
// 					delete bgr_pix;
// 					bgr_pix=NULL;
// 				}
// 				break;
// 			}
// 			if (GetCurrentTime()-oldtim2 >10000)
// 			{
// 				oldtim2=GetCurrentTime();
// 				::RedrawWindow(0, rec_desk, 0, RDW_FRAME|RDW_INVALIDATE|RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
// 				Sleep(10);
// 			}
// 			//3 раза пробуем контекст устройства взять
// 			HDC desk_cdc=::GetDC(GetDesktopWindow());
// 			//HDC desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 			if (!desk_cdc)
// 			{
// 				#ifdef LOG 
// 				this2->trif.RecordLog("Повторно GetDCEx");  
// 				#endif
// 				Sleep(10);
// 				desk_cdc=::GetDC(GetDesktopWindow());
// 				//desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 			}
// 			if (!desk_cdc)
// 			{
// 				#ifdef LOG 
// 				this2->trif.RecordLog("Повторно GetDCEx");  
// 				#endif
// 				Sleep(10);
// 				desk_cdc=::GetDC(GetDesktopWindow());
// 				//desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 			}
// 			if (!desk_cdc)
// 			{
// 				#ifdef LOG 
// 				this2->trif.RecordLog("!!!НЕудача GetDCEx - выходим");  
// 				#endif
// 				this2->zap_thread=false;
// 				return 0;
// 			}
// 			pDesktopDC = CDC::FromHandle(desk_cdc);
// 			if (!pDesktopDC)
// 			{
// 				Sleep(10);
// 				pDesktopDC = CDC::FromHandle(desk_cdc);
// 			}
// 			if (!pDesktopDC)
// 			{
// 				Sleep(10);
// 				pDesktopDC = CDC::FromHandle(desk_cdc);
// 			}
// 			if (!pDesktopDC)
// 			{
// 				#ifdef LOG 
// 				this2->trif.RecordLog("!!!НЕудача CDC::FromHandle");  
// 				#endif
// 				this2->zap_thread=false;
// 				return 0;
// 			}
// 			bgr_desk = MyGetDibBits(pDesktopDC, rec_desk.Width(), rec_desk.Height());
// 			UINT deltatim=GetCurrentTime()-oldtim;
// 			if ((deltatim)>2000)
// 			{
// 				if (deltatim>25000)
// 					deltatim=25000;
// 				Sleep(deltatim/50);
// 			}
// 		}
// 
// 		//** засунуть в массивы для более редкого вызова
// 		GetObject( bit[cur_picter].GetSafeHandle(), sizeof(BITMAP), &m_bmInfo2 );
//  		int pix_sxx=m_bmInfo2.bmWidth, 
//  			pix_syy=m_bmInfo2.bmHeight;
// 		pOldBmp = DCFromFile.SelectObject(&bit[cur_picter]); //закидываем в контекст
// 		bgr_pix = MyGetDibBits(&DCFromFile, pix_sxx, pix_syy);
// 		if (bgr_pix == NULL)
// 		{
// 			this2->zap_thread=false;
// 			return 0;
// 		}
// 		DCFromFile.SelectObject(pOldBmp);
// 		//определяем каркас неодинаковых цветов
// 		UINT oldtime=GetTickCount();
// 	 	CUIntArray red_pix, green_pix, blue_pix, ind_x, ind_y;
// 		int indx=0;
// 	 	for (int ii=0; ii< pix_sxx; ii++){
// 	 	for (int jj=0; jj< pix_syy; jj++)
// 	 	{
// 	 		indx=ii+jj*pix_sxx;
// // 	 		blue_pix [indx]=bgr_pix[indx].r;
// // 	 		green_pix[indx]=bgr_pix[indx].g;
// // 	 		red_pix  [indx]=bgr_pix[indx].b;
// 	// 		//делаем матрицу из неодинаковых цветов, чтобы ускорить поиск
// 	 		if (ind_x.GetSize()>4)//почему???
// 			{
// 				continue;
// 			}
// 	 		if (ii==0 && jj==0) //почему???
// 			{
// 				continue;
// 			}
// 	 		if (bgr_pix[indx].r!=bgr_pix[0].r || 
// 	 			bgr_pix[indx].g!=bgr_pix[0].g || 
// 				bgr_pix[indx].b!=bgr_pix[0].b)
// 	 		{
// 	 			bool razr=1;
// 	 			for (int kk=0; kk<ind_x.GetSize(); kk++)
// 	 			{
// 	 				int newind=ind_x[kk]+ind_y[kk]*pix_sxx;
// 					if (newind>=pix_sxx*pix_syy)
// 					{
// 	 					razr=0;
// 						break;
// 					}
// 	 				if (bgr_pix[indx].r!=bgr_pix[newind].r) 
// 	 				if (bgr_pix[indx].g!=bgr_pix[newind].g) 
// 	 				if (bgr_pix[indx].b!=bgr_pix[newind].b) 
// 	 				{
// 	 					razr=0;
// 						break;
// 	 				}
// 	 			}
// 	 			if (razr)
// 	 			{
// 	 				ind_x.Add(ii);
// 	 				ind_y.Add(jj);
// 	 			}
// 	 		}
// 	 	}
// 	 	}
// 	//	e_dib2.PasteDC( &DCFromFile, 0, 0, pix_sxx, pix_syy);
// 	 	if (ind_x.GetSize()==0)
// 	 	{
// 	 		ind_x.Add(1);
// 	 		ind_y.Add(1);
// 	 	}
// 
// 		//определяем границы поиска
// 		int pix1_x=0;
// 		int pix1_y=0;
// 		int pix2_x=rec_desk.Width ()-pix_sxx;
// 		int pix2_y=rec_desk.Height()-pix_syy;
// 		switch(gtypeSear[cur_picter])
// 		{
// 		case (1):
// 			{
// 			int numsear=(ps % (file_kusok_bmp.GetSize()*20)) / file_kusok_bmp.GetSize();
// 			if (numsear!=19)  
// 			{
// 				pix1_x=gSC.xl[cur_picter];
// 				if (pix1_x>rec_desk.Width ()-pix_sxx)
// 					pix1_x=rec_desk.Width ()-pix_sxx;
// 				pix1_y=gSC.yb[cur_picter];
// 				if (pix1_y>rec_desk.Height()-pix_syy)
// 					pix1_y=rec_desk.Height()-pix_syy;
// 				pix2_x=gSC.xr[cur_picter];
// 				if (pix2_x>rec_desk.Width ()-pix_sxx)
// 					pix2_x=rec_desk.Width ()-pix_sxx;
// 				pix2_y=gSC.yt[cur_picter];
// 				if (pix2_y>rec_desk.Height()-pix_syy)
// 					pix2_y=rec_desk.Height()-pix_syy;
// 			}			
// 			}
// 			break;
// 		case (2):
// 			pix1_x=gSC.xl[cur_picter];
// 			if (pix1_x>rec_desk.Width ()-pix_sxx)
// 				pix1_x=rec_desk.Width ()-pix_sxx;
// 			pix1_y=gSC.yb[cur_picter];
// 			if (pix1_y>rec_desk.Height()-pix_syy)
// 				pix1_y=rec_desk.Height()-pix_syy;
// 			pix2_x=gSC.xr[cur_picter];
// 			if (pix2_x>rec_desk.Width ()-pix_sxx)
// 				pix2_x=rec_desk.Width ()-pix_sxx;
// 			pix2_y=gSC.yt[cur_picter];
// 			if (pix2_y>rec_desk.Height()-pix_syy)
// 				pix2_y=rec_desk.Height()-pix_syy;
// 		    break;
// 		}
// 
// 		for (int ii_desk=pix1_x; ii_desk<pix2_x; ii_desk++){
// 			for (int jj_desk=pix1_y; jj_desk<pix2_y; jj_desk++)
// 			{
// 	// 			if (GetTickCount() % 1000 == 0)
// 	// 				pDesktopDC = CWnd::GetDesktopWindow()->GetDC();
// 				
// 				bool finded=1;
// 	 			int find_karkas=0;
// 	 			for (int kk=0; kk<ind_x.GetSize(); kk++)
// 	 			{
// //	 				int newind=ind_x[kk]+ind_y[kk]*pix_sxx;
// 					int ind1=ind_x[kk]+ind_y[kk]*pix_sxx;
// 					int ind2=ii_desk+ind_x[kk]+(jj_desk+ind_y[kk])*rec_desk.Width();
// //					int debi=bgr_pix[0].r;
// // 					debi=bgr_desk[0].r;
// // 					debi=bgr_pix[ind1].r;
// // 					debi=bgr_desk[ind2].r;
// // 					debi=bgr_pix[ind1].r;
// // 					debi=bgr_pix[ind1].r;
// 					if (bgr_pix[ind1].r == bgr_desk[ind2].r)
// 					if (bgr_pix[ind1].g == bgr_desk[ind2].g)
// 					if (bgr_pix[ind1].b == bgr_desk[ind2].b) 
// 					{
// 			 			find_karkas++;
// 					}
// 					if (find_karkas!=kk+1)
// 						break;
// 	 			}
// 				//если совпал первый пиксель, то делаем дальнейший прочес
// 
// 				if (find_karkas==ind_x.GetSize())
// 				{
// 					vhod++;
// 					finded=1;
// 					sovp=0;
// 					for (int ii=0; ii< pix_sxx; ii++)
// 					{
// 						for (int jj=0; jj< pix_syy; jj++)
// 						{
// 							int ind1=ii+jj*pix_sxx;
// 							int ind2=ii_desk+ii+(jj_desk+jj)*rec_desk.Width();
// 							if (bgr_pix[ind1].r != bgr_desk[ind2].r
// 							||  bgr_pix[ind1].g != bgr_desk[ind2].g 
// 							||  bgr_pix[ind1].b != bgr_desk[ind2].b) 
// 							{
// 								finded=0;
// 								break;
// 							}
// 							sovp++;
// 						}
// 						if (!finded)
// 							break;
// 					}
// 					if (sovp>Max_sovp) Max_sovp=sovp;
// 					if (finded)
// 					{
// 						this2->fi_coorx=ii_desk;
// 						this2->fi_coory=jj_desk;
// 						CPoint pt1=CPoint(ii_desk, jj_desk);
// 						CPoint pt2=CPoint(ii_desk+pix_sxx, jj_desk+pix_syy);
// 						int paus_interv=50-10*this2->SpeedPlay;
// 						if (paus_interv<=0) paus_interv=0;
// 						pt1.x-=50;
// 						pt2.x+=50;
// 						pt1.y-=50;
// 						pt2.y+=50;
// 						this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 						this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 						if (paus_interv)
// 							Sleep(paus_interv*2);
// 						this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 						this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 						for (int ind=0; ind<5; ind++)
// 						{
// 							if (paus_interv)
// 								Sleep(paus_interv);
// 							pt1.x+=10;
// 							pt2.x-=10;
// 							pt1.y+=10;
// 							pt2.y-=10;
// 							this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 							this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 							if (paus_interv)
// 								Sleep(paus_interv*2);
// 							this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 							this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 						}
// 						this2->PictIsFi=true;
// 						this2->num_find_bmp=cur_picter;
// 						break;
// 					}
// 				}
// 			}
// 			if (this2->PictIsFi)
// 				break;
// 		}
// 
// 
// 		//при совпадении красным прямоугольником обрамляем
// 		//чистим ресурсы
// 	//	char ch[1024];
// 		//ReleaseDC(DCFromFile);
// 		//ReleaseDC(pDesktopDC);
// 		if (bgr_pix)
// 		{
// 			delete bgr_pix;
// 			bgr_pix=NULL;
// 		}
// 
// 		if (this2->PictIsFi)
// 			break;
// 	}
// 	#ifdef LOG 
// 	this2->trif.RecordLog("после for (int ps=0; ; ps++)");  
// 	#endif
// 	if (bgr_desk)
// 	{
// 		delete bgr_desk;
// 		bgr_desk=NULL;
// 	}
// 
// 	for (i_bmp=0; i_bmp<bit.GetSize(); i_bmp++)
// 	{
// 			bit[i_bmp].DeleteObject();
// 	}
// 	ReleaseDC(0, pDesktopDC->m_hDC);
// 	ReleaseDC(0, DCFromFile.m_hDC);
// 	pDesktopDC->DeleteDC();
// 	DCFromFile.DeleteDC();
// 	this2->zap_thread=false;
// 	this2->exit_cikl=true;
// 	return 1;
// }
UINT SearchOtkl(LPVOID pParam)
{
	#ifdef LOG 
	this2->trif.RecordLog("ParallelSearch");  
	#endif
	int NumFKar=30;
	UINT begin_time=GetTickCount(), cictime=0;
	int Max_sovp=0, sovp=0, vhod=0;
	CDC *pDesktopDC;
	HDC tmpDC, tmpDC2;
	tmpDC =::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
	tmpDC2=::GetDC(GetDesktopWindow());
	//CDC *pDesktopDC33=CDC::FromHandle (tmpDC );
	CDC *pDesktopDC2 =CDC::FromHandle (tmpDC2);
	CDC DCFromFile;
	MyBitAr bit;
	BITMAP m_bmInfo2;
	CBitmap *pOldBmp;
	bit.SetSize(gSC.saPixContr.GetSize()-1);
	bool loadedbmp=false;
	int nonLoadBit=0;//для учета незагруженных картинок
	for (int i_bmp=1; i_bmp<gSC.saPixContr.GetSize(); i_bmp++)
	{
		//загружаем битмапы из файла
		if (!gSC.saPixContr[i_bmp].IsEmpty())
		if (!bit[i_bmp-1-nonLoadBit].Attach(LoadImage(0, gSC.saPixContr[i_bmp] ,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)))
		{
			#ifdef LOG 
			char deb[1024];
			sprintf(deb, "не загружена картинка bit[%d-1-%d].Attach", i_bmp, nonLoadBit);
			this2->trif.RecordLog(deb);
			#endif
			bit.RemoveAt(i_bmp-1-nonLoadBit);
			nonLoadBit++;
		} else {
#ifdef LOG 
			char deb[1024];
			sprintf(deb, "SearchOtkl загружена картинка для поиска %s", gSC.saPixContr[i_bmp]);
			this2->trif.RecordLog(deb);
#endif
			loadedbmp=true;
		}
	}
	if (!loadedbmp)
	{
		this2->zap_thread=false;
		DeleteObject(tmpDC);
		DeleteObject(tmpDC2);
		return 0;
	}
	HDC desk_cdc= ::GetDC(::GetDesktopWindow());
	if (!desk_cdc)
	{
		#ifdef LOG 
		this2->trif.RecordLog("Повторно GetDCEx");  
		#endif
		Sleep(10);
		desk_cdc=::GetDC(GetDesktopWindow());
	}
	if (!desk_cdc)
	{
		#ifdef LOG 
		this2->trif.RecordLog("!!!НЕудача GetDCEx - выходим");  
		#endif
		this2->zap_thread=false;
		DeleteObject(tmpDC);
		DeleteObject(tmpDC2);
		DeleteObject(desk_cdc);
		return 0;
	}
	//берем рабочий стол
	pDesktopDC = CDC::FromHandle (desk_cdc);
	if (!pDesktopDC)
	{
		#ifdef LOG 
		this2->trif.RecordLog("повторно CDC::FromHandle");  
		#endif
		Sleep(10);
		pDesktopDC = CDC::FromHandle(desk_cdc);
	}
	if (!pDesktopDC)
	{
		#ifdef LOG 
		this2->trif.RecordLog("повторно CDC::FromHandle");  
		#endif
		Sleep(10);
		pDesktopDC = CDC::FromHandle(desk_cdc);
	}
	if (!pDesktopDC)
	{
		#ifdef LOG 
		this2->trif.RecordLog("!!!НЕудача CDC::FromHandle");  
		#endif
		this2->zap_thread=false;
		DeleteObject(tmpDC);
		DeleteObject(tmpDC2);
		DeleteObject(desk_cdc);
		return 0;
	}

	//создаем совместимый с ним контекст для файла
	if (!DCFromFile.CreateCompatibleDC(pDesktopDC))
	{
		#ifdef LOG 
		this2->trif.RecordLog("облом DCFromFile.CreateCompatibleDC");  
		#endif
		ReleaseDC(0, pDesktopDC->m_hDC);
		this2->zap_thread=false;
		DeleteObject(tmpDC);
		DeleteObject(tmpDC2);
		DeleteObject(desk_cdc);
		return 0;
	}
	//Массивы вырезанных пикселей
	MyCRectAr CutRects;
	CUIntArray BegCutRect;
	CUIntArray EndCutRect;
	MyCRectAr SaveRects;
	CStringArray SaveBmps;
	CUIntArray sBegCutRect;
	CUIntArray sEndCutRect;
	if (gSC.OBJs.GetSize())
	{
		for (int ii=0; ii<gSC.OBJs.GetSize(); ii++)
		{
			int oldsize=CutRects.GetSize();
			int soldsize=SaveRects.GetSize();
			this2->StrToCrects(gSC.OBJs[ii], CutRects, SaveRects, SaveBmps);
			int newsize=CutRects.GetSize();
			int snewsize=SaveRects.GetSize();
			if (newsize>oldsize)
			{
				BegCutRect.SetSize(ii+1);
				EndCutRect.SetSize(ii+1);
				BegCutRect[ii]=oldsize;
				EndCutRect[ii]=newsize;
			}
			if (snewsize>soldsize)
			{
				sBegCutRect.SetSize(ii+1);
				sEndCutRect.SetSize(ii+1);
				sBegCutRect[ii]=soldsize;
				sEndCutRect[ii]=snewsize;
			}
		}
	}

	CRect rec_desk;
	pBGR bgr_desk=NULL;
	::GetWindowRect(pDesktopDC->GetWindow()->GetSafeHwnd(), rec_desk);
	UINT oldtim=GetCurrentTime();
	UINT oldtim2=GetCurrentTime();
	UINT iotk=0;
	UINT jotk=0;
	#ifdef LOG 
	this2->trif.RecordLog("перед for (int ps=0; ; ps++)");  
	UINT lastTime=::GetTickCount();
	#endif
	bool sOtk=false; //ищем с учетом цветового отклонения
	bool stopShow=true;
	CRect rectS; 
	int numsear=-1;
	BegCutRect.SetSize(bit.GetSize());
	EndCutRect.SetSize(bit.GetSize());
	for (int ps=0; ; ps++)
	{
		pBGR bgr_pix=NULL;
		int cur_picter;
		if (gSC.randVetv)
		{
			cur_picter = (rand()+GetTickCount()) % bit.GetSize();
		} else {
			cur_picter = ps % (bit.GetSize());
		}
		if (!(ps % (bit.GetSize())))
		{	//ЗАНОВО БЕРЕМ РАБОЧИЙ СТОЛ
			numsear++;//инкрементируем счетчик поисков
			if (numsear==20) numsear=0;
			if (this2->ColPerPix>0.0 && (numsear==3 || numsear==8))
			{	//разрешаем поиск с цветовым отклонением
				sOtk=true; 
			} else {
				sOtk=false;
			}
			
			if (ps)
			{
				ReleaseDC(0, pDesktopDC->m_hDC);
				delete bgr_desk;
				bgr_desk=NULL;
			}
			if (this2->stop_sear && ps>bit.GetSize())
			{
				if (bgr_pix)
				{
					delete bgr_pix;
					bgr_pix=NULL;
				}
				break;
			}
			//перерисовываем весь экран, чтобы всякие артефакты убрать, если есть такие
			if (GetCurrentTime()-oldtim2 >10000)
			{
				oldtim2=GetCurrentTime();
				::RedrawWindow(0, rec_desk, 0, RDW_FRAME|RDW_INVALIDATE|RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
				Sleep(10);
			}
			//3 раза пробуем контекст устройства взять
			HDC desk_cdc=::GetDC(GetDesktopWindow());
			//HDC desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
			if (!desk_cdc)
			{
				#ifdef LOG 
				this2->trif.RecordLog("Повторно GetDCEx");  
				#endif
				Sleep(10);
				desk_cdc=::GetDC(GetDesktopWindow());
				//desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
			}
			if (!desk_cdc)
			{
				#ifdef LOG 
				this2->trif.RecordLog("Повторно GetDCEx");  
				#endif
				Sleep(10);
				desk_cdc=::GetDC(GetDesktopWindow());
				//desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
			}
			if (!desk_cdc)
			{
				#ifdef LOG 
				this2->trif.RecordLog("!!!НЕудача GetDCEx - выходим");  
				#endif
				this2->zap_thread=false;
				DeleteObject(tmpDC);
				DeleteObject(tmpDC2);
				DeleteObject(desk_cdc);
				return 0;
			}
			pDesktopDC = CDC::FromHandle(desk_cdc);
			if (!pDesktopDC)
			{
				Sleep(10);
				pDesktopDC = CDC::FromHandle(desk_cdc);
			}
			if (!pDesktopDC)
			{
				Sleep(10);
				pDesktopDC = CDC::FromHandle(desk_cdc);
			}
			if (!pDesktopDC)
			{
				#ifdef LOG 
				this2->trif.RecordLog("!!!НЕудача CDC::FromHandle");  
				#endif
				this2->zap_thread=false;
				DeleteObject(tmpDC);
				DeleteObject(tmpDC2);
				DeleteObject(desk_cdc);
				return 0;
			}
			//проверяем открытость окна StopMe, 
			//чтобы не засчитывать на нем картинку
			//если до и после MyGetDibBits окно скрыто,
			//то разрешаем поиск по его ректу
			stopShow=true;
			if (this2->stopME)
			{
				::GetWindowRect(this2->stopME, &rectS);
				if (this2->GetPar(::WindowFromPoint(rectS.CenterPoint()))!=
					this2->GetPar(this2->stopME))
				{
#ifdef LOG 
					this2->trif.RecordLog("stopShow=false 1");
#endif
					stopShow=false;
				}
			}
			bgr_desk = this2->MyGetDibBits(pDesktopDC, rec_desk.Width(), rec_desk.Height());
			if (this2->stopME && !stopShow)
			{
				if (this2->GetPar(::WindowFromPoint(rectS.CenterPoint()))!=
					this2->GetPar(this2->stopME))
				{
#ifdef LOG 
						this2->trif.RecordLog("stopShow=false 2");
#endif
					stopShow=false;
				}
			} else stopShow=true;
			if (!this2->stopME)
			{
#ifdef LOG 
					this2->trif.RecordLog("stopShow=false 3");
#endif
				stopShow=false;
			}
// #ifdef LOG 
// 			if (stopShow)
// 			{
// 				this2->trif.RecordLog("stopShow=true");
// 			}
// #endif

			UINT deltatim=GetCurrentTime()-oldtim;
			if ((deltatim)>2000)
			{
				if (deltatim>25000)
					deltatim=25000;
				Sleep(deltatim/50);
			}
		}
// #ifdef LOG 
// 		char ch[1024];
// 		sprintf(ch, "%06d cur_picter=%d ps=%d numsear=%d sOtk=%d", 
// 			(::GetTickCount()-lastTime), cur_picter, ps, numsear, sOtk);
// 		this2->trif.RecordLog(ch);  
// 		lastTime=::GetTickCount();
// #endif

		//** засунуть в массивы для более редкого вызова
		GetObject( bit[cur_picter].GetSafeHandle(), sizeof(BITMAP), &m_bmInfo2 );
 		this2->pix_sxx=m_bmInfo2.bmWidth;
 		this2->pix_syy=m_bmInfo2.bmHeight;
		pOldBmp = DCFromFile.SelectObject(&bit[cur_picter]); //закидываем в контекст
		bgr_pix = this2->MyGetDibBits(&DCFromFile, this2->pix_sxx, this2->pix_syy);
		if (bgr_pix == NULL)
		{
			this2->zap_thread=false;
			DeleteObject(tmpDC);
			DeleteObject(tmpDC2);
			DeleteObject(desk_cdc);
			return 0;
		}
		DCFromFile.SelectObject(pOldBmp);
		//МАССИВ ВЫРЕЗАННЫХ ПИКСЕЛЕЙ
		for (int ii=0; ii< this2->pix_sxx; ii++)
		for (int jj=0; jj< this2->pix_syy; jj++)
		{
			int indx=ii+jj*this2->pix_sxx;
			bgr_pix[indx].pad=1;
			for (UINT ll=BegCutRect[cur_picter]; ll<EndCutRect[cur_picter]; ll++)
			{
				if (PtInRect(CutRects[ll], CPoint(ii, jj)))
					bgr_pix[indx].pad=0;
			}
		}


		//закидываем в массив цветов
		UINT oldtime=GetTickCount();
	 	CUIntArray red_pix, green_pix, blue_pix, ind_x, ind_y;
		int indx=0;
		UINT oldSumOtkl=10000000;
	 	for (int ii=0; ii< this2->pix_sxx; ii++){
	 	for (int jj=0; jj< this2->pix_syy; jj++)
	 	{
	 		indx=ii+jj*this2->pix_sxx;
			//игнорируем вырезанный пиксель
			if (!bgr_pix[indx].pad)
				continue;
	// 		//делаем матрицу из неодинаковых цветов, 
			//чтобы ускорить поиск
	 		if (ind_x.GetSize()>NumFKar-1)//берем 20 пикселей
			{
				break;
			}
	 		if (ii==0 && jj==0) //угловой пиксель не берем в расчет
			{
				continue;
			}
	 		if (bgr_pix[indx].r!=bgr_pix[0].r || 
	 			bgr_pix[indx].g!=bgr_pix[0].g || 
				bgr_pix[indx].b!=bgr_pix[0].b)
	 		{
	 			bool razr=1;
	 			for (int kk=0; kk<ind_x.GetSize(); kk++)
	 			{
	 				int newind=ind_x[kk]+ind_y[kk]*this2->pix_sxx;
					if (newind>=this2->pix_sxx*this2->pix_syy)
					{
	 					razr=0;
						break;
					}
	 				if (bgr_pix[indx].r!=bgr_pix[newind].r) 
	 				if (bgr_pix[indx].g!=bgr_pix[newind].g) 
	 				if (bgr_pix[indx].b!=bgr_pix[newind].b) 
	 				{
	 					razr=0;
						break;
	 				}
	 			}
	 			if (razr)
	 			{
	 				ind_x.Add(ii);
	 				ind_y.Add(jj);
	 			}
	 		}
	 	}
	 	}
	//	e_dib2.PasteDC( &DCFromFile, 0, 0, this2->pix_sxx, this2->pix_syy);
	 	if (ind_x.GetSize()==0)
	 	{
	 		ind_x.Add(1);
	 		ind_y.Add(1);
	 	}

		int pix1_x=0;
		int pix1_y=0;
		int pix2_x=rec_desk.Width ()-this2->pix_sxx;
		int pix2_y=rec_desk.Height()-this2->pix_syy;
		switch(gSC.typeSear[cur_picter])
		{
		case (1):
			{	//поиск по прямоугольнику + иногда по всему экрану
				if (numsear==8 || numsear==2)  
				{	//границы остаются по всему экрану
					numsear=numsear;
				} else {
					pix1_x=gSC.xl[cur_picter];
					if (pix1_x>rec_desk.Width ()-this2->pix_sxx)
						pix1_x=rec_desk.Width ()-this2->pix_sxx;
					pix1_y=gSC.yt[cur_picter];
					if (pix1_y>rec_desk.Height()-this2->pix_syy)
						pix1_y=rec_desk.Height()-this2->pix_syy;
					pix2_x=gSC.xr[cur_picter];
					if (pix2_x>rec_desk.Width ()-this2->pix_sxx)
						pix2_x=rec_desk.Width ()-this2->pix_sxx;
					pix2_y=gSC.yb[cur_picter];
					if (pix2_y>rec_desk.Height()-this2->pix_syy)
						pix2_y=rec_desk.Height()-this2->pix_syy;
				}			
			}
			break;
		case (2)://поиск только по прямоугольнику
			pix1_x=gSC.xl[cur_picter];
			if (pix1_x>rec_desk.Width ()-this2->pix_sxx)
				pix1_x=rec_desk.Width ()-this2->pix_sxx;
			pix1_y=gSC.yt[cur_picter];
			if (pix1_y>rec_desk.Height()-this2->pix_syy)
				pix1_y=rec_desk.Height()-this2->pix_syy;
			pix2_x=gSC.xr[cur_picter];
			if (pix2_x>rec_desk.Width ()-this2->pix_sxx)
				pix2_x=rec_desk.Width ()-this2->pix_sxx;
			pix2_y=gSC.yb[cur_picter];
			if (pix2_y>rec_desk.Height()-this2->pix_syy)
				pix2_y=rec_desk.Height()-this2->pix_syy;
			break;
		}
// #ifdef LOG 
// 		char deb[1024];
// 		sprintf(deb, "ищем в границах х1=%d x2=%d y1=%d y2=%d", pix1_x, pix2_x, pix1_y, pix2_y);
// 		this2->trif.RecordLog(deb);  
// #endif

		//поиск по картинке рабочего стола 
		for (int ii_desk=pix1_x; ii_desk<pix2_x; ii_desk++)
		{
			for (int jj_desk=pix1_y; jj_desk<pix2_y; jj_desk++)
			{
				if (stopShow && ii_desk<=rectS.right && ii_desk>=rectS.left &&
					jj_desk<=rectS.bottom && jj_desk>=rectS.top)
				{	//чтобы не искать картинку на окне "Останови Меня"
					continue;
				}
				//проверяем совпадение каркаса
				UINT SumOtklK=0;
				bool finded=1;
	 			int find_karkas=0;
	 			for (int kk=0; kk<ind_x.GetSize(); kk++)
	 			{
					int ind1=ind_x[kk]+ind_y[kk]*this2->pix_sxx;
					int ind2=ii_desk+ind_x[kk]+(jj_desk+ind_y[kk])*rec_desk.Width();
					int otkl=1000000;
					if (bgr_pix[ind1].r == bgr_desk[ind2].r)
					if (bgr_pix[ind1].g == bgr_desk[ind2].g)
					if (bgr_pix[ind1].b == bgr_desk[ind2].b) 
					{
			 			find_karkas++;
					}
					if (find_karkas!=kk+1)
					{
						if (!sOtk)
							break;
						otkl=abs(bgr_desk[ind2].r-bgr_pix[ind1].r)+
							 abs(bgr_desk[ind2].g-bgr_pix[ind1].g)+
							 abs(bgr_desk[ind2].b-bgr_pix[ind1].b);
						SumOtklK+=otkl;
						//множитель "3" дает запас для каркасного отклонения, так как 
						//среднее отклонение может потом вписываться в рамки разрешенного
						if ((float)SumOtklK/(float)NumFKar<15*this2->ColPerPix/*4*160*3*/)
							find_karkas++;
						if (find_karkas!=kk+1)
							break;
					}
	 			}

				//совпадение каркаса проверяем еще раз отклонение на пиксель (более строго)
				if ((float)SumOtklK/(float)NumFKar>3*this2->ColPerPix/*4*160*3*/)
					find_karkas--;
				if (find_karkas==ind_x.GetSize())
				{
					vhod++;
					finded=1;
					sovp=0;
					UINT SumOtkl=0;
					//UINT minotkl=0;
					for (int ii=0; ii< this2->pix_sxx; ii++)
					{
						for (int jj=0; jj< this2->pix_syy; jj++)
						{
							UINT ind1=ii+jj*this2->pix_sxx;
							if (!bgr_pix[ind1].pad)
								continue;
							UINT ind2=ii_desk+ii+(jj_desk+jj)*rec_desk.Width();
							UINT otkl=1000000;
							if (bgr_pix[ind1].r != bgr_desk[ind2].r
							||  bgr_pix[ind1].g != bgr_desk[ind2].g 
							||  bgr_pix[ind1].b != bgr_desk[ind2].b) 
							{
								finded=0;
								if (sOtk)
								{// считаем отклонение для текущей точки
									otkl=abs(bgr_desk[ind2].r-bgr_pix[ind1].r)+
										 abs(bgr_desk[ind2].g-bgr_pix[ind1].g)+
										 abs(bgr_desk[ind2].b-bgr_pix[ind1].b);
									SumOtkl+=otkl;
									if (SumOtkl>oldSumOtkl)
									{
										SumOtkl=0;
										break;
									}
								}
								//***сделать еще подсчет чисто фонового отклонения
								//потом для соседней
// 								if (ii_desk+ii-1<rec_desk.Width())
// 									otkl1=4*(abs(bgr_desk[ind2p1].r-bgr_pix[ind1].r)+
// 											 abs(bgr_desk[ind2p1].g-bgr_pix[ind1].g)+
// 											 abs(bgr_desk[ind2p1].b-bgr_pix[ind1].b)+10);
// 								if (ii_desk+ii>0)
// 									otkl2=4*(abs(bgr_desk[ind2m1].r-bgr_pix[ind1].r)+
// 											 abs(bgr_desk[ind2m1].g-bgr_pix[ind1].g)+
// 											 abs(bgr_desk[ind2m1].b-bgr_pix[ind1].b)+10);
// 								if (jj_desk+jj-1<rec_desk.Height())
// 									otkl3=4*(abs(bgr_desk[ind2d1].r-bgr_pix[ind1].r)+
// 											 abs(bgr_desk[ind2d1].g-bgr_pix[ind1].g)+
// 											 abs(bgr_desk[ind2d1].b-bgr_pix[ind1].b)+10);
// 								if (jj_desk+jj>0)
// 									otkl4=4*(abs(bgr_desk[ind2u1].r-bgr_pix[ind1].r)+
// 											 abs(bgr_desk[ind2u1].g-bgr_pix[ind1].g)+
// 											 abs(bgr_desk[ind2u1].b-bgr_pix[ind1].b)+10);
								//minotkl=otkl;//min(min(otkl1, otkl2), min(otkl3, otkl4));
							}
							sovp++;
						}
						if (!finded && !SumOtkl)
							break;
					}
					if (sOtk && SumOtkl && SumOtkl<oldSumOtkl)
					{
//						if (ii_desk>400)
						oldSumOtkl=SumOtkl;
						iotk=ii_desk;
						jotk=jj_desk;
					}
					if (sovp>Max_sovp) Max_sovp=sovp;
					if (finded)
					{
						//НАШЛИ КАРТИНКУ 
						//ССХРАНЯЕМ МАССИВ BMP
						if (sEndCutRect.GetSize()>cur_picter)
						for (UINT ll=sBegCutRect[cur_picter]; ll<sEndCutRect[cur_picter]; ll++)
						{
							CString forSave=this2->trif.ExtractPath(gSC.saPixContr[cur_picter+1])+"\\"+SaveBmps[ll];
							CDibExt e_dib_desk;
// 							CDC *pDC = GetDC(); //получаем контекст
							e_dib_desk.PasteDC( pDesktopDC, SaveRects[ll].left+ii_desk, 
								SaveRects[ll].top+jj_desk, SaveRects[ll].Width(), SaveRects[ll].Height());
#ifdef LOG 
							char sdeb[1024]; sprintf(sdeb, "НАШЛИ КАРТИНКУ точно ii_desk=%d jj_desk=%d", ii_desk, jj_desk); this2->trif.RecordLog(sdeb);
#endif
							this2->trif.SaveBitmap((HBITMAP)e_dib_desk.m_Bitmap, forSave);
						}

						this2->com_time=(::GetTickCount())-this2->com_time;
						this2->MinOtk=SumOtkl/this2->pix_sxx/(float)this2->pix_syy;
						this2->fi_coorx=ii_desk;
						this2->fi_coory=jj_desk;
						this2->trif.BlinkRectangle(ii_desk, jj_desk, 
							ii_desk+this2->pix_sxx, jj_desk+this2->pix_syy, this2->SpeedPlay);

						this2->PictIsFi=true;
						this2->num_find_bmp=cur_picter;
						this2->ForPlayAip="";
						if (gSC.saPlayAip.GetSize()>cur_picter+1)
							this2->ForPlayAip=gSC.saPlayAip[cur_picter+1];
						break;
					}
				}
			}
			if (this2->PictIsFi)
				break;
		}

		//проверяем минимальное отклонение
		if (sOtk && oldSumOtkl/this2->pix_sxx/this2->pix_syy<this2->ColPerPix 
			&& !this2->PictIsFi)
		{
			//НАШЛИ КАРТИНКУ с отклонением
			//ССХРАНЯЕМ МАССИВ BMP
			if (sEndCutRect.GetSize()>cur_picter)
				for (UINT ll=sBegCutRect[cur_picter]; ll<sEndCutRect[cur_picter]; ll++)
				{
					CString forSave=this2->trif.ExtractPath(gSC.saPixContr[cur_picter+1])+"\\"+SaveBmps[ll];
					CDibExt e_dib_desk;
					// 							CDC *pDC = GetDC(); //получаем контекст
// 					e_dib_desk.PasteDC( pDesktopDC, 0/*SaveRects[ll].left+ii_desk*/, 
// 						0/*SaveRects[ll].top+jj_desk*/, 500/*SaveRects[ll].Width()*/, 500/*SaveRects[ll].Height()*/);
					e_dib_desk.PasteDC( pDesktopDC, SaveRects[ll].left+iotk, 
						SaveRects[ll].top+jotk, SaveRects[ll].Width(), SaveRects[ll].Height());
#ifdef LOG 
					char sdeb[1024]; sprintf(sdeb, "НАШЛИ КАРТИНКУ с отклонением ii_desk=%d jj_desk=%d", iotk, jotk); this2->trif.RecordLog(sdeb);
#endif
					this2->trif.SaveBitmap((HBITMAP)e_dib_desk.m_Bitmap, forSave);
				}

			this2->com_time=(::GetTickCount())-this2->com_time;
			this2->MinOtk=(float)oldSumOtkl/(float)this2->pix_sxx/(float)this2->pix_syy;
			this2->fi_coorx=iotk;
			this2->fi_coory=jotk;

			this2->trif.BlinkRectangle(iotk, jotk, 
				iotk+this2->pix_sxx, jotk+this2->pix_syy, this2->SpeedPlay);


			this2->PictIsFi=true;
			this2->num_find_bmp=cur_picter;
			this2->ForPlayAip="";
			if (gSC.saPlayAip.GetSize()>cur_picter+1)
				this2->ForPlayAip=gSC.saPlayAip[cur_picter+1];
			if (this2->PictIsFi)
				break;
		}

		//при совпадении красным прямоугольником обрамляем
		//чистим ресурсы
		if (bgr_pix)
		{
			delete bgr_pix;
			bgr_pix=NULL;
		}

		if (this2->PictIsFi)
			break;
	}
	#ifdef LOG 
	char debch[1024];
	sprintf(debch, "%06d после for (int ps=0; ; ps++)", (::GetTickCount()-lastTime));
	this2->trif.RecordLog(debch);  
	#endif
	if (bgr_desk)
	{
		delete bgr_desk;
		bgr_desk=NULL;
	}

	for (int i_bmp=0; i_bmp<bit.GetSize(); i_bmp++)
	{
			bit[i_bmp].DeleteObject();
	}
	ReleaseDC(0, pDesktopDC->m_hDC);
	ReleaseDC(0, DCFromFile.m_hDC);
	pDesktopDC->DeleteDC();
	DCFromFile.DeleteDC();
	this2->zap_thread=false;
	this2->exit_cikl=true;
	DeleteObject(tmpDC);
	DeleteObject(tmpDC2);
	DeleteObject(desk_cdc);
	return 1;
}

// UINT SearchKarkasR(LPVOID pParam)
// {
// 	char ch[1024];
// 	#ifdef LOG 
// 	this2->trif.RecordLog("ParallelSearch");  
// 	#endif
// 	UINT begin_time=GetTickCount(), cictime=0;
// 	int Max_sovp=0, sovp=0, vhod=0;
// 	CDC *pDesktopDC;
// 	HDC tmpDC;
// 	tmpDC=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 	CDC *pDesktopDC33=CDC::FromHandle (tmpDC);
// 	//CDC *pDesktopDC2=CDC::FromHandle (::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE));
// 	CDC *pDesktopDC2=CDC::FromHandle (::GetDC(GetDesktopWindow()));
// 	CDC DCFromFile;
// 	//CDibExt e_dib1;
// 	//CDibExt e_dib2;
// 	MyBitAr bit;
// 	BITMAP m_bmInfo2;
// 	CBitmap *pOldBmp;
// 	if (file_kusok_bmp.GetSize()<2)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("return 0 file_kusok_bmp.GetSize()<2");  
// 		#endif
// 		this2->zap_thread=false;
// 		DeleteObject(tmpDC);
// 		return 0;
// 	}
// 	bit.SetSize(file_kusok_bmp.GetSize()-1);
// 	bool loadedbmp=false;
// 	int nonLoadBit=0;//для учета незагруженных картинок
// 	for (int i_bmp=1; i_bmp<file_kusok_bmp.GetSize(); i_bmp++)
// 	{
// 		//загружаем битмапы из файла
// 		if (!file_kusok_bmp[i_bmp].IsEmpty())
// 		if (!bit[i_bmp-1-nonLoadBit].Attach(LoadImage(0, file_kusok_bmp[i_bmp] ,
// 			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)))
// 		{
// 			#ifdef LOG 
// 			char deb[1024];
// 			sprintf(deb, "не загружена картинка bit[%d-1-%d].Attach", i_bmp, nonLoadBit);
// 			this2->trif.RecordLog(deb);  
// 			#endif
// 			bit.RemoveAt(i_bmp-1-nonLoadBit);
// 			nonLoadBit++;
// 		} else {
// 			loadedbmp=true;
// 		}
// 	}
// 	if (!loadedbmp)
// 	{
// 		this2->zap_thread=false;
// 		DeleteObject(tmpDC);
// 		return 0;
// 	}
// 	HDC desk_cdc= ::GetDC(::GetDesktopWindow());
// 	//HDC desk_cdc2=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 	if (!desk_cdc)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("Повторно GetDCEx");  
// 		#endif
// 		Sleep(10);
// 		//desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 		desk_cdc=::GetDC(GetDesktopWindow());
// 	}
// 	if (!desk_cdc)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("!!!НЕудача GetDCEx - выходим");  
// 		#endif
// 		this2->zap_thread=false;
// 		DeleteObject(tmpDC);
// 		return 0;
// 	}
// 	//берем рабочий стол
// 	pDesktopDC = CDC::FromHandle (desk_cdc);
// 	if (!pDesktopDC)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("повторно CDC::FromHandle");  
// 		#endif
// 		Sleep(10);
// 		pDesktopDC = CDC::FromHandle(desk_cdc);
// 	}
// 	if (!pDesktopDC)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("повторно CDC::FromHandle");  
// 		#endif
// 		Sleep(10);
// 		pDesktopDC = CDC::FromHandle(desk_cdc);
// 	}
// 	if (!pDesktopDC)
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("!!!НЕудача CDC::FromHandle");  
// 		#endif
// 		this2->zap_thread=false;
// 		DeleteObject(tmpDC);
// 		return 0;
// 	}
// 
// 	//создаем совместимый с ним контекст для файла
// 	if (!DCFromFile.CreateCompatibleDC(pDesktopDC))
// 	{
// 		#ifdef LOG 
// 		this2->trif.RecordLog("облом DCFromFile.CreateCompatibleDC");  
// 		#endif
// 		ReleaseDC(0, pDesktopDC->m_hDC);
// 		this2->zap_thread=false;
// 		DeleteObject(tmpDC);
// 		return 0;
// 	}
// 	CRect rec_desk;
// 	pBGR bgr_desk=NULL;
// 	//bool need_del_desk=false;
// 	::GetWindowRect(pDesktopDC->GetWindow()->GetSafeHwnd(), rec_desk);
// 	UINT oldtim=GetCurrentTime();
// 	UINT oldtim2=GetCurrentTime();
// 	#ifdef LOG 
// 	this2->trif.RecordLog("перед for (int ps=0; ; ps++)");  
// 	#endif
// 	for (int ps=0; ps<1; ps++)
// 	{
// 		pBGR bgr_pix=NULL;
// 		int cur_picter;
// 		if (this2->randVetv)
// 		{
// 			cur_picter = (rand()+GetTickCount()) % bit.GetSize();
// 		} else {
// 			cur_picter = ps % (bit.GetSize());
// 		}
// 		if (!(ps % (bit.GetSize())))
// 		{
// 			if (ps)
// 			{
// 				ReleaseDC(0, pDesktopDC->m_hDC);
// 				delete bgr_desk;
// 				bgr_desk=NULL;
// 			}
// 			if (this2->stop_sear && ps)
// 			{
// 				if (bgr_pix)
// 				{
// 					delete bgr_pix;
// 					bgr_pix=NULL;
// 				}
// 				break;
// 			}
// 			if (GetCurrentTime()-oldtim2 >10000)
// 			{
// 				oldtim2=GetCurrentTime();
// 				::RedrawWindow(0, rec_desk, 0, RDW_FRAME|RDW_INVALIDATE|RDW_ALLCHILDREN|RDW_NOINTERNALPAINT);
// 				Sleep(10);
// 			}
// 			//3 раза пробуем контекст устройства взять
// 			HDC desk_cdc=::GetDC(GetDesktopWindow());
// 			//HDC desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 			if (!desk_cdc)
// 			{
// 				#ifdef LOG 
// 				this2->trif.RecordLog("Повторно GetDCEx");  
// 				#endif
// 				Sleep(10);
// 				desk_cdc=::GetDC(GetDesktopWindow());
// 				//desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 			}
// 			if (!desk_cdc)
// 			{
// 				#ifdef LOG 
// 				this2->trif.RecordLog("Повторно GetDCEx");  
// 				#endif
// 				Sleep(10);
// 				desk_cdc=::GetDC(GetDesktopWindow());
// 				//desk_cdc=::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
// 			}
// 			if (!desk_cdc)
// 			{
// 				#ifdef LOG 
// 				this2->trif.RecordLog("!!!НЕудача GetDCEx - выходим");  
// 				#endif
// 				this2->zap_thread=false;
// 				DeleteObject(tmpDC);
// 				return 0;
// 			}
// 			pDesktopDC = CDC::FromHandle(desk_cdc);
// 			if (!pDesktopDC)
// 			{
// 				Sleep(10);
// 				pDesktopDC = CDC::FromHandle(desk_cdc);
// 			}
// 			if (!pDesktopDC)
// 			{
// 				Sleep(10);
// 				pDesktopDC = CDC::FromHandle(desk_cdc);
// 			}
// 			if (!pDesktopDC)
// 			{
// 				#ifdef LOG 
// 				this2->trif.RecordLog("!!!НЕудача CDC::FromHandle");  
// 				#endif
// 				this2->zap_thread=false;
// 				DeleteObject(tmpDC);
// 				return 0;
// 			}
// 			bgr_desk = MyGetDibBits(pDesktopDC, rec_desk.Width(), rec_desk.Height());
// 			UINT deltatim=GetCurrentTime()-oldtim;
// 			if ((deltatim)>2000)
// 			{
// 				if (deltatim>25000)
// 					deltatim=25000;
// 				Sleep(deltatim/50);
// 			}
// 		}
// 
// 		//** засунуть в массивы для более редкого вызова
// 		GetObject( bit[cur_picter].GetSafeHandle(), sizeof(BITMAP), &m_bmInfo2 );
//  		int pix_sxx=m_bmInfo2.bmWidth, 
//  			pix_syy=m_bmInfo2.bmHeight;
// 		pOldBmp = DCFromFile.SelectObject(&bit[cur_picter]); //закидываем в контекст
// 		bgr_pix = MyGetDibBits(&DCFromFile, pix_sxx, pix_syy);
// 		if (bgr_pix == NULL)
// 		{
// 			this2->zap_thread=false;
// 			DeleteObject(tmpDC);
// 			return 0;
// 		}
// 		DCFromFile.SelectObject(pOldBmp);
// 		//считаем суммарный диффернциал слева направо
// 		UINT oldtime=GetTickCount();
// 	 	CUIntArray red_pix, green_pix, blue_pix, ind_x, ind_y;
// 		int indx=0;
// 		int grad1=0;
// 		int SumG1=0;
// 		int grad2=0;
// 		int SumG2=0;
// 	 	for (int ii=0; ii< pix_sxx-1; ii++)
// 	 	for (int jj=0; jj< pix_syy-1; jj++)
// 	 	{
// 	 		indx=ii+jj*pix_sxx;
// 			grad1=bgr_pix[indx+1].r-bgr_pix[indx].r;
// 			if (grad1<0)
// 				grad1=-grad1;
// 			SumG1+=grad1;
// 			grad2=bgr_pix[indx+pix_sxx].r-bgr_pix[indx].r;
// 			if (grad2<0)
// 				grad2=-grad2;
// 			SumG2+=grad2;
// 	 	}
// 	//	e_dib2.PasteDC( &DCFromFile, 0, 0, pix_sxx, pix_syy);
// 	 	if (ind_x.GetSize()==0)
// 	 	{
// 	 		ind_x.Add(1);
// 	 		ind_y.Add(1);
// 	 	}
// 
// 		//определяем границы поиска
// 		int pix1_x=0;
// 		int pix1_y=0;
// 		int pix2_x=rec_desk.Width ()-pix_sxx;
// 		int pix2_y=rec_desk.Height()-pix_syy;
// 		switch(gtypeSear[cur_picter])
// 		{
// 		case (1):
// 			{
// 				int numsear=(ps % (file_kusok_bmp.GetSize()*20)) / file_kusok_bmp.GetSize();
// 				if (numsear!=19)  
// 				{
// 					pix1_x=gSC.xl[cur_picter];
// 					if (pix1_x>rec_desk.Width ()-pix_sxx)
// 						pix1_x=rec_desk.Width ()-pix_sxx;
// 					pix1_y=gSC.yb[cur_picter];
// 					if (pix1_y>rec_desk.Height()-pix_syy)
// 						pix1_y=rec_desk.Height()-pix_syy;
// 					pix2_x=gSC.xr[cur_picter];
// 					if (pix2_x>rec_desk.Width ()-pix_sxx)
// 						pix2_x=rec_desk.Width ()-pix_sxx;
// 					pix2_y=gSC.yt[cur_picter];
// 					if (pix2_y>rec_desk.Height()-pix_syy)
// 						pix2_y=rec_desk.Height()-pix_syy;
// 				}			
// 			}
// 			break;
// 		case (2):
// 			pix1_x=gSC.xl[cur_picter];
// 			if (pix1_x>rec_desk.Width ()-pix_sxx)
// 				pix1_x=rec_desk.Width ()-pix_sxx;
// 			pix1_y=gSC.yb[cur_picter];
// 			if (pix1_y>rec_desk.Height()-pix_syy)
// 				pix1_y=rec_desk.Height()-pix_syy;
// 			pix2_x=gSC.xr[cur_picter];
// 			if (pix2_x>rec_desk.Width ()-pix_sxx)
// 				pix2_x=rec_desk.Width ()-pix_sxx;
// 			pix2_y=gSC.yt[cur_picter];
// 			if (pix2_y>rec_desk.Height()-pix_syy)
// 				pix2_y=rec_desk.Height()-pix_syy;
// 			break;
// 		}
// 		
// 		for (int ii_desk=pix1_x; ii_desk<pix2_x; ii_desk++)
// 		{
// 			for (int jj_desk=pix1_y; jj_desk<pix2_y; jj_desk++)
// 			{
// 	// 			if (GetTickCount() % 1000 == 0)
// 	// 				pDesktopDC = CWnd::GetDesktopWindow()->GetDC();
// 				
// 				bool finded=1;
// 				vhod++;
// 				finded=1;
// 				sovp=0;
// 				int loc_grad1=0;
// 				int loc_SumG1=0;
// 				int loc_grad2=0;
// 				int loc_SumG2=0;
// 				for (int ii=0; ii< pix_sxx-1; ii++)
// 				{
// 					for (int jj=0; jj< pix_syy; jj++)
// 					{
// 						//int ind1=ii+jj*pix_sxx;
// 						int ind2=ii_desk+ii+(jj_desk+jj)*rec_desk.Width();
// 						loc_grad1=bgr_desk[ind2+1].r-bgr_desk[ind2].r;
// 						if (loc_grad1<0)
// 							loc_grad1=-loc_grad1;
// 						loc_SumG1+=loc_grad1;
// 
// 						loc_grad2=bgr_desk[ind2+rec_desk.Width()].r-bgr_desk[ind2].r;
// 						if (loc_grad2<0)
// 							loc_grad2=-loc_grad2;
// 						loc_SumG2+=loc_grad2;
// 					}
// 				}
// 				if (sovp>Max_sovp) Max_sovp=sovp;
// 
// 				loc_grad1=loc_SumG1-SumG1;
// 				if (loc_grad1<0)
// 					loc_grad1=-loc_grad1;
// 				float fl1=(float)loc_SumG1/(SumG1);
// 
// 				loc_grad2=loc_SumG2-SumG2;
// 				if (loc_grad2<0)
// 					loc_grad2=-loc_grad2;
// 				float fl2=(float)loc_SumG2/(SumG2);
// 				sprintf(ch, "sovp1=%.4f SumG1=%d SumGloc1=%d sovp2=%.4f SumG2=%d SumGloc2=%d", 
// 					fl1, SumG1, loc_SumG1, fl2, SumG2, loc_SumG2);
// 				if (fl1>0.999 && fl1<1.001 && fl2>0.999 && fl2<1.001)
// 				{
// 					pDesktopDC2->TextOut(400, 25, ch);
// 					CPoint pt1=CPoint(ii_desk, jj_desk);
// 					CPoint pt2=CPoint(ii_desk+pix_sxx, jj_desk+pix_syy);
// 					this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 					this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 					this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 					this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 				}
// 				if (101<100)
// 				{
// 					this2->fi_coorx=ii_desk;
// 					this2->fi_coory=jj_desk;
// 					CPoint pt1=CPoint(ii_desk, jj_desk);
// 					CPoint pt2=CPoint(ii_desk+pix_sxx, jj_desk+pix_syy);
// 					int paus_interv=50-10*this2->SpeedPlay;
// 					if (paus_interv<=0) paus_interv=0;
// 					pt1.x-=50;
// 					pt2.x+=50;
// 					pt1.y-=50;
// 					pt2.y+=50;
// 					this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 					this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 					if (paus_interv)
// 						Sleep(paus_interv*2);
// 					this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 					this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 					for (int ind=0; ind<5; ind++)
// 					{
// 						if (paus_interv)
// 							Sleep(paus_interv);
// 						pt1.x+=10;
// 						pt2.x-=10;
// 						pt1.y+=10;
// 						pt2.y-=10;
// 						this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 						this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 						if (paus_interv)
// 							Sleep(paus_interv*2);
// 						this2->InvertRectLine(pDesktopDC33, pt1, pt2);
// 						this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
// 					}
// 					this2->PictIsFi=true;
// 					this2->num_find_bmp=cur_picter;
// 					break;
// 				}
// 			}
// 			if (this2->PictIsFi)
// 				break;
// 		}
// 
// 
// 		//AfxMessageBox(ch);
// 		//при совпадении красным прямоугольником обрамляем
// 		//чистим ресурсы
// 	//	char ch[1024];
// 		//ReleaseDC(DCFromFile);
// 		//ReleaseDC(pDesktopDC);
// 		if (bgr_pix)
// 		{
// 			delete bgr_pix;
// 			bgr_pix=NULL;
// 		}
// 
// 		if (this2->PictIsFi)
// 			break;
// 	}
// 	#ifdef LOG 
// 	this2->trif.RecordLog("после for (int ps=0; ; ps++)");  
// 	#endif
// 	if (bgr_desk)
// 	{
// 		delete bgr_desk;
// 		bgr_desk=NULL;
// 	}
// 
// 	for (i_bmp=0; i_bmp<bit.GetSize(); i_bmp++)
// 	{
// 			bit[i_bmp].DeleteObject();
// 	}
// 	ReleaseDC(0, pDesktopDC->m_hDC);
// 	ReleaseDC(0, DCFromFile.m_hDC);
// 	pDesktopDC->DeleteDC();
// 	DCFromFile.DeleteDC();
// 	this2->zap_thread=false;
// 	this2->exit_cikl=true;
// 	DeleteObject(tmpDC);
// 	return 1;
// }

bool CWinWork::StrToCrects(CString &OBJ, MyCRectAr &CutRects, MyCRectAr &SaveRects, CStringArray &SaveBmps)
{
	int fi=OBJ.Find("\n");
	CString tmp;
	if (fi>-1)
		tmp=OBJ.Left(fi);
	else if (OBJ.GetLength()>0)
	{
		tmp=OBJ;
		OBJ="";
		fi=0;
	}
	while (fi>-1)
	{
		CRect rectFor;
		tmp.TrimLeft(" ");
		tmp.TrimLeft("\t");
		if (tmp.Left(5)=="cute(")
		{
			tmp.Delete(0, 5);

			fi =tmp.Find(",");
			int dig=tmp.Left(fi).FindOneOf("-0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			rectFor.left=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("-0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			rectFor.right=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("-0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			rectFor.top=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			dig=tmp.FindOneOf("-0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			rectFor.bottom=atoi(tmp);
// 			fi=tmp.Find(",");
// 			tmp.Delete(0, fi+1);

			CutRects.Add(rectFor);
		} else
		if (tmp.Left(5)=="save(")
		{
			tmp.Delete(0, 5);

			fi =tmp.Find("\"");
			tmp.Delete(0, fi+1);
			SaveBmps.Add(tmp.Left(tmp.Find("\"")));
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			

			fi =tmp.Find(",");
			int dig=tmp.Left(fi).FindOneOf("-0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			rectFor.left=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("-0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			rectFor.right=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("-0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			rectFor.top=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			dig=tmp.FindOneOf("-0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			rectFor.bottom=atoi(tmp);

			SaveRects.Add(rectFor);
		}
		fi=OBJ.Find("\n");
		OBJ.TrimLeft("\n");
		if (fi==-1)
		{
			if (OBJ.GetLength()>0)
			{
				tmp=OBJ;
				fi=0;
				OBJ="";
			}
		} else {
			tmp=OBJ.Left(fi);
			OBJ.Delete(0, fi+1);
		}
	}
	return true;
}

UINT CWinWork::StopSearch()
{
	if (zap_thread)
	{
		ThreadSearchPix->SuspendThread();
		ThreadSearchPix->ExitInstance();
		zap_thread=0;
	}
	return 1;
}

bool CWinWork::KeysToMes(CString &keys, CUIntArray &Mess)
{
	return false;
}

bool CWinWork::ComsToKey(CStringArray &coms, forKeyPress &SC)
{
	return false;
}

bool CWinWork::ComsToMouse(CStringArray &coms, forMousePress &SC)
{
	return false;
}

bool CWinWork::ComsToSC(CStringArray &coms, sSmartControl_tmp &SC, CString pathSC)
{
	CString tmp, tmp2; int fi, dig;
	for (int ii=0; ii<coms.GetSize(); ii++)
	{
		tmp=coms[ii];
		tmp.TrimLeft("\t");
		tmp.TrimLeft(" ");
		//заголовок Пиксельного Контроля
		if (tmp.Left(13)=="PixelControl(")
		{
			tmp.Delete(0, 13);
			fi=tmp.Find(",");
			if (fi==-1)
				return false;
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.time_search=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);

			fi=tmp.Find(",");
			if (fi==-1)
				return false;
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.otk_s=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);

			fi=tmp.Find(",");
			if (fi==-1)
				return false;
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.razrPlay=atoi(tmp);
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);

			fi=tmp.Find(",");
			if (fi==-1)
				return false;
			dig=tmp.Left(fi).Find("\"");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig+1);
			SC.ProvPlayAip=tmp.Left(tmp.Find("\""));
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);

			fi=tmp.Find(",");
			if (fi==-1)
				return false;
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			if (atoi(tmp))
				SC.hideSM=0;
			else SC.hideSM=1;
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);
			
			fi=tmp.Find(")");
			if (fi==-1)
				return false;
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.randVetv=atoi(tmp);
			fi=tmp.Find(")");
			if (fi==-1)
				return false;
			tmp.Delete(0, fi+1);

			SC.saPixContr.RemoveAll();
			SC.saPixContr.Add(pathSC);
			
			SC.clickx.RemoveAll();
			SC.clicky.RemoveAll();
			SC.Rx.RemoveAll();
			SC.Ry.RemoveAll();
			SC.typeClick.RemoveAll();
			SC.typeSear.RemoveAll();
			SC.xl.RemoveAll();
			SC.xr.RemoveAll();
			SC.yt.RemoveAll();
			SC.yb.RemoveAll();
			SC.nodPicRpl.RemoveAll();
			continue;
		}
		//параметры поисков отдельных картинок
		if (tmp.Left(6)=="Find(\"")
		{
			tmp.Delete(0, 6);
			//tmp.Replace("NoClick(ffx+(xx=0), Rx=0, ffy+(yy=0), Ry=0)", "NoClick");

			fi=tmp.Find("\",");
			if (fi==-1)
				return false;
			SC.saPixContr.Add(tmp.Left(fi));
			tmp.Delete(0, fi+2);
			
			fi =tmp.Find(",");
			dig=tmp.Find("(");
			bool ncskob=false;
			if (dig!=-1 && fi!=-1 && fi>dig)
			{
				fi=dig;
				ncskob=true;
			}
			if (fi==-1)
				return false;
			tmp2=tmp.Left(fi);
			int dig=trif.GetTypeClickFromStr(tmp2);
			if (dig==-1)
				return false;
			SC.typeClick.Add(dig);
			tmp.Delete(0, fi+1);
// 			if (!dig && ncskob)
// 			{	//предотвращение NoClick с потрохами
// 				tmp.Delete(0, tmp.Find("TypeSearch="));
// 			}

			if (dig>0 || (!dig && ncskob))
			{	//параметры кликов вычисляем
				fi =tmp.Find(",");
				dig=tmp.Left(fi).FindOneOf("-0123456789");
				if (dig==-1)
					return false;
				tmp.Delete(0, dig);
				SC.clickx.Add(atoi(tmp));
				fi=tmp.Find(",");
				tmp.Delete(0, fi+1);			

				fi =tmp.Find(",");
				dig=tmp.Left(fi).FindOneOf("0123456789");
				if (dig==-1)
					return false;
				tmp.Delete(0, dig);
				SC.Rx.Add(atoi(tmp));
				fi=tmp.Find(",");
				tmp.Delete(0, fi+1);			

				fi =tmp.Find(",");
				dig=tmp.Left(fi).FindOneOf("-0123456789");
				if (dig==-1)
					return false;
				tmp.Delete(0, dig);
				SC.clicky.Add(atoi(tmp));
				fi=tmp.Find(",");
				tmp.Delete(0, fi+1);			

				fi =tmp.Find(",");
				dig=tmp.Left(fi).FindOneOf("0123456789");
				if (dig==-1)
					return false;
				tmp.Delete(0, dig);
				SC.Ry.Add(atoi(tmp));
				fi=tmp.Find(",");
				dig=tmp.Find(")");
				if (dig==-1 || dig>fi)
					return false;
				tmp.Delete(0, fi+1);			
				
			} else {
				SC.clickx.Add(0);
				SC.clicky.Add(0);
				SC.Rx.Add(0);
				SC.Ry.Add(0);
			}
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.typeSear.Add(atoi(tmp));
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(",");
			dig=tmp.Find("RectSearch");
			if (dig==-1 || dig>fi)
				return false;
			tmp.Delete(0, dig+10);
			
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.xl.Add(atoi(tmp));
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.xr.Add(atoi(tmp));
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.yt.Add(atoi(tmp));
			fi=tmp.Find(",");
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(",");
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.yb.Add(atoi(tmp));
			fi=tmp.Find(",");
			dig=tmp.Find(")");
			if (dig==-1 || dig>fi)
				return false;
			tmp.Delete(0, fi+1);			
			
			fi =tmp.Find(")");
			dig=tmp.Left(fi).FindOneOf("0123456789");
			if (dig==-1)
				return false;
			tmp.Delete(0, dig);
			SC.nodPicRpl.Add(atoi(tmp));
			fi=tmp.Find(",");
			if (fi>-1)
				tmp.Delete(0, fi+1);			

			//что воспроизводить в случае нахождения картинки
			fi=tmp.Find(")");
// 			if (fi==-1)
// 				return false;
			dig=tmp.Left(fi).Find("\"");
			if (dig>-1)
			{
				tmp.Delete(0, dig+1);
				SC.saPlayAip.SetSize(SC.typeClick.GetSize()+1);
				SC.saPlayAip[SC.typeClick.GetSize()]= tmp.Left(tmp.Find("\""));
			}

			continue;
		}
		if (tmp.Left(5)=="cute(" || tmp.Left(5)=="save(")
		{
			int indObj=SC.typeClick.GetSize()-1;
			while (SC.OBJs.GetSize()<indObj+1)
			{
				SC.OBJs.Add("");
			}
			if (SC.OBJs[indObj].IsEmpty())
				SC.OBJs[indObj]+=tmp;
			else SC.OBJs[indObj]+="\n"+tmp;
			continue;
		}
		if (tmp.Left(13)=="SetVarialble:")
		{
			tmp.Delete(0, 13);
			tmp.Replace("$(_._&)", "\n");
			SC.saVarsOpers.Add(tmp);
			continue;
		}
		bool start=false;
		if (tmp.Left(7)=="START:\"")
		{
			SC.siApps.Add(0);
			tmp.Delete(0, 7);
			start=true;
		}
		if (tmp.Left(20)=="WaitForTerminating:\"")
		{
			SC.siApps.Add(1);
			tmp.Delete(0, 20);
			start=true;
		}
		if (tmp.Left(28)=="StartAndWaitForTerminating:\"")
		{
			SC.siApps.Add(2);
			tmp.Delete(0, 28);
			start=true;
		}
		if (start)
		{
			fi=tmp.Find("\"");
			SC.saApps.Add(tmp.Left(fi));
			tmp.Delete(0, fi+1);
			fi=tmp.Find(" ComLine=\"");
			if (fi==0)
			{
				tmp.Delete(0, fi+10);
				dig=tmp.Find("\"");//правая граница параметров ком. строки
				while (dig>0 && tmp.Find("\\", dig-1)+1==dig)
				{//кавычки, включаемые в ком. строку разрешаем
					int dig2=tmp.Find("\"", dig+1);
					if (dig2==-1)
						break;
					dig=dig2;
				}
				tmp2=tmp.Left(dig);
				tmp2.Replace("\\\"", "\"");
				SC.saParComLine.Add(tmp2);
			} else {
				fi=tmp.Find("&(\"\"\"");
				if (fi>-1)
				{
					tmp.Delete(0, fi+5);
					SC.saParComLine.Add(tmp.Left(tmp.Find("\"\"\")&")));
				}
				else 
					SC.saParComLine.Add("");
			}
			continue;
		}
		if (tmp.Left(12)=="BlockIfElse:")
		{
			SC.ifElse=tmp.Mid(13);
		}
	}
	return true;
}

//клавишное действие переводим в строку
// bool CWinWork::KeyToComs(forKeyPress &key, CStringArray &coms)
// {
// 	coms.RemoveAll();
// 	//шаблон заголовка клавишного действия
// 	char shabPCcapt[]="	Send(\"%s\", lpar=\"%s\"), ";
// 	CString shab;
// 	shab.Format(shabPCcapt, key.keys, key.lpars);
// 	coms.Add(shab);
// 	return true;
// }
// 
bool CWinWork::SCToComs(sSmartControl_tmp &SC, CStringArray &coms)
{
	coms.RemoveAll();
	if (SC.saPixContr.GetSize()>1)
	{
		//шаблон заголовка Пиксельного Контроля
		char shabPCcapt[]="	PixelControl(st=%d, deviat=%d, NodeIfNotFinded=%d, AipIfFailPC=\"%s\", ShowStopMe=%d, RandNode=%d):";
		//шаблон параметров поиска отдельной картинки
		char shabPCpict[]="		Find(\"%s\", %s(ffx+(xx=%d), Rx=%d, ffy+(yy=%d), Ry=%d), TypeSearch=%d, RectSearch(xl=%d, xr=%d, yt=%d, yb=%d), Node=%d, StopAndReplay=\"%s\")";
		//шаблон редактирования отдельной картинки
		char shabPCobj[] ="%s(xl=%d, xr=%d, yt=%d, yb=%d)";
		CString shab;
		shab.Format(shabPCcapt, SC.time_search, SC.otk_s, 
			SC.razrPlay, SC.ProvPlayAip, (!SC.hideSM), SC.randVetv);
		coms.Add(shab);
		CString PlayAip="";
		if (SC.saPlayAip.GetSize()>1)
			PlayAip=SC.saPlayAip[1];
		shab.Format(shabPCpict, SC.saPixContr[0+1], trif.GetStrFromTypeClick(SC.typeClick[0]), 
			SC.clickx[0], SC.Rx[0], 
			SC.clicky[0], SC.Ry[0], SC.typeSear[0], 
			SC.xl[0], SC.xr[0], SC.yt[0], 
			SC.yb[0], SC.nodPicRpl[0], PlayAip);
		shab.Replace("NoClick(ffx+(xx=0), Rx=0, ffy+(yy=0), Ry=0)", "NoClick");
		coms.Add(shab);

		if (SC.OBJs.GetSize()>0)
		if (!SC.OBJs[0].IsEmpty())
		{
			CString forObj=SC.OBJs[0];
			int fi=forObj.Find("\n");
			while (fi>-1)
			{
				coms.Add(forObj.Left(fi));
				forObj.Delete(0, fi+1);
				fi=forObj.Find("\n");
			}
			if (!forObj.IsEmpty())
				coms.Add(forObj);
		}
		for (int ii=1; ii<SC.typeClick.GetSize(); ii++)
		{
			CString PlayAip="";
			if (SC.saPlayAip.GetSize()>ii+1)
				PlayAip=SC.saPlayAip[ii+1];
			shab.Format(shabPCpict, SC.saPixContr[ii+1], 
				trif.GetStrFromTypeClick(SC.typeClick[ii]), SC.clickx[ii], SC.Rx[ii], 
				SC.clicky[ii], SC.Ry[ii], SC.typeSear[ii], 
				SC.xl[ii], SC.xr[ii], SC.yt[ii], 
				SC.yb[ii], SC.nodPicRpl[ii], PlayAip);
			shab.Replace("NoClick(ffx+(xx=0), Rx=0, ffy+(yy=0), Ry=0)", "NoClick");
			coms.Add(shab);
			if (SC.OBJs.GetSize()>ii)
			if (!SC.OBJs[ii].IsEmpty())
			{
				CString forObj=SC.OBJs[ii];
				int fi=forObj.Find("\n");
				while (fi>-1)
				{
					coms.Add(forObj.Left(fi));
					forObj.Delete(0, fi+1);
					fi=forObj.Find("\n");
				}
				if (!forObj.IsEmpty())
					coms.Add(forObj);
			}
		}
	}

	for (int ii=0; ii<SC.saVarsOpers.GetSize(); ii++)
	{
		coms.Add("	SetVarialble:"+SC.saVarsOpers[ii]);
	}

	CString tmp;
	for (int ii=0; ii<SC.saApps.GetSize(); ii++)
	{
		tmp=SC.saParComLine[ii];
		tmp.Replace("\"", "\\\"");
		switch(SC.siApps[ii])
		{
		case 0:
			coms.Add("	START:\""+SC.saApps[ii]+"\" ComLine=\""+tmp+"\"");
			break;
		case 1:
			coms.Add("	WaitForTerminating:\""+SC.saApps[ii]+"\" ComLine=\""+tmp+"\"");
		    break;
		case 2:
			coms.Add("	StartAndWaitForTerminating:\""+SC.saApps[ii]+"\" ComLine=\""+tmp+"\"");
		    break;
		}
	}

	if (SC.ifElse.GetLength()>3)
	{
		coms.Add("	BlockIfElse: "+SC.ifElse);
	}

	if (!coms.GetSize())
		return false;
	return true;
}

//#include <winable.h>
UINT CWinWork::PlaySmart(CStringArray &coms, int speed, bool uvorot, HWND stopme, int UN, CString pathSC)
{
// #ifdef LOG 
// 	char debc[1024];	sprintf(debc, "PlaySmart time=%d clickx.size=%d clicky.size=%d", SC.time_search, SC.clickx.GetSize(), SC.clicky.GetSize());	trif.RecordLog(debc);
// #endif

	SpeedPlay=speed;
	played=false;
	PictIsFi=false;
	UINT lim;//=SC.time_search*1000;
	//lim*=1000;
	bool resconv=this2->ComsToSC(coms, gSC, pathSC);
	ColPerPix=(float)gSC.otk_s;
	lim=gSC.time_search*1000;
	if (!resconv)
	{
		played=true;
		return false;
	}
	//coms.RemoveAll();
	CStringArray nullSA;
	SearchKusok(nullSA, stopme, pathSC);
	UINT old_time=::GetTickCount();
	while (::GetTickCount()-old_time<lim)
	{
		if (PictIsFi || !zap_thread)
		{
			break;
		}
		Sleep(200);
	}
	stop_sear=true;
	UINT tmp=20*60000+old_time+lim;
	while (!exit_cikl && ::GetTickCount()<tmp && zap_thread)
	{	//разрешаем 20 минут ждать окончания цикла поиска
		Sleep(200);
	}
	int cur_pict=0;

	//делаем скриншот в конце Пиксельного Контроля
	char timings[128];

	//Appdlg->SetHook(false);
	if (!PictIsFi)
	{
		if (UN>-1)
		{
			sprintf_s(timings, "time%07d_PC=NOFINDED", 
				(GetTickCount()-AfxGetMainWnd()->SendMessage(WM_USER34, 1)/*CurRec.StartScr*/));
			trif.SaveScreenToBmp(-1, -1, 
				pathForScr+timings, UN);
		}
		StopSearch();
		played=true;
		#ifdef LOG 
		trif.RecordLog("PlaySmart return 0 по таймауту");  
		#endif
		return 0;
	}
	#ifdef LOG 
	char ch[1024];
	#endif 
	int xxx=fi_coorx+gSC.clickx[num_find_bmp];
	if (gSC.Rx[num_find_bmp])
		xxx+=(2*((rand()+GetTickCount())%gSC.Rx[num_find_bmp])-gSC.Rx[num_find_bmp]);
	int yyy=fi_coory+gSC.clicky[num_find_bmp];
	if (gSC.Ry[num_find_bmp])
		yyy+=(2*((rand()+GetTickCount())%gSC.Ry[num_find_bmp])-gSC.Ry[num_find_bmp]);
	CRect rect;
	if (gSC.typeClick[num_find_bmp]>0)
	{
		rect.left=xxx;
		rect.right=xxx+1;
		rect.top=yyy;
		rect.bottom=yyy+1;
		::ClipCursor(0);
		SetCursorPos(xxx, yyy);
		::ClipCursor(&rect);
	}
	//скриншот перед кликом делаем
	if (UN>-1)
	{
		sprintf_s(timings, "time%07d_PC=%d", 
			(GetTickCount()-AfxGetMainWnd()->SendMessage(WM_USER34, 1)/*CurRec.StartScr*/), num_find_bmp);
		if (gSC.typeClick[num_find_bmp]>0)
		{
			trif.SaveScreenToBmp(xxx, yyy, pathForScr+timings, UN, 
				fi_coorx, fi_coory, fi_coorx+pix_sxx, fi_coory+pix_syy);
		} else {
			trif.SaveScreenToBmp(-1, -1, pathForScr+timings, UN, 
				fi_coorx, fi_coory, fi_coorx+pix_sxx, fi_coory+pix_syy);
		}
	}
	//уворачивание "Останови меня" заказываем
	if (uvorot && gSC.typeClick[num_find_bmp])
	{
		AfxGetMainWnd()->SendMessage(WM_USER23, xxx, yyy);
	}
	switch(gSC.typeClick[num_find_bmp])
	{
	case 0:
		//просто ожидание окна
		break;
	case 1:
		//левый клик мышкой	
		Sleep(5);
// 				INPUT lClick;
// 				lClick.type=INPUT_MOUSE;
// 				lClick.mi.dx=xxx;
// 				lClick.mi.dy=yyy;
// 				lClick.mi.dwFlags=MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN;
// 				SendInput(1, &lClick, sizeof(INPUT));
		SetCursorPos(xxx, yyy);
		mouse_event(MOUSEEVENTF_LEFTDOWN, xxx, yyy, 0, 0);
// 				lClick.mi.dwFlags=MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP;
		//Sleep(1000);
		//Sleep(100);
		SetCursorPos(xxx, yyy);
		Sleep(100);
//				SendInput(1, &lClick, sizeof(INPUT));
		mouse_event(MOUSEEVENTF_LEFTUP, xxx, yyy, 0, 0);
		Sleep(5);
		//Sleep(1000);
		#ifdef LOG 
		sprintf(ch, "SmartContr LEFTDOWN LEFTUP %d:%d", xxx, yyy); trif.RecordLog(ch);  
		#endif
		break;
	case 2:
		//двойной клик ЛКМ
		mouse_event(MOUSEEVENTF_LEFTDOWN, xxx, yyy, 0, 0);
		Sleep(1);
		mouse_event(MOUSEEVENTF_LEFTUP, xxx, yyy, 0, 0);
		Sleep(5);
		mouse_event(MOUSEEVENTF_LEFTDOWN, xxx, yyy, 0, 0);
		Sleep(1);
		mouse_event(MOUSEEVENTF_LEFTUP, xxx, yyy, 0, 0);
		break;
	case 3:
		//только нажатие ЛКМ
		mouse_event(MOUSEEVENTF_LEFTDOWN, xxx, yyy, 0, 0);
		break;
	case 4:
		//только Отжатие ЛКМ
		mouse_event(MOUSEEVENTF_LEFTUP, xxx, yyy, 0, 0);
		break;
	case 5:
		//правый клик мышкой
		#ifdef LOG 
		sprintf(ch, "SmartContr LEFTDOWN LEFTUP %d:%d", xxx, yyy);		trif.RecordLog(ch);  
		#endif
		mouse_event(MOUSEEVENTF_RIGHTDOWN, xxx, yyy, 0, 0);
		Sleep(5);
		mouse_event(MOUSEEVENTF_RIGHTUP, xxx, yyy, 0, 0);
		break;
	case 6:
		//двойной клик ПКМ
		mouse_event(MOUSEEVENTF_RIGHTDOWN, xxx, yyy, 0, 0);
		Sleep(1);
		mouse_event(MOUSEEVENTF_RIGHTUP, xxx, yyy, 0, 0);
		Sleep(1);
		mouse_event(MOUSEEVENTF_RIGHTDOWN, xxx, yyy, 0, 0);
		Sleep(1);
		mouse_event(MOUSEEVENTF_RIGHTUP, xxx, yyy, 0, 0);
		break;
	case 7:
		//только нажатие ПКМ
		mouse_event(MOUSEEVENTF_RIGHTDOWN, xxx, yyy, 0, 0);
		break;
	case 8:
		//только Отжатие ПКМ
		mouse_event(MOUSEEVENTF_RIGHTUP, xxx, yyy, 0, 0);
		break;
	}
	//debpla=true;
	Sleep(5);
	::ClipCursor(0);
	played=true;
	return true;
}

//	stopme		- используется для определения, выведено ли окно stopme на передний план, 
					//чтобы учитывать может ли оно заслонять картинку
//	pathSC		- для правильной конвертации COMS в ComsToSC
UINT CWinWork::SearchKusok(CStringArray &COMS, HWND stopme, CString pathSC/*
		, CUIntArray &typeSear, 
				CUIntArray &xl, CUIntArray &xr, CUIntArray &yt, CUIntArray &yb*/
		)
{
	com_time=::GetTickCount();
	MinOtk=0;
	this2=this;
	stop_sear=false;
	exit_cikl=false;
	stopME=stopme;
// 	file_kusok_bmp.RemoveAll();
// 	file_kusok_bmp.Copy(str_bmp_file);
// 	gtypeSear.RemoveAll();
// 	gtypeSear.Copy(typeSear);
// 	COMs.RemoveAll();
// 	COMs.Copy(COMS);
// 	gSC.xl.RemoveAll();
// 	gSC.xl.Copy(xl);
// 	gSC.xr.RemoveAll();
// 	gSC.xr.Copy(xr);
// 	gSC.yt.RemoveAll();
// 	gSC.yt.Copy(yt);
// 	gSC.yb.RemoveAll();
// 	gSC.yb.Copy(yb);

	if (COMS.GetSize())
	{
		bool resconv=this2->ComsToSC(COMS, gSC, pathSC);
		if (!resconv)
		{
			played=true;
			return false;
		}
	}

	zap_thread=true;
	fi_coorx=0; fi_coory=0; 
	#ifdef LOG 
	trif.RecordLog("SearchKusok");  
	#endif
	ProvPlayAip=gSC.ProvPlayAip;
	ThreadSearchPix = AfxBeginThread(/*ParallelSearch*/*SearchOtkl, 
		AfxGetMainWnd()->m_hWnd, THREAD_PRIORITY_BELOW_NORMAL);
	return 1;
}

BOOL CWinWork::InvertRectLine(CDC *pDc, CPoint ptFrom, CPoint ptTo)
{
	//use R2_NOT to invert line
	int nOldMode = pDc->SetROP2(R2_NOT);
	CRect rect(ptFrom, ptTo);
	CPoint pts[] ={ CPoint(rect.left,rect.top),		// LT
					CPoint(rect.right,rect.top),	// RT
					CPoint(rect.right,rect.bottom), // RB
					CPoint(rect.left,rect.bottom),	// LB
					CPoint(rect.left,rect.top)};	// LT

	BOOL bResult = pDc->Polyline(pts,5);
    pDc->SetROP2(nOldMode);
	return bResult;
}

void CWinWork::NulPopr()
{
	MainWinPoprx=0;
	MainWinPopry=0;
	ChaiWinPoprx=0;
	ChaiWinPopry=0;
}

BOOL CWinWork::Reboot(bool reboot, bool force)
{
	OSVERSIONINFO ver;
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);
	if (ver.dwPlatformId == VER_PLATFORM_WIN32_NT) // в семействе NT для выключения необходимо иметь привилегию SE_SHUTDOWN_NAME
    {
		HANDLE hToken;
		TOKEN_PRIVILEGES* NewState;
		OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken);
		NewState=(TOKEN_PRIVILEGES*)malloc(sizeof(TOKEN_PRIVILEGES) + sizeof (LUID_AND_ATTRIBUTES));
		NewState->PrivilegeCount = 1;
		LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&NewState->Privileges[0].Luid);
		NewState->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, NewState, NULL, NULL,NULL);
		free(NewState);
		CloseHandle(hToken);
    }
	UINT mode = 0;
	if (reboot){
		mode += EWX_REBOOT;
	} else {
		mode += EWX_POWEROFF;
	}
	if (force) mode += EWX_FORCE;
	
	return ExitWindowsEx(mode ,0);
}
