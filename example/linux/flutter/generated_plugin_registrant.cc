//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <oxipng/oxipng_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) oxipng_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "OxipngPlugin");
  oxipng_plugin_register_with_registrar(oxipng_registrar);
}
