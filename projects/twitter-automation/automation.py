from webdriver_manager.firefox import GeckoDriverManager
from selenium import webdriver
import time
#setting driver for mozilla browser
driver = webdriver.Firefox(executable_path=GeckoDriverManager().install())
driver.get('https://twitter.com/login')
email = "your email" # put ur email here
password = "your password" # put ur password here

loginField = driver.find_element_by_xpath('/html/body/div/div/div/div[2]/main/div/div/div[1]/form/div/div[1]/label/div/div[2]/div/input')

passwordField = driver.find_element_by_xpath('/html/body/div/div/div/div[2]/main/div/div/div[1]/form/div/div[2]/label/div/div[2]/div/input')

loginButton = driver.find_element_by_xpath('/html/body/div/div/div/div[2]/main/div/div/div[1]/form/div/div[3]/div/div')

#start automation by sending login credentials
loginField.send_keys(email)
passwordField.send_keys(password)
time.sleep(1)

loginButton.click()

# automating posting tweet
tweet = "Hello Everyone! This is a tweet that I am sending from a selenium automated script written in Python ( It feels really awesome (: ) . \n - Amdjedbens"

tweetInputField = driver.find_element_by_xpath(
  '/html/body/div/div/div/div[2]/main/div/div/div/div/div/div[2]/div/div[2]/div[1]/div/div/div/div[2]/div[1]/div/div/div/div/div/div/div/div/div/div[1]/div/div/div/div[2]/div')

tweetInputField.send_keys(tweet)

time.sleep(1)

tweetButton = driver.find_element_by_xpath(
  '/html/body/div/div/div/div[2]/main/div/div/div/div/div/div[2]/div/div[2]/div[1]/div/div/div/div[2]/div[4]/div/div/div[2]/div[3]')

tweetButton.click()
