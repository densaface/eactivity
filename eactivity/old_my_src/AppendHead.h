#include "trifle1.h"
#include "cpuusage.h"
#include <afxcoll.h>
#include <afxtempl.h>
#include <string>
typedef  CArray  < CBitmap, int > MyBitAr;
typedef  CArray  < CRect, CRect > MyCRectAr;

#define id_hot_klav	1130
typedef  CArray  < HWND, int> hwnd_Array;
//для бального подсчета рейтинга окон
struct sBalReitings
{
	int tt;
	HWND hw;
//	hwnd_Array hws;
	int bals;
	//найден заголовок, хоть немного похожий на записываемый
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
	//numRoad=1     - при множественном выборе сразу попадаем в пиксельный контроль
	//numRoad=2	    - для выбора двойным кликом для GOTO номера действия (в случае нахождения картинки ПК)
	//numRoad=3	    - для выбора двойным кликом для GOTO номера действия (в случае провала ПК)
	//numRoad=21    - для создания альтернативного скриншота из диспетчера задач
	//numRoad=4		- в СмартКонтроле сразу переходим к редактированию ПК
	//numRoad=5		- в СмартКонтроле завели управление буфером обмена или работу с переменными
	//numRoad=6		- в СмартКонтроле завели запуск приложений документов
	//numRoad=15	- в СмартКонтроле завели условный переход
	int par1;
	int par2;
	int par3;
	int par4;
	void  operator = (const greenroad  &gr);
	greenroad();
};
//структура, содержащая настройки записи		m_cMainDirectiv
struct sVariables
{
  CString  name;
  CString	opis;
  int    type_var;
  //0 - int
  //1 - String
  //2 - File
  //текущий результат
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


//структура параметров последнего добавляемого действия
struct LastAct
{
	LastAct();
	int num_nod; //номер ветки
	int type;
	bool isAdd;
	int ind;
	DWORD dw_time;//время последнего нажатия
	HWND hwnd;//домернее окошко, которое посылает действие
	UINT un;
	CString comment;
};

struct sChild;

//стр-ра, содерж. параметры главного окна	
struct sMain
{
	CString csWinCapt;//содержит заголовок главного окна
	CString csClaName;//содержит имя класса главного окна
	HWND hwnd;//хэндл родительского окна
	byte bHowCha;//режим как изменять заголовок гл. окна, если оно не найдено
	//1 - строгий заголовок
	//0 - можно изменять справа
	//2 - можно изменять и справа и слева
	//3 - вообще какой угодно может быть заголовок
	//4 - метастабильный - до первого нахождения после задержки
	
	//можно ли искать главное окно по экзешнику
	bool bSearExe;
	//	bool bWaitClo;
};

//структура, содерж. параметры дочернего окна
struct sChild
{
	CString csWinCapt;//содержит заговолок дочернего окна
	CString csClaName;//имя класса дочернего окна
	UINT in1;//идентификатор дочернего окна
	HWND hwnd;//хэндл дочернего окна
	CString ierarh;//содержит иерархию дочернего окна
	BOOL bEnable;//контроль: "возможно" ли было дочернее окно при нажатии на нем
	byte bHowCha;//режим как изменять заголовок доч. окна, если оно не найдено
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
	CString sKeys;	//символы нажимаемых клавиш - для постоянного хранения
	CUIntArray keys;  //(wparam) какая клавиша мыши нажата: левая, правая или для клавишных - какая клавиша
	CUIntArray updown;//нажатия или отжатия (curAct->message)
	CUIntArray dTime; //интервалы времени между текущим и последним клавишным действием
	BOOL QueueWait; //если не важное действие, то оно не проверяется на отклик 
	void  operator = (forKeyAndMouse &key);
};

//временная структура, в которую записываются параметры МЫШИНЫХ нажатий
struct forMousePress
{
	CStringArray xx;  
	CStringArray yy;
	CDWordArray lpars; // LPARAM нажатия - по сути в мышиных не используется, хранятся отклонения рэндома
	void  operator = (forMousePress &key);
};

//временная структура, в которую записываются параметры КЛАВИШНЫХ нажатий
struct forKeyPress
{
	CDWordArray lpars;//коды LPARAM нажатия
	CUIntArray KeyLang;
	void  operator = (forKeyPress &key);
};
//структура, содержащая параметры записанного окна
struct Wind
{
	byte IndAct;//контролировать окно поступления сообщения
	int iWaitCol;//время ожидания окна, чтобы потом менее строго искать его аналоги
	bool RazrFocus;
	//bool paint;//ждать ли прорисовки окна
	sChild Chi;
	sMain Mai;
	CString Name_exe;//имя запускаемого экзешника
	CString Name_pict;//скриншот дочернего окна
//	bool Slice;//искать главное окно по куску заголовка
	SizeWin saWindows;//размеры и координаты верхнего левого угла дочерн. и гл. окон
};

//временная структура, в которую записываются данные после парсинга
struct sSmartControl_tmp
{
	CStringArray OBJs;//редактирование ПК
	CUIntArray siApps;//тип действия с приложениями
	CStringArray saApps;//какие приложения запускать
	CStringArray saParComLine;//какие приложения запускать
	CStringArray saPixContr;//какие bmp будут искаться в ПК
	CStringArray saPlayAip;//какие Записи Воспроизводить при нахождении картинок
	//сохраняется пристыковыванием к saPixContr через "****"
	//отстыковывается при загрузке
	CString ProvPlayAip;//какой aip Воспроизводить в случае провала поиска
	int time_search;//сколько времени искать окно
	CUIntArray clickx, clicky;//координаты клика относительно левого 
	CUIntArray Rx, Ry;//случайные отклонения при кликах по найденной картинке
	//верхнего угла
	CUIntArray typeSear, xl, xr, yt, yb;//область поиска + тип разрешения на поиск
	CUIntArray typeClick;//тип нажатия мышкой
	//Ветка Воспроизведения для каждой картинки в случае нахождения
	CUIntArray nodPicRpl;
	//Ветка Воспроизведения для Пикс. Контроля 
	//в случае НЕнахождения ни одной картинки
	//int nodRplNF;
	int razrPlay; //Что Воспроизводить при провале поиска
	// 93 - "Остановить и Воспроизвести ..."
	// 94 - "Остановить"
	//193 - "GOTO ..."
	bool hideSM;//скрывать ли стоп me 
	int randVetv;//рэндомный поиск альтернативных изображений
	int otk_s;
	//	bool bStrFix;
	//	CString StrBuf;
	//	bool bFufInFile;
	//	CString StrInFile;
	//	bool bFufFromFile;
	//	CString StrFromFile;
	CStringArray saVarsOpers;//какие действия с переменным совершать
	CString ifElse;//блок условий
	void  operator = (const sSmartControl_tmp  &sc);
	sSmartControl_tmp();
};

struct OptRec
{
	int iModeProc;//как следить за процессором
	int ColProh;
	int SetFocusApp;
	int ScreenSh;
	int pause_act;
};

struct SendStruct
{
	//	virtual ~SendStruct();
	//ПАРАМЕТРЫ ДЕЙСТВИЯ
	__int64 baTypeAct; //тип действия
	//	char csMainWindowCapt[1024];//содержит заголовок главного окна
	//	char csMainWindowClass[512];//содержит имя класса главного окна
	//	char csChildWindowCapt[1024];//содержит заговолок дочернего окна
	//	char csChildClassName[512];//имя класса дочернего окна
	__int64 in1;//идентификатор дочернего окна
	__int64 HChil;//хэндл дочернего окна
	__int64 HMain;//хэндл родительского окна
	__int64 message;//нажата или отжата клавиша (код сообщения)
	__int64 wpar;//код нажатой клавиши (WPARAM)
	__int64 lpar;//LPARAM нажатия
	__int64 mesx;//координата сообщения
	__int64 mesy;//координата сообщения
	BOOL bEnable;//контроль: "возможно" ли было дочернее окно при нажатии на нем
	bool Slice;//искать главное окно по куску заголовка
	__int64 iWaitCol;//время ожидания
	//	char ierarh[256];
	//DWORD SendOrNot;
	__int64 dw_time;
	bool ShiftDown;
	bool AltDown;
	bool CtrlDown;
	__int64 paint;//ждать ли прорисовки окна
	__int64 KeyLang;//раскладка клавы
};

typedef	LRESULT (__stdcall *SetHookFromDll)(bool , HINSTANCE, int, HWND);
typedef	LRESULT (__stdcall *MyFreeLib)(HINSTANCE);

struct Act
{
	Act(const Act& ac);
	Act(){};
//	bool  operator == (SendStruct  *ac);
	UINT UN;//уникальный номер для действия
	void  operator = (Act &ac);
	void  operator = (LastAct &ac);
//	bool  Wpar( Act &ac);
	//ПАРАМЕТРЫ ДЕЙСТВИЯ
	int num_nod; //номер ветки
	byte baTypeAct; //тип действия
	//1 - клики мышкой
	//2 - выключение компьютера (не используется)
	//3 - клавиатурные действия
	//4 - перемещения мышки
	//6 - смена фокусного окна, разрешается принудительный вывод окна в фокус
	//7 - пуст
	//8 - вызов пунктов меню
	//9 - задержка воспроизведения
	//10 - запуск приложения
	//11 - назначение переменных
	//12 - работа с переменными
	//13 - работа с приложениями и документами
	//14 - чисто ПК
	//15 - блок IFelse
//	int mesx;//координата сообщения
//	int mesy;//координата сообщения
	Wind W;
	forKeyAndMouse MK;
	forKeyPress KEY; //клавишное действие
	forMousePress MOUS; //клавишное действие
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

//массив положений окон для их восстановления после проигрывания
struct WINPLA
{
	WINDOWPLACEMENT Pla;
	HWND hwnd;
	bool hide; //окно минимизировалось через SW_HIDE
};

typedef  CArray  < WINPLA, int > WinPla;
typedef  CArray  < BOOL, int > bArray;
typedef  CMyArrayB  < bool, int > booArray;
typedef  CArray  < CStringArray, CStringArray > s2Array;

struct struPlaList
{
	bool begin;//началось ли проигрывание Плейлиста
	bool endStep;//закончилось ли проигрывание шага
	int iCurPlay;//какой посчету текущий аип проигрывается
	CString name_pla;
	//CStringArray sPlaList;
	CUIntArray plaed; //какие уже проиграны
//	bool random;
	void strucpy(const struPlaList& pl2);
};

struct Que
{
	int counQue;//сколько сообщений послалось без очереди
	bool needRepe;//необходим повтор действия
	int lastAct;//для дальнейшего ожидания действия
	int IndInLastKey;
	bool waitAct;//ожидать или не ожидать действие
	int SCTypeClick;
	int lastReceiAct; //последнее отработанное действие
	UINT SendTime;
	void strucpy(const Que& qu2);
	void Reset();
};

struct sInnerRec{//для записи в текущую позицию
	bool Start;
	int begin;
	int end;
};

// Для записи OCR 
struct StructOCR{
	int TypeSrc; // для записи типа источника 1 - экран, 2 - файл
	// если TypeScr равно 1 то пишем координаты экрана
	int sr_x1; 
	int sr_y1; // Координаты верхнего левого угла 
	int sr_x2;
	int sr_y2; // Координаты правого нижнего угла
	CString sFileImage; // Имя файла, в который сохраняется скриншот экрана или путь до выбпанного файла
	CString sHttpUrl; // Адрес с которого загрудена картинка
	BOOL Wait_Text; // C ожиданием текста или нет
	CString sSearch_Text; // Какой текст ищем (если Wait_Text = TRUE)
	CString sCaptLogPass; // Логин и пароль в случае sWayRecog = 2
	int langOcr; // Язык распозавания
	int typeRecog; // Способ распознавания (Way recognition) 1 - MODI, 2 - CaptchaBot
	CString sSuccessResult; // Пишем результат работы диалога в случае успешного распознавания
	CString sNsuccessResult; // Пишем результат работы диалога в случае успешного распознования
	BOOL filled;
	UINT SearchTime;
	StructOCR();
};
