#include <matrix.h>
#include <catch.hpp>
#include <fstream>

SCENARIO("Matrix init", "[init]") {

	GIVEN("The number of rows and columns") {

		auto rows = 3;
		auto columns = 3;

		WHEN("Create instansce of Matrix") {

			matrix matrix(rows, columns);
			THEN("The number of rows and columns must be preserved") {

				REQUIRE(matrix.get_num_rows() == rows);
				REQUIRE(matrix.get_num_cols() == columns);
			}
		}
	}
}

SCENARIO("Matrix +", "[addition]") {
	matrix A = matrix(3, 3);
	A.get_from_file("A3x3.txt");
	matrix B = matrix(3, 3);
	B.get_from_file("B3x3.txt");
	matrix expected = matrix(3, 3);
	expected.get_from_file("A+B.txt");
	matrix result = A + B;
	bool f=true;
	for (int i = 1; i < 3; ++i) {
		for (int j = 1; j < 3; ++j) {
			if (result[i][j] != expected[i][j]) {
				f= false;
			}
		}
	}
	REQUIRE(f == true);
}
