package vp.net;

import java.io.*;
import java.util.*;
import java.net.*;

public class Message 
{   

    static public class Packet 
    {
        private InetAddress address;
        private int port;
        private String msg;
        private boolean _isAddressed;

        //Üzenet címmel
        public Packet(String _msg, InetAddress _address, int _port)
        {
            address = _address;
            port = _port;
            msg = _msg;
            _isAddressed = true;
        }

        //Üzenet cím nélkül, pl cliens->szerver, vagy broadcast server->cliensek
        public Packet(String _msg)
        {
            msg = _msg;
            _isAddressed = false;
        }

        //Getterek
        public InetAddress getAddress()
        {
            return address;
        }
        public int getPort()
        {
            return port;
        }
        public String getMsg()
        {
            return msg;
        }
        public boolean isAddressed()
        {
            return _isAddressed;
        }

    }

    private ArrayList<Packet> socket = new ArrayList<>();
    private ArrayList<Packet> engine = new ArrayList<>();
    private ArrayList<Packet> gui    = new ArrayList<>();

    private Object socketLock = new Object();
    private Object engineLock = new Object();
    private Object guiLock    = new Object();

    public ArrayList<Packet> socketRead()
    {
        synchronized (socketLock)
        {
            ArrayList<Packet> ret = new ArrayList<Packet>(socket);
            socket = new ArrayList<>();
            return ret;
        }
    }

    public void socketWrite(Packet add)
    {
        synchronized (socketLock)
        {
            socket.add(add);
        }
    }

    public ArrayList<Packet> engineRead()
    {
        synchronized (engineLock)
        {
            ArrayList<Packet> ret = new ArrayList<Packet>(engine);
            engine = new ArrayList<>();
            return ret;
        }
    }

    public void engineWrite(Packet add)
    {
        synchronized (engineLock)
        {
            engine.add(add);
        }
    }

    public ArrayList<Packet> guiRead()
    {
        synchronized (guiLock)
        {
            ArrayList<Packet> ret = new ArrayList<Packet>(gui);
            gui = new ArrayList<>();
            return ret;
        }
    }

    public void guiWrite(Packet add)
    {
        synchronized (engineLock)
        {
            gui.add(add);
        }
    }
}