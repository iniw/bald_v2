#include "file_system.h"

#include <Shlobj.h>
#include "../winapi/winapi.h"

bool file_system::setup( ) {

	if ( !SUCCEEDED( g_winapi.sh_get_folder_path( 0, CSIDL_MYDOCUMENTS, 0, SHGFP_TYPE_CURRENT, m_main_path ) ) ) {

		g_console.log( log_error, XOR( "failed to find documents path" ) );
		return false;

	}

	g_winapi.path_append( m_main_path, XOR( "bald_v2" ) );

	strcpy_s( m_fonts_path, m_main_path );
	strcpy_s( m_configs_path, m_main_path );
	strcpy_s( m_logs_path, m_main_path );

	g_winapi.path_append( m_fonts_path, XOR( "fonts" ) );
	g_winapi.path_append( m_configs_path, XOR( "configs" ) );
	g_winapi.path_append( m_logs_path, XOR( "logs" ) );

	g_winapi.create_directory( m_main_path, 0 );
	g_winapi.create_directory( m_fonts_path, 0 );
	g_winapi.create_directory( m_configs_path, 0 );
	g_winapi.create_directory( m_logs_path, 0 );

	return true;

}
