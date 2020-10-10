from flask_restful import Resource
from flask import request, session
from helpers import check_request, hash_password, error_response
from os import urandom
from mongo import users, requests
from bson.objectid import ObjectId


class Account(Resource):

    def get(self):
        ''' Get account info, if the account exists '''

        _id = session['id']
        user_info = users.find_one({'_id': ObjectId(_id)})
        if user_info:
            return user_info, 200

        return 'User not found', 404

    def post(self):
        ''' Submit a account creation request, to be reviewed by an admin to verify
            whether the requester is a student '''

        args_list = ['first_name', 'last_name', 'email', 'serial_number', 'description', 'password']

        data = request.get_json()
        if not check_request(data, args_list):
            return error_response

        if 'student_id' not in request.files:
            return error_response

        student_id = request.files['student_id']
        if not student_id.filename or student_id.filename[-4:] not in ['.png', '.jpg']:
            return error_response

        for arg in ['email', 'serial_number']:
            if users.find_one({arg: data[arg]}):
                return f'An account with the same {arg} exists', 400

            if requests.find_one({arg: data[arg]}):
                return f'An account creation request with the same {arg} exists', 400

        student_id.filename = urandom(16).hex() + student_id.filename[-4:]
        student_id.save(f'student_ids/{student_id.filename}')

        data['student_id'] = student_id.filename
        data['password'] = hash_password(data['password'])
        data['status'] = 'pending'
        data['type'] = 'account'

        requests.insert_one(data)

        return 'Account creation request submitted succesfully, an admin will contact you soon', 200
