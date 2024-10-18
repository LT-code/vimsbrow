// CEF C API example
// Project website: https://github.com/cztomczak/cefcapi

#include <X11/X.h>
#include <X11/Xlib.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include "include/capi/cef_app_capi.h"
#include "ui/entry.h"
#include "ui/css.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

extern cef_browser_t *g_browser;

void app_terminate_signal(int signatl);

void initialize_gtk();

void window_destroy_signal(GtkWidget *widget, gpointer data);

GtkWidget* init_status_bar(GtkWidget *status_bar);

//gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data);

Window create_gtk_window(char *title, int width, int height);

void browser_set_focus();
void browser_get_focus();

void entry_set_focus();
void entry_get_focus();

int is_browser_can_focus();

typedef struct _mytest {
  Display* display;
  GtkWidget* entry;
  GtkWidget* global;
  Window xid;
  int status;
} mytest;
