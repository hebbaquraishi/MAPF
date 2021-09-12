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
import subprocess

os.chdir("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts")


class MapGenerator:
    def __init__(self, path, number_of_agents, number_of_goals):
        self.my_map = {"height": 0, "width": 0, "vertices": [], "obstacles": [], "water": []}
        self.path = path
        self.number_of_agents = number_of_agents
        self.number_of_goals = number_of_goals

    def convert_map_to_json(self):
        input_map = open(self.path, "r")
        map_row = 0

        for line in input_map:
            if line.startswith("type") or line.startswith("map"):
                continue
            elif line.startswith("height") or line.startswith("width"):
                self.my_map[line.split(" ")[0]] = int(line.split(" ")[1])
            else:
                for map_column in range(0, len(line)):
                    if line[map_column] == "@" or line[map_column] == "O" or line[map_column] == "T":
                        self.my_map["obstacles"].append([map_column, map_row])
                    elif line[map_column] == "." or line[map_column] == "G":
                        self.my_map["vertices"].append([map_column, map_row])
                    elif line[map_column] == "W":
                        self.my_map["water"].append([map_column, map_row])
                map_row += 1

        with open('results/my_map.json', 'w') as outfile:
            json.dump(self.my_map, outfile)


    def create_agents_json(self):
        agent_source_locations = random.sample(self.my_map["vertices"], self.number_of_agents)
        agent_names = list()
        agents = {"names": [], "initial": [], "goal": []}
        for i in range(0, self.number_of_agents):
            agent_names.append("agent"+str(i))

        agents["names"] = agent_names
        agents["initial"] = agent_source_locations

        for name in agent_names:
            agents["goal"].append(random.sample(self.my_map["vertices"], self.number_of_goals))

        with open('results/my_agents.json', 'w') as outfile:
            json.dump(agents, outfile)


if __name__ == "__main__":

    max_goals = 20
    max_agents = 20
    executable_path = "/Users/hebbaquraishi/Desktop/MAPF/CBS/MAPF"

    for a in range(2, max_agents):
        for g in range(2, max_goals):
            for n in range(1, 10):
                obj = MapGenerator(path="/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/maps/random-32-32-20.map", number_of_agents=a, number_of_goals=g)
                obj.convert_map_to_json()
                obj.create_agents_json()
                runcpp = subprocess.Popen([executable_path])
                runcpp.wait()