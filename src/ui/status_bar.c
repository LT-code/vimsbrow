#include "ui/entry.h"

static void enter_callback(GtkWidget *widget, GtkWidget *entry) {
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

static GtkWidget* init_input(GtkWidget* hbox) {
    GtkEntryBuffer *p_buffer = gtk_entry_buffer_new(NULL, -1);
    GtkWidget* entry = gtk_entry_new_with_buffer(p_buffer);
    gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 0);
    set_entry_css(entry);
    gtk_widget_grab_focus(entry);
    return entry;
}

GtkWidget* init_status_bar(GtkWidget *box) {
  GtkWidget *status_bar;
  status_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_size_request(status_bar, 0, 15);
  set_css(status_bar);
  gtk_widget_set_hexpand(status_bar, TRUE);
  gtk_widget_set_vexpand(status_bar, FALSE);
  gtk_container_add(GTK_CONTAINER(box), status_bar);

  return init_input(status_bar);
}
