import vp.game.*;
import vp.net.*;

public class Main
{
    public static void main(String[] args) throws Exception
    {
        Message server_message = new Message();
        Server server = new Server(3773,server_message);
        ServerEngine server_engine = new ServerEngine(server_message);
        
        Thread.sleep(1000);
        
        Message client_message = new Message();
        Client client = new Client("localhost",3773,client_message);
        ClientEngine client_engine = new ClientEngine(client_message);
        client_message.engineWrite(new Message.Packet("setname Noah"));

        Thread.sleep(1000);

        Message client_message2 = new Message();
        Client client2 = new Client("localhost",3773,client_message2);
        ClientEngine client_engine2 = new ClientEngine(client_message2); 
        client_message2.engineWrite(new Message.Packet("setname Izzy"));
        
    }
}