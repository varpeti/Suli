#ifndef _komplex_	//ujabb definíció és fordítási hiba elkerülésére
#define _komplex_

class komplex
{
	double a;
	double b;
public:
	komplex(double a,double b) : a(a), b(b) {}

	double re()
	{
		return a;
	};

	double im()
	{
		return b;
	};

	komplex operator*(komplex j)
	{
		return komplex(a*j.a-b*j.b, b*j.a+a*j.b);
	}

	komplex operator+(komplex j)
	{
		return komplex(a+j.a,b+j.b);
	}
	
};

#endif