import 'package:flutter/material.dart';
import 'package:app/youtube_playlist_api.dart';

class PlaylistChoose extends StatefulWidget {
  @override
  PlaylistChooseState createState() {
    return PlaylistChooseState();
  }
}

class PlaylistChooseState extends State<PlaylistChoose> {
  final _formKey = GlobalKey<FormState>();
  final URLController = TextEditingController();
  int length;
  YoutubePlaylistAPI api;
  bool isTrack;
  Map trackData = {};

  @override
  void dispose() {
    URLController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Youtube Playlist Downloader'),
        centerTitle: true,
      ),
      body: Padding(
        padding: const EdgeInsets.symmetric(vertical: 100, horizontal: 10),
        child: Container(
          decoration: BoxDecoration(
            border: Border.all(
              color: Colors.black,
            ),
            borderRadius: BorderRadius.circular(10),
          ),
          child: Form(
            key: _formKey,
            child: Padding(
              padding:
                  const EdgeInsets.symmetric(vertical: 100, horizontal: 10),
              child: Column(
                children: <Widget>[
                  TextFormField(
                    controller: URLController,
                    decoration: InputDecoration(
                        labelText: 'Enter the Playlist/Track URL',
                        border: OutlineInputBorder()),
                    validator: (value) {
                      if (this.length == 0) {
                        return 'Invalid Playlist/Track';
                      }
                      return null;
                    },
                  ),
                  RaisedButton(
                    onPressed: () async {
                      api = YoutubePlaylistAPI(url: URLController.text);
                      Map trackCheck = await api.getSingleTrack();
                      if (trackCheck['is_track']) {
                        this.trackData = {
                          'title': trackCheck['title'],
                          'download_url': trackCheck['download_url'],
                          'thumbnail': trackCheck['thumbnail']
                        };

                        this.length = 1;
                        this.isTrack = true;
                      } else {
                        int result = await api.getPlaylistLength();
                        setState(() {
                          this.length = result;
                          this.isTrack = false;
                        });
                      }

                      if (_formKey.currentState.validate()) {
                        Navigator.pushNamed(
                          context,
                          '/download',
                          arguments: {
                            'playlist_url': URLController.text,
                            'length': this.length,
                            'isTrack': this.isTrack,
                            'trackData': this.trackData
                          },
                        );
                      }
                    },
                    child: Text('Submit'),
                  ),
                ],
              ),
            ),
          ),
        ),
      ),
    );
  }
}
