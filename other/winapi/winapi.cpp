#include "winapi.h"

bool winapi::setup( ) {

	IMPORT( find_window, FindWindowA, g_pe.m_dlls.user32 );
	IMPORT( set_window_long, SetWindowLongW, g_pe.m_dlls.user32 );
	IMPORT( call_window_proc, CallWindowProcW, g_pe.m_dlls.user32 );

	IMPORT( multi_byte_to_wide_char, MultiByteToWideChar, g_pe.m_dlls.kernel32 );
	IMPORT( wide_char_to_multi_byte, WideCharToMultiByte, g_pe.m_dlls.kernel32 );
	IMPORT( create_directory, CreateDirectoryA, g_pe.m_dlls.kernel32 );

	IMPORT( url_download_to_file, URLDownloadToFileA, g_pe.m_dlls.urlmon );

	IMPORT( add_font_resource, AddFontResourceA, g_pe.m_dlls.gdi32 );

	IMPORT( sh_get_folder_path, SHGetFolderPathA, g_pe.m_dlls.shell32 );

	IMPORT( path_append, PathAppendA, g_pe.m_dlls.shlwapi );

	g_console.log( log_completion, XOR( "setup winapi" ) );

	return true;

}
