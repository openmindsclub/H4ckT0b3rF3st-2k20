from hashlib import sha256
from secret import SALT


error_response = 'Invalid Request Body', 400


def check_request(data, args_list):
    if not data:
        return False

    for arg in args_list:
        if arg not in data.keys() or not data[arg]:
            return False

    return True


def hash_password(password):
    return sha256(SALT + password).hexdigest()
