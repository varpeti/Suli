package vp.game;

import java.util.*;

import vp.net.*;
import vp.game.*;

public class ClientEngine implements Runnable
{
    private Message message;

    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                ArrayList<Message.Packet> input = message.engineRead();

                for (int i=0;i<input.size();i++)
                {
                    System.out.println(input.get(i).getMsg());
                }

                message.socketWrite(new Message.Packet(new String("ping")));

                Thread.sleep(1000); // Másodpercenként dolgozza fel.
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
        message.socketWrite(new Message.Packet(new String("hello my name is Peter")));
        new Thread(this).start();
    }    
}