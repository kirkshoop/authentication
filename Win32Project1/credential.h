
namespace credentialprovidercredential
{
	struct tag {};

	class type : public lib::com::aggregating_refcount
	{
	public:

		type() {}

		using aggregating_refcount::interface_constructed;
		inline void interface_constructed(ICredentialProviderCredential*, lib::ifset::interface_tag<ICredentialProviderCredential>&&) 
		{}

        unique_hresult Advise( 
            /* [in] */ ICredentialProviderCredentialEvents *pcpce); 

        unique_hresult UnAdvise( void);
        
        unique_hresult SetSelected( 
            /* [out] */ BOOL *pbAutoLogon);
        
        unique_hresult SetDeselected( void);
        
        unique_hresult GetFieldState( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ CREDENTIAL_PROVIDER_FIELD_STATE *pcpfs,
            /* [out] */ CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE *pcpfis);
        
        unique_hresult GetStringValue( 
            /* [in] */ DWORD dwFieldID,
            /* [string][out] */ LPWSTR *ppsz);
        
        unique_hresult GetBitmapValue( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ HBITMAP *phbmp);
        
        unique_hresult GetCheckboxValue( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ BOOL *pbChecked,
            /* [string][out] */ LPWSTR *ppszLabel);
        
        unique_hresult GetSubmitButtonValue( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ DWORD *pdwAdjacentTo);
        
        unique_hresult GetComboBoxValueCount( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ DWORD *pcItems,
            /* [out] */ DWORD *pdwSelectedItem);
        
        unique_hresult GetComboBoxValueAt( 
            /* [in] */ DWORD dwFieldID,
            DWORD dwItem,
            /* [string][out] */ LPWSTR *ppszItem);
        
        unique_hresult SetStringValue( 
            /* [in] */ DWORD dwFieldID,
            /* [string][in] */ LPCWSTR psz);
        
        unique_hresult SetCheckboxValue( 
            /* [in] */ DWORD dwFieldID,
            /* [in] */ BOOL bChecked);
        
        unique_hresult SetComboBoxSelectedValue( 
            /* [in] */ DWORD dwFieldID,
            /* [in] */ DWORD dwSelectedItem);
        
        unique_hresult CommandLinkClicked( 
            /* [in] */ DWORD dwFieldID);
        
        unique_hresult GetSerialization( 
            /* [out] */ CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE *pcpgsr,
            /* [out] */ CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs,
            /* [out] */ LPWSTR *ppszOptionalStatusText,
            /* [out] */ CREDENTIAL_PROVIDER_STATUS_ICON *pcpsiOptionalStatusIcon);
        
        unique_hresult ReportResult( 
            /* [in] */ NTSTATUS ntsStatus,
            /* [in] */ NTSTATUS ntsSubstatus,
            /* [out] */ LPWSTR *ppszOptionalStatusText,
            /* [out] */ CREDENTIAL_PROVIDER_STATUS_ICON *pcpsiOptionalStatusIcon);

	};
}

lib::ifset::traits_builder<lib::tv::factory<IUnknown, ICredentialProviderCredential>::type, credentialprovidercredential::type>
interface_set_traits(credentialprovidercredential::tag&&);

template<typename Storage, typename InterfaceTag>
credentialprovidercredential::type* interface_storage(Storage* storage, InterfaceTag&&, credentialprovidercredential::tag&&)
{
	return storage;
}

typedef
	lib::ifset::interface_set<credentialprovidercredential::tag>
credential;
