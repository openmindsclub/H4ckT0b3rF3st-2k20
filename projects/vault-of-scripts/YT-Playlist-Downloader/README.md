# Youtube Playlist Downloader

If you're tired of going back and fourth from copying the URL of a youtube video to pasting it on a video downloader website, this app is for you. Find/Create the playlist you 
want to download and run this app, the rest is a work of magic (well, code. But it's the same thing).  

## Overview

The project is made of a `Flask` API serving as an endpoint for a `Flutter` app

### API 

#### Setup

Start by making a python3.8 venv, then install the required dependencies:
```bash
pip install -r requirements.txt
```

to deploy the api, run:
```bash
python api.py
```
the api will deployed at port `5000`.

PS: there is a small [issue](https://stackoverflow.com/questions/61960657/getting-keyerror-url-with-pytube) with `pytube3` library, to fix it, do the following:
> 1. Go to pytube directory in site-packages. If you're not sure where full location is use: `pip show pytube3`. You'll see location of site-packages.
> 2. In `site-packages/pytube` folder opened from above location, you'll see a file called `extract.py`. Open that file in your IDE or text-editor.
> 3. You'll see a function called `apply_descrambler`. Inside that function, in line 301 probably, you'll see something like `parse_qs(formats[i]["cipher"]) for i, data in enumerate(formats)`
> 4. Replace `cipher` in `formats[i]["cipher"]` with `signatureCipher` . Thus that line becomes, `parse_qs(formats[i]["signatureCipher"]) for i, data in enumerate(formats)`
> 5. pytube3 should work fine now

(quoted from the first answer in previous [link](https://stackoverflow.com/questions/61960657/getting-keyerror-url-with-pytube))

The setup should be complete

#### Usage

The API provides two endpoints:
* `/length`: Which takes a playlist URL as an argument, and returns the length of that playlist, this is made to check whether the provided URL is a valid youtube playlist URL or not, if not, it'll yield 0.

* `/`: Whick takes a playlist URL and an offset(or a track URL) and yield details of that track(title, download link, thumbnail image URL):
    * In case of a track URL: it'll yield the details of that track

    * In case of a playlist URl and an offset: it'll yield the details of the track at the given offset in the playlist

    this is to be used by the app to get details of each track in the playlist, by making successive calls. or a single call to get the details of a single track

* `/track`: Which takes a track URL, and checks whether the provided URL is a valid youtube track URL, if it's valid, it'll return the details of that track.

* `/convert`: Which takes a track download URL, download that track, convert it to MP3 format, and send it back in the response

### App

#### Setup

In order to run and test the app, you'll need to setup three things:

* Flutter: a well documented guide is available [here](https://flutter.dev/docs/get-started/install)

* Android Emulator: I recommend using `genymotion`, you can download the personal use edition [here](https://www.genymotion.com/fun-zone/), and follow the setup instructions mentioned [here](https://docs.genymotion.com/desktop/3.1/01_Get_started/012_Installation.html)

* IDE: I personally use VSCode, you can find a guide on how to setup flutter with it [here](https://flutter.dev/docs/development/tools/vs-code), but using Android Studio is also good

after you're done with the above, install the plugins and dependencies in your IDE(it'll likely ask you for them anyway) and Thats it!

head to `app/lib/main.dart` in your IDE and start the app.

#### Usage

The app consists of two pages:

* HomePage: which gives an interface to type in a playlist/track URL, it'll send this URL the `/length` API endpoint to verify(as mentioned in the API doc), if the URL is valid, it'll show the download page, if not, it'll prompt an error and resets the input

* DownloadPage: which shows the tracks and gives the ability to download them(obviously), it starts off blank, and gradually fills up with tracks info by sending successive calls to the `/` API endpoint, you can download each track individually, or download them all using the `Download All` button.

for more technical stuff, check the README.md file in the app folder.

### Tasks
Here are things you can do to complete this implementation:
* Make the API faster? find another way to get the track details

* Make More checks for the app logic, to avoid crashes when an API call fails

* Make tests for both the app Widgets and the API(both `api.py` and `ytpldl.py`)

* Improve my stupid code

* Be Creative!

### Ressources
* [Pytube](https://python-pytube.readthedocs.io/en/latest/)

* [Flask API](https://flask-restful.readthedocs.io/en/latest/)

* [Awesome Flutter Playlist](https://www.youtube.com/watch?v=1ukSR1GRtMU&list=PL4cUxeGkcC9jLYyp2Aoh6hcWuxFDX6PBJ)

