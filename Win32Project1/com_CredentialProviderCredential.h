#ifndef COM_CREDENTIALPROVIDERCREDENTIAL_SOURCE
#define COM_CREDENTIALPROVIDERCREDENTIAL_SOURCE

#ifndef COM_NAMESPACE
#error COM_NAMESPACE must be defined
#endif

namespace COM_NAMESPACE
{
	namespace ifset=INTERFACE_SET_NAMESPACE;

	namespace detail
	{
		template<typename ComObjectTag, typename Base>
		struct com_credentialprovidercredential
			: public Base
		{
			~com_credentialprovidercredential()
			{}

			com_credentialprovidercredential()
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
			explicit com_credentialprovidercredential(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
			com_credentialprovidercredential(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, Param)>
			com_credentialprovidercredential(TPLT_FUNCTION_ARGUMENTS_DECL(3, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(3, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, Param)>
			com_credentialprovidercredential(TPLT_FUNCTION_ARGUMENTS_DECL(4, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(4, Param, std::forward))
			{}

			HRESULT STDMETHODCALLTYPE Advise( 
				/* [in] */ ICredentialProviderCredentialEvents *pcpce)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->Advise(pcpce);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE UnAdvise( void)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->UnAdvise();
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE SetSelected( 
				/* [out] */ BOOL *pbAutoLogon)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->SetSelected(pbAutoLogon);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE SetDeselected( void)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->SetDeselected();
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetFieldState( 
				/* [in] */ DWORD dwFieldID,
				/* [out] */ CREDENTIAL_PROVIDER_FIELD_STATE *pcpfs,
				/* [out] */ CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE *pcpfis)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->GetFieldState(dwFieldID, pcpfs, pcpfis);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetStringValue( 
				/* [in] */ DWORD dwFieldID,
				/* [string][out] */ LPWSTR *ppsz)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->GetStringValue(dwFieldID, ppsz);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetBitmapValue( 
				/* [in] */ DWORD dwFieldID,
				/* [out] */ HBITMAP *phbmp)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->GetBitmapValue(dwFieldID, phbmp);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetCheckboxValue( 
				/* [in] */ DWORD dwFieldID,
				/* [out] */ BOOL *pbChecked,
				/* [string][out] */ LPWSTR *ppszLabel)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->GetCheckboxValue(dwFieldID, pbChecked, ppszLabel);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetSubmitButtonValue( 
				/* [in] */ DWORD dwFieldID,
				/* [out] */ DWORD *pdwAdjacentTo)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->GetSubmitButtonValue(dwFieldID, pdwAdjacentTo);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetComboBoxValueCount( 
				/* [in] */ DWORD dwFieldID,
				/* [out] */ DWORD *pcItems,
				/* [out] */ DWORD *pdwSelectedItem)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->GetComboBoxValueCount(dwFieldID, pcItems, pdwSelectedItem);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetComboBoxValueAt( 
				/* [in] */ DWORD dwFieldID,
				DWORD dwItem,
				/* [string][out] */ LPWSTR *ppszItem)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->GetComboBoxValueAt(dwFieldID, dwItem, ppszItem);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE SetStringValue( 
				/* [in] */ DWORD dwFieldID,
				/* [string][in] */ LPCWSTR psz)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->SetStringValue(dwFieldID, psz);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE SetCheckboxValue( 
				/* [in] */ DWORD dwFieldID,
				/* [in] */ BOOL bChecked)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->SetCheckboxValue(dwFieldID, bChecked);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE SetComboBoxSelectedValue( 
				/* [in] */ DWORD dwFieldID,
				/* [in] */ DWORD dwSelectedItem)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->SetComboBoxSelectedValue(dwFieldID, dwSelectedItem);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE CommandLinkClicked( 
				/* [in] */ DWORD dwFieldID)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->CommandLinkClicked(dwFieldID);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetSerialization( 
				/* [out] */ CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE *pcpgsr,
				/* [out] */ CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs,
				/* [out] */ LPWSTR *ppszOptionalStatusText,
				/* [out] */ CREDENTIAL_PROVIDER_STATUS_ICON *pcpsiOptionalStatusIcon)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->GetSerialization(pcpgsr, pcpcs, ppszOptionalStatusText, pcpsiOptionalStatusIcon);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE ReportResult( 
				/* [in] */ NTSTATUS ntsStatus,
				/* [in] */ NTSTATUS ntsSubstatus,
				/* [out] */ LPWSTR *ppszOptionalStatusText,
				/* [out] */ CREDENTIAL_PROVIDER_STATUS_ICON *pcpsiOptionalStatusIcon)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProviderCredential>(), 
							ComObjectTag()
						)->ReportResult(ntsStatus, ntsSubstatus, ppszOptionalStatusText, pcpsiOptionalStatusIcon);
					}, 
					ifset::interface_tag<ICredentialProviderCredential>(), 
					ComObjectTag()
				);
			}


		};
	}

	class credentialprovidercredential : public aggregating_refcount
	{
	public:
		template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
		explicit credentialprovidercredential(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
			: aggregating_refcount(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
		{}

		using aggregating_refcount::interface_constructed;
		inline void interface_constructed(ICredentialProviderCredential*, ifset::interface_tag<ICredentialProviderCredential>&&) 
		{}

        inline unique_hresult Advise( 
            /* [in] */ ICredentialProviderCredentialEvents *pcpce)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult UnAdvise( void)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult SetSelected( 
            /* [out] */ BOOL *pbAutoLogon)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult SetDeselected( void)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetFieldState( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ CREDENTIAL_PROVIDER_FIELD_STATE *pcpfs,
            /* [out] */ CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE *pcpfis)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetStringValue( 
            /* [in] */ DWORD dwFieldID,
            /* [string][out] */ LPWSTR *ppsz)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetBitmapValue( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ HBITMAP *phbmp)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetCheckboxValue( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ BOOL *pbChecked,
            /* [string][out] */ LPWSTR *ppszLabel)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetSubmitButtonValue( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ DWORD *pdwAdjacentTo)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetComboBoxValueCount( 
            /* [in] */ DWORD dwFieldID,
            /* [out] */ DWORD *pcItems,
            /* [out] */ DWORD *pdwSelectedItem)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetComboBoxValueAt( 
            /* [in] */ DWORD dwFieldID,
            DWORD dwItem,
            /* [string][out] */ LPWSTR *ppszItem)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult SetStringValue( 
            /* [in] */ DWORD dwFieldID,
            /* [string][in] */ LPCWSTR psz)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult SetCheckboxValue( 
            /* [in] */ DWORD dwFieldID,
            /* [in] */ BOOL bChecked)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult SetComboBoxSelectedValue( 
            /* [in] */ DWORD dwFieldID,
            /* [in] */ DWORD dwSelectedItem)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult CommandLinkClicked( 
            /* [in] */ DWORD dwFieldID)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetSerialization( 
            /* [out] */ CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE *pcpgsr,
            /* [out] */ CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs,
            /* [out] */ LPWSTR *ppszOptionalStatusText,
            /* [out] */ CREDENTIAL_PROVIDER_STATUS_ICON *pcpsiOptionalStatusIcon)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult ReportResult( 
            /* [in] */ NTSTATUS ntsStatus,
            /* [in] */ NTSTATUS ntsSubstatus,
            /* [out] */ LPWSTR *ppszOptionalStatusText,
            /* [out] */ CREDENTIAL_PROVIDER_STATUS_ICON *pcpsiOptionalStatusIcon)
		{
			return hresult_cast(E_NOTIMPL);
		}

	};
}

template<typename ComObjectTag>
COM_NAMESPACE::ifset::interface_traits_builder<COM_NAMESPACE::detail::com_credentialprovidercredential , COM_NAMESPACE::credentialprovidercredential>
interface_tag_traits(COM_NAMESPACE::ifset::interface_tag<ICredentialProviderCredential>&&, ComObjectTag&&);

#endif
