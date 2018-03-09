# 03.09 Előadás

AD(x(t)) = kódolás( kvatálás(SNR=3/2*2^n, mintavétel(f[s] >= 2 B, x(t)) )

## Kvantálás (általánosan optimális)

Delta - intervallum felosztás

Q[i] - megadja hogy melyik kvantálási szinthez tartozik az adott intervallum

Hol optimális ez?

L(Delta,Q) = int(Delta[i], , (x-q)^2 p(x), dx)

Ez nem ismert. 

De ha Q adott:

Delta[i] = (x-q[i])^2 < (x-q[i]) minden j = 1,...,N, j<>i

De ha Delta adott:

???

Egyik se adott:

Delta(0);Q(0) -> Delta(1);Q(0) -> Delta(1);Q(1) -> Delta(2);Q(1) -> ... -> Delta(opt);Q(opt)

Delta(opt);Q(opt) -nál megakad és ekkor ez a glóbális optimum. Számítás igényes, mindig változik, nem időinvariáns.


### Diferenciál kvantálás

```
11      -
10    -   -
01  -       - 
00-           -
  1 2 3 4 5 6 7
```

ekkor a sima: 00 01 10 11 10 01 00 : 14 bit

differenciál: 00 1 1 0 0 0 0 : 8 bit

Problémák:
- túl lassan követi
- nem tudja a stagnálást leírni

## Prediktív kvantálás

A múlt valamelyest meghatározza a jelent:

pl:

|Étteremben kértem egy pohár sö | kód |
|--|--|
| rt.                           | 0   |       
| tét gépolajat.                | 10  |
| rétet a puskámba.             | 110 |
| ntésből maradt lét.           | 111 |

```
jel     kodszó a jelhez
x[1]    z[1]="01"
x[2]    z[2]="110"
...     ...
x[n]    z[n]="1"
```

Dataspeed: f[s] * L  ahol az L az átlagos kódszó hossz

## Digitális jelek:

- Véges tartójú jel: 
    - x(n) = 0 ha n neleme [A;B]

- Kauzális jel: 
    - x(n) = 0 ha n<0

- Dirach delta:
    - delta(n) = 1 ha n=0 
    - delta(n) = 0 ha n<>0

- Egység sebesség ugrás:
    - x(n) = n ha n>=0
    - x(n) = 0 ha n<0

- Exponenciális: 
    - x(n) = r^k * n(n)
    - 0<r<1 lecsengő
    - -1<r<0 osszilálva lecsengő

- Szinuszos jel:
    - A * cos(2 pi f n)

- Véges energiájú jel:
    - sum(n=-N, N, x^2(n) )

- Véges átlag energiájú jel:
    - lim(N->+oo) 1/(2N+1) sum(n=-N, N, x^2(n) ) < +oo



