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
	"Alt",
	"LeftAlt",
	"RightAlt",
	"Ctrl",
	"LeftCtrl",
	"RightCtrl",
	"Shift",
	"LeftShift",
	"RightShift",
	"Meta",
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
	return eKey >= KEY_ALT && eKey <= KEY_RIGHTMETA;
}

bool EasyWindow::GetExtendedKeys(EKey eKey, EKey* pOutKey1, EKey* pOutKey2)
{
	switch (eKey)
	{
	case KEY_ALT:
		if (pOutKey1 != NULL) *pOutKey1 = KEY_LEFTALT;
		if (pOutKey2 != NULL) *pOutKey2 = KEY_RIGHTALT;
		return true;
	case KEY_CTRL:
		if (pOutKey1 != NULL) *pOutKey1 = KEY_LEFTCTRL;
		if (pOutKey2 != NULL) *pOutKey2 = KEY_RIGHTCTRL;
		return true;
	case KEY_SHIFT:
		if (pOutKey1 != NULL) *pOutKey1 = KEY_LEFTSHIFT;
		if (pOutKey2 != NULL) *pOutKey2 = KEY_RIGHTSHIFT;
		return true;
	case KEY_META:
		if (pOutKey1 != NULL) *pOutKey1 = KEY_LEFTMETA;
		if (pOutKey2 != NULL) *pOutKey2 = KEY_RIGHTMETA;
		return true;
	default:
		if (pOutKey1 != NULL) *pOutKey1 = KEY_NONE;
		if (pOutKey2 != NULL) *pOutKey2 = KEY_NONE;
		return false;
	}
}

EasyWindow::EKey EasyWindow::GetOriginalKey(EKey eKey)
{
	switch (eKey)
	{
	case KEY_LEFTALT:
	case KEY_RIGHTALT:
		return KEY_ALT;
	case KEY_LEFTCTRL:
	case KEY_RIGHTCTRL:
		return KEY_CTRL;
	case KEY_LEFTSHIFT:
	case KEY_RIGHTSHIFT:
		return KEY_SHIFT;
	case KEY_LEFTMETA:
	case KEY_RIGHTMETA:
		return KEY_META;
	default:
		return KEY_NONE;
	}
}