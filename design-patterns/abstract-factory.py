#!/bin/env python

from abc import ABC, abstractmethod

# ---------- 抽象产品 ----------
class Car(ABC):
    @abstractmethod
    def drive(self):
        pass

class Bike(ABC):
    @abstractmethod
    def ride(self):
        pass

# ---------- 具体产品：奔驰系列 ----------
class BenzCar(Car):
    def drive(self):
        return "驾驶奔驰汽车"

class BenzBike(Bike):
    def ride(self):
        return "骑奔驰自行车"

# ---------- 具体产品：宝马系列 ----------
class BmwCar(Car):
    def drive(self):
        return "驾驶宝马车"

class BmwBike(Bike):
    def ride(self):
        return "骑宝马自行车"

# ---------- 抽象工厂 ----------
class VehicleFactory(ABC):
    @abstractmethod
    def create_car(self) -> Car:
        pass

    @abstractmethod
    def create_bike(self) -> Bike:
        pass

# ---------- 具体工厂 ----------
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

# ---------- 客户端 ----------
def client_code(factory: VehicleFactory):
    car = factory.create_car()
    bike = factory.create_bike()
    print(car.drive())
    print(bike.ride())

if __name__ == "__main__":
    print("=== 使用奔驰工厂 ===")
    client_code(BenzFactory())

    print("\n=== 使用宝马工厂 ===")
    client_code(BmwFactory())
