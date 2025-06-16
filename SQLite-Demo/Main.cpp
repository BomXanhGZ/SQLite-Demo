
#include "SQLiteManager.h"
#include <iostream>


void ShowInstruct()
{
	std::cout << std::endl << "<=================================>" << std::endl;
	std::cout << "Enter Key 0 to exit! " << std::endl;
	std::cout << "Enter Key 1 to Open Db File! " << std::endl;   //demoFile.db
	std::cout << "Enter Key 2 to show Infor File" << std::endl;
	std::cout << "Enter Key 3 to Query" << std::endl;
	std::cout << "Enter Key 4 to Show Data In Table" << std::endl;
}

int main()
{

	int event = 1;
	bool is_quit = false;

	//SQLite Manager and File
	SQLiteManager* p_SqlMr = new SQLiteManager;

	//main_loop
	while (!is_quit)
	{
		ShowInstruct();
		std::cout << "Enter Your choie => ";
		std::cin >> event;

		switch (event)
		{
			case 0:
				is_quit = true;
				break;
			
			case 1:
				p_SqlMr->OpenDbFile();
				break;

			case 2:
				p_SqlMr->ShowInfoFile();
				break;

			case 3:
				p_SqlMr->QueryData();
				break;

			case 4:
				p_SqlMr->ShowDataInTable();
				break;

			default:
				std::cout << "============================ the selection is invalid, plese choie again!";
				break;
		}
	}

	return 0;
}