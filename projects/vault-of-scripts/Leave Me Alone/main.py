from fbchat import Client # pip install fbchat
from fbchat.models import *
from datetime import datetime, timedelta
import time
import random

# Credentials
email = 'email' # Put your email here
pwd = 'password' # Put your password here

# Back listed users
black_list = {
  "jaegger666": "Lilly",
  "VinDiesel": "Vin Diesel",
  "zuck": "Zucc"
}

# Custom Replies
replies = [".", "...", "wtf", "lmao", "lol", "holy shit", "jesus", "hmmm", "rip", "I wanna kms", "idk tbh", "stghf", "cc", "ayah", "ehhhh", "sokka", "naruhodo", "a?", "ah?", "ummm", "🙁", "🤐", "🤣", "🤔", "👩", "nibbaaaa", "ewi", "denya s3iba", "well...", "hahahaha", "XDDDDDDDDDDDDDDDDDD", "man", "welp", "yikes", "je3t", "n3est, gotta go bye", "sinon cv", "ahhh"]

# Variables
now = int(time.mktime(datetime.now().timetuple()))
delta = timedelta(hours = 5).total_seconds() # Choose the time that you see as long enough to be considered ignoring 

def GrabUserID(client, user):
    try:
        return(client.searchForUsers(user, limit=1)[0].uid)
    except:
        return(user)

def wasIgnored(client, user_id):
    message = client.fetchThreadMessages(thread_id = user_id, limit = 1)[0] # Fetch last message in thread
    print('Message: ', message.text)  # Print message text
    if(message.author != client.uid):
        # You are not the author, check message timestamp
        ts = int(message.timestamp)/1000 # divide by 1000 to convert from ms to s
        if(now - delta > ts):
            # Message was sent more than 2 hours ago, user was ignored
            return(True)
        else:
            # 2 hours not yet elapsed since message, user not ignored
            return(False)
    else:
        # You are the author, user not ignored
        return(False)

def AutoReply(client, user_id):
    reply = replies[random.randint(0, len(replies) - 1)] # Choose random reply from list
    client.send(Message(text = reply), thread_id = user_id, thread_type = ThreadType.USER) # Send text message
    return(reply)

def main():
    client = Client(email, pwd) # Connect client
    for user in black_list:
        user_id = GrabUserID(client, user) # Grab User ID
        print("User '" + black_list[user] + "' grabbed.") # Print prompt

        if(wasIgnored(client, user_id)):
            reply = AutoReply(client, user_id) # Auto reply if user was ignored
            print("Replied with: " + reply + ".\n" )
        else:
            print("User not ignored yet.\n")

if __name__ == "__main__":
    main()
