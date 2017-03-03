function [abra, hitelesitettMeresiErtekek, elsoSzenzorHelyesMereseiSzovegben,szenzorokDeliMeresenekAtlagaSzovegben]=gyak3_f32_BUGE0Q(legnyomasErtekek)
% A bemenetünk egy 900 és 1060 közötti véletlenszerű értékeket tartalmazó
% 4x3x31-es mátrix.
%% Ide jöhet az 1. részfeladathoz szükséges adat kigyűjtése

elsoesti = squeeze(legnyomasErtekek(1,3,:));

he= find(930<elsoesti & elsoesti<1060);
nh= find(not (930<elsoesti & elsoesti<1060));


%% Ide kerüljön az ábra kirajzoltatása
abra = figure; % ez után
hold on;
axis([1 31 890 1100]);
plot([0,31],[930,930],'m','LineWidth',2);
plot([0,31],[1060,1060],'m','LineWidth',2);
plot(elsoesti,'-- k','LineWidth',3);
plot(he,elsoesti(he),'o','LineWidth',2,'MarkerSize',7,'MarkerEdgeColor','r','MarkerFaceColor','g');
plot(nh,elsoesti(nh),'k o','LineWidth',2,'MarkerSize',7);

hold off;


%% Itt legyenek a további részfeladatok

hitelesitettMeresiErtekek = NaN;

elsoSzenzorHelyesMereseiSzovegben = NaN

szenzorokDeliMeresenekAtlagaSzovegben = NaN;
end
