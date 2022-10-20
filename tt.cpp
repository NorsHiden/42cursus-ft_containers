#include <iostream>

struct b
{
	std::string yes;
	int no;
	b(const std::string& one, const int& two): yes(one), no(two) {}
};

struct a
{
	b *_b;
	a() { _b = new b("life is good", 5); }

	b*	.operator->()
	{
		return (_b);
	}
};

int main(void)
{
	a _a;

	_a._b->yes.capacity();

	std::cout << _a->yes << std::endl;
	return (0);
}