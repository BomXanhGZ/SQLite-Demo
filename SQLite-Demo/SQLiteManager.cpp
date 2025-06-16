
#include "SQLiteManager.h"


SQLiteManager::SQLiteManager()
{
	db_ = nullptr;
	fileName_ = "";
	is_connected_ = false;
}

SQLiteManager::~SQLiteManager()
{
	FreeSQLite();
}

int SQLiteManager::OpenDbFile(/*std::string fileName*/)
{
	std::cout << "Enter Your File Name:" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, fileName_);

	int success = SQLITE_OK;
	is_connected_ = true;

	if ( !std::filesystem::exists(fileName_) )
	{
		std::cout << "file is not exists, do you want creat new file?" << std::endl;
		std::cout << "enter 1 chose yes !" << std::endl;
		std::cout << "enter 2 chose no !" << std::endl;

		int chose;
		std::cin >> chose;
		switch ( chose)
		{
			case 1: 
				std::cout << "creat new file ! -> ";
				break;

			case 2: return -1;
			default: return -1;
		}
	}

	success = sqlite3_open(fileName_.c_str(), &db_);
	if (success != SQLITE_OK)
	{
		std::cerr << "error at open dbFile" << sqlite3_errmsg(db_) << std::endl;
		return success;
	}

	std::cout << "opening dbFile was successful!" << std::endl;

	return success;
}

int SQLiteManager::QueryData(/*std::string sqlStr, int CallBack(void* csData, int argc, char** argv, char** columnName)*/)
{
	if (!is_connected_)
	{
		std::cout << std::endl << "========>> not connected to any file <<==========" << std::endl;
		return -1;
	}

	std::cout << "Enter Your Query Command =>";
	std::string sqlStr;
	std::cin.ignore();
	std::getline(std::cin, sqlStr);

	int success = SQLITE_OK;
	char* errMsg = nullptr;

	success = sqlite3_exec(db_, sqlStr.c_str(), nullptr, nullptr, &errMsg);
	if (success != SQLITE_OK)
	{
		std::cerr << "error query data, info: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return success;
	}

	std::cout << "the query was executed !" << std::endl;

	return success;
}

void SQLiteManager::FreeSQLite()
{
	if (db_)
	{
		sqlite3_close(db_);
		db_ = nullptr;
	}
}

void SQLiteManager::ShowInfoFile()
{
	if (!is_connected_)
	{
		std::cout << std::endl << "========>> not connected to any file <<==========" << std::endl;
		return;
	} 

	std::cout << std::endl << std::endl << std::endl;
	std::cout << "File Name Is: " << fileName_ << std::endl;
	std::cout << "is_connected: " << is_connected_ << std::endl;
	std::cout << "----------------------" << std::endl;

	int success = SQLITE_OK;
	std::string sqlStr = "SELECT name FROM sqlite_master WHERE type='table';";
	char* errMsg = nullptr;
	
	success = sqlite3_exec(db_, sqlStr.c_str(),
		[](void* ref_this_, int argc, char** argv, char** colName) -> int
	{
			auto* ref_mgr = static_cast<SQLiteManager*>(ref_this_);
			for (int i = 0; i < argc; i++)
			{
				std::string tbname = (argv[i] ? argv[i] : "NULL");
				std::cout << "===============>> Table " << colName[i] << ": " << tbname << " <<=============== " << std::endl;
				char* errMsg2 = nullptr;

				std::string sql = "PRAGMA table_info(" + tbname + ")";
				int success2 = SQLITE_OK;
				success2 = sqlite3_exec(ref_mgr->GetDb(), sql.c_str(), CallBackShowInfo, nullptr, &errMsg2);
				if (errMsg2) { sqlite3_free(errMsg2); errMsg2 = nullptr; }
				return success2;
			}
	}, this, &errMsg);
	if (success)
	{
		std::cerr << "Error show data in file, info: " << errMsg << std::endl;
		if (errMsg) { sqlite3_free(errMsg); errMsg = nullptr; }
	}
	//PRAGMA table_info(table_name);
}

void SQLiteManager::ShowDataInTable()
{
	if (!is_connected_)
	{
		std::cout << std::endl << "========>> not connected to any file <<==========" << std::endl;
		return;
	}

	std::cout << "Enter Table Name:" << std::endl;
	std::string tbName;
	std::cin.ignore();
	std::getline(std::cin, tbName);
	std::string sql = "SELECT * FROM " + tbName;
	char* errMsg = nullptr;

	sqlite3_exec(db_, sql.c_str(), &SQLiteManager::CallBackShowInfo, nullptr, &errMsg);

}

int SQLiteManager::CallBackShowInfo(void* csData, int argc, char** argv, char** columnName)
{
	for (int i = 0; i < argc; i++)
	{
		std::cout << columnName[i] << " : " << (argv[i] != nullptr ? argv[i] : "NULL") << std::endl;
	}
	std::cout << "-------------------------------" << std::endl;

	return 0;
}
