# Multi Agent Path Finding (MAPF)

## Automation Scripts
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


#### map_parser_json.py
This script takes a .map file as an input and 
1. returns a JSON represention of the map
2. initialises a random number of agents on the map. Each agent is assigned a random start location and a random number of goals


## CBS 
This folder contains C++ code to implement Conflict Based Search for agents with multiple goals

## Question to ask
<img width="782" alt="Screenshot 2021-08-02 at 00 13 33" src="https://user-images.githubusercontent.com/17808885/127842078-437c85ac-6821-4c35-8984-ff809322f22a.png">
