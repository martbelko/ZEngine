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

		virtual void setEventCallback(const EventCallbackFn& callback) = 0;

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void* getNativeWindow() const = 0;

		virtual bool isVSync() const = 0;
		virtual void setVSync(bool enabled) = 0;
	public:
		static Window* create(unsigned int width = 1280, unsigned height = 720, const std::string& title = "ZEngine");
	};

}
