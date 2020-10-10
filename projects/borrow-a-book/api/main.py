from flask import Flask
from flask_restful import Api
from os import urandom


app = Flask(__name__)
app.secret_key = urandom(16)
api = Api(app)


if __name__ == "__main__":
    app.run()
