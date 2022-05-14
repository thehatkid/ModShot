#include "oneshot.h"
#include "etc.h"
#include "sharedstate.h"
#include "binding-util.h"
#include "binding-types.h"
#include "eventthread.h"
#include "debugwriter.h"

#ifdef _WIN32
	#include <windows.h>
#endif

RB_METHOD(NotifySend)
{
	RB_UNUSED_PARAM;
    char* title;
    char* info;
    int uID = 0;
    rb_get_args(argc, argv, "zz|i", &title, &info, &uID);

#ifdef _WIN32
    if (!shState->oneshot().hasTrayIcon()) {
        shState->oneshot().addNotifyIcon("OneShot", uID);
    }

    shState->oneshot().sendBalloon(title, info);
#else
    // TODO: use GTK notification server!
    // https://wiki.archlinux.org/title/Desktop_notifications#Notification_servers
#endif

	return Qtrue;
}

void modshotBindingInit()
{
    VALUE modshot_module = rb_define_module("ModShot");
    _rb_define_module_function(modshot_module, "notify", NotifySend);
}
