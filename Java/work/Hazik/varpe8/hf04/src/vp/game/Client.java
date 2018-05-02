package vp.game;

import java.io.*;
import java.util.*;
import java.net.*;

import vp.net.*;

public class Client
{
    class Server implements Runnable
    {
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
                    socketIO.send(new String("Ping"),address,port); //Üzenet küldés
    
                    socketIO.receive(3000); //Válaszra várás
    
                    System.out.println(socketIO.getData());
                    Thread.sleep(1000);
    
                }
                catch (SocketTimeoutException e) 
                {
                    System.err.println("A server nem érhető el!"); //TODO: lekezelni
                    break;
                }
                catch (Exception e) // TODO: jobb Exception kezelés
                {
                    //System.err.println(e.getMessage());
                    e.printStackTrace();
                }
            }
            socket.close();
            
        }
    
        Server(String _address, int _port)
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
    }
    Server server;

    public class Player
    {
        String name;

        public Player(String _name)
        {
            name = _name;
        }
    }
    ArrayList<Player> players = new ArrayList<>();

    boolean mode = false;

    public class Table 
    {
        public class Coord 
        {
            int x;
            int y;

            Coord(int _x, int _y)
            {
                x=_x;
                y=_y;
            }
        }
        Coord size = new Coord(0,0);

        public class Pos 
        {
            Coord xy;
            byte status;

            Pos(Coord _xy, byte _status)
            {
                xy = _xy;
                status = _status;
            }
        }
        ArrayList<Pos> pos = new  ArrayList<>();
    }
    Table table1 = new Table();
    Table table2 = new Table();

    public Client(String _address, int _port)
    {
        server = new Server(_address, _port);
        new Thread(server).start();
    }
}