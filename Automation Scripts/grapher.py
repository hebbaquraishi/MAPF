"""
Author: Hebba Quraishi
Email: quraishi@tf.uni-freiburg.de
"""


import pandas as pd
import json
import numpy as np
import matplotlib.pyplot as plt

def create_dataset(location: str) -> pd.DataFrame:
    result_file = open(location, 'r')
    result_lines = result_file.readlines()
    dataset = pd.DataFrame()
    for line in result_lines:
        entry = json.loads(line)
        dataset = dataset.append(entry, ignore_index=True)
    return dataset


def find_mean(mylist):
    total = 0
    count = 0
    for i in range(len(mylist)):
        if not np.isnan(mylist[i]):
            total += mylist[i]
            count += 1
    if count > 0:
        return round(total/count,2)
    else:
        return 0.0

def preprocess_dataset(dataset: pd.DataFrame) -> pd.DataFrame:
    dataset = dataset.replace(-1, np.NaN)
    dataset = dataset.replace(-99, np.NaN)
    dataset = dataset.dropna(subset=["tsp-exact-cbs", "tsp-branch-and-bound-cbs"], thresh=1)
    dataset = dataset.dropna(subset=["tsp-exact-cbs", "tsp-nn-cbs"], thresh=1)
    dataset.sort_values(by=['tsp-exact-initial'])

    agent_count = []
    goals_per_agent = []
    tsp_branch_bound_cbs = []
    tsp_branch_bound_initial = []
    tsp_exact_cbs = []
    tsp_exact_initial = []
    tsp_nn_cbs = []
    tsp_nn_initial = []

    for num1 in range(2, 20):
        unique = list(set(dataset[dataset['agent_count'] == num1]['goals_per_agent']))
        for num2 in unique:
            data = dataset[dataset['agent_count'] == num1]
            data = data[data['goals_per_agent'] == num2]
            agent_count.append(num1)
            goals_per_agent.append(num2)
            tsp_branch_bound_cbs.append(find_mean(list(data['tsp-branch-and-bound-cbs'])))
            tsp_branch_bound_initial.append(find_mean(list(data['tsp-branch-and-bound-initial'])))
            tsp_exact_cbs.append(find_mean(list(data['tsp-exact-cbs'])))
            tsp_exact_initial.append(find_mean(list(data['tsp-exact-initial'])))
            tsp_nn_cbs.append(find_mean(list(data['tsp-nn-cbs'])))
            tsp_nn_initial.append(find_mean(list(data['tsp-nn-initial'])))

    result = pd.DataFrame()
    result['agent_count'] = agent_count
    result['goals_per_agent'] = goals_per_agent
    result['tsp-branch-and-bound-cbs'] = tsp_branch_bound_cbs
    result['tsp-branch-and-bound-initial'] = tsp_branch_bound_initial
    result['tsp-exact-cbs'] = tsp_exact_cbs
    result['tsp-exact-initial'] = tsp_exact_initial
    result['tsp-nn-cbs'] = tsp_nn_cbs
    result['tsp-nn-initial'] = tsp_nn_initial
    return result


def plot_results(data: pd.DataFrame, flag: bool, title: str) -> None:
    tsp_exact = data[["agent_count", "goals_per_agent", "tsp-exact-cbs"]]
    tsp_bnb = data[["agent_count", "goals_per_agent", "tsp-branch-and-bound-cbs"]]
    tsp_nn = data[["agent_count", "goals_per_agent", "tsp-nn-cbs"]]

    goals = [2, 5, 10, 15]
    tsp_exact_x = list()
    tsp_bnb_x = list()
    tsp_nn_x = list()

    for x in goals:
        tsp_exact_x.append(tsp_exact[tsp_exact["goals_per_agent"] == x])
        tsp_bnb_x.append(tsp_bnb[tsp_exact["goals_per_agent"] == x])
        tsp_nn_x.append(tsp_nn[tsp_exact["goals_per_agent"] == x])

    if flag:
        fig, (ax1, ax2, ax3, ax4) = plt.subplots(1, 4)
        fig.suptitle(title)
        e = ax1.plot(tsp_exact_x[0]["agent_count"], tsp_exact_x[0]["tsp-exact-cbs"], color="#00cc99")
        b = ax1.plot(tsp_bnb_x[0]["agent_count"], tsp_bnb_x[0]["tsp-branch-and-bound-cbs"], color="#3399ff")
        n = ax1.plot(tsp_nn_x[0]["agent_count"], tsp_nn_x[0]["tsp-nn-cbs"], color="#ff6666")
        ax1.set_ylabel("Solution Cost  --------->")
        ax1.set_title(f"Goal count = {goals[0]}")

        ax2.plot(tsp_exact_x[1]["agent_count"], tsp_exact_x[1]["tsp-exact-cbs"], color="#00cc99")
        ax2.plot(tsp_bnb_x[1]["agent_count"], tsp_bnb_x[1]["tsp-branch-and-bound-cbs"], color="#3399ff")
        ax2.plot(tsp_nn_x[1]["agent_count"], tsp_nn_x[1]["tsp-nn-cbs"], color="#ff6666")
        ax2.set_title(f"Goal count = {goals[1]}")
        ax2.set_xlabel("Agent Count --------->")

        ax3.plot(tsp_exact_x[2]["agent_count"], tsp_exact_x[2]["tsp-exact-cbs"], color="#00cc99")
        ax3.plot(tsp_bnb_x[2]["agent_count"], tsp_bnb_x[2]["tsp-branch-and-bound-cbs"], color="#3399ff")
        ax3.plot(tsp_nn_x[2]["agent_count"], tsp_nn_x[2]["tsp-nn-cbs"], color="#ff6666")
        ax3.set_title(f"Goal count = {goals[2]}")

        ax4.plot(tsp_exact_x[3]["agent_count"], tsp_exact_x[3]["tsp-exact-cbs"], color="#00cc99")
        ax4.plot(tsp_bnb_x[3]["agent_count"], tsp_bnb_x[3]["tsp-branch-and-bound-cbs"], color="#3399ff")
        ax4.plot(tsp_nn_x[3]["agent_count"], tsp_nn_x[3]["tsp-nn-cbs"], color="#ff6666")
        ax4.set_title(f"Goal count = {goals[3]}")
        fig.legend([e, b, n], labels=["TSP Exact", "TSP Branch and Bound", "TSP Nearest Neighbour"], loc="upper left")
        plt.show()
    else:
        fig, (ax1, ax2, ax3) = plt.subplots(1, 3)
        fig.suptitle(title)
        e = ax1.plot(tsp_exact_x[0]["agent_count"], tsp_exact_x[0]["tsp-exact-cbs"], color="#00cc99")
        b = ax1.plot(tsp_bnb_x[0]["agent_count"], tsp_bnb_x[0]["tsp-branch-and-bound-cbs"], color="#3399ff")
        n = ax1.plot(tsp_nn_x[0]["agent_count"], tsp_nn_x[0]["tsp-nn-cbs"], color="#ff6666")
        ax1.set_ylabel("Solution Cost  --------->")
        ax1.set_title(f"Goal count = {goals[0]}")

        ax2.plot(tsp_exact_x[1]["agent_count"], tsp_exact_x[1]["tsp-exact-cbs"], color="#00cc99")
        ax2.plot(tsp_bnb_x[1]["agent_count"], tsp_bnb_x[1]["tsp-branch-and-bound-cbs"], color="#3399ff")
        ax2.plot(tsp_nn_x[1]["agent_count"], tsp_nn_x[1]["tsp-nn-cbs"], color="#ff6666")
        ax2.set_title(f"Goal count = {goals[1]}")
        ax2.set_xlabel("Agent Count --------->")

        ax3.plot(tsp_exact_x[2]["agent_count"], tsp_exact_x[2]["tsp-exact-cbs"], color="#00cc99")
        ax3.plot(tsp_bnb_x[2]["agent_count"], tsp_bnb_x[2]["tsp-branch-and-bound-cbs"], color="#3399ff")
        ax3.plot(tsp_nn_x[2]["agent_count"], tsp_nn_x[2]["tsp-nn-cbs"], color="#ff6666")
        ax3.set_title(f"Goal count = {goals[3]}")
        fig.legend([e, b, n], labels=["TSP Exact", "TSP Branch and Bound", "TSP Nearest Neighbour"], loc="upper left")
        plt.show()



if __name__ == "__main__":
    result_location = ["/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/results32x32.json", "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/results64x64.json", "/Users/hebbaquraishi/Desktop/MAPF/Automation Scripts/results/results161x63.json"]
    dataset = create_dataset(location=result_location[0])
    results = preprocess_dataset(dataset=dataset)
    plot_results(data=results, flag=True, title="32 x 32 map")

    dataset = create_dataset(location=result_location[1])
    results = preprocess_dataset(dataset=dataset)
    plot_results(data=results, flag=False, title="64 x 64 map")

    dataset = create_dataset(location=result_location[2])
    results = preprocess_dataset(dataset=dataset)
    plot_results(data=results, flag=False, title="161 x 63 map")