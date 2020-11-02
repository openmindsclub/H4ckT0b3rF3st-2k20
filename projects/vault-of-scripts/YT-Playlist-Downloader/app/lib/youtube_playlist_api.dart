import 'package:http/http.dart';
import 'dart:convert';

class YoutubePlaylistAPI {
  String apiEndpoint = 'http://192.168.1.38:5000';
  String url;

  YoutubePlaylistAPI({this.url});

  Future<int> getPlaylistLength() async {
    Response r = await post(
      '$apiEndpoint/length',
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, String>{
        'playlist_url': this.url,
      }),
    );

    print(jsonDecode(r.body)['length']);
    return jsonDecode(r.body)['length'];
  }

  Future<Map> getTrack(int offset) async {
    Response r = await post(
      '$apiEndpoint/',
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, String>{
        'playlist_url': this.url,
        'offset': offset.toString(),
      }),
    );

    if (r.statusCode == 400) return null;
    return jsonDecode(r.body);
  }

  Future<Map> getSingleTrack() async {
    Response r = await post(
      '$apiEndpoint/track',
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(<String, String>{
        'track_url': this.url,
      }),
    );

    return jsonDecode(r.body);
  }
}
