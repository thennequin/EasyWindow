#include "EasyWindow.h"

#include <string.h>

#include <ctype.h>      // toupper

const char* const c_pKeyTable[] = {
	0,
	"Esc",
	"Return",
	"Tab",
	"Space",
	"Backspace",
	"Up",
	"Down",
	"Left",
	"Right",
	"Insert",
	"Delete",
	"Home",
	"End",
	"PageUp",
	"PageDown",
	"Print",
	"Plus",
	"Minus",
	"LeftBracket",
	"RightBracket",
	"Semicolon",
	"Quote",
	"Comma",
	"Period",
	"Slash",
	"Backslash",
	"Tilde",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"NumPad0",
	"NumPad1",
	"NumPad2",
	"NumPad3",
	"NumPad4",
	"NumPad5",
	"NumPad6",
	"NumPad7",
	"NumPad8",
	"NumPad9",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",

	// Modifiers
	"LeftAlt",
	"RightAlt",
	"LeftCtrl",
	"RightCtrl",
	"LeftShift",
	"RightShift",
	"LeftMeta",
	"RightMeta"
};

const char* EasyWindow::KeyToString(EKey eKey)
{
	return c_pKeyTable[eKey];
}

int _EasyWindowStricmp(const char* str1, const char* str2)
{
	int d;
	while ((d = ::toupper(*str2) - ::toupper(*str1)) == 0 && *str1) { str1++; str2++; }
	return d;
}

EasyWindow::EKey EasyWindow::StringToKey(const char* pString)
{
	if (pString == 0)
		return KEY_NONE;

	for (int i = 1; i < sizeof(c_pKeyTable); ++i)
	{
		if (_EasyWindowStricmp(pString, c_pKeyTable[i]) == 0)
			return (EasyWindow::EKey)i;
	}

	return KEY_NONE;
}

bool EasyWindow::IsModifierKey(EKey eKey)
{
	return eKey >= KEY_LEFTALT && eKey <= KEY_RIGHTMETA;
}

EasyWindow::EKey EasyWindow::GetAlternativeKey(EKey eKey)
{
	switch (eKey)
	{
	case KEY_LEFTALT:
		return KEY_RIGHTALT;
	case KEY_RIGHTALT:
		return KEY_LEFTALT;
	case KEY_LEFTCTRL:
		return KEY_RIGHTCTRL;
	case KEY_RIGHTCTRL:
		return KEY_LEFTCTRL;
	case KEY_LEFTSHIFT:
		return KEY_RIGHTSHIFT;
	case KEY_RIGHTSHIFT:
		return KEY_LEFTSHIFT;
	case KEY_LEFTMETA:
		return KEY_RIGHTMETA;
	case KEY_RIGHTMETA:
		return KEY_LEFTMETA;
	default:
		return KEY_NONE;
	}
}