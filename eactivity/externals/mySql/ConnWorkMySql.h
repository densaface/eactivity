//ConnWorkMySql.h файл заголовка

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

// Обработка ошибок
class ConnWorkMySqlError
{
	public:
		ConnWorkMySqlError(DWORD code);
		// Получаем код ошибок
		DWORD GetErrorCode();
		// Получаем текст ошибки
		std::string GetErrorTrace();
	private:
		DWORD ErrorCode;
		// Текст ошибки
		std::string ErrorTrace;
};

struct mysql_row{
	// Число строк
	int fields;
	// Число столбцов
	int cols;
	//Содержание столбцов
	struct _row{
		//Данные в строке
		std::string _data;
		// Размер данных
	    int lendth;
	} *row;
	// Преобразование row data в целый тип
	int asInt(int index)
	{
		//return atoi(*row[index]._data);
	}
};

class ConnWorkMySql
{
public:
	//Конструктор - соединение с сервером
	#pragma warning( disable : 4290 )
	ConnWorkMySql(const std::string &host, const std::string &user, 
		          const std::string &password) throw (ConnWorkMySqlError);
	//Конструктор соединение с сервером с выбором базы
	ConnWorkMySql(const std::string &host, const std::string &user, 
				  const std::string &password, const std::string &dbname, int port) throw (ConnWorkMySqlError);
	~ConnWorkMySql(void);
	//Возвращает последний запрос
	std::string get_last_sql()
	{
		return this->last_sql;
	}
	//Запрос на сервер
	int query(std::string _sql);
	// Получаем записи из запроса
	mysql_row * fetch(int query_result) throw (ConnWorkMySqlError);
	// Чистим записи
	static void free_rows(mysql_row * rows);
private:
	MYSQL mysql;
	std::string last_sql;
	std::string escape(const std::string &statement);
};

