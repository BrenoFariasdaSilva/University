class Graph:
    def __init__(self, N):
        self.N = N
        self.inDegree = [0]*N
        self.outDegree = [0]*N
        self.degree = [0]*N
    def addEdge(self, u, v, w=1):
        self.inDegree[v] += w
        self.outDegree[u] += w
        self.degree[u] += w
        self.degree[v] += w
    def getInDegree(self, V):
        return self.inDegree[V]
    def getOutDegree(self, V):
        return self.outDegree[V]
    def getDegree(self, V):
        return self.degree[V]