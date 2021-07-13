#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Fraction;//Объявление класса (Class declaration)
Fraction operator*(Fraction left, Fraction right);//прототип ф-ии

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
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1argconstructor:\t" << this << endl;
	}
	Fraction(double decimal)
	{
		integer = decimal;
		decimal -= integer;
		denominator = 1e+9;
		numerator= decimal * denominator;
		reduce();
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

	Fraction& operator *=(const Fraction& other)
	{
		return *this= *this*other;

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

	//		Type-cast operators
	explicit operator int()const
	{
		return integer;
	}
	explicit operator double()const
	{
		return integer + (double)numerator / denominator;
	}

//				methods
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}

	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	Fraction inverted()//Обращает дробь - меняет местами числитель и знаменатель
	{
		/*to_improper();
		int buf = numerator;
		numerator = denominator;
		denominator = buf;
		return *this;*/
		to_improper();
		return Fraction(denominator, numerator);

	}

	//сокращение дроби
	Fraction& reduce() //сокращение дроби по алгоритму Евклида
	{
		//             my code
		/* this->to_improper();
		if (numerator > denominator) {
			int NOD = numerator % denominator;
			int buf;
			while (NOD != 0){
				buf = NOD;
				NOD = denominator % NOD;
			}
			this->set_numerator(numerator / buf);
			this->set_denominator(denominator / buf);
		}
		else {
			int NOD = denominator % numerator;
			int buf;
			while (NOD != 0){
				buf = NOD;
				NOD = numerator % NOD;
			}
			
			this->set_numerator(numerator / buf);
			this->set_denominator(denominator / buf);
		}
		return *this;*/
		int more, less, rest;
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}else{
			more = denominator;
			less = numerator;
		}
		do {
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GSD = more; //наибольший общий делитель
		numerator /= GSD;
		denominator /= GSD;
		return *this;
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
	/*int  commonnumerator;
	commonnumerator = left.get_numerator() * right.get_denominator() +
					  right.get_numerator() * left.get_denominator(); //общий числитель
	
	Fraction result(commonnumerator, commondenominator(left, right));
	result.to_proper();
	return result;*/
	return Fraction(
		left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
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
	/*left.to_improper();
	right.to_improper();
	
	Fraction result;
	result.set_numerator(left.get_numerator() * right.get_denominator());
	result.set_denominator(right.get_numerator() * left.get_denominator());

	result.to_proper();
	return result;*/
	return left * right.inverted();
}
//			 arithmetical operators: +, -, *, /;

//			 comparison operators : == , != , > , < , >= , <=
bool operator==(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();

	if (left.get_numerator() == right.get_numerator() &&
		left.get_denominator() == right.get_denominator()) {
		return true;
	}
	else {
		return false;
	}*/
	//left.to_improper();
	//right.to_improper();
	/*if (left.get_numerator() * right.get_denominator() == left.get_denominator() * right.get_numerator())
		return true;
	else 
		return false;*/
	//return left.get_numerator() * right.get_denominator() == left.get_denominator() * right.get_numerator();
	return  (double)left == (double) right;
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	//left.to_improper();
	//right.to_improper();

	/*if (left.get_numerator() != right.get_numerator() &&
		left.get_denominator() != right.get_denominator()) {
		return true;
	}
	else {
		return false;
	}*/
	//return left.get_numerator() * right.get_denominator() != left.get_denominator() * right.get_numerator();
	return !(left == right);
}

bool operator<(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();
	
	if (left.get_numerator() * right.get_denominator() < 
		left.get_denominator()*right.get_numerator()) {
		return true;
	}
	else {
		return false;
	}*/
	return (double)left < (double)right;
	
}

bool operator<=(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();

	if (left.get_numerator() * right.get_denominator() <=
		left.get_denominator() * right.get_numerator()) {
		return true;
	}
	else {
		return false;
	}*/
	return left < right || left == right;
	//return !(left > right);

}
bool operator>(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();

	if (left.get_numerator() * right.get_denominator() >
		left.get_denominator() * right.get_numerator()) {
		return true;
	}
	else {
		return false;
	}*/
	return (double)left > (double)right;

}
bool operator>=(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();

	if (left.get_numerator() * right.get_denominator() >
		left.get_denominator() * right.get_numerator()) {
		return true;
	}
	else {
		return false;
	}*/
	//return left > right || left == right;
	return !(left < right);

}
//			 comparison operators : == , != , > , < , >= , <=


ostream& operator<<(ostream& os, const Fraction& obj) {
	if (obj.get_integer()) os << obj.get_integer();
	if (obj.get_integer() && obj.get_numerator()) os << "(";
	if (obj.get_numerator()) os << obj.get_numerator() << "/" << obj.get_denominator();
	if (obj.get_integer() && obj.get_numerator()) os << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0) os << 0;
	return os;
}

istream& operator>>(istream& is,  Fraction& obj) {
	/*int integer, numerator, denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);
	*/
	const int n = 32;
	char buffer[n] = {};
	char delimiters[] = "(/) +";
	char* number[5] = {};
	cin.getline(buffer, n);	
	int i = 0;
	/*while (pch)
	{
		cout << pch << "\t";
		pch = strtok(NULL, delimiters);
		number[i++] = pch;// atoi(pch);
	}*/
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters), i++)
	{
		number[i] = pch;
	}
	//for (i = 0; i < 5; i++) cout << number[i] << "\t"<< endl;
	switch (i)
	{
	case 1: obj.set_integer(atoi(number[0])); break;
	case 2: 
		obj.set_numerator(atoi(number[0])); 
		obj.set_denominator(atoi(number[1])); 
		break; 
	case 3:
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
		break;
	default: cout << "Error!" << endl;
	}
	return is;
}

int dva_plus_dva()
{
	return 2 + 2;
}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICALS_OPERATORS_CHECK
//#define COMPARISON_OPERATORS
#define TYPE_CONVERTIONS_HOME_WORK
//#define OUTPUT_CHECK
//#define INPUT_CHECK

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

	//Fraction A(2, 3, 4);
	/*A.print();
	A.to_improper();
	A.print();
	A.to_proper();
	A.print();*/

	//Fraction B(3, 4, 5);
	/*B.print();
	B.to_improper();
	B.print();
	B.to_proper();
	B.print();*/

#ifdef ARITHMETICALS_OPERATORS_CHECK
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

	//Fraction D = A + B;
	//cout << "Сложение: "; 
	(A+B).print();

	Fraction E = A - B;
	cout << "Вычитание: "; E.print();

	Fraction F = A / B;
	cout << "Деление: "; F.print();
#endif ARITHMETICALS_OPERATORS_CHECK
	
#ifdef COMPARISON_OPERATORS
	Fraction A(1,2), B(5,10);
	Fraction X(1, 4), Y(5, 4);
	/*A.to_improper(), B.to_improper();
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

	/*if (A == B) {
		cout << "A == B" << endl;
	}else { cout << "A != B" << endl; }	

	if (X != Y){
		cout << "X != Y" << endl;
	}else { cout << "X == Y" << endl; }*/
	cout << (A == B) << endl;
	cout << (A != B) << endl;
	cout << (A > B) << endl;
	cout << (A >= B) << endl;
	cout << (A < B) << endl;
	cout << (A <= B) << endl;
#endif //COMPARISON_OPERATORS

#ifdef OUTPUT_CHECK
	Fraction A;
	cout << A << endl;
	Fraction B(5);
	cout << B << endl;
	Fraction C(1,2);
	cout << C << endl;
	Fraction D(2,3,4);
	cout << D << endl;
#endif //OUTPUT_CHECK

#ifdef INPUT_CHECK
	Fraction A;
	cout << "Введите простую дробь: ";  cin >> A; cout << "Вы ввели: " << A<< endl;
	cout << "Сокращенная дробь: " << A.reduce()<< endl;
#endif //INPUT_CHECK
	//A *= B;
	//A.print();
	/*int a = 2;
	Fraction A = (Fraction)5; //From int to Fraction (from less to more)
	A.print();
	Fraction B;
	B = (Fraction)3;//явное преобразование
	B.print();*/

	/*//сокращение дроби
	Fraction R(14,21);
	R.print();
	R.reduce();
	R.print();*/
#ifdef TYPE_CONVERTIONS_HOME_WORK
	/*//Task1
	Fraction A(2, 3, 4);
	double a = A;
	cout << a << endl;*/

	//Task2
	double b = 3.14;
	Fraction B = b;
	B.print();
#endif //TYPE_CONVERTIONS_HOME_WORK

}