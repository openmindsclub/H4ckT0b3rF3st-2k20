'''
Make sure that secret.key exists in directory
if not, generate it with generate_key() once 
'''
from cryptography.fernet import Fernet  # pip install cryptography
import pickle   # pip install pickle
import pyperclip    # pip install pyperclip
from random import seed, randint
import os

# Generate keyfile once with "generate_key()" and hide it in a secure place
def generate_key():
    key = Fernet.generate_key()
    with open("secret.key", "wb") as key_file:
        key_file.write(key)

# Load key from keyfile
def load_key():
    return open("secret.key", "rb").read()

# Return encrypted password
def encrypt_message(message):
    key = load_key()
    encoded_message = message.encode()
    f = Fernet(key)
    encrypted_message = f.encrypt(encoded_message)

    return(encrypted_message)

# Return decrypted password
def decrypt_message(encrypted_message):
    key = load_key()
    f = Fernet(key)
    decrypted_message = f.decrypt(encrypted_message)

    return(decrypted_message.decode())

# Load password from binary file
def load_password(website):
    # if file doesn't exist, exit with prompt
    if(not(os.path.isfile('./passwords.bin'))):
        print("No password stored")
    else:
        # if file exists and if website already recorded, retrieve decrypted password
        passwords_file = open("passwords.bin", "rb")
        passwords_dict = pickle.load(passwords_file)

        if website in passwords_dict:
            pyperclip.copy(decrypt_message(passwords_dict[website]))
            print('Password copied to clipboard.')
            passwords_file.close()
        else:
            # if website doesn't exist, exit with prompt
            print("This password is not stored")
            passwords_file.close()

# Store password to binary file
def store_password(website, password):
    # encrypt password
    password = encrypt_message(password)
    # if file doesn't exist, create a new file and record encrypted password
    if(not(os.path.isfile('./passwords.bin'))):
        passwords_file = open("passwords.bin", "wb")
        passwords_dict = {website: password}
        pickle.dump(passwords_dict, passwords_file)
        passwords_file.close()
    else:
        # if file exists and if record already exists, exit with prompt
        passwords_file = open("passwords.bin", "rb")
        passwords_dict = pickle.load(passwords_file)

        if website in passwords_dict:
            print("Password already stored.")
            passwords_file.close()
        else:
        # if record doesn't exist, save record and exit
            passwords_file.close()

            passwords_file = open('passwords.bin', 'wb')
            passwords_dict[website] = password
            pickle.dump(passwords_dict, passwords_file)
            passwords_file.close()

if __name__ == "__main__":
    if(int(input('''
    Do you want to:
        (0) Store a password
        (1) Load a password

    >>> '''))):
        load_password(input("\nWebsite : "))
    else:
        store_password(input("\nWebsite : "), input("Password : "))
