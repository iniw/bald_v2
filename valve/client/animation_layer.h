#pragma once

#include "../studio.h"

struct animation_layer {

	byte pad0[ 0x8 ]; // 0
	studio_hdr* m_dispatched_studio_hdr; // 8
	int m_dispatched_src; // 12
	int m_dispatched_dst; // 16
	byte pad1[ 0x4 ]; // 20
	int m_sequence; // 24
	byte pad2[ 0x4 ]; // 28
	float m_weight; // 32
	byte pad3[ 0x4 ]; // 36
	float m_playback_rate; // 40
	float m_cycle; // 44

};