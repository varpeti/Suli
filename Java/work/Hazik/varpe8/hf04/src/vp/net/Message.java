package vp.net;

import java.io.*;
import java.util.*;

public class Message 
{   
    private ArrayList<String> socket    = new ArrayList<>();
    private ArrayList<String> engine    = new ArrayList<>();
    private ArrayList<String> gui       = new ArrayList<>();

    private Object socketLock = new Object();
    private Object engineLock = new Object();
    private Object guiLock    = new Object();

    public ArrayList<String> socketRead()
    {
        synchronized (socketLock)
        {
            ArrayList<String> ret = new ArrayList<String>(socket);
            socket = new ArrayList<>();
            return ret;
        }
    }

    public void socketWrite(String add)
    {
        synchronized (socketLock)
        {
            socket.add(add);
        }
    }

    public ArrayList<String> engineRead()
    {
        synchronized (engineLock)
        {
            ArrayList<String> ret = new ArrayList<String>(engine);
            engine = new ArrayList<>();
            return ret;
        }
    }

    public void engineWrite(String add)
    {
        synchronized (engineLock)
        {
            engine.add(add);
        }
    }

    public ArrayList<String> guiRead()
    {
        synchronized (guiLock)
        {
            ArrayList<String> ret = new ArrayList<String>(gui);
            gui = new ArrayList<>();
            return ret;
        }
    }

    public void guiWrite(String add)
    {
        synchronized (engineLock)
        {
            gui.add(add);
        }
    }
}