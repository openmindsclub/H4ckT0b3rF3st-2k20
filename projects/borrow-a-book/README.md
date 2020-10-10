# Borrow a Book

An app to borrow books from the club's library, keep logs of the members who borrowed a book, the persons who reviewed their request, and the return deadline

## Overview

The project consists of a RESTful API and a Flutter app with MongoDB as a database solution, the API is made using `Flask`

## API

the development of the api was made using `python 3.8`, so it's best to create a virtual env with this version.

to install the dependencies, run:

```bash
pip install -r requirements.txt
```

to deploy the api, run:

```bash
python main.py
```

the API features the following services:

* `/account`: 
    * Submit account creation requests, and store them for review later, the request must contain a student id to verify that the one sending a request is a student

    * Get an account's info

* `/admin`: 
    * Reply to an account creation request, storing the answer to that request and the reviewer for logging purposes

    * View all the pending requests

* `/login`:
    * Login and logout

* `/books`: 
    * Submit a book borrow request

    * View pending book borrow requests(to be performed by an admin)

More Docs Coming soon