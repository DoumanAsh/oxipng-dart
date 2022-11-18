#ifndef FLUTTER_PLUGIN_OXIPNG_PLUGIN_H_
#define FLUTTER_PLUGIN_OXIPNG_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace oxipng {

class OxipngPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  OxipngPlugin(std::shared_ptr<flutter::MethodChannel<flutter::EncodableValue>> channel);

  virtual ~OxipngPlugin();

  // Disallow copy and assign.
  OxipngPlugin(const OxipngPlugin&) = delete;
  OxipngPlugin& operator=(const OxipngPlugin&) = delete;

 private:
  std::shared_ptr<flutter::MethodChannel<flutter::EncodableValue>> channel;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace oxipng

#endif  // FLUTTER_PLUGIN_OXIPNG_PLUGIN_H_
