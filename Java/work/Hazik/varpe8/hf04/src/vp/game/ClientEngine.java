package vp.game;

import java.util.*;

import vp.net.*;
import vp.game.*;

public class ClientEngine implements Runnable
{
    Message message;

    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                ArrayList<String> input = message.engineRead();

                for (int i=0;i<input.size();i++) 
                {
                    System.out.println(input.get(i));
                }

                message.socketWrite("ping");

                Thread.sleep(1000);
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
        message.socketWrite("hello");
        new Thread(this).start();
    }    
}