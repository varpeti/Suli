#ifndef _KAMERA_
#define _KAMERA_

#include "math.h"

class KAMERA
{
private:
	double kx;
	double ky;
	double ks;
	double kr;

public:
	void aset(double bx, double by, double bs, double br);
	void rset(double bx, double by, double bs, double br);
	void get(double &bx, double &by, double bs, double br);

	void getKamCoords(double &x, double &y);
	void getCoords(double &x, double &y);

	KAMERA();
	~KAMERA();
};

void KAMERA::getKamCoords(double &x,double &y)
{
	double c = cos(-kr);
	double s = sin(-kr);
	x-= kx;
	y-= ky;
	double seged;
	seged = c*x - s*y;
	y = s*x + c*y;
	x = seged;
	x*= ks;
	y*= ks;
}

void KAMERA::getCoords(double &x,double &y)
{
	double c = cos(kr);
	double s = sin(kr);
	x*=ks;
	y*=ks;
	double seged;
	seged = c*x - s*y;
	y = s*x + c*y;
	x = seged;
	x-= kx;
	y-= ky;
}

void KAMERA::aset(double bx, double by, double bs, double br)
{
	kx=bx;
	ky=by;
	ks=bs;
	kr=br;
}

void KAMERA::rset(double bx, double by, double bs, double br)
{
	kx+=bx;
	ky+=by;
	ks*=bs;
	kr+=br;
}

#endif