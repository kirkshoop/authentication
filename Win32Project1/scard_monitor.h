
namespace detail
{
	namespace close_scardcontext
	{
		struct tag {};
		inline SCARDCONTEXT unique_resource_invalid(tag&&) { return 0; }
		inline void unique_resource_reset(SCARDCONTEXT resource, tag&&) { SCardReleaseContext(resource); }
	}
}
typedef
	UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::close_scardcontext::tag>
unique_close_scardcontext;

#if 0

//
// windowmessage_produce is run in the producer thread 
//   implmentations should only access the parameters
//   and the producer.
// windowmessage_consume is run in the consumer thread
//   implmentations should only access the parameters
//   and the consumer.
//
template<typename MessageTag>
class windowmessage
{
public:
	typedef
		MessageTag
	tag;

	typedef
		decltype(windowmessage_produce(tag()))
	type;

	template<typename Arg>
	unique_winerror post(Arg&& arg)
	{
		auto produced = windowmessage_produce(std::forward<Arg>(arg), tag());
		{
			std::lock_guard<std::mutex> guarddata(shareddata);
			queue.push_back(std::move(produced));
		}
		return winerror_if(!PostMessage(window, message, 0, 0));
	}

	template<typename Arg>
	unique_winerror send(Arg&& arg)
	{
		auto produced = windowmessage_produce(std::forward<Arg>(arg), tag());
		{
			std::lock_guard<std::mutex> guarddata(shareddata);
			queue.push_back(std::move(produced));
		}
		return winerror_cast(SendMessage(window, message, 0, 0));
	}

	template<typename Arg>
	unique_winerror receive(Arg&& arg)
	{
		item consumed;
		{
			std::lock_guard<std::mutex> guarddata(shareddata);
			consumed = std::move(queue.front());
			queue.erase(queue.begin());
		}
		return windowmessage_consume(std::forward<Arg>(arg), consumed, tag());
	}

	std::mutex shareddata;
	std::vector<type> queue;
	HWND window;
	UINT message;
};

unique_winerror windowmessage_consume(item readers, tag&&)
{
	for (auto& reader : readers)
	{
		// get certs
		// create tiles
	}
	events.credentialschanged();
}

template<typename MessageVector>
class windowmessages
{
	unique_close_window window;
};

#endif 

namespace smart_card
{

inline SCARD_READERSTATE make(
	LPCWSTR reader, 
	lib::rng::range<PBYTE> atr = lib::rng::range<PBYTE>(), 
	DWORD current = SCARD_STATE_UNAWARE, 
	DWORD event = SCARD_STATE_UNAWARE, 
	PVOID data = nullptr
)
{
	SCARD_READERSTATE result;

	result.dwCurrentState = current;
	result.dwEventState = event;
	result.pvUserData = data;
	if (atr.empty())
	{
		ZeroMemory(result.rgbAtr, sizeof(result.rgbAtr));
		result.cbAtr = 0;
	}
	else
	{
		std::copy(atr.begin(), atr.end(), result.rgbAtr);
		result.cbAtr = lib::rng::size_cast<DWORD>(atr.size());
	}
	result.szReader = reader;

	return result;
}

template<typename Functor>
void monitor_error_contract(Functor&& functor)
{
	FAIL_FAST_ON_THROW(
		[&]
		{
			try
			{
				std::forward<Functor>(functor)();
			}
			catch (const std::bad_alloc& )
			{
			}
		}
	);
}

struct KeyWithCertificate
{
	std::wstring key;
	std::vector<BYTE> cert;
};
typedef
	std::vector<KeyWithCertificate>
KeyWithCertificateVector;

inline
std::pair<unique_winerror, KeyWithCertificateVector> 
smartcard_certificates(
	const std::wstring& kspstring
)
{
	unique_winerror winerror;
	KeyWithCertificateVector output;

	NCRYPT_PROV_HANDLE provider = NULL;
	ON_UNWIND_AUTO(
		[&] { if (provider) {NCryptFreeObject(provider);};}
	);
	winerror.reset(
		NCryptOpenStorageProvider
		(
			&provider,
			kspstring.c_str(),
			0
		)
	);
	if (!winerror)
	{
		return std::make_pair(winerror, std::move(output));
	}

	NCryptKeyName* keyname = nullptr;
	ON_UNWIND_AUTO(
		[&] { if (keyname) {NCryptFreeBuffer(keyname);};}
	);
	void* enumstate = nullptr;
	ON_UNWIND_AUTO(
		[&] { if (enumstate) {NCryptFreeBuffer(enumstate);};}
	);
	for (;;)
	{
		winerror.reset(
			NCryptEnumKeys(
				provider,
				NULL,
				&keyname,
				&enumstate,
				NCRYPT_SILENT_FLAG
			)
		);
		if (winerror == winerror_cast(NTE_NO_MORE_ITEMS))
		{
			winerror.suppress().release();
			break;
		}
		if (!winerror)
		{
			return std::make_pair(winerror, std::move(output));
		}

		KeyWithCertificate keystate;
		keystate.key = keyname->pszName;

		NCRYPT_KEY_HANDLE key = NULL;
		ON_UNWIND_AUTO(
			[&] { if (key) {NCryptFreeObject(key);};}
		);
		winerror.reset(
				NCryptOpenKey(
					provider,
					&key,
					keyname->pszName,
					keyname->dwLegacyKeySpec,
					NCRYPT_SILENT_FLAG
				)
		);
		if (!winerror)
		{
			return std::make_pair(winerror, std::move(output));
		}

		DWORD sizecert = 0;
		for (bool getsize = true; ; getsize = false)
		{
			winerror.reset(
				NCryptGetProperty(
					key, 
					NCRYPT_CERTIFICATE_PROPERTY, 
					getsize ? nullptr : &keystate.cert[0],
					sizecert,
					&sizecert,
					0
				)
			);
			if (!winerror)
			{
				return std::make_pair(winerror, std::move(output));
			}
			if (getsize)
			{
				keystate.cert.resize(sizecert);
			}
			else
			{
				break;
			}
		}

		output.push_back(keystate);
	}

	return std::make_pair(winerror, std::move(output));
}

struct CardWithProvider
{
	std::wstring cardname;
	std::wstring kspname;
};

inline
std::pair<unique_winerror, CardWithProvider> 
smartcard_name_and_provider(
	lib::rng::range<const BYTE*> atr
)
{
	unique_winerror winerror;
	unique_close_scardcontext context;

	CardWithProvider output;

	winerror.reset(
		SCardEstablishContext(
			SCARD_SCOPE_USER,
			NULL,
			NULL,
			context.replace()
		)
	);
	if (!winerror)
	{
		return std::make_pair(winerror, std::move(output));
	}

	LPWSTR kspstring = nullptr;
	ON_UNWIND(
		unwind_kspstring,
		[&] { if (kspstring) {SCardFreeMemory(context.get(), kspstring);};}
	);
	DWORD ksplength = SCARD_AUTOALLOCATE;

	LPWSTR cardsstring = nullptr;
	ON_UNWIND_AUTO(
		[&] { if (cardsstring) {SCardFreeMemory(context.get(), cardsstring);};}
	);
	DWORD cardslength = SCARD_AUTOALLOCATE;

	winerror.reset(
		SCardListCards(
			context.get(), 
			atr.begin(), 
			NULL, 
			NULL, 
			reinterpret_cast<LPWSTR>(&cardsstring),
			&cardslength
		)
	);
	if (winerror == winerror_cast(SCARD_E_READER_UNAVAILABLE))
	{
		winerror.suppress();
		// don't free the static string we are about to assign
		unwind_kspstring.dismiss();
		kspstring = MS_SMART_CARD_KEY_STORAGE_PROVIDER;
		ksplength = wcslen(kspstring);
	}
	else if (!winerror)
	{
		return std::make_pair(winerror, std::move(output));
	}
	else
	{
		winerror.reset(
			SCardGetCardTypeProviderName(
				context.get(), 
				cardsstring, 
				SCARD_PROVIDER_KSP, 
				reinterpret_cast<LPWSTR>(&kspstring),
				&ksplength
			)
		);
		if (!winerror)
		{
			return std::make_pair(winerror, std::move(output));
		}
	}

	if (cardsstring)
	{
		output.cardname = cardsstring;
	}
	output.kspname = kspstring;

	return std::make_pair(winerror, std::move(output));
}

template<typename SetContext, typename ClearContext, typename Wait, typename Report>
unique_winerror 
monitor_smartcard_readers(
	SetContext&& setContext, 
	ClearContext&& clearContext, 
	Wait&& wait, 
	Report&&  report
)
{
	unique_winerror winerror;

	std::vector<wchar_t> readernames;
	std::vector<SCARD_READERSTATE> readers;

	while (winerror)
	{
		//
		// make sure that the scard service has started 
		// and that the loop has not been cancelled
		//

		if (!std::forward<Wait>(wait)())
		{
			return winerror_cast(SCARD_E_CANCELLED);
		}

		monitor_error_contract(
			[&] () 
			{
				unique_close_scardcontext context;
				ON_UNWIND_AUTO(
					[&]
					{
						std::forward<ClearContext>(clearContext)();
					}
				);

				//
				// need a fresh context whenever we start over.
				// lots of sytem changes could have caused this 
				// restart including the scard service stopping 
				// and then restarting.
				//

				winerror.reset(
					SCardEstablishContext(
						SCARD_SCOPE_USER,
						NULL,
						NULL,
						context.replace()
					)
				);
				if (!winerror || !context)
				{
					return;
				}

				std::forward<SetContext>(setContext)(context.get());

				//
				// make sure that loop has not been cancelled.
				// without this there is a race where the new 
				// context is not cancelled because the caller
				// cancelled at a time when there was no 
				// context yet.
				//

				if (!std::forward<Wait>(wait)())
				{
					winerror = winerror_cast(SCARD_E_CANCELLED);
					return;
				}

				if (readers.empty())
				{
					//
					// add PnP state query
					// setting the state to unaware causes SCardGetStatusChange
					// to return immediately with the actual pnp state.
					//
					readers.push_back(make(L"\\\\?PnP?\\Notification"));
				}

				for(;;)
				{
					auto readersstaterange = lib::rng::make_range_raw(readers);

					winerror.reset(
						SCardGetStatusChange(
							context.get(),
							INFINITE,
							readersstaterange.begin(),
							lib::rng::size_cast<DWORD>(readersstaterange.size())
						)
					);
					if (!winerror)
					{
						// exit
						return;
					}

					//
					// report changes
					//
					auto readersrange = lib::rng::make_range_raw(readers, 0, -1);
					if (!readersrange.empty())
					{
						std::forward<Report>(report)(readersrange);
					}

					//
					// record the changes we have reported
					//
					for (auto& state : readers)
					{
						state.dwCurrentState = state.dwEventState;
					}

					if ((readers.back().dwEventState & SCARD_STATE_CHANGED) == SCARD_STATE_CHANGED)
					{
						// Pnp event - list readers.
						break;
					}
				}

				// keep the old allocations for use to build the new list.
				std::vector<wchar_t> oldreadernames(std::move(readernames));
				std::vector<SCARD_READERSTATE> oldreaders(std::move(readers));

				// exclude the pnp reader
				auto oldreaderssortedrange = lib::rng::make_range(oldreaders, 0, -1);

				LPWSTR concatreaderstrings = nullptr;
				ON_UNWIND_AUTO(
					[&] { if (concatreaderstrings) {SCardFreeMemory(context.get(), concatreaderstrings);};}
				);
				DWORD totallength = SCARD_AUTOALLOCATE;

				winerror.reset(
					SCardListReaders(
						context.get(), 
						nullptr,
						reinterpret_cast<LPWSTR>(&concatreaderstrings),
						&totallength
					)
				);
				if (winerror == winerror_cast(SCARD_E_NO_READERS_AVAILABLE))
				{
					// no readers is not an error, loop around to wait 
					// for a reader to be connected
					winerror.suppress().release();
					return;
				}
				else if (!winerror)
				{
					return;
				}

				// keep the names around because the state array will have pointers into this
				readernames.assign(concatreaderstrings, concatreaderstrings + totallength);

				auto readerstateless = [](const SCARD_READERSTATE& lhs, const SCARD_READERSTATE& rhs) -> bool 
				{
					return _wcsicmp(lhs.szReader, rhs.szReader) < 0;
				};
	
				//
				// all the reader names are concatenated in this array with 
				// embedded nulls for each and two nulls to mark the end
				//
				auto cursorreadernames = lib::rng::make_range_raw(readernames);
				while(!cursorreadernames.empty() && cursorreadernames.front() != L'\0')
				{
					// access the current name
					auto namerange = lib::rng::make_range(
						cursorreadernames, 
						0,
						wcslen(cursorreadernames.begin()) - cursorreadernames.size()
					);
					// skip to the next name
					cursorreadernames = lib::rng::make_range(namerange, namerange.size() + 1, 0);

					auto oldreader = std::equal_range(
						oldreaderssortedrange.begin(), 
						oldreaderssortedrange.end(), 
						make(namerange.begin()), 
						readerstateless
					);
					if (oldreader.first != oldreader.second)
					{
						// keep the old state for this reader
						readers.push_back(*oldreader.first);

						// must use the new string allocation, 
						// the old one will be gone soon
						readers.back().szReader = namerange.begin();
					}
					else
					{
						readers.push_back(make(namerange.begin()));
					}
				}

				// keeping them sorted makes the updates more stable and allows the 
				// equal_range above instead of a linear find.
				std::sort(readers.begin(), readers.end(), readerstateless);

				//
				// add PnP state query
				// keep the existing state, and keep it at the 
				// end, out of the sorted area.
				//
				readers.push_back(oldreaders.back());
			}
		);
	}
	return winerror;
}

template<typename T>
class producerqueue
{
public:
	~producerqueue()
	{
		join();
	}

	template<typename Produce>
	producerqueue(std::function<void()> cancel, Produce&& produce)
		: cancel(std::move(cancel))
	{
		unique_winerror winerror;

		std::tie(winerror, producedevent) = lib::wr::winerror_and_event(CreateEvent(NULL, TRUE, FALSE, NULL));
		winerror.throw_if("could not create futures available event");

		std::tie(winerror, exitevent) = lib::wr::winerror_and_event(CreateEvent(NULL, TRUE, FALSE, NULL));
		winerror.throw_if("could not create exit event");

		producer = std::thread(std::forward<Produce>(produce));
	}

	T pop()
	{
		WaitForSingleObject(producedevent.get(), INFINITE);
		T item;
		{
			std::lock_guard<std::mutex> guardScope(guard);
			if (futures.empty())
			{
				throw std::runtime_error("empty queue");
			}
			item = std::move(futures.front());
			futures.erase(futures.begin());
			if (futures.empty())
			{
				ResetEvent(producedevent.get());
			}
		}
		return std::move(item);
	}

	template<typename Item>
	void push_back(Item&& item)
	{
		std::lock_guard<std::mutex> guardScope(guard);
		futures.push_back(std::forward<Item>(item));
		SetEvent(producedevent.get());
	}

	void join()
	{
		if (producer.joinable())
		{
			{
				std::lock_guard<std::mutex> guardScope(guard);
				SetEvent(exitevent.get());
				if (cancel)
				{
					cancel();
				}
			}
			producer.join();
		}
	}

	HANDLE getexitevent()
	{
		return exitevent.get();
	}

	HANDLE getproducedevent()
	{
		return producedevent.get();
	}

	void lock()
	{
		guard.lock();
	}

	void unlock()
	{
		guard.unlock();
	}

private:
	producerqueue();
	producerqueue(const producerqueue&);
	producerqueue& operator=(const producerqueue&);

	std::function<void()> cancel;

	std::mutex guard;
	std::vector<T> futures;
	lib::wr::unique_event producedevent;
	lib::wr::unique_event exitevent;
	std::thread producer;
};


class monitor_readers
{
public:
	struct readerstate
	{
		DWORD oldstate;
		DWORD newstate;
		DWORD changesinstate;
		std::vector<BYTE> atr;
		std::wstring reader;
	};

	typedef std::vector<readerstate> readersstatus;
	typedef producerqueue<readersstatus> output;

	monitor_readers()
		: updates(
			[&]() -> void
			{
				if (this->context)
				{
					SCardCancel(this->context);
				}
			},
			[&]() -> void
			{
				this->monitor();
			}
		)
	{
	}

private:

	void monitor()
	{
		HANDLE waitfor[2] = {SCardAccessStartedEvent(), updates.getexitevent()};
		ON_UNWIND_AUTO([] {SCardReleaseStartedEvent();});

		unique_winerror winerror;

		for (;;)
		{
			winerror = monitor_smartcard_readers(
				[&](SCARDCONTEXT context)
				{
					std::lock_guard<output> guardsharedcontext(this->updates);
					this->context = context;
				},
				[&]()
				{
					std::lock_guard<output> guardsharedcontext(this->updates);
					this->context = NULL;
				},
				[&]() -> bool
				{
					if (WAIT_OBJECT_0 != WaitForMultipleObjects(lib::rng::size(waitfor), waitfor, FALSE, INFINITE))
					{
						// monitor_smardcard_readers will return SCARD_E_CANCELLED
						return false;
					}
					return true;
				},
				[&](lib::rng::range<SCARD_READERSTATE*> readersrange)
				{
					readersstatus update;
					for (auto& state : readersrange)
					{
						readerstate item;
						item.newstate = state.dwEventState;
						item.oldstate = state.dwCurrentState;
						item.changesinstate = (
							(state.dwCurrentState ^ state.dwEventState) & 
							std::numeric_limits<unsigned short>::max()
						);
						item.reader = state.szReader;
						item.atr.assign(state.rgbAtr, state.rgbAtr + state.cbAtr);
						update.push_back(item);
					}
					this->updates.push_back(update);
				}
			);
			winerror.suppress();
		}
	}

	SCARDCONTEXT context;
public:
	output updates;
};

class monitor_certificates
{
public:
	struct cardstate
	{
		CardWithProvider state;
		KeyWithCertificateVector certificates;
	};

	struct readerstate
	{
		readerstate()
			: oldstate(SCARD_STATE_UNAWARE)
			, newstate(SCARD_STATE_UNAWARE)
			, changesinstate(SCARD_STATE_UNAWARE)
		{}

		readerstate(readerstate&& other)
			: oldstate(other.oldstate)
			, newstate(other.newstate)
			, changesinstate(other.changesinstate)
			, atr(std::move(other.atr))
			, reader(std::move(other.reader))
			, card(std::move(other.card))
		{
		}

		readerstate& operator=(readerstate other)
		{
			using std::swap;
			swap(oldstate, other.oldstate);
			swap(newstate, other.newstate);
			swap(changesinstate, other.changesinstate);
			swap(atr, other.atr);
			swap(reader, other.reader);
			swap(card, other.card);

			return *this;
		}

		DWORD oldstate;
		DWORD newstate;
		DWORD changesinstate;
		std::vector<BYTE> atr;
		std::wstring reader;
		std::future<cardstate> card;

	private:
		readerstate(const readerstate&);
	};

	typedef std::vector<readerstate> readersstatus;
	typedef producerqueue<readersstatus> output;

	monitor_certificates()
		: updates(
			[&]() -> void
			{
				if (this->context)
				{
					SCardCancel(this->context);
				}
			},
			[&]() -> void
			{
				this->monitor();
			}
		)
	{
	}

private:

	void monitor()
	{
		HANDLE waitfor[2] = {SCardAccessStartedEvent(), updates.getexitevent()};
		ON_UNWIND_AUTO([] {SCardReleaseStartedEvent();});

		unique_winerror winerror;

		for (;;)
		{
			winerror = monitor_smartcard_readers(
				[&](SCARDCONTEXT context)
				{
					std::lock_guard<output> guardsharedcontext(this->updates);
					this->context = context;
				},
				[&]()
				{
					std::lock_guard<output> guardsharedcontext(this->updates);
					this->context = NULL;
				},
				[&]() -> bool
				{
					if (WAIT_OBJECT_0 != WaitForMultipleObjects(lib::rng::size(waitfor), waitfor, FALSE, INFINITE))
					{
						// monitor_smardcard_readers will return SCARD_E_CANCELLED
						return false;
					}
					return true;
				},
				[&](lib::rng::range<SCARD_READERSTATE*> readersrange)
				{
					readersstatus update;
					for (auto& state : readersrange)
					{
						readerstate item;

						item.newstate = state.dwEventState;
						item.oldstate = state.dwCurrentState;
						item.reader = state.szReader;
						item.changesinstate = (
							(state.dwCurrentState ^ state.dwEventState) & 
							std::numeric_limits<unsigned short>::max()
						);
						item.atr.assign(state.rgbAtr, state.rgbAtr + state.cbAtr);

						if (item.oldstate == SCARD_STATE_UNAWARE ||
							((item.newstate & SCARD_STATE_PRESENT) == SCARD_STATE_PRESENT &&
							  item.changesinstate != SCARD_STATE_INUSE &&
							  item.changesinstate != SCARD_STATE_UNPOWERED &&
							  !(item.newstate & (SCARD_STATE_UNPOWERED | SCARD_STATE_EMPTY | SCARD_STATE_IGNORE | SCARD_STATE_UNKNOWN | SCARD_STATE_UNAVAILABLE | SCARD_STATE_MUTE)) &&
							  !item.atr.empty()))
						{
							// we have not seen this reader before or all of:
							// card present
							// not only flipped INUSE
							// not only flipped UNPOWERED
							// not UNPOWERED EMPTY UNKNOWN UNAVAILABLE MUTE
							// has atr
							//
							// try to read the card

							item.card = std::async(
								std::launch::async,
								[](const std::vector<BYTE>& atr) -> cardstate
								{
									unique_winerror winerror;
									cardstate output;

									std::tie(winerror, output.state) = smartcard_name_and_provider(lib::rng::make_range_raw(atr));
									winerror.throw_if("failed to read card name and provider");

									std::tie(winerror, output.certificates) = smartcard_certificates(output.state.kspname);
									winerror.throw_if("failed to read certificates");

									return std::move(output);
								},
								item.atr
							);
						}

						update.emplace_back(std::move(item));
					}
					this->updates.push_back(std::move(update));
				}
			);
			winerror.suppress();
		}
	}

	SCARDCONTEXT context;
public:
	output updates;
};

}
