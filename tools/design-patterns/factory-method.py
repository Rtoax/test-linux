#!/bin/env python

class Product:
    def use(self):
        return "product"

class ConcreteProduct(Product):
    def use(self):
        return "concrete"

class Creator:
    def factory(self):
        return Product()

class ConcreteCreator(Creator):
    def factory(self):
        return ConcreteProduct()

print(ConcreteCreator().factory().use())
print(type(ConcreteCreator().factory()))
