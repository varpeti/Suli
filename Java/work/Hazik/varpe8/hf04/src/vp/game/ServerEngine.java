package vp.game;

import java.util.*;

import vp.net.*;

public class ServerEngine implements Runnable
{
    private Message message;

    void handle(Message.DestMsg input)
    {
        System.out.println("Server.handle: "+input.getMsg());
        if (Objects.equals(input.getMsg(),"ping") ) message.socketWrite(new Message.DestMsg(new String("pong"),input.getAddress(),input.getPort()));
    }

    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                ArrayList<Message.DestMsg> input = message.engineRead();

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