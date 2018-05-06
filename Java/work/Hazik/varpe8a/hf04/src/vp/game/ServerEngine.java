package vp.game;

import java.util.*;
import java.net.*;

import vp.net.*;

public class ServerEngine implements Runnable
{
    private Message message;

    //Broadcasthoz tárolja az eddigi clienseket
    private ArrayList<InetAddress> clientAddresses = new ArrayList<>();
    private ArrayList<Integer>     clientPorts     = new ArrayList<>();
    private HashSet<String>        existingClients = new HashSet<>();

    // pong-al folyamatosan streamelt message
    private String status = "wait4players 2 0";

    // Játék változók
    static public class Game
    {
        static public int players = 2; //Ne nyomjon "error gameisfull"-t
        static public int ship2   = 0;
        static public int ship3   = 0;
        static public int ship4   = 0;
        static public int ship5   = 0;
        static public int round   = 0;
    }

    private void clientinfo(Message.Packet input)
    {
        // Ha elsőször csatlakozik hozzáadjuk //TODO: lecsatlakozottak, régóta nem válaszolók kivétele a listáról.

        String clientID = input.getAddress().toString() + "," + input.getPort();
        if (!existingClients.contains(clientID)) 
        {

            if (Game.players<=clientAddresses.size())
            {
                message.socketWrite(new Message.Packet("error gameisfull",input.getAddress(),input.getPort()));
                return; // Ha megvan az összes játékos.
            }

            existingClients.add(clientID);
            clientAddresses.add(input.getAddress());
            clientPorts.add(input.getPort());
        }
    }
    private void broadcast(String msg)
    {
        for (int j=0; j < clientAddresses.size(); j++) //Broadcast
        {
            message.socketWrite(new Message.Packet(msg,clientAddresses.get(j),clientPorts.get(j)) ); 
        }
    }
    private void broadcast(String msg,int repeate)
    {
        for (int j=0; j < clientAddresses.size(); j++) //Broadcast
        {
            message.socketWrite(new Message.Packet(msg,clientAddresses.get(j),clientPorts.get(j),repeate) ); 
        }
    }

    private void handle(Message.Packet input)
    {
        System.out.println("LOG.Server.handle: "+input.getMsg());

        ArrayList<String> cmd = Message.split(input.getMsg(),"\\s");

        if (Objects.equals(cmd.get(0),"ping"))
        {
            ArrayList<String> statusf = Message.split(status,"\\s");

            if (Objects.equals(statusf.get(0),"wait4players"))
            {
                if (Game.players==clientAddresses.size()) 
                {
                    Game.round = 0;
                    status = "game -1";
                }
                else
                {
                    status = "wait4players "+Game.players+" "+clientAddresses.size();
                }

            }
            else if (Objects.equals(statusf.get(0),"game"))
            {
                status = "game "+Game.round;
            }

            message.socketWrite(new Message.Packet("pong "+status,input.getAddress(),input.getPort()));
        }
        else if (Objects.equals(cmd.get(0),"hello"))
        {
            broadcast("welcome "+cmd.get(4));
        }
        else
        {
            message.socketWrite(new Message.Packet("???",input.getAddress(),input.getPort()));
        }
    }


    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                ArrayList<Message.Packet> input = message.engineRead();

                for (int i=0;i<input.size();i++) 
                {
                    clientinfo(input.get(i));
                    handle(input.get(i));
                }

                Thread.sleep(100); // 0.1 másodpercenként dolgozza fel.
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }
    }
    
    public ServerEngine(Message _message, int players, int ship2, int ship3, int ship4, int ship5)
    {
        message      = _message;
        Game.players = players;
        Game.ship2   = ship2;
        Game.ship3   = ship3;
        Game.ship4   = ship4;
        Game.ship5   = ship5;
        new Thread(this).start();
    }    
}