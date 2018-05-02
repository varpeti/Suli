import vp.game.Client;

public class ClientMain 
{
    public static void main(String[] args) throws InterruptedException
    {
       new Client("localhost",3773);
    }
}