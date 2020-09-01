#ifndef UNICODE
#define UNICODE
#endif

#include "BaseWindow.h"
#include <Serilializer.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win("Create a Simple Window", 1080, 720);
	MainWindow win2("Second Window", 800, 600);

	if (!win.Create(L"Create a Simple Window", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}

	if (!win2.Create(L"Second Window", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}

	win.Show();
	win2.Show();
	win.SetActive();

	Serialization::Serilializer::Load();

	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Serialization::Serilializer::Save();

	return 0;
}

