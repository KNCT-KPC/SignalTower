import requests
from bs4 import BeautifulSoup
import time
import re

y = input('学科を入れてね！　')

if y == '情報':
    html = open('Jyouhou.html','r',encoding='utf-8').read()
elif y == '機械':
    html = open('Kikai.html','r',encoding='utf-8').read()
elif y == '電気':
    html = open('Denki.html','r',encoding='utf-8').read()
elif y == '電子':
    html = open('Densi.html','r',encoding='utf-8').read()
elif y == '建築':
    html = open('Kentiku.html','r',encoding='utf-8').read()
elif y == '一般':
    html = open('Ippan.html','r',encoding='utf-8').read()
x = input('教員の名字を入れてね!　')


soup = BeautifulSoup(html,'html.parser')
scry = soup.find('div',{'class','pico_orgbody'})
target = scry.find_all('tr')

i = 1
while i < len(target):
    if target[i].find('td') != None:
        if x == str(target[i].find('td').text).split('　')[0]:
            print(target[i].text)
    i += 1
