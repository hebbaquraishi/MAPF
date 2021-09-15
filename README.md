# Multi Agent Path Finding (MAPF)
The purpose of this project is to extend a MAPF problem such that each agent has multiple goals. Conflict Based Search (CBS) is used to detect conflicts between agents. In the low level search of CBS, three versions of Travelling Salesman Problem (TSP) is used to determine the order in which each agent should visit its goals i.e.
1. TSP Exact : generates all ```n!``` permutations of goal traversal orders and returns the most optimal one
2. TSP Branch and Bound : returns the optimal goal traversal order in a branch and bound manner
3. TSP Nearest Neighbour : returns the goal traversal order by picking up goals in a greedy manner

# Automation Scripts
This folder contais Python scripts for automating certain tasks. <br/> 
The directory structure is as shown below : \
\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ ```configs``` (all map and agent configs used in testing and evaluation)\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ my_agents_agent_2_goals_2_config_1.json\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ my_agents_agent_2_goals_2_config_2.json\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ .....\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ my_agents_agent_20_goals_20_config_10.json\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ ```maps```  (all maps used in testing and evaluation)\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ random-32-32-20.map\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ room-64-64-16.map\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ warehouse-10-20-10-2-1.map\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ ```results``` (JSON file containing the final results of the project)\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ results.json\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|___ ```map_parser_json.py```


## map_parser_json.py
This script takes a .map file as an input and 
1. Returns a JSON represention of the map
2. Initialises agents  on the map. Each agent is assigned a random start location and a number of goals such that ```2 <= number of agents <= 20 and 2 <= number of goals per agent <= 20```. <br/> Each configuration that is generated is stored in ```configs```
3. Runs an MAPF instance on each configuration produced in 2.

<br/>Before running ```map_parser_json.py```, the values of ```working_directory```, ```executable_path```, and ```map_path``` must be set.\
Hint: search for ```TODO``` in ```map_parser_json.py``` to find the aforementioned variables.

<br/>
<br/>

# CBS 
This folder contains C++ code to implement Conflict Based Search for agents with multiple goals.\
To run this code:
1. Download and install nlohmann::json. [Instructions here](https://github.com/nlohmann/json). <br/> If you have a MacBook, you can directly use [Homebrew](https://brew.sh/) command ```brew install nlohmann-json```.
2. Provide the path of the ```include``` folder of ```nlohmann-json``` in ```CMakeLists.txt``` on line 10. <br/> Example: ```target_include_directories(MAPF SYSTEM PRIVATE /opt/homebrew/Cellar/nlohmann-json/3.9.1_1/include)```.
3. Open Terminal (MacBook) or Command Line Prompt (Windows) and navigate to the ```CBS``` directory of this repository <br/> Example: ```cd Desktop/MAPF/CBS```
4. Run command ```cmake ..```
5. Run command ```make -f Makefile``` 
6. You will now have a ```Makefile``` and ```MAPF executable``` file in the ```CBS``` directory. Set the value of ```executable_path``` in ```map_parser_json.py``` to the path of the ```MAPF executable``` file.
7. Since the ```MAPF executable``` file is now available, you can run ```map_parser_json.py```

<br/>

## Flow Diagram
![alt text](https://github.com/hebbaquraishi/MAPF/blob/38141bc54117e68a3bfbdd9a323c490fe2606ee2/Flow%20Diagram.jpg)
