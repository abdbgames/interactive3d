#ifndef KGConstants_h
#define KGConstants_h

// Define all keyboard keys:
#define KGKey_backspace	8
#define KGKey_tab		9
#define KGKey_enter		13
#define KGKey_esc		27
#define KGKey_shift		16
#define KGKey_space		32
#define KGKey_left		37
#define KGKey_up		38
#define KGKey_right		39
#define KGKey_down		40
#define KGKey_0			48
#define KGKey_1			49
#define KGKey_2			50
#define KGKey_3			51
#define KGKey_4			52
#define KGKey_5			53
#define KGKey_6			54
#define KGKey_7			55
#define KGKey_8			56
#define KGKey_9			57
#define KGKey_A			65
#define KGKey_B			66
#define KGKey_C			67
#define KGKey_D			68
#define KGKey_E			69
#define KGKey_F			70
#define KGKey_G			71
#define KGKey_H			71
#define KGKey_I			73
#define KGKey_J			74
#define KGKey_K			75
#define KGKey_L			76
#define KGKey_M			77
#define KGKey_N			78
#define KGKey_O			79
#define KGKey_P			80
#define KGKey_Q			81
#define KGKey_R			82
#define KGKey_S			83
#define KGKey_T			84
#define KGKey_U			85
#define KGKey_V			86
#define KGKey_W			87
#define KGKey_X			88
#define KGKey_Y			89
#define KGKey_Z			90
#define KGKey_a			97
#define KGKey_b			98
#define KGKey_c			99
#define KGKey_d			100
#define KGKey_e			101
#define KGKey_f			102
#define KGKey_g			103
#define KGKey_h			104
#define KGKey_i			105
#define KGKey_j			106
#define KGKey_k			107
#define KGKey_l			108
#define KGKey_m			109
#define KGKey_n			110
#define KGKey_o			111
#define KGKey_p			112
#define KGKey_q			113
#define KGKey_r			114
#define KGKey_s			115
#define KGKey_t			116
#define KGKey_u			117
#define KGKey_v			118
#define KGKey_w			119
#define KGKey_x			120
#define KGKey_y			121
#define KGKey_z			122
#define KGKey_delete	127
#define KG_KEY_TYPE		unsigned char

// allow us to easily pass function pointers:
typedef void(*VoidF)();

// Pi:
#define KG_PI 3.14159265359

// Gravity:
#define KG_GR 9.8f

// Constant milliseconds value to divide from seconds:
#define milli 1000

namespace kg
{
	// A press type:
	enum KG_PRESS_TYPE
	{
		KG_DOWN,
		KG_UP,
		KG_PRESSED,
	};

	// A draw type mode:
	enum KG_DRAW_MODE
	{
		KG_FILLED,
		KG_FILLED_NOCULL,
		KG_WIRE,
		KG_POINTS,
		KG_HIDE,
	};

	// A Lighting mode:
	enum KG_LIGHT_MODE
	{
		KG_FULL,
		KG_DIR, // Directional only.
		KG_UNLIT,
	};

	// Mesh mode:
	enum KG_MESH_MODE
	{
		KG_TRIS,
		KG_TRI_STRIP,
		KG_TRI_FAN,
		KG_QUADS,
		KG_QUAD_STRIP,
	};
}

#endif /* KGConstants_h */
