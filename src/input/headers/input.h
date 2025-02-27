/*
** input.h
**
** This file is part of mkxp.
**
** Copyright (C) 2013 Jonas Kulla <Nyocurio@gmail.com>
**
** mkxp is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** mkxp is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with mkxp.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL_keycode.h>

struct InputPrivate;
struct RGSSThreadData;

#define BUTTONCODE_SDLK_OFFSET 60
#define BUTTONCODE_SDLK_COUNT 0x180

class Input
{
public:
	enum ButtonCode
	{
		None = 0,

		Down = 2, Left = 4, Right = 6, Up = 8,

		Action = 11,
		Cancel = 12,
		Menu = 13,
		Items = 14,
		Run = 15,
		Deactivate = 16,

		L = 17, R = 18,

		F5 = 25, F6 = 26, F7 = 27, F8 = 28, F9 = 29,

		Settings = 41, Pause = 42,

		/* Non-standard extensions */
		MouseLeft = 38, MouseMiddle = 39, MouseRight = 40,

		/* Non-standard SDL keycode extensions */
#define DECLARE_SDL_KEYCODE_NORMAL(name) \
	KEY_##name = SDLK_##name + BUTTONCODE_SDLK_OFFSET,
#define DECLARE_SDL_KEYCODE_CAPITAL(lower, upper) \
	KEY_##upper = SDLK_##lower + BUTTONCODE_SDLK_OFFSET,
#define DECLARE_SDL_KEYCODE_EXTENDED(name) \
	KEY_##name = (SDLK_##name & 0xff | ((SDLK_##name & 0x180) == 0x100 ? 0x180 : 0)) + BUTTONCODE_SDLK_OFFSET,

		DECLARE_SDL_KEYCODE_NORMAL(UNKNOWN)
		DECLARE_SDL_KEYCODE_NORMAL(BACKSPACE)
		DECLARE_SDL_KEYCODE_NORMAL(TAB)
		DECLARE_SDL_KEYCODE_NORMAL(RETURN)
		DECLARE_SDL_KEYCODE_NORMAL(ESCAPE)
		DECLARE_SDL_KEYCODE_NORMAL(SPACE)
		DECLARE_SDL_KEYCODE_NORMAL(EXCLAIM)
		DECLARE_SDL_KEYCODE_NORMAL(QUOTEDBL)
		DECLARE_SDL_KEYCODE_NORMAL(HASH)
		DECLARE_SDL_KEYCODE_NORMAL(DOLLAR)
		DECLARE_SDL_KEYCODE_NORMAL(PERCENT)
		DECLARE_SDL_KEYCODE_NORMAL(AMPERSAND)
		DECLARE_SDL_KEYCODE_NORMAL(QUOTE)
		DECLARE_SDL_KEYCODE_NORMAL(LEFTPAREN)
		DECLARE_SDL_KEYCODE_NORMAL(RIGHTPAREN)
		DECLARE_SDL_KEYCODE_NORMAL(ASTERISK)
		DECLARE_SDL_KEYCODE_NORMAL(PLUS)
		DECLARE_SDL_KEYCODE_NORMAL(COMMA)
		DECLARE_SDL_KEYCODE_NORMAL(MINUS)
		DECLARE_SDL_KEYCODE_NORMAL(PERIOD)
		DECLARE_SDL_KEYCODE_NORMAL(SLASH)
		DECLARE_SDL_KEYCODE_NORMAL(0)
		DECLARE_SDL_KEYCODE_NORMAL(1)
		DECLARE_SDL_KEYCODE_NORMAL(2)
		DECLARE_SDL_KEYCODE_NORMAL(3)
		DECLARE_SDL_KEYCODE_NORMAL(4)
		DECLARE_SDL_KEYCODE_NORMAL(5)
		DECLARE_SDL_KEYCODE_NORMAL(6)
		DECLARE_SDL_KEYCODE_NORMAL(7)
		DECLARE_SDL_KEYCODE_NORMAL(8)
		DECLARE_SDL_KEYCODE_NORMAL(9)
		DECLARE_SDL_KEYCODE_NORMAL(COLON)
		DECLARE_SDL_KEYCODE_NORMAL(SEMICOLON)
		DECLARE_SDL_KEYCODE_NORMAL(LESS)
		DECLARE_SDL_KEYCODE_NORMAL(EQUALS)
		DECLARE_SDL_KEYCODE_NORMAL(GREATER)
		DECLARE_SDL_KEYCODE_NORMAL(QUESTION)
		DECLARE_SDL_KEYCODE_NORMAL(AT)
		DECLARE_SDL_KEYCODE_NORMAL(LEFTBRACKET)
		DECLARE_SDL_KEYCODE_NORMAL(BACKSLASH)
		DECLARE_SDL_KEYCODE_NORMAL(RIGHTBRACKET)
		DECLARE_SDL_KEYCODE_NORMAL(CARET)
		DECLARE_SDL_KEYCODE_NORMAL(UNDERSCORE)
		DECLARE_SDL_KEYCODE_NORMAL(BACKQUOTE)
		DECLARE_SDL_KEYCODE_NORMAL(DELETE)

		DECLARE_SDL_KEYCODE_CAPITAL(a, A)
		DECLARE_SDL_KEYCODE_CAPITAL(b, B)
		DECLARE_SDL_KEYCODE_CAPITAL(c, C)
		DECLARE_SDL_KEYCODE_CAPITAL(d, D)
		DECLARE_SDL_KEYCODE_CAPITAL(e, E)
		DECLARE_SDL_KEYCODE_CAPITAL(f, F)
		DECLARE_SDL_KEYCODE_CAPITAL(g, G)
		DECLARE_SDL_KEYCODE_CAPITAL(h, H)
		DECLARE_SDL_KEYCODE_CAPITAL(i, I)
		DECLARE_SDL_KEYCODE_CAPITAL(j, J)
		DECLARE_SDL_KEYCODE_CAPITAL(k, K)
		DECLARE_SDL_KEYCODE_CAPITAL(l, L)
		DECLARE_SDL_KEYCODE_CAPITAL(m, M)
		DECLARE_SDL_KEYCODE_CAPITAL(n, N)
		DECLARE_SDL_KEYCODE_CAPITAL(o, O)
		DECLARE_SDL_KEYCODE_CAPITAL(p, P)
		DECLARE_SDL_KEYCODE_CAPITAL(q, Q)
		DECLARE_SDL_KEYCODE_CAPITAL(r, R)
		DECLARE_SDL_KEYCODE_CAPITAL(s, S)
		DECLARE_SDL_KEYCODE_CAPITAL(t, T)
		DECLARE_SDL_KEYCODE_CAPITAL(u, U)
		DECLARE_SDL_KEYCODE_CAPITAL(v, V)
		DECLARE_SDL_KEYCODE_CAPITAL(w, W)
		DECLARE_SDL_KEYCODE_CAPITAL(x, X)
		DECLARE_SDL_KEYCODE_CAPITAL(y, Y)
		DECLARE_SDL_KEYCODE_CAPITAL(z, Z)

		DECLARE_SDL_KEYCODE_EXTENDED(CAPSLOCK)
		DECLARE_SDL_KEYCODE_EXTENDED(F1)
		DECLARE_SDL_KEYCODE_EXTENDED(F2)
		DECLARE_SDL_KEYCODE_EXTENDED(F3)
		DECLARE_SDL_KEYCODE_EXTENDED(F4)
		DECLARE_SDL_KEYCODE_EXTENDED(F5)
		DECLARE_SDL_KEYCODE_EXTENDED(F6)
		DECLARE_SDL_KEYCODE_EXTENDED(F7)
		DECLARE_SDL_KEYCODE_EXTENDED(F8)
		DECLARE_SDL_KEYCODE_EXTENDED(F9)
		DECLARE_SDL_KEYCODE_EXTENDED(F10)
		DECLARE_SDL_KEYCODE_EXTENDED(F11)
		DECLARE_SDL_KEYCODE_EXTENDED(F12)
		DECLARE_SDL_KEYCODE_EXTENDED(PRINTSCREEN)
		DECLARE_SDL_KEYCODE_EXTENDED(SCROLLLOCK)
		DECLARE_SDL_KEYCODE_EXTENDED(PAUSE)
		DECLARE_SDL_KEYCODE_EXTENDED(INSERT)
		DECLARE_SDL_KEYCODE_EXTENDED(HOME)
		DECLARE_SDL_KEYCODE_EXTENDED(PAGEUP)
		DECLARE_SDL_KEYCODE_EXTENDED(END)
		DECLARE_SDL_KEYCODE_EXTENDED(PAGEDOWN)
		DECLARE_SDL_KEYCODE_EXTENDED(RIGHT)
		DECLARE_SDL_KEYCODE_EXTENDED(LEFT)
		DECLARE_SDL_KEYCODE_EXTENDED(DOWN)
		DECLARE_SDL_KEYCODE_EXTENDED(UP)
		DECLARE_SDL_KEYCODE_EXTENDED(NUMLOCKCLEAR)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_DIVIDE)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MULTIPLY)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MINUS)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_PLUS)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_ENTER)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_1)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_2)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_3)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_4)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_5)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_6)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_7)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_8)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_9)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_0)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_PERIOD)
		DECLARE_SDL_KEYCODE_EXTENDED(APPLICATION)
		DECLARE_SDL_KEYCODE_EXTENDED(POWER)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_EQUALS)
		DECLARE_SDL_KEYCODE_EXTENDED(F13)
		DECLARE_SDL_KEYCODE_EXTENDED(F14)
		DECLARE_SDL_KEYCODE_EXTENDED(F15)
		DECLARE_SDL_KEYCODE_EXTENDED(F16)
		DECLARE_SDL_KEYCODE_EXTENDED(F17)
		DECLARE_SDL_KEYCODE_EXTENDED(F18)
		DECLARE_SDL_KEYCODE_EXTENDED(F19)
		DECLARE_SDL_KEYCODE_EXTENDED(F20)
		DECLARE_SDL_KEYCODE_EXTENDED(F21)
		DECLARE_SDL_KEYCODE_EXTENDED(F22)
		DECLARE_SDL_KEYCODE_EXTENDED(F23)
		DECLARE_SDL_KEYCODE_EXTENDED(F24)
		// KEY_EXECUTE is used in windows, so it is not exposed. not that anyone really needs it.
		// DECLARE_SDL_KEYCODE_EXTENDED(EXECUTE)
		DECLARE_SDL_KEYCODE_EXTENDED(HELP)
		DECLARE_SDL_KEYCODE_EXTENDED(MENU)
		DECLARE_SDL_KEYCODE_EXTENDED(SELECT)
		DECLARE_SDL_KEYCODE_EXTENDED(STOP)
		DECLARE_SDL_KEYCODE_EXTENDED(AGAIN)
		DECLARE_SDL_KEYCODE_EXTENDED(UNDO)
		DECLARE_SDL_KEYCODE_EXTENDED(CUT)
		DECLARE_SDL_KEYCODE_EXTENDED(COPY)
		DECLARE_SDL_KEYCODE_EXTENDED(PASTE)
		DECLARE_SDL_KEYCODE_EXTENDED(FIND)
		DECLARE_SDL_KEYCODE_EXTENDED(MUTE)
		DECLARE_SDL_KEYCODE_EXTENDED(VOLUMEUP)
		DECLARE_SDL_KEYCODE_EXTENDED(VOLUMEDOWN)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_COMMA)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_EQUALSAS400)
		DECLARE_SDL_KEYCODE_EXTENDED(ALTERASE)
		DECLARE_SDL_KEYCODE_EXTENDED(SYSREQ)
		DECLARE_SDL_KEYCODE_EXTENDED(CANCEL)
		DECLARE_SDL_KEYCODE_EXTENDED(CLEAR)
		DECLARE_SDL_KEYCODE_EXTENDED(PRIOR)
		DECLARE_SDL_KEYCODE_EXTENDED(RETURN2)
		DECLARE_SDL_KEYCODE_EXTENDED(SEPARATOR)
		DECLARE_SDL_KEYCODE_EXTENDED(OUT)
		DECLARE_SDL_KEYCODE_EXTENDED(OPER)
		DECLARE_SDL_KEYCODE_EXTENDED(CLEARAGAIN)
		DECLARE_SDL_KEYCODE_EXTENDED(CRSEL)
		DECLARE_SDL_KEYCODE_EXTENDED(EXSEL)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_00)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_000)
		DECLARE_SDL_KEYCODE_EXTENDED(THOUSANDSSEPARATOR)
		DECLARE_SDL_KEYCODE_EXTENDED(DECIMALSEPARATOR)
		DECLARE_SDL_KEYCODE_EXTENDED(CURRENCYUNIT)
		DECLARE_SDL_KEYCODE_EXTENDED(CURRENCYSUBUNIT)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_LEFTPAREN)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_RIGHTPAREN)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_LEFTBRACE)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_RIGHTBRACE)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_TAB)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_BACKSPACE)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_A)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_B)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_C)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_D)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_E)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_F)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_XOR)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_POWER)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_PERCENT)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_LESS)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_GREATER)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_AMPERSAND)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_DBLAMPERSAND)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_VERTICALBAR)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_DBLVERTICALBAR)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_COLON)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_HASH)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_SPACE)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_AT)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_EXCLAM)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MEMSTORE)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MEMRECALL)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MEMCLEAR)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MEMADD)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MEMSUBTRACT)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MEMMULTIPLY)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_MEMDIVIDE)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_PLUSMINUS)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_CLEAR)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_CLEARENTRY)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_BINARY)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_OCTAL)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_DECIMAL)
		DECLARE_SDL_KEYCODE_EXTENDED(KP_HEXADECIMAL)
		DECLARE_SDL_KEYCODE_EXTENDED(LCTRL)
		DECLARE_SDL_KEYCODE_EXTENDED(LSHIFT)
		DECLARE_SDL_KEYCODE_EXTENDED(LALT)
		DECLARE_SDL_KEYCODE_EXTENDED(LGUI)
		DECLARE_SDL_KEYCODE_EXTENDED(RCTRL)
		DECLARE_SDL_KEYCODE_EXTENDED(RSHIFT)
		DECLARE_SDL_KEYCODE_EXTENDED(RALT)
		DECLARE_SDL_KEYCODE_EXTENDED(RGUI)
		DECLARE_SDL_KEYCODE_EXTENDED(MODE)
		DECLARE_SDL_KEYCODE_EXTENDED(AUDIONEXT)
		DECLARE_SDL_KEYCODE_EXTENDED(AUDIOPREV)
		DECLARE_SDL_KEYCODE_EXTENDED(AUDIOSTOP)
		DECLARE_SDL_KEYCODE_EXTENDED(AUDIOPLAY)
		DECLARE_SDL_KEYCODE_EXTENDED(AUDIOMUTE)
		DECLARE_SDL_KEYCODE_EXTENDED(MEDIASELECT)
		DECLARE_SDL_KEYCODE_EXTENDED(WWW)
		DECLARE_SDL_KEYCODE_EXTENDED(MAIL)
		DECLARE_SDL_KEYCODE_EXTENDED(CALCULATOR)
		DECLARE_SDL_KEYCODE_EXTENDED(COMPUTER)
		DECLARE_SDL_KEYCODE_EXTENDED(AC_SEARCH)
		DECLARE_SDL_KEYCODE_EXTENDED(AC_HOME)
		DECLARE_SDL_KEYCODE_EXTENDED(AC_BACK)
		DECLARE_SDL_KEYCODE_EXTENDED(AC_FORWARD)
		DECLARE_SDL_KEYCODE_EXTENDED(AC_STOP)
		DECLARE_SDL_KEYCODE_EXTENDED(AC_REFRESH)
		DECLARE_SDL_KEYCODE_EXTENDED(AC_BOOKMARKS)
		DECLARE_SDL_KEYCODE_EXTENDED(BRIGHTNESSDOWN)
		DECLARE_SDL_KEYCODE_EXTENDED(BRIGHTNESSUP)
		DECLARE_SDL_KEYCODE_EXTENDED(DISPLAYSWITCH)
		DECLARE_SDL_KEYCODE_EXTENDED(KBDILLUMTOGGLE)
		DECLARE_SDL_KEYCODE_EXTENDED(KBDILLUMDOWN)
		DECLARE_SDL_KEYCODE_EXTENDED(KBDILLUMUP)
		DECLARE_SDL_KEYCODE_EXTENDED(EJECT)
		DECLARE_SDL_KEYCODE_EXTENDED(SLEEP)
	};

	void update();

	bool isPressed(int button);
	bool isTriggered(int button);
	bool isRepeated(int button);

	int dir4Value();
	int dir8Value();

	/* Non-standard extensions */
	int mouseX();
	int mouseY();

	bool hasQuit();

	Uint16 modkeys;

	void setKey(int button);
	void unsetKey(int button);
	void setPressed(int button);
	void setTriggered(int button);
	void setRepeated(int button);

private:
	Input(const RGSSThreadData &rtData);
	~Input();

	friend struct SharedStatePrivate;

	InputPrivate *p;
};

#endif // INPUT_H
