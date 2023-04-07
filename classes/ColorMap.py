import numpy as np
from PIL.ImageColor import getrgb
from scipy.interpolate import interp1d

class ColorMap():
  type: str
  def __init__(self, type: str):
    ''' type = 'gradient' or 'hsb' '''
    self.type = type

  def colorMap(self, *args, **kwargs):
    if self.type == 'gradient':
      return self._gradient()
    elif self.type == 'hsb':
      return self._hsb(*args, **kwargs)

  def _hsb(self, hue_degrees: int, saturation: float, brightness: float):
    return getrgb(
        f"hsv({hue_degrees % 360},"
        f"{saturation * 100}%,"
        f"{brightness * 100}%)"
    )

  def _denormalize(self, palette):
    return [
        tuple(int(channel * 255) for channel in color)
        for color in palette
    ]

  def _gradient(self):
    black = (0, 0, 0)
    blue = (0, 0, 1)
    maroon = (0.5, 0, 0)
    navy = (0, 0, 0.5)
    red = (1, 0, 0)

    colors = [black, navy, blue, maroon, red, black]
    gradient = self._make_gradient(colors, interpolation="cubic")

    num_colors = 256
    palette = self._denormalize([
        gradient(i / num_colors) for i in range(num_colors)
    ])
    return palette
  
  def _make_gradient(self, colors, interpolation="linear"):
    X = [i / (len(colors) - 1) for i in range(len(colors))]
    Y = [[color[i] for color in colors] for i in range(3)]
    channels = [interp1d(X, y, kind=interpolation) for y in Y]
    return lambda x: [np.clip(channel(x), 0, 1) for channel in channels]