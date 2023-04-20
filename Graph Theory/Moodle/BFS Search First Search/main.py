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

	def BFS(self, source):
		queue = [self.nodes[source]]
		self.nodes[source].visited = True

		while queue:
			u = queue.pop(0)
			print(u.number, end=' ')
			for v in u.edges:
				if not v.visited:
					queue.append(v)
					v.visited = True
		
				
def main():
	g = Graph(4)
	g.addEdge(0, 1)
	g.addEdge(0, 2)
	g.addEdge(1, 2)
	g.addEdge(2, 0)
	g.addEdge(2, 3)
	g.addEdge(3, 3)
	g.BFS(2)

if __name__ == '__main__':
	main()
	