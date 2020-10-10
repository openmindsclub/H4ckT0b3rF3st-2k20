from flask_restful import Resource
from flask import request, session
from helpers import check_request, hash_password, error_response
from mongo import users


class Login(Resource):

    def post(self):
        args_list = ['email', 'password']

        data = request.get_json()
        if not check_request(data, args_list):
            return error_response

        user = users.find_one({'email': data['email'], 'password': hash_password(data['password'])})
        if not user:
            return 'Invalid email/password', 401

        _id = user['_id']
        session['id'] = _id.binary

        return '', 200

    def delete(self):
        ''' Logout '''

        session.pop('_id', None)
        return '', 200
