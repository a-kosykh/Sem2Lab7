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
SCENARIO("addTest"){
	Matrix<int> mat3(3,3);
	std::ifstream("mat3");
	
	Matrix<int> mat4(3,3);
	std::ifstream ("mat4") >> mat4;
	
	Matrix<int> matRes(3,3);
	std::ifstream("addRes") >> matRes;
	
	REQUIRE ((mat3 + mat4) == matRes);
}
