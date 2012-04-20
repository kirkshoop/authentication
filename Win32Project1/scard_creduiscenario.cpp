#include "stdafx.h"

#include "scenario.h"
#include "scard_monitor.h"
#include "credential.h"
#include "scard_creduiscenario.h"

namespace FieldIds
{
	enum type {
		Title
	};
};

CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR fields[] = {
	{FieldIds::Title, CPFT_LARGE_TEXT, L"Title", GUID_NULL},
};

namespace MessageWindow
{
	struct tag {};

	typedef
		lib::wnd::Context<tag>
	Context;

	struct window
	{
		explicit window(CREATESTRUCT& create)
		{
			scenario = reinterpret_cast<scard_creduiscenario*>(create.lpCreateParams);
		}

		LRESULT OnUnhandled(const Context& context)
		{
			if (context.message == WM_USER+1)
			{
				auto consumer = scenario->monitor.getconsumer();
				auto readers = consumer.pop();
				for (auto& reader : readers)
				{
					if (reader.card.valid())
					{
						auto card = reader.card.get();
						for (auto& key : card.certificates)
						{
							unique_winerror winerror;

							PCCERT_CONTEXT certcontext = CertCreateCertificateContext(
								X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
								&key.cert[0],
								key.cert.size()
							);
							winerror = make_winerror_if(!certcontext);

							if (!winerror)
							{

								continue;
							}

							DWORD sizesubject = 0;
							std::wstring subjectname;
							for (bool getsize = true; ; getsize = false)
							{
								sizesubject = CertGetNameString(
									certcontext,
									CERT_ALT_NAME_RFC822_NAME,//CERT_NAME_FRIENDLY_DISPLAY_TYPE,
									0,
									NULL,
									getsize ? nullptr : &subjectname[0],
									sizesubject
								);
								if (sizesubject == 1)
								{
									break;
								}
								if (getsize)
								{
									subjectname.resize(sizesubject - 1);
								}
								else
								{
									break;
								}
							}
						}
					}
				}
				return 0;
			}
			return DefWindowProc(context.window, context.message, context.wParam, context.lParam);
		}
		scard_creduiscenario* scenario;
	};

	lib::wnd::traits_builder<window> window_class_traits(tag&&);

	void window_class_register(PCWSTR windowClass, WNDCLASSEX* wcex, tag&&)
	{
		wcex->style         = 0;
		wcex->hIcon         = NULL;
		wcex->hCursor       = LoadCursor(NULL, IDC_ARROW);
		wcex->lpszMenuName  = NULL;
		wcex->lpszClassName = windowClass;
	}
}

template<typename Function, typename MessageTag>
void window_message_error_contract(Function&& function, const MessageWindow::Context& , MessageTag&&, MessageWindow::tag&&)
{
	try
	{
		std::forward<Function>(function)();
	}
	catch(std::bad_alloc&&)
	{
	}
	catch(unique_winerror::exception&&)
	{
	}
	catch(unique_hresult::exception&&)
	{
	}
}

typedef
	lib::wnd::window_class<MessageWindow::tag>
MessageWindowClass;


unique_hresult scard_creduiscenario::SetUsageScenario( 
	/* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
	/* [in] */ DWORD dwFlags)
{
	scenarioFlags = dwFlags;

	MessageWindowClass::Register(L"ScProviderMessages");

	unique_winerror winerror;

	std::tie(winerror, window) = 
		lib::wr::winerror_and_close_window(
			CreateWindow(
				L"ScProviderMessages", L"",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
				HWND_MESSAGE, NULL, 
				lib::cmn::GetCurrentInstance(), 
				this));

	if (!winerror || !window)
	{
		return hresult_cast(HRESULT_FROM_WIN32(winerror.get()));
	}

	monitor.start(WindowNotifier(window.get()));

	return hresult_cast(S_OK);
}

unique_hresult scard_creduiscenario::SetSerialization( 
	/* [in] */ const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs)
{
	return hresult_cast(E_NOTIMPL);
}

unique_hresult scard_creduiscenario::Advise( 
	/* [in] */ ICredentialProviderEvents *pcpe,
	/* [in] */ UINT_PTR upAdviseContext)
{
	events = credentialevents(pcpe, upAdviseContext);
	return hresult_cast(S_OK);
}

unique_hresult scard_creduiscenario::UnAdvise( void)
{
	events = credentialevents();
	return hresult_cast(S_OK);
}

unique_hresult scard_creduiscenario::GetFieldDescriptorCount( 
	/* [out] */ DWORD *pdwCount)
{
	*pdwCount = lib::rng::size_cast<DWORD>(lib::rng::size(fields));
	return hresult_cast(S_OK);
}

unique_hresult scard_creduiscenario::GetFieldDescriptorAt( 
	/* [in] */ DWORD dwIndex,
	/* [out] */ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd)
{
	if (dwIndex >=lib::rng::size_cast<DWORD>(lib::rng::size(fields)))
	{
		return hresult_cast(E_BOUNDS);
	}
	*ppcpfd = fields + dwIndex;
	return hresult_cast(S_OK);
}

unique_hresult scard_creduiscenario::GetCredentialCount( 
	/* [out] */ DWORD *pdwCount,
	/* [out] */ DWORD *pdwDefault,
	/* [out] */ BOOL *pbAutoLogonWithDefault)
{
	*pdwCount = lib::rng::size_cast<DWORD>(tiles.size());
	*pdwDefault = 0;
	*pbAutoLogonWithDefault = FALSE;
	return hresult_cast(S_OK);
}

unique_hresult scard_creduiscenario::GetCredentialAt( 
	/* [in] */ DWORD dwIndex,
	/* [out] */ ICredentialProviderCredential **ppcpc)
{
	if (dwIndex >= tiles.size())
	{
		return hresult_cast(E_BOUNDS);
	}

	std::unique_ptr<credential> object(new credential);

	if (!object)
	{
		return hresult_cast(E_OUTOFMEMORY);
	}

	unique_hresult hresult;

	hresult.reset(object->QueryInterface(IID_ICredentialProviderCredential, (VOID**)ppcpc));
	if (hresult)
	{
		object.release();
	}
	return hresult;
}
