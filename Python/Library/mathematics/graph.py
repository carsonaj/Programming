import numpy as np
import mathematics.category as category
import mathematics.data_structures as ds

class Category_of_Graphs(category.Category):

    def __init__(self, objects=None, morphisms=None):
        super().__init__(objects, morphisms)

class Graph(category.Object):

    def __init__(self, adj_mat=None, vertices=None, edges=None):
        """defines a graph given the adjacency matrix
        as a two dimensional numpy array or given the
        vertices and edges explicitely"""
        super().__init__()
        if vertices == None and edges == None:
            self._adj_mat = adj_mat
            self._deg_mat = deg_mat(self.adj_mat, self.size, self.vertices)
            self._lap_mat = lap_mat(self.adj_mat, self.deg_mat)

            self._size = size(self.adj_mat)
            self._vertices = vertices(self.size)
            self._edges = edges(self.adj_mat, self.vertices)

    @property
    def adj_mat(self):
        """returns the adjacency matrix of the graph"""
        return self._adj_mat

    @property
    def deg_mat(self):
        """returns the degree matrix of the graph"""
        return self._deg_mat

    @property
    def lap_mat(self):
        """returns the laplacian matrix of the graph"""

    @property
    def size(self):
        """returns the number of vertices of the graph"""
        return self._size

    @property
    def vertices(self):
        """retruns the set of vertices of the graph"""
        return self._vertices

    @property
    def edges(self):
        """returns a list of edges of the graph"""
        return self._edges

def size(adj_mat):
    """returns the number of vertices of the graph given by adj_mat"""
    return adj_mat.shape[0]

def vertices(size):
    """returns the set of vertices of a graph given by adj_mat"""
    return set(range(size))

def edges(adj_mat, vertices):
    """returns a list of edges of a graph given by adj_mat"""
    return [(i,j) for i,j in
            vertices if (i < j and adj_mat[i][j] == 1)]

def degree(adj_mat, vertex):
    """returns the degree of vertex given by adj_mat"""
    return np.sum(adj_mat[vertex][:])

def deg_mat(adj_mat, size, vertices):
    """returns the degree matrix of a graph given by adj_mat"""
    deg_mat = np.zeros((size,size))
    for i in vertices:
        deg_mat[i][i] = degree(adj_mat, i)
    return deg_mat

def lap_mat(adj_mat, deg_mat):
    return np.subtract(deg_mat, adj_mat)

def connected_components(vertices, edges):
    """returns the set of connected component graphs"""

    l = dict()

    for v in vertices:
        l[v] = ds.make_set(v)

    for edge in edges:
        if ds.find_set(l[edge[0]]) != ds.find_set(l[edge[1]]):
            ds.union(l[edge[0]], l[edge[1]])

    roots = [l[v] for v in vertices if l[v].parent == l[v]]
    cc = list()

    for root in roots:
        cc.append(list(map(lambda x: x.data, root.descendants())))

    return cc

def maximal_clique(vertex, vertices, edges):
    """given a vertex and the vertices and edges
    of a connected graph, returns a
    maximal clique containing the vertex"""

    clique = [vertex]

    for vert in vertices:
        if all(list(map(lambda x: (min(vert,x), max(vert,x)) in edges, clique))):
            clique.append(vert)

    return clique
