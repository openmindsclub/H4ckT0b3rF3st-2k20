# -*- coding: utf-8 -*-

'''
Wellcome to AutoBadMeme, the first and only bad meme generator
'''

#Task one : put the bare minimum to load an image and write text on it. DONE

#Task two : make the image getter read random images from one directory.Done

#Task three : find the position where you write the meme stuff. Semi-Done

'''partie import'''
import os
import cv2
import numpy as np
import csv

'''Partie initialisation de variables'''
dirMemeFolder = 'memeFolder/'
dirText = ''
csvfile = ''
fontSize = 0
text1 = "a"
text2 = "a"
memeGen=0


'''Partie fonctions'''
def imgGetter(directory,csvfile):
  '''
We use a CSV file as a way to store information related to the meme folder, like
the number of meme templates, the positions of the text in the meme folder as well
as other informations we might use in the future.
The relevant data is the directory of the meme folder as well as the name of the
csv file
  '''
  taille = os.listdir(directory)
  taille = len(taille)

  pc = np.random.randint(0,taille-1)
  gtFile = open(directory + csvfile + '.csv') # annotations file
  gtReader = csv.reader(gtFile, delimiter=';') # csv parser for annotations file
  gtReader.__next__() # skip header
  liste = []
  for row in gtReader:
      liste.append(row)
      
  meme = liste[pc]
  #Get the position of the text fields
  #textPos2 only gets relevant data when using two-panel memes
  textPos1 = [int(meme[1]),int(meme[2])]
  textPos2 = [int(meme[3]),int(meme[4])]
  #Get the image
  img = cv2.imread(directory+meme[0]+'.jpg',1)
  return img,textPos1,textPos2

def putText(img,text1 = "", text2 = "",textPos1="",textPos2=""):
  size = img.shape
  font = cv2.FONT_HERSHEY_SIMPLEX
  #This function serves to inject text fields into a still image
  #and as a result produces a meme
  for i in range(len(text1)):
      img2 = cv2.putText(img,text1[i].strip(),(textPos1[0],textPos1[1]+(i*20)),font,fontSize,(0,0,0),2,cv2.LINE_AA)
  
  for i in range(len(text2)):
      img2 = cv2.putText(img,text2[i].strip(),(textPos2[0],textPos2[1]+(i*20)),font,fontSize,(0,0,0),2,cv2.LINE_AA)
  
  img2 = cv2.putText(img2,'made by autoBadMeme',(int(size[0]*0.8),int(size[1]*0.85))
                        ,font,0.5,(0,0,0),2,cv2.LINE_AA)
  return img2

def imgSaver(img):
  #Placeholder code for saving an image
  fileName = 'yourMeme/yourMeme.jpg'
  cv2.imwrite(fileName, img)
  return 0

def getMemeTxt(directory):
  #This function serves as a text getter, it gets lines from a meme folder.
  f = open(directory+"whenmemes.txt","r")
  txt = f.readlines()
  f.close()
  pc = np.random.randint(0,len(txt))
  return txt[pc]

'''Partie code'''

while(int(memeGen) !=1 and int(memeGen) !=2):
    memeGen = input('''Please enter which meme you wanna generate?:
1-a one panel meme (the most common meme format)
2-a two-panel meme(Example : the drake meme)  : ''')
    if int(memeGen) ==1:
        dirText = "textFolder/onepanel/"
        dirMemeFolder+='onepanel/'
        text1 = getMemeTxt(dirText)
        text2 = ""
        csvfile="onePanel"
        fontSize = 0.9

    elif int(memeGen) == 2:
        dirText = "textFolder/twopanel/"
        dirMemeFolder+='twopanel/'
        while text1==text2:
            text1 = getMemeTxt(dirText)
            text2 = getMemeTxt(dirText)
            if text1 == "Linux":
                text1,text2 = text2,text1
        csvfile="twoPanels"
        fontSize = 0.6
    else:
        print("Incorrect")

funline = text1.split('#',maxsplit=-1)
funline2 = text2.split('#',maxsplit=-1)

img,textPos1,textPos2 = imgGetter(dirMemeFolder,csvfile)

img2 = putText(img,text1=funline,text2=funline2,textPos1=textPos1,textPos2=textPos2)


imgSaver(img2)
