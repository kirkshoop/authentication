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

unique_hresult scard_creduiscenario::SetUsageScenario( 
    /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    /* [in] */ DWORD dwFlags)
{
	scenarioFlags = dwFlags;
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
	if (dwIndex >= lib::rng::size(fields))
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
