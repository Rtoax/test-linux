#!/bin/env python

from abc import ABC, abstractmethod

# ---------- abstract product ----------
class Car(ABC):
    @abstractmethod
    def drive(self):
        pass

class Bike(ABC):
    @abstractmethod
    def ride(self):
        pass

# ---------- product: benz ----------
class BenzCar(Car):
    def drive(self):
        return "drive Benz Car"

class BenzBike(Bike):
    def ride(self):
        return "ride Benz Bike"

# ---------- product: bmw ----------
class BmwCar(Car):
    def drive(self):
        return "drive Bmw Car"

class BmwBike(Bike):
    def ride(self):
        return "ride Bmw Bike"

# ---------- abstract factory ----------
class VehicleFactory(ABC):
    @abstractmethod
    def create_car(self) -> Car:
        pass

    @abstractmethod
    def create_bike(self) -> Bike:
        pass

# ---------- real factory ----------
class BenzFactory(VehicleFactory):
    def create_car(self) -> Car:
        return BenzCar()

    def create_bike(self) -> Bike:
        return BenzBike()

class BmwFactory(VehicleFactory):
    def create_car(self) -> Car:
        return BmwCar()

    def create_bike(self) -> Bike:
        return BmwBike()

# ---------- client ----------
def client_code(factory: VehicleFactory):
    car = factory.create_car()
    bike = factory.create_bike()
    print(car.drive())
    print(bike.ride())

if __name__ == "__main__":
    print("=== Use BenzFactory ===")
    client_code(BenzFactory())

    print("\n=== Use BmwFactory ===")
    client_code(BmwFactory())
