# A transport company often needs to deliver goods from one city to another city.
# The transport company has made a special deal with a hotel chain which allows its drivers to stay in the hotels of this chain for free.
# Drivers are only allowed to drive up to 10 hours a day.
# The transport company wants to find a route from the starting city to the destination city such that a driver can always spend the night in one of the hotels of the hotel chain,
# and that he needs to drive at most 10 hours from one hotel to the next hotel (or the destination).
# Of course, the number of days needed to deliver the goods should also be minimized.

# Input:
# The input file contains several test cases.
# Each test case starts with a line containing an integer n, (2 ≤ n ≤ 10000), the number of cities to be considered when planning the route.
# For simplicity, cities are numbered from 1 to n, where 1 is the starting city, and n is the destination city.
# The next line contains an integer h followed by the numbers c1, c2, ..., ch indicating the numbers of the cities where hotels of the hotel chain are located.
# You may assume that 0 ≤ h ≤ min(n, 100). The third line of each test case contains an integer m (1 ≤ m ≤ 105), the number of roads to be considered for planning the route.
# The following m lines describe the roads.
# Each road is described by a line containing 3 integers a, b, t (1 ≤ a, b ≤ n and 1 ≤ t ≤ 600), where a, b
# are the two cities connected by the road, and t is the time in minutes needed by the driver to drive from one end of the road to the other.
# Input is terminated by n = 0.

# Output:
# For each test case, print one line containing the minimum number of hotels the transport company has to book for a delivery from city 1 to city n.
# If it is impossible to find a route such that the driver has to drive at most 10 hours per day, print -1 instead.

# Sample Input:
# 6
# 3 2 5 3
# 8
# 1 2 400
# 3 2 80
# 3 4 301
# 4 5 290
# 5 6 139
# 1 3 375
# 2 5 462
# 4 6 300
# 3
# 0
# 2
# 1 2 371
# 2 3 230
# 0

# Expected Output:
# 2
# -1

def main():
	while True:
		n = int(input())
		if n == 0:
			break
		raw_input = input().split()
		h = int(raw_input[0])
		hotels = [int(raw_input[i]) for i in range(1, h + 1)]
		m = int(input())
		roads = []
		for i in range(m):
			roads.append([int(x) for x in input().split()])
		print(solve(n, h, hotels, m, roads))

def solve(n, h, hotels, m, roads):
	# Create a graph
	graph = {}
	for i in range(n):
		graph[i + 1] = []
	for road in roads:
		graph[road[0]].append([road[1], road[2]])
		graph[road[1]].append([road[0], road[2]])

	# Find the shortest path from 1 to n
	visited = [False] * (n + 1)
	distance = [float('inf')] * (n + 1)
	distance[1] = 0
	queue = [1]
	while queue:
		node = queue.pop(0)
		visited[node] = True
		for neighbor in graph[node]:
			if not visited[neighbor[0]]:
				distance[neighbor[0]] = min(distance[neighbor[0]], distance[node] + neighbor[1])
				queue.append(neighbor[0])

	# Find the number of hotels needed
	if distance[n] == float('inf'):
		return -1
	else:
		hotels.append(n)
		hotels.sort()
		hotelDistance = [0] * len(hotels)
		for i in range(len(hotels) - 1):
			hotelDistance[i] = distance[hotels[i + 1]] - distance[hotels[i]]
		hotelDistance[-1] = distance[n] - distance[hotels[-1]]
		hotelsNeeded = 0
		for i in range(len(hotels)):
			if hotelDistance[i] > 600:
				return -1
			if hotelDistance[i] > 300:
				hotelsNeeded += 1
		return hotelsNeeded

if __name__ == '__main__':
	main()