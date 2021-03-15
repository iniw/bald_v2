#include "../hooked.h"

void __fastcall hooked::paint( void* ecx, void* edx, paint_mode mode ) {

	static auto o_paint = g_detour.get< decltype( &paint ) >( "CEngineVGui::Paint" );

	if ( mode & paint_uipanels ) {

		g_interfaces.m_surface->start_drawing( );

		g_visuals.paint( );

		g_legitbot.paint( );

		g_interfaces.m_surface->finish_drawing( );

	}

	return o_paint( ecx, edx, mode );

}