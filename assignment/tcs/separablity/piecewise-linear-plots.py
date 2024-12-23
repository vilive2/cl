import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import sys

if __name__ == '__main__':
    if len(sys.argv) == 1 :
        sys.exit('Usage: %s <input files>' % sys.argv[0])

    for infile in sys.argv[1:]:
        with open(infile, encoding="utf-8", mode="r") as f:
            fn1 = f.readline().split()
            assert len(fn1) == 2*int(fn1[0]) + 1
            fn2 = f.readline().split()
            assert len(fn2) == 2*int(fn2[0]) + 1
            a, b = [ float(i) for i in f.readline().split() ]

            f_xs = [ float(x) for i,x in enumerate(fn1[1:]) if i % 2 == 0 ]
            f_ys = [ float(x) for i,x in enumerate(fn1[1:]) if i % 2 == 1 ]
            g_xs = [ float(x) for i,x in enumerate(fn2[1:]) if i % 2 == 0 ]
            g_ys = [ float(x) for i,x in enumerate(fn2[1:]) if i % 2 == 1 ]
            min_y = min(f_ys + g_ys)
            max_y = max(f_ys + g_ys)

            # Generate plots
            plt.grid(True)
            plt.plot(f_xs, f_ys, 'r-', g_xs, g_ys, 'b--',
                     [a, a, a], [min_y, 0, max_y], 'k-',
                     [b, b, b], [min_y, 0, max_y], 'k-')
            # plt.savefig(f'input1-{serial}.pdf')
            plt.show()
            plt.clf()

