# Line Functions - Python Practice Problems
# Reese Ford
# Created 10/22/2024
# Modified 10/22/2024 by Reese Ford
# Last Commit: none

# Line = [y, m, x, b]

def calc_slope(elementList):
    return (elementList[0] - elementList[3]) / elementList[2]

def calc_y(elementList):
    return elementList[0] + elementList[1]*elementList[2]

def calc_x(elementList):
    return (elementList[0] - elementList[3]) / elementList[1]

def calc_b(elementList):
    return elementList[0] - elementList[1]*elementList[2]
