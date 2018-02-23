--[[02.23 Gyak
]]

Olah András
    olaha@itk.ppke.hu
    409 szoba

Vizsga:
    Írásbeli
    Szóbeli

Pluszpontok:
    Olah andrásnak is küldjük mert ő dokumentáljas

-----------------

Folytonos rendszerek

    Benement->Rendszer->Kimenet

    explicit: y(t)=Đ{x(t)}
    implicit: Đ{y(t),x(t)}=0

    lineáris:
        Ha érvényes rá a szuper pozíció elve

    időinvariáns:
        Nem függ az időtől
        y(t)=Đ{x(t)} -> y(t-A)=Đ{y(t-A)}

    kauzalitás:
        y(t=t`) = Đ{x(t),y(t),-oo<t<t`}

    stabil:

    hálózat és rendszer
        A hálózat is rendszer, csak a rendszernél nem kell tudni mi van benne.

    rendszer szintézis:
        hálózat->rendszer

    rendszer analízis
        rendszer->hálózat


    Lineáris időinvariáns (+passzív) rendszerek

        komponensek
            explicit
            implicit

            pl:
                ellenállás
                    u[R](t)=i[R](t)/R
                kapacitás
                    i[C](t)=C*u`[C](t)
                tekercs
                    u[L](t)=L*u`[L](t)
                dioda (nem lineáris | időinvariáns)
                    z[D](t)=i[0] * e^(u[D]/i[D])
--------------
1) Rendszer analízis
    áramkör e + komp k = diff e = rendszer e

    [[ 
        o--r1---+---r2----+---o
       x(t)     c1        l1
        o-------+---------+---o
    ]]

    Egyenletek:
        u[r1]=r1*i[r1]
        stb
    
    Kirchoff törvények:
        Csomóponti:
            i[r1]-i[r2]-i[c]=0
            i[r2]-i[l]=0
        Hurok:
            u[r1]+u[c]-u[l]=0
            u[r2]+u[l]-u[c]=0

    Diff egyenlet rendszer:
        u[c]`= -u[c]/(r1*c) - i[l]/c + u(x)/(r1*c)
        u[l]`= -u[c]/l - (r2*il)/c
    
    Diff egyenlet:
        l*i[l]`` + (r2 + l/(r1*c) )*i[l]` + (r2/(r1*c) + 1/c ) *i[l] + u(x)/(r1*c) = 0

---------

2) Vizsgáló jelek rendszere:
    DirachDelta =   | +oo ha t=0
                    | 0   def

    x(t) = int(-oo,+oo, x(Tau)*DirachDelta(t-Tau), dt)

    y(t) = Đ{x(t)} = Đ{ int(-oo,+oo, x(Tau)*DirachDelta(t-Tau), dt) } = int(-oo,+oo, x(Tau)*Đ{DirachDelta(t-Tau)}, dt) 
         = int(-oo,+oo, x(Tau)*h(t-Tau), dt)
         = x(t) ¤ h(t) -- ahol a '¤' az konvolúció

------------

3) Analízis a ferkvencia tartományon
    Jelek dekopozíciója

    Fourier transzformáció
        x(f) =  int(-oo,+oo,x(t)* e^(-j*2pi*f*t), dt)
        x(t) = 1/2pi * int(-oo,+oo,x(f)*e^(j*2pi*f*t, df)

    A konvolúció a ferkvencia tartományon szorzás

    Szűrők
        Alul áteresztő (felül vágó)  [[__--__]]
        Felül áteresztő (alul vágó)  [[--__--]]
        Sáv vágó              [[---__---__----]]
        Sáv áteresztő         [[-__---__---__-]]
        Mindent áteresztő     [[--------------]]

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
2) Belépő jel: x(t)~=0 ha t>=0
3) Abszulut integrálható: int(-oo,+oo,|x(t)|,dt) < +oo
4) Véges energiájú jel: int(-oo,+oo,x(t)^2,dt) < +oo
5) Véges átlag energiájú jel 1/T * int(-T/2,T/2,x(t)^2,dt) < +oo

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
    x(f) =  int(-oo,+oo,x(t)* e^(-j*2pi*f*k*t), dt)

    int(-oo,+oo,x^2(t),dt) = int(-oo,+oo,|X(f)|^2,df)

9) Lapace transzformáció
    int(-oo,+oo,x(t)*e^(-A*t), dt) < +oo;
        -> int(-oo,+oo,x(t)*e^(-A*t)*e^(-j*2pi*f*k*t), dt) = int(0,+oo,x(t)*e^(-s*t), dt) = X(s)

10) Lineáris Időinvariáns rendszerek (LTI)
    x(t)->[LTI]->y(t)

    DirachDelta(t)->[LTI]->h(t) - Impulzus válasz fv