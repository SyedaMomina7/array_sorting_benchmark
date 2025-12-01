import numpy as np

sizes = [10, 500, 2000, 5000]

for n in sizes:
    A = np.random.randint(0, 10, size=(n, n))
    B = np.random.randint(0, 10, size=(n, n))

    # Save with tabs
    np.savetxt(f"matrixA_{n}x{n}.txt", A, fmt="%d", delimiter='\t')
    np.savetxt(f"matrixB_{n}x{n}.txt", B, fmt="%d", delimiter='\t')

print("Matrices generated successfully in tab-separated format!")


