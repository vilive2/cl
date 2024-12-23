from sympy import symbols, solve, integrate, Abs
import sys

def find_intersection(x1, y1, x2, y2, x3, y3, x4, y4):
    """
    Finds the intersection of two lines defined by points (x1, y1), (x2, y2)
    and (x3, y3), (x4, y4). Returns None if the lines are parallel.
    """
    # Calculate the determinants
    denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)

    if denominator == 0:
        return None  # Lines are parallel or coincident

    # Numerators for the x and y coordinates
    px_numerator = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
    py_numerator = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4))

    # Intersection point
    px = px_numerator / denominator
    py = py_numerator / denominator

    return px, py


def line_equation(x1, y1, x2, y2, x):
    """Returns the line equation in terms of x for two points (x1, y1) and (x2, y2)."""
    slope = (y2 - y1) / (x2 - x1)
    return slope * (x - x1) + y1

def find_area_between_lines(x1, y1, x2, y2, x3, y3, x4, y4, x_range):
    """
    Calculates the area between two lines defined by points (x1, y1), (x2, y2) 
    and (x3, y3), (x4, y4) in the given x-range.
    
    Parameters:
    - x1, y1, x2, y2: Points defining the first line.
    - x3, y3, x4, y4: Points defining the second line.
    - x_range: A tuple (x_start, x_end) representing the range of x.
    
    Returns:
    - The total area between the two lines in the given range.
    """
    x = symbols('x')
    
    # Define the two line equations
    f1 = line_equation(x1, y1, x2, y2, x)
    f2 = line_equation(x3, y3, x4, y4, x)
    
    # Find intersection points
    intersection_points = solve(f1 - f2, x)
    intersection_points = [pt for pt in intersection_points if x_range[0] <= pt <= x_range[1]]
    
    # Include the start and end points of the range
    points = [x_range[0]] + intersection_points + [x_range[1]]
    
    # Calculate the area in each subrange
    total_area = 0
    for i in range(len(points) - 1):
        subrange = (points[i], points[i + 1])
        difference = Abs(f1 - f2)
        area = integrate(difference, (x, subrange[0], subrange[1]))
        total_area += area
    
    return total_area

# Example usage:
# x1, y1, x2, y2 = 5, -2, 7, 1  # Line 1 points
# x3, y3, x4, y4 = 3, 3, 6, 1  # Line 2 points
# x_range = (5, 6)

# intersection = find_intersection(x1, y1, x2, y2, x3, y3, x4, y4)
# if intersection:
#     print(f"The intersection point is: {intersection}")
# else:
#     print("The lines do not intersect (they are parallel or coincident).")

# area = find_area_between_lines(x1, y1, x2, y2, x3, y3, x4, y4, x_range)
# print(f"The area between the lines in the range {x_range} is: {area}")



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

            m = int(fn1[0])
            n = int(fn2[0])

            area = 0.0
            i, j = 0, 0
            while i < m - 1 and j < n - 1 :
                x1, y1, x2, y2 = f_xs[i], f_ys[i], f_xs[i+1], f_ys[i+1]  # Line 1 points
                x3, y3, x4, y4 = g_xs[j], g_ys[j], g_xs[j+1], g_ys[j+1]  # Line 2 points
                x_range = (max(a, x1, x3), min(b, x2, x4))
                if x_range[0] < x_range[1]:
                    area += find_area_between_lines(x1, y1, x2, y2, x3, y3, x4, y4, x_range)

                if x2 == x4 :
                    i += 1
                    j += 1
                elif x2 < x4 :
                    i += 1
                else :
                    j += 1

            print("%.4f"%area)