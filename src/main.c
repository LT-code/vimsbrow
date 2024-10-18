// CEF C API example
// Project website: https://github.com/cztomczak/cefcapi

#include <glib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>
#include <gdk/gdkx.h>

//#include "ui/ui.h"

// #include "capi/cef_base.h"
#include "capi/cef_app.h"
#include "capi/cef_browser.h"
#include "capi/cef_client.h"
#include "include/capi/cef_browser_capi.h"

// #include "capi/cef_life_span_handler.h"

// Globals
cef_life_span_handler_t g_life_span_handler; // not used currently
cef_display_handler_t g_display_handler;
cef_render_handler_t g_render_handler;
cef_keyboard_handler_t g_keyboard_handler;
cef_permission_handler_t g_permssion_handler;
cef_browser_t* g_browser;
cef_focus_handler_t g_focus_handler;

// Signatures
int x11_error_handler(Display *display, XErrorEvent *event);
int x11_io_error_handler(Display *display);

int main(int argc, char **argv) {
  // This executable is called many times, because it
  // is also used for subprocesses. Let's print args
  // so we can differentiate between main process and
  // subprocesses. If one of the first args is for
  // example "--type=renderer" then it means that
  // this is a Renderer process. There may be more
  // subprocesses like GPU (--type=gpu-process) and
  // others. On Linux there are also special Zygote
  // processes.
  printf("\nProcess args: ");
  if (argc == 1) {
    printf("none (Main process)");
  } else {
    for (int i = 1; i < argc; i++) {
      if (strlen(argv[i]) > 128)
        printf("... ");
      else
        printf("%s ", argv[i]);
    }
  }
  printf("\n\n");

  // Main args.
  cef_main_args_t main_args = {};
  main_args.argc = argc;
  main_args.argv = argv;

  cef_app_t app = {};
  initialize_cef_app(&app);

  // Execute subprocesses. It is also possible to have
  // a separate executable for subprocesses by setting
  // cef_settings_t.browser_subprocess_path. In such
  // case cef_execute_process should not be called here.
  printf("cef_execute_process, argc=%d\n", argc);
  int code = cef_execute_process(&main_args, &app, NULL);
  if (code >= 0) {
    _exit(code);
  }

  // Application settings. It is mandatory to set the
  // "size" member.
  cef_settings_t settings = {};
  settings.size = sizeof(cef_settings_t);
  settings.log_severity = -1; // Show only warnings/errors
  settings.no_sandbox = 0;
  //settings.disable_signal_handlers
  //settings.windowless_rendering_enabled = 1;

  char root_cache_path[] = "/home/retzs64/.cache/cef_user_data/cache/";
  cef_string_t cef_root_cache_path = {};
  cef_string_utf8_to_utf16(root_cache_path, strlen(root_cache_path), &cef_root_cache_path);
  settings.root_cache_path = cef_root_cache_path;

  char cache_path[] = "/home/retzs64/.cache/cef_user_data/cache/cache_path/";
  cef_string_t cef_cache_path = {};
  cef_string_utf8_to_utf16(cache_path, strlen(cache_path), &cef_cache_path);
  settings.cache_path = cef_cache_path;

  char log_file[] = "/home/retzs64/.cache/cef_user_data/test.log";
  cef_string_t cef_log_file = {};
  cef_string_utf8_to_utf16(log_file, strlen(log_file), &cef_log_file);
  settings.log_file = cef_log_file;
  //settings.chrome_runtime = true;

  // Initialize CEF.
  printf("cef_initialize\n");
  cef_initialize(&main_args, &settings, &app, NULL);

  // Create GTK window. Alternatively you can pass a NULL handle
  // to CEF and then it will create a window of its own.
  // When passing NULL you have to implement cef_life_span_handler_t
  // and call cef_quit_message_loop from the on_before_close
  // callback. Example initialization of this handler and its
  // callback is Windows example.
  initialize_gtk();
  cef_window_info_t window_info = {};
  window_info.parent_window = create_gtk_window("cefcapi example", 800, 600);

  //GtkWidget* button = gtk_button_new_with_label("Button 1");
  //gtk_box_pack_start(GTK_BOX(gtk_window), button, TRUE, TRUE, 0);
  // Copied from upstream cefclient. Install xlib error
  // handlers so that the application won't be terminated on
  // non-fatal errors. Must be done after initializing GTK.
  XSetErrorHandler(x11_error_handler);
  XSetIOErrorHandler(x11_io_error_handler);

  // Initial url
  //char url[] = "https://bitmovin.com/demos/drm";
  //char url[] = "https://jsbenchmark.com/";
  char url[] = "https://duckduckgo.com";
  //char url[] = "https://europixhd.site/tv/tt0212671-s7#vidbox";
  cef_string_t cef_url = {};
  cef_string_utf8_to_utf16(url, strlen(url), &cef_url);

  // Browser settings. It is mandatory to set the
  // "size" member.
  cef_browser_settings_t browser_settings = {};
  browser_settings.size = sizeof(cef_browser_settings_t);
  //browser_settings.javascript_dom_paste 
  printf("===================================");

  // Client handler and its callbacks
  cef_client_t client = {};
  initialize_cef_client(&client);

  // Create browser asynchronously. There is also a
  // synchronous version of this function available.
  g_browser = cef_browser_host_create_browser_sync(
      &window_info, &client, &cef_url, &browser_settings, NULL, NULL);

  initialize_cef_browser(g_browser);

  // Message loop. There is also cef_do_message_loop_work()
  // that allow for integrating with existing message loops.
  printf("cef_run_message_loop\n");
  cef_run_message_loop();

  // Shutdown CEF
  printf("cef_shutdown\n");
  cef_shutdown();

  return 0;
}

int x11_error_handler(Display *display, XErrorEvent *event) {
  printf("X11 error: type=%d, serial=%lu, code=%d\n", event->type,
         event->serial, (int)event->error_code);
  return 0;
}

int x11_io_error_handler(Display *display) { return 0; }
