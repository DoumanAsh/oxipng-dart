import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:oxipng/oxipng_method_channel.dart';

void main() {
  MethodChannelOxipng platform = MethodChannelOxipng();
  const MethodChannel channel = MethodChannel('oxipng');

  TestWidgetsFlutterBinding.ensureInitialized();

  setUp(() {
    channel.setMockMethodCallHandler((MethodCall methodCall) async {
      return '42';
    });
  });

  tearDown(() {
    channel.setMockMethodCallHandler(null);
  });

  test('getPlatformVersion', () async {
    expect(await platform.getPlatformVersion(), '42');
  });
}
