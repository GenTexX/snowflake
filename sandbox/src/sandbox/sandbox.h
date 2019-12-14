#pragma once
#include "application/application.h"
#include "logging/log.h"
#include "window/window.h"

class Sandbox : public SF::Application
{

private:
	SF::Window* m_ApplicationWindow;

public:
	Sandbox();
	~Sandbox();

	void init() override;
	void run() override;

};

