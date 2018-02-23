package Merleg;

import java.util.ArrayList;
import java.util.Arrays;

public class Merleg {
    private ArrayList<Integer> sulyok = new ArrayList<Integer>(); //Sulyokat tárolja

    public int[] sulyokraValt(int t)
    {

        //Adat készítés:

        ArrayList<Integer[]> ka         = new ArrayList<Integer[]>(); //3: suly, maradek, db
        ArrayList<Integer[]> megoldasok = new ArrayList<Integer[]>(); //3: suly, maradek, db

        ka.add(new Integer[]{0,t,0});

        while (ka.size()>0) { //Rekurzió helyett
            Integer[] k = ka.get(ka.size()-1);
            ka.remove(ka.size()-1);
            megoldasok.add(k);

            for (int i=0;i<sulyok.size();i++) 
            {
                int suly = sulyok.get(i);
                if (k[1]<suly) continue; //Ha kissebb mint a suly akkor off.
                Integer[] kk = new Integer[]{suly,k[1]%suly,k[1]/suly+k[2]};
                boolean off = false;
                for (int j=0;j<ka.size();j++) 
                {
                    if  (ka.get(j)[1]      == kk[1] &&                      //Ha benne van
                         ka.get(j)[2]+k[2] <  kk[2]  ) {off=true; break;}   //és nagyobb, akkor off. 
                    
                }
                if ( kk[1]==0 ) {off=true; megoldasok.add(kk);}
                if (off) continue;
                ka.add(kk);
                
            }
        }

        //Adat feldolgozás:

        //Minimum keresés       // (ha [1]==0 akkor megoldás, és a legjobb megoldás, ha ekkor [2] a minimum)
        Integer[] min = megoldasok.get(0);
        int id = 0;
        for (int i=1;i<megoldasok.size();i++) if (megoldasok.get(i)[1]==0 && (megoldasok.get(i)[2]<min[2] || min[2]==0) ) { min=megoldasok.get(i); id=i;}

        /*Adat kiírás:
        for (int i=0;i<megoldasok.size();i++) {
            for (int j=0;j<3;j++) {
                System.out.print(megoldasok.get(i)[j]+" ");
            }
           System.out.println();
        }
        System.out.println("min: "+min[0]+" "+min[1]+" "+min[2]+" id: "+id);
        //*/

        //Visszafejtés a minimumtól
        int[] megoldas = new int[sulyok.size()+1];
        megoldas[megoldas.length-1]=megoldasok.get(id)[2];
        for (int i=id-1;i>=0;i--) 
        {   
            if (megoldasok.get(i)[1]>=megoldasok.get(id)[0]) 
            {
                for (int j=0;j<sulyok.size();j++) if ((int)sulyok.get(j)==(int)megoldasok.get(id)[0]) {megoldas[j]+=megoldasok.get(i)[1]/megoldasok.get(id)[0]; break; } // (int) nélkül random néha jó volt néha nem... vicc(es) ez a nyelv.
                id=i;
            }
        }

        return megoldas;
    }

    public Merleg(Integer[] _sulyok)
    {
        this.sulyok.addAll(Arrays.asList(_sulyok)); // arrayból arraylistet csinál.
        //System.out.println(this + " " + sulyok);
    }
}