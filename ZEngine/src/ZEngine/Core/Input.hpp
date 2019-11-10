#pragma once

namespace ZEngine {

	class Input
	{
	public:
		static inline bool isKeyPressed(int keycode) { return s_pInstance->isKeyPressedImpl(keycode); }
		static inline bool isMouseButtonPressed(int button) { return s_pInstance->isMouseButtonPressedImpl(button); }
		static inline std::pair<float, float> getMousePosition() { return s_pInstance->getMousePositionImpl(); }
		static inline float getMouseX() { return s_pInstance->getMouseXImpl(); }
		static inline float getMouseY() { return s_pInstance->getMouseYImpl(); }
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
	private:
		static Input* s_pInstance;
	};

}
