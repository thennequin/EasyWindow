
#include "EasyWindow.h"

#include <stdio.h>

void OnSize(const EasyWindow* /*pWindow*/, int iW, int iH)
{
	printf("OnSize %d %d\n", iW, iH);
}

bool OnClose(const EasyWindow* /*pWindow*/)
{
	printf("OnClose\n");
	static int s_iCloseCount = 0;
	return s_iCloseCount++ < 3;
}

void OnChar(const EasyWindow* /*pWindow*/, unsigned long iChar)
{
	printf("OnChar %c\n", (char)iChar);
}

void OnKey(const EasyWindow* /*pWindow*/, EasyWindow::EKey eKey, bool bDown)
{
	printf("OnKey %s %d %s\n", bDown ? "down" : "up", eKey, EasyWindow::KeyToString(eKey));
}

int main()
{
	EasyWindow* pWindow = EasyWindow::Create("Test", 640, 480, true, 0, EasyWindow::E_STYLE_NORMAL, EasyWindow::E_FLAG_OWN_DC);
	pWindow->OnSize.Set(&OnSize);
	pWindow->OnClose.Set(&OnClose);

	pWindow->OnKey.Set(&OnKey);
	pWindow->OnChar.Set(&OnChar);
	pWindow->Show();
	pWindow->SetCursor(EasyWindow::E_CURSOR_HAND);

	while (pWindow->Update())
	{
		if ((pWindow->GetLastEvents() & EasyWindow::E_EVENT_SIZED) != 0)
		{
			printf("Updated size\n");
		}
	}

	return 0;
}