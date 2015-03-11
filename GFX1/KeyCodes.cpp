#include "KeyCodes.h"

namespace Input{
	namespace VKEY{

		std::string keyToString(VKEY key){
			std::string str = "Unknown";

			switch (key){
			case VKEY_ESC:
				str = "Escape";
				break;
			case VKEY_F1:
				str = "F1";
				break;
			case VKEY_F2:
				str = "F2";
				break;
			case VKEY_F3:
				str = "F3";
				break;
			case VKEY_F4:
				str = "F4";
				break;
			case VKEY_F5:
				str = "F5";
				break;
			case VKEY_F6:
				str = "F6";
				break;
			case VKEY_F7:
				str = "F7";
				break;
			case VKEY_F8:
				str = "F8";
				break;
			case VKEY_F9:
				str = "F9";
				break;
			case VKEY_F10:
				str = "F10";
				break;
			case VKEY_F11:
				str = "F11";
				break;
			case VKEY_F12:
				str = "F12";
				break;
			case VKEY_PAUSE:
				str = "Pause";
				break;
			case VKEY_PRINTSCREEN:
				str = "Print Screen";
				break;
			case VKEY_DELETE:
				str = "Delete";
				break;
			case VKEY_TILDA:
				str = "~";
				break;
			case VKEY_1:
				str = "1";
				break;
			case VKEY_2:
				str = "2";
				break;
			case VKEY_3:
				str = "3";
				break;
			case VKEY_4:
				str = "4";
				break;
			case VKEY_5:
				str = "5";
				break;
			case VKEY_6:
				str = "6";
				break;
			case VKEY_7:
				str = "7";
				break;
			case VKEY_8:
				str = "8";
				break;
			case VKEY_9:
				str = "9";
				break;
			case VKEY_0:
				str = "0";
				break;
			case VKEY_MINUS:
				str = "-";
				break;
			case VKEY_PLUS:
				str = "+";
				break;
			case VKEY_BACKSPACE:
				str = "Back Space";
				break;
			case VKEY_TAB:
				str = "Tab";
				break;
			case VKEY_Q:
				str = "Q";
				break;
			case VKEY_W:
				str = "W";
				break;
			case VKEY_E:
				str = "E";
				break;
			case VKEY_R:
				str = "R";
				break;
			case VKEY_T:
				str = "T";
				break;
			case VKEY_Y:
				str = "Y";
				break;
			case VKEY_U:
				str = "U";
				break;
			case VKEY_I:
				str = "I";
				break;
			case VKEY_O:
				str = "O";
				break;
			case VKEY_P:
				str = "P";
				break;
			case VKEY_LBRACKET:
				str = "[";
				break;
			case VKEY_RBRACKET:
				str = "]";
				break;
			case VKEY_BACKSLASH:
				str = "\\";
				break;
			case VKEY_CAPSLOCK:
				str = "Caps Lock";
				break;
			case VKEY_A:
				str = "A";
				break;
			case VKEY_S:
				str = "S";
				break;
			case VKEY_D:
				str = "D";
				break;
			case VKEY_F:
				str = "F";
				break;
			case VKEY_G:
				str = "G";
				break;
			case VKEY_H:
				str = "H";
				break;
			case VKEY_J:
				str = "J";
				break;
			case VKEY_K:
				str = "K";
				break;
			case VKEY_L:
				str = "L";
				break;
			case VKEY_SEMICOLIN:
				str = ";";
				break;
			case VKEY_QUOTE:
				str = "\"";
				break;
			case VKEY_ENTER:
				str = "Enter";
				break;
			case VKEY_LSHIFT:
				str = "Left Shift";
				break;
			case VKEY_Z:
				str = "Z";
				break;
			case VKEY_X:
				str = "X";
				break;
			case VKEY_C:
				str = "C";
				break;
			case VKEY_V:
				str = "V";
				break;
			case VKEY_B:
				str = "B";
				break;
			case VKEY_N:
				str = "N";
				break;
			case VKEY_M:
				str = "M";
				break;
			case VKEY_COMMA:
				str = ",";
				break;
			case VKEY_PERIOD:
				str = ".";
				break;
			case VKEY_FORWARDSLASH:
				str = "/";
				break;
			case VKEY_RSHIFT:
				str = "Right Shift";
				break;
			case VKEY_LCTRL:
				str = "Left Ctrl";
				break;
			case VKEY_LALT:
				str = "Left Alt";
				break;
			case VKEY_SPACE:
				str = "Space";
				break;
			case VKEY_RALT:
				str = "Right Alt";
				break;
			case VKEY_RCTRL:
				str = "Right Ctrl";
				break;
			case VKEY_HOME:
				str = "Home";
				break;
			case VKEY_PGUP:
				str = "Page Up";
				break;
			case VKEY_PGDN:
				str = "Page Down";
				break;
			case VKEY_END:
				str = "End";
				break;
			case VKEY_NUMLOCK:
				str = "Num Lock";
				break;
			case VKEY_NUMDIVIDE:
				str = "Num /";
				break;
			case VKEY_NUMMULT:
				str = "Num *";
				break;
			case VKEY_NUMMINUS:
				str = "Num -";
				break;
			case VKEY_NUMPLUS:
				str = "Num +";
				break;
			case VKEY_NUMENTER:
				str = "Num Enter";
				break;
			case VKEY_NUM7:
				str = "Num 7";
				break;
			case VKEY_NUM8:
				str = "Num 8";
				break;
			case VKEY_NUM9:
				str = "Num 9";
				break;
			case VKEY_NUM4:
				str = "Num 4";
				break;
			case VKEY_NUM5:
				str = "Num 5";
				break;
			case VKEY_NUM6:
				str = "Num 6";
				break;
			case VKEY_NUM1:
				str = "Num 1";
				break;
			case VKEY_NUM2:
				str = "Num 2";
				break;
			case VKEY_NUM3:
				str = "Num 3";
				break;
			case VKEY_NUM0:
				str = "Num 0";
				break;
			case VKEY_NUMPERIOD:
				str = "Num .";
				break;
			case VKEY_UARROW:
				str = "Up Arrow";
				break;
			case VKEY_DARROW:
				str = "Down Arrow";
				break;
			case VKEY_LARROW:
				str = "Left Arrow";
				break;
			case VKEY_RARROW:
				str = "Right Arrow";
				break;
			case VKEY_SCROLLLOCK:
				str = "Scroll Lock";
				break;
			}

			return str;
		}//std::string keyToString(VKEY key)

		VKEY stringToKey(std::string){
			return VKEY_UNKNOWN;
		}//VKEY stringToKey(std::string)

	}//namespace VKEY
}//namespace System