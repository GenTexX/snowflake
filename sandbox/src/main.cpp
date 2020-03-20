#include "snowflake/entrypoint/entrypoint.h"
#include "snowflake.h"
#include "sandbox/sandbox.h"

SF::Application* getApplication() {

	return new Sandbox();

}