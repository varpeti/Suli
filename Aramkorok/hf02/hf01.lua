sqrt = math.sqrt

t={}
i={}
A={}
s={}

--[[                        U0=10V
        +--(L=5H->)--(C=100uF->)--o
        |                          / K1: t(0)=zár
        +--(<-R=10Ohm)------------o

--]]

--[[
    Másodrendű
    Állandósult állapotbeli megoldás = 0
    Két kezdeti feltétel
]]

R=10        --Ohm
L=5         --H
C=100e-6    --F

--Kezdeti feltételek:
U0=10
i[0]=0

--Kirchhoff:

--[[
    V["R"]+V["L"]+V["C"]=0
    
    ebből:

    +R*i+U0 +dif(L[1],i,1) -V[0]+(1/C[1])*int(0,t,i,r)

    ebből diffegyenlet:

    (1/C[1])*i +diff(R[1],i,1) +diff(L[1],i,2)
--]]

--[[
    Megoldás keresése i=A*e^(s*t) formában.

    i   = A*e^(s*t)
    i'  = s*A*e^(s*t)
    i'' = s^2*A*e^(s*t)

    Behelyettesítés:

    A*e^(s*t)*(1/C + s*R + s^2*L) = 0

    s[1]= (-R+sqrt(R^2-(4*L)/C)) / (2*L)
    s[2]= (-R-sqrt(R^2-(4*L)/C)) / (2*L)

    i = A[1]*e^(s[1]*t) + A[2]*e^(s[2]*t)

]]

--Behelyettesítés
s[1]= (-R+sqrt(R^2-(4*L)/C)) / (2*L)
s[2]= (-R-sqrt(R^2-(4*L)/C)) / (2*L) --Komplex számok




