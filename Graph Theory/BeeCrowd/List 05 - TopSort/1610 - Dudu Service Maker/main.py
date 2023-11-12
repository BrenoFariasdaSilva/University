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
# 3
# 2 1
# 1 2
# 2 2 
# 1 2
# 2 1
# 4 4
# 2 3
# 3 4
# 4 2
# 1 3

# Expected Output:
# NAO
# SIM
# SIM

def hasCycle(graph):
	visited = [False] * len(graph)
	recStack = [False] * len(graph)
	for i in range(len(graph)):
		if not visited[i]:
			if dfs(graph, i, visited, recStack):
				return True
	return False

def dfs(graph, node, visited, recStack):
	visited[node] = True
	recStack[node] = True
	for i in graph[node]:
		if not visited[i]:
			if dfs(graph, i, visited, recStack):
				return True
		elif recStack[i]:
			return True
	recStack[node] = False
	return False

def main():
	testCases = int(input())
	for i in range(testCases):
		numberOfDocuments, numberOfDependencies = map(int, input().split())
		graph = [[] for i in range(numberOfDocuments)]
		for j in range(numberOfDependencies):
			documentA, documentB = map(int, input().split())
			graph[documentA - 1].append(documentB - 1)
		if hasCycle(graph):
			print("SIM")
		else:
			print("NAO")

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function

