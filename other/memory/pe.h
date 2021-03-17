#pragma once

#include <Windows.h>
#include <intrin.h>
#include <winternl.h>
#include <TlHelp32.h>

#include <unordered_map>

#include "../hash/hash.h"
#include "../console/console.h"
#include "address.h"

struct pe {

	bool setup( );

	// get export address
	address export_fn( const address base, const size_t fn_hash, const bool in_memory = false );

	address get( const std::string& name ) {

		return m_loaded_modules[ name ];

	}

	std::unordered_map< std::string, address > m_loaded_modules;

};

inline pe g_pe;