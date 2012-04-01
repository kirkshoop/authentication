#include "stdafx.h"

#include "scenario.h"
#include "scard_monitor.h"
#include "scard_creduiscenario.h"
#include "smartcardlogon.h"
#include "provider.h"
#include "credential.h"

namespace credentialprovider
{
}

unique_hresult factory_create(IUnknown *pUnkOuter, REFIID riid, void **ppvObject, providerfactory::tag&&)
{
	std::unique_ptr<provider> object(new provider(pUnkOuter));

	if (!object)
	{
		return hresult_cast(E_OUTOFMEMORY);
	}

	unique_hresult hresult;

	hresult.reset(object->QueryInterface(riid, ppvObject));
	if (hresult)
	{
		object.release();
	}
	return hresult;
}
