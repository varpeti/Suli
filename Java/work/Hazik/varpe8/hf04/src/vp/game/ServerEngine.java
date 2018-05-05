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

    public void clientinfo(Message.Packet input)
    {
        // Ha elsőször csatlakozik hozzáadjuk //TODO: lecsatlakozottak, régóta nem válaszolók kivétele a listáról.
        String clientID = input.getAddress().toString() + "," + input.getPort();
        if (!existingClients.contains(clientID)) 
        {
            existingClients.add(clientID);
            clientAddresses.add(input.getAddress());
            clientPorts.add(input.getPort());
        }
    }
    public void broadcast(String msg)
    {
        for (int j=0; j < clientAddresses.size(); j++) //Broadcast
        {
            message.socketWrite(new Message.Packet(msg,clientAddresses.get(j),clientPorts.get(j)) ); 
        }
    }
    public void broadcast(String msg,int repeate)
    {
        for (int j=0; j < clientAddresses.size(); j++) //Broadcast
        {
            message.socketWrite(new Message.Packet(msg,clientAddresses.get(j),clientPorts.get(j),repeate) ); 
        }
    }

    void handle(Message.Packet input)
    {
        System.out.println("LOG.Server.handle: "+input.getMsg());

        ArrayList<String> cmd = Message.split(input.getMsg(),"\\s");

        if (Objects.equals(cmd.get(0),"ping"))
        {
            message.socketWrite(new Message.Packet("pong",input.getAddress(),input.getPort()));
        }
        else if (Objects.equals(cmd.get(0),"setserver"))
        {
            ;//TODO
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
    
    public ServerEngine(Message _message)
    {
        message = _message;
        new Thread(this).start();
    }    
}