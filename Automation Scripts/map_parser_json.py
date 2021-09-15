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

    def get_agent_goals(self, init):
        x = random.sample(self.my_map["vertices"], self.number_of_goals)
        if (init not in x):
            return x
        else:
            return self.get_agent_goals(init)

    def convert_map_to_json(self, config) -> None:
        """
        Take a .map file and return a JSON representation of it.
        Output file name: my_agents.json
        Output file location: ${WORKING_DIRECTORY}$/results/my_agents.json
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
                        self.my_map["obstacles"].append([map_row, map_column])
                    elif line[map_column] == "." or line[map_column] == "G":
                        self.my_map["vertices"].append([map_row, map_column])
                    elif line[map_column] == "W":
                        self.my_map["water"].append([map_column, map_row])
                map_row += 1

        with open('results/my_map.json', 'w') as outfile:
            json.dump(self.my_map, outfile)

        with open('configs/my_map_agent_'+str(self.number_of_agents)+'_goals_'+str(self.number_of_goals)+'_config_'+str(config)+'.json', 'w') as configfile:
            json.dump(self.my_map, configfile)

    def create_agents_json(self, config):
        """
        Initialises agents on a map
        Output file name: my_map.json
        Output file location: ${WORKING_DIRECTORY}$/results/my_map.json
        """
        agent_source_locations = random.sample(self.my_map["vertices"], self.number_of_agents)
        agent_names = list()
        agents = {"names": [], "initial": [], "goal": []}
        for i in range(0, self.number_of_agents):
            agent_names.append("agent" + str(i))

        agents["names"] = agent_names
        agents["initial"] = agent_source_locations

        for i in range(0, len(agent_names)):
            init = agent_source_locations[i]
            x = self.get_agent_goals(init[0])
            agents["goal"].append(x)

        with open('results/my_agents.json', 'w') as outfile:
            json.dump(agents, outfile)

        with open('configs/my_agents_agent_'+str(self.number_of_agents)+'_goals_'+str(self.number_of_goals)+'_config_'+str(config)+'.json', 'w') as configfile:
            json.dump(agents, configfile)


if __name__ == "__main__":
    max_goals = 15
    max_agents = 20
    # TODO: Set working directory
    working_directory = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/"
    os.chdir(working_directory)
    if not os.path.exists('results'):
        os.mkdir(working_directory + "results")
    if not os.path.exists('configs'):
        os.mkdir(working_directory + "configs")
    # TODO: Set path to C++ executable file
    executable_path = "/Users/hebbaquraishi/Desktop/MAPF/CBS/MAPF"
    # TODO: Set path to .map file
    map_path = "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/maps/random-32-32-20.map"

    for a in range(2, max_agents+1):
        for g in range(2, max_goals+1):
            for n in range(1, 11):
                obj = MapGenerator(path=map_path, number_of_agents=a, number_of_goals=g)
                obj.convert_map_to_json(n)
                obj.create_agents_json(n)
                runcpp = subprocess.Popen([executable_path])
                runcpp.wait()
