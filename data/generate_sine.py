import math

with open("sine_table.txt", "w") as f:
    for angle in range(360):
        value = math.sin(math.radians(angle))
        f.write(f"{angle} {value}\n")
