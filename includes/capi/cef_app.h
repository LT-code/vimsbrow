// CEF C API example
// Project website: https://github.com/cztomczak/cefcapi

#pragma once

#include "cef_base.h"
#include "include/capi/cef_app_capi.h"
#include <string.h>

// ----------------------------------------------------------------------------
// cef_app_t
// ----------------------------------------------------------------------------

///
// Implement this structure to provide handler implementations. Methods will be
// called by the process and/or thread indicated.
///

///
// Provides an opportunity to view and/or modify command-line arguments before
// processing by CEF and Chromium. The |process_type| value will be NULL for
// the browser process. Do not keep a reference to the cef_command_line_t
// object passed to this function. The CefSettings.command_line_args_disabled
// value can be used to start with an NULL command-line object. Any values
// specified in CefSettings that equate to command-line arguments will be set
// before this function is called. Be cautious when using this function to
// modify command-line arguments for non-browser processes as this may result
// in undefined behavior including crashes.
///
void CEF_CALLBACK on_before_command_line_processing(
        struct _cef_app_t* self, const cef_string_t* process_type,
        struct _cef_command_line_t* command_line) {
    //char str5[] = "deny-permission-prompts";
    char str5[] = "enable-widevine";
    cef_string_t test = {};
    cef_string_utf8_to_utf16(str5, strlen(str5), &test);
    command_line->append_switch(command_line, &test);

    char str8[] = "cros-bundled-widevine";
    cef_string_t load_ext10 = {};
    cef_string_utf8_to_utf16(str8, strlen(str8), &load_ext10);

    char str9[] = "~/.cache/cef_user_data/cache/WidevineCdm/";
    cef_string_t load_ext_path10 = {};
    cef_string_utf8_to_utf16(str9, strlen(str9), &load_ext_path10);

    //command_line->append_switch_with_value(command_line, &load_ext10, &load_ext_path10);

    //char str6[] = "ash-no-nudges";
    //cef_string_t test2 = {};
    //cef_string_utf8_to_utf16(str6, strlen(str6), &test2);
    //command_line->append_switch(command_line, &test2);

    char str7[] = "disable-search-engine-choice-screen";
    cef_string_t test3 = {};
    cef_string_utf8_to_utf16(str7, strlen(str7), &test3);
    command_line->append_switch(command_line, &test3);

    char str[] = "enable-extensions";
    cef_string_t enable_ext = {};
    cef_string_utf8_to_utf16(str, strlen(str), &enable_ext);
    command_line->append_switch(command_line, &enable_ext);

    char str2[] = "enable-experimental-extension-apis";
    cef_string_t enable_ext2 = {};
    cef_string_utf8_to_utf16(str2, strlen(str2), &enable_ext2);
    command_line->append_switch(command_line, &enable_ext2);

    //--disable-extensions-except
    //--disable-hang-monitor

    //char str3[] = "load-extension";
    //cef_string_t load_ext = {};
    //cef_string_utf8_to_utf16(str3, strlen(str3), &load_ext);

    //char str4[] = "~/Programming/Perso/lt-brow/test/extensions/uBlock0.chromium/";
    //cef_string_t load_ext_path = {};
    //cef_string_utf8_to_utf16(str4, strlen(str4), &load_ext_path);
    //command_line->append_switch_with_value(command_line, &load_ext, &load_ext_path);
    //
    printf("cmd : %s\n", (char*)command_line->get_command_line_string(command_line)->str);
}

///
// Provides an opportunity to register custom schemes. Do not keep a reference
// to the |registrar| object. This function is called on the main thread for
// each process and the registered schemes should be the same across all
// processes.
///
void CEF_CALLBACK on_register_custom_schemes(
        struct _cef_app_t* self,
        struct _cef_scheme_registrar_t* registrar) {
}

///
// Return the handler for resource bundle events. If
// CefSettings.pack_loading_disabled is true (1) a handler must be returned.
// If no handler is returned resources will be loaded from pack files. This
// function is called by the browser and render processes on multiple threads.
///
struct _cef_resource_bundle_handler_t*
        CEF_CALLBACK get_resource_bundle_handler(struct _cef_app_t* self) {
    return NULL;
}

///
// Return the handler for functionality specific to the browser process. This
// function is called on multiple threads in the browser process.
///
struct _cef_browser_process_handler_t* 
        CEF_CALLBACK get_browser_process_handler(struct _cef_app_t* self) {
    return NULL;
}

///
// Return the handler for functionality specific to the render process. This
// function is called on the render process main thread.
///
struct _cef_render_process_handler_t*
        CEF_CALLBACK get_render_process_handler(struct _cef_app_t* self) {
    return NULL;
}

void initialize_cef_app(cef_app_t* app) {
    printf("initialize_cef_app\n");
    app->base.size = sizeof(cef_app_t);
    initialize_cef_base_ref_counted((cef_base_ref_counted_t*)app);
    // callbacks
    app->on_before_command_line_processing = on_before_command_line_processing;
    app->on_register_custom_schemes = on_register_custom_schemes;
    app->get_resource_bundle_handler = get_resource_bundle_handler;
    app->get_browser_process_handler = get_browser_process_handler;
    app->get_render_process_handler = get_render_process_handler;
}
