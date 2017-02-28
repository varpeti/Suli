function [abra, hitelesitettMeresiErtekek, elsoSzenzorHelyesMereseiSzovegben,szenzorokDeliMeresenekAtlagaSzovegben]=gyak3_f32_BUGE0Q(legnyomasErtekek)
% A bemenetünk egy 900 és 1060 közötti véletlenszerű értékeket tartalmazó
% 4x3x31-es mátrix.
%% Ide jöhet az 1. részfeladathoz szükséges adat kigyűjtése

%% Ide kerüljön az ábra kirajzoltatása
abra = figure; % ez után
hold on;
plot([0,31],[930,930],'m','LineWidth',2);
plot([0,31],[1060,1060],'m','LineWidth',2);
hold off;


%% Itt legyenek a további részfeladatok

hitelesitettMeresiErtekek = NaN;

elsoSzenzorHelyesMereseiSzovegben = NaN

szenzorokDeliMeresenekAtlagaSzovegben = NaN;
end
