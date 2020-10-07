from pickle import load, dump
from pyperclip import copy
from random import seed, randint


def load_password(website):
    passwords_file = open("passwords.bin", "rb")
    # complete this function to load passwords

    passwords_file.close()


def store_password(website, password):
    try:
        passwords_file = open("passwords.bin", "rb")
        passwords = load(passwords_file)
    except:
        passwords_file = open("passwords.bin", "wb")
    # complete function to store passwords
    passwords_file.close()


def generate_password(
    nb_chars=16,
    include_special_chars=False,
    contains_uppercase=False,
    contains_numbers=False,
):
    special_char_range = [i for i in range(32, 48)]
    special_char_range.extend([i for i in range(58, 65)])
    special_char_range.extend([i for i in range(91, 97)])
    special_char_range.extend([i for i in range(123, 127)])
    char = {
        "lowercase_chars": [chr(i) for i in range(97, 123)],
        "uppercase_chars": [chr(i) for i in range(65, 91)],
        "special_chars": [chr(i) for i in special_char_range],
        "numbers": [chr(i) for i in range(48, 58)]
    }
    # complete function to generate a password


if __name__ == "__main__":
    seed()
    if(int(input("Do you want to:\n0-Store a password or\n1-load a password:\n"))):
        load_password(input("website:"))
    else:
        store_password(input("website:"), input("password:"))
        generate_password()
