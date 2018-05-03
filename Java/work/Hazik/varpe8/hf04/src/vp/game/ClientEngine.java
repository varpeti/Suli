package vp.game;

import java.util.*;

import vp.net.*;
import vp.game.*;

public class ClientEngine implements Runnable
{
    private Message message;

    void handle(Message.Packet input)
    {
        System.out.println("LOG.Client."+name+".handle: "+input.getMsg());

        ArrayList<String> cmd = Message.split(input.getMsg(),"\\s");

        if (Objects.equals(cmd.get(0),"pong"))
            ;//Mivel gyakran jön, ezért ne nézze végig a többit.
        else if (Objects.equals(cmd.get(0),"setname"))
        {
            name = cmd.get(1);
            message.socketWrite(new Message.Packet("hello my name is "+name));
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
                    handle(input.get(i));
                }

                message.socketWrite(new Message.Packet("ping")); // Pulzáló életjel a szervernek

                Thread.sleep(1000); // Másodpercenként dolgozza fel, küld fel adatot, pulzál.
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }
    }
    
    public ClientEngine(Message _message)
    {
        message = _message;
        message.socketWrite(new Message.Packet(new String("ping")));
        new Thread(this).start();
    }

    String name = new String("nill");
}