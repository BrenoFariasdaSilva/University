# BFS Algorithm
# You are on your way to your first job interview as a program tester, and you are already late.
# The interview is in a skyscraper and you are currently in floor S, where you see an elevator.
# Upon entering the elevator, you learn that it has only two buttons, marked “UP u” and “DOWN d”.
# You conclude that the UP-button takes the elevator U floors up (if there aren’t enough floors, pressing the UP-botton does nothing, or at least so you assume),
# whereas the DOWN-button takes you D stories down (or none if there aren’t enough).
# Knowing that the interview is at floor G, and that there are only F floors in the building,
# you quickly decide to write a program that gives you the amount of button pushes you need to perform.
# If you simply cannot reach the correct floor, your program halts with the message “use the stairs”.

# Given input F, S, G, U and D (floors, start, goal, up, down),
# find the shortest sequence of button presses you must press in order to get from S to G, given a building of F floors,
# or output “use the stairs” if you cannot get from S to G by the given elevator.

# Input:
# The input will consist of one line, namely F S G U D, where 1 ≤ S, G ≤ F ≤ 1000000 and 0 ≤ U, D ≤ 1000000. The floors are one-indexed, i.e. if there are 10 stories, S and G be in [1, 10].

# Output
# You must reply with the minimum numbers of pushes you must make in order to get from S to G, or output "use the stairs" if it is impossible given the configuration of the elevator.

import sys
import time
import math
import random

# define macro
IMPOSSIBLE = -1

class Graph:
	def __init__(self):
		self.nodes = []

	def add_node(self, node):
		self.nodes.append(node)

	def bfs(self, start, goal):
		# initialize queue
		minimumNumberOfPushes = IMPOSSIBLE

		# initialize queue
		queue = []			
		queue.append(start)

		# mark start node as visited
		start.visited = True

		# loop until queue is empty
		while queue:
			# pop a vertex from queue
			currentNode = queue.pop(0)

			# get adjacent vertices of the popped vertex
			# if a adjacent has not been visited, then mark it visited and enqueue it
			for adjacentNode in currentNode.adjacent:
				if not adjacentNode.visited:
					adjacentNode.visited = True
					adjacentNode.parent = currentNode
					adjacentNode.distance = currentNode.distance + 1
					queue.append(adjacentNode)

					# check if adjacent node is goal node
					if adjacentNode.name == goal:
						return adjacentNode.distance

		return minimumNumberOfPushes

class Node:
	def __init__(self, name):
		self.name = name
		self.visited = False
		self.distance = 0
		self.adjacent = []

	def __str__(self):
		return self.name

def validateInputs(floors, start, goal, up, down):
	# if 1 ≤ s, g ≤ f ≤ 1000000
	if (start < 1 or start > floors or goal < 1 or goal > floors):
		return False

	# if 0 ≤ u, d ≤ 1000000
	if (up < 0 or up > 1000000 or down < 0 or down > 1000000):
		return False

	return True

def showAdjacencyList(graph):
	# print adjacency list representation of the above graph
	print("Adjacency List Representation:")
	for i in range(len(graph.nodes)):
		print(graph.nodes[i].name, end = " ")
		for adjacentNode in graph.nodes[i].adjacent:
			print("->", adjacentNode.name, end = " ")
		print()
	print()

def main():
		# get number of  floors, start, goal, up, down
		floors, start, goal, up, down = map(int, input().split())

		# validate inputs
		if validateInputs(floors, start, goal, up, down) == False:
			return

		if (start == goal):
			print(0)
			return

		# create graph
		graph = Graph()

		# create nodes
		for i in range(floors):
			graph.add_node(Node(i))

		# create edges
		for i in range(floors):
			# create edge from current node to node up
			if i + up < floors:
				graph.nodes[i].adjacent.append(graph.nodes[i + up])

			# create edge from current node to node down
			if i - down >= 0:
				graph.nodes[i].adjacent.append(graph.nodes[i - down])

		# print adjacency list representation of the above graph
		# showAdjacencyList(graph)	

		# run bfs
		minimumNumberOfPushes = graph.bfs(graph.nodes[start - 1], goal - 1)
		
		if minimumNumberOfPushes == IMPOSSIBLE:
			print("use the stairs")
		else:
			print(minimumNumberOfPushes)

if __name__ == "__main__":
	main()