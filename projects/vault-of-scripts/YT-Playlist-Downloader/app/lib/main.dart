import 'package:flutter/material.dart';
import 'package:app/playlist_choose.dart';
import 'package:app/playlist_download.dart';

void main() {
  runApp(MaterialApp(
    theme: ThemeData.dark(),
    darkTheme: ThemeData.dark(),
    initialRoute: '/',
    routes: {
      '/': (context) => PlaylistChoose(),
      '/download': (context) => PlaylistDownload(),
    },
  ));
}
