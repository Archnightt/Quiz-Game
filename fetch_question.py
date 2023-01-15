import os
import random
import sys

if len(sys.argv) < 3:
    print("Please make sure you execute the program with the proper arguments.")
    exit(1)

topic, difficulty = [arg.lower() for arg in sys.argv[1:3]]
filename = f"questions/{topic}/{topic.replace(' ', '_')}_{difficulty}.txt"

if not os.path.isfile(filename):
    print("The file for the entered topic and difficulty doesn't exist.")
    exit(2)

questions_done = list(map(int, sys.argv[3:]))
with open(filename, "r") as file:
    lines = file.readlines()
    new_lines = []

    for index, line in enumerate(lines):
        if index in questions_done:
            continue

        new_lines.append(lines[index])

    print(random.choice(new_lines), end="")
