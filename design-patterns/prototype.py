#!/bin/env python
import copy

# ---------- 原型类：实现克隆方法 ----------
class Sheep:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    # 浅拷贝实现克隆（最简形式）
    def clone(self):
        # 使用 copy.copy 进行浅拷贝（也可使用 __dict__.copy() 或手动新建对象赋值）
        return copy.copy(self)

    # 如果需要深拷贝（例如对象包含列表、字典等可变嵌套结构），可以使用 copy.deepcopy
    def deep_clone(self):
        return copy.deepcopy(self)

    def __str__(self):
        return f"Sheep(name={self.name}, age={self.age}, id={id(self)})"

# ---------- 客户端 ----------
if __name__ == "__main__":
    # 创建原型对象
    original = Sheep("Dolly", 3)
    print("原始对象:", original)

    # 通过克隆创建新对象
    cloned = original.clone()
    print("克隆对象:", cloned)

    # 修改克隆对象的属性，不影响原对象
    cloned.name = "Molly"
    cloned.age = 2
    print("\n修改后的克隆:", cloned)
    print("原始对象不变:", original)
