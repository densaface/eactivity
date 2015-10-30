//#include "app.h"
#include "bmpext/Dib3.h"
#include <string>
using namespace std;
//#include "appendHead.h"
//#include "WinWork.h"
// Trifle1.h: interface for the CTrifle class.
//
//////////////////////////////////////////////////////////////////////
#define ERROR_REPLAY_OCR_WAIT_TEXT 71
#define ERROR_REPLAY_MODIERROR1 75
#define ERROR_REPLAY_CANTCONNECTMODI 70


#if !defined(AFX_TRIFLE1_H__C205DA1F_7C97_4A2F_BF3D_0CD2A7F808BD__INCLUDED_)
#define AFX_TRIFLE1_H__C205DA1F_7C97_4A2F_BF3D_0CD2A7F808BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTrifle  
{
public:
	BOOL InvertRectLine(CDC *pDc, CPoint ptFrom, CPoint ptTo);
	void BlinkRectangle(int x1, int y1, int x2, int y2, int SpeedReplay);
	//РАБОТА С COMS
// 	bool ComsToSC(CStringArray &coms, CStringArray &saBmps, CUIntArray &typeSr, 
// 		CUIntArray &xl, CUIntArray &xr, CUIntArray &yt, CUIntArray &yb,
// 		CUIntArray &gclickx, CUIntArray &gclicky, CUIntArray &gtypeClick, CUIntArray &gRx, CUIntArray &gRy);
	CString GetFirstBmpFromPC(CStringArray &coms);
	CString GetFirstBmpFromPC2(CStringArray &coms, int &counPict);
	CString GetBmpFromPC3(CStringArray &coms, int numPict, int &counPict);
	CString GetStrFromTypeClick(int TypeClick);
	int GetTypeClickFromStr(CString TypeClick);
	bool SetNodePicRpl(CStringArray &COMS, int &num_bmp, int &NumNodR);

	PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
	void CreateBMPFile(LPCSTR pszFile, PBITMAPINFO pbi, 
		HBITMAP hBMP, HDC hDC);
	void SaveBitmap(HBITMAP bmp, LPCSTR file);
	void SaveScreenToBmp(int x, int y, CString path, int UN, 
		int rectx1=-1, int recty1=-1, int rectx2=-1, int recty2=-1);
	CString SaveHWNDToBmp(int x, int y, CString path, HWND child);
	//удаление сопуствующей папки с пиксельными контролями
	bool DelPixFolder(CString name_dir, bool del_fold=true);
	//работа с буфером обмена
	void CopyText(CString test);
	CString GetText();
	void ActsIntoBuf(CString test);
	CString GetActsFromBuf();
	bool WriteJournal(CString sRec);
	CString ClicksToStr(CUIntArray& upordown);
	CString ClicksToStr2(CUIntArray& upordown);
	CString KeysToStr(CUIntArray& keys, CUIntArray& upordown, CUIntArray& lang, bool with_r=false);
	bool StrToLPars(CDWordArray& lpars, CString sKeys);
	bool StrToTime(CUIntArray& dTime, CString sKeys);
	bool StrToClicks(CUIntArray& keys, CUIntArray& upordown, CString sKeys);
	bool StrToKeys(CUIntArray& keys, CUIntArray& upordown, CUIntArray& lang, CString sKeys);
	bool Get1Click(CUIntArray& keys, CUIntArray& upordown, CString &sKeys);
	bool Get1Key  (CUIntArray& keys, CUIntArray& upordown, CUIntArray& lang, CString &sKeys);
	bool Get1Liter(CUIntArray& keys, CUIntArray& lang, CString &sKeys);
	int CodeSysKey(CString key);
	CString NameKey(int wpar, int Lang);
	char * NameClick(int mes);
	char * NameClick2(int upordown);
	bool UpOrDown(UINT code);
	CString sPathToExe;
	bool SaveArc(CString NameAip, CString NameArc);
	void MakeArchiv(CString fName);

	bool IfProccessExist(CString &sProcess);
	CString ExtractFileName(CString &NameFile);
	CString ExtractPath(CString &NameFile);
	CString GetPixPath(CString &aipName, CString &path_exe, bool DirCreate);
//	CString GetPixPathOld(CString &aipName, CString &path_exe);
	bool IsFileExist(CString sFile);
#ifdef LOG
	bool RecordLog(CString szRec, int count=0);
#endif
	COLORREF AddColor(COLORREF beg_col, int r, int g, int b);
	bool IsDirExist(CString sDir);
	UINT GetIds(UINT IDS);
	UINT TransModifiers(WORD wMod);
//	void SetNumLan(int NumLanSet);
	HANDLE h;
	bool MyReadString(CStdioFile &file, bool &endFile, CString &f_str);
	void TransformKeyLayout(int &code);
	void UpperCase2(int &code);
	CTrifle();
	virtual ~CTrifle();
	void RemStr(CString &str, CString razd1, CString razd2, bool delrazd=true);
	//проверка: нужно ли переключать клаву
	bool ToogleKeyb(UINT code);
	CString ExtractStr(CString str, CString razd1, CString razd2, bool delrazd=false);
	CString IntToStr(int ii);
	CString MyGetWindowText(HWND child);
	CString MyGetClassName(HWND child);
	CString ExtrTime(CString str);
	BOOL Is64BitOS();
	CString XToStr(LPARAM hw);
	BOOL BringWindowToForeground(HWND hw);
	//пошаговое перемещение курсора
	void MySetCursorPos(int x, int y);
	void CapSetCursorPos(int x, int y);
	int GetNumLan();
	int GetPartner();
	string getEnd(int val);
	void TrimKavich(CString &sRes);
	CString GetNum(CString aTmp);// Для выделения из строки цифр, используется для получения координат
	int Find(CStringArray &tmpMyList, CString str); // Поиск строки в массиве строк
	void OnParseStr(CStringArray &aList, CString tmpStr);// Разбивает строку на подстроки по основным разделителям("!<>{} [](),)
	BOOL IsMODIInstal(); // Функция проверки наличия установленного MODI
	void GetSystmLang(CStringArray &langStringArr); // Получаем языки системы
	int isFindTemplateInText (CString needle, CString tmpstrlen); // Поиск текста по щаблону
//	int NumLan;
protected:
};


#endif // !defined(AFX_TRIFLE1_H__C205DA1F_7C97_4A2F_BF3D_0CD2A7F808BD__INCLUDED_)
