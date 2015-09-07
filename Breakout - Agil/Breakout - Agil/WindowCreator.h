#pragma once
#include <Windows.h>
#include <windowsx.h>
#include "GraphicsEngine.h"
class WindowCreator
{
public:
	WindowCreator();
	~WindowCreator();
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	GraphicsEngine *mGraphicsEngine;
};

