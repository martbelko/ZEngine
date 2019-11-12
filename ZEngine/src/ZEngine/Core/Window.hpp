#pragma once

#include "zpch.hpp"
#include "ZEngine/Events/Event.hpp"

namespace ZEngine {

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window() = default;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool enabled) = 0;
	public:
		static Window* Create(unsigned int width = 1280, unsigned height = 720, const std::string& title = "ZEngine");
	};

}
