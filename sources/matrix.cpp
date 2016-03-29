#include "matrix.h"
#include <iostream>
using namespace std;


//Êîíñòðóêòîð ïî óìîë÷àíèþ
matrix::matrix() :rows(0), columns(0), _matrix(nullptr)
{

}



//êîíñòðóêòîð ñ ïàðàìåòðàìè êîë-âî ñòðîê, êîë-âî ñòîëáöîâ
matrix::matrix(int _rows, int _columns): rows(_rows), columns(_columns)
{
	create_memory();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) _matrix[i][j] = 0;
	};
}




//êîíñòðóêòîð ñëó÷àéíîé ìàòðèöû
matrix::matrix(int _rows, int _columns, int time) : rows(_rows), columns(_columns)
{
	create_memory();
	srand(time);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{

			_matrix[i][j] = rand() % 10;
		}
	};
}



//êîíñòðóêòîð (ãëóáîêîãî) êîïèðîâàíèÿ 
matrix::matrix(const matrix & matrix): rows(matrix.rows), columns(matrix.columns)
{
	create_memory();
	copy_matrix(matrix);
}



// Çàïîëåíèå ìàòðèöû èç ôàéëà 
void matrix::get_from_file(string name)
{
	string full_name;
	full_name = name;
	ifstream fin(full_name);
	if (fin.is_open()) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				fin >> _matrix[i][j];
		fin.close();
	}
	else {
		cout << "Îøèáêà, ïîïðîáóéòå åùå ðàç";
		exit(100);
	}
}



// äåñòðóêòîð
matrix::~matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] _matrix[i];

	delete[] _matrix;
}



// ïå÷àòü ìàòðèöû
void matrix::print_matrix() const
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << "   " << _matrix[i][j];
		};
		cout << "\n";
	};
}


void matrix::get_line(int k)
{
	int *row_matrix;  //óêàçàòåëü
	row_matrix = _matrix[k - 1];
	for (int i = 0; i < columns; i++)
		cout << " " << row_matrix[i];
}


// êîïèðîâàíèå ìàòðèöû
void matrix::copy_matrix(const matrix & matrix)
{
	for (int i = 0; i <rows; i++)
		for (int j = 0; j < columns; j++)
			_matrix[i][j] = matrix._matrix[i][j];
}



// ïåðåãðóçêà îïåðàòîðà = 
matrix & matrix::operator=(const matrix & matrix)
{
	copy_matrix(matrix);
	return *this;
}


// ïåðåäà÷à íîìåðà ñòðîêè, ñòîëáöà è çíà÷åíèÿ
void matrix::set(int row, int columns, int set)
{
	_matrix[row][columns] = set;
}


// âçÿòèå ýëåìåíòà 
int matrix::get(int row, int columns) const
{
	return _matrix[row][columns];
}



// ñóììà ïîñòðî÷íî
void matrix::get_sum_r(const matrix &matrix_1, const matrix &matrix_2, int i)
{
	for (int j = 0; j < get_num_cols(); j++)
		set(i, j, matrix_1.get(i, j) + matrix_2.get(i, j));
}



//ïåðåãðóçêà îïåðàòîðà + 
matrix operator+(const matrix &matrix_1, const matrix &matrix_2)
{
	matrix matrix(matrix_1.rows, matrix_1.columns);//ñîçäàåì íîâóþ ìàòðèöó 

	for (int i = 0; i < matrix.rows; i++)
		matrix.get_sum_r(matrix_1, matrix_2, i);
	return matrix;
};


//ïåðåãðóçêà îïåðàòîðà * 
matrix operator*(const matrix &matrix_1, const matrix &matrix_2) {
	matrix matrix(matrix_1.rows, matrix_1.columns);
	for (int i = 0; i < matrix.rows; i++)
		matrix.get_multi_r(matrix_1, matrix_2, i);
	return matrix;
};

// êîëè÷åñòâî ñòðîê
int matrix::get_num_rows() const
{
	return rows;
}


// Ïðîèçâåäåíèå
void matrix::get_multi_r(const matrix &matrix_1, const matrix &matrix_2, int i)
{
	int value = 0;
	for (int row = 0; row < matrix_1.rows; row++) {
		for (int col = 0; col < matrix_2.columns; col++) {
			for (int inner = 0; inner < matrix_2.rows; inner++) {
				value += matrix_1._matrix[row][inner] * matrix_2._matrix[inner][col];
			}
			set(row, col, value);
			value = 0;
		}
	}
};



//Êîëè÷åñòâî ñòîëáöîâ
int matrix::get_num_cols() const
{
	return columns;
}


// âûäåëÿåì ïàìÿòü
void matrix::create_memory()
{
	_matrix = new int*[rows];

	for (int i = 0; i < rows; i++)
		_matrix[i] = new int[columns];
}



// ïåðåãðóçêà îïåðàòîðà [] 
int* matrix::operator [] (int i) const
{
	int *Getline = new int[columns];// îäíîìåðíûé ìàññèâ äëÿ õðàíåíèÿ ñòîëáöîâ
	for (int j = 0; j < columns; j++)
		Getline[j] = _matrix[i - 1][j];
	return Getline;

}

bool matrix::operator== (const matrix &right) const// оператор сравнения
{
	if (rows != right.rows || columns != right.columns)
		return false; // матрицы с разным количеством элементов

	for (int ix = 0; ix < rows; ix++)
		for (int jx = 0; jx < columns; jx++)
			if (_matrix[ix][jx] != right._matrix[ix][jx])
				return false; // матрицы не равны

	return true; // матрицы равны
}
