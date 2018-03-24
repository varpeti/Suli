package vp.leagueOfHeroes;

import  vp.leagueOfHeroes.*;

import java.util.*;

public class Leagues {

    private static String[] leagues = {"Humans","Orcs","Elves","Undeads"};
    private static ArrayList< ArrayList<Hero> > heroes = new ArrayList< ArrayList<Hero> >();
    private static Integer[] repos = {0,0,0,0};
    private static ArrayList< ArrayList<Boolean> > athome = new ArrayList< ArrayList<Boolean> >();

    public static void setLeagues(Quests quests,Equipments equipments)
    {
        heroes.add( new ArrayList<Hero>() {{ add(new Hero("Luna",quests,equipments));             add(new Hero("Mirana",quests,equipments));      add(new Hero("Kunkka",quests,equipments));       }} );
        heroes.add( new ArrayList<Hero>() {{ add(new Hero("Axe",quests,equipments));              add(new Hero("Lion",quests,equipments));        add(new Hero("Troll Warlord",quests,equipments));}} );
        heroes.add( new ArrayList<Hero>() {{ add(new Hero("Nature's Prophet",quests,equipments)); add(new Hero("Enchantress",quests,equipments)); add(new Hero("Lone Druid",quests,equipments));   }} );
        heroes.add( new ArrayList<Hero>() {{ add(new Hero("Lich",quests,equipments));             add(new Hero("Undying",quests,equipments));     add(new Hero("Necrophos",quests,equipments));    }} );
        
        // Ha végeztek mind hazamegy
        for (int i=0;i<heroes.size();i++)
        {
            ArrayList<Boolean> b = new ArrayList<Boolean>();
            for (int j=0;j<heroes.get(i).size();j++) b.add(false);
            athome.add(b);
        }
    }

    public static synchronized void fin(String name) // Befejezte a küldetést
    {
        for (int i=0;i<heroes.size();i++) 
            for (int j=0;j<heroes.get(i).size();j++)
                if ( Objects.equals(name,heroes.get(i).get(j).getName()) ) athome.get(i).set(j,true); 
    }
}