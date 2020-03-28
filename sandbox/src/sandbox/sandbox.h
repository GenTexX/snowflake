#pragma once
#include "snowflake.h"


class Sandbox : public SF::Application
{

private:
	virtual void createWindow() override;
	SF::ImGuiLayer* m_ImGuiLayer = nullptr;

public:
	Sandbox();
	~Sandbox();

	void onEvent(SF::Event& e) override;

	void init() override;
	void run() override;

};

