// Trifle1.cpp: implementation of the CTrifle class.
//
//////////////////////////////////////////////////////////////////////
#include <string>
using namespace std;

#include "..\stdafx.h"
#include "Trifle1.h"
//#include "appdlg.h"
//#include "Ctrl_tree_list/zip/zip.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define NumPartner 0;//мое
//#define NumPartner 1;//xStarter

#ifdef DebugRU
#define NumLan 1;//русский
#elif ReleaseRU
#define NumLan 1;//русский
#else
#define NumLan 2;//английский
#endif

#ifdef LOG
//запись в лог-файл
bool CTrifle::RecordLog(CString //*
						sRec, int count//*/////////
						)
{
	count++;
	CStdioFile sfLog;
	//AfxMessageBox("ll__1");
	char chFile[100];
	strcpy(chFile, "C:\\ace.log");
	if (count>100)
		sprintf_s(chFile, "C:\\ace_%d.log", count);

	if (!sfLog.Open("C:\\ace.log", CFile::modeWrite))
	{
		//AfxMessageBox("ll__24");
		if (!IsFileExist(chFile))
		{
			//AfxMessageBox("ll__23");
			if (!sfLog.Open(chFile, CFile::modeWrite|CFile::modeCreate))
			{
				//AfxMessageBox("ll__22");
				Sleep(10);
				RecordLog(sRec, count);
				return true;
			}	
		} else {
			//AfxMessageBox("ll__21");
			Sleep(10);
			RecordLog(sRec, count);
			return false;
		}   
	}
	char ch[1024];
	sprintf_s(ch, "\n%011d ", GetTickCount());
	sRec=ch+sRec;
	sfLog.SeekToEnd();
	sfLog.WriteString(sRec);
	sfLog.Close();
	return true;
}
#endif

CTrifle::CTrifle()
{
	sPathToExe="";
	h = CreateEvent(0, true, false, "");
}

CTrifle::~CTrifle()
{

}
CString CTrifle::getSqlIp(CString path_activity)
{
	CFtpConnection *m_pFtpConnection = NULL;
	CInternetSession m_Session;

	try
	{
		m_pFtpConnection = m_Session.GetFtpConnection("debug.autoclickextreme.com",
			"autoclic-debug","thae7Sae",INTERNET_INVALID_PORT_NUMBER);
	}
	catch(CInternetException *pEx)
	{
		pEx->ReportError(MB_ICONEXCLAMATION);
		m_pFtpConnection = NULL;
		pEx->Delete();
		return false;
	}
	m_pFtpConnection->SetCurrentDirectory("debug");
	//CFileFind Finder;
	//CString strFileName;

	// 	if(Finder.FindFile("C:\\ace.log")==TRUE)
	// 	{
	// 		Finder.FindNextFile();
	// 		strFileName = Finder.GetFileName();
	// 		Finder.Close();
	// 	}
	// 	
	CString fileName = path_activity + "sql_ip.txt\0";
	DeleteFile(fileName);
	CString strfile = path_activity + "sql_ip.txt";
	BOOL bUploaded = m_pFtpConnection->GetFile(
		"sql_ip.txt",
		strfile, FALSE);

	CString res;
	if (!bUploaded) //чтение из файла
	{
		if(m_pFtpConnection!=NULL)
			delete m_pFtpConnection;
		return "";
	}
	CStdioFile sf;
	if (!sf.Open(path_activity + "sql_ip.txt", CFile::modeRead))
	{
		if(m_pFtpConnection!=NULL)
			delete m_pFtpConnection;
		return "";
	}
	sf.ReadString(res);
	sf.Close();

	//m_Session.Close();
	m_pFtpConnection->Close();

	DeleteFile(fileName);
	if(m_pFtpConnection!=NULL)
		delete m_pFtpConnection;
	return res;
}

void CTrifle::BlinkRectangle(int x1, int y1, int x2, int y2, int SpeedReplay)
{
	HDC tmpDC;
	tmpDC =::GetDCEx(NULL, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
	CDC *pDesktopDC33=CDC::FromHandle (tmpDC );

	CPoint pt1=CPoint(x1, y1);
	CPoint pt2=CPoint(x2, y2);
	int paus_interv=50-10*SpeedReplay;
	if (paus_interv<=0) paus_interv=0;
	pt1.x-=50;
	pt2.x+=50;
	pt1.y-=50;
	pt2.y+=50;
	InvertRectLine(pDesktopDC33, pt1, pt2);
	//this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
	if (paus_interv)
		Sleep(paus_interv*2);
	InvertRectLine(pDesktopDC33, pt1, pt2);
	//this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
	for (int ind=0; ind<5; ind++)
	{
		if (paus_interv)
			Sleep(paus_interv);
		pt1.x+=10;
		pt2.x-=10;
		pt1.y+=10;
		pt2.y-=10;
		InvertRectLine(pDesktopDC33, pt1, pt2);
		//this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
		if (paus_interv)
			Sleep(paus_interv*2);
		InvertRectLine(pDesktopDC33, pt1, pt2);
		//this2->InvertRectLine(pDesktopDC2 , pt1, pt2);
	}
}
BOOL CTrifle::InvertRectLine(CDC *pDc, CPoint ptFrom, CPoint ptTo)
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

#define VelOtkCur 10
#define Prozrach 200
//UN - при Записи - уникальный номер записываемого действия, 
//при Воспроизведении УН ожидаемого действия
void CTrifle::SaveScreenToBmp(int x, int y, CString path, int UN, 
	int rectx1, int recty1, int rectx2, int recty2)
{
	//return;
	CRect rec_desk;
	::GetWindowRect(GetDesktopWindow(), rec_desk);
	Sleep(1);
	//CDC *pDesktopDC = CDC::FromHandle ( ::GetDCEx(NULL, NULL, 
	//	DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE));
	CDC *pDesktopDC = CDC::FromHandle ( ::GetDC(GetDesktopWindow()));
	Sleep(1);
	CDibExt e_dib_desk;
	e_dib_desk.PasteDC( pDesktopDC, 0, 0, rec_desk.Width(), rec_desk.Height());

	//прямоугольник для пиксельного контроля
	//проверка на превышение границ
	if (rectx1<2) rectx1=2;
	if (rectx2>=rec_desk.Width ()-2) rectx2=rec_desk.Width ()-3;
	if (recty1<2) recty1=2;
	if (recty2>=rec_desk.Height()-2) recty2=rec_desk.Height()-3;

	if (rectx1>-1 && rectx2>-1)
	{
		rectx1-=1;
		rectx2+=1;
		recty1-=1;
		recty2+=1;
		e_dib_desk.LineGlass(rectx1, recty1, rectx2, recty1, 255, 0, 0, Prozrach);
		e_dib_desk.LineGlass(rectx2, recty1, rectx2, recty2, 255, 0, 0, Prozrach);
		e_dib_desk.LineGlass(rectx2, recty2, rectx1, recty2, 255, 0, 0, Prozrach);
		e_dib_desk.LineGlass(rectx1, recty2, rectx1, recty1, 255, 0, 0, Prozrach);
		rectx1-=1;
		rectx2+=1;
		recty1-=1;
		recty2+=1;
		e_dib_desk.LineGlass(rectx1, recty1, rectx2, recty1, 0, 255, 0, Prozrach);
		e_dib_desk.LineGlass(rectx2, recty1, rectx2, recty2, 0, 255, 0, Prozrach);
		e_dib_desk.LineGlass(rectx2, recty2, rectx1, recty2, 0, 255, 0, Prozrach);
		e_dib_desk.LineGlass(rectx1, recty2, rectx1, recty1, 0, 255, 0, Prozrach);
	}
	if (x>-1)
	{
		//крестик для координаты клика
		if (x==0) x++;
		if (x==rec_desk.Width()) x--;
		if (y==0) y++;
		if (y==rec_desk.Height()) y--;
		rectx1=x-VelOtkCur;
		rectx2=x+VelOtkCur;
		recty1=y-VelOtkCur;
		recty2=y+VelOtkCur;
		//контролируем гриницы крестика
		if (rectx1<0)
		{
			rectx2-=rectx1;
			rectx1=0;
		}
		if (rectx2>=rec_desk.Width())
		{
			rectx1-=rectx2-rec_desk.Width();
			rectx2=rec_desk.Width()-1;
		}
		if (recty1<0)
		{
			recty2-=recty1;
			recty1=0;
		}
		if (recty2>=rec_desk.Height())
		{
			recty1-=recty2-rec_desk.Height();
			recty2=rec_desk.Height()-1;
		}
		e_dib_desk.LineGlass(x  , recty1, x  , recty2, 255, 0, 0, Prozrach);
		e_dib_desk.LineGlass(x-1, recty1, x-1, recty2, 0, 255, 0, Prozrach);
		e_dib_desk.LineGlass(x+1, recty1, x+1, recty2, 0, 255, 0, Prozrach);
		e_dib_desk.LineGlass(rectx1, y  , rectx2, y  , 255, 0, 0, Prozrach);	
		e_dib_desk.LineGlass(rectx1, y-1, rectx2, y-1, 0, 255, 0, Prozrach);	
		e_dib_desk.LineGlass(rectx1, y+1, rectx2, y+1, 0, 255, 0, Prozrach);	
	}

	char chfname[1024];
	sprintf_s(chfname, path+"_UN%06d.bmp", UN);
	SaveBitmap((HBITMAP)e_dib_desk.m_Bitmap, chfname);
	ReleaseDC(0, pDesktopDC->m_hDC);
	//pDesktopDC->DeleteDC();
}

//сохранение дочернего окошка, или части его в bmp файл
CString CTrifle::SaveHWNDToBmp(int x, int y, CString path, HWND child)
{
// #ifdef LOG 
// 	AfxGetMainWnd()->SendMessage(WM_USER31, 1); //SetHook(false);
// #endif
	//return;
	CRect rec_win;
	::GetWindowRect(child, rec_win);
	//скриншот позиционируем на клике
	if (x>-1 && x-rec_win.left>100)
		rec_win.left=x-100;
	if (y>-1 && y-rec_win.top>70)
		rec_win.top=y-70;

//	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USER+31, 1, 0);
	Sleep(1);
	//CDC *pDesktopDC = CDC::FromHandle ( ::GetDCEx(NULL, NULL, 
	//	DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE));
	CDC *pDesktopDC = CDC::FromHandle ( ::GetDC(GetDesktopWindow()));
	Sleep(1);
	CDibExt e_dib_desk;
	int leftgran=rec_win.left;
	int topgran=rec_win.top;
	int width_rec=rec_win.Width();
	int height_rec=rec_win.Height();
	if (leftgran>4)
	{
		leftgran-=4;
		width_rec+=4;
	}
	if (topgran>4)
	{
		topgran-=4;
		height_rec+=4;
	}
	if (width_rec>200)
		width_rec=200;
	if (height_rec>140)
		height_rec=140;
	e_dib_desk.PasteDC(pDesktopDC, leftgran, topgran, width_rec, height_rec);
	

	if (x>-1)
	{
		//крестик для координаты клика
		if (x==0) x++;
		if (x==leftgran+width_rec) x--;
		if (y==0) y++;
		if (y==topgran+height_rec) y--;
		//прямоугольник крестика
		int rectx1=x-VelOtkCur;
		int rectx2=x+VelOtkCur;
		int recty1=y-VelOtkCur;
		int recty2=y+VelOtkCur;
		//контролируем гриницы крестика
		if (rectx1<0)
		{
			rectx2-=rectx1;
			rectx1=0;
		}
		if (rectx2>=leftgran+width_rec)
		{
			rectx1-=rectx2-(leftgran+width_rec);
			rectx2=leftgran+width_rec-1;
		}
		if (recty1<0)
		{
			recty2-=recty1;
			recty1=0;
		}
		if (recty2>=topgran+height_rec)
		{
			recty1-=recty2-(topgran+height_rec);
			recty2=topgran+height_rec-1;
		}
		if (rectx1<leftgran)
			rectx1=leftgran;
		if (recty1<topgran)
			recty1=topgran;
		e_dib_desk.LineGlass(x  -leftgran, recty1-topgran, x  -leftgran, recty2-topgran, 255, 0, 0, Prozrach);
		e_dib_desk.LineGlass(x-1-leftgran, recty1-topgran, x-1-leftgran, recty2-topgran, 0, 255, 0, Prozrach);
		e_dib_desk.LineGlass(x+1-leftgran, recty1-topgran, x+1-leftgran, recty2-topgran, 0, 255, 0, Prozrach);
		e_dib_desk.LineGlass(rectx1-leftgran, y  -topgran, rectx2-leftgran, y  -topgran, 255, 0, 0, Prozrach);	
		e_dib_desk.LineGlass(rectx1-leftgran, y-1-topgran, rectx2-leftgran, y-1-topgran, 0, 255, 0, Prozrach);	
		e_dib_desk.LineGlass(rectx1-leftgran, y+1-topgran, rectx2-leftgran, y+1-topgran, 0, 255, 0, Prozrach);	
	}
	
	char chfname[1024];
	sprintf_s(chfname, "x%dy%d.bmp", leftgran, topgran);
	path+=chfname;
	SaveBitmap((HBITMAP)e_dib_desk.m_Bitmap, path);
	ReleaseDC(0, pDesktopDC->m_hDC);
	return path;
	//pDesktopDC->DeleteDC();
}

PBITMAPINFO CTrifle::CreateBitmapInfoStruct(HBITMAP hBmp){ 
    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 
	
    // Retrieve the bitmap color format, width, and height. 
    GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp); 
	
    // Convert the color format to a count of bits. 
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else cClrBits = 32; 
	
    // Allocate memory for the BITMAPINFO structure. (This structure 
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD 
    // data structures.) 
	
	if (cClrBits != 24) pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1<< cClrBits)); 
	
	// There is no RGBQUAD array for the 24-bit-per-pixel format. 
	
	else pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER)); 
	
    // Initialize the fields in the BITMAPINFO structure. 
	
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24) pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 
	
    // If the bitmap is not compressed, set the BI_RGB flag. 
    pbmi->bmiHeader.biCompression = BI_RGB; 
	
    // Compute the number of bytes in the array of color 
    // indices and store the result in biSizeImage. 
    // For Windows NT, the width must be DWORD aligned unless 
    // the bitmap is RLE compressed. This example shows this. 
    // For Windows 95/98/Me, the width must be WORD aligned unless the 
    // bitmap is RLE compressed. 
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8 * pbmi->bmiHeader.biHeight; 
    // Set biClrImportant to 0, indicating that all of the 
    // device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0; 
	return pbmi; 
}

void CTrifle::SaveBitmap(HBITMAP bmp, LPCSTR file)
{
    PBITMAPINFO pbi=CreateBitmapInfoStruct(bmp);
	
    HDC hdcImage=CreateCompatibleDC(NULL);
    CreateBMPFile(file,pbi,bmp, hdcImage);
	
    DeleteDC(hdcImage);
	
	LocalFree(pbi);
}

void CTrifle::CreateBMPFile(LPCSTR pszFile, PBITMAPINFO pbi, 
						 HBITMAP hBMP, HDC hDC)
{ 
    HANDLE hf;                 // file handle 
    BITMAPFILEHEADER hdr;       // bitmap file-header 
    PBITMAPINFOHEADER pbih;     // bitmap info-header 
    LPBYTE lpBits;              // memory pointer 
    DWORD dwTotal;              // total count of bytes 
    DWORD cb;                   // incremental count of bytes 
    BYTE *hp;                   // byte pointer 
    DWORD dwTmp; 
	
    pbih = (PBITMAPINFOHEADER) pbi; 
    lpBits = (LPBYTE) new char[pbih->biSizeImage];
	//(LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
	
    if (!lpBits) 
    {
		return;
        //errhandler("GlobalAlloc", hwnd);
    }
    // Retrieve the color table (RGBQUAD array) and the bits 
    // (array of palette indices) from the DIB. 
    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, 
        DIB_RGB_COLORS)) 
    {
		return;
        //errhandler("GetDIBits", hwnd);
    }
	
    // Create the .BMP file. 
    hf = CreateFile(pszFile, 
		GENERIC_READ | GENERIC_WRITE, 
		(DWORD) 0, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL); 
    if (hf == INVALID_HANDLE_VALUE) 
    {
		return;
		//        errhandler("CreateFile", hwnd); 
    }
    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
    // Compute the size of the entire file. 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof(RGBQUAD) + pbih->biSizeImage); 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 
	
    // Compute the offset to the array of color indices. 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof (RGBQUAD); 
	
    // Copy the BITMAPFILEHEADER into the .BMP file. 
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTmp,  NULL)) 
    {
		return;
		//       errhandler("WriteFile", hwnd);
    }
	
    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
		+ pbih->biClrUsed * sizeof (RGBQUAD), 
		(LPDWORD) &dwTmp, ( NULL)) )
		return;
	// errhandler("WriteFile", hwnd); 
	
    // Copy the array of color indices into the .BMP file. 
    dwTotal = cb = pbih->biSizeImage; 
    hp = lpBits; 
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
		return;
	//  errhandler("WriteFile", hwnd); 
	
    // Close the .BMP file. 
	if (!CloseHandle(hf)) 
		return;
	//  errhandler("CloseHandle", hwnd);
	
	// Free memory. 
	delete lpBits;
	//GlobalFree((HGLOBAL)lpBits);
}

COLORREF CTrifle::AddColor(COLORREF beg_col, int r, int g, int b)
{
	r+=GetRValue(beg_col);
	g+=GetGValue(beg_col);
	b+=GetBValue(beg_col);
	if (r>255) r=255;
	if (g>255) g=255;
	if (b>255) b=255;
	if (r<0) r=0;
	if (g<0) g=0;
	if (b<0) b=0;
	return RGB(r,g,b);
}
int CTrifle::GetNumLan()
{
	return NumLan;
}
int CTrifle::GetPartner()
{
	return NumPartner;
}

//extern CAppDlg* Appdlg;
//установка курсора с захватом его
void CTrifle::CapSetCursorPos(int x, int y)
{
	CRect rect;
	rect.left=x;
	rect.right=x+1;
	rect.top=y;
	rect.bottom=y+1;
	::ClipCursor(0);
	SetCursorPos(x, y);
	::ClipCursor(&rect);
}

//пошаговое перемещение курсора
//сначала курсор двигается по горизонтали, потом по вертикали
void CTrifle::MySetCursorPos(int x, int y)
{
	CPoint po;
	::GetCursorPos(&po);
	//deb.Format("po_x=%d: po_y=%d", po.x,po.y);
	//Appdlg->RecordLog(deb);
	if (po.x<x){
		for (int ii=po.x; ii<=x; ii++){
			::SetCursorPos(ii, po.y);
			if (ii-po.x<10)
				WaitForSingleObject(h, 1);
				//Sleep(1);
		}
	} else {
		for (int ii=po.x; ii>=x; ii--){
			::SetCursorPos(ii, po.y);
			if (po.x-ii<10)
				WaitForSingleObject(h, 1);
				//Sleep(1);
		}
	}
	if (po.y<y){
		for (int ii=po.y; ii<=y; ii++){
			::SetCursorPos(x, ii);
			if (ii-po.y<10)
				WaitForSingleObject(h, 1);
				//Sleep(1);
		}
	} else {
		for (int ii=po.y; ii>=y; ii--){
			::SetCursorPos(x, ii);
			if (po.y-ii<10)
				WaitForSingleObject(h, 1);
				//Sleep(1);
		}
	}
	/*if (po.y<y){
		for (int ii=po.y; ii<=y; ii++){
			::SetCursorPos(po.x, ii);
			if (ii-po.y<10)
				Sleep(1);
		}
	} else {
		for (int ii=po.y; ii>=y; ii--){
			::SetCursorPos(po.x, ii);
			if (po.y-ii<10)
				Sleep(1);
		}
	}
	if (po.x<x){
		for (int ii=po.x; ii<=x; ii++){
			::SetCursorPos(ii, y);
			if (ii-po.x<10)
				Sleep(1);
		}
	} else {
		for (int ii=po.x; ii>=x; ii--){
			::SetCursorPos(ii, y);
			if (po.x-ii<10)
				Sleep(1);
		}
	}*/
}

CString CTrifle::IntToStr(int ii)
{
	char ch[512];
	sprintf_s(ch, "%d", ii);
	return ch;
}

CString CTrifle::XToStr(LPARAM hw)
{
	CString str;
	str.Format("%X", hw);
	return str;
}

//удаление из строки куска мужду двумя разделителями
void CTrifle::RemStr(CString &str, CString razd1, CString razd2, bool delrazd)
{
	int fi, fi2;
	if (razd1=="") {fi=0;} else 
	{ fi=str.Find(razd1);}
	if (razd2=="") {fi2=str.GetLength();} else 
	{ fi2=str.Find(razd2);}	
	if (fi==-1) fi=0;
	if (fi2==-1) {
		fi2=str.GetLength();
		razd2="";
	}
	if (delrazd) {//удалять вместе с разделителями или нет
		str.Delete(fi, fi2-fi+razd2.GetLength());
	} else {
		str.Delete(fi+razd1.GetLength(), fi2-fi-razd1.GetLength());
	}
}

//взятие заголовка окна с одновременным его скидыванием в CString
CString CTrifle::MyGetWindowText(HWND child)
{
	if (!child) return "";
 	if (!IsWindow(child)) 
 		return "";
	char wintext[1024];
	int ress=::SendMessageTimeout(child, WM_GETTEXT, 1024-1, (LPARAM)wintext, 0, 100, 0);
	//::GetWindowText(child, wintext, 1024);
	return wintext;
}

//выделение времени из строки опций
CString CTrifle::ExtrTime(CString str)
{
	return this->ExtractStr(str, "(&!TiMe", "!&)", true);
}

//взятие имени класса окна с его скидыванием в CString
CString CTrifle::MyGetClassName(HWND child)
{
	if (!child) return "";
	if (!IsWindow(child)) return "";
	char wintext[100];
	::GetClassName(child, wintext, 100);
	return wintext;
}


//выделение из строки куска мужду стринговыми разделителями
CString CTrifle::ExtractStr(CString str, CString razd1, CString razd2, bool delrazd)
{
	int fi, fi2;
	if (razd1=="") {fi=0;} else 
	{ fi=str.Find(razd1);}
	if (fi==-1) return "";//fi=0;
	if (delrazd) {//выделять вместе с разделителями или нет
		str.Delete(0, fi+razd1.GetLength());
		if (razd2=="") {
			return str;
			//fi2=0;
		} else { 
			fi2=str.Find(razd2);
		}	
		if (fi2==-1) fi2=str.GetLength();
		str.Delete(fi2/*+razd2.GetLength()*/, str.GetLength()-fi2/*-razd2.GetLength()*/);
	} else {
		str.Delete(0, fi+razd1.GetLength());
		if (razd2=="") {return str;} else 
		{ fi2=str.Find(razd2);}	
		if (fi2==-1) return "";//fi2=str.GetLength();
		str.Delete(fi2, str.GetLength()-fi2);
	}
	return str;		
}

UINT CTrifle::TransModifiers(WORD wMod)
{
	UINT uMod = 0;
	
	if (wMod & HOTKEYF_ALT)
		uMod |= MOD_ALT;
	
	if (wMod & HOTKEYF_SHIFT)
		uMod |= MOD_SHIFT;
	
	if (wMod & HOTKEYF_CONTROL)
		uMod |= MOD_CONTROL;
	
	return uMod;
}


//typedef int 
// (WINAPI *PFN_MyFunction)(char *);  
typedef	void (__stdcall *SWitchToThisWindow)(HWND, BOOL);
SWitchToThisWindow mySwitchToThisWindow=NULL; 

//вынос на передний план окна
BOOL CTrifle::BringWindowToForeground(HWND hw)
{
	::ShowWindow(hw, SW_SHOW);
	if (mySwitchToThisWindow==NULL)
	{
		HMODULE hUser32ModuleHandle = GetModuleHandle("user32.dll");
		if(hUser32ModuleHandle == NULL)
		{
			AfxMessageBox("hUser32ModuleHandle == NULL");
			return false;
		}
		mySwitchToThisWindow=(SWitchToThisWindow)::GetProcAddress
							   (hUser32ModuleHandle,"SwitchToThisWindow");
		if(mySwitchToThisWindow == NULL){
			AfxMessageBox("mySwitchToThisWindow == NULL");
			return false;
		}
	}
	mySwitchToThisWindow(hw, TRUE);
	//2-ой способ
	DWORD dwUserInputTimeout;
	::SystemParametersInfo(0x2000, 0,&dwUserInputTimeout, 0);
	::SystemParametersInfo(0x2001, 0, 0, 0);
	if (hw == NULL)
		return  FALSE;
	if(!::IsWindow(hw))
		return FALSE;
	::SystemParametersInfo(0x2000, 0,
	&dwUserInputTimeout, 0);
	::SystemParametersInfo(0x2001, 0, 0, 0);
	::SetWindowPos(hw, HWND_TOPMOST, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE);
	Sleep(1);
	::SetWindowPos(hw, HWND_NOTOPMOST, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE);
	Sleep(1);
	::SystemParametersInfo(0x2001, 0,
		(LPVOID) dwUserInputTimeout, 0);
	Sleep(1);

	/*HWND hCurWnd;

	while((hCurWnd = ::GetForegroundWindow()) != hw)
	{
		HWND hWndActive = ::GetForegroundWindow();

		DWORD dwThreadID = ::GetCurrentThreadId();
		DWORD dwCurThreadID = ::GetWindowThreadProcessId(hWndActive, 0);

		AttachThreadInput(dwThreadID, dwCurThreadID, TRUE);

		SetForegroundWindow(hw);
		Sleep(1);

		AttachThreadInput(dwThreadID, dwCurThreadID, FALSE);

		Sleep(20);
	}*/

// 
	for (int ii=1; ii<=10; ii++){
	if (GetForegroundWindow()!=hw &&
		GetWindow(hw, GW_OWNER)!=GetForegroundWindow() &&
		GetWindow(GetForegroundWindow(), GW_OWNER)!=hw)	
		Sleep(100);
	}
	return TRUE;
}

//Приведение русской раскладки к английской
void CTrifle::TransformKeyLayout(int &code)
{
	switch(code)
	{
		//строчные буквы 
	case 233:	code=113;	break;
	case 246:	code=119;	break;
	case 243:	code=101;	break;
	case 234:	code=114;	break;
	case 229:	code=116;	break;
	case 237:	code=121;	break;
	case 227:	code=117;	break;
	case 248:	code=105;	break;
	case 249:	code=111;	break;
	case 231:	code=112;	break;
	case 245:	code=91;	break;
	case 250:	code=93;	break;
	case 244:	code=97;	break;
	case 251:	code=115;	break;
	case 226:	code=100;	break;
	case 224:	code=102;	break;
	case 239:	code=103;	break;
	case 240:	code=104;	break;
	case 238:	code=106;	break;
	case 235:	code=107;	break;
	case 228:	code=108;	break;
	case 230:	code=59;	break;
	case 253:	code=39;	break;
// 	case 92:/ 		code=92;/ 		break;
	case 255:	code=122;	break;
	case 247:	code=120;	break;
	case 241:	code=99;	break;
	case 236:	code=118;	break;
	case 232:	code=98;	break;
	case 242:	code=110;	break;
	case 252:	code=109;	break;
	case 225:	code=44;	break;
	case 254:	code=46;	break;// "ю" переводим в запятую
// 	case 46://русскую точку не будем трансформировать
// 		code=47;
// 		break;
	case 257:	code=96;	break;// "ё" переводим в апостроф "`"
	//ПРОПИСНЫЕ БУКВЫ 
	case 177:	code=96;	break;
	case 192:	code=70;	break;
	case 193:	code=44;	break;
	case 194:	code=68;	break;
	case 195:	code=85;	break;
	case 196:	code=76;	break;
	case 197:	code=84;	break;
	case 198:	code=59;	break;
	case 199:	code=80;	break;
	case 200:	code=66;	break;
	case 201:	code=81;	break;
	case 202:	code=82;	break;
	case 203:	code=75;	break;
	case 204:	code=86;	break;
	case 205:	code=89;	break;
	case 206:	code=74;	break;
	case 207:	code=71;	break;
	case 208:	code=72;	break;
	case 209:	code=67;	break;
	case 210:	code=78;	break;		
	case 211:	code=69;	break;
	case 212:	code=65;	break;
	case 213:	code=91;	break;
	case 214:	code=87;	break;		
	case 215:	code=88;	break;
	case 216:	code=73;	break;
	case 217:	code=79;	break;
	case 218:	code=93;	break;
	case 219:	code=83;	break;//"Х" 
	case 220:	code=77;	break;
	case 221:	code=83;	break;//"Ъ"
	case 222:	code=46;	break;
	case 223:	code=90;	break;
	}
}

//УВЕЛИЧЕНИЕ РЕГИСТРА (для нечувственности к регистру в АТ)
void CTrifle::UpperCase2(int &code)
{
	switch(code)
	{
		//в данном диапазоне просто отнимаем 32
	//английский алфавит
	case 97:		case 98:		case 99:		case 100:
	case 101:		case 102:		case 103:		case 104:
	case 105:		case 106:		case 107:		case 108:
	case 109:		case 110:		case 111:		case 112:
	case 113:		case 114:		case 115:		case 116:
	case 117:		case 118:		case 119:		case 120:
	case 121:		case 122:		
		//русский алфавит		
	case 224:		case 225:		case 226:		case 227:
	case 228:		case 229:		case 230:		case 231:
	case 232:		case 233:		case 234:		case 235:
	case 236:		case 237:		case 238:		case 239:
	case 240:		case 241:		case 242:		case 243:
	case 244:		case 245:		case 246:		case 247:
	case 248:		case 249:		case 250:		case 251:
	case 252:		case 253:		case 254:		case 255:
		code-=32;
		break;
	case 257:
		code=177;
	    break;
	}
}

//проверка: нужно ли переключать клаву
bool CTrifle::ToogleKeyb(UINT code)
{
	switch (code)
	{
	case 192:
	case 81:
	case 87:
	case 69:
	case 82:
	case 48:
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 187:
	case 189:
	case 84:
	case 89:
	case 85:
	case 73:
	case 79:
	case 80:
	case 219:
	case 221:
	case 65:
	case 83:
	case 68:
	case 70:
	case 71:
	case 72:
	case 74:
	case 75:
	case 76:
	case 186:
	case 222:
	case 220:
	case 90:
	case 88:
	case 67:
	case 86:
	case 66:
	case 78:
	case 77:
	case 188:
	case 190:
	case 191:
		return true;
	}
	return false;
}

//#include "resource.h"
bool CTrifle::MyReadString(CStdioFile &file, bool &endFile, 
						   CString &f_str)
{
	if (!endFile){
		if (file.ReadString(f_str)){
			//AfxMessageBox("ReadString f_str="+f_str);
		} else {
			f_str="";
			endFile=true;
			return false;
		}
	} else {
		f_str="";
		return false;
	}
	return true;
}

//установка номера языка
// void CTrifle::SetNumLan(int NumLanSet)
// {
// 	NumLan=NumLanSet;
// }

// bool ComsToSC(CStringArray &coms, CStringArray &saBmps, CUIntArray &typeSr, 
// 		CUIntArray &xl, CUIntArray &xr, CUIntArray &yt, CUIntArray &yb,
// 		CUIntArray &gclickx, CUIntArray &gclicky, CUIntArray &gtypeClick, CUIntArray &gRx, CUIntArray &gRy)
// {
// 	return true;
// }
//для COMS
CString CTrifle::GetStrFromTypeClick(int TypeClick)
{
	switch(TypeClick)
	{
	case 0:
		return "NoClick";
	case 1:
		return "MouseLeftClick";
	case 2:
		return "MouseLeftDblClick";
	case 3:
		return "MouseLeftDown";
	case 4:
		return "MouseLeftUp";
	case 5:
		return "MouseRightClick";
	case 6:
		return "MouseRightDblClick";
	case 7:
		return "MouseRightDown";
	case 8:
		return "MouseRightUp";
	default:
		return "UnDefClick";
	}
}

int CTrifle::GetTypeClickFromStr(CString TypeClick)
{
	TypeClick.TrimLeft(" ");
	TypeClick.TrimRight(" ");
	if (TypeClick=="NoClick")
		return 0;
	if (TypeClick=="MouseLeftClick")
		return 1;
	if (TypeClick=="MouseLeftDblClick")
		return 2;
	if (TypeClick=="MouseLeftDown")
		return 3;
	if (TypeClick=="MouseLeftUp")
		return 4;
	if (TypeClick=="MouseRightClick")
		return 5;
	if (TypeClick=="MouseRightDblClick")
		return 6;
	if (TypeClick=="MouseRightDown")
		return 7;
	if (TypeClick=="MouseRightUp")
		return 8;
// 	if (TypeClick.Find("UnDefClick")>-1)
// 		return 0;
	return -1;
}

//с подсчетом количества искомых картинок
CString CTrifle::GetFirstBmpFromPC2(CStringArray &coms, int &counPict)
{
	int coun=0;
	CString resul;
	for (int jj=0; jj<coms.GetSize(); jj++)
	{
		int fi=coms[jj].Find("Find(\"");
		if (fi>-1)
		{
			if (!coun)
			{
				resul=coms[jj];
				resul.Delete(0, fi+6);
				resul=resul.Left(resul.Find("\""));
			}
			coun++;
		}
	}
	if (coun)
	{
		counPict=coun;
		return resul;
	}
	return "";
}

//с подсчетом количества искомых картинок
CString CTrifle::GetBmpFromPC3(CStringArray &coms, int numPict, int &counPict)
{
	int coun=0;
	CString resul;
	for (int jj=0; jj<coms.GetSize(); jj++)
	{
		int fi=coms[jj].Find("Find(\"");
		if (fi>-1)
		{
			if (coun==numPict)
			{
				resul=coms[jj];
				resul.Delete(0, fi+6);
				resul=resul.Left(resul.Find("\""));
			}
			coun++;
		}
	}
	if (coun>=numPict)
	{
		counPict=coun;
		return resul;
	}
	return "";
}

CString CTrifle::GetFirstBmpFromPC(CStringArray &coms)
{
	for (int jj=0; jj<coms.GetSize(); jj++)
	{
		int fi=coms[jj].Find("Find(\"");
		if (fi>-1)
		{
			CString tmp=coms[jj];
			tmp.Delete(0, fi+6);
			return tmp.Left(tmp.Find("\""));
		}
	}
	return "";
}

void CTrifle::MakeArchiv(CString fName)
{
// 	char date[15];
// 	SYSTEMTIME st;
// 	GetLocalTime(&st);
// 	GetDateFormat(LOCALE_USER_DEFAULT, LOCALE_USE_CP_ACP, &st, "_yyyy_MM_dd", date, 13);
// 	CString NameArc=fName+date;
// 	NameArc+=".zip";
// 	
// 	CFileDialog mFileSaveAs( FALSE, "zip",NameArc, 
// 		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "*.zip|*.zip|All files (*.*)|*.*||",NULL );
// 	if( mFileSaveAs.DoModal ()!=IDOK )
// 		return;
// 	CString pathName = mFileSaveAs.GetPathName();
// 	//	CString fileName = mFileSaveAs.GetFileTitle (
// 	if (SaveArc(fName, pathName))
// 		pathName.LoadString(GetIds(IDS_STRING1523));
// 	else pathName.LoadString(GetIds(IDS_STRING1521));
// 	AfxMessageBox(pathName);
} 

bool CTrifle::SaveArc(CString NameAip, CString NameArc) 
{
	//NameArc="c:\\1.zip";
// 	HZIP hz = CreateZip(NameArc,0);	
// 	if (hz==0)
// 		return false;
// 	if (ZipAdd(hz, NameAip,  NameAip))
// 	{
// 		CloseZip(hz);
// 		return false;
// 	}
// 	//все сопровождающие папку файлы тоже добавляем в архив
// 	CString shName=ExtractFileName(NameAip);
// 	CString rec_path=ExtractPath(NameAip)+"\\dir_aip_"+shName.Left(shName.GetLength()-4)+"\\\0";	
// 	//перебираем все файлы в папке Записи
// 	WIN32_FIND_DATA FFData;
// 	HANDLE hFind = FindFirstFile(rec_path+"\\*.*", &FFData);
// 	if (hFind == INVALID_HANDLE_VALUE)
// 	{
// 		CloseZip(hz);
// 		return true;
// 	}
// 	do 
// 	{
// 		if (strcmp(FFData.cFileName, "..")!=0 &&
// 			strcmp(FFData.cFileName, ".")!=0 &&
// 			strcmp(FFData.cFileName, "play")!=0 &&
// 			strcmp(FFData.cFileName, "rec")!=0
// 			)
// 			if (ZipAdd(hz, rec_path+FFData.cFileName,  rec_path+FFData.cFileName))
// 			{
// 				CloseZip(hz);
// 				return false;
// 			}
// 	} while (FindNextFile(hFind, &FFData));		
// 	FindClose(hFind);
// 	CloseZip(hz);
	return true;
}

string CTrifle::getEnd(int val)
{
	switch(val % 10)
	{
	case 0:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		return "ков";
	case 2:
	case 3:
	case 4:
		return "ка";
	case 1:
		return "ок";
	}
	return "";
}
//
UINT CTrifle::GetIds(UINT IDS)
{
	int ret=0;
	if (GetNumLan()==2) 
		IDS++;
	return IDS;
}

bool CTrifle::IsFileExist(CString sFile)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(sFile, &findFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		return false;
	}
	FindClose(hFind);
	return true;
}
bool CTrifle::IsDirExist(CString sDir)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(sDir+"\\*.*", &findFileData);

	if (hFind == INVALID_HANDLE_VALUE){
		FindClose(hFind);
		return false;
	}

	FindClose(hFind);
	return true;
}

#include "tlhelp32.h"
bool CTrifle::IfProccessExist(CString &sProcess)
{
	sProcess.MakeLower();
	HANDLE hSnap;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == NULL) 
	{
		WriteJournal("Error Load ToolHelp !!!");
	}
	PROCESSENTRY32 proc;
	if (Process32First(hSnap, &proc))
	{
		CString str=proc.szExeFile;
		str=ExtractFileName(str);
		str.MakeLower();
		if (str==sProcess)
			return true;
		while (Process32Next(hSnap, &proc)) 
		{
			str=proc.szExeFile;
			//str=ExtractFileName(str);
			str.MakeLower();
			if (str==sProcess)
				return true;
		}
	}// 	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
// 	MODULEENTRY32 me32;
// 	// Take a snapshot of all modules in the specified process.
// 	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, 0 );
// 	if( hModuleSnap == INVALID_HANDLE_VALUE )
// 	{
// 		//printError( "CreateToolhelp32Snapshot (of modules)" );
// 		return false;
// 	}
// 
// 	// Set the size of the structure before using it.
// 	me32.dwSize = sizeof( MODULEENTRY32 );
// 
// 	// Retrieve information about the first module,
// 	// and exit if unsuccessful
// 	if( !Module32First( hModuleSnap, &me32 ) )
// 	{
// 		//printError( "Module32First" );  // Show cause of failure
// 		CloseHandle( hModuleSnap );     // Must clean up the snapshot object!
// 		return false;
// 	}
// 
// 	// Now walk the module list of the process,
// 	// and display information about each module
// 	do
// 	{
// 		CString str=me32.szExePath;
// 		str=ExtractFileName(str);
// 		str.MakeLower();
// 		if (str==sProcess){
// 			return true;
// 		}
// 		
// 	} while( Module32Next( hModuleSnap, &me32 ) );
// 			CloseHandle( hModuleSnap );
	return false;
}

CString CTrifle::ExtractPath(CString &NameFile)
{
	int fi=NameFile.ReverseFind('\\');
	if (fi==-1)
		fi=NameFile.ReverseFind('/');
	return NameFile.Left(fi);
}
CString CTrifle::ExtractFileName(CString &NameFile)
{
	int fi=NameFile.ReverseFind('\\');
	if (fi==-1)
		fi=NameFile.ReverseFind('/');
	return NameFile.Right(NameFile.GetLength()-fi-1);
}

BOOL CTrifle::Is64BitOS()
{
	BOOL bIs64Bit = FALSE;
	
#if defined(_WIN64)
	
	bIs64Bit = TRUE;  // 64-bit programs run only on Win64
	
#elif defined(_WIN32)
	
	// Note that 32-bit programs run on both 32-bit and 64-bit Windows
	
	typedef BOOL (WINAPI *LPFNISWOW64PROCESS) (HANDLE, PBOOL);
	LPFNISWOW64PROCESS pfnIsWow64Process = (LPFNISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")), "IsWow64Process");
	
	if (pfnIsWow64Process)
		pfnIsWow64Process(GetCurrentProcess(), &bIs64Bit);
	
#endif
	
	return bIs64Bit;
}
void CTrifle::TrimKavich(CString &sRes)
{
	if (sRes.GetLength()>1 && sRes[0]=='\"')
	{ //тримим кавычки слева и справа
		sRes.Delete(0);
		if (sRes=='\"')
		{
			sRes.Delete(0);
		} else {
			if (sRes.GetLength()>1 && sRes[sRes.GetLength()-2]!='\\' && sRes[sRes.GetLength()-1]=='\"')
				sRes.Delete(sRes.GetLength()-1);
		}
	}
}

CString CTrifle::GetPixPath(CString &aipName, CString &path_exe, bool DirCreate)
{
	CString str=aipName;
	if (str.Right(4)==".aip")
	{
		//str=+str.Left(str.GetLength()-4);
		CString shName=ExtractFileName(str);
		CString pixp=ExtractPath(str)+"\\dir_aip_"+shName.Left(shName.GetLength()-4);
		if (DirCreate)
		{
			if (!IsDirExist(pixp))
			if (!CreateDirectory(pixp, NULL))
			{
				//если не удается папку создать
				str=path_exe+"\\cash";
			} else {
				SetFileAttributes(pixp, FILE_ATTRIBUTE_HIDDEN);
			}
		} else {
			if (!IsDirExist(pixp))
			{
				str=ExtractPath(str)+"\\"+shName.Left(shName.GetLength()-4);
				if (IsDirExist(str))
				{
					if (MoveFile(str, pixp))
						return pixp;
					return str;
				}
			}
		}
		return pixp;
		//проверяем - создан ли уже каталог для пиксельн. контр.
	} else {
		str=path_exe+"\\cash";
	}
	return str;
}
// CString CTrifle::GetPixPathOld(CString &aipName, CString &path_exe)
// {
// 	CString str=aipName;
// 	if (str.Right(4)==".aip")
// 	{
// 		str=str.Left(str.GetLength()-4);
// // 		if (!IsDirExist(str))
// // 			if (!CreateDirectory(str, NULL))
// // 			{
// // 				//если не удается папку создать
// // 				str=path_exe+"cash";
// // 			} else {
// // 				SetFileAttributes(str, FILE_ATTRIBUTE_HIDDEN);
// // 			}
// 			//проверяем - создан ли уже каталог для пиксельн. контр.
// 	} else {
// 		str=path_exe+"cash";
// 	}
// 	return str;
// }

//удаление сопуствующей папки с пиксельными контролями
bool CTrifle::DelPixFolder(CString name_dir, bool del_fold)
{
	WIN32_FIND_DATA FFData;
	HANDLE hFind = FindFirstFile(name_dir+"\\*.bmp", &FFData);
	// удаляем все bmp, чтобы вместе со скриншотами действий и с ПК
	//						DeleteFile(name_dir+"\\pixcontrol_*.bmp");
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			DeleteFile(name_dir+"\\"+FFData.cFileName);
		} while(FindNextFile(hFind, &FFData));
		FindClose(hFind);
	}
	DeleteFile(name_dir+"\\aip.log");
	DeleteFile(name_dir+"\\stat.txt");

	//УДАЛЯЕМ СКРИНШОТЫ
	hFind = FindFirstFile(name_dir+"\\play\\*.bmp", &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			DeleteFile(name_dir+"\\play\\"+FFData.cFileName);
		} while(FindNextFile(hFind, &FFData));
		FindClose(hFind);
	}		
	hFind = FindFirstFile(name_dir+"\\rec\\*.bmp", &FFData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do 
		{
			DeleteFile(name_dir+"\\rec\\"+FFData.cFileName);
		} while(FindNextFile(hFind, &FFData));
		FindClose(hFind);
	}		
	if (del_fold)
	{
		RemoveDirectory(name_dir+"\\rec");
		RemoveDirectory(name_dir+"\\play");
		RemoveDirectory(name_dir);
	}
	return true;
}

//копирование действий в буфер 
void CTrifle::ActsIntoBuf(CString test)
{
	"num=0//ver=4.9";
	if (AfxGetMainWnd()->OpenClipboard())
	{
		if (EmptyClipboard())
		{
			HGLOBAL clipbuffer;
			wchar_t* buffer;
			clipbuffer=GlobalAlloc(GMEM_DDESHARE, 2*test.GetLength()+2);
			buffer = (wchar_t*)GlobalLock(clipbuffer);
			test+='\0';
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPCSTR)test, 
				test.GetLength(), buffer, test.GetLength());
			GlobalUnlock(clipbuffer);
			SetClipboardData(CF_PRIVATEFIRST+3, clipbuffer);
		}
	}
	CloseClipboard();
}

//копирование в буфер
void CTrifle::CopyText(CString test)
{
	if (AfxGetMainWnd()->OpenClipboard())
	{
		if (EmptyClipboard())
		{
			HGLOBAL clipbuffer;
			wchar_t* buffer;
			clipbuffer=GlobalAlloc(GMEM_DDESHARE, 2*test.GetLength()+2);
			buffer = (wchar_t*)GlobalLock(clipbuffer);
			test+='\0';
			MultiByteToWideChar(CP_THREAD_ACP/*CP_ACP*/, 0/*MB_PRECOMPOSED*/, (LPCSTR)test, 
				test.GetLength(), buffer, test.GetLength());
			GlobalUnlock(clipbuffer);
			SetClipboardData(CF_UNICODETEXT, clipbuffer);
		}
	}
	CloseClipboard();
}
//запись в журнал
bool CTrifle::WriteJournal(CString sRec)
{
	CTime ct=CTime::GetCurrentTime();
	char ch[1024];
	sprintf_s(ch, "\n%02d.%02d.%02d\t%02d:%02d:%02d "+sRec, 
		ct.GetYear(), ct.GetMonth(), ct.GetDay(),
		ct.GetHour(), ct.GetMinute(), ct.GetSecond());
	CStdioFile sfLog;
	if (sPathToExe.GetLength()<3)
		GetProfileString("App","path_exe", "", sPathToExe.GetBuffer(1024), 1024);
	if (!sfLog.Open(sPathToExe+"\\Journal.txt", CFile::modeWrite))
	{
		if (!sfLog.Open(sPathToExe+"\\Journal.txt", CFile::modeWrite|CFile::modeCreate)){
			//** в статус строке пометка о невозможность ведения журнала
			return false;
		}   
	}
	sfLog.SeekToEnd();
	sfLog.WriteString(ch);
	sfLog.Close();
	return true;
}

char * CTrifle::NameClick(int mes)
{
	switch(mes)
	{
	case WM_LBUTTONDOWN:
	case WM_NCLBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_NCLBUTTONUP:
		return "LKM";
	case WM_LBUTTONDBLCLK:
	case WM_NCLBUTTONDBLCLK:
		return "DLKM";
	case WM_RBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_NCRBUTTONUP:
		return "RKM";
	case WM_RBUTTONDBLCLK:
	case WM_NCRBUTTONDBLCLK:
		return "DRKM";
	case WM_MBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_NCMBUTTONUP:
		return "MKM";
	case WM_MBUTTONDBLCLK:
	case WM_NCMBUTTONDBLCLK:
		return "DMKM";
	default:
	    return "";
	}
}

int CTrifle::CodeSysKey(CString key)
{
	switch(key[0])
	{
	case 'S':
		switch(key[1])
		{
		case 'H':
			return VK_SHIFT;
		case 'c':
			return VK_SCROLL;
		case 'P':
			return VK_SPACE;
		}
		break;
	case 'C':
		switch(key[1])
		{
		case 'T':
			return VK_CONTROL;
		case 'a':
			return VK_CAPITAL;
		}
		break;
	case 'A':
		switch(key[1])
		{
		case 'L':
			return VK_MENU;
		case 'P':
			return VK_APPS;
		}
		break;
	case 'L':
		switch(key[1])
		{
		case 'W':
			return VK_LWIN;
		case 'E':
			return VK_LEFT;
		}
		break;
	case 'R':
		switch(key[1])
		{
		case 'W':
			return VK_RWIN;
		case 'I':
			return VK_RIGHT;
		}
		break;
	case 'E':
		switch(key[1])
		{
		case 'S':
			return VK_ESCAPE;
		case 'n':
			return VK_RETURN;
		case 'N':
			return VK_END;
		}
		break;
	case 'P':
		switch(key[4])
		{
		case ' ':
			return VK_SNAPSHOT;
		case 'e':
			return VK_PAUSE;
		case 'U':
			return VK_PRIOR;
		case 'D':
			return VK_NEXT;
		}
		break;
	case 'D':
		switch(key[1])
		{
		case 'E':
			return VK_DELETE;
		case 'O':
			return VK_DOWN;
		}
		break;

	case 'F':
		if (key.GetLength()==3)
		{
			switch(key[2])
				{
			case '0':
				return VK_F10;
			case '1':
				return VK_F11;
			case '2':
				return VK_F12;
			case '3':
				return VK_F13;
			case '4':
				return VK_F14;
			case '5':
				return VK_F15;
			case '6':
				return VK_F16;
				}
		}
		switch(key[1])
		{
		case '1':
			return VK_F1;
		case '2':
			return VK_F2;
		case '3':
			return VK_F3;
		case '4':
			return VK_F4;
		case '5':
			return VK_F5;
		case '6':
			return VK_F6;
		case '7':
			return VK_F7;
		case '8':
			return VK_F8;
		case '9':
			return VK_F9;
		}
		break;
	case 'B':
		return VK_BACK;
	case 'I':
		return VK_INSERT;
	case 'H':
		return VK_HOME;
	case 'U':
		return VK_UP;
	case '1':
		return VK_NUMPAD1;
	case '2':
		return VK_NUMPAD2;
	case '3':
		return VK_NUMPAD3;
	case '4':
		return VK_NUMPAD4;
	case '5':
		return VK_NUMPAD5;
	case '6':
		return VK_NUMPAD6;
	case '7':
		return VK_NUMPAD7;
	case '8':
		return VK_NUMPAD8;
	case '9':
		return VK_NUMPAD9;
	case '0':
		return VK_NUMPAD0;
	case '+':
		return VK_ADD;
	case '-':
		return VK_SUBTRACT;
	case 'T':
		return VK_TAB;
	case '*':
		return VK_MULTIPLY;
	case '/':
		return VK_DIVIDE;
	case 'N':
		return VK_NUMLOCK;
	case '.':
		return VK_DECIMAL;
	}
	return 0;
}

//прееобразуем код клавиши в ее название
CString CTrifle::NameKey(int wpar, int Lang)
{
	//::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USER+31, 1, 0);
	switch (wpar)
	{
	case VK_BACK:
		return "[BackSp]";
	case VK_INSERT:
		return "[INSERT]";
	case VK_HOME:
		return "[HOME]";
	case VK_UP:
		return "[UP]";
		
	case VK_F1:
		return "[F1]";
	case VK_F2:
		return "[F2]";
	case VK_F3:
		return "[F3]";
	case VK_F4:
		return "[F4]";
	case VK_F5:
		return "[F5]";
	case VK_F6:
		return "[F6]";
	case VK_F7:
		return "[F7]";
	case VK_F8:
		return "[F8]";
	case VK_F9:
		return "[F9]";
	case VK_F10:
		return "[F10]";
	case VK_F11:
		return "[F11]";
	case VK_F12:
		return "[F12]";
	case VK_F13:
		return "[F13]";
	case VK_F14:
		return "[F14]";
	case VK_F15:
		return "[F15]";
	case VK_F16:
		return "[F16]";

	case VK_NUMPAD1:
		return "[1 NumPad]";
	case VK_NUMPAD2:
		return "[2 NumPad]";
	case VK_NUMPAD3:
		return "[3 NumPad]";
	case VK_NUMPAD4:
		return "[4 NumPad]";
	case VK_NUMPAD5:
		return "[5 NumPad]";
	case VK_NUMPAD6:
		return "[6 NumPad]";
	case VK_NUMPAD7:
		return "[7 NumPad]";
	case VK_NUMPAD8:
		return "[8 NumPad]";
	case VK_NUMPAD9:
		return "[9 NumPad]";
	case VK_NUMPAD0:
		return "[0 NumPad]";
	case VK_DECIMAL:
		return "[. NumPad]";
	case VK_ADD:
		return "[+ NumPad]";
	case VK_SUBTRACT:
		return "[- NumPad]";
	case VK_TAB:
		return "[TAB]";
	case VK_MULTIPLY:
		return "[* NumPad]";
	case VK_DIVIDE:
		return "[/ NumPad]";
	case VK_NUMLOCK:
		return "[NUMLOCK]";
	
	case VK_DELETE:
		return "[DELETE]";
	case VK_DOWN:
		return "[DOWN]";
		
	case VK_SNAPSHOT:
		return "[Prnt Scr]";
	case VK_PAUSE:
		return "[Pause]";
	case VK_PRIOR:
		return "[PageUp]";
	case VK_NEXT:
		return "[PageDown]";
		
	case VK_ESCAPE:
		return "[ESCAPE]";
	case VK_RETURN:
		return "[Enter]";
	case VK_END:
		return "[END]";
		
	case VK_CONTROL:
		return "[CTRL]";
	case VK_CAPITAL:
		return "[CapsLock]";

	case VK_SHIFT:
		return "[SHIFT]";
	case VK_SCROLL:
		return "[Scroll Lock]";
	case VK_SPACE:
		return "[SPACE]";

	case VK_MENU:
		return "[ALT]";
	case VK_APPS:
		return "[APPS]";

	case VK_LWIN:
		return "[LWIN]";
	case VK_LEFT:
		return "[LEFT]";

	case VK_RWIN:
		return "[RWIN]";
	case VK_RIGHT:
		return "[RIGHT]";

	case 189:
		return "\"-\"";
	case 187:
		return "\"=\"";
	case 49:
		return "\"1\"";
	case 50:
		return "\"2\"";
	case 51:
		return "\"3\"";
	case 52:
		return "\"4\"";
	case 53:
		return "\"5\"";
	case 54:
		return "\"6\"";
	case 55:
		return "\"7\"";
	case 56:
		return "\"8\"";
	case 57:
		return "\"9\"";
	case 48:
		return "\"0\"";
	case 81:{
		if (Lang==419){
			return "\"й\"";
		} else {
			if (Lang==409){
				return "\"q\"";
			} else {
				return "{81}";
			}
		}
		break;
				 }
	case 87:{
		if (Lang==419){
			return "\"ц\"";
		} else {
			if (Lang==409){
				return "\"w\"";
			} else {
				return "{87}";
			}
		}
		break;
				 }
	case 69:{
		if (Lang==419){
			return "\"у\"";
		} else {
			if (Lang==409){
				return "\"e\"";
			} else {
				return "{69}";
			}
		}
		break;
				 }
	case 80:{
		if (Lang==419){
			return "\"з\"";
		} else {
			if (Lang==409){
				return "\"p\"";
			} else {
				return "{80}";
			}
		}
		break;
				 }
	case 79:{
		if (Lang==419){
			return "\"щ\"";
		} else {
			if (Lang==409){
				return "\"o\"";
			} else {
				return "{79}";
			}
		}
		break;
				 }
	case 73:{
		if (Lang==419){
			return "\"ш\"";
		} else {
			if (Lang==409){
				return "\"i\"";
			} else {
				return "{73}";
			}
		}
		break;
				 }
	case 85:{
		if (Lang==419){
			return "\"г\"";
		} else {
			if (Lang==409){
				return "\"u\"";
			} else {
				return "{85}";
			}
		}
		break;
				 }
	case 89:{
		if (Lang==419){
			return "\"н\"";
		} else {
			if (Lang==409){
				return "\"y\"";
			} else {
				return "{89}";
			}
		}
		break;
				 }
	case 84:{
		if (Lang==419){
			return "\"е\"";
		} else {
			if (Lang==409){
				return "\"t\"";
			} else {
				return "{84}";
			}
		}
		break;
				 }
	case 82:{
		if (Lang==419){
			return "\"к\"";
		} else {
			if (Lang==409){
				return "\"r\"";
			} else {
				return "{82}";
			}
		}
		break;
				 }
	case 76:{
		if (Lang==419){
			return "\"д\"";
		} else {
			if (Lang==409){
				return "\"l\"";
			} else {
				return "{76}";
			}
		}
		break;
				 }
	case 75:{
		if (Lang==419){
			return "\"л\"";
		} else {
			if (Lang==409){
				return "\"k\"";
			} else {
				return "{75}";
			}
		}
		break;
				 }
	case 74:{
		if (Lang==419){
			return "\"о\"";
		} else {
			if (Lang==409){
				return "\"j\"";
			} else {
				return "{74}";
			}
		}
		break;
				 }
	case 72:{
		if (Lang==419){
			return "\"р\"";
		} else {
			if (Lang==409){
				return "\"h\"";
			} else {
				return "{72}";
			}
		}
		break;
				 }
	case 71:{
		if (Lang==419){
			return "\"п\"";
		} else {
			if (Lang==409){
				return "\"g\"";
			} else {
				return "{71}";
			}
		}
		break;
				 }
	case 70:{
		if (Lang==419){
			return "\"а\"";
		} else {
			if (Lang==409){
				return "\"f\"";
			} else {
				return "{70}";
			}
		}
		break;
				 }
	case 68:{
		if (Lang==419){
			return "\"в\"";
		} else {
			if (Lang==409){
				return "\"d\"";
			} else {
				return "{68}";
			}
		}
		break;
				 }
	case 83:{
		if (Lang==419){
			return "\"ы\"";
		} else {
			if (Lang==409){
				return "\"s\"";
			} else {
				return "{83}";
			}
		}
		break;
				 }
	case 65:{
		if (Lang==419){
			return "\"ф\"";
		} else {
			if (Lang==409){
				return "\"a\"";
			} else {
				return "{65}";
			}
		}
		break;
				 }
	case 77:{
		if (Lang==419){
			return "\"ь\"";
		} else {
			if (Lang==409){
				return "\"m\"";
			} else {
				return "{77}";
			}
		}
		break;
				 }
	case 78:{
		if (Lang==419){
			return "\"т\"";
		} else {
			if (Lang==409){
				return "\"n\"";
			} else {
				return "{78}";
			}
		}
		break;
				 }
	case 66:{
		if (Lang==419){
			return "\"и\"";
		} else {
			if (Lang==409){
				return "\"b\"";
			} else {
				return "{66}";
			}
		}
		break;
				 }
	case 86:{
		if (Lang==419){
			return "\"м\"";
		} else {
			if (Lang==409){
				return "\"v\"";
			} else {
				return "{86}";
			}
		}
		break;
				 }
	case 67:{
		if (Lang==419){
			return "\"с\"";
		} else {
			if (Lang==409){
				return "\"c\"";
			} else {
				return "{67}";
			}
		}
		break;
				 }
	case 88:{
		if (Lang==419){
			return "\"ч\"";
		} else {
			if (Lang==409){
				return "\"x\"";
			} else {
				return "{88}";
			}
		}
		break;
				 }
	case 90:{
		if (Lang==419){
			return "\"я\"";
		} else {
			if (Lang==409){
				return "\"z\"";
			} else {
				return "{90}";
			}
		}
		break;
				 }
	case 191:{
		if (Lang==419){
			return "\".\"";
		} else {
			if (Lang==409){
				return "\"/\"";
			} else {
				return "{191}";
			}
		}
		break;
				 }
	case 190:{
		if (Lang==419){
			return "\"ю\"";
		} else {
			if (Lang==409){
				return "\".\"";
			} else {
				return "{190}";
			}
		}
		break;
				 }
	case 188:{
		if (Lang==419){
			return "\"б\"";
		} else {
			if (Lang==409){
				return "\",\"";
			} else {
				return "{188}";
			}
		}
		break;
				 }
	case 220:{
		if (Lang==419){
			return "\"\\\"";
		} else {
			if (Lang==409){
				return "\"\\\"";
			} else {
				return "{220}";
			}
		}
		break;
				 }
	case 222:{
		if (Lang==419){
			return "\"э\"";
		} else {
			if (Lang==409){
				return "\"'\"";
			} else {
				return "{222}";
			}
		}
		break;
				 }
	case 186:{
		if (Lang==419){
			return "\"ж\"";
		} else {
			if (Lang==409){
				return "\";\"";
			} else {
				return "{186}";
			}
		}
		break;
				 }
	case 221:{
		if (Lang==419){
			return "\"ъ\"";
		} else {
			if (Lang==409){
				return "\"]\"";
			} else {
				return "{221}";
			}
		}
		break;
				 }
	case 219:{
		if (Lang==419){
			return "\"х\"";
		} else {
			if (Lang==409){
				return "\"[\"";
			} else {
				return "{219}";
			}
		}
		break;
				 }
	case 192:{
		if (Lang==419){
			return "\"ё\"";
		} else {
			if (Lang==409){
				return "\"`\"";
			} else {
				return "{192}";
			}
		}
		break;
				 }
	default:
		{
			char ch[128];
			sprintf_s(ch, "{%d}", wpar);
			return ch;
		}
					
	}
}

//прееобразуем код клика в его название
char * CTrifle::NameClick2(int upordown)
{
	switch (upordown)
	{
	case WM_LBUTTONDOWN:
	case WM_NCLBUTTONDOWN:
		return "LMB_down";
	case WM_LBUTTONUP:
	case WM_NCLBUTTONUP:
		return "LMB_up";
	case WM_LBUTTONDBLCLK:
	case WM_NCLBUTTONDBLCLK:
		return "LMBx2_down";
	case WM_RBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
		return "RMB_down";
	case WM_RBUTTONUP:
	case WM_NCRBUTTONUP:
		return "RMB_up";
	case WM_RBUTTONDBLCLK:
	case WM_NCRBUTTONDBLCLK:
		return "RMBx2_down";
	case WM_MBUTTONUP:
		return "MMB_up";
	case WM_MBUTTONDOWN:
		return "MMB_down";
	case WM_MBUTTONDBLCLK:
		return "MMBx2_down";
	}
	return "";
}

CString CTrifle::ClicksToStr(CUIntArray& upordown)
{
	CString res="";
	//	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USER31, 1, 0);
	
	for (int ii=0; ii<upordown.GetSize(); ii++)
	{
		res+=NameClick2(upordown[ii]);
	}
	res.Replace("LMB_downLMB_up", "LMB");
	res.Replace("LMBLMBx2_downLMB_up", "LMBx2");
	res.Replace("RMB_downRMB_up", "RMB");
	res.Replace("RMBRMBx2_downRMB_up", "RMBx2");
	return res;
}

CString CTrifle::ClicksToStr2(CUIntArray& upordown)
{
	CString res="";
	//	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USER31, 1, 0);
	
	for (int ii=0; ii<upordown.GetSize(); ii++)
	{
		if (ii>=upordown.GetSize())
			break;
		res+=NameClick2(upordown[ii]);
		res+=" + ";
	}
	res.Delete(res.GetLength()-3, 3);
	return res;
}

bool CTrifle::Get1Liter(CUIntArray& keys, CUIntArray& lang, CString &sKeys)
{
	switch(sKeys[0])
	{
	case ' ':
		lang.Add(0);
		keys.Add(VK_SPACE);
		
		return true ;
	case '-':
		lang.Add(0);
		keys.Add(189);
		
		return true ;
	case '=':
		lang.Add(0);
		keys.Add(187);
		
		return true ;
	case '1':
		lang.Add(0);
		keys.Add(49);
		
		return true ;
	case '2':
		lang.Add(0);
		keys.Add(50);
		
		return true ;
	case '3':
		lang.Add(0);
		keys.Add(51);
		
		return true ;
	case '4':
		lang.Add(0);
		keys.Add(52);
		
		return true ;
	case '5':
		lang.Add(0);
		keys.Add(53);
		
		return true ;
	case '6':
		lang.Add(0);
		keys.Add(54);
		
		return true ;
	case '7':
		lang.Add(0);
		keys.Add(55);
		
		return true ;
	case '8':
		lang.Add(0);
		keys.Add(56);
		
		return true ;
	case '9':
		lang.Add(0);
		keys.Add(57);
		
		return true ;
	case '0':
		lang.Add(0);
		keys.Add(48);
		
		return true ;

	case 'Q':
	case 'q':
		lang.Add(409);
		keys.Add(81);
		
		return true ;
	case 'W':
	case 'w':
		lang.Add(409);
		keys.Add(87);
		
		return true ;
	case 'E':
	case 'e':
		lang.Add(409);
		keys.Add(69);
		
		return true ;
	case 'P':
	case 'p':
		lang.Add(409);
		keys.Add(80);
		
		return true ;
	case 'O':
	case 'o':
		lang.Add(409);
		keys.Add(79);
		
		return true ;
	case 'I':
	case 'i':
		lang.Add(409);
		keys.Add(73);
		
		return true ;
	case 'U':
	case 'u':
		lang.Add(409);
		keys.Add(85);
		
		return true ;
	case 'Y':
	case 'y':
		lang.Add(409);
		keys.Add(89);
		
		return true ;
	case 'T':
	case 't':
		lang.Add(409);
		keys.Add(84);
		
		return true ;
	case 'R':
	case 'r':
		lang.Add(409);
		keys.Add(82);
		
		return true ;
	case 'L':
	case 'l':
		lang.Add(409);
		keys.Add(76);
		
		return true ;
	case 'K':
	case 'k':
		lang.Add(409);
		keys.Add(75);
		
		return true ;
	case 'J':
	case 'j':
		lang.Add(409);
		keys.Add(74);
		
		return true ;
	case 'H':
	case 'h':
		lang.Add(409);
		keys.Add(72);
		
		return true ;
	case 'G':
	case 'g':
		lang.Add(409);
		keys.Add(71);
		
		return true ;
	case 'F':
	case 'f':
		lang.Add(409);
		keys.Add(70);
		
		return true ;
	case 'D':
	case 'd':
		lang.Add(409);
		keys.Add(68);
		
		return true ;
	case 'S':
	case 's':
		lang.Add(409);
		keys.Add(83);
		
		return true ;
	case 'A':
	case 'a':
		lang.Add(409);
		keys.Add(65);
		
		return true ;
	case 'M':
	case 'm':
		lang.Add(409);
		keys.Add(77);
		
		return true ;
	case 'N':
	case 'n':
		lang.Add(409);
		keys.Add(78);
		
		return true ;
	case 'B':
	case 'b':
		lang.Add(409);
		keys.Add(66);
		
		return true ;
	case 'V':
	case 'v':
		lang.Add(409);
		keys.Add(86);
		
		return true ;
	case 'C':
	case 'c':
		lang.Add(409);
		keys.Add(67);
		
		return true ;
	case 'X':
	case 'x':
		lang.Add(409);
		keys.Add(88);
		
		return true ;
	case 'Z':
	case 'z':
		lang.Add(409);
		keys.Add(90);
		
		return true ;
	case '/':
		lang.Add(409);
		keys.Add(191);
		
		return true ;
	case '>':
		lang.Add(409);
		keys.Add(190);
		
		return true ;
	case '.':
		lang.Add(419);
		keys.Add(191);
		
		return true ;
	case ',':
		lang.Add(409);
		keys.Add(188);
		
		return true ;
	case '|':
		lang.Add(409);
		keys.Add(220);
		
		return true ;
	case '\'':
		lang.Add(409);
		keys.Add(222);
		
		return true ;
	case ';':
		lang.Add(409);
		keys.Add(186);
		
		return true ;
	case ']':
		lang.Add(409);
		keys.Add(221);
		
		return true ;
	case '[':
		lang.Add(409);
		keys.Add(219);
		
		return true ;
	case '`':
		lang.Add(409);
		keys.Add(192);
		
		return true ;
	case 'Й':
	case 'й':
		lang.Add(419);
		keys.Add(81);
		
		return true ;
	case 'Ц':
	case 'ц':
		lang.Add(419);
		keys.Add(87);
		
		return true ;
	case 'У':
	case 'у':
		lang.Add(419);
		keys.Add(69);
		
		return true ;
	case 'З':
	case 'з':
		lang.Add(419);
		keys.Add(80);
		
		return true ;
	case 'Щ':
	case 'щ':
		lang.Add(419);
		keys.Add(79);
		
		return true ;
	case 'Ш':
	case 'ш':
		lang.Add(419);
		keys.Add(73);
		
		return true ;
	case 'Г':
	case 'г':
		lang.Add(419);
		keys.Add(85);
		
		return true ;
	case 'Н':
	case 'н':
		lang.Add(419);
		keys.Add(89);
		
		return true ;
	case 'Е':
	case 'е':
		lang.Add(419);
		keys.Add(84);
		
		return true ;
	case 'К':
	case 'к':
		lang.Add(419);
		keys.Add(82);
		
		return true ;
	case 'Д':
	case 'д':
		lang.Add(419);
		keys.Add(76);
		
		return true ;
	case 'Л':
	case 'л':
		lang.Add(419);
		keys.Add(75);
		
		return true ;
	case 'О':
	case 'о':
		lang.Add(419);
		keys.Add(74);
		
		return true ;
	case 'Р':
	case 'р':
		lang.Add(419);
		keys.Add(72);
		
		return true ;
	case 'П':
	case 'п':
		lang.Add(419);
		keys.Add(71);
		
		return true ;
	case 'А':
	case 'а':
		lang.Add(419);
		keys.Add(70);
		
		return true ;
	case 'В':
	case 'в':
		lang.Add(419);
		keys.Add(68);
		
		return true ;
	case 'Ы':
	case 'ы':
		lang.Add(419);
		keys.Add(83);
		
		return true ;
	case 'Ф':
	case 'ф':
		lang.Add(419);
		keys.Add(65);
		
		return true ;
	case 'Ь':
	case 'ь':
		lang.Add(419);
		keys.Add(77);
		
		return true ;
	case 'Т':
	case 'т':
		lang.Add(419);
		keys.Add(78);
		
		return true ;
	case 'И':
	case 'и':
		lang.Add(419);
		keys.Add(66);
		
		return true ;
	case 'М':
	case 'м':
		lang.Add(419);
		keys.Add(86);
		
		return true ;
	case 'С':
	case 'с':
		lang.Add(419);
		keys.Add(67);
		
		return true ;
	case 'Ч':
	case 'ч':
		lang.Add(419);
		keys.Add(88);
		
		return true ;
	case 'Я':
	case 'я':
		lang.Add(419);
		keys.Add(90);
		
		return true ;
	case 'Ю':
	case 'ю':
		lang.Add(419);
		keys.Add(190);
		
		return true ;
	case 'Б':
	case 'б':
		lang.Add(419);
		keys.Add(188);
		
		return true ;
	case '\\':
		lang.Add(419);
		keys.Add(220);
		
		return true ;
	case 'Э':
	case 'э':
		lang.Add(419);
		keys.Add(222);
		
		return true ;
	case 'Ж':
	case 'ж':
		lang.Add(419);
		keys.Add(186);
		
		return true ;
	case 'Ъ':
	case 'ъ':
		lang.Add(419);
		keys.Add(221);
		
		return true ;
	case 'Х':
	case 'х':
		lang.Add(419);
		keys.Add(219);
		
		return true ;
	case 'Ё':
	case 'ё':
		lang.Add(419);
		keys.Add(192);
		
		return true ;
	}
	return false;
}
bool CTrifle::Get1Click(CUIntArray& keys, CUIntArray& upordown, CString &sKeys)
{
	if (sKeys.GetLength()<2) return false;
	switch(sKeys[0])
	{
	case 'L':
		keys.Add(1);
		switch(sKeys[4])
		{
		case 'd':
			upordown.Add(WM_LBUTTONDOWN);
			sKeys.Delete(0, 8);
			break;
		case 'u':
			upordown.Add(WM_LBUTTONUP);
			sKeys.Delete(0, 6);
		    break;
		case '2':
			upordown.Add(WM_LBUTTONDBLCLK);
			sKeys.Delete(0, 10);
			break;
		}
		sKeys.TrimLeft(' ');
		sKeys.TrimLeft('+');
		sKeys.TrimLeft(' ');
		return true;
	case 'R':
		keys.Add(2);
		switch(sKeys[4])
		{
		case 'd':
			upordown.Add(WM_RBUTTONDOWN);
			sKeys.Delete(0, 8);
			break;
		case 'u':
			upordown.Add(WM_RBUTTONUP);
			sKeys.Delete(0, 6);
			break;
		case '2':
			upordown.Add(WM_RBUTTONDBLCLK);
			sKeys.Delete(0, 10);
			break;
		}
		sKeys.TrimLeft(' ');
		sKeys.TrimLeft('+');
		sKeys.TrimLeft(' ');
		return true;
	case 'M':
		keys.Add(3);
		switch(sKeys[4])
		{
		case 'd':
			upordown.Add(WM_MBUTTONDOWN);
			sKeys.Delete(0, 8);
			break;
		case 'u':
			upordown.Add(WM_MBUTTONUP);
			sKeys.Delete(0, 6);
			break;
		case '2':
			upordown.Add(WM_MBUTTONDBLCLK);
			sKeys.Delete(0, 10);
			break;
	}
		sKeys.TrimLeft(' ');
		sKeys.TrimLeft('+');
		sKeys.TrimLeft(' ');
		return true;
	}
	

	return false;
}
bool CTrifle::Get1Key(CUIntArray& keys, CUIntArray& upordown, CUIntArray& lang, CString &sKeys)
{   
	if (sKeys.GetLength()<2) return false;
	if (sKeys[0]=='[')
	{//служебная клавиша
		lang.Add(409);
		sKeys.Delete(0);
		int fi=sKeys.Find(']');
		if (fi==-1) return false;
		int key_cod=CodeSysKey(sKeys.Left(fi));
		if (!key_cod)
			return false;
		keys.Add(key_cod);
		sKeys.Delete(0, fi+1);
		if (sKeys.GetLength()<2)
		{
			keys.Add(key_cod);
			lang.Add(409);
			upordown.Add(WM_KEYDOWN);
			upordown.Add(WM_KEYUP);
			return true;
		}
		if (sKeys[0]=='_')
		{
			if (sKeys[1]=='d')
			{
				upordown.Add(WM_KEYDOWN);
				sKeys.Delete(0, 5);
			} else {
				upordown.Add(WM_KEYUP);
				sKeys.Delete(0, 3);
			}
		} else {
			keys.Add(key_cod);
			lang.Add(409);
			upordown.Add(WM_KEYDOWN);
			upordown.Add(WM_KEYUP);
		}
		return true;
	} else if (sKeys[0]=='\"')
	{
		sKeys.Delete(0);
		bool ret=0;
		while (ret=Get1Liter(keys, lang, sKeys))
		{	//берем закавыченную строчку литеральных символов
			if (!ret) return false;
			sKeys.Delete(0);
			if (sKeys[0]=='\"')
			{
				sKeys.Delete(0);
				if (!sKeys.GetLength())
				{
					lang.Add(lang[lang.GetSize()-1]);
					keys.Add(keys[keys.GetSize()-1]);
					upordown.Add(WM_KEYDOWN);
					upordown.Add(WM_KEYUP);
					return true;
				}
				if (sKeys[0]=='_')
				{
					if (sKeys[1]=='d')
					{
						upordown.Add(WM_KEYDOWN);
						sKeys.Delete(0, 5);
					} else {
						upordown.Add(WM_KEYUP);
						sKeys.Delete(0, 3);
					}
				} else {
					lang.Add(lang[lang.GetSize()-1]);
					keys.Add(keys[keys.GetSize()-1]);
					upordown.Add(WM_KEYDOWN);
					upordown.Add(WM_KEYUP);
				}
				return true;
			} else {	//сразу другой символ идет, а текущий и нажался и отжался
				lang.Add(lang[lang.GetSize()-1]);
				keys.Add(keys[keys.GetSize()-1]);
				upordown.Add(WM_KEYDOWN);
				upordown.Add(WM_KEYUP);
			}
		}
		return ret;
	} else if (sKeys[0]=='{')
	{
		lang.Add(0);
		sKeys.Delete(0);
		int fi=sKeys.Find('}');
		if (fi==-1) return false;
		int key_cod=atoi(sKeys.Left(fi));
		if (!key_cod)
			return false;
		keys.Add(key_cod);
		sKeys.Delete(0, fi+1);
		if (sKeys.GetLength()<2)
		{
			keys.Add(key_cod);
			lang.Add(409);
			upordown.Add(WM_KEYDOWN);
			upordown.Add(WM_KEYUP);
			return true;
		}
		if (sKeys[0]=='_')
		{
			if (sKeys[1]=='d')
			{
				upordown.Add(WM_KEYDOWN);
				sKeys.Delete(0, 5);
			} else {
				upordown.Add(WM_KEYUP);
				sKeys.Delete(0, 3);
			}
		} else {
			keys.Add(key_cod);
			lang.Add(0);
			upordown.Add(WM_KEYDOWN);
			upordown.Add(WM_KEYUP);
		}
		return true;
	} else return false;
	//return true;
}

bool CTrifle::StrToClicks(CUIntArray& keys, CUIntArray& upordown, CString sKeys)
{   
	if (sKeys=="")
		return false;
	while (Get1Click(keys, upordown, sKeys))
	{
	}
	if (sKeys!="")
		return false;
	return true;
}

bool CTrifle::StrToKeys(CUIntArray& keys, CUIntArray& upordown, CUIntArray& lang, CString sKeys)
{   
	if (sKeys.GetLength()<3)
		return false;
	while (Get1Key(keys, upordown, lang, sKeys))
	{
	}
	if (sKeys!="")
		return false;
	return true;
}

bool CTrifle::StrToTime(CUIntArray& dTime, CString sKeys)
{   
	if (!sKeys.GetLength())
		return false;
	dTime.Add(atoi(sKeys));
	int fi=sKeys.Find(", ");
	while (fi>-1)
	{
		sKeys.Delete(0, fi+2);
		dTime.Add(atoi(sKeys));
		fi=sKeys.Find(", ");
	}
	return true;
}

bool CTrifle::StrToLPars(CDWordArray& lpars, CString sKeys)
{   
	if (!sKeys.GetLength())
		return false;
	DWORD dw;
	int fi=sKeys.Find(", ");
	if (fi==-1)
		 sscanf_s(sKeys, "%X", &dw);
	else sscanf_s(sKeys.Left(fi), "%X", &dw);
	lpars.Add(dw);
	while (fi>-1)
	{
		sKeys.Delete(0, fi+2);
		sscanf_s(sKeys.Left(fi), "%x", &dw);
// 		char ch[100];
// 		sprintf_s(ch, "%X", dw);
		lpars.Add(dw);
		fi=sKeys.Find(", ");
	}
	return true;
}

//with_r - имена нажатий с переходами строк
CString CTrifle::KeysToStr(CUIntArray& keys, CUIntArray& upordown, CUIntArray& lang, bool with_r)
{
	CString res="";
	CString tmp1="";
	CString tmp2="";
	int old_key_r=0;
//	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_USER31, 1, 0);

	for (int ii=0; ii<keys.GetSize(); ii++)
	{
		if (ii>=upordown.GetSize() || ii>=lang.GetSize())
			break;
		tmp2=NameKey(keys[ii], lang[ii]);
		if (ii+1<keys.GetSize())
			if (keys[ii]==keys[ii+1] && !UpOrDown(upordown[ii]) && UpOrDown(upordown[ii+1]))
			{	//слияние нажатия и отжатия
				res+=tmp2;
				ii++;
				if (with_r && res.GetLength()-old_key_r>50)
				{
					old_key_r=res.GetLength();
					res+="\r\n";
				}
				continue;
			}
		if (tmp2.GetLength()==3 && tmp2[0]=='\"' && tmp2[2]=='\"' && ii+3<keys.GetSize())
		{ //проверяем слияние внутри 4 действий
			if (keys[ii]==keys[ii+2] && !UpOrDown(upordown[ii]) && UpOrDown(upordown[ii+2]) &&
				keys[ii+1]==keys[ii+3] && !UpOrDown(upordown[ii+1]) && UpOrDown(upordown[ii+3]))
			{	//слияние нажатия и отжатия
				tmp1=NameKey(keys[ii+1], lang[ii+1]);
				if (tmp1.GetLength()==3 && tmp1[0]=='\"' && tmp1[2]=='\"')
				{
					res+=tmp2+tmp1;
					ii+=3;
					if (with_r && res.GetLength()-old_key_r>50)
					{
						old_key_r=res.GetLength();
						res+="\r\n";
					}
					continue;
				}
			//	continue;
			}
			if (keys[ii]==keys[ii+3] && !UpOrDown(upordown[ii]) && UpOrDown(upordown[ii+3]) &&
				keys[ii+1]==keys[ii+2] && !UpOrDown(upordown[ii+1]) && UpOrDown(upordown[ii+2]))
			{	//слияние нажатия и отжатия
				tmp1=NameKey(keys[ii+1], lang[ii+1]);
				if (tmp1.GetLength()==3 && tmp1[0]=='\"' && tmp1[2]=='\"')
				{
					res+=tmp2+tmp1;
					ii+=3;
					if (with_r && res.GetLength()-old_key_r>50)
					{
						old_key_r=res.GetLength();
						res+="\r\n";
					}
					continue;
				}
			}
		}
		res+=tmp2+(UpOrDown(upordown[ii]) ? "_up" : "_down");
//		res.Delete(0, 100);
		if (with_r && res.GetLength()-old_key_r>50)
		{
			old_key_r=res.GetLength();
			res+="\r\n";
		}
	}
	res.Replace("\"\"", "");
	return res;
}

//отжатие (1) или нажатие (0) клавиши
//дубликат из CRecSaveLoad
bool CTrifle::UpOrDown(UINT code)
{
	switch (code){
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_NCLBUTTONDOWN:
	case WM_NCLBUTTONDBLCLK:
		{
			return false;
		}
	case WM_SYSKEYUP:
	case WM_KEYUP:
	case WM_LBUTTONUP:
	case WM_NCLBUTTONUP:
		{
			return true;
		}
		//действия правой мышью
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_NCRBUTTONDOWN:
	case WM_NCRBUTTONDBLCLK:
		{
			return false;
		}
	case WM_RBUTTONUP:
	case WM_NCRBUTTONUP:
		{
			return true;
		}
	}
#ifdef LOG 
	RecordLog("CRecSaveLoad::UpOrDown неправильный code");
#endif
	return true;
}

CString CTrifle::GetNum(CString aTmp)// Для выделения из строки цифр, используется для получения координат
{
	int lstr = strlen(aTmp);
	int n = aTmp.Find("=",0)+1;
	aTmp = aTmp.Right((lstr - n));
	return aTmp;
}

int CTrifle::Find(CStringArray &tmpMyList, CString str)
{
	CString cs;
	int i,l;
	for(i=0,l=tmpMyList.GetSize();i<l;i++)
	{
		cs=tmpMyList.GetAt(i);
		if(cs.Find(str)>-1)
			return i;
	}
	return -1;	
}

void CTrifle::OnParseStr(CStringArray &aList, CString tmpStr)
{
	const CString wordDelim = "\"!<>{} [](),";
	enum CStates {ScanNormal, ScanBracket, ScanQuoted, ScanPunctuation};
	CString tmp;
	CStates mStates = ScanNormal;
	CString CurWord;
	tmp = tmpStr;
		for (int jj=0; jj < tmp.GetLength(); jj++)
		{
			char tmpch = tmp[jj];
			switch (mStates)
			{
				case ScanNormal:
					if ((tmpch == '(') || (tmpch == ')'))
					{
						if (!CurWord.IsEmpty())
						{
							aList.Add(CurWord);
						}
						CurWord = "";
						mStates = ScanBracket;
					}else{
						if (tmpch == '\"')
						{
							if (!CurWord.IsEmpty())
							{
								aList.Add(CurWord);
							}
							CurWord = "";
						mStates = ScanQuoted;
						}else{
							if (wordDelim.Find(tmpch, 0) != -1)
							{
								if (!CurWord.IsEmpty())
								{	
									if (tmpch == ' ')
									{
										CurWord += tmpch;

									}else{
										aList.Add(CurWord);
										CurWord = "";
										mStates = ScanPunctuation;
									}
									
								}
								
							}else{
								CurWord += tmpch;
							}
						}						
					}
					break;
				case ScanBracket:
					if (wordDelim.Find(tmpch, 0) != -1)
					{	
						if (!CurWord.IsEmpty())
						{
							aList.Add(CurWord);
							CurWord = "";
						}						
						mStates = ScanPunctuation;
					}else{
						if ((tmpch == ')') || (tmpch == '('))
						{
							// Прежде чем записать слово нужно его проверить
							if (!CurWord.IsEmpty())
							{
								aList.Add(CurWord);
								CurWord = "";
							}							
							mStates = ScanNormal;
						}else{
							CurWord += tmpch;
						}						
					}				
					break;
				case ScanQuoted:					
					if (wordDelim.Find(tmpch, 0) != -1)
					{
						//aList.Add(CurWord);
						//CurWord = "";
						if (tmpch == '\"')
						{	
							aList.Add(CurWord);
						    CurWord = "";
							mStates = ScanNormal;
						}else{
							// Вот в этом месте пишет лишнюю скобку потому что не тываются остальные разделители
							if ((tmpch == ')') || (tmpch == '('))
							{
								// Прежде чем записать слово нужно его проверить
								if (!CurWord.IsEmpty())
								{
									aList.Add(CurWord);
									CurWord = "";
								}
								mStates = ScanNormal;
							}else{
								CurWord += tmpch;
								mStates = ScanPunctuation;
							}							
						}						
					}else{
						if (tmpch == '\"')
						{
							aList.Add(CurWord);
							CurWord = "";
							mStates = ScanNormal;
						}else{
							CurWord += tmpch;
							mStates = ScanNormal;
						}						
					}
					break;
				case ScanPunctuation:
					if (tmpch =='(')
					{
						//CurWord = "(";
						mStates = ScanBracket;
					}else{
						if (tmpch == '\"')
						{
							mStates = ScanQuoted;
						}else{
							if (wordDelim.Find(tmpch, 0) == -1)
							{
								if (!CurWord.IsEmpty())
								{
									//aList.Add(CurWord);
									//CurWord = "";									
									CurWord += tmpch;
									mStates = ScanNormal;
								}else{									
									//aList.Add(CurWord);
									//CurWord = "";
									CurWord = tmpch;								
								}
								mStates = ScanNormal;
							}else{							
								mStates = ScanNormal;
							}
						}						
						
					}
					break;

			}
		}
		if (mStates == ScanBracket)
		{
			//MessageBox("Не закрыта скобка!");
		}
		if (!CurWord.IsEmpty())
		{
			aList.Add(CurWord);
		}
	
}

BOOL CTrifle::IsMODIInstal() // Функция проверки наличия установленного MODI
{
	// Проверяем наличие библиотеки на компьтере
	CFileFind myFind;
	CString PathModi = "C:\\Program Files\\Common Files\\Microsoft Shared\\MODI";
	BOOL dWorking;
	DWORD dwAtrr = GetFileAttributes(PathModi);
	if (dwAtrr == 0xffffffff) // Проверяем наличие папки
	{
		DWORD dwError = GetLastError(); 		
		if(dwError == ERROR_FILE_NOT_FOUND)  
		{ 
			myFind.Close();
			return FALSE;  // Если папки не существует возвращаем ЛОЖЬ
		} 
	}else{
		// Если папка существует то получаем все подкаталоги которые в ней находятся 
		dWorking = myFind.FindFile(PathModi +    "\\*.*");
		CStringArray ModiCatalog;
		while  (dWorking)  
		{  		
			dWorking = myFind.FindNextFile(); 			
			if (myFind.IsDirectory()&& !myFind.IsDots())  
			{  
				ModiCatalog.Add(myFind.GetFileName());		
			}
		}
		// Перебираем список подкаталогов и проверяем наличие вних библиотеки MDIVWCTL.DLL
		for (int i = 0; i < ModiCatalog.GetSize(); i++)
		{
			CString PathFile = PathModi + "\\" + ModiCatalog.GetAt(i) + "\\MDIVWCTL.DLL";
			if (IsFileExist(PathFile))
			{
				myFind.Close();
				return TRUE;			
			}else{
				continue;
			}
		}
		myFind.Close();
		return FALSE;		
	}
	return FALSE;
}

int CTrifle::isFindTemplateInText (CString sTemplate, CString TextForSearch)// Поиск текста по шаблону
{
	do 
	{
		int position = sTemplate.Find("*");
		if (position == -1)
		{
			if (TextForSearch.Find(sTemplate, 0)==-1)
				return FALSE;
			else return TRUE;			
		}
		int fi2 = TextForSearch.Find(sTemplate.Left(position), 0);
		if (fi2 == -1)return FALSE;			
		TextForSearch.Delete(0, fi2+position);
		sTemplate.Delete(0, position+1);
	} while (sTemplate.GetLength() > 0);
	return TRUE;
}

void CTrifle::GetSystmLang(CStringArray &langStringArr) // Получаем языки ситемы
{
	HKL * lpList = new HKL;
	int wLang = GetKeyboardLayoutList(0, NULL);	
	wLang = GetKeyboardLayoutList(wLang, lpList);
	HKL hklCurrent;
	char szBuf[256];	
	for(int i=0; i<wLang; i++)
	{
		// Берем очередной идентификатор раскладки 
		hklCurrent = *(lpList + i);		
		// Получаем название национального языка 
		GetLocaleInfo(
			MAKELCID(((UINT)hklCurrent & 0xffffffff), 
			SORT_DEFAULT),
			LOCALE_SLANGUAGE, szBuf, 512);
		/*char ch1[256];
		int redex = 10;
		CString tmp = itoa(	MAKELCID(((UINT)hklCurrent & 0xffffffff), 
			SORT_DEFAULT), ch1, redex);*/
		langStringArr.Add(szBuf);				
	}	
}


