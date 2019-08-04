#include <utility.hpp>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstddef>
#include <cassert>
#include <limits>
#include <cstdlib>

Matrix::Matrix() : mRows(0), mColumns(0), mData(nullptr)
{
}

Matrix::~Matrix()
{
	delete[] mData;
	mData = nullptr;
}

void Matrix::initialize(const std::size_t r, const std::size_t c)
{
	assert(r > 0 && r < std::numeric_limits<std::size_t>::max() && "value is not valid");
	assert(c > 0 && c < std::numeric_limits<std::size_t>::max() && "value is not valid");
	assert((std::numeric_limits<std::size_t>::max() / r) > c && "value is not valid");
	mRows = r;
	mColumns = c;
	delete[] mData;
	mData = new dataType[r * c];
}

void Matrix::setData(const std::size_t i, const std::size_t j, const dataType& d)
{
	assert(i < mRows && "out of range");
	assert(j < mColumns && "out of range");
	assert(d < std::numeric_limits<dataType>::max() && "range maximum value");
	const std::size_t index = i * mColumns + j;
	assert(index < mRows * mColumns && "out of range");
	mData[index] = d;
}

dataType Matrix::getData(const std::size_t i, const std::size_t j) const
{
	assert(i < mRows && "out of range"); 
	assert(j < mColumns && "out of range"); 
	const std::size_t index = i * mColumns + j;
	assert(index < mRows*mColumns && "out of range");
	return mData[index];
}

std::size_t Matrix::getRows() const
{
	assert(mRows > 0 && "object is not initialized");
	return mRows;
}

std::size_t Matrix::getColumns() const
{
	assert(mColumns > 0 && "object is not initialized");
	return mColumns;
}

//It is assumed that the file provided is correct, which means that the matrices in file are complete full and
//there is no missing data or incorrect data. Else we need to check additional condition in if operator.
std::size_t readMatrixNumber(std::ifstream& fi)
{
	assert(fi.good() && "unable to read from file");
	std::size_t n = std::numeric_limits<std::size_t>::max();
	fi >> n;
	assert( n > 0 && n < std::numeric_limits<std::size_t>::max() && "matrix number value is not valid");
	return n;
}

bool matrixNumberComparator(std::ifstream& fa, std::ifstream& fb, std::size_t& number_out)
{
	number_out = std::numeric_limits<std::size_t>::max();
	number_out = readMatrixNumber(fa);
	assert(number_out > 0 && number_out < std::numeric_limits<std::size_t>::max() && "matrix number value is not valid");
	if(number_out != readMatrixNumber(fb)) {
		return false;
	}
	return true;
}

void readMatrix(Matrix& m, std::ifstream& fi)	
{
	assert(fi.good() && "unable to read from file");
	std::size_t r = std::numeric_limits<std::size_t>::max();
	fi >> r;
	assert( r > 0 && r < std::numeric_limits<std::size_t>::max() && "matrix row value is not valid");
	assert(fi.good() && "unable to read from file");
	char s;
	fi >> s;
	assert(s == 'x' && "reading 'x' character failed");
	assert(fi.good() && "unable to read from file");
	std::size_t c = std::numeric_limits<std::size_t>::max();
	fi >> c;
	assert(c > 0 && c < std::numeric_limits<std::size_t>::max() && "matrix column value is not valid");
	m.initialize(r, c);
	for(std::size_t i = 0; i < r; ++i) {
		for(std::size_t j = 0; j < c; ++j) {
			assert(fi.good() && "unable to read from file");
			dataType d = std::numeric_limits<dataType>::max();
			fi >> d;
			assert(d < std::numeric_limits<dataType>::max() && "matrix data value is not valid");
			fi >> s;
			assert(s == ',' && "reading 'x' character failed");
			m.setData(i, j, d);
		}
	}
	assert(fi.good() && "unable to read from file");
}

void writeMatrix(std::size_t number, const Matrix& m, std::ofstream& fo)
{
	assert(fo.good() && "unable to write '#' to file");
	fo << '#';
	assert(fo.good() && "unable to write matrix number to file");
	assert(number < std::numeric_limits<std::size_t>::max() && "invalid matrix number");
	fo << number << '\n';
	assert(fo.good() && "unable to write matrix rows number to file");
	fo << m.getRows() << 'x';
	assert(fo.good() && "unable to write matrix columns number to file");
	fo << m.getColumns() << '\n';
	for(std::size_t i = 0; i < m.getRows(); ++i) {
                for(std::size_t j = 0; j < m.getColumns(); ++j) {
                        assert(fo.good() && "unable to write to file");
			fo << std::setw(7) << m.getData(i, j) << ", ";
                }
                assert(fo.good() && "unable to write to file");
                fo << std::endl;
        }
	assert(fo.good() && "unable to write to file");
        fo << std::endl;
}

void writeStatistics(float duration, std::size_t row, std::size_t col,
                     std::size_t col_2, const char* message, std::ofstream& fo) {
	assert(fo.good() && "unable to write to file");
	assert(row > 0 && row < std::numeric_limits<std::size_t>::max() && "invalid value");
	assert(col > 0 && col < std::numeric_limits<std::size_t>::max() && "invalid value");
	assert(col_2 > 0 && col_2 < std::numeric_limits<std::size_t>::max() && "invalid value");
	fo << "\nOperation type : ";
	assert(fo.good() && "unable to write to file");
	fo << message;
	assert(fo.good() && "unable to write to file");
	fo << "\nmatrix sizes: ";
	assert(fo.good() && "unable to write to file");
	fo << row << "x" << col << ", ";
	assert(fo.good() && "unable to write to file");
	fo << col << "x" << col_2;
	assert(fo.good() && "unable to write to file");
	fo << "\nOperation duration: ";
	assert(fo.good() && "unable to write to file");
	fo << duration <<" seconds\n";
}


void multMatrix(const Matrix& a, const Matrix& b, Matrix& t)
{
	std::size_t a_r = a.getRows();
	std::size_t a_c = a.getColumns();
	std::size_t b_r = b.getRows();
	std::size_t b_c = b.getColumns();
	assert(a_c == b_r && "incompatible matrices for multiplication");
	assert(a_r == t.getRows() && "incompatible matrices dimension");
	assert(b_c == t.getColumns() && "incompatible matrices dimension");
	for(std::size_t i = 0; i < a_r; ++i) {
                for(std::size_t j = 0; j < b_c; ++j) {
			dataType s = 0; 
			for(std::size_t k = 0; k < a_c; ++k) {
				dataType v1 = a.getData(i, k);
				dataType v2 = b.getData(k, j);
				assert(v1 == 0 || (std::abs(v2) < std::numeric_limits<dataType>::max() / std::abs(v1)) && "overflow on multiplication");
				dataType m = v1 * v2;
				assert((s >= 0 && m < std::numeric_limits<dataType>::max() - s) ||
		                       (s < 0 && std::numeric_limits<dataType>::min() - s < m));
				s += m;
			}
			t.setData(i, j, s);
		}
	}
}

void transposeMatrix(const Matrix& m, Matrix& mt)
{
	std::size_t r = mt.getRows();
	std::size_t c = mt.getColumns();
	assert(m.getRows() == c && "incompatible matrices for transpose");
	assert(m.getColumns() == r && "incompatible matrices for transpose");
	for(std::size_t i = 0; i < r; ++i) {
		for(std::size_t j = 0; j < c; ++j) {
			mt.setData(i, j, m.getData(j, i));
		}
	}

}

void multMatrixTranspose(const Matrix& a, const Matrix& b, Matrix& t)
{
	std::size_t a_r = a.getRows();
	std::size_t a_c = a.getColumns();
	Matrix bt;
	bt.initialize(b.getColumns(), b.getRows());
	std::size_t bt_r = bt.getRows();
	std::size_t bt_c = bt.getColumns();
	transposeMatrix(b, bt);
	assert(b.getData(0, b.getColumns() - 1) == bt.getData(b.getColumns() - 1, 0) && "wrong transpose");
	assert(a_c == bt_c && "incompatible matrices for transpose multiplication");
	assert(a_r == t.getRows() && "incompatible matrices dimension");
	assert(bt_r == t.getColumns() && "incompatible matrices dimension");
	for(std::size_t i = 0; i < a_r; ++i) {
                for(std::size_t j = 0; j < bt_r; ++j) {
			dataType s = 0; 
			for(std::size_t k = 0; k < a_c; ++k) {
				dataType v1 = a.getData(i, k);
				dataType v2 = bt.getData(j, k);
				assert(v1 == 0 || (std::abs(v2) < std::numeric_limits<dataType>::max() / std::abs(v1)) && "overflow on multiplication");
				dataType m = v1 * v2;
				assert((s >= 0 && m < std::numeric_limits<dataType>::max() - s) ||
		                       (s < 0 && std::numeric_limits<dataType>::min() - s < m));
				s += m;
			}
			t.setData(i, j, s);
		}
	}
}
