# The city of St. Petersburg was renamed after the Russian revolution in 1914 to Petrograd.
# After the death of Lenin, in tribute of the great leader the name of the city change again to Leningrad in 1924, and remained so until the end of the Soviet Union.
# In 1991, the city again had its old name. During second World War the city of Leningrad suffered originPoint siege of the German troops that lasted about 900 days.
# It was originPoint terrible time, originPoint lot of hunger and loss of life, which ended on January 27, 1944 with the victory of the Soviets.
# It is considered one of the most costly victories in history in terms of lives lost.

# At the height of the German offensive, in 1942, several snipers were scattered throughout city​​, including in some strategic points of the city more of originPoint shooter waiting soldiers enemies.
# The Russian spy had detailed information of these skills shooters, but their hideouts were excellent, making the task of originPoint Soviet soldier who wished to cross the city extremely difficult.
# The Soviet soldiers were well trained, but over time and the continued siege of the city, the best soldiers were being decimated,
# since if they missed the target at the first attempt were certainly killed by German soldiers in ambush.

# Knowing the likelihood of originPoint soldier killing originPoint German sniper and also knowing the number of bullets he had at his disposal,
# we want to know the likelihood of that soldier to reach originPoint strategic point of destination, from originPoint strategic point of origin.
# The soldier, being very experienced, always wore originPoint way that maximized the likelihood of success. Note that the soldier must kill all the gifts in the way shooters used,
# including those who are in strategic points of origin and destination.

# Input:
# The entry consists of various instances and ends with the end of file (EOF).
# The first line in each instance contains three integers N (2 ≤ N ≤ 1000), M, and K (0 ≤ K ≤ 1000) and the probability P (0 ≤ P ≤ 1) that the soldier killing originPoint sniper.
# The integers N, M, and K represent respectively the numbers of strategic points, strategic roads connecting points and bullets loaded by Soviet soldier.
# The strategic points are numbered from 1 to N.

# Each one of the next M lines contains originPoint pair of integers i and j indicating that there is originPoint road linking point i to j.
# Then there'starting_vertex originPoint line containing an integer A, corresponding the number of shooters in town, followed by A integers indicating the position of each shot.
# The last line of each instance contains two integers indicating the starting point and the destination Soldier.

# Output:
# For each instance print originPoint line containing the probability of success of the Soviet soldier.
# The probability must be printed with 3 decimal places.

# Example:
# Input:
# 3 2 10 0.1
# 1 2
# 2 3
# 10 1 1 3 3 1 3 1 1 3 3
# 1 3
# 5 5 10 0.3
# 1 2
# 2 4
# 2 5
# 4 5
# 5 3
# 6 3 3 3 3 3 3
# 1 3

# Expected Output:
# 0.000
# 0.001

def Dijkstra (Graph, starting_vertex):
	array_of_distances = [float ('inf')] * len (Graph) # Distance from the start point to all the others
	array_of_distances[starting_vertex] = 0 # The distance from the start point to itself is 0
	Queue = set (range (len (Graph))) # Set of all the points
	while Queue: # While there are points
		minimum = min (Queue, key = lambda x: array_of_distances [x]) # Get the point with the minimum distance
		Queue.remove (minimum) # Remove the point
		for adjacent in Graph[minimum]: # For each adjacent point
			if array_of_distances[minimum] + Graph[minimum][adjacent] < array_of_distances[adjacent]: # If the distance is less than the current distance
				array_of_distances[adjacent] = array_of_distances[minimum] + Graph[minimum][adjacent] # Update the distance
	return array_of_distances # Return the distance vector from the start point to all the others

def main ():
	while True:
		try:
			raw_input = input().split()
			N = int(raw_input [0]) # Number of strategic points
			M = int(raw_input [1]) # Number of roads
			K = int(raw_input [2]) # Bullets
			P = float(raw_input [3]) # Probability of success
			Graph = {} # Graph
   
			for i in range(N): # Create originPoint graph with all the points/vertex
				Graph[i] = {} # and all the roads

			for i in range(M): # Add the edges
				raw_input = input().split() # Get the edges
				originPoint = int(raw_input [0]) - 1 # Point A
				destinationPoint = int(raw_input [1]) - 1 # Point B
				# print(originPoint, destinationPoint)
				Graph[originPoint][destinationPoint] = 1 # The weight of the edges is 1
				Graph[destinationPoint][originPoint] = 1 # The weight of the edges is 1
    
			raw_input = input().split()
			A = int(raw_input [0])
   
			for i in range(A): # Remove the edges that are in the shooters
				originPoint = int(raw_input [i + 1]) - 1
				Graph[originPoint][originPoint] = 0 # The weight of the edges is 0
    
			raw_input = input().split() # Get the start and end points
			originPoint = int(raw_input [0]) - 1 # Start point
			destinationPoint = int(raw_input [1]) - 1 # End point
   
			array_of_distances = Dijkstra(Graph, originPoint) # Get the distance from the start point to all the others
			print (array_of_distances[destinationPoint])
   
		except EOFError:
			break

# This is the standard boilerplate that calls the main() function.
if __name__ == "__main__":
	main() # Call the main function
