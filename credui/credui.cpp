// credui.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\win32project1\scard_monitor.h"

void unique_error_report_initiated(HRESULT value, unique_hresult_def::tag&&)
{
	static HRESULT anchor;
	anchor = value;
}

void unique_error_report_reset(HRESULT value, unique_hresult_def::tag&&)
{
	static HRESULT anchor;
	anchor = value;
}

void unique_error_report_initiated(DWORD value, unique_winerror_def::tag&&)
{
	static DWORD anchor;
	anchor = value;
}

void unique_error_report_reset(DWORD value, unique_winerror_def::tag&&)
{
	static DWORD anchor;
	anchor = value;
}

inline CREDUI_INFO make(PCWSTR caption = NULL, PCWSTR message = NULL, HBITMAP banner = NULL)
{
	CREDUI_INFO result = {};

	result.cbSize = sizeof(CREDUI_INFO);
	result.pszMessageText = message;
    result.pszCaptionText = caption;
    result.hbmBanner = banner;

	return result;
}

int wmain(int argc, WCHAR* argv[])
{
	unique_winerror winerror;
	CREDUI_INFO info = make(L"Test CredUI", L"Enter a credential.");
	ULONG package = 0;
	PVOID auth;
	ULONG authsize = 0;
	BOOL save = FALSE;
	for(;;)
	{
		winerror.reset(
			CredUIPromptForWindowsCredentials(
				&info,
				winerror.get(),
				&package,
				NULL,
				0,
				&auth,
				&authsize,
				&save,
				0
			)
		);
		winerror.suppress();
	}
	return 0;
}

