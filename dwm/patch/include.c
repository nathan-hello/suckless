/* Bar functionality */
#include "bar_indicators.c"
#include "bar_tagicons.c"
#include "bar.c"

#include "bar_status.c"
#include "bar_tags.c"
#include "bar_wintitle.c"

/* Other patches */
#include "autostart.c"
#include "cmdcustomize.c"
#include "dwmc.c"
#include "focusmaster.c"
#include "games.c"
#include "ipc.c"
#ifdef VERSION
#include "ipc/IPCClient.c"
#include "ipc/yajl_dumps.c"
#include "ipc/ipc.c"
#include "ipc/util.c"
#endif
#include "movestack.c"
#include "restartsig.c"
#include "swallow.c"
#include "vanitygaps.c"
#include "fullscreen.c"
#include "xrdb.c"
/* Layouts */
#include "layout_facts.c"
#include "layout_monocle.c"
#include "layout_tile.c"

