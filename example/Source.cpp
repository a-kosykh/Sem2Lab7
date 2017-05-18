#include "testclass.hpp"
int main() {
	Matrix<int> res(2,2);
	ifstream("mat1.txt") >> res;
	cout << res;
	
	system("pause");
	return 0;
}