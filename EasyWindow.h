#ifndef __EASY_WINDOW_H__
#define __EASY_WINDOW_H__

class EasyWindow
{
public:
	//Callbacks

	template<typename R>
	class Callback
	{
		class Caller
		{
		public:
			virtual R					Call() = 0;
		};

		class FunctionCall : public Caller
		{
		public:
			FunctionCall(R(*pFunctionPtr)())
			{
				m_pFunctionPtr = pFunctionPtr;
			}
			virtual R					Call()
			{
				return m_pFunctionPtr();
			}
			R(*m_pFunctionPtr)();
		};

		template<typename C>
		class InstanceCall : public Caller
		{
		public:
			InstanceCall(C* pThis, R(C::*pMemberPtr)())
			{
				m_pThis = pThis;
				m_pMemberPtr = pMemberPtr;
			}
			virtual R					Call()
			{
				return (m_pThis->*m_pMemberPtr)();
			}
			R(C::*m_pMemberPtr)();
			C* m_pThis;
		};
	public:
		Callback()
		{
			m_pCaller = 0;
		}
		~Callback()
		{
			if (0 != m_pCaller) delete m_pCaller;
		}
		void							Set(R(*pFuncPtr)())
		{
			if (0 != m_pCaller) delete m_pCaller;
			m_pCaller = new FunctionCall(pFuncPtr);
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtr)())
		{
			if (0 != m_pCaller) delete m_pCaller;
			m_pCaller = new InstanceCall<C>(pThis, pMemberPtr);
		}

		R								operator()()
		{
			if (0 != m_pCaller) return m_pCaller->Call();
			return R();
		}
	protected:
		Caller*							m_pCaller;
	};

	template<typename T1, typename R>
	class CallbackOneArg
	{
		class Caller
		{
		public:
			virtual R					Call(const T1& oT1) = 0;
		};

		class FunctionCall : public Caller
		{
		public:
			FunctionCall(R(*pFunctionPtr)(const T1&))
			{
				m_pFunctionPtr = pFunctionPtr;
			}
			virtual R					Call(const T1& oT1)
			{
				return m_pFunctionPtr(oT1);
			}
			R(*m_pFunctionPtr)(const T1&);
		};

		template<typename C>
		class InstanceCall : public Caller
		{
		public:
			InstanceCall(C* pThis, R(C::*pMemberPtr)(T1))
			{
				m_pThis = pThis;
				m_pMemberPtr = pMemberPtr;
			}
			virtual R					Call(const T1& oT1)
			{
				return (m_pThis->*m_pMemberPtr)(oT1);
			}
			R(C::*m_pMemberPtr)(T1);
			C* m_pThis;
		};

		template<typename C>
		class InstanceCallConstRef : public Caller
		{
		public:
			InstanceCallConstRef(C* pThis, R(C::*pMemberPtr)(const T1&))
			{
				m_pThis = pThis;
				m_pMemberPtr = pMemberPtr;
			}
			virtual R					Call(const T1& oT1)
			{
				return (m_pThis->*m_pMemberPtr)(oT1);
			}
			R(C::*m_pMemberPtr)(const T1&);
			C* m_pThis;
		};
	public:
		CallbackOneArg()
		{
			m_pCaller = 0;
		}
		~CallbackOneArg()
		{
			if (0 != m_pCaller) delete m_pCaller;
		}
		void							Set(R(*pFuncPtr)(T1))
		{
			if (0 != m_pCaller) delete m_pCaller;
			m_pCaller = new FunctionCall(pFuncPtr);
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtr)(T1))
		{
			if (NULL != m_pCaller) delete m_pCaller;
			m_pCaller = new InstanceCall<C>(pThis, pMemberPtr);
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtr)(const T1&))
		{
			if (NULL != m_pCaller) delete m_pCaller;
			m_pCaller = new InstanceCallConstRef<C>(pThis, pMemberPtr);
		}

		R								operator()(const T1& oT1)
		{
			if (0 != m_pCaller) return m_pCaller->Call(oT1);
			return R();
		}
	protected:
		Caller*							m_pCaller;
	};

	template<typename T1, typename T2, typename R>
	class CallbackTwoArg
	{
		class Caller
		{
		public:
			virtual R					Call(const T1& oT1, const T2& oT2) = 0;
		};

		class FunctionCall : public Caller
		{
		public:
			FunctionCall(R(*pFunctionPtr)(T1, T2))
			{
				m_pFunctionPtr = pFunctionPtr;
			}
			virtual R					Call(const T1& oT1, const T2& oT2)
			{
				return m_pFunctionPtr(oT1, oT2);
			}
			R(*m_pFunctionPtr)(T1, T2);
		};

		template<typename C>
		class InstanceCall : public Caller
		{
		public:
			InstanceCall(C* pThis, R(C::*pMemberPtr)(T1, T2))
			{
				m_pThis = pThis;
				m_pMemberPtr = pMemberPtr;
			}
			virtual R					Call(const T1& oT1, const T2& oT2)
			{
				return (m_pThis->*m_pMemberPtr)(oT1, oT2);
			}
			R(C::*m_pMemberPtr)(T1, T2);
			C* m_pThis;
		};

		template<typename C>
		class InstanceCallConstRef : public Caller
		{
		public:
			InstanceCallConstRef(C* pThis, R(C::*pMemberPtr)(T1, T2))
			{
				m_pThis = pThis;
				m_pMemberPtr = pMemberPtr;
			}
			virtual R					Call(const T1& oT1, const T2& oT2)
			{
				return (m_pThis->*m_pMemberPtr)(oT1, oT2);
			}
			R(C::*m_pMemberPtr)(T1, T2);
			C* m_pThis;
		};
	public:
		CallbackTwoArg()
		{
			m_pCaller = 0;
		}
		~CallbackTwoArg()
		{
			if (0 != m_pCaller) delete m_pCaller;
		}
		void							Set(R(*pFuncPtr)(T1, T2))
		{
			if (0 != m_pCaller) delete m_pCaller;
			m_pCaller = new FunctionCall(pFuncPtr);
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtr)(T1, T2))
		{
			if (NULL != m_pCaller) delete m_pCaller;
			m_pCaller = new InstanceCall<C>(pThis, pMemberPtr);
		}

		template<typename C>
		void							Set(C* pThis, R(C::*pMemberPtr)(const T1&, const T2&))
		{
			if (NULL != m_pCaller) delete m_pCaller;
			m_pCaller = new InstanceCallConstRef<C>(pThis, pMemberPtr);
		}

		R								operator()(const T1& oT1, const T2& oT2)
		{
			if (0 != m_pCaller) return m_pCaller->Call(oT1, oT2);
			return R();
		}
	protected:
		Caller*	m_pCaller;
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
		E_FLAG_NONE						= 0,
		E_FLAG_OWN_DC					= 1,
		E_FLAG_ACCEPT_FILES_DROP		= 2
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
	CallbackOneArg<int, void>			OnMouseWheel;

	/* int Key, bool IsDown */
	CallbackTwoArg<EKey, bool, void>	OnKey;
	/* int Char */
	CallbackOneArg<int, void>			OnChar;

	/* int FileCount, char** Files */
	CallbackOneArg<DropFiles, void>		OnDropFiles;
};

#endif //__EASY_WINDOW_H__