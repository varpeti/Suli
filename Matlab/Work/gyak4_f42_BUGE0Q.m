function abra=gyak4_f42_BUGE0Q(archivum)
load(archivum);

a1 = kep*A1;
a2 = kep*A2;
a3 = kep*A3;
a4 = kep*A4;

%% Ide kerüljön az ábra kirajzoltatása
abra = figure; % ez után

subplot(2,2,1);
plot(a1(:,1),a1(:,2));
%% X nyújt

subplot(2,2,2);
plot(a2(:,1),a2(:,2));
%% Y nyújt

subplot(2,2,3);
plot(a3(:,1),a3(:,2));
%% +90

subplot(2,2,4);
plot(a4(:,1),a4(:,2));
%% +180
end