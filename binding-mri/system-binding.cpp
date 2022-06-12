#include "oneshot.h"
#include "etc.h"
#include "sharedstate.h"
#include "binding-util.h"
#include "binding-types.h"
#include "eventthread.h"

#ifdef _WIN32
#include <windows.h>
#endif

RB_METHOD(GetScreenResolution) {
	SDL_DisplayMode displayMode;
	int di = SDL_GetWindowDisplayIndex(shState->rtData().window);
	SDL_GetCurrentDisplayMode(di, &displayMode);
	return rb_ary_new3(2, LONG2FIX(displayMode.w), LONG2FIX(displayMode.h));
}

void systemBindingInit()
{
    VALUE module = rb_define_module("System");
    _rb_define_module_function(module, "GetScreenResolution", GetScreenResolution);
}