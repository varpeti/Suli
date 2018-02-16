package Merleg;

import java.util.ArrayList;
import java.util.Arrays;

import Matek.Komplex;

public class Merleg {
    private ArrayList<Integer> sulyok = new ArrayList<Integer>(); //Sulyokat tárolja

    public int[] sulyokraValt(int t)
    {
        ArrayList<Komplex> ka       = new ArrayList<Komplex>(); 
        ArrayList<Komplex> megoldas = new ArrayList<Komplex>();

        ka.add(new Komplex(t,0));

        while (ka.size()>0) {
            Komplex k = ka.get(ka.size()-1);
            ka.remove(ka.size()-1);
            megoldas.add(new Komplex(maradek,k.get) );

            int maradek = (int)Math.floor(k.getRe());
            int db = (int)Math.floor(k.getIm());

            for (int i=0;i<sulyok.size();i++) 
            {
                int suly = sulyok.get(i);
                if (maradek<suly) continue; //Ha kissebb mint a suly akkor off.
                Komplex kk = new Komplex(maradek%suly,maradek/suly+db); System.out.println("kk: "+kk);
                boolean off = false;
                for (int j=0;j<ka.size();j++) 
                {
                    if  ((int)ka.get(j).getRe()    == (int)kk.getRe() &&                      //Ha benne van
                         (int)ka.get(j).getIm()+db <  (int)kk.getIm()  ) {off=true; break;}   //és nagyobb, akkor off. 
                    
                }
                if ( (int)kk.getRe()==0 ) {off=true;  megoldas.add(new Komplex(maradek,kk.getIm()) );}
                //megoldas.add(kk);
                if (off) continue;
                ka.add(kk);
                
            }
        }

        System.out.println(megoldas);

        int[] i = {1,2,3};
        return i;
    }

    public Merleg(Integer[] _sulyok)
    {
        this.sulyok.addAll(Arrays.asList(_sulyok)); // arrayból arraylistet csinál.
        System.out.println(this + " " + sulyok);
    }
}