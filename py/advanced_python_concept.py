"""
Advanced Python Concepts
"""

# x: int = 10 data type setup possible to declear a var. int float str bool 
# 1- Variables and Data Types (with Type Hinting)
x: int = 10           # Integer
pi: float = 3.14      # Float
name: str = "Python"  # String
is_valid: bool = True  # Boolean

from typing import Any

def print_types(*args: Any) -> None:
  print(*(type(arg) for arg in args))

print_types(x, pi, name, is_valid)

# 2- Conditional Statements with Ternary Operator
print("x is bigger than 5" if x > 5 else "x is 5 or less")

# 3- Loops with Enumerate
for i, val in enumerate(range(5), 1):
  print(f"loop({i}): {val}")

count = 0
while count < 5:
  print(f"while loop({count})")
  count += 1

# 4- List and Tuples with Advanced Operations
lst = [1, 2, 3, 4]
tpl = (5, 6, 7, 8)
lst.append(5)
lst.extend([6, 7])
print(lst, tpl)

# 5- Dictionary and Set Operations
dict_sample = {"name": "Alice", "age": 25}
set_sample = {1, 2, 3, 4}
dict_sample["city"] = "New York"
set_sample.add(5)
print(dict_sample, set_sample)

# 6- Function with *args and **kwargs
def add(a: int, b: int = 10, *args: int, **kwargs: Any) -> int:
  return a + b + sum(args)

print(add(5, 5, 2, 3, x=100))

# 7- Class with Static Method and Property Decorator
class Person:
  def __init__(self, name: str, age: int):
    self._name = name
    self._age = age

  @property
  def age(self) -> int:
    return self._age

  @staticmethod
  def species() -> str:
    return "Homo sapiens"

  def introduce(self) -> str:
    return f"Hello, I'm {self._name}, {self._age} years old."

p = Person("Alice", 25)
print(p.introduce(), p.species())

# 8- Exception Handling with Multiple Exceptions
try:
  result = 10 / 0
except (ZeroDivisionError, ValueError) as e:
  print(f"Error: {e}")
finally:
  print("Completed execution")

# 9- File I/O with Context Manager and Exception Handling
try:
  with open("sample.txt", "w") as file:
    file.write("Hello, Advanced Python!")

  with open("sample.txt", "r") as file:
    print(file.read())
except IOError as e:
  print(f"File error: {e}")

# 10- List Comprehension with Conditionals
squared_odd_numbers = [x**2 for x in range(10) if x % 2 == 1]
print(squared_odd_numbers)

# 11- Lambda Function with Map and Filter
square = lambda x: x ** 2
filtered_numbers = list(filter(lambda x: x > 5, map(square, range(10))))
print(filtered_numbers)

# 12- Decorator with Arguments
def repeat(n: int):
  def decorator(func):
    def wrapper(*args, **kwargs):
      for _ in range(n):
        func(*args, **kwargs)
    return wrapper
  return decorator

@repeat(3)
def say_hello():
  print("Hello!")

say_hello()

# 13- Generator with Yield from
def my_generator():
  yield from range(3)

gen = my_generator()
print(next(gen), next(gen), next(gen))
