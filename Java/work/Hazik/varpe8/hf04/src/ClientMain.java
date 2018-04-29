import java.io.*;
import java.util.*;
import java.net.*;

import vp.net.SocketIO;

public class ClientMain implements Runnable
{
    InetAddress address;
    int port;
    DatagramSocket socket;
    SocketIO socketIO;

    public void run() 
    {
        while (!(!(!(false))))
        {
            try
            {
                socketIO.send(new String("Ping"),address,port); //Üzenet küldés

                socketIO.receive(); //Válaszra várás

                System.out.println(socketIO.getData());
                Thread.sleep(1000);

            }
            catch (Exception e) // TODO: jobb Exception kezelés
            {
                //System.err.println(e.getMessage());
                e.printStackTrace();
                break;
            }
        }
        socket.close();
        
    }

    ClientMain(String _address, int _port)
    {
        try
        {
            address = InetAddress.getByName(_address);
            port = _port;
            socket = new DatagramSocket();
            socketIO = new SocketIO(socket);
        }
        catch (Exception e) // TODO: jobb Exception kezelés
        {
            //System.err.println(e.getMessage());
            e.printStackTrace();
        }
        
    }
    public static void main(String[] args) throws InterruptedException
    {
        new Thread(new ClientMain("localhost",3773)).start();
    }
}