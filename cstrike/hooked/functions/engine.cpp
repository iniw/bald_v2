#include "../hooked.h"

bool __fastcall hooks::is_hltv( void* ecx, void* edx ) {

    static auto o_is_hltv = g_detour.get< decltype( &is_hltv ) >( XOR( "CEngineClient::IsHLTV" ) );

    stack stack( _AddressOfReturnAddress( ) );

    if ( stack.return_address( ) == g_signatures.m_accumulate_layers )
        return true;

    return o_is_hltv( ecx, edx );

}