#import library
   import speech_recognition as sr
   # Initialize recognizer class (for recognizing the speech)
   def recog():
      r = sr.Recognizer()
      # Reading Microphone as source
      # listening the speech and store in audio_text variable
      with sr.Microphone() as source:
         print("Talk")
         audio_text = r.listen(source)
         print("Time over, thanks")
         # recoginize_() method will throw a request error if the API is unreachable, hence using exception handling
         try:
            # using google speech recognition
            print("Converting audio transcripts into text ...")
            print("Text: "+r.recognize_google(audio_text))
        except:
            print("Sorry, I did not get that")

   while(True):
      recog()
      x=input("Would you like to try again?? Type(yes/no)")
      if (x=='yes'):
         continue
      elif (x=='no'):
         print("Hope you liked this program!!!")
         break
      else:
         print("Invalid option")
         break
