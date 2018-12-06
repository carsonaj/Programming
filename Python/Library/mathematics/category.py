from abc import ABC, abstractmethod

class Category(ABC):
    
    def __init__(self, objects=None, morphisms=None):
        """intializes a category with objects 
        and morphisms"""
        super().__init__()
        self._objects = objects
        self._morphisms = morphisms
    
    @property    
    def objects(self):
        """returns the objects of the category"""
        return self._objects
    
    @property
    def morphisms(self):
        """returns the morphisms of 
        the category"""
        return self._morphisms

class Object(ABC):
    def __init__(self):
        """initializes an object"""
        super().__init__()

class Morphism(ABC):
    """The morphism class"""
    
    def __init__(self, A, B):
        """initializes a morphism with domain 
        A and codomain B"""
        super().init()
        self._domain = A
        self._codomain = B                
    
    @property    
    def domain(self):
        """returns the domain of morphism"""
        return self._domain

    @property    
    def codomain(self):
        """returns codomain of the morphism"""
        return self._codomain
    
    @abstractmethod
    def identity(A):
        """returns the identity morphism for 
        object A"""
        pass
    
    @abstractmethod
    def compose(self, other):
        """returns the morphism 'self' composed with 
        the morphism 'other'"""
        pass
    
    def __mul__(self, other):
        """overrides the the multiplication 
        syntax to be used with composition"""
        return self.compose(other)
    