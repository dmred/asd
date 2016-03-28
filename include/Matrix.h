#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


class matrix
{
public:
	matrix();
	matrix(int _cols, int _rows);
	matrix(const matrix &Matrix);
	matrix(int _rows, int _columns, int time);
	~matrix();
	void get_line(int k);
	void get_from_file(string _name);
	void print_matrix() const;
	void copy_matrix(const matrix &Matrix);
	matrix &operator=(const matrix &Matrix);
	friend matrix operator+(const matrix &matrix_1, const matrix &matrix_2);
	friend matrix operator*(const matrix &matrix_1, const matrix &matrix_2);
	int *operator[] (int i) const;
	void get_sum_r(const matrix &matrix_1, const matrix &matrix_2, int s);
	void get_multi_r(const matrix &matrix_1, const matrix &matrix_2, int m);
	void create_memory();
	int get_num_rows() const;
	int get_num_cols() const;
	int get(int rows, int columns) const;
	void set(int row, int columns, int set);


	int rows;
	int columns;
	int **_matrix;
};




