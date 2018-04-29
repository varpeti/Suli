package vp.net;

import java.net.*;
import java.io.*;

public class SocketIO 
{
    private DatagramSocket socket;
    byte[] inputB = new byte[1024];
    DatagramPacket inputPacket;

    public SocketIO(DatagramSocket _socket)
    {
        socket = _socket;
    }

    //Egy IP:port szerverre küld egy Stringet
    public void send(String data, InetAddress address, int port) throws IOException
    {
        byte[] outputB = new byte[1024]; 
        outputB = data.getBytes();
        DatagramPacket outputPacket = new DatagramPacket(outputB, outputB.length, address, port);
        socket.send(outputPacket);
    }

    //Visszaküld a kliensnek egy Stringet, elötte kell egy socketIO.receive() !!!
    public void send(String data) throws IOException
    {
        byte[] outputB = new byte[1024]; 
        outputB = data.getBytes();
        DatagramPacket outputPacket = new DatagramPacket(outputB, outputB.length, getAddress(), getPort());
        socket.send(outputPacket);
    }

    //Kérésre, válaszra vár.
    public void receive() throws IOException
    {
        inputB = new byte[1024];
        inputPacket = new DatagramPacket(inputB, inputB.length);
        socket.receive(inputPacket);
    }

    // A socketIO.receive() által kapott adatok getterei, elötte kell a socketIO.receive() !!!

    public InetAddress getAddress()
    {
        return inputPacket.getAddress();
    }

    public int getPort()
    {
        return inputPacket.getPort();
    }

    public String getData()
    {
        return new String (inputB,0,inputPacket.getLength());
    }
}