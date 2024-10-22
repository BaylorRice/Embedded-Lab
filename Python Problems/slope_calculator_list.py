# Slope Calculator List - Python Practice Problems
# Reese Ford
# Created 10/22/2024
# Modified 10/22/2024 by Reese Ford
# Last Commit: none

def calc_slope_list(elementList):
    return (elementList[0] - elementList[3]) / elementList[2]

lineList1 = [28, 999, 3, 5]
lineList2 = [135, 888, 21, -325]

lineList1[1] = calc_slope_list(lineList1)
lineList2[1] = calc_slope_list(lineList2)