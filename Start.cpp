#include "UI.h"
#include "DogService.h"
#include "DogRepository.h"
#include "DogFileRepository.h"
#include <crtdbg.h>
#include "Tests.h"
#include "FileAdoptionList.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include <iostream>
#include "GUI.h"
#include "TestGui.h"

int main(int argc, char* argv[])
{
	{
		Tests::testAll();
	}

	{
		try {
			QApplication a(argc, argv);
			FileAdoptionList* adoption_list{};
			FileRepository fileRepo{ "Dogs.txt" };
			Repository& repository{ fileRepo };
			Service service = Service(repository, adoption_list, DogValidator());
			//UI ui(service);
			//ui.startUI();
			GUI gui{service};
			gui.show();
			//TestGui gui{ service };
			//gui.show();
			return a.exec();
		}
		catch (FileException ex)
		{
			std::cout << ex.what();
		}
	}
	
	_CrtDumpMemoryLeaks();
}