import vp.game.*;
import vp.net.*;

public class Main 
{
    public static void main(String[] args) throws Exception
    {
        Message server_message = new Message();
        Server server = new Server(3773,server_message);
        ServerEngine server_engine = new ServerEngine(server_message);
        
        
        Message client_message = new Message();
        Client client = new Client("localhost",3773,client_message);
        ClientEngine client_engine = new ClientEngine(client_message); 
        
    }
}