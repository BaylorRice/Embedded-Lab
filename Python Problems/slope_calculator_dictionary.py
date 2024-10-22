# Slope Calculator Dictionary - Python Practice Problems
# Reese Ford
# Created 10/22/2024
# Modified 10/22/2024 by Reese Ford
# Last Commit: 13801668ff8ea79726757fa88a2b1683d8bac6c2

def calc_slope_list(elementDict):
    return (elementDict['y'] - elementDict['b']) / elementDict['x']

lineDict1 = {'y': 28, 'm': 999, 'x': 3, 'b': 5}
lineDict2 = {'y': 135, 'm': 888, 'x': 21, 'b': -325}

slope1 = calc_slope_list(lineDict1)
slope2 = calc_slope_list(lineDict2)

lineDict1['m'] = slope1 # type: ignore
lineDict2['m'] = slope2 # type: ignore

print("Slope of List 1 =", lineDict1['m'])
print("Slope of Line 2 =", lineDict2['m'])
print(lineDict1)
print(lineDict2)
