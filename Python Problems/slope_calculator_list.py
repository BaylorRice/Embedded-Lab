# Slope Calculator List - Python Practice Problems
# Reese Ford
# Created 10/22/2024
# Modified 10/22/2024 by Reese Ford
# Last Commit: d5a0e1317efeae0541e263797fac4f62ab1be223

def calc_slope_list(elementList):
    return (elementList[0] - elementList[3]) / elementList[2]

lineList1 = [28, 999, 3, 5]
lineList2 = [135, 888, 21, -325]

slope1 = calc_slope_list(lineList1)
slope2 = calc_slope_list(lineList2)

lineList1[1] = slope1 # type: ignore
lineList2[1] = slope2 # type: ignore

print("Slope of List 1 =", lineList1[1])
print("Slope of Line 2 =", lineList2[1])
print(lineList1)
print(lineList2)
