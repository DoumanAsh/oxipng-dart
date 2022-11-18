#include "oxipng_plugin.h"
#include "oxipng-ffi.h"

// This must be included before many other Windows headers.
#include <windows.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <vector>
#include <string>
#include <thread>

namespace oxipng {

template<typename T>
T GetArgument(flutter::EncodableValue arg, const flutter::EncodableValue* args, T fallback) {
  T result {fallback};
  const auto* arguments = std::get_if<flutter::EncodableMap>(args);
  if (arguments) {
    auto result_it = arguments->find(arg);
    if (result_it != arguments->end()) {
      if (!result_it->second.IsNull())
        result = std::get<T>(result_it->second);
    }
  }
  return result;
}

// static
void OxipngPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_shared<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "oxipng",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<OxipngPlugin>(channel);

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

OxipngPlugin::OxipngPlugin(std::shared_ptr<flutter::MethodChannel<flutter::EncodableValue>> channel): channel(channel) {}

OxipngPlugin::~OxipngPlugin() {}

void OxipngPlugin::HandleMethodCall(const flutter::MethodCall<flutter::EncodableValue> &method_call, std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("optimizeImage") == 0) {
    const auto args = method_call.arguments();
    const auto bytes = GetArgument(flutter::EncodableValue("image"), args, std::vector<uint8_t>());
    const auto fix_errors = GetArgument<bool>(flutter::EncodableValue("fix_errors"), args, false);
    const auto strip_headers = GetArgument<bool>(flutter::EncodableValue("strip_headers"), args, true);
    const auto level_arg = GetArgument<int32_t>(flutter::EncodableValue("level"), args, 4);

    if (level_arg <= 0 || level_arg > 6) {
        result->Error("-1", "Invalid level");
        return;
    }

    uint8_t level = static_cast<uint8_t>(level_arg);

    OxiPngOptions options;
    //imagine not supporting designated initializers
    options.fix_errors = fix_errors;
    options.strip_headers = strip_headers;
    options.level = level;

    OxiPngOutput output = {};
    const auto oxipng_result = oxipng_optimize_file(bytes.data(), bytes.size(), options, &output);

    if (oxipng_result == OxiPngResultOk) {
        const std::vector<uint8_t> optimized(output.data, output.data + output.len);
        oxipng_output_free(&output);
        result->Success(flutter::EncodableValue(optimized));
    } else {
        result->Error(std::to_string(oxipng_result), oxipng_result_description(oxipng_result));
    }
  } else {
    result->NotImplemented();
  }
}

}  // namespace oxipng
