/*
___________________________________

KG Engine Keyboard library
___________________________________

Written by Alastair Bilby
Edited by:

___________________________________

Description:

This library handles user input.
It allows the user to effectivly
attach as many function calls they
want to any keyboard or mouse input
with a name, so that it can be
easily accessed for deletion if
needed. It will not handle any
strings on an update, or to call
a key press (as this would slow
things down significantly!)
___________________________________

Knoob Group 2013,
All rights reserved.
___________________________________
*/

/* Please note this file has been modified for
   use in Interactive3D */

#ifndef keyboard_h
#define keyboard_h

//#include "GraphicsAPI.h"

// Define all keyboard keys:
#ifndef KG_USEGL
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
#define KG_KeyType		unsigned char
#else /* KG_USEGL */
#include <GLFW\glfw3.h>
#define KGkey_backspace	GLFW_KEY_BACKSPACE
#define KGkey_enter		GLFW_KEY_ENTER
#define KGkey_esc		GLFW_KEY_ESCAPE
#define KGkey_Rshift	GLFW_KEY_RIGHT_SHIFT
#define KGkey_Lshift	GLFW_KEY_LEFT_SHIFT
#define KGkey_space		GLFW_KEY_SPACE
#define KGkey_delete	GLFW_KEY_DELETE
#define KGkey_left		GLFW_KEY_LEFT
#define KGkey_up		GLFW_KEY_UP
#define KGkey_right		GLFW_KEY_RIGHT
#define KGkey_down		GLFW_KEY_DOWN
#define KGkey_0			GLFW_KEY_0
#define KGkey_1			GLFW_KEY_1
#define KGkey_2			GLFW_KEY_2
#define KGkey_3			GLFW_KEY_3
#define KGkey_4			GLFW_KEY_4
#define KGkey_5			GLFW_KEY_5
#define KGkey_6			GLFW_KEY_6
#define KGkey_7			GLFW_KEY_7
#define KGkey_8			GLFW_KEY_8
#define KGkey_9			GLFW_KEY_9			
#define KGkey_a			GLFW_KEY_A
#define KGkey_b			GLFW_KEY_B
#define KGkey_c			GLFW_KEY_C
#define KGkey_d			GLFW_KEY_D
#define KGkey_e			GLFW_KEY_E
#define KGkey_f			GLFW_KEY_F
#define KGkey_g			GLFW_KEY_G
#define KGkey_h			GLFW_KEY_H
#define KGkey_i			GLFW_KEY_I
#define KGkey_j			GLFW_KEY_J
#define KGkey_k			GLFW_KEY_K
#define KGkey_l			GLFW_KEY_L
#define KGkey_m			GLFW_KEY_M
#define KGkey_n			GLFW_KEY_N
#define KGkey_o			GLFW_KEY_O
#define KGkey_p			GLFW_KEY_P
#define KGkey_q			GLFW_KEY_Q
#define KGkey_r			GLFW_KEY_R
#define KGkey_s			GLFW_KEY_S
#define KGkey_t			GLFW_KEY_T
#define KGkey_u			GLFW_KEY_U
#define KGkey_v			GLFW_KEY_V
#define KGkey_w			GLFW_KEY_W
#define KGkey_x			GLFW_KEY_X
#define KGkey_y			GLFW_KEY_Y
#define KGkey_z			GLFW_KEY_Z
#define KG_KeyType		int
#endif /* KG_USEGL */

// #include "multiPlatformHelper.h"
#include "platformInclude.h"

namespace kg
{
	typedef std::map<KG_KeyType, VoidF> voidMap;
	typedef std::map<std::string, VoidF> voidNameMap;
	typedef std::map<KG_KeyType, voidNameMap> voidKeyMap;

	struct keyboardControl
	{
		// Methods:
		static void keyboardCallback(KG_KeyType key, int x, int y);
		static void keyBufferBegin();
		static void keyBufferEnd();
		static void setKeyPress(const KG_KeyType &key, const std::string &fName, VoidF function);
		static void breakKeyPress(const KG_KeyType &key, const std::string &fName);
		static void setKeyPressed(const KG_KeyType &key, const std::string &fName, VoidF function);
		static void breakKeyPressed(const KG_KeyType &key, const std::string &fName);
		static void setKeyRelease(const KG_KeyType &key, const std::string &fName, VoidF function);
		static void breakKeyRelease(const KG_KeyType &key, const std::string &fName);
		static void keyPress(const KG_KeyType &key);
		static void keyPressed(const KG_KeyType &key);
		static void keyRelease(const KG_KeyType &key);
		static void setMousePressL(const std::string &fName, VoidF function);
		static void setMousePressR(const std::string &fName, VoidF function);
		static void setMousePressM(const std::string &fName, VoidF function);
		static void setMouseReleaseL(const std::string &fName, VoidF function);
		static void setMouseReleaseR(const std::string &fName, VoidF function);
		static void setMouseReleaseM(const std::string &fName, VoidF function);
		static void setMousePressedL(const std::string &fName, VoidF function);
		static void setMousePressedR(const std::string &fName, VoidF function);
		static void setMousePressedM(const std::string &fName, VoidF function);
		static void breakMousePressL(const std::string &fName);
		static void breakMousePressR(const std::string &fName);
		static void breakMousePressM(const std::string &fName);
		static void breakMouseReleaseL(const std::string &fName);
		static void breakMouseReleaseR(const std::string &fName);
		static void breakMouseReleaseM(const std::string &fName);
		static void breakMousePressedL(const std::string &fName);
		static void breakMousePressedR(const std::string &fName);
		static void breakMousePressedM(const std::string &fName);
		static void mouseLPress();
		static void mouseRPress();
		static void mouseMPress();
		static void mouseLRelease();
		static void mouseRRelease();
		static void mouseMRelease();
		static void mouseLPressed();
		static void mouseRPressed();
		static void mouseMPressed();
		static void clearKeyFunctions();
		static void clearMouseFunctions();

	protected:
		// Protected Methods:
		static voidKeyMap functionList;
		static voidKeyMap functionRList;
		static voidKeyMap functionPList;
		static std::map<KG_KeyType, bool> keyTrack;

		static voidNameMap mouseL;
		static voidNameMap mouseR;
		static voidNameMap mouseM;
		static voidNameMap RmouseL;
		static voidNameMap RmouseR;
		static voidNameMap RmouseM;
		static voidNameMap PmouseL;
		static voidNameMap PmouseR;
		static voidNameMap PmouseM;

		static bool removeFunctionInNameList(voidNameMap &vnm, const std::string &fName);
		static void runAllFunctionsForName(voidNameMap &vnm);
		static void addFunctionToKeyList(voidKeyMap &vkm, const KG_KeyType &key, const std::string &fName, VoidF function);
		static void removeFunctionInKeyList(voidKeyMap &vkm, const KG_KeyType &key, const std::string &fName);
		static void runAllFunctionsForKey(voidKeyMap &vkm, const KG_KeyType &key);
	};
}

#endif
