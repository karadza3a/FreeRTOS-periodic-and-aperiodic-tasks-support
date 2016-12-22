import fileinput
import re
from matplotlib.patches import Rectangle
import matplotlib.pyplot as plt
import numpy as np
from process import NameIndexer, process

# Usage:
#   $ ./cmake-build-debug/FreeRTOS_Sim_master > Python/out.txt
#   $ python Python/plot.py Python/out.txt
# and if you want parsed data:
#   $ python Python/process.py Python/out.txt > Python/out-parsed.txt


class Cursor(object):
    def __init__(self, ax):
        self.ax = ax
        self.lx = ax.axhline(color='k')  # the horiz line
        self.ly = ax.axvline(color='k')  # the vert line

        # text location in axes coords
        self.txt = ax.text(0.7, 0.9, '', transform=ax.transAxes)

    def mouse_move(self, event):
        if not event.inaxes:
            return

        x, y = event.xdata, event.ydata
        # update the line positions
        self.lx.set_ydata(y)
        self.ly.set_xdata(x)

        self.txt.set_text('x=%1.2f, y=%1.2f' % (x, y))
        plt.draw()


class SnapToCursor(object):
    """
    Like Cursor but the crosshair snaps to the nearest x,y point
    For simplicity, I'm assuming x is sorted
    """

    def __init__(self, ax, x):
        self.ax = ax
        self.ly = ax.axvline(color='k')
        self.x = x
        self.txt = ax.text(0.7, 0.9, '', transform=ax.transAxes)

    def mouse_move(self, event):

        if not event.inaxes:
            return

        x, y = event.xdata, event.ydata

        idx = np.searchsorted(self.x, [x])[0]
        if idx < len(self.x):
            x = self.x[idx]
            self.ly.set_xdata(x)
            self.txt.set_text('x=%.0f' % x)
        plt.draw()


def main():
    print("Parsing input...")
    parsed, time_max, i_max = process(fileinput.input())
    print("Input parsed")

    fig, ax = plt.subplots()
    ax.axis([-5, time_max + 100, -0.1, 0.1])
    ax.grid(which='vertical')

    xs = []
    indexer = NameIndexer()
    patches = {}
    colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k', 'w']
    for l in parsed:
        r = re.compile("(.+): (\d+)-(\d+)")
        groups = r.search(l)
        name, t1, t2 = groups.group(1), int(groups.group(2)), int(groups.group(3))
        i = indexer.index_for_name(name)
        x = [t1, t2]
        y = [0, 0]
        xs.append(t2)
        ax.plot(x, y, '-' + colors[i], label=name, linewidth=50, solid_capstyle="butt")
        patches[name] = Rectangle((0, 0), 1, 1, fc=colors[i], fill=True)

    plt.legend(
        [patches[k] for k in patches.keys()],
        [k for k in patches.keys()],
        loc="upper left"
    )

    cursor = SnapToCursor(ax, xs)
    plt.connect('motion_notify_event', cursor.mouse_move)
    plt.show()


if __name__ == '__main__':
    main()
