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

	inline address get( const std::string& name ) {

		return m_loaded_modules[ name ];

	}

	// general pourpose modules used by the entire cheat

	struct {

		address client;
		address engine;
		address server;
		address gameoverlayrenderer;
		address vgui2;
		address vguimatsurface;
		address studiorender;
		address localize;
		address datacache;
		address materialsystem;
		address vstdlib;
		address vphysics;
		address user32;
		address kernel32;
		address gdi32;
		address urlmon;
		address shell32;
		address shlwapi;

	} m_dlls;

private:

	std::unordered_map< std::string, address > m_loaded_modules;

};

inline pe g_pe;