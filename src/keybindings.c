#include <gtk/gtk.h>
#include <stdio.h>
#include "keybindings.h"
#include "ui/ui.h"

int keybindings_on_pre_key_event(struct _cef_keyboard_handler_t* self,
                                    struct _cef_browser_t* browser,
                                    const cef_key_event_t* event,
                                    cef_event_handle_t os_event,
                                    int* is_keyboard_shortcut) {
  cef_key_event_t key_up;
  key_up.type = event->type;
  key_up.is_system_key = 0;
  key_up.character = '\0';
  key_up.modifiers = 0;


  if(!event->focus_on_editable_field) {
    cef_browser_host_t* host = browser->get_host(browser);
    switch (event->character) {
      case 'k':
        key_up.native_key_code = 111;
        key_up.windows_key_code = 38;
        host->send_key_event(host,&key_up);
        return 1;
      case 'j':
        key_up.native_key_code = 116;
        key_up.windows_key_code = 40;
        host->send_key_event(host,&key_up);
        return 1;
      case 'K':
        key_up.native_key_code = 112;
        key_up.windows_key_code = 33;
        host->send_key_event(host,&key_up);
        return 1;
      case 'J':
        key_up.native_key_code = 117;
        key_up.windows_key_code = 34;
        host->send_key_event(host,&key_up);
        return 1;
      case 'H':
        if(event->type == 2) {
          browser->go_back(browser);
        printf("goback\n");
          return 1;
        }
        break;
      case 'L':
        if(event->type == 2) {
          browser->go_forward(browser);
        printf("goforwardddd\n");
          return 1;
        }
        break;
      case ':':
        //gtk_widget_grab_focus(GTK_WIDGET(browser->get_host(browser)->get_window_handle(host)));
        entry_get_focus();
        return 1;
    }
  }


  if (event->type == KEYEVENT_RAWKEYDOWN && event->modifiers & EVENTFLAG_CONTROL_DOWN) {
      switch (event->native_key_code) {
        case 28: return 1; // Ctrl+t
        case 25: return 1; // Ctrl+w
        case 30: return 1; // Ctrl+u
      }
  }
  //printf("key pressed on_pre_key_event is_keyboard_shortcut %i focus_on_editable_field %i character %c  type %i is_system_key %i native_key_code %i unmodified_character %i modifiers %i windows_key_code %i \n", *is_keyboard_shortcut, event->focus_on_editable_field, event->character, (int)event->type, event->is_system_key, event->native_key_code, event->unmodified_character, event->modifiers, event->windows_key_code);
  return 0;
}

int keybindings_on_key_event(struct _cef_keyboard_handler_t* self,
                                  struct _cef_browser_t* browser,
                                  const cef_key_event_t* event,
                                  cef_event_handle_t os_event) {

  //printf("key pressed on_key_event %c %c %i %i \n", event->character, event->windows_key_code, event->modifiers, (int)event->type);
  return 0;
}

