
struct scard_creduiscenario
{
	scard_creduiscenario() {}

	scard_creduiscenario(scard_creduiscenario&& other)
		: events(std::move(other.events))
		, scenarioFlags(other.scenarioFlags)
		, monitor(std::move(other.monitor))
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

	struct NoReadersTile
	{
	};

	struct EmptyReaderTile
	{
	};

	struct CardErrorTile
	{
	};

	struct CertificateTile
	{
	};

	typedef
		lib::of::one_of<typename lib::tv::factory<NoReadersTile, EmptyReaderTile, CardErrorTile, CertificateTile>::type>
	Tile;

	struct WindowNotifier
	{
		explicit WindowNotifier(HWND window)
			: window(window)
		{}

		void push()
		{
			PostMessage(window, WM_USER+1, 0, 0);
		}

		void pop()
		{
		}

		HWND window;
	};

	DWORD scenarioFlags;
	lib::wr::unique_close_window window;
	credentialevents events;
	smart_card::monitor_certificates<WindowNotifier> monitor;
	std::vector<std::shared_ptr<Tile>> tiles;
private:
	scard_creduiscenario(const scard_creduiscenario&);
};
