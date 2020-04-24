#include <iostream>
#include <cstring>

using namespace std;

class car
{
private:
	int wheels;
	double thing;

public:
	void setWheels(int w)
	{
		wheels = w;
	}

	void setThing(double t)
	{
		thing = t;
	}
};

int main()
{
	car c;
	c.setWheels(4);
	c.setThing(3.14);

	car *ptr = &c;

	struct bs
	{
		int w;
		double t;
	};

	bs base;
	bs *basePtr = &base;

	memcpy(basePtr, ptr, sizeof(struct bs));

	cout << base.w;
	cout << base.t;

	return 0;
}
