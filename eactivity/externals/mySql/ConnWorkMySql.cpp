#include "../../StdAfx.h"
#include <stdio.h>
#include "ConnWorkMySql.h"


/*Класс обработки ошибок*/
ConnWorkMySqlError::ConnWorkMySqlError(DWORD code)
{
	this->ErrorCode = code;
	char ch[2048];
	sprintf_s(ch, "Ошибка работы с сервером (0x%X)", code);
	this->ErrorTrace = ch;
}

DWORD ConnWorkMySqlError::GetErrorCode()
{
	return this->ErrorCode;
}

std::string ConnWorkMySqlError::GetErrorTrace()
{
	return this->ErrorTrace;
}

/*Класс работы с SQl*/
ConnWorkMySql::ConnWorkMySql(const std::string &host, const std::string &user, 
	                         const std::string &password) throw (ConnWorkMySqlError)
{
	if (!mysql_init(&this->mysql))
	{
		connectError = true;
		return;
		//throw ConnWorkMySqlError(MYSQLE_INITIALIZATION_ERROR);
	}
	
	if (!mysql_real_connect(&this->mysql, host.c_str(), user.c_str(), password.c_str(), NULL, 0, NULL, 0)) 
	{
		connectError = true;
		return;
		//throw ConnWorkMySqlError(MYSQLE_CONNECT_ERROR);
	}
	connectError = false;
}

ConnWorkMySql::ConnWorkMySql(const std::string &host, const std::string &user, 
	                         const std::string &password, const std::string &dbname, int port) throw (ConnWorkMySqlError)
{
	if (!mysql_init(&this->mysql)) 
	{
		//throw ConnWorkMySqlError(MYSQLE_INITIALIZATION_ERROR);
		connectError = true;
		return;
	}
	if (!mysql_real_connect(&this->mysql, host.c_str(), user.c_str(), password.c_str(), dbname.c_str(), port, NULL, 0))
	{
		connectError = true;
		return;
	}
	connectError = false;
}

ConnWorkMySql::~ConnWorkMySql(void)
{
	mysql_close(&this->mysql);
}

int ConnWorkMySql::query(std::string _sql)
{
	int result = mysql_real_query(&this->mysql, _sql.c_str(), strlen(_sql.c_str()));
	this->last_sql = _sql;
	return result;
}

mysql_row * ConnWorkMySql::fetch(int query_result) throw (ConnWorkMySqlError)
{
	if (query_result)
	{
		return NULL;
	}
	MYSQL_RES * res = mysql_store_result(&this->mysql);
	if (res == NULL) 
		throw ConnWorkMySqlError(MYSQLE_SQL_ERROR);
	// Количество строк
	int num_rows = (int)mysql_num_rows(res);
	if (!num_rows)
	{
		mysql_free_result(res);
		return NULL;
	}
	MYSQL_ROW real_row;
	// Количество столбцов
	int num_cols = mysql_num_fields(res);
	// Строки
	int i = 0;
	// Строки из запроса пишем в структуру для их хранения
	mysql_row * rows = new mysql_row[num_rows];
	while (real_row = mysql_fetch_row(res))
	{
		unsigned long * lengths;		
		rows[i].fields = num_rows;
		rows[i].cols = num_cols;
		rows[i].row = new mysql_row::_row[num_cols];
		lengths = mysql_fetch_lengths(res);
		for (int j = 0; j < num_cols; j++)
		{
			rows[i].row[j].lendth = (int)lengths[j];
			if (rows[i].row[j].lendth > 0)
				rows[i].row[j]._data = real_row[j];
		}
		i++;
	}
	mysql_free_result(res);
	return rows;
}

void ConnWorkMySql::free_rows(mysql_row * rows)
{
	if (rows == NULL)
	{
		return;
	}
	for (int i = 0; i < rows->fields; i++ )
	{
		for (int j = 0; j < rows->cols; j++)		
					rows[i].row[i]._data = "";
		delete [] rows[i].row;
	}
	delete [] rows;
}
