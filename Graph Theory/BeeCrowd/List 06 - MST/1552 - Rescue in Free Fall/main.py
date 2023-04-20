# Oh, my God!
# A group of people is falling in free fall! They all jumped at the very same time from several airplanes which were at the very same height.
# They were intending to perform the greatest and most beautiful synchronised jump in History.
# However, evil Loki, in order to delight himself in human insignificance, had sabotaged the parachutes, and now the only hope lies in a joint action between Iron Man and Spider-Man.
# As they both are very nerds, they've noticed that the people were falling all in a same plane parallel to the ground, despite of air resistance and other factors.
# Then, they've made up an infalible plan.
# First, the arachnid shall join all the people through web wires between them.
# Once there is no person not connected to the group, the playboy will be able to eletromagnetise the whole group and, holding the hand of just one person, land them all safely.
# But there is no much time left for divagations. Spider-Man needs to be quick, what in his case means spending web as least as possible.
# Thereunto, Iron Man has projected the plane where the people are in a cartesian mesh in his screen, using the centimetre as unity of length, and has obtained the coordinates of each person in the mesh.
# Now, J.A.R.V.I.S. is computing the minimum of web Spider-Man will need.
# Depending on the answer, Iron Man won't wait for the boy and will improvise some stunt.

# Input:
# The input consists of several test cases.
# The first line of input contains an integer C that determines the number of test cases.
# Each test case starts with a sigle positive integer n (n ≤ 500), which stands for the number of people in the group.
# Follow then n lines, each of them representing one person of the group by one's coordinates x and y in the mesh (0 ≤ x, y ≤ 104).

# Output:
# For each test case, your program is meant to output a line containing the value with two decimal places of precision relative to the minimum length of web, in metres,
# needed to connect all the people in the group.
# Watch for the decimal mark is . (dot), not , (comma).

## Example:
# Input: 
# 2
# 5
# 0 0
# 0 100
# 100 200
# 200 400
# 300 300
# 4
# 1 5
# 1 4
# 2 3
# 3 2

# Expected Output:
# 6.06
# 0.04

# More Test Cases At:https://www.udebug.com/URI/1552

def prim(graph, start):
	visited = [False] * len(graph) 
	visited[start] = True
	edges = []
	for i in graph[start]:
		edges.append(i) 
	edges.sort()
	cost = 0
	while len(edges) > 0:
		edge = edges.pop(0)
		if not visited[edge[1]]:
			visited[edge[1]] = True
			cost += edge[0]
			for i in graph[edge[1]]:
					edges.append(i)
			edges.sort()
	return cost

def distance(x1, y1, x2, y2):
	return ((x1 - x2) ** 2 + (y1 - y2) ** 2) ** 0.5

def main():
	testCases = int(input()) # C
	for i in range(testCases):
		numberOfPeople = int(input())
		coordinates = [] # Create a list of coordinates of each person holding the x and y values
		for j in range(numberOfPeople):
			coordinates.append(list(map(int, input().split()))) # Add the x and y values to the list
		graph = [[] for i in range(numberOfPeople)] # Create a list of lists to hold the edges of the graph
		for j in range(numberOfPeople):
			for k in range(j + 1, numberOfPeople):
				graph[j].append([distance(coordinates[j][0], coordinates[j][1], coordinates[k][0], coordinates[k][1]), k]) # Add the edges to the graph
				graph[k].append([distance(coordinates[j][0], coordinates[j][1], coordinates[k][0], coordinates[k][1]), j]) # Add the edges to the graph
		minimumMeters = prim(graph, 0) / 100
		print("{:.2f}".format(minimumMeters))

if __name__ == "__main__":
	main()