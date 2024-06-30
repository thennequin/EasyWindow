#ifndef __EASY_WINDOW_H__
#define __EASY_WINDOW_H__

class EasyWindow
{
public:
	//Caller
	//No arg
	template<typename R>
	class Caller
	{
	public:
		virtual ~Caller() {}
		virtual R					Call(const EasyWindow* pWindow) = 0;
	};

	template<typename R>
	class FunctionCaller : public Caller<R>
	{
	public:
		FunctionCaller(R(*pFunctionPtr)(const EasyWindow*))
		{
			m_pFunctionPtr = pFunctionPtr;
		}
		virtual R					Call(const EasyWindow* pWindow)
		{
			return m_pFunctionPtr(pWindow);
		}
		R(*m_pFunctionPtr)(const EasyWindow*);
	};

	template<typename C, typename R>
	class InstanceCaller : public Caller<R>
	{
	public:
		InstanceCaller(C* pThis, R(C::*pMemberPtr)(const EasyWindow*))
		{
			m_pThis = pThis;
			m_pMemberPtr = pMemberPtr;
		}
		virtual R					Call(const EasyWindow* pWindow)
		{
			return (m_pThis->*m_pMemberPtr)(pWindow);
		}
		R(C::*m_pMemberPtr)(const EasyWindow*);
		C* m_pThis;
	};

	//One args
	template<typename T1, typename R>
	class CallerOneArg
	{
	public:
		virtual ~CallerOneArg() {}
		virtual R					Call(const EasyWindow* pWindow, const T1& oT1) = 0;
	};

	template<typename T1, typename R>
	class FunctionCallerOneArg : public CallerOneArg<T1, R>
	{
	public:
		FunctionCallerOneArg(R(*pFunctionPtr)(const EasyWindow*, T1))
		{
			m_pFunctionPtr = pFunctionPtr;
		}
		virtual R					Call(const EasyWindow* pWindow, const T1& oT1)
		{
			return m_pFunctionPtr(pWindow, oT1);
		}
		R(*m_pFunctionPtr)(const EasyWindow*, T1);
	};

	template<typename C, typename T1, typename R>
	class InstanceCallerOneArg : public CallerOneArg<T1, R>
	{
	public:
		InstanceCallerOneArg(C* pThis, R(C::*pMemberPtr)(const EasyWindow*, T1))
		{
			m_pThis = pThis;
			m_pMemberPtr = pMemberPtr;
			m_pMemberPtrConstRef = NULL;
		}
		InstanceCallerOneArg(C* pThis, R(C::*pMemberPtrConstRef)(const EasyWindow*, const T1&))
		{
			m_pThis = pThis;
			m_pMemberPtr = NULL;
			m_pMemberPtrConstRef = pMemberPtrConstRef;
		}
		virtual R					Call(const EasyWindow* pWindow, const T1& oT1)
		{
			if (m_pMemberPtr != NULL)
				return (m_pThis->*m_pMemberPtr)(pWindow, oT1);
			return (m_pThis->*m_pMemberPtrConstRef)(pWindow, oT1);
		}
		R(C::*m_pMemberPtr)(const EasyWindow*, T1);
		R(C::*m_pMemberPtrConstRef)(const EasyWindow*, const T1&);
		C* m_pThis;
	};

	//Two args
	template<typename T1, typename T2, typename R>
	class CallerTwoArg
	{
	public:
		virtual ~CallerTwoArg(){}
		virtual R					Call(const EasyWindow* pWindow, const T1& oT1, const T2& oT2) = 0;
	};

	template<typename T1, typename T2, typename R>
	class FunctionCallerTwoArg : public CallerTwoArg<T1, T2, R>
	{
	public:
		FunctionCallerTwoArg(R(*pFunctionPtr)(const EasyWindow*, T1, T2))
		{
			m_pFunctionPtr = pFunctionPtr;
		}
		virtual R					Call(const EasyWindow* pWindow, const T1& oT1, const T2& oT2)
		{
			return m_pFunctionPtr(pWindow, oT1, oT2);
		}
		R(*m_pFunctionPtr)(const EasyWindow*, T1, T2);
	};

	template<typename C, typename T1, typename T2, typename R>
	class InstanceCallerTwoArg : public CallerTwoArg<T1, T2, R>
	{
	public:
		InstanceCallerTwoArg(C* pThis, R(C::*pMemberPtr)(const EasyWindow*, T1, T2))
		{
			m_pThis = pThis;
			m_pMemberPtr = pMemberPtr;
		}
		virtual R					Call(const EasyWindow* pWindow, const T1& oT1, const T2& oT2)
		{
			return (m_pThis->*m_pMemberPtr)(pWindow, oT1, oT2);
		}
		R(C::*m_pMemberPtr)(const EasyWindow*, T1, T2);
		C* m_pThis;
	};

	//Callbacks
	template<typename R>
	class Callback
	{
	public:
		Callback()
		{
			m_pCaller = 0;
		}
		~Callback()
		{
			if (0 != m_pCaller)
				delete m_pCaller;
		}

		bool							IsSet() const
		{
			return m_pCaller != 0;
		}

		void							Set(R(*pFuncPtr)(const EasyWindow* pWindow))
		{
			if (0 != m_pCaller)
				delete m_pCaller;

			if (pFuncPtr != 0)
				m_pCaller = new FunctionCaller<R>(pFuncPtr);
			else
				m_pCaller = 0;
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtr)(const EasyWindow*))
		{
			if (0 != m_pCaller)
				delete m_pCaller;

			if (0 != pThis && 0 != pMemberPtr)
				m_pCaller = new InstanceCaller<C, R>(pThis, pMemberPtr);
			else
				m_pCaller = 0;
		}

		R								operator()(const EasyWindow* pWindow)
		{
			if (0 != m_pCaller)
				return m_pCaller->Call(pWindow);
			return R();
		}
	protected:
		Caller<R>*						m_pCaller;
	};

	template<typename T1, typename R>
	class CallbackOneArg
	{
	public:
		CallbackOneArg()
		{
			m_pCaller = 0;
		}
		~CallbackOneArg()
		{
			if (0 != m_pCaller)
				delete m_pCaller;
		}

		bool							IsSet() const
		{
			return m_pCaller != 0;
		}

		void							Set(R(*pFuncPtr)(const EasyWindow*, T1))
		{
			if (0 != m_pCaller)
				delete m_pCaller;

			if (pFuncPtr != 0)
				m_pCaller = new FunctionCallerOneArg<T1, R>(pFuncPtr);
			else
				m_pCaller = 0;
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtr)(const EasyWindow*, T1))
		{
			if (NULL != m_pCaller)
				delete m_pCaller;
			if (0 != pThis && 0 != pMemberPtr)
				m_pCaller = new InstanceCallerOneArg<C, T1, R>(pThis, pMemberPtr);
			else
				m_pCaller = 0;
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtrConstRef)(const EasyWindow*, const T1&))
		{
			if (NULL != m_pCaller)
				delete m_pCaller;

			if (0 != pThis && 0 != pMemberPtrConstRef)
				m_pCaller = new InstanceCallerOneArg<C, T1, R>(pThis, pMemberPtrConstRef);
			else
				m_pCaller = 0;
		}

		R								operator()(const EasyWindow* pWindow, const T1& oT1)
		{
			if (0 != m_pCaller)
				return m_pCaller->Call(pWindow, oT1);
			return R();
		}
	protected:
		CallerOneArg<T1, R>*			m_pCaller;
	};

	template<typename T1, typename T2, typename R>
	class CallbackTwoArg
	{
	public:
		CallbackTwoArg()
		{
			m_pCaller = 0;
		}
		~CallbackTwoArg()
		{
			if (0 != m_pCaller)
				delete m_pCaller;
		}

		bool							IsSet() const
		{
			return m_pCaller != 0;
		}

		void							Set(R(*pFuncPtr)(const EasyWindow*, T1, T2))
		{
			if (0 != m_pCaller)
				delete m_pCaller;
			if (pFuncPtr != 0)
				m_pCaller = new FunctionCallerTwoArg<T1, T2, R>(pFuncPtr);
			else
				m_pCaller = 0;
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtr)(const EasyWindow*, T1, T2))
		{
			if (NULL != m_pCaller)
				delete m_pCaller;

			if (0 != pThis && 0 != pMemberPtr)
				m_pCaller = new InstanceCallerTwoArg<C, T1, T2, R>(pThis, pMemberPtr);
			else
				m_pCaller = 0;
		}

		R								operator()(const EasyWindow* pWindow, const T1& oT1, const T2& oT2)
		{
			if (0 != m_pCaller)
				return m_pCaller->Call(pWindow, oT1, oT2);
			return R();
		}
	protected:
		CallerTwoArg<T1, T2, R>*		m_pCaller;
	};

	// Enums and structs

	enum EKey
	{
		KEY_NONE = 0,
		KEY_ESC,
		KEY_RETURN,
		KEY_TAB,
		KEY_SPACE,
		KEY_BACKSPACE,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_INSERT,
		KEY_DELETE,
		KEY_HOME,
		KEY_END,
		KEY_PAGEUP,
		KEY_PAGEDOWN,
		KEY_PRINT,
		KEY_PLUS,
		KEY_MINUS,
		KEY_LEFTBRACKET,
		KEY_RIGHTBRACKET,
		KEY_SEMICOLON,
		KEY_QUOTE,
		KEY_COMMA,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_BACKSLASH,
		KEY_TILDE,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_NUMPAD0,
		KEY_NUMPAD1,
		KEY_NUMPAD2,
		KEY_NUMPAD3,
		KEY_NUMPAD4,
		KEY_NUMPAD5,
		KEY_NUMPAD6,
		KEY_NUMPAD7,
		KEY_NUMPAD8,
		KEY_NUMPAD9,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,

		// Modifiers
		KEY_ALT,
		KEY_LEFTALT,
		KEY_RIGHTALT,
		KEY_CTRL,
		KEY_LEFTCTRL,
		KEY_RIGHTCTRL,
		KEY_SHIFT,
		KEY_LEFTSHIFT,
		KEY_RIGHTSHIFT,
		KEY_META,
		KEY_LEFTMETA,
		KEY_RIGHTMETA,
	};

	enum EWindowStyle
	{
		E_STYLE_NORMAL,
		E_STYLE_BORDERLESS,
		E_STYLE_BORDERLESS_RESIZABLE,
		E_STYLE_POPUP,
	};

	enum EWindowFlag
	{
		E_FLAG_NONE								= 0,
		E_FLAG_OWN_DC							= (1 << 0),
		E_FLAG_ACCEPT_FILES_DROP				= (1 << 1),
		E_FLAG_CATCH_ALT_KEY					= (1 << 2),
		E_FLAG_ALWAYS_CAPTURE_MOUSE_ON_CLICK	= (1 << 3)
	};
	typedef int EWindowFlags;

	enum ECursor
	{
		E_CURSOR_NONE,
		E_CURSOR_ARROW,
		E_CURSOR_TEXT_INPUT,
		E_CURSOR_HAND,
		E_CURSOR_RESIZE_NS,
		E_CURSOR_RESIZE_EW,
		E_CURSOR_RESIZE_NESW,
		E_CURSOR_RESIZE_NWSE
	};

	enum EEventFlag
	{
		E_EVENT_NONE							= 0,
		E_EVENT_CLOSED							= (1 << 0),
		E_EVENT_MOVED							= (1 << 1),
		E_EVENT_SIZED							= (1 << 2),
		E_EVENT_MAXIMIZED						= (1 << 3),
		E_EVENT_MINIMIZED						= (1 << 4),
		E_EVENT_RESTORED						= (1 << 5),
		E_EVENT_FOCUSED							= (1 << 6),
		E_EVENT_UNFOCUSED						= (1 << 7),
		E_EVENT_MOUSE_MOVED						= (1 << 8),
		E_EVENT_MOUSE_WHEEL						= (1 << 9),
		E_EVENT_MOUSE_BUTTON_DOWN				= (1 << 10),
		E_EVENT_MOUSE_BUTTON_UP					= (1 << 11),
		E_EVENT_KEY_DOWN						= (1 << 12),
		E_EVENT_KEY_UP							= (1 << 13),
		E_EVENT_CHAR							= (1 << 14),
		E_EVENT_FILES_DROPPED					= (1 << 15),
		E_EVENT_PAINT							= (1 << 16)
	};
	typedef unsigned long EEventFlags;

	enum EHoveredArea
	{
		E_HOVEREDAREA_NONE,
		E_HOVEREDAREA_MENU,
		E_HOVEREDAREA_CAPTION,
		E_HOVEREDAREA_MINIMIZE,
		E_HOVEREDAREA_MAXIMIZE,
		E_HOVEREDAREA_CLOSE
	};

	struct Point
	{
		int								x;
		int								y;
	};

	struct DropFiles
	{
		int								iCount;
		char**							pFiles;
		Point							oPosition;
	};

	// Static functions

	static EasyWindow*					Create(const char* pTitle, int iWidth, int iHeight, bool bClientSize, EasyWindow* pParent = 0, EWindowStyle eStyle = E_STYLE_NORMAL, EWindowFlags eFlags = E_FLAG_NONE);
	static const char*					KeyToString(EKey eKey);
	static EKey							StringToKey(const char* pString);
	static bool							IsModifierKey(EKey eKey);
	static bool							GetExtendedKeys(EKey eKey, EKey* pOutKey1, EKey* pOutKey2);
	static EKey							GetOriginalKey(EKey eKey);

	// Members

	virtual								~EasyWindow() {};

	virtual bool						Update() = 0;
	virtual EEventFlags					GetLastEvents() = 0;

	virtual void						Show(bool bShow = true) = 0;

	virtual bool						IsFocused() const = 0;
	virtual void						SetFocused() = 0;

	virtual void						SetSize(int iWidth, int iHeight, bool bClientSize) = 0;
	virtual void						SetPosition(int iPosX, int iPosY, bool bClientPos) = 0;
	virtual void						SetMaximized(bool bMaximized) = 0;
	virtual void						SetMinimized(bool bMinimized) = 0;
	virtual void						SetTitle(const char* pTitle) = 0;
	virtual void						SetAlpha(unsigned char iAlpha) = 0;
	virtual void						SetCursor(ECursor eCursorStyle) = 0;

	virtual void						GetSize(int* iWidth, int* iHeight) const = 0;
	virtual void						GetClientSize(int* iWidth, int* iHeight) const = 0;
	virtual void						GetPosition(int* iX, int* iY) const = 0;
	virtual void						GetClientPosition(int* iX, int* iY) const = 0;
	virtual bool						IsMaximized() const = 0;
	virtual bool						IsMinimized() const = 0;

	virtual bool						IsKeyCtrlDown() = 0;
	virtual bool						IsKeyAltDown() = 0;
	virtual bool						IsKeyShiftDown() = 0;

	virtual void*						GetHandle() = 0;

	// Events

	/* int Width, int Height */
	CallbackTwoArg<int, int, void>		OnSize;
	/* int PosX, int PosY */
	CallbackTwoArg<int, int, void>		OnMove;
	Callback<void>						OnMaximize;
	Callback<void>						OnMinimize;
	Callback<void>						OnRestore;
	/* bool HasFocus */
	CallbackOneArg<bool, void>			OnFocus;
	/* return bool AbortClosing */
	Callback<bool>						OnClose;

	/* int Button, bool IsDown */
	CallbackTwoArg<int, bool, void>		OnMouseButton;
	/* int PosX, int PosY */
	CallbackTwoArg<int, int, void>		OnMouseMove;
	/* int wheel step */
	CallbackOneArg<float, void>			OnMouseWheel;

	/* int Key, bool IsDown */
	CallbackTwoArg<EKey, bool, void>	OnKey;
	/* int Char */
	CallbackOneArg<unsigned long, void>	OnChar;

	/* int FileCount, char** Files */
	CallbackOneArg<DropFiles, void>		OnDropFiles;


	CallbackTwoArg<int, int, EHoveredArea>	BorderlessHoveredArea;
};

#endif //__EASY_WINDOW_H__