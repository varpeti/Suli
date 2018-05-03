package vp.game;

import java.util.*;

import vp.net.*;

public class ServerEngine implements Runnable
{
    private Message message;

    void handle(Message.Packet input)
    {
        System.out.println("Server.handle: "+input.getMsg()); //LOG

        ArrayList<String> cmd = Message.split(input.getMsg(),"\\s");

        if (Objects.equals(cmd.get(0),"ping"))
            message.socketWrite(new Message.Packet("pong",input.getAddress(),input.getPort()));
        else if (Objects.equals(cmd.get(0),"hello"))
            message.socketWrite(new Message.Packet("welcome "+cmd.get(4))); //Broadcast
        else 
            message.socketWrite(new Message.Packet("???",input.getAddress(),input.getPort()));
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