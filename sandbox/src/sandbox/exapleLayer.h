#pragma once
#include "snowflake/layer/layer.h"
#include "snowflake/event/event.h"
#include "snowflake/time/timestep.h"

class ExampleLayer : public SF::Layer {


public:
	ExampleLayer() {}
	~ExampleLayer() {}

	virtual void onAttach() {}
	virtual void onDetach() {}

	virtual void onEvent(SF::Event& e) {
	
		SF_TRACE("ExampleLayer" + e.toString());
		e.m_Handled = true;
	
	};
	virtual void onUpdate() {
		
		SF_TRACE("update ExampleLayer");
	
	}
	virtual void onImGuiRender() {}

};