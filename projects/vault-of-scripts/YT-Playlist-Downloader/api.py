from flask_restful import Resource, Api
from flask import Flask, request
from ytpldl import YouTubePlaylistDownloader
import logging
from time import sleep

app = Flask(__name__)
api = Api(app)


class YTPlaylistDownloadAPI(Resource):

    def post(self):
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
        data = request.get_json()
        logging.info(data['playlist_url'])
        if 'playlist_url' not in data.keys():
            return 'The request must include a playlist_url', 400

        downloader = YouTubePlaylistDownloader(data['playlist_url'])
        return {'length': len(downloader.urls)}


api.add_resource(YTPlaylistDownloadAPI, '/')
api.add_resource(YTPlaylistLength, '/length')
if __name__ == "__main__":
    app.run('0.0.0.0', debug=True)
