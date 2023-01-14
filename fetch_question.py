import os
import random
import sys

if len(sys.argv) < 3:
    print("Please make sure you execute the program with the proper arguments.")
    exit(1)

topic, difficulty = [arg.lower() for arg in sys.argv[1:3]]
print(topic, difficulty)
filename = f"questions/{topic}/{topic.replace(' ', '_')}_{difficulty}.txt"

if not os.path.isfile(filename):
    print("The file for the entered topic and difficulty doesn't exist.")
    exit(2)

with open(filename, "r") as file:
    lines = file.readlines()
    print(random.choice(lines), end="")
