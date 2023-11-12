# BFS Algorithm

# In a certain city there are N intersections connected by one-way and two-way streets. It is a modern city, and several of the streets have tunnels or overpasses. Evidently it must be possible to travel between any two intersections. More precisely given two intersections V and W it must be possible to travel from V to W and from W to V.

# Your task is to write a program that reads a description of the city street system and determines whether the requirement of connectedness is satisfied or not.
# Input

# The input contains several test cases. The first line of a test case contains two integers N and M, separated by a space, indicating the number of intersections (2 ≤ N ≤ 2000) and number of streets (2 ≤ M ≤ N(N−1)/2). The next M lines describe the city street system, with each line describing one street. A street description consists of three integers V, W and P, separated by a blank space, where V and W are distinct identifiers for intersections (1 ≤ V, W ≤ N , V ≠ W ) and P can be 1 or 2; if P = 1 the street is one-way, and traffic goes from V to W; if P = 2 then the street is two-way and links V and W. A pair of intersections is connected by at most one street.

# The last test case is followed by a line that contains only two zero numbers separated by a blank space.
# Output

# For each test case your program should print a single line containing an integer G, where G is equal to one if the condition of connectedness is satisfied, and G is zero otherwise.

# Sample Input: 
# 4 5
# 1 2 1
# 1 3 2
# 2 4 1
# 3 4 1
# 4 1 2
# 0 0

# Sample Output:
# 1

import sys
import time
import math
import random

# define macros
# LOOP macro
STOPCODE = "0 0"

# DIRECTION macros
UNIDIRECTIONAL = 1
BIDIRECTIONAL = 2

# CONNECTEDNESS macros
CONNECTED = 1
NOT_CONNECTED = 0

class Graph:
	def __init__(self):
		self.nodes = []

	def add_node(self, node):
		self.nodes.append(node)

	def add_edge_one_way(self, source, destination):
		# add edge from source to destination
		routeNode = Node(destination.name)
		source.adjacent.append(routeNode)

	def bfs(self, start):
		# initialize all nodes as not visited
		self.reset_node_visited()

		# initialize nodesToVisit
		nodesToVisit = []
		# start node is gray
		start.visited = True
		nodesToVisit.append(start)

		while nodesToVisit:
			# dequeue
			node = nodesToVisit.pop(0)
			index = self.get_node_index(node.name)
			currentNode = self.nodes[index]
			# visit all adjacent nodes
			for i in range(len(currentNode.adjacent)):
				if currentNode.adjacent[i].visited == False:
					currentNode.adjacent[i].visited = True
					index = self.get_node_index(currentNode.adjacent[i].name)
					self.nodes[index].visited = True
					nodesToVisit.append(currentNode.adjacent[i])

		connectdness = self.is_connected()

		# free memory
		del nodesToVisit
		del currentNode
		del node

		return connectdness

	def print_edges(self):
		for i in range(len(self.nodes)):
			print(f'Node {i} has {len(self.nodes[i].adjacent)} adjacent nodes: ', end='')
			for j in range(len(self.nodes[i].adjacent)):
				print(f'{self.nodes[i].adjacent[j].name} ', end='')
			print()
  
	def reset_node_visited(self):
		for i in range(len(self.nodes)):
			self.nodes[i].visited = False
			for j in range(len(self.nodes[i].adjacent)):
				self.nodes[i].adjacent[j].visited = False

	def is_connected(self):
		i = 0
		for i in range(len(self.nodes)):
			if self.nodes[i].visited == False:
				return NOT_CONNECTED
				break
		if i == len(self.nodes):
			return CONNECTED

	def get_node_index(self, name):
		for i in range(len(self.nodes)):
			if self.nodes[i].name == name:
				return i
		return -1
		
class Node:
	def __init__(self, name):
		self.name = name
		self.visited = False
		self.adjacent = []

	def __str__(self):
		return self.name

def main():
	# while user input is not 0 0, keep looping
	while True:
		userInput = input()
		if userInput == STOPCODE:
			break
			
		# print(f'userInput: {userInput}')

		# get number of nodes and edges
		numberOfVertex, numberOfEdges = map(int, userInput.split(" "))

		if ((numberOfVertex <= 2 or numberOfVertex >= 2000) or  (numberOfEdges <= 2 or numberOfEdges >= (numberOfVertex * (numberOfVertex - 1) / 2))):
			# print("Invalid input")
			[input() for i in range(numberOfEdges)]
			continue

		# create graph
		graph = Graph()

		# create nodes
		for i in range (numberOfVertex):
			graph.add_node(Node(str(i)))
		
		# create edges
		for i in range(numberOfEdges):
			# get source and destination
			source, destination, direction = map(int, input().split(' '))

			if ((direction != UNIDIRECTIONAL and direction != BIDIRECTIONAL)):
				print("Invalid input 1")
				[input() for curEdge in range(numberOfEdges - (i + 1))]
				break
			if ((source < 1 and source > numberOfVertex)):
				print("Invalid input 2")
				[input() for curEdge in range(numberOfEdges - (i + 1))]
				break
			if ((destination < 1 and destination > numberOfVertex)):
				print("Invalid input 3")
				[input() for curEdge in range(numberOfEdges - (i + 1))]
				break

			# add edges
			if (source == 0 or destination == 0):
				# print('Invalid source or destination')
				return
			
			graph.add_edge_one_way(graph.nodes[source - 1], graph.nodes[destination - 1])
			if direction == BIDIRECTIONAL:
				graph.add_edge_one_way(graph.nodes[destination - 1], graph.nodes[source - 1])

		isConnected = CONNECTED
		# run bfs
		for i in range(numberOfVertex):
			if (graph.bfs(graph.nodes[i]) == NOT_CONNECTED):
				isConnected = NOT_CONNECTED
				break
			
		if isConnected == CONNECTED:
			print(f'{CONNECTED}')
		else:
			print(f'{NOT_CONNECTED}')

		# free memory
		del graph

	del userInput
	

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function
