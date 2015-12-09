#include "trifle1.h"
#include "cpuusage.h"
#include <afxcoll.h>
#include <afxtempl.h>
#include <string>
typedef  CArray  < CBitmap, int > MyBitAr;
typedef  CArray  < CRect, CRect > MyCRectAr;

#define id_hot_klav	1130
typedef  CArray  < HWND, int> hwnd_Array;
//��� �������� �������� �������� ����
struct sBalReitings
{
	int tt;
	HWND hw;
//	hwnd_Array hws;
	int bals;
	//������ ���������, ���� ������� ������� �� ������������
	bool norm_capt;
};
struct sBalChildReits
{
	HWND main_hw;
	HWND chi_hw;
	int bals;
};

typedef  CArray  <sBalReitings,  int> mai_hwnd_Array;
typedef  CArray  <sBalChildReits,  int> chi_hwnd_Array;
struct greenroad
{
	int numRoad;
	//numRoad=1     - ��� ������������� ������ ����� �������� � ���������� ��������
	//numRoad=2	    - ��� ������ ������� ������ ��� GOTO ������ �������� (� ������ ���������� �������� ��)
	//numRoad=3	    - ��� ������ ������� ������ ��� GOTO ������ �������� (� ������ ������� ��)
	//numRoad=21    - ��� �������� ��������������� ��������� �� ���������� �����
	//numRoad=4		- � ������������� ����� ��������� � �������������� ��
	//numRoad=5		- � ������������� ������ ���������� ������� ������ ��� ������ � �����������
	//numRoad=6		- � ������������� ������ ������ ���������� ����������
	//numRoad=15	- � ������������� ������ �������� �������
	int par1;
	int par2;
	int par3;
	int par4;
	void  operator = (const greenroad  &gr);
	greenroad();
};
//���������, ���������� ��������� ������		m_cMainDirectiv
struct sVariables
{
  CString  name;
  CString	opis;
  int    type_var;
  //0 - int
  //1 - String
  //2 - File
  //������� ���������
  int iRes;
  CString sRes;
  //sVariableCurrentRec();
};
typedef  CArray  < sVariables, int > aVariables;

typedef struct ssBGR {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char pad;
	bool  operator == (ssBGR  &bgr);
} sBGR;
typedef sBGR *pBGR;


//��������� ���������� ���������� ������������ ��������
struct LastAct
{
	LastAct();
	int num_nod; //����� �����
	int type;
	bool isAdd;
	int ind;
	DWORD dw_time;//����� ���������� �������
	HWND hwnd;//�������� ������, ������� �������� ��������
	UINT un;
	CString comment;
};

struct sChild;

//���-��, ������. ��������� �������� ����	
struct sMain
{
	CString csWinCapt;//�������� ��������� �������� ����
	CString csClaName;//�������� ��� ������ �������� ����
	HWND hwnd;//����� ������������� ����
	byte bHowCha;//����� ��� �������� ��������� ��. ����, ���� ��� �� �������
	//1 - ������� ���������
	//0 - ����� �������� ������
	//2 - ����� �������� � ������ � �����
	//3 - ������ ����� ������ ����� ���� ���������
	//4 - �������������� - �� ������� ���������� ����� ��������
	
	//����� �� ������ ������� ���� �� ���������
	bool bSearExe;
	//	bool bWaitClo;
};

//���������, ������. ��������� ��������� ����
struct sChild
{
	CString csWinCapt;//�������� ��������� ��������� ����
	CString csClaName;//��� ������ ��������� ����
	UINT in1;//������������� ��������� ����
	HWND hwnd;//����� ��������� ����
	CString ierarh;//�������� �������� ��������� ����
	BOOL bEnable;//��������: "��������" �� ���� �������� ���� ��� ������� �� ���
	byte bHowCha;//����� ��� �������� ��������� ���. ����, ���� ��� �� �������
	int id;
	LONG exSty;
	LONG Styl;
};

struct SizeWin
{
	int Main_l;
	int Main_t;
	int Main_r;
	int Main_b;
	int Chil_l;
	int Chil_t;
	int Chil_r;
	int Chil_b;
};

struct forKeyAndMouse
{
	CString sKeys;	//������� ���������� ������ - ��� ����������� ��������
	CUIntArray keys;  //(wparam) ����� ������� ���� ������: �����, ������ ��� ��� ��������� - ����� �������
	CUIntArray updown;//������� ��� ������� (curAct->message)
	CUIntArray dTime; //��������� ������� ����� ������� � ��������� ��������� ���������
	BOOL QueueWait; //���� �� ������ ��������, �� ��� �� ����������� �� ������ 
	void  operator = (forKeyAndMouse &key);
};

//��������� ���������, � ������� ������������ ��������� ������� �������
struct forMousePress
{
	CStringArray xx;  
	CStringArray yy;
	CDWordArray lpars; // LPARAM ������� - �� ���� � ������� �� ������������, �������� ���������� �������
	void  operator = (forMousePress &key);
};

//��������� ���������, � ������� ������������ ��������� ��������� �������
struct forKeyPress
{
	CDWordArray lpars;//���� LPARAM �������
	CUIntArray KeyLang;
	void  operator = (forKeyPress &key);
};
//���������, ���������� ��������� ����������� ����
struct Wind
{
	byte IndAct;//�������������� ���� ����������� ���������
	int iWaitCol;//����� �������� ����, ����� ����� ����� ������ ������ ��� �������
	bool RazrFocus;
	//bool paint;//����� �� ���������� ����
	sChild Chi;
	sMain Mai;
	CString Name_exe;//��� ������������ ���������
	CString Name_pict;//�������� ��������� ����
//	bool Slice;//������ ������� ���� �� ����� ���������
	SizeWin saWindows;//������� � ���������� �������� ������ ���� ������. � ��. ����
};

//��������� ���������, � ������� ������������ ������ ����� ��������
struct sSmartControl_tmp
{
	CStringArray OBJs;//�������������� ��
	CUIntArray siApps;//��� �������� � ������������
	CStringArray saApps;//����� ���������� ���������
	CStringArray saParComLine;//����� ���������� ���������
	CStringArray saPixContr;//����� bmp ����� �������� � ��
	CStringArray saPlayAip;//����� ������ �������������� ��� ���������� ��������
	//����������� ���������������� � saPixContr ����� "****"
	//��������������� ��� ��������
	CString ProvPlayAip;//����� aip �������������� � ������ ������� ������
	int time_search;//������� ������� ������ ����
	CUIntArray clickx, clicky;//���������� ����� ������������ ������ 
	CUIntArray Rx, Ry;//��������� ���������� ��� ������ �� ��������� ��������
	//�������� ����
	CUIntArray typeSear, xl, xr, yt, yb;//������� ������ + ��� ���������� �� �����
	CUIntArray typeClick;//��� ������� ������
	//����� ��������������� ��� ������ �������� � ������ ����������
	CUIntArray nodPicRpl;
	//����� ��������������� ��� ����. �������� 
	//� ������ ������������ �� ����� ��������
	//int nodRplNF;
	int razrPlay; //��� �������������� ��� ������� ������
	// 93 - "���������� � ������������� ..."
	// 94 - "����������"
	//193 - "GOTO ..."
	bool hideSM;//�������� �� ���� me 
	int randVetv;//��������� ����� �������������� �����������
	int otk_s;
	//	bool bStrFix;
	//	CString StrBuf;
	//	bool bFufInFile;
	//	CString StrInFile;
	//	bool bFufFromFile;
	//	CString StrFromFile;
	CStringArray saVarsOpers;//����� �������� � ���������� ���������
	CString ifElse;//���� �������
	void  operator = (const sSmartControl_tmp  &sc);
	sSmartControl_tmp();
};

struct OptRec
{
	int iModeProc;//��� ������� �� �����������
	int ColProh;
	int SetFocusApp;
	int ScreenSh;
	int pause_act;
};

struct SendStruct
{
	//	virtual ~SendStruct();
	//��������� ��������
	__int64 baTypeAct; //��� ��������
	//	char csMainWindowCapt[1024];//�������� ��������� �������� ����
	//	char csMainWindowClass[512];//�������� ��� ������ �������� ����
	//	char csChildWindowCapt[1024];//�������� ��������� ��������� ����
	//	char csChildClassName[512];//��� ������ ��������� ����
	__int64 in1;//������������� ��������� ����
	__int64 HChil;//����� ��������� ����
	__int64 HMain;//����� ������������� ����
	__int64 message;//������ ��� ������ ������� (��� ���������)
	__int64 wpar;//��� ������� ������� (WPARAM)
	__int64 lpar;//LPARAM �������
	__int64 mesx;//���������� ���������
	__int64 mesy;//���������� ���������
	BOOL bEnable;//��������: "��������" �� ���� �������� ���� ��� ������� �� ���
	bool Slice;//������ ������� ���� �� ����� ���������
	__int64 iWaitCol;//����� ��������
	//	char ierarh[256];
	//DWORD SendOrNot;
	__int64 dw_time;
	bool ShiftDown;
	bool AltDown;
	bool CtrlDown;
	__int64 paint;//����� �� ���������� ����
	__int64 KeyLang;//��������� �����
};

typedef	LRESULT (__stdcall *SetHookFromDll)(bool , HINSTANCE, int, HWND);
typedef	LRESULT (__stdcall *MyFreeLib)(HINSTANCE);

struct Act
{
	Act(const Act& ac);
	Act(){};
//	bool  operator == (SendStruct  *ac);
	UINT UN;//���������� ����� ��� ��������
	void  operator = (Act &ac);
	void  operator = (LastAct &ac);
//	bool  Wpar( Act &ac);
	//��������� ��������
	int num_nod; //����� �����
	byte baTypeAct; //��� ��������
	//1 - ����� ������
	//2 - ���������� ���������� (�� ������������)
	//3 - ������������ ��������
	//4 - ����������� �����
	//6 - ����� ��������� ����, ����������� �������������� ����� ���� � �����
	//7 - ����
	//8 - ����� ������� ����
	//9 - �������� ���������������
	//10 - ������ ����������
	//11 - ���������� ����������
	//12 - ������ � �����������
	//13 - ������ � ������������ � �����������
	//14 - ����� ��
	//15 - ���� IFelse
//	int mesx;//���������� ���������
//	int mesy;//���������� ���������
	Wind W;
	forKeyAndMouse MK;
	forKeyPress KEY; //��������� ��������
	forMousePress MOUS; //��������� ��������
	CStringArray COMS;
	CString comment;
};

template<class TYPE, class ARG_TYPE>
class CMyArray : public CArray< Act, Act >
{
public:
	CArray <Act, Act>& operator = (CArray <Act, Act>&);
};

typedef  CMyArray  < Act, Act > Acti;

template<class TYPE, class ARG_TYPE>
class CMyArrayB : public CArray< BOOL, int >
{
public:
	CArray < BOOL, int >& operator = (CArray < BOOL, int >&);
};

//������ ��������� ���� ��� �� �������������� ����� ������������
struct WINPLA
{
	WINDOWPLACEMENT Pla;
	HWND hwnd;
	bool hide; //���� ���������������� ����� SW_HIDE
};

typedef  CArray  < WINPLA, int > WinPla;
typedef  CArray  < BOOL, int > bArray;
typedef  CMyArrayB  < bool, int > booArray;
typedef  CArray  < CStringArray, CStringArray > s2Array;

struct struPlaList
{
	bool begin;//�������� �� ������������ ���������
	bool endStep;//����������� �� ������������ ����
	int iCurPlay;//����� ������� ������� ��� �������������
	CString name_pla;
	//CStringArray sPlaList;
	CUIntArray plaed; //����� ��� ���������
//	bool random;
	void strucpy(const struPlaList& pl2);
};

struct Que
{
	int counQue;//������� ��������� ��������� ��� �������
	bool needRepe;//��������� ������ ��������
	int lastAct;//��� ����������� �������� ��������
	int IndInLastKey;
	bool waitAct;//������� ��� �� ������� ��������
	int SCTypeClick;
	int lastReceiAct; //��������� ������������ ��������
	UINT SendTime;
	void strucpy(const Que& qu2);
	void Reset();
};

struct sInnerRec{//��� ������ � ������� �������
	bool Start;
	int begin;
	int end;
};

// ��� ������ OCR 
struct StructOCR{
	int TypeSrc; // ��� ������ ���� ��������� 1 - �����, 2 - ����
	// ���� TypeScr ����� 1 �� ����� ���������� ������
	int sr_x1; 
	int sr_y1; // ���������� �������� ������ ���� 
	int sr_x2;
	int sr_y2; // ���������� ������� ������� ����
	CString sFileImage; // ��� �����, � ������� ����������� �������� ������ ��� ���� �� ���������� �����
	CString sHttpUrl; // ����� � �������� ��������� ��������
	BOOL Wait_Text; // C ��������� ������ ��� ���
	CString sSearch_Text; // ����� ����� ���� (���� Wait_Text = TRUE)
	CString sCaptLogPass; // ����� � ������ � ������ sWayRecog = 2
	int langOcr; // ���� ������������
	int typeRecog; // ������ ������������� (Way recognition) 1 - MODI, 2 - CaptchaBot
	CString sSuccessResult; // ����� ��������� ������ ������� � ������ ��������� �������������
	CString sNsuccessResult; // ����� ��������� ������ ������� � ������ ��������� �������������
	BOOL filled;
	UINT SearchTime;
	StructOCR();
};
