// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "scenario.h"
#include "scard_monitor.h"
#include "scard_creduiscenario.h"
#include "smartcardlogon.h"
#include "provider.h"

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


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



// {9A1153D7-99D3-4B96-B8D2-40782217B0DD}
static const GUID CLSID_SampleCredentialProvider = 
{ 0x9a1153d7, 0x99d3, 0x4b96, { 0xb8, 0xd2, 0x40, 0x78, 0x22, 0x17, 0xb0, 0xdd } };

HRESULT __stdcall DllGetClassObject(
  __in   REFCLSID rclsid,
  __in   REFIID riid,
  __out  LPVOID *ppv
)
{
	return com_function_contract_hresult(
		[&]() -> unique_hresult
		{
			unique_hresult hresult;

			if (InlineIsEqualGUID(CLSID_SampleCredentialProvider, rclsid))
			{
				std::unique_ptr<provider_factory> object(new provider_factory);

				if (!object)
				{
					return hresult_cast(E_OUTOFMEMORY);
				}

				hresult.reset(object->QueryInterface(riid, ppv));
				if (hresult)
				{
					object.release();
				}
			}
			else
			{
				hresult = hresult_cast(CLASS_E_CLASSNOTAVAILABLE);
			}
			return hresult;
		}, 
		int(), 
		int()
	);
}
