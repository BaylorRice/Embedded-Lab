# Slope Calculator Using Module - Python Practice Problems
# Reese Ford
# Created 10/22/2024
# Modified 10/22/2024 by Reese Ford
# Last Commit: none

import line_functions as lf

lineList = [56, 82, -34, 8]

lineList_slope = lf.calc_slope(lineList)
print("Slope:", lineList_slope)

lineList_y = lf.calc_y(lineList)
print("Y:", lineList_y)

lineList_x = lf.calc_x(lineList)
print("X:", lineList_x)

lineList_b = lf.calc_b(lineList)
print("B:", lineList_b)
