from flask_restful import Resource
from flask import request, session
from mongo import books, users, requests
from helpers import check_request, error_response
from bson.objectid import ObjectId


class Books(Resource):

    def get(self):
        ''' Get list of all books '''

        if not session.get('id', None):
            return 'Not a member', 401

        return [i for i in books.find()]

    def post(self):
        ''' Submit a book borrow request '''

        args_list = ['book_id', 'borrow_time']
        if not session.get('id', None):
            return 'Not a member', 401

        data = request.get_json()
        if not check_request(data, args_list):
            return error_response

        book_request = {
            'book_id': data['book_id'],
            'borrow_time': data['borrow_time'],
            'type': 'book'
        }

        result = requests.insert_one(book_request)
        user = users.find_one({'_id': ObjectId(session['id'])})
        users.find_one_and_update(
            {
                '_id': user['_id']
            },
            {
                '$set': {'book_requests': user['book_requests'] + [result.inserted_id]},
                '$currentDate': {'lastModified': True}
            }
        )

        return '', 200
