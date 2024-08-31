#include <iostream>
#include <getopt.h>
#include <cstdlib>
#include <iomanip>
#include <cassert>
#include <arm_neon.h>
#include <vector>
#include <thread>
#include <sys/time.h>
#include <cstring>

using namespace std;



float NumberReturner(); 
void SingleCore(float * a, float * b, float * c, int m);
void initializePointerToZero(float * p, int size) ;
double SumOfSums(float * p, int size);
void Intrinsic(float * a, float * b, float * c, int r);


int main(int argc, char *argv[]) 
{
	using namespace std;

    srand(time(0));
    int g;        // the current option character
    int size = 128; // default value for size
    int iter = 1;   // default value for iteration
    double pickupthetotal = 0;

    // Loop through all the options
    while (( g = getopt(argc, argv, "hs:i:")) != -1) {
        switch (g) {
            case 'h':
                // Print help message and exit
                cout << "Help: " << argv[0] << " [-h] [-s size] [-i iter]\n";
                cerr << "  -h     display this help and exit\n";
                cerr << "  -s     set the size to the specified value (default is 128- will be made divisible by 16)\n";
                cerr << "  -i     set the iteration count to the specified value (default is 1)\n";
                exit(0);
            case 's':
                // Set the size to the specified value
                size = atoi(optarg);
                break;
            case 'i':
                // Set the iteration count to the specified value
                iter = atoi(optarg);
                break;
            case '?':
                // Handle unrecognized options
                cout << "Unknown option: " << char(optopt) << endl;
                exit(1);
        }
    }

    if(size % 16 != 0)
    {
        size = size + (16 - size % 16);  
    }
    
	float * a = (float *) aligned_alloc(16, size * sizeof(float));//fill this with random nunmber outcome 
	float * b = (float *) aligned_alloc(16, size * sizeof(float));//fill this with random number outcome 
	float * c = (float *) aligned_alloc(16, size * sizeof(float));//memset this pointer with 0 

    
    for(int i = 0; i < size; i++ )
    {
      *a = NumberReturner();//receiving a random number 
      *b = NumberReturner();//receiving a random number 
    }


    struct timeval start, end;
    gettimeofday(&start, NULL); // get start time

    for(int i = 0; i < iter; i++)
    {
      SingleCore(a,b,c,size);
      pickupthetotal = pickupthetotal + SumOfSums(c, size);
      initializePointerToZero(c, size);//memset c to 0
    }
   
    
    gettimeofday(&end, NULL); // get end time
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0; // in seconds
    
    // Do whatever I want to do with the options
    cout << "Array Size: " << size <<  " Total size of MB: 5" << endl;
    cout << "Iterations: " << iter << endl;
    cout << "Single core timings..." << endl;
    cout << "Naive: " << setprecision(6) << fixed <<time_taken << " Check: "<< pickupthetotal << endl;

    return 0;
}

/*
This function is retruning a random number inclusive from 0 to 1
*/
float NumberReturner()
{
    return (float)rand() / RAND_MAX;
}

/*
This function to initialize an array to zero using memset
*/ 
void initializePointerToZero(float * p, int size) 
{
    memset(p, 0, size * sizeof(float));
}

/*
This function is given in the spec for our SingleCore
*/
void SingleCore(float * a, float * b, float * c, int size)
{
	// Ensure compatibility with a 16-times unrolled loop.
	assert((size & 0xF) == 0);
	size = size / 16;

	for (int i = 0; i < size; i++) 
    {
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
		*(c++) = *(a++) + *(b++);
	}
   
}

/*
This function is adds up the first size floats at the given address and returns the sum. 
SumOfSums() will be used to validate your later variations of SingleCore()).
*/
double SumOfSums(float * p, int size)
{
    double sum = 0.0;//carrying the running sum of c everytime It get its in this function.
    for (int i = 0; i < size; i++)
    {  
        sum += *(p++);//the p will be holding the c value 
    }

    return sum;//returning the new sum 

}