# Auto Mobile - Python Practice Problems
# Reese Ford
# Created 10/22/2024
# Modified 10/22/2024 by Reese Ford
# Last Commit: b45ae8b2d8ab0042d61d308cfa3deb5cd2e9296d

class Automobile:
    def __init__(self, make, model, mpg, range, fuelType):
        self.make = make
        self.model = model
        self.mpg = mpg
        self.range = range
        self.fuelType = fuelType
    
    def CalculateGallonsUsed(self, milesDriven):
        return milesDriven * (1 / self.mpg)

vehicle1 = Automobile("Toyota", "Camry Hybrid", 48, 500, "regular")
v1Gallons = vehicle1.CalculateGallonsUsed(250)

vehicle2 = Automobile("Honda", "CRV Hybrid", 35, 450, "regular")
v2Gallons = vehicle2.CalculateGallonsUsed(250)

print(vehicle1.make, vehicle1.model, "used", v1Gallons, "of gas")
print(vehicle2.make, vehicle2.model, "used", v2Gallons, "of gas")