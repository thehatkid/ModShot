#include "notifications.h"
#include "etc.h"
#include "sharedstate.h"
#include "binding-util.h"
#include "binding-types.h"
#include "eventthread.h"
#include "debugwriter.h"

Notification notifi;

RB_METHOD(modshotNotify)
{
	RB_UNUSED_PARAM;
	char* title;
	char* info;
	VALUE icon = Qnil;
	rb_get_args(argc, argv, "zz|o", &title, &info, &icon RB_ARG_END);

#ifdef _WIN32
	if (!notifi.hasTrayIcon)
		notifi.addTrayIcon("OneShot");
#elif defined __linux__
	if (!notifi.hasGApp)
		notifi.regApp("org.ModShot.Notifier");
#endif

	switch (TYPE(icon))
	{
		case T_NIL:
			notifi.send(title, info, 0, NULL);
			break;
		case T_FIXNUM:
			notifi.send(title, info, NUM2INT(icon), NULL);
			break;
		case T_STRING:
		{
			std::string iconStr = std::string(RSTRING_PTR(icon), RSTRING_LEN(icon));
			notifi.send(title, info, 0, iconStr.c_str());
			break;
		}
		default:
			notifi.send(title, info, 0, NULL);
			break;
	}

	return Qnil;
}

RB_METHOD(modshotNotifyCleanup)
{
	RB_UNUSED_PARAM;

#ifdef _WIN32
	if (notifi.hasTrayIcon)
		notifi.delTrayIcon();
#elif defined __linux__
	if (notifi.hasGApp)
		notifi.quitApp();
#endif

	return Qnil;
}

void modshotBindingInit()
{
	VALUE module = rb_define_module("ModShot");

	// ModShot:: module functions
	_rb_define_module_function(module, "notify", modshotNotify);
	_rb_define_module_function(module, "notify_cleanup", modshotNotifyCleanup);
}
