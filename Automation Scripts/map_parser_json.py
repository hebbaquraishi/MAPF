"""
Author: Hebba Quraishi
Email: quraishi@tf.uni-freiburg.de

This code is divided into 2 sections:
Section 1:
    The objective of this section is to take a path to a .map file as input and convert it to a JSON file
    1) the .map file format can be found here: https://www.movingai.com/benchmarks/formats.html
    2) sample maps can be found here: https://movingai.com/benchmarks/mapf/index.html

Section 2:
    The objective of this section is to randomly generate agents and randomly assign start and end goals for the agents
"""

import json
import random
import os

os.chdir("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts")

#######################################
##           SECTION 1               ##
#######################################

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
        for map_column in range(0, len(line)):
            if line[map_column] == "@" or line[map_column] == "O" or line[map_column] == "T":
                my_map["obstacles"].append([map_column, map_row])
            elif line[map_column] == "." or line[map_column] == "G":
                my_map["vertices"].append([map_column, map_row])
            elif line[map_column] == "W":
                my_map["water"].append([map_column, map_row])
        map_row += 1

with open('results/my_map.json', 'w') as outfile:
    json.dump(my_map, outfile)


#######################################
##           SECTION 2               ##
#######################################

number_of_agents = random.randint(6,6)
number_of_goals = random.randint(5,5)
agent_source_locations = random.sample(my_map["vertices"], number_of_agents)
agent_names = list()
agents = {"names":[], "initial":[], "goal":[]}
for i in range(0, number_of_agents):
    agent_names.append("agent"+str(i))

agents["names"] = agent_names
agents["initial"] = agent_source_locations


for name in agent_names:
    agents["goal"].append(random.sample(my_map["vertices"], number_of_goals))


with open('results/my_agents.json', 'w') as outfile:
    json.dump(agents, outfile)