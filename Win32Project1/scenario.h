
typedef
	lib::wr::unique_com_interface<ICredentialProviderEvents>::type
unique_com_credentialproviderevents;

struct credentialevents
{
	inline ~credentialevents()
	{
		context = 0;
	}

	inline credentialevents()
		: context(0)
	{
	}

	inline credentialevents(credentialevents&& other)
		: events(std::move(other.events))
		, context(other.context)
	{
		other.context = 0;
	}

	inline credentialevents(ICredentialProviderEvents* eventsArg, UINT_PTR contextArg)
		: events(eventsArg)
		, context(contextArg)
	{
		if (events)
		{
			events->AddRef();
		}
	}

	inline credentialevents& operator=(credentialevents other)
	{
		events = std::move(other.events);
		using std::swap;
		swap(context, other.context);
		return *this;
	}

	inline unique_hresult CredentialsChanged()
	{
		if (!events || !context)
		{
			return hresult_cast(E_UNEXPECTED);
		}
		return hresult_cast(events->CredentialsChanged(context));
	}

	unique_com_credentialproviderevents events;
	UINT_PTR context;
private:
	credentialevents(const credentialevents&);
};

namespace scenario
{

	struct unsupportedscenario
	{
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

	//  CPUS_LOGON
    //  CPUS_UNLOCK_WORKSTATION
    //  CPUS_CHANGE_PASSWORD
    //  CPUS_CREDUI
    //  CPUS_PLAP
	template<
		typename LogonScenario = unsupportedscenario, 
		typename UnlockScenario = unsupportedscenario, 
		typename ChangeScenario = unsupportedscenario, 
		typename CredUiScenario = unsupportedscenario, 
		typename PlapScenario = unsupportedscenario>
	struct scenarios : public lib::com::aggregating_refcount
	{
		template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
		explicit scenarios(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
			: lib::com::aggregating_refcount(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
		{}

		using lib::com::aggregating_refcount::interface_constructed;
		inline void interface_constructed(ICredentialProvider*, lib::ifset::interface_tag<ICredentialProvider>&&) 
		{}

		unique_hresult SetUsageScenario( 
            /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
            /* [in] */ DWORD dwFlags)
		{
			scenarioId = cpus;
			switch (scenarioId)
			{
			case CPUS_LOGON:
				{
					scenario.reset(LogonScenario());
				}
				break;
			case CPUS_UNLOCK_WORKSTATION:
				{
					scenario.reset(UnlockScenario());
				}
				break;
			case CPUS_CHANGE_PASSWORD:
				{
					scenario.reset(ChangeScenario());
				}
				break;
			case CPUS_CREDUI:
				{
					scenario.reset(CredUiScenario());
				}
				break;
			case CPUS_PLAP:
				{
					scenario.reset(PlapScenario());
				}
				break;
			default:
				{
					return hresult_cast(E_NOTIMPL);
				}
				break;
			};

			return scenario.call_switch(
				[&] (LogonScenario& scenario) { return scenario.SetUsageScenario(scenarioId, dwFlags);},
				[&] (UnlockScenario& scenario) { return scenario.SetUsageScenario(scenarioId, dwFlags);},
				[&] (ChangeScenario& scenario) { return scenario.SetUsageScenario(scenarioId, dwFlags);},
				[&] (CredUiScenario& scenario) { return scenario.SetUsageScenario(scenarioId, dwFlags);},
				[&] (PlapScenario& scenario) { return scenario.SetUsageScenario(scenarioId, dwFlags);},
				[&] () { return hresult_cast(E_NOTIMPL);}
			);
		}
        
        unique_hresult SetSerialization( 
            /* [in] */ const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs)
		{
			return scenario.call_switch(
				[&] (LogonScenario& scenario) { return scenario.SetSerialization(pcpcs);},
				[&] (UnlockScenario& scenario) { return scenario.SetSerialization(pcpcs);},
				[&] (ChangeScenario& scenario) { return scenario.SetSerialization(pcpcs);},
				[&] (CredUiScenario& scenario) { return scenario.SetSerialization(pcpcs);},
				[&] (PlapScenario& scenario) { return scenario.SetSerialization(pcpcs);},
				[&] () { return hresult_cast(E_NOTIMPL);}
			);
		}
        
        unique_hresult Advise( 
            /* [in] */ ICredentialProviderEvents *pcpe,
            /* [in] */ UINT_PTR upAdviseContext)
		{
			return scenario.call_switch(
				[&] (LogonScenario& scenario) { return scenario.Advise(pcpe, upAdviseContext);},
				[&] (UnlockScenario& scenario) { return scenario.Advise(pcpe, upAdviseContext);},
				[&] (ChangeScenario& scenario) { return scenario.Advise(pcpe, upAdviseContext);},
				[&] (CredUiScenario& scenario) { return scenario.Advise(pcpe, upAdviseContext);},
				[&] (PlapScenario& scenario) { return scenario.Advise(pcpe, upAdviseContext);},
				[&] () { return hresult_cast(E_NOTIMPL);}
			);
		}
        
        unique_hresult UnAdvise( void)
		{
			return scenario.call_switch(
				[&] (LogonScenario& scenario) { return scenario.UnAdvise();},
				[&] (UnlockScenario& scenario) { return scenario.UnAdvise();},
				[&] (ChangeScenario& scenario) { return scenario.UnAdvise();},
				[&] (CredUiScenario& scenario) { return scenario.UnAdvise();},
				[&] (PlapScenario& scenario) { return scenario.UnAdvise();},
				[&] () { return hresult_cast(E_NOTIMPL);}
			);
		}
        
        unique_hresult GetFieldDescriptorCount( 
            /* [out] */ DWORD *pdwCount)
		{
			return scenario.call_switch(
				[&] (LogonScenario& scenario) { return scenario.GetFieldDescriptorCount(pdwCount);},
				[&] (UnlockScenario& scenario) { return scenario.GetFieldDescriptorCount(pdwCount);},
				[&] (ChangeScenario& scenario) { return scenario.GetFieldDescriptorCount(pdwCount);},
				[&] (CredUiScenario& scenario) { return scenario.GetFieldDescriptorCount(pdwCount);},
				[&] (PlapScenario& scenario) { return scenario.GetFieldDescriptorCount(pdwCount);},
				[&] () { return hresult_cast(E_NOTIMPL);}
			);
		}
        
        unique_hresult GetFieldDescriptorAt( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd)
		{
			return scenario.call_switch(
				[&] (LogonScenario& scenario) { return scenario.GetFieldDescriptorAt(dwIndex, ppcpfd);},
				[&] (UnlockScenario& scenario) { return scenario.GetFieldDescriptorAt(dwIndex, ppcpfd);},
				[&] (ChangeScenario& scenario) { return scenario.GetFieldDescriptorAt(dwIndex, ppcpfd);},
				[&] (CredUiScenario& scenario) { return scenario.GetFieldDescriptorAt(dwIndex, ppcpfd);},
				[&] (PlapScenario& scenario) { return scenario.GetFieldDescriptorAt(dwIndex, ppcpfd);},
				[&] () { return hresult_cast(E_NOTIMPL);}
			);
		}
        
        unique_hresult GetCredentialCount( 
            /* [out] */ DWORD *pdwCount,
            /* [out] */ DWORD *pdwDefault,
            /* [out] */ BOOL *pbAutoLogonWithDefault)
		{
			return scenario.call_switch(
				[&] (LogonScenario& scenario) { return scenario.GetCredentialCount(pdwCount, pdwDefault, pbAutoLogonWithDefault);},
				[&] (UnlockScenario& scenario) { return scenario.GetCredentialCount(pdwCount, pdwDefault, pbAutoLogonWithDefault);},
				[&] (ChangeScenario& scenario) { return scenario.GetCredentialCount(pdwCount, pdwDefault, pbAutoLogonWithDefault);},
				[&] (CredUiScenario& scenario) { return scenario.GetCredentialCount(pdwCount, pdwDefault, pbAutoLogonWithDefault);},
				[&] (PlapScenario& scenario) { return scenario.GetCredentialCount(pdwCount, pdwDefault, pbAutoLogonWithDefault);},
				[&] () { return hresult_cast(E_NOTIMPL);}
			);
		}
        
        unique_hresult GetCredentialAt( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ ICredentialProviderCredential **ppcpc)
		{
			return scenario.call_switch(
				[&] (LogonScenario& scenario) { return scenario.GetCredentialAt(dwIndex, ppcpc);},
				[&] (UnlockScenario& scenario) { return scenario.GetCredentialAt(dwIndex, ppcpc);},
				[&] (ChangeScenario& scenario) { return scenario.GetCredentialAt(dwIndex, ppcpc);},
				[&] (CredUiScenario& scenario) { return scenario.GetCredentialAt(dwIndex, ppcpc);},
				[&] (PlapScenario& scenario) { return scenario.GetCredentialAt(dwIndex, ppcpc);},
				[&] () { return hresult_cast(E_NOTIMPL);}
			);
		}

		CREDENTIAL_PROVIDER_USAGE_SCENARIO scenarioId;
		lib::of::one_of<
			typename lib::tv::factory<
				LogonScenario, 
				UnlockScenario, 
				ChangeScenario, 
				CredUiScenario, 
				PlapScenario
			>::type
		> scenario;
	};
}