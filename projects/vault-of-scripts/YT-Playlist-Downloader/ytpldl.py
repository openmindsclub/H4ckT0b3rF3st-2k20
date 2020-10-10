from pytube import YouTube # pip install pytube or pytube3
from pytube import Playlist
import os, re

def Download(yt):
    print("Downloading....")
    # Filter Streams (Optional)
    vids = yt.streams.filter()
    # Get only .mp4 format
    vids[0].download(r"Tracks/")

def main(c, playlist):
    # Filter Playlist Url
    playlist._video_regex = re.compile(r"\"url\":\"(/watch\?v=[\w-]*)")
    # Iterate Through Playlist
    urls = playlist.video_urls
    print("Number of tracks: ", len(urls))
    for url in urls:
        # Handle Url
        yt = YouTube(url)
        # Filename specification
        _filename = yt.title
        print(c, ". ", _filename)
        # Downloading
        Download(yt)
        c = c + 1

if __name__ == '__main__':
    playlist = Playlist("https://www.youtube.com/playlist?list=PL8A83A276F0D85E70")
    main(1, playlist)
