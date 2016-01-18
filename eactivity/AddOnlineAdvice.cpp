// AddOnlineAdvice.cpp : implementation file
//

#include "stdafx.h"
#include "eactivity.h"
#include "AddOnlineAdvice.h"

// CAddOnlineAdvice dialog

IMPLEMENT_DYNAMIC(CAddOnlineAdvice, CDialog)

CAddOnlineAdvice::CAddOnlineAdvice(CWnd* pParent /*=NULL*/)
	: CDialog(CAddOnlineAdvice::IDD, pParent)
{

}

CAddOnlineAdvice::~CAddOnlineAdvice()
{
}

void CAddOnlineAdvice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_nickname);
	DDX_Control(pDX, IDC_EDIT5, edit_advice);
	DDX_Control(pDX, IDC_EDIT2, edit_left_symbols);
	DDX_Control(pDX, IDC_EDIT3, edit_author);
}


BEGIN_MESSAGE_MAP(CAddOnlineAdvice, CDialog)
	ON_BN_CLICKED(IDOK, &CAddOnlineAdvice::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddOnlineAdvice::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT5, &CAddOnlineAdvice::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT3, &CAddOnlineAdvice::OnEnChangeEdit3)
END_MESSAGE_MAP()

//------------------------------------------------------------------------
// Converts the given SID to a string format.
// Uses ConvertSidToStringSid Win32 API function.
// Uses AtlThrow to signal error conditions.
//------------------------------------------------------------------------
#include <Sddl.h>       // ConvertSidToStringSid
#include <vector>       // STL vector container
CString ConvertSidToString(PSID pSID)
{
	// Check input pointer
	ATLASSERT( pSID != NULL );
	if ( pSID == NULL )
	{
		AtlThrow( E_POINTER );
	}

	// Get string corresponding to SID
	LPTSTR pszSID = NULL;
	if ( ! ConvertSidToStringSid( pSID, &pszSID ) )
	{
		AtlThrowLastWin32();
	}

	// Deep copy result in a CString instance
	CString strSID( pszSID );

	// Release buffer allocated by ConvertSidToStringSid API
	LocalFree( pszSID );
	pszSID = NULL;

	// Return string representation of the SID
	return strSID;
}

string CAddOnlineAdvice::getUserSID() 
{
	HANDLE hToken = NULL;
	if ( ! OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken ) ) 
	{
		_tprintf( _T("OpenProcessToken failed. GetLastError returned: %d\n"),
			GetLastError());
		return "";
	}

	//
	// Get the size of the memory buffer needed for the SID
	//
	DWORD dwBufferSize = 0;
	if ( ! GetTokenInformation( hToken, TokenUser, NULL, 0, &dwBufferSize ) &&
		( GetLastError() != ERROR_INSUFFICIENT_BUFFER ) )
	{
		_tprintf( _T("GetTokenInformation failed. GetLastError returned: %d\n"),
			GetLastError());

		// Cleanup
		CloseHandle( hToken );
		hToken = NULL;

		return "";
	}


	//
	// Allocate buffer for user token data
	//
	std::vector<BYTE> buffer;
	buffer.resize( dwBufferSize );
	PTOKEN_USER pTokenUser = reinterpret_cast<PTOKEN_USER>( &buffer[0] );


	//
	// Retrieve the token information in a TOKEN_USER structure
	//
	if ( ! GetTokenInformation( 
		hToken, 
		TokenUser, 
		pTokenUser, 
		dwBufferSize,
		&dwBufferSize)) 
	{
		_tprintf( _T("2 GetTokenInformation failed. GetLastError returned: %d\n"),
			GetLastError());

		// Cleanup
		CloseHandle( hToken );
		hToken = NULL;

		return "";
	}


	//
	// Check if SID is valid
	//
	if ( ! IsValidSid( pTokenUser->User.Sid ) ) 
	{
		_tprintf( _T("The owner SID is invalid.\n") );

		// Cleanup
		CloseHandle(hToken);
		hToken = NULL;

		return "";
	}
	string res = ConvertSidToString( pTokenUser->User.Sid ).GetString();

	// Cleanup
	CloseHandle(hToken);
	hToken = NULL;
	return res;
}

BOOL CAddOnlineAdvice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	userSID = getUserSID();
	edit_left_symbols.SetWindowText("2000");
	CString str = AfxGetApp()->GetProfileString("App", "UserName", "Anonymous");
	edit_nickname.SetWindowText(str);
	isEnableSend();
	return TRUE;
}
void CAddOnlineAdvice::OnBnClickedOk()
{
	if (GetDlgItem(IDC_BUTTON1)->IsWindowEnabled())
	{
		if (AfxMessageBox(trif.GetIds(IDS_STRING1847), MB_YESNO)==IDNO)
			return;
	}
	CString str;
	edit_nickname.GetWindowText(str);
	AfxGetApp()->WriteProfileString("App", "UserName", str);
	OnOK();
}

void CAddOnlineAdvice::OnBnClickedButton1()
{
	CString sAdvice;
	edit_advice.GetWindowText(sAdvice);
	if (sAdvice.GetLength() < 6)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1811));
		return;
	}
	if (sAdvice.GetLength()>2000)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1801));
		return;
	}

	CString sNickName;
	edit_nickname.GetWindowText(sNickName);
	if (!sNickName.GetLength())
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1803));
		return;
	}
	if (sNickName.GetLength()>20)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1805));
		return;
	}

	CString sAuthor;
	edit_author.GetWindowText(sAuthor);
	if (!sAuthor.GetLength())
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1809));
		return;
	}
	if (sAuthor.GetLength()>20)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1807));
		return;
	}
	string ip = trif.getSqlIp(path_actuser.c_str());
	if (ip == "")
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1855));
		return;
	}
	mySql = new ConnWorkMySql(ip, "eactivity_user", "djgvyetgjdbu", 
		"eactivity_text_messages", 3306);
	if (mySql->connectError)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1855));
		return;
	}

	//предмодерация сообщений других пользователей
	mysql_row *myRows;
	char ch[4096];
	mySql->query("SET NAMES \'cp1251\'");
	sprintf_s(ch, 
		"SELECT * FROM text_mes_for_moderate WHERE moderate_type = 10 AND user_sid != '%s' AND id not in ( SELECT id FROM rates_premoderate WHERE text_mes_for_moderate.id = rates_premoderate.id AND rates_premoderate.user_sid = '%s') ORDER BY RAND( ) LIMIT 3;", 
		userSID.c_str(), userSID.c_str());
	myRows = mySql->fetch(mySql->query(ch));
	if (myRows && myRows->fields > 0)
	{
		CString str;
		str.LoadString(trif.GetIds(IDS_STRING1817));
		sprintf_s(ch, str, myRows->fields);
		if (AfxMessageBox(ch, MB_YESNO) != IDYES)
			return;
		COnlineAdviceModerate dialModerate;
		dialModerate.myRows = myRows;
		if (dialModerate.DoModal()!=IDOK)
			return;
		//отправка модераторских голосов
		for (int ii=0; ii < myRows->fields; ii++)
		{
			char ch[4096];
			sprintf_s(ch, 
				"insert into rates_premoderate (id, rate, rate1, rate2, rate3, rate4, user_sid) values (%d,'%d','%d','%d','%d','%d','%s');",
				atoi(myRows[ii].row[0]._data.c_str()), 0, dialModerate.rate1[ii], 
				dialModerate.rate2[ii], dialModerate.rate3[ii], 0, userSID.c_str());
			CString strReq = ch;
			strReq.Replace("'6'", "NULL"); //6-ка - это отсуствие голоса и для более 
			//точного вычисления среднего ставим оценку NULL
			string sReq = strReq;
			mySql->query(sReq);
		}
	}

	mySql->query("SET NAMES \'cp1251\'");
	sprintf_s(ch, 
		"insert into text_mes_for_moderate (message, owner_mes, user, moderate_type, user_sid) values ('%s','%s','%s','%d','%s');",
		sAdvice, sAuthor, sNickName, 10, userSID.c_str());
	int res_query = mySql->query(ch);
	if (!res_query)
	{
		AfxMessageBox(trif.GetIds(IDS_STRING1813));
		edit_advice.SetWindowText("");
	} else {
		AfxMessageBox(trif.GetIds(IDS_STRING1815));
	}
	delete myRows;
}

void CAddOnlineAdvice::isEnableSend()
{
	CString str;
	edit_advice.GetWindowText(str);
	CString sAuthor;
	edit_author.GetWindowText(sAuthor);
	if (sAuthor.GetLength() && str.GetLength()>=10)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	} else {
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
}
void CAddOnlineAdvice::OnEnChangeEdit5()
{
	CString str;
	edit_advice.GetWindowText(str);
	char ch[100];
	sprintf_s(ch, "%d", 2000 - str.GetLength());
	edit_left_symbols.SetWindowText(ch);
	isEnableSend();
}

void CAddOnlineAdvice::OnEnChangeEdit3()
{
	isEnableSend();
}
