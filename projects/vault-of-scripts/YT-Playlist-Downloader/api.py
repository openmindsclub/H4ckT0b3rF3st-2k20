from flask_restful import Resource, Api
from flask import Flask, request, send_file
from ytpldl import YouTubePlaylistDownloader
from time import sleep
import requests
from os import urandom
from moviepy.editor import VideoFileClip


app = Flask(__name__)
api = Api(app)


class YTPlaylistDownloadAPI(Resource):

    def post(self):
        ''' Yield a download URL for a certain track '''
        data = request.get_json()
        if 'playlist_url' not in data.keys() or 'offset' not in data.keys():
            return 'The request must include a playlist_url and an offset', 400

        downloader = YouTubePlaylistDownloader(data['playlist_url'])
        if not len(downloader.urls):
            return "Couldn't find a playlist in that URL", 400

        while True:
            try:
                details = downloader.get_download_details(int(data['offset']))
                break
            except Exception:
                sleep(3)
                pass

        return details, 200


class YTPlaylistLength(Resource):

    def post(self):
        ''' Yield the length of the playlist, to be used by the app to check if a certain
            playlist URL is valid, if length !=0 then the URL is valid, unvalid if not
        '''

        data = request.get_json()

        if 'playlist_url' in data.keys():
            try:
                downloader = YouTubePlaylistDownloader(data['playlist_url'])

                return {'length': len(downloader.urls)}
            except Exception:
                return {'length': 0}

        return 'The request must include a playlist_url or a track_url', 400


class YTTrackChecker(Resource):

    def post(self):
        ''' Check whether the provided URL is a youtube track URL, yield it's info
            if valid, Bad Request response if not
        '''

        data = request.get_json()

        if 'track_url' in data.keys():
            try:
                details = YouTubePlaylistDownloader().get_download_details(track_url=data['track_url'])
                details['is_track'] = True

                return details
            except Exception:
                return {'is_track': False}

        return 'The request must include a track_url', 400


class MP3Converter(Resource):

    def get(self):
        ''' Convert an MP4 file to an MP3 file and send it back in the response '''

        data = request.args
        if 'download_url' in data.keys():
            r = requests.get(data['download_url'], allow_redirects=True)
            filename = urandom(16).hex()
            with open(f'/tmp/{filename}.mp4', 'wb') as f:
                f.write(r.content)

            videoclip = VideoFileClip(f'/tmp/{filename}.mp4')
            audioclip = videoclip.audio
            audioclip.write_audiofile(f'/tmp/{filename}.mp3')

            audioclip.close()
            videoclip.close()

            return send_file(f'/tmp/{filename}.mp3', attachment_filename='download.mp3')

        return 'Request must include a download URL', 400


api.add_resource(YTPlaylistDownloadAPI, '/')
api.add_resource(YTPlaylistLength, '/length')
api.add_resource(YTTrackChecker, '/track')
api.add_resource(MP3Converter, '/convert')
if __name__ == "__main__":
    app.run('0.0.0.0', debug=True)
