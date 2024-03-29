#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

template<typename T>
class Matrix{
public:
	// Конструктор
	Matrix(int m, int n) :elem{new T[m*n]}, numRows{m}, numColumns{n} { }

	// Конструктор с копированием
	Matrix(const Matrix<T>& other) :elem{new T[other.numRows*other.numColumns]}, numRows{other.numRows}, numColumns{other.numColumns} {
		for (int i = 0; i!=numRows; ++i)
			for (int j = 0; j!=numColumns; ++j)
				(*this)(i,j) = other(i,j);

	}

	// Считывание
	void scan() {
		for (int i = 0; i!=numRows; ++i)
			for (int j = 0; j!=numColumns; ++j) {
				cout  << "(" << i << ", " << j << ")=";
				cin >> elem[i*numColumns + j];
			}
	}

	// Вывод
	void print() {
		for (int i = 0; i!=numRows; ++i) {
			for (int j = 0; j!=numColumns; ++j)
				cout << elem[i*numColumns + j] << '\t';
			cout << endl;
		}
	}

	// Доступ к элементам по индексам
	T& operator()(int m, int n) { return elem[m*numColumns + n]; }
	T operator()(int m, int n) const { return elem[m*numColumns + n]; }// Выполняется в случае, если элементы вызванной матрицы нельзя менять

	// Копирование
	Matrix& operator=(const Matrix& other) {
		if (elem==other.elem) return *this;

		if ( (numRows!=other.numRows)||(numColumns!=other.numColumns) )
			throw invalid_argument("Копирование не выполнено: матрицы разных размеров!");

		for (int i = 0; i!=numRows; ++i)
			for (int j = 0; j!=numColumns; ++j)
				(*this)(i,j) = other(i,j);

		return *this;
	}

	// Сложение
	Matrix& operator+(const Matrix& other) {
		if (elem==other.elem) return *this;

		if ( (numRows!=other.numRows)||(numColumns!=other.numColumns) )
			throw invalid_argument("Сложение не выполнено: матрицы разных размеров!");
		
		for (int i = 0; i!=numRows; ++i)
			for (int j = 0; j!=numColumns; ++j)
				(*this)(i,j) += other(i,j);

		return *this;
	}

	// Вычитание
	Matrix& operator-(const Matrix& other) {
		if (elem==other.elem) return *this;

		if ( (numRows!=other.numRows)||(numColumns!=other.numColumns) )
			throw invalid_argument("Вычитание не выполнено: матрицы разных размеров!");

		for (int i = 0; i!=numRows; ++i)
			for (int j = 0; j!=numColumns; ++j)
				(*this)(i,j) -= other(i,j);

		return *this;
	}

private:
	unique_ptr<T[]> elem;	// "Умный" указатель на элементы
	int numRows;		// Число строк матрицы
	int numColumns;		// Число столбцов матрицы
};

int main() {
	int numRows, numColumns;

	cout << "iMatr:" << endl << "Число строк матрицы:\t";
	cin >> numRows;
	cout << "Число столбцов матрицы:\t";
	cin >> numColumns;
	Matrix<int> iMatr(numRows, numColumns);
	iMatr.scan();
	iMatr.print();

	/*
	cout << "iMatr(0,0)=" << iMatr(0,0) << endl;
	iMatr(0,0) = iMatr(0,1);
	cout << "iMatr(0,0)=" << iMatr(0,0) << endl;
	*/

	//iMatr = iMatr;

	cout << "iMatr2:" << endl << "Число строк матрицы:\t";
	cin >> numRows;
	cout << "Число столбцов матрицы:\t";
	cin >> numColumns;
	Matrix<int> iMatr2(numRows,numColumns);
	iMatr2.scan();
	iMatr2.print();

	iMatr = iMatr - iMatr2;
	iMatr.print();

	/*
	cout << "iMatr3:" << endl << "Число строк матрицы:\t";
	cin >> numRows;
	cout << "Число столбцов матрицы:\t";
	cin >> numColumns;
	Matrix<int> iMatr3(numRows, numColumns);
	*/

	/*
	try { iMatr3 = iMatr2 + iMatr; }
	catch (invalid_argument e) {
		cout << "Error!" << endl;
		cout << e.what() << endl;

		return 0;
	}
	*/

	//cout << "iMatr3:" << endl;
	//iMatr3.print();

	return 0;
}
