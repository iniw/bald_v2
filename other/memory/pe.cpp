#include "pe.h"

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
		const auto name = std::string( wide_name.begin( ), wide_name.end( ) );

		m_loaded_modules.insert_or_assign( name, address( ldr_entry->DllBase ) );

		//g_console.log( "found module %s -> 0x%x" , name.data( ) , m_loaded_modules[ g_hash.get( name ) ] );

	}

	g_console.log( "found %d modules", m_loaded_modules.size( ) );

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

	const auto dos_headers = reinterpret_cast< PIMAGE_DOS_HEADER >( base.as< size_t >( ) );
	if ( dos_headers->e_magic != IMAGE_DOS_SIGNATURE )
		return address( );

	const auto nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( base.as< size_t >( ) + dos_headers->e_lfanew );
	if ( nt_headers->Signature != IMAGE_NT_SIGNATURE )
		return address( );

	const auto exports = reinterpret_cast< IMAGE_EXPORT_DIRECTORY* >(
		rva_2_offset( base.as< size_t >( ) + nt_headers->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress,
		nt_headers, in_memory ) );

	const auto names = reinterpret_cast< uint32_t* >( base.as< size_t >( ) + rva_2_offset( exports->AddressOfNames, nt_headers, in_memory ) );
	if ( !names )
		return address( );

	auto ordinal_index = static_cast< uint32_t >( -1 );

	// go thru all exported functions until we find our export
	for ( uint32_t i = 0; i < exports->NumberOfFunctions; i++ ) {

		const auto function_name = reinterpret_cast< const char* >( base.as< size_t >( ) + rva_2_offset( names[ i ], nt_headers, in_memory ) );

		// it is what it is
		if ( g_hash.get( function_name ) == fn_hash ) {

			ordinal_index = i;
			break;

		}

	}

	if ( ordinal_index > exports->NumberOfFunctions )
		return address( );

	const auto ordinals = reinterpret_cast< uint16_t* >( base.as< uintptr_t >( ) + rva_2_offset( exports->AddressOfNameOrdinals, nt_headers, in_memory ) );
	const auto addresses = reinterpret_cast< uint32_t* >( base.as< uintptr_t >( ) + rva_2_offset( exports->AddressOfFunctions, nt_headers, in_memory ) );

	return address( base.as< uintptr_t >( ) + rva_2_offset( addresses[ ordinals[ ordinal_index ] ], nt_headers, in_memory ) );

}