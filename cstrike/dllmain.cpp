#include "cstrike.h"

BOOL APIENTRY DllMain( HMODULE module_handle, DWORD call_reason, LPVOID reserved ) {

	if ( call_reason == DLL_PROCESS_ATTACH ) {

		DisableThreadLibraryCalls( module_handle );

		return g_utils.create_thread( g_cstrike.setup, module_handle );

	} else if ( call_reason == DLL_PROCESS_DETACH ) {

		g_cstrike.unload( EXIT_SUCCESS );

		return TRUE;

	}

	return FALSE;

}