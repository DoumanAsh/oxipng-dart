import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'oxipng_platform_interface.dart';

/// An implementation of [OxipngPlatform] that uses method channels.
class MethodChannelOxipng extends OxipngPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('oxipng');

  @override
  ///Requests to optimize image
  Future<Uint8List?> optimizeFromMemory(Uint8List data) async {
    final arguments = <String, dynamic>{
        'image': data,
        'fix_errors': true,
        'strip_headers': true,
        'level': 4,
    };

    return await methodChannel.invokeMethod<Uint8List>('optimizeImage', arguments);
  }
}
