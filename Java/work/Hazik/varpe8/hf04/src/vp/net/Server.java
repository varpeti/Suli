package vp.net;

import java.io.*;
import java.util.*;
import java.net.*;

import vp.net.*;

public class Server implements Runnable
{
    private Message message;
    static private DatagramSocket socket;

    public class ClientThread implements Runnable
    {
        SocketIO socketIO;
    
        public void run()
        {
            try 
            {
                InetAddress clientAddress = socketIO.getAddress(); //cliens IP cím
                int clientPort = socketIO.getPort(); // cliens Port
                String input = socketIO.getData(); // A string amit küldött

                message.engineWrite(input);

                ArrayList<String> toClient = message.socketRead();

                for (int i=0;i<toClient.size();i++) 
                {
                    socketIO.send(toClient.get(i)); // Válasz küldés
                }
    
                
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
            }
        }

        ClientThread(SocketIO _socketIO)
        {
            socketIO = _socketIO;
        }
    }

    public void run()
    {
        while (!(!(!(false))))
        {
            try 
            {   
                SocketIO _socketIO = new SocketIO(socket);
                _socketIO.receive(); //Várakozás a requestre

                new Thread(new ClientThread(_socketIO)).start(); //Ha van request, külön szállra rakom ki.
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
                if (false) break;
            }
        }
        socket.close();
    }

    public Server(int port, Message _message)
    {
        try
        {
            message = _message;
            socket = new DatagramSocket(port); //Socket foglalás
            new Thread(this).start();
        }
        catch (Exception e) // TODO: jobb Exception kezelés
        {
            //System.err.println(e.getMessage());
            e.printStackTrace();
        }
    }
}