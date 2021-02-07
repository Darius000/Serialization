#pragma once
#include <iostream>
//#include <Reflection/ClassProperty.h>
#include <Serialization/Serilializer.h>
#include <Serialization/Serialize.h>
#include <Serialization/Archive.h>
//#include <Window/BaseWindow.h>
#include <Reflection/Text.h>
#include <Importer/Importer.h>
#include <Sound/SoundWave.h>
#include <FileReadWriter/Reader/FileReader.h>
#include "Test2.h"
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
	Text text2;
	text2.line = "New Text";
	Text text;
	text.line = "Sentence";
	text.age = 300;
	text.height = 54;
	text.text = new Text();
	text.GetClass().GetProperty<int>("age") = 30;
	text.GetClass().GetProperty<std::string>("line") = "Micheal";
	text.GetClass().GetProperty<float>("height") = 94.0f;
	//text.GetClass().GetProperty<Text>("Text") = text2;
	
	for (auto prop : text.GetClass().GetProperties())
	{
		std::cout << "name: " << prop.first <<  " value: ";
		prop.second->PrintValue();
	}

	//SoundWave* test1 = Importer::Import<SoundWave>(L"C:\\Users\\Darius Bigbee\\Desktop\\test1.wav");
	//test1->bLoop = true;
	//test1->PrintInfo();
	////test1->Play();
	//
	//SoundMpeg* ost = Importer::Import<SoundMpeg>(L"C:\\Users\\Darius Bigbee\\Desktop\\DBLegendsShallotSSJ3OST.mp3");
	//ost->Play();

	/*SoundWave* DoorWave = Importer::Import<SoundWave>(L"C:\\Users\\Darius Bigbee\\Desktop\\SW_Door_Open.wav");
	DoorWave->PrintInfo();
	DoorWave->Play();*/

	//test1->Stop();
	

	//delete waveptr;

	//Serialization test example
	Serialization::Archive archive = Serialization::Archive("Test2SavedNonBinary", false);
	Test2 test;

	test.average = 30.0f;
	test.time = 20;

	archive.DeSerialize(test);

	test.average = 45.0f;
	test.time = 54;
	test.floats.push_back(60.0f);
	test.floats.push_back(800.7f);

	archive.Serialize(test);


	/*Serialization::Serilializer::Load();

	Serialization::Serilializer::Save();*/

	std::cin.get();
	return 0 ;
}

