#pragma once
#include <GL/glew.h>
#include "snowflake/application/application.h"
#include "snowflake/event/event.h"
#include "snowflake/event/inputevent.h"
#include "snowflake/event/windowevent.h"
#include "snowflake/event/keycode.h"
#include "snowflake/imgui/imGuiLayer.h"
#include "snowflake/imgui/imGuiWindow.h"
#include "snowflake/input/input.h"
#include "snowflake/layer/layer.h"
#include "snowflake/layer/layerStack.h"
#include "snowflake/logging/log.h"
#include "snowflake/renderer/buffer.h"
#include "snowflake/renderer/shader.h"
#include "snowflake/renderer/camera.h"
#include "snowflake/renderer/vertexArray.h"
#include "snowflake/time/timestep.h"
#include "snowflake/window/window.h"
#include <imgui.h>

#define OPENGL