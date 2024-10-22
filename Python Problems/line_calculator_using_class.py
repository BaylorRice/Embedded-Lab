# Line Calculator using Class - Python Practice Problems
# Reese Ford
# Created 10/22/2024
# Modified 10/22/2024 by Reese Ford
# Last Commit: none

class LineCalculator:
    def __init__(self, name, lineData):
        self.name = name
        self.lineData = lineData
    
    def calc_slope(self):
        return (self.lineData[0] - self.lineData[3]) / self.lineData[2]

    def calc_y(self):
        return self.lineData[0] + self.lineData[1] * self.lineData[2]

    def calc_x(self):
        return (self.lineData[0] - self.lineData[3]) / self.lineData[1]

    def calc_b(self):
        return self.lineData[0] - self.lineData[1] * self.lineData[2]

    def print_line(self):
        print(self.name + ":")
        print("Slope:", self.calc_slope())
        print("Y:", self.calc_y())
        print("X:", self.calc_x())
        print("B:", self.calc_b())
        print("")
    
line1 = LineCalculator("Line 1", [34, 56, 7, -123])
line2 = LineCalculator("Line 2", [-873, 123, 1, 29])
line3 = LineCalculator("Line 3", [3, 7, 99, -4])
line4 = LineCalculator("Line 4", [865, -235, 777, -928])

line1.print_line()
line2.print_line()
line3.print_line()
line4.print_line()
