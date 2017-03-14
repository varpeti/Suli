function abra=gyak5_f51_BUGE0Q(a,b,c,d,e,f)

x1=e:1:f;
x2=e:0.001:f;

y1= a*x1.^3+b*x1.^2+c*x1+d;
y2= a*x2.^3+b*x2.^2+c*x2+d;

%% Ide kerüljön az ábra kirajzoltatása
abra = figure; % ez után

hold on;
xlabel('x érték','FontSize', 14,...
 'FontWeight', 'bold');
ylabel('y értek', 'FontSize', 14,...
 'FontWeight', 'bold');
title('Polinom', 'FontSize', 14,...
 'FontWeight', 'bold');
plot(x1,y1,'b');
plot(x2,y2,'r');
hold off;

end