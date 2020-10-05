'''Welcome to C4324R Notis, an attempt at creating a caesar cypher using
python and my shitty knowledge this took me more or less 10 minutes
Vae Victis, AVE CAESAR
'''

#Step one : create an alphabet

import string
alphabetum = list(string.ascii_lowercase)

#Step two : giving a promt for writing a sentence.
nuntius = input('Please write the message you wanna code : \n Message : ')
rotatione = int(input('How many positions you want the cypher to rotate? : '))

#Step three : creating the caesar cypher.

def notis(nts, rotatione):
    codedNuntius = ''
    for i in nts:
        if i.isalpha() == False:
            codedNuntius += i
        else:
            statum = alphabetum.index(i.lower()) + rotatione
            codedNuntius += alphabetum[statum % 25]
    return codedNuntius

#Step four : print the ciphered message
print(notis(nuntius,rotatione))
