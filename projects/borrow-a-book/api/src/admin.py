from flask_restful import Resource
from flask import request, session
from mongo import users, requests
from helpers import check_request, error_response
from bson.objectid import ObjectId


class Admin(Resource):

    def get(self):
        ''' Get account creation requests list '''

        if not session.get('admin', None):
            return 'Unauthorized', 401

        return [i for i in requests.find({'status': 'pending', 'type': 'account'})], 200

    def post(self):
        ''' Reply to an account creation request '''

        args_list = ['request_id', 'answer']

        if not session.get('admin', None):
            return 'Unauthorized', 401

        data = request.get_json()
        if not check_request(data, args_list) or type(data['answer']) != bool:
            return error_response

        pending_request = requests.find_one({'_id': ObjectId(data['request_id'])})
        if not pending_request or pending_request['type'] != 'account':
            return 'Request not found', 404

        requests.find_one_and_update(
            {
                '_id': pending_request['_id']
            },
            {
                '$set': {'status': 'answered', 'reviewer': session['name']},
                '$currentDate': {'lastModified': True}
            }
        )
        if data['answer']:
            user = {
                'first_name': pending_request['first_name'],
                'last_name': pending_request['last_name'],
                'password': pending_request['password'],
                'serial_number': pending_request['serial_number'],
                'book_requests': []
            }

            users.insert_one(user)

        return '', 200

    def put(self):
        ''' Add a book to the library '''
        pass

    def delete(self):
        ''' Remove a book from the library '''
        pass
