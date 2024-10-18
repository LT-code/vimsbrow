#include "include/capi/cef_browser_capi.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>


  cef_window_handle_t(CEF_CALLBACK* get_opener_window_handle)(
      struct _cef_browser_host_t* self);

void initialize_cef_browser(cef_browser_t* browser) {
  cef_browser_host_t* host = browser->get_host(browser);
  //host->set_focus(host, 1);
  //cef_window_info_t info;
  //cef_browser_settings_t settings;
  //cef_point_t point;
  //host->show_dev_tools(host,&info,NULL,&settings, &point);
}
