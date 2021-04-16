"""
Author: Hebba Quraishi
Email: quraishi@tf.uni-freiburg.de

The objective of this script is to take a path to a .map file as input and convert it to a YAML file
1) the .map file format can be found here: https://www.movingai.com/benchmarks/formats.html
2) sample maps can be found here: https://movingai.com/benchmarks/mapf/index.html
"""

import json

my_map = {"height": 0, "width": 0, "vertices": [], "obstacles": [], "water": []}
path = input("Please enter the path to the .map file\n")
input_map = open(path, "r")
map_row = 0

for line in input_map:
    if line.startswith("type") or line.startswith("map"):
        continue
    elif line.startswith("height") or line.startswith("width"):
        my_map[line.split(" ")[0]] = int(line.split(" ")[1])
    else:
        for i in range(0, len(line)):
            if line[i] == "@" or line[i] == "O" or line[i] == "T":
                my_map["obstacles"].append([map_row, i])
            elif line[i] == "." or line[i] == "G":
                my_map["vertices"].append([map_row, i])
            elif line[i] == "W":
                my_map["water"].append([map_row, i])
        map_row += 1

with open('my_map.json', 'w') as outfile:
    json.dump(my_map, outfile)
