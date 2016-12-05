Lineáris algebrával való megoldás:
a+b+c=114

Mértani:
a=a
b=a*q
c=a*q^2

Számtani:
a=a
b=a+3d
c=a+24d

Átírva: (a q paraméter mert nem lineáris)

 a		 b		 c		 d
+1 		+1 		+1 		+0 	= 	+114 	| a+b+c=114
+q 		-1 		+0 		+0 	= 	+0 		| a*q-b=0
+q^2 	+0 		-1 		+0 	= 	+0 		| a*q^2-c=0
+1 		-1 		+0 		+3 	= 	+0 		| a+3d-b=0
+1 		+0 		-1 		+24 =	+0 		| a+24d-c=0

Mátrixal: {{1,1,1,0,114},{q,-1,0,0,0},{q^2,0,-1,0,0},{1,-1,0,3,0},{1,0,-1,24,0}}

{1		1		1		0	|	114	}
{q		-1		0		0	|	0	}
{q^2	0		-1		0	|	0	}
{1		-1		0		3	|	0	}
{1		0		-1		24	|	0	}

Gauss-Jordan elimináció után:

A q lehetséges értékei: 7, 1

Ha q = 7 akkor:

{1		0		0		0	|	2	}
{0		1		0		0	|	14	}
{0		0		1		0	|	98	}
{0		0		0		1	|	4	}
{0		0		0		0	|	0	}

a=2 b=14 c=98 d=4 q=7

Ha q = 1 akkor:

{1		0		0		0	|	38	}
{0		1		0		0	|	38	}
{0		0		1		0	|	38	}
{0		0		0		1	|	38	}
{0		0		0		0	|	0	}

a=38 b=38 c=38 d=0 q=1

------------------------------------------------------------------------------- 

Középiskolás megoldás:

Kiindulás
				a+b+c = 114
					b = a*q
					c = a*q^2
					b = a+3d
					c = a+24d0

A mértani sor miatt
				  a*c = b^2

Számtanival felírva
			 a(a+24d) = (a+3d)^2
			  a^2+24d = a^2+6ad+9d^2
				   d1 = 0
				   d2 = 2a

a+b+c=114 be behelyetesítés a számtani soros képletekkel
   a+(a+3*d)+(a+24*d) = 114
				   a1 = 2
				   a2 = 38

Mértani sor
					b = a+3d
				   b1 = 14
				   b2 = 38

				    c = a+24d
				   c1 = 98
				   c2 = 38

A mértani sor hányadosa
					q = b/a
				   q1 = 7
				   q2 = 1 