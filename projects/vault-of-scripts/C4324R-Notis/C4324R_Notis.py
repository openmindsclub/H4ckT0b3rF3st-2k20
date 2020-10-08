import string

def notis(nts, rotatione, alphabetum):
#Step four : creating the cipher from message
  codedNuntius = ''
  for i in nts:
      if i.isalpha() == False:
          codedNuntius += i
      else:
          statum = alphabetum.index(i.lower()) + rotatione
          codedNuntius += alphabetum[statum % 25]
  return codedNuntius

def recito(nts, rotatione, alphabetum):
#Step four : deciphering the message
  decodedNuntius = ''
  for i in nts:
      if i.isalpha() == False:
          decodedNuntius += i
      else:
          statum = alphabetum.index(i.lower()) - rotatione
          decodedNuntius += alphabetum[statum % 25]
  return decodedNuntius

def main(alphabetum):
    #Step two : giving a promt for writing a sentence.
    arbitrium = int(input('''
    Do you want to:
      (1) Cypher a Message
      (2) Decypher a Message
    >>> '''))
    nuntius = input('\nMessage : ')
    rotatione = int(input('Number of rotations : '))

    #Step three : user chooses to either cipher or decipher
    if(arbitrium == 1):
    #Step five : print the ciphered message
      print('>>> ', notis(nuntius, rotatione, alphabetum))
    else:
    #Step five : print the deciphered message
      print('>>> ', recito(nuntius, rotatione, alphabetum))

if __name__ == "__main__":
    #Step one : create an alphabet
    alphabetum = list(string.ascii_lowercase)
    main(alphabetum)
