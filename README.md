# EasyWindow

EasyWindow is a simple library for creating and managing windows.

It's usefull for create graphics project.

__!!!WARNING!!!__

Only work on Windows actually (need an Linux and MacOS support) and not stable enough for production.

## How to use
Include files in you project:
 * EasyWindow.h
 * EasyWindow.h
 * EasyWindowWin32.h
 
 
EasyWindow allow you to create a window in 3 lines

``` c++
#include "EasyWindow.h"

EasyWindow* pMyWindow = EasyWindow::Create("My window", 640, 480);
while (pMyWindow->Update());
```

## How to get some events

Available events:
 * OnSize
 * OnMove
 * OnMaximize
 * OnMinimize
 * OnRestore
 * OnFocus
 * OnClose
 * OnMouseButton
 * OnMouseMove
 * OnMouseWheel
 * OnKey
 * OnChar
 
 ### Example
 
``` c++
#include "EasyWindow.h"

void MyOnSizeFunction(int iWidth, int iHeight)
{
	printf("%d x %d\n", iWidth, iHeight);
}

void MyOnKeyFunction(EasyWindow::EKey eKey, bool bIsDown)
{
	printf("Key '%s' is %s\n", EasyWindow::KeyToString(eKey), bIsDown ? "down" : "up");
}

void main()
{
	// Create window
	EasyWindow* pMyWindow = EasyWindow::Create("My window", 640, 480);
	// Set events callback
	pMyWindow->OnSize.Set(&MyOnSizeFunction);
	pMyWindow->OnKey.Set(&MyOnKeyFunction);
	// Update window
	while (pMyWindow->Update());
}
```

## Use with BGFX

```c++
EasyWindow* pMyWindow = EasyWindow::Create("My window", 640, 480);

bgfx::PlatformData pd;
memset(&pd, 0, sizeof(pd));
pd.nwh = pMyWindow->GetHandle();
bgfx::setPlatformData(pd);

bool bInit = bgfx::init(bgfx::RendererType::OpenGL);

bgfx::createFrameBuffer(pMyWindow->GetHandle(), pMyWindow->GetClientWidth(), pMyWindow->GetClientHeight());
```
