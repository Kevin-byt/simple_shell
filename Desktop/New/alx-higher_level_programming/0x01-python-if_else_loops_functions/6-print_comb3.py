#!/usr/bin/python3
for num in range(0, 10):
    for sec_num in range(num + 1, 10):
        if num == 8 and sec_num == 9:
            print("{}{}".format(num, sec_num))
        else:
            print("{}{}".format(num, sec_num), end=", ")
