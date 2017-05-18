#include <testclass.hpp>
#include <catch.hpp>

SCENARIO ("constructorTest"){
	Matrix<int> mat(3,3);
	unsigned int rows;
	unsigned int cls;
	rows =	mat.getRows();
	cls = mat.getColumns();
	REQUIRE (rows == cls);
}

