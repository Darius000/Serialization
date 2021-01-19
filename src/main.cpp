#pragma once
#include <iostream>
//#include <Reflection/ClassProperty.h>
//#include <Serialization/Serilializer.h>
//#include <Window/BaseWindow.h>
//#include <Reflection/Text.h>
#include <WaveParser/WaveParser.h>

//#ifndef UNICODE
//#define UNICODE
//#endif


//#include <Serilializer.h>

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
//{
//	MainWindow win("Create a Simple Window", 1080, 720);
//	MainWindow win2("Second Window", 800, 600);
//
//	if (!win.Create(L"Create a Simple Window", WS_OVERLAPPEDWINDOW))
//	{
//		return 0;
//	}
//
//	if (!win2.Create(L"Second Window", WS_OVERLAPPEDWINDOW))
//	{
//		return 0;
//	}
//
//	win.Show();
//	win2.Show();
//	win.SetActive();
//
//	Serialization::Serilializer::Load();
//
//	MSG msg = {};
//	while (GetMessage(&msg, nullptr, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	Serialization::Serilializer::Save();
//
//	return 0;
//}

int main()
{
	/*Text text;
	text.line = "Sentence";
	text.age = 300;
	text.height = 54;
	text.GetClass().GetProperty<int>("age") = 30;
	text.GetClass().GetProperty<std::string>("line") = "Micheal";
	text.GetClass().GetProperty<float>("height") = 94.0f;
	
	for (auto prop : text.GetClass().GetProperties())
	{
		std::cout << "name: " << prop.first <<  " value: ";
		prop.second->PrintValue();
	}*/

	WaveFile test1("C:\\Users\\Darius Bigbee\\Desktop\\test1.wav");
	WaveFile DoorOpenWave("C:\\Users\\Darius Bigbee\\Desktop\\SW_Door_Open.wav");

	//WaveFile* waveptr = new WaveFile("C:\\Users\\Darius Bigbee\\Desktop\\554406__kongehund__metal-bucket-water.wav");

	test1.PrintInfo();
	DoorOpenWave.PrintInfo();
	//waveptr->PrintInfo();
	DoorOpenWave.Play();
	test1.Play();


	//delete waveptr;

	std::cin.get();
	return 0 ;
}

