import requests

URL = "http://localhost"
PORT = "8090"
# Session = requests.Session()
# Request = Session.post(URL+':'+PORT+'/', data={'name':'AuthedUserName'})
r = requests.session()
#r.config['keep_alive'] = False
#r = requests.post("http://localhost:8090", data={'text': "hello"})

response =r.post("http://localhost:8090", data={'text': "hello"})
print response.text
print("finished")