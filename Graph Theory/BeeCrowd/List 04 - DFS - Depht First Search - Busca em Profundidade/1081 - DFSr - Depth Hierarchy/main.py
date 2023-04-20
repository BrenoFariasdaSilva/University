# Dudu needs a document to finalize a task in his work.
# After searching, he found out that this document needed other documents, which also needed other documents and so on.
# Dudu made a final list with the documents he will need.
# With that in hands, he suspects that the list contains loops.
# For instance, if a document A depends on the document B that also depends on A, it would make the task impossible to finish.
# In this case the loop contains only two documents, but there might be cases with three or more!
# Given the list of the dependencies, help him compute if he can obtain all the documents, it is, to compute if there isn't a loop in the given dependencies.

# Input:
# The first line contains an integer T (T = 100) indicating the number of test cases.
# On the first line in each test case there will be the integers N (2 ≤ N ≤ 100* or 2 ≤ N ≤ 104**) and M (1 ≤ M ≤ 300* or 1 ≤ M ≤ 3*104​**),
# indicating the number of documents and the dependencies.
# In each of the following M lines, there will be two integers A (1 ≤ A) and B (B ≤ N and A != B),
# indicating that the document A depends on the document B. There might be repeated dependencies!
# *For around 90% of the cases;
# **For the other cases.

# Output:
# For each case, print SIM (Portuguese word for YES) if there is at least one loop, and NAO otherwise (Portuguese word for NO).

# Example:
# Input:
# 2
# 12 9
# 0 1
# 1 5
# 5 6
# 0 4
# 4 2
# 2 3
# 7 8
# 1 7
# 10 11
# 11 8
# 0 1
# 1 2
# 3 4
# 4 3
# 5 6
# 6 8
# 7 9
# 9 10

# Expected Output:
# Case 1:
#   0-1 pathR(G,1)
#     1-5 pathR(G,5)
#       5-6 pathR(G,6)
#     1-7 pathR(G,7)
#       7-8 pathR(G,8)
#   0-4 pathR(G,4)
#     4-2 pathR(G,2)
#       2-3 pathR(G,3)

#   10-11 pathR(G,11)

# Case 2:
#   0-1 pathR(G,1)
#     1-2 pathR(G,2)

#   3-4 pathR(G,4)
#     4-3

#   5-6 pathR(G,6)
#     6-8 pathR(G,8)

#   7-9 pathR(G,9)
#     9-10 pathR(G,10)

MAX = 20

# graph class
class Graph:
	def __init__(self, V):
		self.V = V
		# create matrix of MAX x MAX
		self.adj = [[] for i in range(MAX)]

	def addEdge(self, v, w):
		self.adj[v].append(w)

# recursive function to find path
def pathR(G, v):
	# print current node
	print(v, end=" ")

	# mark current node as visited
	visited[v] = True

	# traverse all adjacent nodes
	for i in G.adj[v]:
		# if node is not visited
		if not visited[i]:
			# call pathR recursively
			pathR(G, i)

# function to find path
def path(G, v):
	# mark all nodes as unvisited
	visited = [False] * MAX

	# call pathR recursively
	pathR(G, v)

# main function
if __name__ == '__main__':
	tests = int(input())
	for t in range(tests):
		# input number of nodes and edges
		n, m = map(int, input().split())

		# create graph
		G = Graph(n)

		# input edges
		for i in range(m):
			u, v = map(int, input().split())
			G.addEdge(u, v)

		# print path
		print("Case", t + 1)
		for i in range(n):
			path(G, i)
			print()
			

