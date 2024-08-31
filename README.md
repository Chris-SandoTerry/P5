Vector Addition Performance Measurement
This project is designed to measure the performance of vector addition on a single-core ARM system. The program initializes two arrays with random numbers, performs element-wise addition of these arrays, and measures the time taken for the operation. The results are intended to be used as a baseline for comparing with SIMD-optimized versions using ARM NEON intrinsics.

Features
Command-line interface to set array size and iteration count.
Aligned memory allocation for arrays to ensure efficient access.
Element-wise addition using a loop unrolled 16 times.
Timing of the addition operation.
Verification of results by summing the elements of the result array.
Getting Started
Prerequisites
A C++ compiler with support for ARM NEON intrinsics.
getopt.h for command-line argument parsing.
Compilation
Compile the program using the following command:

sh
Copy code
g++ -o vector_addition main.cpp
Usage
Run the program with the following command:

sh
Copy code
./vector_addition [-h] [-s size] [-i iter]
-h: Display help message and exit.
-s size: Set the size of the arrays (default is 128; will be adjusted to be divisible by 16).
-i iter: Set the number of iterations (default is 1).
Example
sh
Copy code
./vector_addition -s 256 -i 10
Function Descriptions
main(int argc, char *argv[])
Parses command-line arguments.
Allocates memory for arrays a, b, and c.
Initializes arrays a and b with random numbers.
Measures the time taken for vector addition over the specified number of iterations.
Outputs the performance metrics.
float NumberReturner()
Generates a random float number between 0 and 1.
void initializePointerToZero(float *p, int size)
Sets all elements of the given array to zero using memset.
void SingleCore(float *a, float *b, float *c, int size)
Performs the addition of elements in arrays a and b and stores the result in array c.
The loop is unrolled 16 times for performance improvement.
double SumOfSums(float *p, int size)
Calculates and returns the sum of all elements in the given array p.
Future Enhancements
Implement the Intrinsic function using ARM NEON intrinsics for SIMD operations.
Compare the performance of the single-core implementation with the SIMD-optimized version.
Add more detailed performance metrics and potentially visualize the results.
Ensure proper error handling and memory management, especially for larger array sizes.
