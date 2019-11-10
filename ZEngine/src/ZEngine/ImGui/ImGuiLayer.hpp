#pragma once

#include "ZEngine/Core/Layer.hpp"

namespace ZEngine {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() override;

		virtual void onAttach() override;
		virtual void onDetach() override;

		virtual void onImGuiRender() override;

		void begin();
		void end();
	};

}
