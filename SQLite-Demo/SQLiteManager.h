#ifndef SQLITE_MANAGER_H_
#define SQLITE_MANAGER_H_


#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include "sqlite3.h"


class SQLiteManager
{
public:

	SQLiteManager();
	~SQLiteManager();

	int OpenDbFile(/*std::string fileName*/);
	int QueryData(/*std::string sqlStr, int CallBack(void* csData, int argc, char** argv, char** columnName)*/);
	void FreeSQLite();
	void ShowInfoFile();
	void ShowDataInTable();
	static int CallBackShowInfo(void* csData, int argc, char** argv, char** columnName);

	//Get_Function
	sqlite3* GetDb() { return db_; }

private:
	
	sqlite3* db_;
	std::string fileName_;
	bool is_connected_;

};


#endif // !SQLITE_MANAGER_H_
