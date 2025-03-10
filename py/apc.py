"""

apc.py (Advanced Python Concepts)

Author: from openAI import chatGPT codes

tf8

"""

# x: int = 10 data type setup possible to declear a var. int float str bool 
# 1- Variables and Data Types (with Type Hinting)
x: int = 10           # Integer
pi: float = 3.14      # Float
name: str = "Python"  # String
is_valid: bool = True  # Boolean
test1: str = "test1 string variable one decleared!"
test_integer: int = 100
is_tested: bool = True
from typing import Any
def print_type(*args: Any) -> None:
  print(*(type(arg) for arg in args))
print_type(test1, test_integer, is_tested)


# typing module(readability and mypy type checking tool only used not using in execution time), Any object(an typehinting metadata) 
from typing import Any

# None -> return type nothing! *(Variable length var) 
def print_types(*args: Any) -> None:
  print(*(type(arg) for arg in args))

print_types(x, pi, name, is_valid)

# 2- Conditional Statements with Ternary Operator ( 3 speedy type if else ) ( c ? 1: 0 <-- same )
print("x is bigger than 5" if x > 5 else "x is 5 or less")
print("a is small than 5" if x < 5 else "a is 5 or big")


# 3- Loops with Enumerate # other's type: Enumerate using loop! range(5) = 0...4 onto i, 1 = index onto i 
#    enumerate return a tuple 
for i, val in enumerate(range(5), 1):
  print(f"loop({i}): {val}")

# 3_1.- 3 more value set to before for after vars possible using tuples and list

data = [ (10, "apple", "a"), (20, "banana", "b"), (30, "cherry", "c") ] 

for i, (num, fruit, firstchar) in enumerate(data, 1):  
    print(f"Index: {i}, Number: {num}, Fruit: {fruit} FirstChar: {firstchar}")

data2 = [(1, "KJ1", "virtual1"), (2, "Toda1", "tida"), (3, "Erika", "c")]
for i, (num, names, desc) in enumerate(data2, 1):
  print(f"Index: {i}, num: {num}, Name: {names}, Description: {desc}")

count0 = 0
while count0 < 5:
  print(f"while loop {count0}")
  count0 += 1

count = 0
while count < 5:
  print(f"while loop({count})")
  count += 1

# 4- List and Tuples with Advanced Operations
# two more append using [x, y, z]
lst = [1, 2, 3, 4]
tpl = (5, 6, 7, 8)
lst.append(5)
lst.extend([6, 7, 8])
print(lst, tpl)
lst2 = [1, 2, 3, 4, 5]
tpl2 = (5, 6, 7, 8, 9)
lst2.append(6)
lst2.extend([6, 7, 8, 9])
print(lst2, tpl2)


# 5- Dictionary and Set Operations
dict_sample = {"name": "Alice", "age": 25}
set_sample = {1, 2, 3, 4}
dict_sample["city"] = "New York"
set_sample.add(5)
print(dict_sample, set_sample)

dict2 = {"rn": "KJ", "age": 1}
dict2["wording"] = "haha"
dict2["wording2"] = "hello"
set1 = {1, 2, 3, 4, 5, 6, 8, 9, 10}
set1.add(7)
set2 = {1, 2, 3, 4}
for j in range(30):
  set2.add(j+1)

print(dict2, set1)
print(set2)

# 6- Function with *args and **kwargs
def add(a: int, b: int = 10, *args: int, **kwargs: Any) -> int:
  return a + b + sum(args)

print(add(5, 5, 2, 3, x=100))

def add_2(a: int, b: int = 10, *args: int, **kwargs: Any) -> int:
    return a + b + sum(args) + sum(kwargs.values())

print(add_2(5, 5, 2, 3, x=100, i=300, z=-30))  # 출력: 115 (5 + 5 + 2 + 3 + 100)



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

p = Person("KJ", 1)
print(p.introduce(), p.species())

class Person2:
  def __init__(self, name2: str, age2: int):
    self._name = name2
    self._age = age2

  @property
  def age(self) -> int:
    return self._age

  @staticmethod
  def species() -> str:
    return "Hum"

  def introdu(self) -> str:
    return f"Hello~ {self._name}: {self._age} yesrs old..."

p = Person2("KJKJKJKJKJKJKJ", 2)
print(p.introdu, p.species())

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

### python is a scripting.
### system supports
### but it's bad error control.
### many not good deserted codes and walking code types in a one styles.
### .
### like this.
### dirty
### 4 space? tab ? what the heck?! hacker style.

