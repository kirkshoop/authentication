
struct scard_creduiscenario
{
	scard_creduiscenario() {}

	scard_creduiscenario(scard_creduiscenario&& other)
		: events(std::move(other.events))
		, scenarioFlags(other.scenarioFlags)
		//, monitor(std::move(other.monitor))
		, tiles(std::move(other.tiles))
	{}

	unique_hresult SetUsageScenario( 
        /* [in] */ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
        /* [in] */ DWORD dwFlags);

	unique_hresult SetSerialization( 
        /* [in] */ const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcs);

	unique_hresult Advise( 
        /* [in] */ ICredentialProviderEvents *pcpe,
        /* [in] */ UINT_PTR upAdviseContext);

	unique_hresult UnAdvise( void);

	unique_hresult GetFieldDescriptorCount( 
        /* [out] */ DWORD *pdwCount);

	unique_hresult GetFieldDescriptorAt( 
        /* [in] */ DWORD dwIndex,
        /* [out] */ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd);

	unique_hresult GetCredentialCount( 
        /* [out] */ DWORD *pdwCount,
        /* [out] */ DWORD *pdwDefault,
        /* [out] */ BOOL *pbAutoLogonWithDefault);

	unique_hresult GetCredentialAt( 
        /* [in] */ DWORD dwIndex,
        /* [out] */ ICredentialProviderCredential **ppcpc);

	struct Tile
	{
	};

	credentialevents events;
	DWORD scenarioFlags;
	//smart_card::monitor_certificates monitor;
	std::vector<std::shared_ptr<Tile>> tiles;
private:
	scard_creduiscenario(const scard_creduiscenario&);
};
