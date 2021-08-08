#include <iostream>
#include "vec3.h"

using namespace std;
int main()
{
	Vec3f x(1.0);
	cout << x << endl;
	Vec3f y(2.0, 1.0, 2.0);
	cout << x - y << endl;
	cout << normalize(y) << endl;
	cout << nolm(normalize(y)) << endl;

	cout << dot(x, y) << endl;
	cout << cross(x, y) << endl;
	cout << dot(x, cross(x, y)) << endl;

	return 0;
}