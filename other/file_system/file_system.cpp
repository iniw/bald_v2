#include "file_system.h"

#include <Shlobj.h>
#include "../winapi/winapi.h"


bool file_system::setup( ) {

	m_main_path.resize( MAX_PATH + 1 );
	m_fonts_path.resize( MAX_PATH + 1 );
	m_configs_path.resize( MAX_PATH + 1 );

	if ( !SUCCEEDED( g_winapi.sh_get_folder_path( 0, CSIDL_MYDOCUMENTS, 0, SHGFP_TYPE_CURRENT, m_main_path.data( ) ) ) )
		return false;

	g_winapi.path_append( m_main_path.data( ), XOR( "bald_v2" ) );

	m_fonts_path = m_configs_path = m_main_path;

	g_winapi.path_append( m_fonts_path.data( ), XOR( "fonts" ) );

	g_winapi.path_append( m_configs_path.data( ), XOR( "configs" ) );

	g_winapi.create_directory( m_main_path.data( ), 0 );

	g_winapi.create_directory( m_fonts_path.data( ), 0 );

	g_winapi.create_directory( m_configs_path.data( ), 0 );

	return true;

}
