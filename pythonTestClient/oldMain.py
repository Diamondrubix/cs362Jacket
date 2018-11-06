from texting import texting
from post import post
import sys

#import argparse

url = "http://ec2-34-207-101-233.compute-1.amazonaws.com"
#url = "http://localhost"
p = post()
key = 0


def main2():
    running = True
    command = "null"
    play = True;

    while (running):
        running = False

        #command = raw_input("CNTLR~")
        if (sys.argv[1] == "battery"):
            battery()
        elif (sys.argv[1] =="chat"):
            chat()
        elif (sys.argv[1] == "texting" or sys.argv[1] == "text"):
            message =""
            for i in range(3,len(sys.argv)):
                message +=sys.argv[i]+" "
            text(sys.argv[2],message)
        elif (str(sys.argv[1])[0:6] == "volume"):
            print str(sys.argv[2])
            if (str(sys.argv[2])[0:2] == "++"):
                volume(1)
            elif (str(sys.argv[2])[0:2] == "--"):
                volume(-1)
            elif (str(sys.argv[2])[0:1] == "+"):
                volume(int(str(sys.argv[2])[1:len(command)]))
            elif (str(sys.argv[2])[0:1] == "-"):
                volume(int(str(sys.argv[2])[1:len(command)]))
            else:
                print "not a valid command vol"
        elif (sys.argv[1] == "exit"):
            running = False
        elif (sys.argv[1] == "login"):
            login()
        elif (sys.argv[1] == "signup"):
            signup()
        elif (sys.argv[1] == "audio"):
            audio(sys.argv[2])
        elif (sys.argv[1] == "t"):
            message =""
            for i in range(2,len(sys.argv)):
                print sys.argv(i)
            text(sys.argv[2],"test")
        else:
            print "not valid command"  # will implement a help options later


def main():
    running = True
    command = "null"
    play = True
    while(running):
        command = raw_input("CNTLR~")
        if(command == "battery"):
            battery()
        elif(command == "texting" or command =="text"):
            text(16302461919, "demo text")
        elif(command[0:6] == "volume"):
            if(command[7:9]=="++"):
                volume(1)
            elif(command[7:9] =="--"):
                volume(-1)
            elif(command[7:8] =="+"):
                volume(int(command[8:len(command)]))
            elif(command[7:8] =="-"):
                volume(int(command[8:len(command)]))
            else:
                print "not a valid command"
        elif(command[0:4] == "test"):
            test(command[5:len(command)])
        elif(command =="exit"):
            running = False
        elif(command =="login"):
            login()
        elif(command =="signup"):
            signup()
        elif(command =="t"):
            if(play):
                play = False
                audio("play")
            else:
                play = True;
                audio("pause")
        else:
            print "not valid command"#will implement a help options later

def audio(action):
    p.send(url + ":8090/music", {'key': key, 'action': action})



def music():
    print key
    p.send(url+":8090/music",{'key':key,'action':"play"})



def battery():
    #does the code to return battery
    print "the battery lv"
    #p.send("battery")

def chat():
    t = texting()
    t.main()
    #will start the section that deals with textiing.

def text(number, message):
    p.send(url+":8090/message",{'key':key,'number':str(number),'content':message})
    #print p

def volume(change):
    #this will add change to the volume of the phone
    #print "volume changed by "+str(change)
    #p.send("volume "+str(change))
    p.send(url + ":8090/message", {'volum': change})

def login():
    global key
    key = (p.send(url+":8090/login",{'username':'marc','password':'admin'}).text)
    print key
    key = key[9:-2]
    #key = (p.send(url+":8090/login",{'username':'marc','password':'admin'}).text)
    print key
    write(key)
    #print key[9:-2]

def signup():
    #p.send(url+":8090/signup",{'username': "username",'password':'password','email':'email'})
    p.send(url+":8090/signup", {'username':'adam','password':'password1','email':'emailThing'})
    #{'text': str(packet)}


def song(next):
    if(next):
        #print "went to next song"
        p.send(url+":8090/","next song")
    else:
        #print "went to previous song"
        p.send(url+"/","previous song")


def write(keyer):
    target = open('key.txt', 'w')
    target.truncate()
    target.write(keyer)
    target.close()

def readKey():
    file=open('key.txt', 'r')
    return file.read()


#print args
#if(args.square!=None):
 #   main2()
#else:
#print (len(sys.argv))
key = readKey()
if(len(sys.argv)>1):
   # print "main2"
    main2()
else:
    #print "main"
    main()
