#pragma once

#include "../memory/pe.h"

using FindWindowA_fn = HWND( __stdcall* )( LPCSTR, LPCSTR );
using SetWindowLongW_fn = LONG( __stdcall* )( HWND, int, LONG );
using CallWindowProcW_fn = LONG( __stdcall* )( WNDPROC, HWND, UINT, WPARAM, LPARAM );
using MultiByteToWideChar_fn = int( __stdcall* )( UINT, DWORD, LPCCH, int, LPWSTR, int );
using WideCharToMultiByte_fn = int( __stdcall* )( UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL );

struct winapi {

	// modules 

	struct {

		address user32;
		address kernel32;

	} m_dlls;

	// functions 

	FindWindowA_fn find_window_a;
	SetWindowLongW_fn set_window_long_w;
	CallWindowProcW_fn call_window_proc_w;
	MultiByteToWideChar_fn multi_byte_to_wide_char;
	WideCharToMultiByte_fn wide_char_to_multi_byte;

	bool setup( ) {

		m_dlls.user32 = g_pe.get( XOR( "user32.dll" ) );
		if ( !m_dlls.user32 )
			return false;

		m_dlls.kernel32 = g_pe.get( XOR( "kernel32.dll" ) );
		if ( !m_dlls.kernel32 )
			return false;

		find_window_a = g_pe.export_fn( m_dlls.user32, g_hash.get( XOR( "FindWindowA" ) ) ).as< FindWindowA_fn >( );
		if ( !find_window_a )
			return false;

		set_window_long_w = g_pe.export_fn( m_dlls.user32, g_hash.get( XOR( "SetWindowLongW" ) ) ).as< SetWindowLongW_fn >( );
		if ( !set_window_long_w )
			return false;

		call_window_proc_w = g_pe.export_fn( m_dlls.user32, g_hash.get( XOR( "CallWindowProcW" ) ) ).as< CallWindowProcW_fn >( );
		if ( !call_window_proc_w )
			return false;

		multi_byte_to_wide_char = g_pe.export_fn( m_dlls.kernel32, g_hash.get( XOR( "MultiByteToWideChar" ) ) ).as< MultiByteToWideChar_fn >( );
		if ( !multi_byte_to_wide_char )
			return false;

		wide_char_to_multi_byte = g_pe.export_fn( m_dlls.kernel32, g_hash.get( XOR( "WideCharToMultiByte" ) ) ).as< WideCharToMultiByte_fn >( );
		if ( !wide_char_to_multi_byte )
			return false;

		return true;

	}

};

inline winapi g_winapi;