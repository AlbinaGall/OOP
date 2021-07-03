#include <iostream>
using namespace std;

class Fraction
{
	int integer; //Целая часть
	int numerator;
	int denomenator;
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denomenator()const
	{
		return denomenator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denomenator(int denomenator)
	{
		if (denomenator == 0) denomenator = 1; //Фильтрация данных
		this->denomenator = denomenator;
	}
	//Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denomenator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denomenator = 1;
		cout << "1argConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denomenator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->set_denomenator(denomenator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denomenator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denomenator(denomenator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denomenator = other.denomenator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}
	//				Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denomenator = other.denomenator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

		
	//				инкремент - декремент
	Fraction& operator++()		//префикс инкремент
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)	//постфикс(суффикс) инкремент
	{
		Fraction old = *this;	//Сохраняем старое значение
		integer++;
		return old;
	}

	//				Methods
	void to_improper()
	{
		numerator += integer * denomenator;
		integer = 0;
	}

	void to_proper()
	{
		integer += numerator / denomenator;
		numerator %= denomenator;
	}

	void Print() {
		if (integer) cout << integer;
		if (integer && numerator) cout << "(";
		if (numerator) cout << numerator << "/" << denomenator;
		if (integer && numerator) cout << ")";
		if (integer==0 && numerator==0) cout << 0;
		cout << endl;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	//через конструктор
	Fraction result(left.get_numerator() * right.get_numerator(),
					left.get_denomenator() * right.get_denomenator());
	/*через set-методы
	result.set_numerator(left.get_numerator() * right.get_numerator());
	result.set_denomenator(left.get_denomenator() * right.get_denomenator());*/
	//return result;

	//третий способ
	//через явный вызов конструктора, к-й создает безымянный об-т с нужным результатом
	return Fraction (
		left.get_numerator() * right.get_numerator(),
		left.get_denomenator() * right.get_denomenator());
}

int dva_plus_dva()
{
	return 2 + 2;
}

//#define CONSTRUCTORS_CHECK

void main() {
	setlocale(LC_ALL, "Russian");
#ifdef CONSTRUCTORS_CHECK
	Fraction A; //Default constructor
	A.Print();

	Fraction B=3;//Single argument constructor
	B.Print();

	Fraction C(3, 4);
	C.Print();

	Fraction D(2, 3, 4);
	D.Print();

	Fraction E = D; //CopyConstructor
	E.Print();

	Fraction F;		//DefaultConstructor
	F = E;			//CopyAssignment
	F.Print();
	cout << dva_plus_dva() << endl;
#endif CONSTRUCTORS_CHECK
	Fraction A(2, 3,4);
	/*A.Print();
	A.to_improper();
	A.Print();
	A.to_proper();
	A.Print();*/

	Fraction B(3, 4,5);
	/*b.print();
	b.to_improper();
	b.print();
	b.to_proper();
	b.print();*/

	Fraction C = A * B;
	C.Print();

	/*for (Fraction I(1,4); I.get_integer() < 10; ++I )
	{
		I.Print();		
	}*/
	for (Fraction I(1, 4); I.get_integer() < 10; I++)
	{
		I.Print();
	}
}