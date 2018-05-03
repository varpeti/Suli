package vp.game;

import java.util.*;

import vp.net.*;

public class ServerEngine implements Runnable
{
    Message message;

    void handle(String input)
    {
        if (Objects.equals(input,"ping")) message.socketWrite("pong"); 
        else if (Objects.equals(input,"hello")) message.socketWrite("Welcome!"); 
        else message.socketWrite("???");

        System.out.println("Server.handle: "+input);
    }

    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                ArrayList<String> input = message.engineRead();

                for (int i=0;i<input.size();i++) 
                {
                    handle(input.get(i));
                }

                Thread.sleep(1000);
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