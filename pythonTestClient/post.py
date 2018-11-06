import requests

class post():
    def send(self,URL,packet):
        #URL="http://localhost"
        PORT="8090"
        r = requests.session()
        response = r.post(URL, data=packet)
        return response