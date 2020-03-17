#pragma once
#include "opengl/openGLBuffer.h"
#include "opengl/openGLShader.h"
#include "opengl/openGLVertexArray.h"
#include "snowflake/logging/log.h"
#include "snowflake/application/application.h"
#include "snowflake/window/window.h"
#include "snowflake/event/event.h"
#include "exapleLayer.h"


class Sandbox : public SF::Application
{

private:


public:
	Sandbox();
	~Sandbox();

	void onEvent(SF::Event& e) override;

	void init() override;
	void run() override;

};

