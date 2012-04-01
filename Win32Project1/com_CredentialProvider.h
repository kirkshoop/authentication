#ifndef COM_CREDENTIALPROVIDER_SOURCE
#define COM_CREDENTIALPROVIDER_SOURCE

#ifndef COM_NAMESPACE
#error COM_NAMESPACE must be defined
#endif

namespace COM_NAMESPACE
{
	namespace ifset=INTERFACE_SET_NAMESPACE;

	namespace detail
	{
		template<typename ComObjectTag, typename Base>
		struct com_credentialprovider
			: public Base
		{
			~com_credentialprovider()
			{}

			com_credentialprovider()
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
			explicit com_credentialprovider(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
			com_credentialprovider(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, Param)>
			com_credentialprovider(TPLT_FUNCTION_ARGUMENTS_DECL(3, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(3, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, Param)>
			com_credentialprovider(TPLT_FUNCTION_ARGUMENTS_DECL(4, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(4, Param, std::forward))
			{}

			HRESULT STDMETHODCALLTYPE SetUsageScenario( 
				/* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
				/* [in] */ DWORD dwFlags)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProvider>(), 
							ComObjectTag()
						)->SetUsageScenario(cpus, dwFlags);
					}, 
					ifset::interface_tag<ICredentialProvider>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE SetSerialization( 
				/* [in] */ const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProvider>(), 
							ComObjectTag()
						)->SetSerialization(pcpcs);
					}, 
					ifset::interface_tag<ICredentialProvider>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE Advise( 
				/* [in] */ ICredentialProviderEvents *pcpe,
				/* [in] */ UINT_PTR upAdviseContext)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProvider>(), 
							ComObjectTag()
						)->Advise(pcpe, upAdviseContext);
					}, 
					ifset::interface_tag<ICredentialProvider>(), 
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
							ifset::interface_tag<ICredentialProvider>(), 
							ComObjectTag()
						)->UnAdvise();
					}, 
					ifset::interface_tag<ICredentialProvider>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetFieldDescriptorCount( 
				/* [out] */ DWORD *pdwCount)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProvider>(), 
							ComObjectTag()
						)->GetFieldDescriptorCount(pdwCount);
					}, 
					ifset::interface_tag<ICredentialProvider>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetFieldDescriptorAt( 
				/* [in] */ DWORD dwIndex,
				/* [out] */ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProvider>(), 
							ComObjectTag()
						)->GetFieldDescriptorAt(dwIndex, ppcpfd);
					}, 
					ifset::interface_tag<ICredentialProvider>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetCredentialCount( 
				/* [out] */ DWORD *pdwCount,
				/* [out] */ DWORD *pdwDefault,
				/* [out] */ BOOL *pbAutoLogonWithDefault)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProvider>(), 
							ComObjectTag()
						)->GetCredentialCount(pdwCount, pdwDefault, pbAutoLogonWithDefault);
					}, 
					ifset::interface_tag<ICredentialProvider>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE GetCredentialAt( 
				/* [in] */ DWORD dwIndex,
				/* [out] */ ICredentialProviderCredential **ppcpc)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<ICredentialProvider>(), 
							ComObjectTag()
						)->GetCredentialAt(dwIndex, ppcpc);
					}, 
					ifset::interface_tag<ICredentialProvider>(), 
					ComObjectTag()
				);
			}

		};
	}

	class credentialprovider : public aggregating_refcount
	{
	public:
		template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
		explicit credentialprovider(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
			: aggregating_refcount(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
		{}

		using aggregating_refcount::interface_constructed;
		inline void interface_constructed(ICredentialProvider*, ifset::interface_tag<ICredentialProvider>&&) 
		{}

		inline unique_hresult SetUsageScenario( 
            /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
            /* [in] */ DWORD dwFlags)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult SetSerialization( 
            /* [in] */ const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult Advise( 
            /* [in] */ ICredentialProviderEvents *pcpe,
            /* [in] */ UINT_PTR upAdviseContext)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult UnAdvise( void)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetFieldDescriptorCount( 
            /* [out] */ DWORD *pdwCount)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetFieldDescriptorAt( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetCredentialCount( 
            /* [out] */ DWORD *pdwCount,
            /* [out] */ DWORD *pdwDefault,
            /* [out] */ BOOL *pbAutoLogonWithDefault)
		{
			return hresult_cast(E_NOTIMPL);
		}
        
        inline unique_hresult GetCredentialAt( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ ICredentialProviderCredential **ppcpc)
		{
			return hresult_cast(E_NOTIMPL);
		}
	};
}

template<typename ComObjectTag>
COM_NAMESPACE::ifset::interface_traits_builder<COM_NAMESPACE::detail::com_credentialprovider, COM_NAMESPACE::credentialprovider>
interface_tag_traits(COM_NAMESPACE::ifset::interface_tag<ICredentialProvider>&&, ComObjectTag&&);

#endif
