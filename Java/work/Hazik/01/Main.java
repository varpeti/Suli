import java.util.Vector;
import java.util.Arrays;

import Merleg.Merleg;

public class Main
{
    public static void kiir(Integer[] sulyok, int suly)
    {
        Merleg merleg = new Merleg(sulyok);
        int[] megoldas = merleg.sulyokraValt(suly);
        System.out.println("Targy súlya: "+suly+"g,");
        System.out.print("Felhasználható súlyok: ");
        for (int i=0;i<sulyok.length;i++) System.out.print(sulyok[i]+"g, ");
        System.out.print("\nFelhasznált súlyok: ");
        for (int i=0;i<megoldas.length-1;i++) if (megoldas[i]>0) System.out.print(megoldas[i]+"db "+sulyok[i]+"g, ");
        System.out.println("\nÖsszesen: "+megoldas[megoldas.length-1]+"db súly lett felhasználva.");
        System.out.println();
    }


    public static void main(String[] args) 
    {
        {   //A trükkös
            Integer[] sulyok = {1,5,20,25};
            kiir(sulyok,42);
            kiir(sulyok,44);
        }

        {   //Nagy számok
            Integer[] sulyok = {1,2,5,10,20,50,100,200};
            kiir(sulyok,231);
            kiir(sulyok,247);
        }

        {   //Nincs 1
            Integer[] sulyok = {2,3,5,7};
            kiir(sulyok,11);
            kiir(sulyok,15);
        }
        
    }
}