--[[02.16
]]

Követelmény:
    4 kis ZH
    1 Nagy ZH
    1 VizsgaZH
    Gyakjegy+Vizsgajegy=Jegy

Megajánlott:
    Legalább 4es kis és nagy ZH-k

------

1) Véges tartalmú jel: x(t)~=0 ha t: [A;B]
2) Belépő jel: x(t)~=0 ha t~<0
3) 

6) Speciális jelek:
    Dirach delta
    Egy ugrás
        x(t)=0 ha t<0 
        x(t)=1 ha t>0
    Egység sebesség ugrás
        x(t)=t
7) Periodikus jelek:
    x(t)=x(t+ET)
    f = 1/T ; x(t)=sum(k=-oo,+oo,C[k]*e^(-j*2pi*f*k*t) ) ; C[k] = 1/T int(-T/2,T/2,x(t)*e^(-j*2pi*f*k*t), dt) 

8) Fourier transzformáció
    int(-oo,+oo,x(t),dt) < +oo ; int(-oo,+oo,x(t)*e^(j*2pi*f*k*t), dt)
    X(f) =  int(-oo,+oo,x(t)*(-j*2pi*f*k*t), dt)

    int(-oo,+oo,x^2(t),dt) = int(-oo,+oo,|X(f)|^2,df)

9) Lapace transzformáció
    int(-oo,+oo,x(t)*e^(-A*t), dt) < +oo;
        -> int(-oo,+oo,x(t)*e^(-A*t)*e^(-j*2pi*f*k*t), dt) = int(0,+oo,x(t)*e^(-s*t), dt) = X(s)

10) Lineáris Időinvariáns rendszerek (LTI)
    x(t)->[LTI]->y(t)

    DirachDelta(t)->[LTI]->h(t) - Impulzus válasz fv