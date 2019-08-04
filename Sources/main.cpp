#include <utility.hpp>

#include <iostream>
#include <fstream>
#include <cstddef>
#include <cassert>
#include <limits>
#include <cstdlib>
#include <ctime>    //"CPU time used: "
//#include <chrono> //"Wall clock time passed: "
		//auto start = std::chrono::high_resolution_clock::now();
		//auto end = std::chrono::high_resolution_clock::now();
		//std::chrono::duration<float> duration = end - start;
		//fta << duration.count() / duration_t.count();

int main()
{
	std::ifstream fa("Data/a.txt"), fb("Data/b.txt");
	std::ofstream fr("Data/result.txt"), fta("Data/timeAnalysis.txt");
	Matrix a, b, r;
	char sa, sb;
	while(fa >> sa && fb >> sb) {
       		assert(sa == '#' && "reading '#' character failed");
       		assert(sb == '#' && "reading '#' character failed");
                std::size_t number = std::numeric_limits<std::size_t>::max();
                bool bv = matrixNumberComparator(fa, fb, number);
	        assert(bv && "incompatible numbers");	
	        assert(number < std::numeric_limits<std::size_t>::max() && "matrix number value is not valid");	
		readMatrix(a, fa);
	        assert(a.getRows() > 0 && a.getRows() < std::numeric_limits<std::size_t>::max() && "matrix row value is not valid");	
	        assert(a.getColumns() > 0 && a.getColumns() < std::numeric_limits<std::size_t>::max() && "matrix column value is not valid");	
	        readMatrix(b, fb);
	        assert(b.getRows() > 0 && b.getRows() < std::numeric_limits<std::size_t>::max() && "matrix row value is not valid");	
	        assert(b.getColumns() > 0 && b.getColumns() < std::numeric_limits<std::size_t>::max() && "matrix column value is not valid");	
		r.initialize(a.getRows(), a.getColumns());
		std::clock_t c_start = std::clock();
		multMatrix(a, b, r);
		std::clock_t c_end = std::clock();  
		//To convert result value to seconds divide it by CLOCKS_PER_SEC.
		//clock (function) returns raw processor clock time since the program is start.
		//CLOCKS_PER_SEC(macro constant) number of processor clock ticks per second
		float duration = float(c_end-c_start) / CLOCKS_PER_SEC;
		writeStatistics(duration, a.getRows(), a.getColumns(), b.getColumns(), "standart multiplication", fta);
		writeMatrix(number, r, fr);
		c_start = std::clock();
		multMatrixTranspose(a, b, r);
		c_end = std::clock();  
		float duration_t = float(c_end-c_start) / CLOCKS_PER_SEC;
		writeStatistics(duration_t, a.getRows(), a.getColumns(), b.getRows(), "transposed multiplication", fta);
		writeMatrix(number, r, fr);
		assert(fta.good() && "unable to write to file");
		fta << "\ntransposed multiplication is ";
		assert(fta.good() && "unable to write to file");
		fta << duration / duration_t;
		assert(fta.good() && "unable to write to file");
		fta << " times faster\n___________________________________________________ ";
		
	}
	fa.close();
	fb.close();
	fr.close();
	fta.close();
	return 0;
}
