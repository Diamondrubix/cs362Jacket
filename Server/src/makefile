JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
        Main.java \
        Client.java \
        Server.java

default: classes

classes: $(CLASSES:.java=.class)

run:
	java Main

clean:
	$(RM) *.class

