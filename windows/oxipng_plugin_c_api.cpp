#include "include/oxipng/oxipng_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "oxipng_plugin.h"

void OxipngPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  oxipng::OxipngPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
