package vp.net;

import java.io.*;
import java.util.*;
import java.net.*;

public class Message 
{   

    static public class DestMsg 
    {
        private InetAddress address;
        private int port;
        private String msg;
        private boolean _isAddressed;

        //Üzenet címmel
        public DestMsg(String _msg, InetAddress _address, int _port)
        {
            address = _address;
            port = _port;
            msg = _msg;
            _isAddressed = true;
        }

        //Üzenet cím nélkül
        public DestMsg(String _msg)
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

    private ArrayList<DestMsg> socket = new ArrayList<>();
    private ArrayList<DestMsg> engine = new ArrayList<>();
    private ArrayList<DestMsg> gui    = new ArrayList<>();

    private Object socketLock = new Object();
    private Object engineLock = new Object();
    private Object guiLock    = new Object();

    public ArrayList<DestMsg> socketRead()
    {
        synchronized (socketLock)
        {
            ArrayList<DestMsg> ret = new ArrayList<DestMsg>(socket);
            socket = new ArrayList<>();
            return ret;
        }
    }

    public void socketWrite(DestMsg add)
    {
        synchronized (socketLock)
        {
            socket.add(add);
        }
    }

    public ArrayList<DestMsg> engineRead()
    {
        synchronized (engineLock)
        {
            ArrayList<DestMsg> ret = new ArrayList<DestMsg>(engine);
            engine = new ArrayList<>();
            return ret;
        }
    }

    public void engineWrite(DestMsg add)
    {
        synchronized (engineLock)
        {
            engine.add(add);
        }
    }

    public ArrayList<DestMsg> guiRead()
    {
        synchronized (guiLock)
        {
            ArrayList<DestMsg> ret = new ArrayList<DestMsg>(gui);
            gui = new ArrayList<>();
            return ret;
        }
    }

    public void guiWrite(DestMsg add)
    {
        synchronized (engineLock)
        {
            gui.add(add);
        }
    }
}