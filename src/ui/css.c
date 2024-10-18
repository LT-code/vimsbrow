#include "ui/css.h"

static GtkTextBuffer* bufferLog;
static GtkCssProvider* cssProviderLog;
static GtkStyleContext* context;

gboolean wndDeleteEventHandler(__attribute__((unused)) GtkWidget* widget,
                                __attribute__((unused)) GdkEvent* event,
                                __attribute__((unused)) gpointer user_data)
{
    gtk_main_quit();
    
    return TRUE;
}

void set_css(GtkWidget* layoutGrid) {
    // g_signal_connect(window, "delete-event", G_CALLBACK(wndDeleteEventHandler), NULL);


    //gtk_widget_set_name(layoutGrid, "");
    cssProviderLog = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProviderLog,
                                    "box {"
                                    "background-color: black;"
                                    "}",-1, NULL);
    context = gtk_widget_get_style_context(layoutGrid);
    gtk_style_context_add_provider(context,
                                GTK_STYLE_PROVIDER(cssProviderLog),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void set_entry_css(GtkWidget* entry) {
    cssProviderLog = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProviderLog,
                                    "entry {"
                                    "   font: 13px Sans;"
                                    "   min-height: 0px;"
                                    "   margin-left: 2px;"
                                    "   padding-left: 2px;"
                                    "   border: 1px solid black;"
                                    "   background-color: black;"
                                    "   color: white;"
                                    "   border-radius: 0px;"
                                    "   box-shadow: 0px 0px 0px rgba(0, 0, 0, 0);"
                                    "   caret-color: white;"
                                    "}"
                                    "entry:hover {"
                                    "   border-color: black;"
                                    "}"
                                    "entry:focus {"
                                    "   border-color: black;"
                                    "}",-1, NULL);
    context = gtk_widget_get_style_context(entry);
    gtk_style_context_add_provider(context,
                                GTK_STYLE_PROVIDER(cssProviderLog),
                                GTK_STYLE_PROVIDER_PRIORITY_USER);
}
