#pragma once
#include "snowflake/entrypoint/entrypoint.h"
#include "snowflake/application/application.h"
#include "snowflake/event/event.h"
#include "snowflake/event/inputevent.h"
#include "snowflake/event/windowevent.h"
#include "snowflake/event/keycode.h"
#include "snowflake/input/input.h"
#include "snowflake/layer/layer.h"
#include "snowflake/layer/layerStack.h"
#include "snowflake/logging/log.h"
#include "snowflake/renderer/buffer.h"
#include "snowflake/time/timestep.h"
#include "snowflake/window/window.h"

#define OPENGL

#ifdef OPENGL
#include "opengl/openGLBuffer.h"
#include "opengl/openGLBuffer.h"
#endif