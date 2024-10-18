#include "include/capi/cef_client_capi.h"

int keybindings_on_pre_key_event(struct _cef_keyboard_handler_t* self,
                                    struct _cef_browser_t* browser,
                                    const cef_key_event_t* event,
                                    cef_event_handle_t os_event,
                                    int* is_keyboard_shortcut);

int keybindings_on_key_event(struct _cef_keyboard_handler_t* self,
                                  struct _cef_browser_t* browser,
                                  const cef_key_event_t* event,
                                  cef_event_handle_t os_event);
