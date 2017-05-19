#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

template<class T> class Matrix;
template<class T> ostream& operator<< (ostream& out, const Matrix<T>& mat);


template <typename T>
class Matrix {
private:
	unsigned int rows_;
	unsigned int columns_;
	T** Array_;

	Matrix<T> getFromFile_(string stringname);
public:
	Matrix() {
		rows_ = 0;
		columns_ = 0;
		Array_ = nullptr;
	}
	Matrix(unsigned int rows, unsigned int columns) {
		rows_ = rows;
		columns_ = columns;

		Array_ = new T* [rows];
		for (unsigned int i = 0; i < rows; ++i) {
			Array_[i] = new T[columns_];
			for (unsigned int j = 0; j < columns; ++j)
				Array_[i][j] = 0;
		}
	}
	
	Matrix(const Matrix& get) {
		rows_ = get.rows_;
		columns_ = get.columns_;
		Array_ = new T* [rows_];
		for (unsigned int i = 0; i < rows_; ++i) {
			Array_[i] = new T[columns_];
			for (unsigned int j = 0; j < columns_; ++j) {
				Array_[i][j] = get.Array_[i][j];
			}
		}
	}
	unsigned int getRows() {
		return rows_;
	}
	unsigned int getColumns() {
		return columns_;
	}
	T getElement(unsigned int i, unsigned j) {
		return Array_[i-1][j-1];
	}
	
	void setElement(unsigned int row, unsigned int column, T key) {
		Array_[row][column] = key;
	}
	
	Matrix<T> fillMatrix(string filename);
	
	Matrix<T> operator+ (const Matrix& mat) const {
		try {
			if ((rows_ == mat.rows_) && (columns_ == mat.columns_)) {
				Matrix getRes(rows_, columns_);
				for (unsigned int i = 0; i < rows_; ++i)
					for (unsigned int j = 0; j < columns_; ++j)
						getRes.Array_[i][j] = Array_[i][j] + mat.Array_[i][j];
				return getRes;
			}
			else {
				throw "Matrixes are not identical\nFirst matrix:\n";
			}
		}
		catch (char *msg) {
			cout << "Error: " << msg;
			return *this;
		}
		
	}
	Matrix<T> operator* (const Matrix& mat) const {
		try {
			if ((columns_ == mat.rows_)) {
				Matrix getRes(rows_, mat.columns_);
				for (unsigned int i = 0; i < rows_; ++i) {
					for (unsigned int j = 0; j < mat.columns_; ++j)
						for (unsigned int k = 0; k < columns_; ++k)
							getRes.Array_[i][j] += Array_[i][k] * mat.Array_[k][j];
				}
				return getRes;
			}
			else {
				throw "!These matrixes can't be multiplied!\nFirst matrix:\n";
			}
		}
		catch (char *msg) {
			cout << "Error" << msg;
			return *this;
		}
	}
	Matrix<T>& operator= (const Matrix& right) {
		if (this == &right) {
			return *this;
		}
		for (unsigned int i = 0; i < rows_; ++i) {
			delete[]Array_[i];
		}
		delete[]Array_;
		Array_ = new T*[right.rows_];
		for (unsigned int i = 0; i < right.rows_; ++i) {
			Array_[i] = new T[right.columns_];
			for (unsigned int j = 0; j < right.columns_; ++j)
				Array_[i][j] = right.Array_[i][j];
		}
		rows_ = right.rows_;
		columns_ = right.rows_;
		return *this;
	}
	bool operator== (const Matrix& right) const {
		if ((rows_ == right.rows_) && (columns_ == right.columns_)) {
			for (unsigned int i = 0; i < rows_; ++i)
				for (unsigned int j = 0; j < columns_; ++j) {
					if (Array_[i][j] != right.Array_[i][j]) { return false; }
				}
		}
		else return false;
	}
	
	template <typename K> friend ostream& operator << (ostream& out, const Matrix<K>& mat);
	template <typename U> friend istream& operator >> (istream& in, Matrix<U>& mat);
	
	void print(ostream&) {
		cout << "**************\n";
		cout << "Rows: " << rows_ << endl;
		cout << "Columns: " << columns_ << endl;
		cout << "--------------\n";
		for (unsigned int i = 0; i < rows_; ++i) {
			for (unsigned int j = 0; j < columns_; ++j)
				cout << Array_[i][j] << " ";
			cout << endl;
		}
		cout << "**************\n";
	}
	~Matrix() {
		for (unsigned int i = 0; i < rows_; ++i) {
			delete[]Array_[i];
		}
		delete[]Array_;
	}
};

template<typename T>
Matrix<T> Matrix<T>::getFromFile_(string filename)
{
	ifstream in(filename);
	try {
		if (in) {
			for (unsigned int i = 0; i < rows_; ++i)
				for (unsigned int j = 0; j < columns_; ++j)
					in >> Array_[i][j];
			return *this;
		}
		else throw "Can't open file\n";
	}
	catch (char *msg) {
		cout << "Error: " << msg;
		return *this;
	}
}

template<typename T>
Matrix<T> Matrix<T>::fillMatrix(string filename)
{
	return getFromFile_(filename);
}

template <typename T>
istream & operator >> (istream & in, Matrix<T>& mat)
{
	try {
		if (in) {
			for (unsigned int i = 0; i < mat.rows_; ++i)
				for (unsigned int j = 0; j < mat.columns_; ++j)
					in >> mat.Array_[i][j];
			return in;
		}
		else throw "Can't open file\n";
	}
	catch (char* msg) {
		cout << "Error: " << msg;
		return in;
	}
}

template<class T>
ostream& operator<< (ostream& out, const Matrix<T>& mat) {
	out << "**************\n";
	out << "Rows: " << mat.rows_ << endl;
	out << "Columns: " << mat.columns_ << endl;
	out << "--------------\n";
	for (unsigned int i = 0; i < mat.rows_; ++i) {
		for (unsigned int j = 0; j < mat.columns_; ++j)
			out << mat.Array_[i][j] << " ";
		out << endl;
	}
	out << "**************\n";
	return out;
}