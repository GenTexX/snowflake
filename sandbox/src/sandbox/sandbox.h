#pragma once
#include "snowflake/logging/log.h"
#include "snowflake/application/application.h"
#include "snowflake/window/window.h"
#include "snowflake/event/event.h"

class Sandbox : public SF::Application
{

private:
	SF::Window* m_ApplicationWindow;

public:
	Sandbox();
	~Sandbox();

	void onEvent(SF::Event& e) override;

	void init() override;
	void run() override;

};

