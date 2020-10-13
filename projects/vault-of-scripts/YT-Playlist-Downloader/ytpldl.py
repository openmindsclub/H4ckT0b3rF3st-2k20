from pytube import YouTube
from pytube import Playlist
import re
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s %(levelname)-8s %(message)s')


class YouTubePlaylistDownloader():

    def __init__(self, playlist_url):
        playlist = Playlist(playlist_url)
        playlist._video_regex = re.compile(r"\"url\":\"(/watch\?v=[\w-]*)")
        self.urls = playlist.video_urls
        logging.info(f"[+] Number of tracks: {len(self.urls)}")

    def download_a_track(self, yt_instance, offset=1):
        logging.info(f"[+] {offset}. Downloading {yt_instance.title}")

        try:
            # Filter Streams (Optional)
            vids = yt_instance.streams.filter()
            # Get only .mp4 format
            logging.info(vids[0].url)
            vids[0].download(r"Tracks/")

            logging.info(f'[+] {offset}. Download Done')

        except Exception as e:
            logging.error(f'[-] {offset}. Encountered Error {e}')

    def download(self, offset=None):
        if not offset:
            for n, url in enumerate(self.urls):
                self.download_a_track(YouTube(url), n)
        else:
            self.download_a_track(YouTube(self.urls[offset]), offset)

    def get_download_details(self, offset):
        target = YouTube(self.urls[offset])
        data = {
            'title': target.title,
            'download_url': target.streams.get_highest_resolution().url,
            'thumbnail': target.thumbnail_url
        }
        return data


if __name__ == '__main__':
    downloader = YouTubePlaylistDownloader("https://www.youtube.com/playlist?list=PL8A83A276F0D85E70")
    downloader.download()
