#include "../hooked.h"

int __fastcall hooked::list_leaves_in_box( void* ecx, void* edx, const vec_3& mins, const vec_3& maxs, unsigned short* list, int list_max ) {

	static auto o_list_leaves_in_box = g_detour.get< decltype( &list_leaves_in_box ) >( XOR( "CEngineBSPTree::ListLeavesInBox" ) );

	stack stack( _AddressOfReturnAddress( ) );

	if ( stack.return_address( ) != g_signatures.m_insert_into_tree.add( 0x5 ) )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	auto info = stack.address_of_return_address( ).add( 0x14 ).to< rendereable_info* >( );
	if ( !info )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	auto rendereable = info->m_rendereable;
	if ( !rendereable )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	auto entity = rendereable->get_client_unknown( )->get_base_entity( );
	if ( !entity || !entity->is_player( ) || !g_cstrike.m_local->is_enemy( entity ) )
		return o_list_leaves_in_box( ecx, edx, mins, maxs, list, list_max );

	info->m_flags &= ~rendereable_flags_force_opaque_pass;
	info->m_flags_2 |= rendereable_flags_bounds_always_recompute;

	static vec_3 map_min( -16'384.f, -16'384.f, -16'384.f );
	static vec_3 map_max( 16'384.f, 16'384.f, 16'384.f );

	return o_list_leaves_in_box( ecx, edx, map_min, map_max, list, list_max );

}