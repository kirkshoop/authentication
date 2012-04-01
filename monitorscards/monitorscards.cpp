// monitorscards.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\win32project1\scard_monitor.h"

void unique_error_report_initiated(HRESULT value, unique_hresult_def::tag&&)
{
	static HRESULT anchor;
	anchor = value;
}

void unique_error_report_reset(HRESULT value, unique_hresult_def::tag&&)
{
	static HRESULT anchor;
	anchor = value;
}

void unique_error_report_initiated(DWORD value, unique_winerror_def::tag&&)
{
	static DWORD anchor;
	anchor = value;
}

void unique_error_report_reset(DWORD value, unique_winerror_def::tag&&)
{
	static DWORD anchor;
	anchor = value;
}

template<typename Certificate>
void printCertificates(lib::rng::range<Certificate> certificates)
{
	for (auto& key : certificates)
	{
		unique_winerror winerror;

		PCCERT_CONTEXT certcontext = CertCreateCertificateContext(
			X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
			&key.cert[0],
			key.cert.size()
		);
		winerror = make_winerror_if(!certcontext);

		if (!winerror)
		{
			std::wcout << L"could not get cert context" << std::endl; 
			continue;
		}

		DWORD sizesubject = 0;
		std::wstring subjectname;
		for (bool getsize = true; ; getsize = false)
		{
			sizesubject = CertGetNameString(
				certcontext,
				CERT_NAME_FRIENDLY_DISPLAY_TYPE,
				0,
				NULL,
				getsize ? nullptr : &subjectname[0],
				sizesubject
			);
			if (sizesubject == 1)
			{
				std::wcout << L"could not get subject name" << std::endl; 
				break;
			}
			if (getsize)
			{
				subjectname.resize(sizesubject - 1);
			}
			else
			{
				std::wcout << L"key name: " << key.key.c_str() << L" subject name: " << subjectname.c_str() << std::endl; 
				break;
			}
		}
	}
}

template<typename Stream>
Stream& printSCardState(Stream& stream, DWORD state)
{
	stream 
		<< ((state == SCARD_STATE_UNAWARE)  ? L" SCARD_STATE_UNAWARE" : L"")
		<< ((state & SCARD_STATE_PRESENT)  ? L" SCARD_STATE_PRESENT" : L"")
		<< ((state & SCARD_STATE_ATRMATCH)  ? L" SCARD_STATE_ATRMATCH" : L"")
		<< ((state & SCARD_STATE_CHANGED)  ? L" SCARD_STATE_CHANGED" : L"")
		<< ((state & SCARD_STATE_EMPTY)  ? L" SCARD_STATE_EMPTY" : L"")
		<< ((state & SCARD_STATE_EXCLUSIVE)  ? L" SCARD_STATE_EXCLUSIVE" : L"")
		<< ((state & SCARD_STATE_IGNORE)  ? L" SCARD_STATE_IGNORE" : L"")
		<< ((state & SCARD_STATE_INUSE)  ? L" SCARD_STATE_INUSE" : L"")
		<< ((state & SCARD_STATE_MUTE)  ? L" SCARD_STATE_MUTE" : L"")
		<< ((state & SCARD_STATE_UNAVAILABLE)  ? L" SCARD_STATE_UNAVAILABLE" : L"")
		<< ((state & SCARD_STATE_UNKNOWN)  ? L" SCARD_STATE_UNKNOWN" : L"")
		<< ((state & SCARD_STATE_UNPOWERED)  ? L" SCARD_STATE_UNPOWERED" : L"")
	;
	return stream;
}

int wmain(int argc, WCHAR* argv[])
{
	unique_winerror winerror;

#if 0
	LARGE_INTEGER frequency;
	(VOID)QueryPerformanceFrequency(&frequency);

	auto secBetween = [&](const LARGE_INTEGER& begin, const LARGE_INTEGER& end) -> double
	{
		return double(end.QuadPart - begin.QuadPart) / frequency.QuadPart;
	};
#endif

#if 0
	for (;;)
	{
		SCARDCONTEXT context = NULL;

		HANDLE waitfor[] = {SCardAccessStartedEvent()};
		ON_UNWIND_AUTO([] {SCardReleaseStartedEvent();});

		winerror = smart_card::monitor_smartcard_readers(
			[&](SCARDCONTEXT context)
			{
				context = context;
			},
			[&]()
			{
				context = NULL;
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
				for (auto& state : readersrange)
				{
					auto stateChanges = (state.dwCurrentState ^ state.dwEventState) & std::numeric_limits<unsigned short>::max();
					std::wcout 
						<< L"nothread - "
						<< state.szReader
						<< L" changes: " << std::hex << std::showbase << stateChanges
						<< L"["
					;
					printSCardState(std::wcout, stateChanges)
						<< L"] state: " << std::hex << std::showbase << state.dwEventState
						<< L"["
					;
					printSCardState(std::wcout, state.dwEventState)
						<< L"]" 
						<< std::endl
					; 

					if (state.dwCurrentState != SCARD_STATE_UNAWARE && 
						((state.dwEventState & SCARD_STATE_PRESENT) != SCARD_STATE_PRESENT ||
						  stateChanges == SCARD_STATE_INUSE ||
						  stateChanges == SCARD_STATE_UNPOWERED ||
						  (state.dwEventState & (SCARD_STATE_UNPOWERED | SCARD_STATE_EMPTY | SCARD_STATE_IGNORE | SCARD_STATE_UNKNOWN | SCARD_STATE_UNAVAILABLE | SCARD_STATE_MUTE)) ||
						  state.cbAtr == 0))
					{
						// we have seen this reader before and one of:
						// no card
						// only flipped INUSE
						// only flipped UNPOWERED
						// UNPOWERED EMPTY UNKNOWN UNAVAILABLE MUTE
						// no atr
						//
						// don't try to read the card
						continue;
					}

					CardWithProvider card;
					std::tie(winerror, card) = smart_card::smartcard_name_and_provider(lib::rng::make_range_raw(state.rgbAtr));
					if (!winerror)
					{
						continue;
					}

					KeyWithCertificateVector certificates;
					std::tie(winerror, certificates) = smart_card::smartcard_certificates(card.kspname);
					if (!winerror)
					{
						continue;
					}

					std::wcout << L"nothread -"
						<< L" kspname: " << card.kspname.c_str()
						<< std::endl; 

					printCertificates(lib::rng::make_range_raw(certificates));
				}
			}
		);
		winerror.suppress();
	}
#endif

	smart_card::monitor_certificates monitor;

	for(;;)
	{
		HANDLE waitfor[] = {monitor.updates.getproducedevent()};
		if (WAIT_OBJECT_0 == WaitForMultipleObjects(lib::rng::size(waitfor), waitfor, FALSE, INFINITE))
		{
			auto update = monitor.updates.pop();

			for (auto& state : update)
			{
				unique_winerror winerror;

				std::wcout 
					<< L"Monitor #3 - "
					<< state.reader.c_str()
					<< L" changes: " << std::hex << std::showbase << state.changesinstate
					<< L"["
				;
				printSCardState(std::wcout, state.changesinstate)
					<< L"] state: " << std::hex << std::showbase << state.newstate
					<< L"["
				;
				printSCardState(std::wcout, state.newstate)
					<< L"]" 
					<< std::endl
				; 

				if (!state.card.valid())
				{
					continue;
				}

				auto card = state.card.get();

				std::wcout << L"Monitor #3 -"
					<< L" kspname: " << card.state.kspname.c_str()
					<< std::endl; 

				printCertificates(lib::rng::make_range_raw(card.certificates));
			}
			continue;
		}
	}
	return 0;
}

