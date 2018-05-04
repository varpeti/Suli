package vp.game;

import vp.net.Message;
import vp.game.GUI.Stages;

import javafx.application.Application;
import javafx.stage.Stage;

public class ClientGUI extends Application
{
    static private Message message;

    @Override
    public void start(Stage primaryStage) 
    {
        primaryStage.setTitle("Torpedo by Vp");
        Stages.welcome(primaryStage);
    }

    public static void main(String[] args) 
    {
        launch(args);
    }

    static public void addMessage(Message _message)
    {
        message = _message;
        Stages.addMessage(message); //Tovább adja
    } 
}