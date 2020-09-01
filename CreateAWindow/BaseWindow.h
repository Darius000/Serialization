#pragma once

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <Serialize.h>
#include <Archive.h>

enum class WindowShowType : int
{
	ForceMinimized = SW_FORCEMINIMIZE,
	Hide = SW_HIDE,
	Maximize = SW_MAXIMIZE,
	Minimize = SW_MINIMIZE,
	Restore = SW_RESTORE,
	Show = SW_SHOW,
	Default = SW_SHOWDEFAULT,
	ShowMaximized = SW_SHOWMAXIMIZED,
	ShowMinimized = SW_SHOWMINIMIZED,
	ShowMiniNoActive = SW_SHOWMINNOACTIVE,
	ShowNotActive = SW_SHOWNA,
	ShowRecentAndNotActive = SW_SHOWNOACTIVATE,
	ShowNormal = SW_SHOWNORMAL
};

template<class DERIVED_TYPE>
class BaseWindow : public Serialization::ISerializable
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVED_TYPE* pThis = nullptr;
		if (uMsg == WM_CREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)(lParam);
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hwnd = hwnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		
	}

	BaseWindow(const std::string& name, int32_t width = CW_USEDEFAULT, int32_t height = CW_USEDEFAULT):m_Name(name), 
		m_WindowName(), m_hwnd(nullptr), m_Width(width), m_Height(height){}

	BOOL Create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int32_t x = CW_USEDEFAULT,
		int32_t y = CW_USEDEFAULT,
		HWND hWndParent = nullptr,
		HMENU hMenu = nullptr
	)
	{
		m_WindowName = lpWindowName;

		WNDCLASS wc = {0};

		wc.lpfnWndProc  = DERIVED_TYPE::WindowProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpszClassName = ClassName();

		RegisterClass(&wc);

		m_hwnd = CreateWindowEx(dwExStyle, ClassName(),
		m_WindowName, dwStyle, x, y, m_Width, m_Height, hWndParent,
		hMenu, GetModuleHandle(nullptr), this);

		return (m_hwnd ? TRUE : FALSE);
	}

	void Show(WindowShowType windowShowType = WindowShowType::Default )
	{
		ShowWindow(m_hwnd, (int)windowShowType);
	}

	std::string& GetName() { return m_Name; }
	const char* GetFileName() override { return m_Name.c_str(); }

	HWND GetNativeWindow() const { return m_hwnd; }
	uint32_t GetWidth() const { return m_Width;}
	uint32_t GetHeight() const { return m_Height;}
	void Resize()
	{
		HWND Handle = ::FindWindow(ClassName(), GetWindowName());
		::SetWindowPos(Handle, nullptr, 0, 0, m_Width, m_Height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	}

	void SetActive()
	{
		::SetActiveWindow(m_hwnd);
	}

	void Serialize(Serialization::Archive& ar, unsigned int version) const override
	{
		ar & m_Name;
		ar & m_Width & m_Height;
	}

	void DeSerialize(Serialization::Archive& ar, unsigned int version) override
	{
		ar & m_Name;
		ar & m_Width & m_Height;

		Resize();
	}

protected:
	virtual PCWSTR ClassName() const = 0;
	virtual PCWSTR GetWindowName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	std::string m_Name;
	PCWSTR m_WindowName;
	HWND m_hwnd;
	int32_t m_Width;
	int32_t m_Height;
};


class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow(const std::string& name, uint32_t width = CW_USEDEFAULT, uint32_t height = CW_USEDEFAULT)
		: BaseWindow<MainWindow>(name, width, height){}
	PCWSTR ClassName() const override { return L"Main Window"; };
	PCWSTR GetWindowName() const override{ return m_WindowName; };

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			if (MessageBox(m_hwnd, L"Quit?", L"My Application", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(m_hwnd);
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(m_hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(m_hwnd, &ps);
		}
		return 0;
		case WM_SIZE:
		{
			int32_t width = LOWORD(lParam);
			int32_t height = HIWORD(lParam);

			OnResize(m_hwnd, (UINT)wParam, width, height);
		}
			return 0;
		default:
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		}
		
		return TRUE;
	}

	void OnResize(HWND hwnd, UINT flag, int32_t width, int32_t height)
	{
		m_Width = width;
		m_Height = height;
	}
};