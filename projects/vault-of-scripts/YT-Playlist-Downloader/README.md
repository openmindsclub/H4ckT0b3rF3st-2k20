## Youtube Playlist Downloader
If you're tired of going back and fourth from copying the URL of a youtube video to pasting it on a video downloader website, this script is for you. Find/Create the playlist you 
want to download and execute this script, the rest is a work of magic (well, code. But it's the same thing).  

### Setup 
You need to install pytube:
``` bash
pip install pytube
```
or
``` bash
pip install pytube3
```

### Usage 
Either change url of the playlist you want to download inside the .py file or leave it as it is.
``` bash
cd 'python-file-directory'
python ytpldl.py 
```

### Tasks
Here are things you can do to complete this implementation:
* I originally was going for a music playlist downloader but I was too lazy to convert the files to mp3. Why don't you try it out? You can convert the downloaded files 
using ffmpeg module. (if you're going for that, I recommend that you filter the streams to download audio files only, this will save us a lot of time during the download process).
* Improve my stupid code
* Be creative!

### Ressources
* [Pytube](https://python-pytube.readthedocs.io/en/latest/)

