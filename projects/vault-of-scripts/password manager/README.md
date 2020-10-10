## Password Manager 
This is a script that manages (stores, loads and generates) your password localy (for all you paranoids that don't trust the tools available
all over the internet)

### Setup 
To get started you'll need to install the python packages.
To do that you can use the command 
```bash 
pip install requirements.txt
```

### Usage 
``` bash
cd 'password manager'
python main.py
```

### Tasks
Here are things you can do to complete this implementation:
* Complete the functions :
	* generate_password (done)
	* store_password (done)
	* load_password (Don't print the loaded passowrd Make sure that you copy it to the clipboard) (done)
* Add an encryption algorithm to make sure that the passwords stay safe even if the file is stolen (done)
* Use a database instead of a binary file (you can use google storage services if you want)
* Add A GUI to complete the app using pyQt or pyWebView

### Resource
* [pickle](https://docs.python.org/3/library/pickle.html)
* [pyperclip](https://pypi.org/project/pyperclip/)
* [pywebview](https://pypi.org/project/pywebview/)
* [PyQt5](https://pypi.org/project/PyQt5/)
* [pymongo](https://pypi.org/project/pymongo/)
* You'll find some encryption algorithms in this repo [Vigenere-chiffrement](https://github.com/openmindsclub/H4ckT0b3rF3st-2k20/tree/main/projects/vault-of-scripts/Vigenere-chiffrement
)<br/>
**Warning: this encrytpion is not secure and should not be used in to encrypt sensible data like passwords**

