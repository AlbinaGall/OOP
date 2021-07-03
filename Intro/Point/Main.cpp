#include <iostream>
using namespace std;

#define delimiter "\n---------------------------------------------------------\n"

//#define CONSTRUCTOR_OVERLOADING

class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	//Constructors
#ifdef CONSTRUCTOR_OVERLOADING
	Point() //Конструктор по умолчанию
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}
	Point(double x) {
		//Конструктор с одним параметром
		this->x = x;
		this->y = 0;
		cout << "SingleArgumentConstructor: \t\t" << this << endl;
	}
#endif CONSTRUCTOR_OVERLOADING
	Point(double x=0,double y=0) {
		
		this->x = x;
		this->y = y;
		cout << "Constructor: \t\t" << this << endl;
	}
	Point(const Point& other) {
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor: \t\t" << this << endl;
	}
	// Operators
	Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssigment: \t\t" << this << endl;
		return *this;
	}
	void print() const
	{
		cout << "X = " << x << "\t Y = " << y << endl;
	}
	double distance(const Point& other)
	{
		//B-this
		//A-other
		double x_distance = this->x - other.x; 
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance* x_distance+ y_distance* y_distance);
		return distance;
	}
	
};

double distance(Point& A, Point& B) {
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
	return distance;
}
/*struct Point
{
	double x;
	double y;
};*/

//#define STRUCT_POINT
#define DISTANCE_CHECK
//#define CONSTRUCTORS_CHECK
//#define ASSIGMENTS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	Point A;
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
	cout << (*pA).x << "\t" << (*pA).y << endl;


#endif // STRUCT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;
	Point B;
	B.set_x(4);
	B.set_y(5);
	cout << delimiter << endl;
	cout << "Расстояние от B до A равно: " << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от A до B равно: " << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << distance(B, A) << endl;
	cout << delimiter << endl;
#endif DISTANCE_CHECK

#ifdef CONSTRUCTORS_CHECK
	Point C;
	C.set_x(4);
	C.set_y(5);
	Point D = C;
	D.print();

	Point E;
	E = C;
	E.print();
#endif CONSTRUCTORS_CHECK

#ifdef ASSIGMENTS_CHECK
	int a , b , c;
	a = b = c = 0;
	cout << a << "\t" << b << "\t" << c << endl;

	Point A, B, C;
	cout << "\n-------------------------------------------\n";
	A = B = C = Point(4, 5);
	cout << "\n-------------------------------------------\n";
	A.print();
	B.print();
	C.print();
#endif // ASSIGMENTS_CHECK

}

