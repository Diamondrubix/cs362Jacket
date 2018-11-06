from post import post

p = post()


def getText():
    return "Number:this is a reply"


def sendText(message):
    #print"this sends a text with message " + message
    print getText()

class texting:

    def main(self):
        texting = True;
        while(texting):
            input = raw_input("Texting~")
            if(input[0:1] == '/'):
                if(input == "/exit"):
                    texting =False
            else:
                sendText(input)



