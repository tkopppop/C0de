

"""

basic

"""

# 1- var and data type
x = 10           # int
pi = 3.14        # float
name = "Python"  # str
is_valid = True  # bool

def print_types():
  print(type(x), type(pi), type(name), type(is_valid))
print_types()

# 2- if~elif~else
if x > 5:
  print("x is bigger than 5")
elif x == 5:
  print("x is 5.")
else:
  print("x is less than 5")

# 3- loop
for i in range(5):
  print("loop(5)", i)

count = 0
while count < 5:
  print("while loop(5)", count)
  count += 1

# 4- list and tuples
lst = [1, 2, 3, 4]
tpl = (5, 6, 7, 8)
lst.append(5)  # append list item
print(lst, tpl)

# 5- dictionary and set
dict_sample = {"name": "Alice", "age": 25}
set_sample = {1, 2, 3, 4}
print(dict_sample["name"], set_sample)

# 6- define function and calls
def add(a, b=10):
  return a + b
print(add(5))

# 7- class and oopS
class Person:
  def __init__(self, name, age):
      self.name = name
      self.age = age

  def introduce(self):
    return f"Hello, I'm {self.name} : {self.age}."

p = Person("Alice", 25)
print(p.introduce())

# 8- excpt
try:
  result = 10 / 0
except ZeroDivisionError:
  print("can't devide by 0")
finally:
  print("comple!t")

# 9- file input/output
with open("sample.txt", "w") as file:
  file.write("Hello, Python!")

with open("sample.txt", "r") as file:
  print(file.read())

# 10- list comprehension
squared_numbers = [x**2 for x in range(5)]
print(squared_numbers)

# 11- lambda funcs (람다 함수들) **..씨언어에서는 하나씩 띄워서 곱하기 해야 하죠 ^^ 3*3*3*3 네. 그런 표현이네요 같은-)...
square = lambda x: x ** 2
print(square(4))

# 12- decoration wrapper function could be define for calling say_hello()
def decorator(func):
  def wrapper():
    print("pre function to call")
    func()
    print("after function to called")
  return wrapper

@decorator # @repeat(3)와 같이 데코레이터를 설정할 수 있음. 데코레이터에서는 n: int와 같이 인자를 수신해야 한다.
def say_hello():
  print("Hello!")

  say_hello() # say_hello -> say_hello decorator -> say_hello(by func) -> say_hello(not call decorator) direct say_hello func calling made.

# 13- generator
def my_generator():
  for i in range(3):
    yield i

gen = my_generator()
print(next(gen), next(gen), next(gen))
# end of codes
# dirty
# hacker style.
