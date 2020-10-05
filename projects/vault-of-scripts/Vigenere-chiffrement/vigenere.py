'''
Welcome to yet another attempt at being a bad programmer, brought to you by
the rainy rain. Today, we're gonna try to implement the vigenere cypher, or
as they call it "Le Chiffrement de Vigenère". So come follow my adventures.
'''
#Step rei : create an alphabet.

import string

alphabet = list(string.ascii_lowercase)

#Step one : get the message to cypher.

missive = input("Please enter the message you wanna cypher, general : ")

#Step two : make a cypher key (it'll be randomly generated, you just enter the
#length of the key.
import random
key = int(input("please enter the length of the key you wanna use : "))

cle = ''
for i in range(key):
    cle += alphabet[random.randint(0,25)]

#Step three : create the vigenere cypher
#Many problems have to be solved here.

def chiffre_vigenere(missive):
    missiveChiffre = ''
    for i in range(len(missive)):
        if missive[i].isalpha() == False:
            missiveChiffre += missive[i]
        else:
            rotation = cle[i % 3]
            pos = alphabet.index(missive[i].lower()) + alphabet.index(rotation)
            missiveChiffre += alphabet[pos % 25].upper()
    return missiveChiffre

#Step Four : test the vigenere cypher.
cypher = chiffre_vigenere(missive)
print(cypher)
