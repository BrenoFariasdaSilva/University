class Node:
	def __init__(self, number):
		self.number = number
		self.visited = False
		self.edges = []

	def addEdge(self, node):
		self.edges.append(node)

class Graph:
	def __init__(self, N):
		self.N = N
		self.nodes = [Node(i) for i in range(N)]

	def addEdge(self, u, v):
		self.nodes[u].addEdge(self.nodes[v])

	def DFS(self, start):
		self.DFSVisit(self.nodes[start])

	def DFSVisit(self, node):
		node.visited = True
		print(node.number, end=' ')
		for edge in node.edges:
			if not edge.visited:
				self.DFSVisit(edge)
    
def main():
	g = Graph(4) 
	g.addEdge(0, 1) 
	g.addEdge(0, 2) 
	g.addEdge(1, 2) 
	g.addEdge(2, 0) 
	g.addEdge(2, 3) 
	g.addEdge(3, 3) 
	g.DFS(2) 
	# 2 0 1 3

if __name__ == '__main__':
	main()