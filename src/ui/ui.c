// CEF C API example
// Project website: https://github.com/cztomczak/cefcapi

#include "ui/ui.h"
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <glib-object.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

extern cef_browser_t *g_browser;
static struct _mytest status_var;
//static struct _mytest status_var;

void app_terminate_signal(int signatl) {
  printf("app_terminate_signal\n");
  cef_quit_message_loop();
}

void initialize_gtk() {
  printf("initialize_gtk %u.%u.%u\n", gtk_get_major_version(),
         gtk_get_minor_version(), gtk_get_micro_version());
  gtk_init(0, NULL);
  signal(SIGINT, app_terminate_signal);
  signal(SIGTERM, app_terminate_signal);
}

void window_destroy_signal(GtkWidget *widget, gpointer data) {
  printf("window_destroy_signal\n");
  cef_quit_message_loop();
}

static void fix_default_x11_visual(GtkWidget *widget) {
#if GTK_CHECK_VERSION(3, 15, 1)
  // GTK+ > 3.15.1 uses an X11 visual optimized for GTK+'s OpenGL stuff
  // since revid dae447728d: https://github.com/GNOME/gtk/commit/dae447728d
  // However, it breaks CEF: https://github.com/cztomczak/cefcapi/issues/9
  // Let's use the default X11 visual instead of the GTK's blessed one.
  GdkScreen *screen = gdk_screen_get_default();
  GList *visuals = gdk_screen_list_visuals(screen);
  GdkX11Screen *x11_screen = GDK_X11_SCREEN(screen);
  g_return_if_fail(x11_screen != NULL);
  Visual *default_xvisual = DefaultVisual(GDK_SCREEN_XDISPLAY(x11_screen),
                                          GDK_SCREEN_XNUMBER(x11_screen));
  GList *cursor = visuals;
  while (cursor != NULL) {
    GdkVisual *visual = GDK_X11_VISUAL(cursor->data);
    if (default_xvisual->visualid ==
        gdk_x11_visual_get_xvisual(visual)->visualid) {
      gtk_widget_set_visual(widget, visual);
      break;
    }
    cursor = cursor->next;
  }
  g_list_free(visuals);
#endif
}

static gboolean on_configure_event(GtkWidget *widget, GdkRectangle *allocation,
                                   Display *display) {
  if (g_browser) {
    cef_browser_host_t *host = g_browser->get_host(g_browser);
    unsigned long host_handle = host->get_window_handle(host);

    XResizeWindow(display, host_handle, allocation->width, allocation->height);
    XMoveWindow(display, host_handle, allocation->x, allocation->y);
    XFlush(display);
  }

  return FALSE; // Propagate the event further
}


static gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data){
    printf("kkkkkeyyyyyyyyyyyyyy %i \n", event->keyval);

    switch(event->keyval) {
        case 65307:
          //if (data->status == 1) data->status = 0;
          //if (data->status == 0) data->status = 1;
        browser_get_focus();

            //printf("browser focus %i %i\n", gtk_widget_get_can_focus(data->global), data->status);
          //gtk_widget_grab_focus(data->global);
          return TRUE;
    }
    return FALSE;
}

void entry_set_focus() {
    status_var.status = 0;
    gtk_widget_show_all(status_var.entry);
}

void entry_get_focus() {
    XSetInputFocus(status_var.display, status_var.xid, 1, 0);
          cef_browser_host_t* host = g_browser->get_host(g_browser);
          host->set_focus(host, 0);
  printf("ennnnnnnnnnnttttttttttttrrrrrrrrrrrryyyyyyyyyyyyyyyyyyy %i\n", status_var.status);
    gtk_widget_get_can_focus(status_var.entry);
    gtk_widget_grab_focus(status_var.entry);
    gtk_entry_set_text(GTK_ENTRY(status_var.entry), ":");
    gtk_editable_set_position(GTK_EDITABLE(status_var.entry), -1);
    entry_set_focus();
}

void browser_set_focus() {
    status_var.status = 1;
    gtk_widget_hide(status_var.entry);
}

void browser_get_focus() {
    gtk_widget_get_can_focus(status_var.global);
    gtk_widget_grab_focus(status_var.global);
  printf("brrrrrrrrrrrrrrrrrrrrroooooooooooooooowwwwwwwwwwssssssssssserrrrrr %i\n", status_var.status);
    cef_browser_host_t* host = g_browser->get_host(g_browser);
    host->set_focus(host, 1);
    XSetInputFocus(status_var.display, host->get_window_handle(host), 1, 0);
    browser_set_focus();
}

int is_browser_can_focus() {
  return status_var.status;
}

//gboolean on_focus_in(GtkWidget *widget, GdkEventFocus *event, mytest* data) {
gboolean on_focus_in(GtkWidget *widget, GdkEventFocus *event, gpointer data) {
  printf("Widget gained focus %i\n", status_var.status);
  if (status_var.status) {
    //printf("hooo 2 %i\n", status_var.status);
    browser_get_focus();
  } else {
    //printf("hooo %i\n", status_var.status);
    entry_get_focus();
  }
    
  return FALSE;  // Propagate event further if necessary
}

gboolean on_focus_out(GtkWidget *widget, GdkEventFocus *event, gpointer data) {
    printf("Widget lost focus %i\n", status_var.status);
    gtk_widget_get_can_focus(status_var.global);
    gtk_widget_grab_focus(status_var.global);
  //if (data->status) {
  //        cef_browser_host_t* host = g_browser->get_host(g_browser);
  //        host->set_focus(host, 0);

  //} else {
  //  gtk_widget_get_can_focus(widget);
  //  gtk_widget_grab_focus(widget);
  //}
    
    return FALSE;  // Propagate event further if necessary
}

void on_mouse_enter(GtkWidget *widget, GdkEventFocus *event, GtkEntry *entry) {
  printf("7777777777777777777777777777777777777777777777777777 %i\n", event->type);
    //entry_get_focus(); // Set focus back to entry
}



Window create_gtk_window(char *title, int width, int height) {
  GtkWidget *window;
  GtkWidget *global_vbox;
  GtkWidget *cef_view_vbox;
  GtkWidget* entry;

  // Create window.
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Destroy signal.
  g_signal_connect(G_OBJECT(window), "destroy",
                   G_CALLBACK(window_destroy_signal), NULL);


  // Default size.
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);

  // Center.
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  // Title.
  gtk_window_set_title(GTK_WINDOW(window), title);

  // TODO: focus
  // g_signal_connect(window, "focus", G_CALLBACK(&HandleFocus), NULL);

  // CEF requires a container. Embedding browser in a top
  // level window fails.
  global_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  cef_view_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  gtk_container_add(GTK_CONTAINER(window), global_vbox);
  // gtk_container_add(GTK_CONTAINER(cef_view_vbox), global_vbox);
  gtk_box_pack_start(GTK_BOX(global_vbox), cef_view_vbox, TRUE, TRUE, 0);

  fix_default_x11_visual(GTK_WIDGET(window));

  gtk_window_set_resizable(GTK_WINDOW(window), TRUE);

  Display *display = GDK_DISPLAY_XDISPLAY(gdk_display_get_default());

  g_signal_connect(GTK_WIDGET(cef_view_vbox), "size-allocate",
                   G_CALLBACK(on_configure_event), display);


  entry = init_status_bar(global_vbox);
  //mytest* mytest = &widgets;
  //mytest->entry = entry;
  //mytest->display = display;
  //mytest->global = cef_view_vbox;
  //mytest->status = 0;
  status_var.entry = entry;
  status_var.display = display;
  status_var.global = cef_view_vbox;
  status_var.status = 0;
  printf("ffffffffffffffffffffff %i\n", status_var.status);
  g_signal_connect(window, "focus-in-event", G_CALLBACK(on_focus_in), NULL);
  g_signal_connect(window, "focus-out-event", G_CALLBACK(on_focus_out), NULL);
  g_signal_connect(G_OBJECT (entry), "key_press_event", G_CALLBACK(on_key_press), NULL);


  g_signal_connect(window, "enter-notify-event", G_CALLBACK(on_mouse_enter), entry);

  gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT (window), "key_press_event", G_CALLBACK(on_key_press), NULL);

  gtk_widget_show_all(window);
  gtk_widget_show_all(cef_view_vbox);

  // gtk_widget_hide(status_bar);

  Window xid = gdk_x11_window_get_xid(gtk_widget_get_window(cef_view_vbox));
  status_var.xid = xid;
  return xid;
}
