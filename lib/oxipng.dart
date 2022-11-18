
import 'oxipng_platform_interface.dart';

import 'dart:typed_data' show Uint8List;

class Oxipng {
  ///Requests to optimize image
  Future<Uint8List?> optimizeFromMemory(Uint8List data) async {
    return OxipngPlatform.instance.optimizeFromMemory(data);
  }
}
