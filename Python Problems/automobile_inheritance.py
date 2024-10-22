# Automobile Inheritance - Python Practice Problems
# Reese Ford
# Created 10/22/2024
# Modified 10/22/2024 by Reese Ford
# Last Commit: none

from automobile_class import Automobile

class Truck(Automobile):
    def __init__(self, make, model, mpg, range, fuelType, cargoCapacity, cargoWeight):
        super().__init__(make, model, mpg, range, fuelType)
        self.cargoCapacity = cargoCapacity
        self.cargoWeight = cargoWeight

vehicle3 = Truck("Ford", "F-350", 10, 400, "diesel", 2000, 1500)
v3Gallons = vehicle3.CalculateGallonsUsed(250)
print(vehicle3.make, vehicle3.model, "used", v3Gallons, "of gas while carrying", vehicle3.cargoWeight, "lbs of cargo")