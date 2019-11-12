#pragma once

namespace ZEngine {

	class Input
	{
	public:
		static inline bool IsKeyPressed(int keycode) { return s_pInstance->IsKeyPressedImpl(keycode); }
		static inline bool IsMouseButtonPressed(int button) { return s_pInstance->IsMouseButtonPressedImpl(button); }
		static inline std::pair<float, float> GetMousePosition() { return s_pInstance->GetMousePositionImpl(); }
		static inline float GetMouseX() { return s_pInstance->GetMouseXImpl(); }
		static inline float GetMouseY() { return s_pInstance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_pInstance;
	};

}
