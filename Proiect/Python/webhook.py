import requests
import json

url = 'https://maker.ifttt.com/use/cJ9QhIWnyX9nbKMomkE7L1gzvUgS7ub9ARZXlJJ6XBZ'

data = { 'name': 'DevOps Journey', 
         'Channel URL': 'https://www.youtube.com/channel/UC4Snw5yrSDMXys31I18U3gg' }

r = requests.post(webhook_url, data=json.dumps(data), headers={'Content-Type': 'application/json'})