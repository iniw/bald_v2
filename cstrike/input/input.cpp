#include "input.h"

bool input::setup( ) {

	m_original_wnd_proc = reinterpret_cast< WNDPROC >( g_winapi.set_window_long( g_cstrike.m_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( wnd_proc ) ) );
	if ( !m_original_wnd_proc )
		return false;

	g_console.log( log_completion, XOR( "setup wndproc" ) );

	return true;

}

void input::unload( ) {

	if ( !m_original_wnd_proc )
		return;

	g_winapi.set_window_long( g_cstrike.m_window, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( m_original_wnd_proc ) );

}

void input::think( UINT message, WPARAM w_param, LPARAM l_param ) {

	size_t key;
	key_state state;

	switch ( message ) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			key = w_param;
			state = down;
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			key = w_param;
			state = up;
			break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			key = VK_LBUTTON;
			state = message == WM_LBUTTONUP ? up : down;
			break;
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			key = VK_RBUTTON;
			state = message == WM_RBUTTONUP ? up : down;
			break;
		default:
			return;
	}

	if ( m_key_states[ key ].m_state == up && state == down ) {

		m_key_states[ key ].m_framecount = g_interfaces.m_globals->m_framecount + 1;
		m_key_states[ key ].m_state = toggled;

	} else {

		m_key_states[ key ].m_state = state;

	}

}

long __stdcall input::wnd_proc( HWND window, UINT message, WPARAM w_param, LPARAM l_param ) {

	g_input.think( message, w_param, l_param );

	return g_winapi.call_window_proc( g_input.m_original_wnd_proc, window, message, w_param, l_param );

}