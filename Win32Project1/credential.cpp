#include "stdafx.h"

#include "credential.h"

namespace credentialprovidercredential
{
    unique_hresult type::Advise( 
        /* [in] */ ICredentialProviderCredentialEvents *pcpce)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::UnAdvise( void)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::SetSelected( 
        /* [out] */ BOOL *pbAutoLogon)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::SetDeselected( void)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::GetFieldState( 
        /* [in] */ DWORD dwFieldID,
        /* [out] */ CREDENTIAL_PROVIDER_FIELD_STATE *pcpfs,
        /* [out] */ CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE *pcpfis)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::GetStringValue( 
        /* [in] */ DWORD dwFieldID,
        /* [string][out] */ LPWSTR *ppsz)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::GetBitmapValue( 
        /* [in] */ DWORD dwFieldID,
        /* [out] */ HBITMAP *phbmp)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::GetCheckboxValue( 
        /* [in] */ DWORD dwFieldID,
        /* [out] */ BOOL *pbChecked,
        /* [string][out] */ LPWSTR *ppszLabel)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::GetSubmitButtonValue( 
        /* [in] */ DWORD dwFieldID,
        /* [out] */ DWORD *pdwAdjacentTo)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::GetComboBoxValueCount( 
        /* [in] */ DWORD dwFieldID,
        /* [out] */ DWORD *pcItems,
        /* [out] */ DWORD *pdwSelectedItem)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::GetComboBoxValueAt( 
        /* [in] */ DWORD dwFieldID,
        DWORD dwItem,
        /* [string][out] */ LPWSTR *ppszItem)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::SetStringValue( 
        /* [in] */ DWORD dwFieldID,
        /* [string][in] */ LPCWSTR psz)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::SetCheckboxValue( 
        /* [in] */ DWORD dwFieldID,
        /* [in] */ BOOL bChecked)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::SetComboBoxSelectedValue( 
        /* [in] */ DWORD dwFieldID,
        /* [in] */ DWORD dwSelectedItem)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::CommandLinkClicked( 
        /* [in] */ DWORD dwFieldID)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::GetSerialization( 
        /* [out] */ CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE *pcpgsr,
        /* [out] */ CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs,
        /* [out] */ LPWSTR *ppszOptionalStatusText,
        /* [out] */ CREDENTIAL_PROVIDER_STATUS_ICON *pcpsiOptionalStatusIcon)
	{
		return hresult_cast(E_NOTIMPL);
	}
        
    unique_hresult type::ReportResult( 
        /* [in] */ NTSTATUS ntsStatus,
        /* [in] */ NTSTATUS ntsSubstatus,
        /* [out] */ LPWSTR *ppszOptionalStatusText,
        /* [out] */ CREDENTIAL_PROVIDER_STATUS_ICON *pcpsiOptionalStatusIcon)
	{
		return hresult_cast(E_NOTIMPL);
	}
}

