import computing.data_structures as ds

# suffix tree and Ukkonen's algorithm implementation

# suffix tree node implementation
class SuffixNode(ds.Node)

    def __init__(self, data=None, parent=None, children=[], path='', link=None):
        super().__init__(data=data, parent=parent)
        self.path = path
        self.link = link

    def add_child(self, child):
        assert isinstance(child, SuffixNode)
        self.children.append(child)

    def change_parent(self, new_parent):
        assert isinstance(new_parent, SuffixNode)
        self.parent = new_parent

# Ukkonen's algorithm implementation

def build_suffix_tree(str):
    root  = SuffixNode():
    root

# -----------------------------------------------------
