#pragma once

namespace Dina
{
#define SCANCODE_MASK (1<<30)
#define SCANCODE_TO_KEYCODE(X)  (X | SCANCODE_MASK)
#define SCANCODE_RIGHT 79
#define	SCANCODE_LEFT 80
#define	SCANCODE_DOWN 81
#define	SCANCODE_UP 82

	enum class KeyCode
	{
		Unknown = 0,
		// Special char
		Backspace = 0x08,
		Tab = '\t',
		Return = '\r',
		Escape = 0x1B,
		Space = ' ',

		// Move keys
		Right = SCANCODE_TO_KEYCODE(SCANCODE_RIGHT),
		Left = SCANCODE_TO_KEYCODE(SCANCODE_LEFT),
		Down = SCANCODE_TO_KEYCODE(SCANCODE_DOWN),
		Up = SCANCODE_TO_KEYCODE(SCANCODE_UP),

		// Numbers
		Key_1 = '1',
		Key_2 = '2',
		Key_3 = '3',
		Key_4 = '4',
		Key_5 = '5',
		Key_6 = '6',
		Key_7 = '7',
		Key_8 = '8',
		Key_9 = '9',
		Key_0 = '0',

		//Letters
		Key_A = 'a',
		Key_B = 'b',
		Key_C = 'c',
		Key_D = 'd',
		Key_E = 'e',
		Key_F = 'f',
		Key_G = 'g',
		Key_H = 'h',
		Key_I = 'i',
		Key_J = 'j',
		Key_K = 'k',
		Key_L = 'l',
		Key_M = 'm',
		Key_N = 'n',
		Key_O = 'o',
		Key_P = 'p',
		Key_Q = 'q',
		Key_R = 'r',
		Key_S = 's',
		Key_T = 't',
		Key_U = 'u',
		Key_V = 'v',
		Key_W = 'w',
		Key_X = 'x',
		Key_Y = 'y',
		Key_Z = 'z',

		// Other char
		Exclamation = '!',
		Question = '?',
		Hash = '#',
		Quote = '\'',
		DoubleQuote = '"',
		Percent = '%',
		Dollar = '$',
		Ampersand = '&',
		LeftParenthese = '(',
		RightParenthese = ')',
		Asterisk = '*',
		Plus = '+',
		Comma = ',',
		Minus = '-',
		Dot = '.',
		Slash = '/',
		Colon = ':',
		SemiColon = ';',
		Less = '<',
		Equal = '=',
		More = '>',
		Arobas = '@',


		MAX_KeyCode
	};
}