from PIL import Image
from classes import *
import numpy as np
from matplotlib import pyplot as plt

def paint(mandelbrot_set, viewport, palette, smooth):
    for pixel in viewport:
        stability = mandelbrot_set.stability(complex(pixel), smooth)
        index = int(min(stability * len(palette), len(palette) - 1))
        pixel.color = palette[index % len(palette)]

def render(center, width):
    colorMap = ColorMap("hsb")
    mandelbrot_set = MandelbrotSet(max_iterations=20, escape_radius=1000)
    image = Image.new(mode="RGB", size=(128, 128))
    for pixel in Viewport(image, center=center, width=width):
        stability = mandelbrot_set.stability(complex(pixel), smooth=True)
        pixel.color = (0, 0, 0) if stability == 1 else colorMap.colorMap(
            hue_degrees=int(stability * 360),
            saturation=stability,
            brightness=1,
        )
    return image

width = 3.5
center = -0.75
image = render(center, width)
fig, ax = plt.subplots()
def on_key_press(event):
    global width, ax, center
    offset = 0.1
    if event.key == "+" or event.key == "=":
        width /= 2
    elif event.key == "up":
        center += offset * 1j
    elif event.key == "down":
        center -= offset * 1j
    elif event.key == "left":
        center -= offset
    elif event.key == "right":
        center += offset
    else:
        print(event.key)
    image = render(center, width)
    ax.imshow(image)
    plt.show()

fig.canvas.mpl_connect("key_press_event", on_key_press)
ax.imshow(image)
plt.show()
