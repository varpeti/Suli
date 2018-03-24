package vp.leagueOfHeroes;

import vp.leagueOfHeroes.*;

import java.util.*;

public class Quests implements Runnable {
    private int number;                                            // Questek száma
    private ArrayList<Integer> repu = new ArrayList<Integer>();    // Hírnév
    private ArrayList<Integer> time = new ArrayList<Integer>();    // Quest elvégzésének ideje
    private ArrayList< ArrayList<String> > equipments = new ArrayList< ArrayList<String> >(); // Szükséges felszerelés
    private ArrayList<Integer> minrep = new ArrayList<Integer>();  // Elválaláshoz szükséges hírnév
    private ArrayList<Boolean> status = new ArrayList<Boolean>();  // True - szabad, False - rajta vannak az ügyön \ végeztek vele
    private static Random rand = new Random();

    private void newQuest(int i)
    {   
        //Magic numbers
        int mA = number/2;
        int mB = number/4;
        int mC = 5000;
        int mD = 5;

        repu.add(rand.nextInt(mA)+1);
        time.add(rand.nextInt(mC));
        minrep.add(rand.nextInt(mB*((i*mD)/number)+1)); //Növekszik idővel, az elején 0
        status.add(true);

        ArrayList<String> equs = new ArrayList< String>();
        do {equs.add(Equipments.getRandom());} while (rand.nextInt(3)!=0); 
        for (int k=0;k<equs.size();k++) for (int j=0;j<equs.size();j++) if (k!=j && equs.get(k)==equs.get(j)) equs.remove(j);
        equipments.add(equs);
        

        System.out.println("Új küldetés! "+i +". ("+
            "repu: "       +repu.get(i)      +", "+
            "idő: "        +time.get(i)      +", "+
            "felszerelés: "+equipments.get(i)+", "+
            "minimum rep: "+minrep.get(i)    +")\n"
        );
    }

    public void run() {
        int i = 0;
        while (i<number)
        {   
            newQuest(i++);
            newQuest(i++);
            try { Thread.sleep(500);} catch (Exception e) {}
        }
        number=-1;
    }

    public Quests(int _number)
    {
        number = _number*2;
        new Thread(this).start();
    }

    public Quests(){}

    public Boolean isOver() //Ha vége van nem mennek többet a hősök küldetésre
    {
        return (number==-1);
    }

    public synchronized int getQuest(int repu)
    {
        for (int i=0;i<minrep.size();i++) 
            if (minrep.get(i)<=repu && status.get(i))
            {
                status.set(i,new Boolean(false));
                try { Thread.sleep(500);} catch (Exception e) {}
                return i;
            }
        return -1;
    }

    public synchronized ArrayList<String> getItemList(int id)
    {
        return equipments.get(id);
    }

    public synchronized int getQuestTime(int id)
    {
        return time.get(id);
    }

    public synchronized int getQuestRepu(int id)
    {
        return repu.get(id);
    }
}