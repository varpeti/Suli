import java.util.Vector;
import java.util.Arrays;

import Merleg.Merleg;

public class Main
{
    public static void kiir(Merleg merleg,int suly)
    {
        int[] megoldas = merleg.sulyokraValt(suly);
        System.out.print("Targy: "+suly+" Felhasznált súlyok: [ ");
        for (int i=0;i<megoldas.length-1;i++) System.out.print(megoldas[i]+" ");
        System.out.println("] összesen: "+megoldas[megoldas.length-1]);
    }


    public static void main(String[] args) 
    {
        {   //A trükkös
            Integer[] sulyok = {1,5,20,25};
            Merleg merleg = new Merleg(sulyok);
            kiir(merleg,42);
            kiir(merleg,44);
        }

        {   //Nagy számok
            Integer[] sulyok = {1,2,5,10,20,50,100,200};
            Merleg merleg = new Merleg(sulyok);
            kiir(merleg,231);
            kiir(merleg,247);
        }

        {   //Nincs 1
            Integer[] sulyok = {2,3,5,7};
            Merleg merleg = new Merleg(sulyok);
            kiir(merleg,11);
            kiir(merleg,15);
        }
        
    }
}