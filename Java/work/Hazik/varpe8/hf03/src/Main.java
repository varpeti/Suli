import vp.leagueOfHeroes.*;
import java.io.*;
import java.util.*;

public class Main
{
    public static void main(String[] args) throws InterruptedException
    {
        Quests quests = new Quests(30); //30sec
        Equipments equipments = new Equipments();
        Leagues.setLeagues(quests,equipments);

        try{System.in.read();}catch(Exception e){} //TODO: earse me
    }
}