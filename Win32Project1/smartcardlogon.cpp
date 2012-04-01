#include "stdafx.h"

#include "scenario.h"
#include "scard_monitor.h"
#include "smartcardlogon.h"

unique_hresult smartcardlogon::SetUsageScenario( 
    /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    /* [in] */ DWORD dwFlags)
{
	return hresult_cast(E_NOTIMPL);
}
        
unique_hresult smartcardlogon::SetSerialization( 
    /* [in] */ const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs)
{
	return hresult_cast(E_NOTIMPL);
}
        
unique_hresult smartcardlogon::Advise( 
    /* [in] */ ICredentialProviderEvents *pcpe,
    /* [in] */ UINT_PTR upAdviseContext)
{
	return hresult_cast(E_NOTIMPL);
}
        
unique_hresult smartcardlogon::UnAdvise( void)
{
	return hresult_cast(E_NOTIMPL);
}
        
unique_hresult smartcardlogon::GetFieldDescriptorCount( 
    /* [out] */ DWORD *pdwCount)
{
	return hresult_cast(E_NOTIMPL);
}
        
unique_hresult smartcardlogon::GetFieldDescriptorAt( 
    /* [in] */ DWORD dwIndex,
    /* [out] */ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd)
{
	return hresult_cast(E_NOTIMPL);
}
        
unique_hresult smartcardlogon::GetCredentialCount( 
    /* [out] */ DWORD *pdwCount,
    /* [out] */ DWORD *pdwDefault,
    /* [out] */ BOOL *pbAutoLogonWithDefault)
{
	return hresult_cast(E_NOTIMPL);
}
        
unique_hresult smartcardlogon::GetCredentialAt( 
    /* [in] */ DWORD dwIndex,
    /* [out] */ ICredentialProviderCredential **ppcpc)
{
	return hresult_cast(E_NOTIMPL);
}
