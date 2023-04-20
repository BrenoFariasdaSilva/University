# Before Santa Claus begin his travels in Brazil to deliver Christmas presents, he asked you to help him drawing a map with all the cities that he should visit.
# Follows the rule to draw this map: the sum of all routes (distances between two cities)
# existing on the map should be as small as possible and must be possible to arrive in any destination from any origin.
# Claus does not mind to go to a particular city more than once, as long as it uses only the routes drawn on the map.

# Input:
# The input file contains several test cases.
# Each test case starts with two numbers M (2 ≤ M < 40000) and N (1 ≤ N < 50000), the number of cities and the number of roads respectively.
# Input is terminated by M = N = 0. Then follow N integer triples X (0 ≤ X), Y (Y < M) and Z (1 ≤ Z ≤ 999),
# pecifying that there will be a bidirectional route between X and Y with Z kilometers,
# considering that X ≠ Y and the total sum of all routes in each map is less than 231.

# Output:
# For each test case, print a single integer indicating the sum of all distances or routes of your map.

# Example:
# Input:
# 6 8
# 0 1 350
# 1 2 180
# 0 3 270
# 3 4 200
# 4 5 300
# 1 4 190
# 3 5 500
# 2 5 400 
# 7 11
# 0 1 7
# 0 3 5
# 1 2 8
# 1 3 9
# 1 4 7
# 2 4 5
# 3 4 15
# 3 5 6
# 4 5 8
# 4 6 9
# 5 6 11
# 0 0

# Expected Output:
# 1140
# 39

def main():
	while True:
		M, N = map(int, input().split())
		if M == N == 0:
			break
		graph = [[] for _ in range(M)]
		for _ in range(N):
			X, Y, Z = map(int, input().split())
			graph[X].append((Y, Z))
			graph[Y].append((X, Z))
		print(prim(graph))

def prim(graph):
	visited = [False] * len(graph)
	visited[0] = True
	edges = []
	for edge in graph[0]:
		edges.append(edge)
	edges.sort(key = lambda x: x[1])
	total = 0
	while edges:
		Y, Z = edges.pop(0)
		if not visited[Y]:
			visited[Y] = True
			total += Z
			for edge in graph[Y]:
					if not visited[edge[0]]:
						edges.append(edge)
			edges.sort(key = lambda x: x[1])
	return total

if __name__ == "__main__":
	main()