#!/usr/bin/env python3

def railFenceEncryption(plain_text, e_key):
    cipher_text = ''
    step1 = (e_key - 1) * 2
    step2 = 0
    cycle = 1
    if e_key <= 0:
        print('key must be bigger than 1')
        exit
    elif e_key == 1:
        return plain_text
    else:
        for line in range(0, e_key):
            cipher_text += plain_text[line]
            column = line
            if line != e_key - 1:
                cycle = 1
            else:
                cycle = 0
            while column < len(plain_text):
                if (step1 > 0) and cycle:
                    column += step1
                    if column < len(plain_text): cipher_text += plain_text[column]
                    if line != 0: cycle = 0
                if step2 > 0 and not cycle:
                    column += step2
                    if column < len(plain_text): cipher_text += plain_text[column]
                    if line != e_key-1: cycle = 1
            step1 -= 2
            step2 += 2
        return cipher_text

def railFenceDecryption(cipher_text, e_key):
    return


if __name__ == '__main__':
    msg = str(input("Enter a message : \n"))
    try:
        key = int(input("Enter the encryption key (number) : \n"))
    except:
        print('Error: encryption key must be a number')
        exit()
    if key < 0:
        print('The encryption key must be a positive number')
        exit()
    else:
        print(railFenceEncryption(msg, key))
