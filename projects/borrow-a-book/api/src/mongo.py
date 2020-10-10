from pymongo import MongoClient


client = MongoClient('localhost', 27017)
db = client.library
users = db.users
books = db.books
requests = db.requests
