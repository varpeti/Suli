package vp.net;

import java.io.*;
import java.util.*;
import java.net.*;

import vp.net.*;

public class Client implements Runnable
{
    private Message message;
    private InetAddress address;
    private int port;
    private DatagramSocket socket;
    private SocketIO socketIO;

    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                ArrayList<String> toServer = message.socketRead();
                
                for (int i=0;i<toServer.size();i++) 
                {
                     socketIO.send(toServer.get(i),address,port); //Üzenet küldés
                }

                socketIO.receive(1000); //Válaszra várás

                String input = socketIO.getData();

                System.out.println(input);

                message.engineWrite(input);
                
                Thread.sleep(1000);

            }
            catch (SocketTimeoutException e) 
            {
                System.err.println("A server nem érhető el!");
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

    public Client(String _address, int _port, Message _message)
    {
        try
        {
            message = _message;
            address = InetAddress.getByName(_address);
            port = _port;
            socket = new DatagramSocket();
            socketIO = new SocketIO(socket);
            new Thread(this).start();
        }
        catch (Exception e) // TODO: jobb Exception kezelés
        {
            //System.err.println(e.getMessage());
            e.printStackTrace();
        }
        
    }
}