import numpy as np

# stack data structure
class Stack:
    def __init__(self):
        self._items = []

    @property
    def items(self):
        return self._items

    def push(self, x):
        self.items.append(x)

    def pop(self):
        return self.items.pop()

    def peek(self):
        return self.items[len(self.items)-1]

    def is_empty(self):
        return len(self.items) == 0

    def size(self):
        return len(self.items)

#-----------------------------------------------------------------
# queue data structure
class Queue:
    def __init__(self):
        self._items = []

    @property
    def items(self):
        return self._items

    def enqueue(self, item):
        self.items.append(item)

    def dequeue(self):
        self.items.remove(self.items[0])

    def front(self):
        return self.items[0]

    def rear(self):
        return self.items[len(self.items)-1]

    def is_empty(self):
        return len(self.items) == 0

    def size(self):
        return len(self.items)

#-----------------------------------------------------------------
# deque data structure
class Deque:
    def __init__(self):
        self._items = []

    @property
    def items(self):
        return self._items

    def add_front(self, item):
        self.items.insert(0, item)

    def add_rear(self, item):
        self.items.append(item)

    def front(self):
        return self.items[0]

    def rear(self):
        return self.items[len(self.items)-1]

    def is_empty(self):
        return len(self.items) == 0

    def size(self):
        return len(self.items)

#-----------------------------------------------------------------
# node/tree/forest data structure for trees
class Node:
    def __init__(self, data=None, parent=None):
        if parent is None:
            self._parent = self
        else:
            assert isinstance(parent, Node)
            self._parent = parent
        self._data = data
        self._children = []
        if parent is not None:
            parent.add_child(self)

    @property
    def parent(self):
        return self._parent

    @parent.setter
    def parent(self, parent):
        self._parent = parent

    @property
    def data(self):
        return self._data

    @property
    def children(self):
        return self._children

    def add_child(self, child):
        assert isinstance(child, Node)
        self.children.append(child)

    def descendants(self):
        descendants = [self]
        for child in self.children:
            descendants = descendants + child.descendants()
        return descendants

class Tree:
    def __init__(self, root=None):
        if root is None:
            self._root = root
        else:
            assert isinstance(root, Node)
            self._root = root

        if root is None:
            self._nodes = []
        else:
            self._nodes = self.root.descendants()

    @property
    def root(self):
        return self._root

    @property
    def nodes(self):
        return self._nodes

    def is_root(self, node):
        assert isinstance(node, Node) and node in self.nodes
        return self.root == node

    def parent(self, node):
        assert isinstance(node, Node) and node in self.nodes
        return node.parent

    def children(self, node):
        assert isinstance(node, Node) and node in self.nodes
        return node.children

    def is_empty(self):
        return len(self.nodes) == 0

#-------------------------------------------------------------------
# disjoint sets data structure (implemented using nodes)
class Partition:
    def __init__(self):
        self._sets = []
        self._elements = []
# not sure if i should have make_set only
#take instances of class Node or
#anything and make it of class Node
    @property
    def sets(self):
        return self._sets

    @property
    def elements(self):
        return self._elements

    def make_set(self, element=None):
        """makes a new disjoint set containing
        only element"""
        if element is None:
            pass
        else:
            x = Node(data=element)

            if x not in self.elements:
                self.elements.append(x)
                self.sets.append(x)

    def find_set(self, element):
        """return the representative of the set
        that contains element"""

        assert isinstance(element, Node) and element in self.elements
        if element.parent == element:
            return element
        else:
            return self.find_set(element.parent)

    def union(self, element1, element2):
        """forms the union of the sets containing
        element1 and element2 repectively"""

        assert all([isinstance(element1, Node), isinstance(element2, Node),
                    element1 in self.elements, element2 in self.elements])
        x1 = self.find_set(element1)
        y1 = self.find_set(element2)

        if x1 == y1:
            return y1
        else:
            x1.parent = y1
            y1.add_child(x1)
            self.sets.remove(x1)

#---------------------------------------------------------------------
# regular graph data structure
class Vertex:
    def __init__(self, data):
        self._data = data

    @property
    def data(self):
        return self._data

    @property
    def adjacent(self):
        return self._adjacent

class Edge:
    def __init__(self, vertex1, vertex2, directed=False, weight=1):
        assert isinstance(vertex1, Vertex) and isinstance(vertex2, Vertex)
        self._vertices = (vertex1, vertex2)
        self._weight = weight

    @property
    def vertices(self):
        return self._vertices

    @property
    def weight(self):
        return self._weight

    def __eq__(self, other):
        assert isinstance(other, Edge)

        if (self.vertices == other.vertices or
        self.vertices == (other.vertices[1], other.vertices[0])):
            return True
        else:
            return False

    def __neq__(self, other):
        if not self == other:
            return True
        else:
            return False

    def adjacent(self, vertex):
        assert isinstance(vertex, Vertex) and vertex in self.vertices
        if vertex != self.vertices[0]:
            return self.vertices[0]
        else:
            return self.vertices[1]

class Graph:
    def __init__(self, adj_mat=None):
        """defines a graph given the adjacency matrix
        as a two dimensional numpy array or given the
        vertices and edges explicitely"""

        if  isinstance(adj_mat, np.ndarray):
            self._adj_mat = adj_mat
            self._size = self.adj_mat.shape[0]
            self._vertices = self.make_vertices()
            self._edges = self.make_edges()
            self._deg_mat = self.make_deg_mat()
            self._lap_mat = self.make_lap_mat()
            self._vertex_dict = {x.data: x for x in self.vertices}

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
        return self._lap_mat

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

    def make_vertices(self):
        """returns the set of
        vertices of a graph given by adj_mat"""

        return list(map(lambda x: Vertex(data=x), list(range(self.size))))

    def make_edges(self):
        """returns a list of edges of a graph given by adj_mat"""

        edges = [(vert1, vert2) for vert1 in self.vertices for vert2 in
                 self.vertices if vert1.data < vert2.data and
                 self.adj_mat[vert1.data][vert2.data] !=0]

        return list(map(lambda x: (Edge(x[0], x[1],
                        weight=self.adj_mat[x[0].data][x[1].data])),
                        edges))

    def degree(self, vertex):
        """returns the degree of vertex given by adj_mat"""
        return np.sum(self.adj_mat[vertex.data])

    def make_deg_mat(self):
        """returns the degree matrix of a graph given by adj_mat"""
        deg_mat = np.zeros((self.size, self.size))
        for vert in self.vertices:
            deg_mat[vert.data][vert.data] = self.degree(vert)
        return deg_mat

    def make_lap_mat(self):
        return np.subtract(self.deg_mat, self.adj_mat)

    def connected_components(self):
        """returns the set of connected component graphs"""

        p = Partition()
        d = dict()

        for v in self.vertices:
            p.make_set(element=v)

        for node in p.elements:
            d[node.data] = node

        for edge in self.edges:
            if (p.find_set(d[edge.vertices[0]])
            != p.find_set(d[edge.vertices[1]])):
                p.union(d[edge.vertices[0]], d[edge.vertices[1]])

        return list(map(lambda x: list(map( lambda y: y.data.data, x.descendants())), p.sets))

    def maximal_clique(self, vertex):
        """given a vertex of a connected graph, returns a
        maximal clique containing the vertex"""

        clique = [vertex]

        for vert1 in self.vertices:
            for vert2 in clique:
                if Edge(vert1, vert2) in self.edges:
                    clique.append(vert1)

        return list(map(lambda x: x.data, clique))
