#include "Window.h"
#include "wtypes.h"
#include<iostream>

int Window::_width;
int Window::_height;
glm::vec3 Window::_center;

int Window::_usableWidth;
int Window::_usableHeight;
glm::vec3 Window::_usableCenter;

void Window::Init()
{
	UpdateWindowAttributes();
}

void Window::UpdateWindowAttributes()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	_width = desktop.right;
	_height = desktop.bottom;
	_center = glm::vec3(_width / 2.0, _height / 2.0, 0.0f);


	//_usableWidth = _width - ComponentUI::GetUIWindowWidth();
	//_usableWidth = _width;
    //_usableHeight= _height; //No UI at top or bottom. But might change in the future. TODO
	//_usableCenter = glm::vec3(_usableWidth / 2.0, _usableHeight / 2.0, 0.0f);
}