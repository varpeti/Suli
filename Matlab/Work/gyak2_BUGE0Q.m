function [c,d,e,f,g,h]=gyak2_BUGE0Q(x,a,b)
  c = a<x & x<b;
  d = x(c);
  e = find(a<x & x<b);
  f = mean(x);
  g = f<x & x<a;
  h = x(g)
end