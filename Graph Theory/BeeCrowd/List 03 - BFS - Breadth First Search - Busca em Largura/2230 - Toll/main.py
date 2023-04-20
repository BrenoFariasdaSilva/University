# BFS Algorithm

# The prize for first place in the Brazilian Olympiad of Informatics, Juquinha and his family have won a one week trip to South Korea.
# As the country is stunning, with traditions, culture, very different architecture and cuisine of Brazil, the father of Juquinha Mr. Juca, decided to rent a car to explore the country.
# The roads are well maintained;
# all are two-way, and two cities can be directly connected by more than one road.
# However, on all roads you pay a fixed amount of toll (there is a toll each way between two cities).
# As Mr. Juca does not have much money to spend, travel with the car should be very thoughtful.

# Write a program that known cities and existing roads in the country and the city where Juquinha and your family are,
# find each city (not the city where they are) that can be visited by them,
# given the restriction that Mr . Juca want to pay at most P tolls (considering only the outward journey).

# Input
# C = number of cities, E = number of roads, S = city where Juquinha and his family are, P = maximum number of tolls.
# The input consists of several test sets.
# The first line of a test set contains four integers C (0 ≤ C ≤ 50), E (0 ≤ E ≤ 2500), L (0 ≤ L ≤ C) e P (0 ≤ P ≤ C).
# The values C = numberOfCities e E = numberOfRoads .
# Cities are identified by integers from 1 to C.
# The values L = currentCity e P = tollLimit.
# At E following lines each one contains information of a road represented by a pair of positive integers X e Y (1 ≤ X,Y ≤ C),
# indicating that there is a road (two-way) of the city X to the city Y.
# The end of the input is indicated by C = E = L = P = 0.

# Output
# For each entry test set your program should produce three lines in the output.
# The first line should contain a test set identifier in the format "Teste n", where n is numbered from 1.
# In the second line should appear the identifiers of the cities that can be reached, in ascending order, separated by at least a blank.
# The third line should be left blank. The spelling shown in Example output below should be followed strictly.

# Example
# Input:
# 5 4 2 1
# 1 2
# 2 3
# 3 4
# 4 5
# 9 12 1 2
# 2 1
# 1 5
# 2 1
# 3 2
# 9 3
# 3 4
# 4 8
# 4 7
# 7 6
# 5 6
# 4 5
# 3 7
# 0 0 0 0

# Expected output:
# Teste 1
# 1 3

# Teste 2
# 2 3 4 5 6

import sys
import time
import math
import random

# define macros
# LOOP macro
STOPCODE = "0 0 0 0"

class Node:
    def __init__(self, number):
        self.number = number
        self.visited = False
        self.distance = 0
        self.roads = []

    def addEdge(self, node):
        self.roads.append(node)

class Graph:
    def __init__(self):
        self.nodes = []

    def add_node(self, node):
        self.nodes.append(node)

    def add_edge_two_way(self, source, destination):
        source.addEdge(destination)
        destination.addEdge(source)

    def bfs(self, source, tollLimit):
        reachableCities = []

        # set all nodes to unvisited
        for node in self.nodes:
            node.visited = False
            node.distance = 0

        # set source node to visited
        source.visited = True

        # create queue
        queue = []

        # enqueue source node
        queue.append(source)

        # while queue is not empty
        while queue:
            # dequeue node
            currentNode = queue.pop(0)

            # for each edge of currentNode
            for edge in currentNode.roads:
                # if edge is not visited
                if edge.visited == False:
                    edge.visited = True
                    edge.distance = currentNode.distance + 1

                    # enqueue edge
                    queue.append(edge)

                    # if distance is less than toll limit
                    if edge.distance <= tollLimit:
                        # add edge to reachable cities
                        reachableCities.append(edge.number)

        return reachableCities

    def showRoads(self):
        for node in self.nodes:
            print(f'Node: {node.number} -> ', end='')
            for edge in node.roads:
                print(f'{edge.number}', end=' ')
            print()
        print()


def showReachableCities(test, reachableCities):
    print(f'Teste {test}')
    reachableCities.sort()
    for city in reachableCities:
        print(f'{city}', end=' ')
    print()
    print()


def validateInput(numberOfCities, numberOfRoads, currentCity, tollLimit):
    # numberOfCities (0 ≤ numberOfCities ≤ 50)
    # numberOfRoads (0 ≤ numberOfRoads ≤ 2500)
    # currentCity (0 ≤ currentCity ≤ numberOfCities)
    # tollLimit (0 ≤ tollLimit ≤ numberOfCities).
    if numberOfCities < 0 or numberOfCities > 50:
        return False

    if numberOfRoads < 0 or numberOfRoads > 2500:
        return False

    if currentCity < 0 or currentCity > numberOfCities:
        return False

    if tollLimit < 0 or tollLimit > numberOfCities:
        return False

    return True


def main():
    # while user input is not 0 0, keep looping
    loop = 1
    while True:
        userInput = input()
        if userInput == STOPCODE:
            break

        # split user input into list
        userInput = userInput.split()

        # get number of cities
        numberOfCities, numberOfRoads, currentCity, tollLimit = int(
            userInput[0]), int(userInput[1]), int(userInput[2]), int(userInput[3])

        # validate input
        if not validateInput(numberOfCities, numberOfRoads, currentCity, tollLimit):
            break

        # create graph
        graph = Graph()

        # create nodes
        for city in range(numberOfCities):
            graph.add_node(Node(int(city+1)))

        # add roads
        for roads in range(numberOfRoads):
            userInput = input().split()
            source, destination = int(userInput[0]), int(userInput[1])
            graph.add_edge_two_way(
                graph.nodes[source-1], graph.nodes[destination-1])

        # show Roads
        # graph.showRoads()

        # run bfs
        reachableCities = graph.bfs(graph.nodes[currentCity-1], tollLimit)

        # show reachable cities
        showReachableCities(loop, reachableCities)

        loop += 1


if __name__ == "__main__":
    main()
