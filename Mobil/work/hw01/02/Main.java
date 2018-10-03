import java.util.*;

import Weapon.L1.L2.BayonettRifle;

public class Main
{
    public static void main(String[] args) 
    {
        BayonettRifle br = new BayonettRifle();

        System.out.println(br.name());

        try{System.in.read();}catch(Exception e){} //TODO: remove
    }
}