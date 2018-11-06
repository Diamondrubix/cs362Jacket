import argparse
parser = argparse.ArgumentParser()
parser.parse_args()


parser.add_argument("square", help="display a square of a given number",
                    type=int)
parser.add_argument("other")
args = parser.parse_args()
print args
#print args.square**2
print int(args.square)+int(args.other)