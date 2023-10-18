#include "pch.h"
#define DBCONNECTASDFASDF123123
#include "DBConnect.h"

DBConnect* DBConnect::dbc = NULL;

DBConnect::DBConnect(LPCTSTR opendb)
{
	db.OpenEx(opendb);
}

DBConnect* DBConnect::GetInstance(LPCTSTR opendb)
{
	if (dbc == NULL)
	{
		dbc = new DBConnect(opendb);
	}
	return dbc;
}

void DBConnect::ExecuteQuery(LPCTSTR query)
{
	db.ExecuteSQL(query);
}

CRecordset* DBConnect::Select()
{
	CRecordset* rs = new CRecordset(&db);
	return rs;
}

void DBConnect::Close()
{
	db.Close();
}