#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstddef>
#include <cassert>
#include <limits>

void Square_Matrix_Generator(std::ofstream& fout, std::size_t matrix_number, std::size_t matrix_dimension)
{
	std::srand(std::time(0));
	assert(matrix_number > 0 && matrix_number < std::numeric_limits<std::size_t>::max() && "invalid matrix dimension");
	assert(matrix_dimension > 0 && matrix_dimension < std::numeric_limits<std::size_t>::max() && "invalid matrix dimension");
	assert(fout.good() && "unable to write '#' to file");
	fout << '#';
	assert(fout.good() && "unable to write matrix number to file");
	fout << matrix_number << '\n';
	assert(fout.good() && "unable to write matrix dimension to file");
	fout << matrix_dimension << 'x' << matrix_dimension << "\n";	
	for(std::size_t i = 0; i < matrix_dimension; ++i) {
		for(std::size_t j = 0; j < matrix_dimension; ++j) {
			assert(fout.good() && "unable to write to file");
			fout << std::setw(3) << rand() % 198 -99 << ", ";
		}
		assert(fout.good() && "unable to write to file");
		fout << std::endl;
	}
	assert(fout.good() && "unable to write to file");
	fout << std::endl;
}


int main()
{
	std::ofstream fo1("Data/a.txt"), fo2("Data/b.txt");
	std::size_t matrix_number = 1;
	do {
		char key;
		std::cout << "To generate the quare matrix in the a.txt and b.txt files, enter 1, otherwise enter any key except 1: ";
		std::cin >> key;
		if(key != '1') {
			break;
		}
		std::size_t matrix_dimension;
		std::cout << "Enter matrix dimension: ";
		std::cin >> matrix_dimension;
		Square_Matrix_Generator(fo1, matrix_number, matrix_dimension);
		Square_Matrix_Generator(fo2, matrix_number, matrix_dimension);
		++matrix_number;
	}while(1);
	fo1.close();
	fo2.close();
	return 0;
}



