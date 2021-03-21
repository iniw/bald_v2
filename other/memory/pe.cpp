#include "pe.h"

#include <algorithm>

bool pe::setup( ) {

	const auto peb = reinterpret_cast< _PEB* >( __readfsdword( 0x30 ) );
	if ( !peb )
		return false;

	const auto list = &peb->Ldr->InMemoryOrderModuleList;

	for ( auto it = list->Flink; it != list; it = it->Flink ) {

		const auto ldr_entry = CONTAINING_RECORD( it, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks );
		if ( !ldr_entry )
			continue;

		const auto base_dll_name = reinterpret_cast< UNICODE_STRING* >( &ldr_entry->Reserved4[ 0 ] );

		// not a good way to do this, causes a warning as well
		// but winapi is forcing my hand
		const auto wide_name = std::wstring( base_dll_name->Buffer, base_dll_name->Length >> 1 );
		auto name = std::string( wide_name.begin( ), wide_name.end( ) );

		std::transform( name.begin( ), name.end( ), name.begin( ), ::tolower );

		m_loaded_modules.insert_or_assign( name, address( ldr_entry->DllBase ) );

	}

	g_console.log( XOR( "found %d modules" ), m_loaded_modules.size( ) );

	return true;

}

address pe::export_fn( const address base, const size_t fn_hash, const bool in_memory ) {

	const auto rva_2_offset = [ ]( const uint32_t rva, PIMAGE_NT_HEADERS nt_headers, const bool in_memory = false ) {

		if ( !rva || !in_memory )
			return static_cast< int32_t >( rva );

		auto sec = IMAGE_FIRST_SECTION( nt_headers );
		for ( size_t i = 0; i < nt_headers->FileHeader.NumberOfSections; i++ ) {

			if ( rva >= sec->VirtualAddress && rva < sec->VirtualAddress + sec->Misc.VirtualSize )
				break;

			sec++;

		}

		return static_cast< int32_t >( rva - sec->VirtualAddress + sec->PointerToRawData );

	};

	const auto dos_headers = base.as< PIMAGE_DOS_HEADER >( );
	if ( dos_headers->e_magic != IMAGE_DOS_SIGNATURE )
		return address( );

	const auto nt_headers = base.add( dos_headers->e_lfanew ).as< PIMAGE_NT_HEADERS >( );
	if ( nt_headers->Signature != IMAGE_NT_SIGNATURE )
		return address( );

	const auto exports = reinterpret_cast< IMAGE_EXPORT_DIRECTORY* >( rva_2_offset( base.add( nt_headers->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress ), nt_headers, in_memory ) );

	const auto names = base.add( rva_2_offset( exports->AddressOfNames, nt_headers, in_memory ) ).as< uint32_t* >( );
	if ( !names )
		return address( );

	auto ordinal_index = static_cast< uint32_t >( -1 );

	// go thru all exported functions until we find our export
	for ( uint32_t i = 0; i < exports->NumberOfFunctions; i++ ) {

		auto function_name = base.add( rva_2_offset( names[ i ], nt_headers, in_memory ) ).as< const char* >( );

		// it is what it is
		if ( g_hash.get( function_name ) == fn_hash ) {

			ordinal_index = i;
			break;

		}

	}

	if ( ordinal_index > exports->NumberOfFunctions ) {

		g_console.log( XOR( "failed to export function!" ) );
		return address( );

	}

	const auto ordinals = base.add( rva_2_offset( exports->AddressOfNameOrdinals, nt_headers, in_memory ) ).as< uint16_t* >( );
	const auto addresses = base.add( rva_2_offset( exports->AddressOfFunctions, nt_headers, in_memory ) ).as< uint32_t* >( );

	return base.add( rva_2_offset( addresses[ ordinals[ ordinal_index ] ], nt_headers, in_memory ) );

}