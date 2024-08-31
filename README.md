# Vector Addition Performance Measurement

This project is designed to measure the performance of vector addition on a single-core ARM system. The program initializes two arrays with random numbers, performs element-wise addition of these arrays, and measures the time taken for the operation. The results are intended to be used as a baseline for comparing with SIMD-optimized versions using ARM NEON intrinsics.

## Features

- Command-line interface to set array size and iteration count.
- Aligned memory allocation for arrays to ensure efficient access.
- Element-wise addition using a loop unrolled 16 times.
- Timing of the addition operation.
- Verification of results by summing the elements of the result array.
