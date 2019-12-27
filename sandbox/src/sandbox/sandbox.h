#pragma once
#include "logging/log.h"
#include"application/application.h"
#include "window/window.h"
#include "event/event.h"

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

