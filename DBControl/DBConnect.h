#pragma once
#include <afxdb.h>

#ifdef DBCONNECTASDFASDF123123
#define DLL_CLASS __declspec(dllexport)
#else
#define DLL_CLASS __declspec(dllimport)
#endif

class DLL_CLASS DBConnect
{
private:
	static DBConnect* dbc;
	CDatabase db;
private:
	DBConnect(LPCTSTR opendb);
public:
	static DBConnect* GetInstance(LPCTSTR opendb);
public:
	void ExecuteQuery(LPCTSTR query);
	void Close();
public:
	CRecordset* Select();
};

