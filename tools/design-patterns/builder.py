#!/bin/env python

# ---------- Product ----------
class Computer:
    def __init__(self):
        self.cpu = None
        self.memory = None
        self.disk = None

    def __str__(self):
        return f"Computer(cpu={self.cpu}, memory={self.memory}, disk={self.disk})"

# ---------- Builder ----------
class ComputerBuilder:
    def __init__(self):
        self.computer = Computer()

    def build_cpu(self):
        pass

    def build_memory(self):
        pass

    def build_disk(self):
        pass

    def get_result(self):
        return self.computer

# ---------- Builder: Office Computer ----------
class OfficeComputerBuilder(ComputerBuilder):
    def build_cpu(self):
        self.computer.cpu = "Intel i3"

    def build_memory(self):
        self.computer.memory = "8GB DDR4"

    def build_disk(self):
        self.computer.disk = "256GB SSD"

# ---------- Builder: Gaming Computer ----------
class GamingComputerBuilder(ComputerBuilder):
    def build_cpu(self):
        self.computer.cpu = "Intel i9"

    def build_memory(self):
        self.computer.memory = "32GB DDR5"

    def build_disk(self):
        self.computer.disk = "1TB NVMe SSD"

# ---------- 导演（可选，但体现模式精髓）----------
class Director:
    def __init__(self, builder: ComputerBuilder):
        self.builder = builder

    def construct_computer(self):
        self.builder.build_cpu()
        self.builder.build_memory()
        self.builder.build_disk()
        return self.builder.get_result()

# ---------- 客户端 ----------
if __name__ == "__main__":
    # 建造办公电脑
    office_builder = OfficeComputerBuilder()
    director = Director(office_builder)
    office_pc = director.construct_computer()
    print("办公电脑:", office_pc)

    # 建造游戏电脑
    gaming_builder = GamingComputerBuilder()
    director = Director(gaming_builder)
    gaming_pc = director.construct_computer()
    print("游戏电脑:", gaming_pc)
