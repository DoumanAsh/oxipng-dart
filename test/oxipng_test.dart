import 'package:flutter_test/flutter_test.dart';
import 'package:oxipng/oxipng.dart';
import 'package:oxipng/oxipng_platform_interface.dart';
import 'package:oxipng/oxipng_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockOxipngPlatform
    with MockPlatformInterfaceMixin
    implements OxipngPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final OxipngPlatform initialPlatform = OxipngPlatform.instance;

  test('$MethodChannelOxipng is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelOxipng>());
  });

  test('getPlatformVersion', () async {
    Oxipng oxipngPlugin = Oxipng();
    MockOxipngPlatform fakePlatform = MockOxipngPlatform();
    OxipngPlatform.instance = fakePlatform;

    expect(await oxipngPlugin.getPlatformVersion(), '42');
  });
}
