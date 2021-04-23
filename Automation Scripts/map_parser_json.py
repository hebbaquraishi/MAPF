"""
Author: Hebba Quraishi
Email: quraishi@tf.uni-freiburg.de

The objective of this script is to take a path to a .map file as input and convert it to a JSON file
1) the .map file format can be found here: https://www.movingai.com/benchmarks/formats.html
2) sample maps can be found here: https://movingai.com/benchmarks/mapf/index.html
"""

import json
import random

"""
This section of the code is used to parse a map
"""

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
                my_map["obstacles"].append([map_row, map_column])
            elif line[map_column] == "." or line[map_column] == "G":
                my_map["vertices"].append([map_row, map_column])
            elif line[map_column] == "W":
                my_map["water"].append([map_row, map_column])
        map_row += 1

with open('my_map.json', 'w') as outfile:
    json.dump(my_map, outfile)


"""
This section of the code is used to randomly generate agents and randomly assign start and end goals for the agents
"""

number_of_agents = random.randint(1, 3)
number_of_goals = random.randint(1, 3)
agent_source_locations = random.sample(my_map["vertices"], number_of_agents)
agent_names = list()
agents = dict()
for i in range(0, number_of_agents):
    agent_names.append("agent"+str(i))

for name in agent_names:
    agents[name] = dict()
    agents[name]["initial"] = agent_source_locations.pop()
    agents[name]["goal"] = random.sample(my_map["vertices"], number_of_goals)

print(agent_names)
print(agents)

with open('my_agents.json', 'w') as outfile:
    json.dump(agents, outfile)