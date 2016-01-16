//ConnWorkMySql.h ���� ���������

#include "afxwin.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
//#include "mySqlConn/mysql_driver.h"
//#include "mySqlConn/mysql_connection.h"
#include "mysql.h"

#pragma once

#pragma comment (lib, "libmysql.lib")
//#pragma comment (lib, "mysqlcppconn.lib")
//#pragma comment (lib, "mysqlcppconn-static.lib")

#define MYSQLE_INITIALIZATION_ERROR 0x001
#define MYSQLE_CONNECT_ERROR 0x002
#define MYSQLE_SQL_ERROR 0x003
#define MYSQLE_UNKNOWN_ERROR 0x004

// ��������� ������
class ConnWorkMySqlError
{
	public:
		ConnWorkMySqlError(DWORD code);
		// �������� ��� ������
		DWORD GetErrorCode();
		// �������� ����� ������
		std::string GetErrorTrace();
	private:
		DWORD ErrorCode;
		// ����� ������
		std::string ErrorTrace;
};

struct mysql_row{
	// ����� �����
	int fields;
	// ����� ��������
	int cols;
	//���������� ��������
	struct _row{
		//������ � ������
		std::string _data;
		// ������ ������
	    int lendth;
	} *row;
	// �������������� row data � ����� ���
	int asInt(int index)
	{
		//return atoi(*row[index]._data);
	}
};

class ConnWorkMySql
{
public:
	//����������� - ���������� � ��������
	#pragma warning( disable : 4290 )
	ConnWorkMySql(const std::string &host, const std::string &user, 
		          const std::string &password) throw (ConnWorkMySqlError);
	//����������� ���������� � �������� � ������� ����
	ConnWorkMySql(const std::string &host, const std::string &user, 
				  const std::string &password, const std::string &dbname, int port) throw (ConnWorkMySqlError);
	~ConnWorkMySql(void);
	//���������� ��������� ������
	std::string get_last_sql()
	{
		return this->last_sql;
	}
	//������ �� ������
	int query(std::string _sql);
	// �������� ������ �� �������
	mysql_row * fetch(int query_result) throw (ConnWorkMySqlError);
	// ������ ������
	static void free_rows(mysql_row * rows);
private:
	MYSQL mysql;
	std::string last_sql;
	std::string escape(const std::string &statement);
};

