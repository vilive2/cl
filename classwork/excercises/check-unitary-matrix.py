import numpy as np

n = int(input("Enter the size of the square matrix (n x n): "))

matrix_entries = []

print("Enter the entries of the matrix as complex numbers (e.g., 1+2j):")
for i in range(n):
    row = []
    for j in range(n):
        entry = complex(input(f"Entry ({i+1}, {j+1}): "))
        row.append(entry)
    matrix_entries.append(row)

U = np.array(matrix_entries, dtype=complex)

print("\nMatrix:\n", U)

UH = U.T.conj()

res = np.dot(UH, U)

I = np.eye(res.shape[0], dtype=complex)

is_identity = np.allclose(res, I)

if is_identity:
    print("Unitary.")
else:
    print("Not Unitary.")