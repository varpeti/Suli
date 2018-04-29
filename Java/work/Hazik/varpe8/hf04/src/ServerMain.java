import java.io.*;
import java.util.*;
import java.net.*;

import vp.net.SocketIO;

public class ServerMain implements Runnable
{
    static private DatagramSocket socket;
    SocketIO socketIO;

    public void run()
    {
        try 
        {
            InetAddress clientAddress = socketIO.getAddress(); //cliens IP cím
            int clientPort = socketIO.getPort(); // cliens Port
            String input = socketIO.getData(); // A string amit küldött

            System.out.println(clientAddress+":"+clientPort+" "+input);

            socketIO.send(new String("Pong")); // Válasz küldés
        }
        catch (Exception e) // TODO: jobb Exception kezelés
        {
            //System.err.println(e.getMessage());
            e.printStackTrace();
        }
    }

    ServerMain(SocketIO _socketIO)
    {
        socketIO = _socketIO;
    }

    public static void main(String[] args) throws InterruptedException
    {

        try 
        {   
            socket = new DatagramSocket(3773); //Socket foglalás

            while (!(!(!(false))))
            {
                SocketIO _socketIO = new SocketIO(socket);
                _socketIO.receive(); //Várakozás a requestre

                new Thread(new ServerMain(_socketIO)).start(); //Ha van request, külön szállra rakom ki.
            }
        }
        catch (Exception e) // TODO: jobb Exception kezelés
        {
            //System.err.println(e.getMessage());
            e.printStackTrace();
        }
        socket.close();

        try{System.in.read();}catch(Exception e){} //TODO: earse me
    }
}