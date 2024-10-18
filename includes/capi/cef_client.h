// CEF C API example
// Project website: https://github.com/cztomczak/cefcapi

#pragma once

#include "cef_base.h"
#include "cef_life_span_handler.h"
#include "include/capi/cef_client_capi.h"
#include "keybindings.h"
#include "ui/ui.h"
#include <stdio.h>

extern cef_life_span_handler_t g_life_span_handler;
extern cef_display_handler_t g_display_handler;
extern cef_render_handler_t g_render_handler;
extern cef_keyboard_handler_t g_keyboard_handler;
extern cef_permission_handler_t g_permssion_handler;
extern cef_focus_handler_t g_focus_handler;

enum current_mode {
  VISUAL = 0,
  INSERT
};

// ----------------------------------------------------------------------------
// struct cef_client_t
// ----------------------------------------------------------------------------

///
// Implement this structure to provide handler implementations.
///

///
// Return the handler for context menus. If no handler is
// provided the default implementation will be used.
///

struct _cef_context_menu_handler_t* CEF_CALLBACK get_context_menu_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_context_menu_handler\n");
    return NULL;
}

///
// Return the handler for dialogs. If no handler is provided the default
// implementation will be used.
///
struct _cef_dialog_handler_t* CEF_CALLBACK get_dialog_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_dialog_handler\n");
    return NULL;
}

///
// Return the handler for browser display state events.
///
struct _cef_display_handler_t* CEF_CALLBACK get_display_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_display_handler\n");

    return &g_display_handler;
}

///
// Return the handler for download events. If no handler is returned downloads
// will not be allowed.
///
struct _cef_download_handler_t* CEF_CALLBACK get_download_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_download_handler\n");
    return NULL;
}

///
// Return the handler for drag events.
///
struct _cef_drag_handler_t* CEF_CALLBACK get_drag_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_drag_handler\n");
    return NULL;
}

///
// Return the handler for focus events.
///
struct _cef_focus_handler_t* CEF_CALLBACK get_focus_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_focus_handler\n");
    return &g_focus_handler;
}

///
// Return the handler for geolocation permissions requests. If no handler is
// provided geolocation access will be denied by default.
///
struct _cef_permission_handler_t* get_permission_handler(
      struct _cef_client_t* self) {
    printf("get_permission_handler\n");
    return &g_permssion_handler;
}

///
// Return the handler for JavaScript dialogs. If no handler is provided the
// default implementation will be used.
///
struct _cef_jsdialog_handler_t* CEF_CALLBACK get_jsdialog_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_jsdialog_handler\n");
    return NULL;
}

///
// Return the handler for keyboard events.
///
struct _cef_keyboard_handler_t* CEF_CALLBACK get_keyboard_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_keyboard_handler\n");

    return &g_keyboard_handler;
}

///
// Return the handler for browser life span events.
///
struct _cef_life_span_handler_t* CEF_CALLBACK get_life_span_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_life_span_handler\n");
    // Implemented!

    return &g_life_span_handler;
}

///
// Return the handler for browser load status events.
///
struct _cef_load_handler_t* CEF_CALLBACK get_load_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_load_handler\n");
    return NULL;
}

///
// Return the handler for off-screen rendering events.
///
struct _cef_render_handler_t* CEF_CALLBACK get_render_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_render_handler\n");
    return &g_render_handler;
}

///
// Return the handler for browser request events.
///
struct _cef_request_handler_t* CEF_CALLBACK get_request_handler(
        struct _cef_client_t* self) {
    DEBUG_CALLBACK("get_request_handler\n");
    return NULL;
}

///
// Called when a new message is received from a different process. Return true
// (1) if the message was handled or false (0) otherwise. Do not keep a
// reference to or attempt to access the message outside of this callback.
///
int CEF_CALLBACK on_process_message_received(
        struct _cef_client_t* self,
        struct _cef_browser_t* browser, cef_process_id_t source_process,
        struct _cef_process_message_t* message) {
    DEBUG_CALLBACK("on_process_message_received\n");
    return 0;
}

int on_request_media_access_permission(
      struct _cef_permission_handler_t* self,
      struct _cef_browser_t* browser,
      struct _cef_frame_t* frame,
      const cef_string_t* requesting_origin,
      uint32_t requested_permissions,
      struct _cef_media_access_callback_t* callback) {

  printf("##################################### on_request_media_access_permission %i %hu\n", requested_permissions, *requesting_origin->str);
  return 0;
}

int on_show_permission_prompt(
      struct _cef_permission_handler_t* self,
      struct _cef_browser_t* browser,
      uint64_t prompt_id,
      const cef_string_t* requesting_origin,
      uint32_t requested_permissions,
      struct _cef_permission_prompt_callback_t* callback) {

  printf("##################################### on_show_permission_prompt %i %s\n", requested_permissions, (char*)requesting_origin->str);
  return 0;
}

int on_auto_resize(struct _cef_display_handler_t* self,
                                    struct _cef_browser_t* browser,
                                    const cef_size_t* new_size) {
  printf("======================== %i %i\n", new_size->width, new_size->height);
  return 1;
}

void on_got_focus(struct _cef_focus_handler_t* self,
                                   struct _cef_browser_t* browser) {
  //browser_set_focus();
}
  void on_take_focus(struct _cef_focus_handler_t* self,
                                    struct _cef_browser_t* browser,
                                    int next) {

    
    printf("-----------------> on_take_focus%i\n", is_browser_can_focus());
    entry_set_focus();
  }

  int on_set_focus(struct _cef_focus_handler_t* self,
                                  struct _cef_browser_t* browser,
                                  cef_focus_source_t source) {
    printf("-----------------> on_set_focus%i\n", is_browser_can_focus());
    if (!is_browser_can_focus()) {

    entry_get_focus();
    }
    return is_browser_can_focus();
  }




void initialize_cef_client(cef_client_t* client) {
    DEBUG_CALLBACK("initialize_client_handler\n");
    client->base.size = sizeof(cef_client_t);
    initialize_cef_base_ref_counted((cef_base_ref_counted_t*)client);
    // callbacks
    client->get_context_menu_handler = get_context_menu_handler;
    client->get_dialog_handler = get_dialog_handler;
    client->get_display_handler = get_display_handler;
    client->get_download_handler = get_download_handler;
    client->get_drag_handler = get_drag_handler;
    client->get_focus_handler = get_focus_handler;
    //client->get_geolocation_handler = get_geolocation_handler;
    client->get_permission_handler = get_permission_handler;
    client->get_jsdialog_handler = get_jsdialog_handler;
    client->get_keyboard_handler = get_keyboard_handler;
    client->get_life_span_handler = get_life_span_handler;  // Implemented!
    client->get_load_handler = get_load_handler;
    client->get_render_handler = get_render_handler;
    client->get_request_handler = get_request_handler;
    //client->on_process_message_received = on_process_message_received;
    //
    g_render_handler.base.size = sizeof(cef_render_handler_t);
    initialize_cef_base_ref_counted((cef_base_ref_counted_t*)&g_render_handler);

    g_display_handler.base.size = sizeof(cef_display_handler_t);
    initialize_cef_base_ref_counted((cef_base_ref_counted_t*)&g_display_handler);
    g_display_handler.on_auto_resize = on_auto_resize;

    initialize_cef_life_span_handler(&g_life_span_handler);

    g_keyboard_handler.base.size = sizeof(cef_keyboard_handler_t);
    initialize_cef_base_ref_counted((cef_base_ref_counted_t*)&g_keyboard_handler);
    g_keyboard_handler.on_pre_key_event = keybindings_on_pre_key_event;
    g_keyboard_handler.on_key_event = keybindings_on_key_event;

    g_permssion_handler.base.size = sizeof(cef_permission_handler_t);
    initialize_cef_base_ref_counted((cef_base_ref_counted_t*)&g_permssion_handler);
    g_permssion_handler.on_request_media_access_permission = on_request_media_access_permission;
    g_permssion_handler.on_show_permission_prompt = on_show_permission_prompt;

    g_focus_handler.base.size = sizeof(cef_focus_handler_t);
    initialize_cef_base_ref_counted((cef_base_ref_counted_t*)&g_focus_handler);
    g_focus_handler.on_got_focus = on_got_focus;
    g_focus_handler.on_take_focus = on_take_focus;
    g_focus_handler.on_set_focus = on_set_focus;
}
