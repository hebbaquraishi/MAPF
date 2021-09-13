"""
Author: Hebba Quraishi
Email: quraishi@tf.uni-freiburg.de
"""

import json
import random
import os
import subprocess


class MapGenerator:
    def __init__(self, path, number_of_agents, number_of_goals) -> None:
        """
        Initialise the class variables
        # Parameters
        #   (string) path: path to the .map file (format can be found here: https://www.movingai.com/benchmarks/formats.html)
        #   (int) number_of_agents: number of agents to initialise on the map
        #   (int) number_of_goals: number of goals each agent must have
        """
        self.my_map = {"height": 0, "width": 0, "vertices": [], "obstacles": [], "water": []}
        self.path = path
        self.number_of_agents = number_of_agents
        self.number_of_goals = number_of_goals

    def convert_map_to_json(self) -> None:
        """
        Take a .map file and return a JSON representation of it.
        Output file name: my_map.json
        Output file location: ${WORKING_DIRECTORY}$/results/my_map.json
        """
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
    # Set working directory
    os.chdir("/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts")
    # path to C++ executable file
    executable_path = "/Users/hebbaquraishi/Desktop/MAPF/CBS/MAPF"
    # path to .map file
    map_path = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/maps/random-32-32-20.map"

    for a in range(2, max_agents):
        for g in range(2, max_goals):
            for n in range(1, 10):
                obj = MapGenerator(path=map_path, number_of_agents=a, number_of_goals=g)
                obj.convert_map_to_json()
                obj.create_agents_json()
                runcpp = subprocess.Popen([executable_path])
                runcpp.wait()