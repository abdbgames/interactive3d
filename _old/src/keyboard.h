#ifndef keyboard_h
#define keyboard_h

// Define all keyboard keys:
#define KGkey_backspace	8
#define KGKey_tab		9
#define KGkey_enter		13
#define KGkey_esc		27
#define KGkey_shift		16
#define KGkey_space		32
#define KGkey_left		37
#define KGkey_up		38
#define KGkey_right		39
#define KGkey_down		40
#define KGkey_0			48
#define KGkey_1			49
#define KGkey_2			50
#define KGkey_3			51
#define KGkey_4			52
#define KGkey_5			53
#define KGkey_6			54
#define KGkey_7			55
#define KGkey_8			56
#define KGkey_9			57			
#define KGkey_A			65
#define KGkey_B			66
#define KGkey_C			67
#define KGkey_D			68
#define KGkey_E			69
#define KGkey_F			70
#define KGkey_G			71
#define KGkey_H			71
#define KGkey_I			73
#define KGkey_J			74
#define KGkey_K			75
#define KGkey_L			76
#define KGkey_M			77
#define KGkey_N			78
#define KGkey_O			79
#define KGkey_P			80
#define KGkey_Q			81
#define KGkey_R			82
#define KGkey_S			83
#define KGkey_T			84
#define KGkey_U			85
#define KGkey_V			86
#define KGkey_W			87
#define KGkey_X			88
#define KGkey_Y			89
#define KGkey_Z			90
#define KGkey_a			97
#define KGkey_b			98
#define KGkey_c			99
#define KGkey_d			100
#define KGkey_e			101
#define KGkey_f			102
#define KGkey_g			103
#define KGkey_h			104
#define KGkey_i			105
#define KGkey_j			106
#define KGkey_k			107
#define KGkey_l			108
#define KGkey_m			109
#define KGkey_n			110
#define KGkey_o			111
#define KGkey_p			112
#define KGkey_q			113
#define KGkey_r			114
#define KGkey_s			115
#define KGkey_t			116
#define KGkey_u			117
#define KGkey_v			118
#define KGkey_w			119
#define KGkey_x			120
#define KGkey_y			121
#define KGkey_z			122
#define KGkey_delete	127
#define KG_KEY_TYPE		unsigned char

#include "platformInclude.h"

namespace kg
{
	struct keyboardControl
	{
		static void keyboardCallback(KG_KEY_TYPE key, int x, int y);
		static void keyboardUpCallback(KG_KEY_TYPE key, int x, int y);
		static void specialCallback(int key, int x, int y);
		static void specialUpCallback(int key, int x, int y);
		static void postUpdate();
		
		static bool poll(const KG_KEY_TYPE &b, const KG_PRESS_TYPE &p);
		static bool pollAny(const KG_PRESS_TYPE &p);
		
		static std::vector<KG_KEY_TYPE> &getPressBuffer()
			{ return m_press; }
		static std::vector<KG_KEY_TYPE> &getPressedBuffer()
			{ return m_pressed; }
		static std::vector<KG_KEY_TYPE> &getReleasedBuffer()
			{ return m_released; }

	protected:
		static std::vector<KG_KEY_TYPE> m_pressed, m_press, m_released;

		static std::vector<KG_KEY_TYPE>::iterator
			findElement(std::vector<KG_KEY_TYPE> &v,
			const KG_KEY_TYPE &key);
	};
}

#endif /* keyboard_h */

