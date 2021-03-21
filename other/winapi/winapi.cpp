#include "winapi.h"

bool winapi::setup( ) {

	if ( m_dlls.user32 = g_pe.get( XOR( "user32.dll" ) ); !m_dlls.user32 )
		return false;

	if ( m_dlls.kernel32 = g_pe.get( XOR( "kernel32.dll" ) ); !m_dlls.kernel32 )
		return false;

	if ( m_dlls.gdi32 = g_pe.get( XOR( "gdi32.dll" ) ); !m_dlls.gdi32 )
		return false;

	if ( m_dlls.urlmon = g_pe.get( XOR( "urlmon.dll" ) ); !m_dlls.urlmon )
		return false;

	if ( m_dlls.shell32 = g_pe.get( XOR( "shell32.dll" ) ); !m_dlls.shell32 )
		return false;

	if ( m_dlls.shlwapi = g_pe.get( XOR( "shlwapi.dll" ) ); !m_dlls.shlwapi )
		return false;

	find_window = g_pe.export_fn( m_dlls.user32, g_hash.get( XOR( "FindWindowA" ) ) ).as< FindWindowA_fn >( );
	if ( !find_window )
		return false;

	set_window_long = g_pe.export_fn( m_dlls.user32, g_hash.get( XOR( "SetWindowLongW" ) ) ).as< SetWindowLongW_fn >( );
	if ( !set_window_long )
		return false;

	multi_byte_to_wide_char = g_pe.export_fn( m_dlls.kernel32, g_hash.get( XOR( "MultiByteToWideChar" ) ) ).as< MultiByteToWideChar_fn >( );
	if ( !multi_byte_to_wide_char )
		return false;

	wide_char_to_multi_byte = g_pe.export_fn( m_dlls.kernel32, g_hash.get( XOR( "WideCharToMultiByte" ) ) ).as< WideCharToMultiByte_fn >( );
	if ( !wide_char_to_multi_byte )
		return false;

	create_directory = g_pe.export_fn( m_dlls.kernel32, g_hash.get( XOR( "CreateDirectoryA" ) ) ).as< CreateDirectoryA_fn >( );
	if ( !create_directory )
		return false;

	call_window_proc = g_pe.export_fn( m_dlls.user32, g_hash.get( XOR( "CallWindowProcW" ) ) ).as< CallWindowProcW_fn >( );
	if ( !call_window_proc )
		return false;

	url_download_to_file = g_pe.export_fn( m_dlls.urlmon, g_hash.get( XOR( "URLDownloadToFileA" ) ) ).as< URLDownloadToFileA_fn >( );
	if ( !url_download_to_file )
		return false;

	add_font_resource = g_pe.export_fn( m_dlls.gdi32, g_hash.get( XOR( "AddFontResourceA" ) ) ).as< AddFontResourceA_fn >( );
	if ( !add_font_resource )
		return false;

	sh_get_folder_path = g_pe.export_fn( m_dlls.shell32, g_hash.get( XOR( "SHGetFolderPathA" ) ) ).as< SHGetFolderPathA_fn >( );
	if ( !sh_get_folder_path )
		return false;

	path_append = g_pe.export_fn( m_dlls.shlwapi, g_hash.get( XOR( "PathAppendA" ) ) ).as< PathAppendA_fn >( );
	if ( !path_append )
		return false;

	g_console.log( XOR( "imported winapi functions" ) );

	return true;

}
