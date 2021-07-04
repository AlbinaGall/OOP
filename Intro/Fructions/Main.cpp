#include <iostream>
using namespace std;

class Fraction
{
	int integer; //целая часть
	int numerator;
	int denominator;
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0) denominator = 1; //фильтрация данных
		this->denominator = denominator;
	}
	//constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "defaultconstructor:\t" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1argconstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		cout << "constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}
	//				operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
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
		Fraction old = *this;	//сохраняем старое значение
		integer++;
		return old;
	}
	Fraction& operator--()		//префикс декремент
	{
		integer--;
		return *this;
	}
	Fraction operator--(int)	//постфикс(суффикс) декремент
	{
		Fraction old = *this;	//сохраняем старое значение
		integer--;
		return old;
	}

//				methods
	void to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
	}

	void to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
	}
	
	void print() {
		if (integer) cout << integer;
		if (integer && numerator) cout << "(";
		if (numerator) cout << numerator << "/" << denominator;
		if (integer && numerator) cout << ")";
		if (integer==0 && numerator==0) cout << 0;
		cout << endl;
	}

};

//			общий знаменатель
int commondenominator(Fraction left, Fraction right) {
	return left.get_denominator() * right.get_denominator();
} 
//			 arithmetical operators: +, -, *, /;

Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	int  commonnumerator;
	commonnumerator = left.get_numerator() * right.get_denominator() +
					  right.get_numerator() * left.get_denominator(); //общий числитель
	
	Fraction result(commonnumerator, commondenominator(left, right));
	result.to_proper();
	return result;
}

Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	int  commonnumerator;
	if (left.get_numerator() < right.get_numerator()) {
		commonnumerator = right.get_numerator() * left.get_denominator() -
			left.get_numerator() * right.get_denominator();
	}
	else {
		commonnumerator = left.get_numerator() * right.get_denominator() -
						  right.get_numerator() * left.get_denominator();
	}
	
	Fraction result(commonnumerator, commondenominator(left,right));
	result.to_proper();
	return result;
}

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	//через конструктор
	/*Fraction result(left.get_numerator() * right.get_numerator(),
					left.get_denominator() * right.get_denominator());*/
	/*через set-методы
	result.set_numerator(left.get_numerator() * right.get_numerator());
	result.set_denominator(left.get_denominator() * right.get_denominator());*/
	//return result;

	//третий способ
	//через явный вызов конструктора, к-й создает безымянный об-т с нужным результатом
	return Fraction (
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator());
}

Fraction operator/(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	
	Fraction result;
	result.set_numerator(left.get_numerator() * right.get_denominator());
	result.set_denominator(right.get_numerator() * left.get_denominator());

	result.to_proper();
	return result;
}//			 arithmetical operators: +, -, *, /;

//			comparison operators : == , != , > , < , >= , <=
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	if (left.get_numerator() == right.get_numerator() &&
		left.get_denominator() == right.get_denominator()) {
		return true;
	}
	else {
		return false;
	}
}
bool operator!=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	if (left.get_numerator() != right.get_numerator() &&
		left.get_denominator() != right.get_denominator()) {
		return true;
	}
	else {
		return false;
	}
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	
	if (left.get_numerator() * right.get_denominator() < 
		left.get_denominator()*right.get_numerator()) {
		return true;
	}
	else {
		return false;
	}
	
}
bool operator<=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	if (left.get_numerator() * right.get_denominator() <=
		left.get_denominator() * right.get_numerator()) {
		return true;
	}
	else {
		return false;
	}

}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	if (left.get_numerator() * right.get_denominator() >
		left.get_denominator() * right.get_numerator()) {
		return true;
	}
	else {
		return false;
	}

}
bool operator>=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	if (left.get_numerator() * right.get_denominator() >
		left.get_denominator() * right.get_numerator()) {
		return true;
	}
	else {
		return false;
	}

}//			 comparison operators : == , != , > , < , >= , <=


int dva_plus_dva()
{
	return 2 + 2;
}

//#define CONSTRUCTORS_CHECK

void main() {
	setlocale(LC_ALL, "Russian");
#ifdef CONSTRUCTORS_CHECK
	Fraction A; //default constructor
	A.print();

	Fraction B = 3;//single argument constructor
	B.print();

	Fraction C(3, 4);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D; //copyconstructor
	E.print();

	Fraction F;		//defaultconstructor
	F = E;			//copyassignment
	F.print();
	cout << dva_plus_dva() << endl;
#endif CONSTRUCTORS_CHECK

	Fraction A(2, 3, 4);
	/*A.print();
	A.to_improper();
	A.print();
	A.to_proper();
	A.print();*/

	Fraction B(3, 4, 5);
	/*B.print();
	B.to_improper();
	B.print();
	B.to_proper();
	B.print();*/

	Fraction C = A * B;
	C.print();


	/*префикс инкремент
	for (Fraction I(1,4); I.get_integer() < 10; ++I )
	{
		I.print();
	}*/
	/*постфикс инкремент
	for (Fraction I(1, 4); I.get_integer() < 10; I++)
	{
		I.print();
	}*/

	cout << "префикс декремент: " << endl;
	for (Fraction I(2, 1, 4); I.get_integer() != 0; --I)
	{
		I.print();
	}
	cout << endl;
	cout << "постфикс декремент: " << endl;
	for (Fraction I(2, 1, 4); I.get_integer() != 0; I--)
	{
		I.print();
	}
	cout << endl;

	Fraction D = A + B;
	cout << "Сложение: "; D.print();

	Fraction E = A - B;
	cout << "Вычитание: "; E.print();

	Fraction F = A / B;
	cout << "Деление: "; F.print();

	Fraction X(1, 1, 4), Y(5, 4);
	A.to_improper(), B.to_improper();
	X.to_improper(), Y.to_improper();

	if (A > B) {
		cout << "A > B" << endl;
	}else { cout << "B > A" << endl; }

	if (A < B) {
		cout << "A < B" << endl;
	}else { cout << "B < A" << endl; }

	if (X >= Y) {
		cout << "X >= Y" << endl;
	}else { cout << "Y >= X" << endl; }

	if (X <= Y) {
		cout << "X <= Y" << endl;
	}else { cout << "Y <= X" << endl; }

	if (A == B) {
		cout << "A == B" << endl;
	}else { cout << "A != B" << endl; }

	if (X != Y){
		cout << "X != Y" << endl;
	}else { cout << "X == Y" << endl; }	

}