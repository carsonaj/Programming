import mathematics.category as category

class CategoryRing(category.Category):

    def __init__(self, objects=None, morphisms=None):
        super().__init__(objects, morphisms)

class Homomorphism(category.Morphism):
    def __init__(self, A, B):
        super().__init__(A, B)

R = Ring()
R.test()
