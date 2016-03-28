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

SCENARIO("Matrix: operator +", "[addition]") {
	matrix A(rows, columns);
	matrix B(rows, columns);
	matrix expected(rows, columns);
	matrix result(rows, columns);
	A.get_from_file("A3x3.txt");
	B.get_from_file("B3x3.txt");
	expected.get_from_file("A+B.txt");
	result = A + B;
	REQUIRE(result == expected);
}
