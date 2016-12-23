import fileinput
import matplotlib.pyplot as plt
from process import NameIndexer, process

# Usage:
#   $ ./cmake-build-debug/FreeRTOS_Sim_master > Python/out.txt
#   $ python Python/plot.py Python/out.txt
# and if you want parsed data:
#   $ python Python/process.py Python/out.txt > Python/out-parsed.txt


def main():
    print("Parsing input...")
    _, c_parser = process(fileinput.input())
    print("Input parsed")

    x, y = zip(*c_parser.output_dict.items())
    plt.plot(x, y)
    plt.show()


if __name__ == '__main__':
    main()
