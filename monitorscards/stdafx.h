// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
// Windows Header Files:
#include <windows.h>
#include <Unknwn.h>
#include <winscard.h>
#include <ncrypt.h>
#include <Wincrypt.h>
#include <credentialprovider.h>

// TODO: reference additional headers your program requires here
#include <type_traits>
#include <algorithm>
#include <new>
#include <memory>
#include <utility>
#include <limits>
#include <iterator>
#include <thread>
#include <future>
#include <mutex>
#include <vector>

#include <iostream>
#include <iomanip>

template<typename Functor, typename InterfaceTag, typename ObjectTag>
HRESULT com_function_contract_hresult(Functor&& functor, InterfaceTag&&, ObjectTag&&);

#define LIBRARIES_NAMESPACE nslib
#include <libraries.h>
namespace lib=LIBRARIES_NAMESPACE;

template<typename Functor, typename InterfaceTag, typename ObjectTag>
HRESULT com_function_contract_hresult(Functor&& functor, InterfaceTag&&, ObjectTag&&)
{
	HRESULT hr = E_UNEXPECTED;
	FAIL_FAST_ON_THROW(
		[&]
		{
			try
			{
				hr = std::forward<Functor>(functor)().suppress().release();
			}
			catch(const unique_hresult::exception& e)
			{
				hr = e.get();
			}
			catch(const unique_winerror::exception& e)
			{
				hr = HRESULT_FROM_WIN32(e.get());
			}
			catch (const std::bad_alloc& )
			{
				hr = E_OUTOFMEMORY;
			}
		}
	);
	return hr;
}



// TODO: reference additional headers your program requires here
