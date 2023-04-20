# Crie uma classe que servirá como base para todas as outras submissões relativas ao curso de Teoria dos Grafos.

# Observe as seguintes convenções:

# - o nome da classe é Graph 

# - o método construtor da classe receberá como parâmetro 1 valor inteiro N. N é a quantidade de vértices presentes nesse grafo. Os vértices serão identificados pelos valores [0... N-1]

# - um método polimórfico chamado addEdge será membro dessa classe, da seguinte maneira:

# addEdge(u,v) - adiciona uma aresta direcionada que sai do vértice u para o vértice v

# addEdge(u,v,w) - adiciona uma aresta direcionada que sai do vértice u para o vértice v com peso w

# - um método chamado getInDegree(V) retorna o grau de entrada do vértice V

# - um método chamado getOutDegree(V) retorna o grau de saída do vértice V

# - um método chamada getDegree(V) retorna o grau do vértice V.

# Teste 1

# g = Graph(1)

# g.addEdge(0,0)

# print(g.getInDegree(0), g.getOutDegree(0), g.getDegree(0))

# Saída:

# 1 1 2

# Teste 2

# g = Graph(2)

# g.addEdge(0,1)

# print(g.getInDegree(0), g.getOutDegree(1), g.getInDegree(1),g.getOutDegree(0))

# Saída:

# 0 0 1 1 

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