###AutoBadMeme(ABM)

Welcome to ATB, the ONLY bad meme generator.
Inspired by literally nothing, i wanted to create a program for one unique objective, which is making the shittiest memes possible in the history of mankind.
So here it is, autobadmeme, also called ABM, will generate automatically a meme for you to "enjoy" and repost on your favorite social media account, using multiple different templates (for now only 2 type of templates are availlable), you'll be able, you too, to experience the meme life and maybe become the next grandday or dolan dark.
### Used Libraries / Frameworks

* cv2 (also called opencv) : opencv is your go-to when you want to manipulate images or do image recognition algorithms
* csv : lets you read excel-style files, also compatible with the libreoffice equivalent.
* numpy : numpy allows you to do more precise calculations as well as using pseudo-random functions

### How to use the meme generator
You will need to install opencv.

``` bash
pip install opencv-python
```

and then, just execute the file

``` bash
python ABT.py
```
A prompt will appear, asking you which kind of meme you want to generate.

### How it works
Quite simple, the user choses which kind of meme he wanna generate, after that, the program will handle everything : fetching the meme template, fetching the text, putting the text in the right position in the meme and save the meme in the "yourMeme" folder

### How to choose a template
So far, only 2 kind of templates are availlable : the one-panel meme(3 templates) and the two-panel meme(2 templates)
A one-panel meme is self-explanatory, it's an image with text on the top, it's the most common form of memes, generally speaking, one-panel are used as a reaction image, like if something happen or you wanna comment on something, you're gonna use a one-panel as it directs the message in a clear and precise way.

Two-panel memes are a good way to compare two different things, generally speaking, the one on the left or the top is the one you are supposed to hate, whereas the choice at the bottom or right is the thing you are supposed to like, the most famous example of it is the drake meme

In the future, more templates are gonna be added, and more meme types are gonna be added.


### Contributions.
Several contributions can be made:
1-Give me more ideas of kind of memes you want me to implement.
2-Add meme templates that corresponds to the categories in place (so either a one-panel or a two-panel)
3-Make a GUI which would make it easier to generate a meme.
