import numpy as np

# LDR readings (0-1023) vs desired LED brightness (0-255)
# Replace with your own measured data for better marks
ldr = np.array([50, 150, 300, 450, 600, 750, 900, 1000])
brightness = np.array([250, 215, 170, 130, 90, 50, 15, 0])

w, b = np.polyfit(ldr, brightness, 1)  # linear regression
print(f"const float W = {w:.4f}f;")
print(f"const float B = {b:.4f}f;")
