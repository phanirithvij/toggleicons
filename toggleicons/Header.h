#pragma once
#include <windows.h>
#include <shellapi.h>
#include <ShlObj.h>    // Shell API
#include <atlcomcli.h> // CComPtr & Co.
#include <string>
#include <iostream>
#include <system_error>

// https://stackoverflow.com/q/495021/8608146
// Templates can only be defined in the header file
// if not need to have all the code in a single file

// Throw a std::system_error if the HRESULT indicates failure.
template <typename T>
void ThrowIfFailed(HRESULT hr, T&& msg)
{
	if (FAILED(hr))
		throw std::system_error{ hr, std::system_category(), std::forward<T>(msg) };
}
// RAII wrapper to initialize/uninitialize COM
struct CComInit
{
	CComInit() { ThrowIfFailed(::CoInitialize(nullptr), "CoInitialize failed"); }
	~CComInit() { ::CoUninitialize(); }
	CComInit(CComInit const&) = delete;
	CComInit& operator=(CComInit const&) = delete;
};

void ToggleDesktopIcons();
