import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'oxipng_method_channel.dart';

import 'dart:typed_data' show Uint8List;

abstract class OxipngPlatform extends PlatformInterface {
  /// Constructs a OxipngPlatform.
  OxipngPlatform() : super(token: _token);

  static final Object _token = Object();

  static OxipngPlatform _instance = MethodChannelOxipng();

  /// The default instance of [OxipngPlatform] to use.
  ///
  /// Defaults to [MethodChannelOxipng].
  static OxipngPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [OxipngPlatform] when
  /// they register themselves.
  static set instance(OxipngPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<Uint8List?> optimizeFromMemory(Uint8List data) async {
    throw UnimplementedError('optimizeFromMemory() has not been implemented.');
  }
}
