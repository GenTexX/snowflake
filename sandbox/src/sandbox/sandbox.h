#pragma once
#include "application/application.h"
#include "logging/log.h"
class Sandbox : public SF::Application
{

private:

public:
	Sandbox();
	~Sandbox();

	void init() override;
	void run() override;

};

