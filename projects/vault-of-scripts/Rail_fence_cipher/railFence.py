#!/usr/bin/env python3


def railFenceEncryption(plain_text, key):
    if key < 2:
        print('The encryption key must be > 1')
        exit

    cipher_text = ''
    step_down = (key - 1) * 2
    step_up = 0

    for line in range(key):
        cipher_text += plain_text[line]
        column = line
        while column < len(plain_text):
            if step_down > 0:
                column += step_down
                if column < len(plain_text): cipher_text += plain_text[column]
            if step_up > 0:
                column += step_up
                if column < len(plain_text): cipher_text += plain_text[column]
        step_down -= 2
        step_up += 2
    return cipher_text


def railFenceDecryption(cipher_text, key):
    return


if __name__ == '__main__':
    msg = str(input("Enter a message : \n"))
    try:
        key = int(input("Enter the encryption key (a number > 1) : \n"))
    except:
        print('The encryption key must be a number > 1')
        exit()
    else:
        print(railFenceEncryption(msg, key))
