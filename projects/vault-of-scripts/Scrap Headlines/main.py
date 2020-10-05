import requests
from bs4 import BeautifulSoup

keyword = "BLM" # Change Keyword here.
urls = [
    'https://www.nytimes.com/',     # New york Times
    'https://www.huffpost.com/',    # Huffing Post
    'https://www.usatoday.com/',    # USA Today
    'https://www.wsj.com/',         # WallStreet Journal
    'https://www.latimes.com/',     # LA Times
    'https://www.theguardian.com/international',    # The Guardian International
    'http://global.chinadaily.com.cn/']             # China Daily
tags = ['h2', 'h3', 'span', 'a']
headlines = []

def display(headlines):
    for headline in headlines:
        print(headline + '\n')

def parse(urls, tags, keyword):
    # Iterate through all newspaper websites
    for url in urls:
        print("Parsing " + url + "...") # Display start of parsing prompt
        # Send HTTP/1.1 request to current url
        r = requests.get(url)
        # Parsing the current url
        soup = BeautifulSoup(r.text, 'lxml')

        # Iterate through all tags
        for tag in tags:
            # Iterate through all the headlines found
            for headline in soup.find_all(tag):
                # Add the headline to list of headlines if it contains the specified keyword
                if keyword in headline.text:
                    headlines.append(headline.text)

        print("Done.") # Display end of parsing prompt

parse(urls, tags, keyword)
display(headlines)
