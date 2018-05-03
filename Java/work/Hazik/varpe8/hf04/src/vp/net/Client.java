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
    private byte timeout;

    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                ArrayList<Message.DestMsg> output = message.socketRead();
                
                for (int i=0;i<output.size();i++) 
                {
                     socketIO.send(output.get(i).getMsg(),address,port); //Üzenet küldés
                }

                socketIO.receive(1000); //Válaszra várás
                Message.DestMsg destMsg = new Message.DestMsg(socketIO.getData(),address,port);
                message.engineWrite(destMsg);
                timeout=0;
            }
            catch (SocketTimeoutException e) 
            {
                timeout++;
                if (timeout<0)
                {
                    System.err.println("A server nem érhető el!");
                    break;
                }
            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
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