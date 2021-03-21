#pragma once

#include "../memory/pe.h"

using FindWindowA_fn = HWND( __stdcall* )( LPCSTR, LPCSTR );
using SetWindowLongW_fn = LONG( __stdcall* )( HWND, int, LONG );
using CallWindowProcW_fn = LONG( __stdcall* )( WNDPROC, HWND, UINT, WPARAM, LPARAM );
using MultiByteToWideChar_fn = int( __stdcall* )( UINT, DWORD, LPCCH, int, LPWSTR, int );
using WideCharToMultiByte_fn = int( __stdcall* )( UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL );
using URLDownloadToFileA_fn = HRESULT( __stdcall* )( LPUNKNOWN, LPCSTR, LPCSTR, DWORD, LPBINDSTATUSCALLBACK );
using AddFontResourceA_fn = int( __stdcall* )( LPCSTR );
using GetUserNameA_fn = BOOL( __stdcall* )( LPSTR, LPDWORD );
using SHGetFolderPathA_fn = HRESULT( __stdcall* )( HWND, int, HANDLE, DWORD, LPSTR );
using CreateDirectoryA_fn = BOOL( __stdcall* )( LPCSTR, LPSECURITY_ATTRIBUTES );
using PathAppendA_fn = BOOL( __stdcall* )( LPSTR, LPCSTR );

struct winapi {

	// modules 

	struct {

		address user32;
		address kernel32;
		address gdi32;
		address urlmon;
		address shell32;
		address shlwapi;

	} m_dlls;

	// functions 

	FindWindowA_fn         find_window;
	SetWindowLongW_fn      set_window_long;
	CallWindowProcW_fn     call_window_proc;
	MultiByteToWideChar_fn multi_byte_to_wide_char;
	WideCharToMultiByte_fn wide_char_to_multi_byte;
	CreateDirectoryA_fn    create_directory;
	URLDownloadToFileA_fn  url_download_to_file;
	AddFontResourceA_fn    add_font_resource;
	SHGetFolderPathA_fn    sh_get_folder_path;
	PathAppendA_fn         path_append;

	bool setup( );

};

inline winapi g_winapi;