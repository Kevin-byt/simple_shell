#!/usr/bin/python3
import random
number = random.randint(-10000, 10000)
text1 = 'Last digit of'
last_digit = abs(number) % 10
if number < 0:
    last_digit *= -1
if last_digit > 5:
    print(f"{text1} {number} is {last_digit} and is greater than 5")
elif last_digit == 0:
    print(f"{text1} {number} is {last_digit} and is {last_digit}")
else:
    print(f"{text1} {number} is {last_digit} and is less than 6 and not 0")
