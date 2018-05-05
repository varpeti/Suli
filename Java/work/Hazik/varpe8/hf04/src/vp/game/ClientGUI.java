package vp.game;

import vp.net.Message;
import vp.game.GUI.Scenes;

import javafx.application.Application;
import javafx.stage.Stage;

public class ClientGUI extends Application
{
    private Stage stage;

    @Override
    public void start(Stage primaryStage) 
    {
        stage = primaryStage;
        Scenes.addStage(stage);

        stage.setTitle("Torpedo by Vp");

        stage.setScene(Scenes.welcome());
        stage.show();

        //TODO instant kilépés
    }

    public static void main(String[] args) 
    {
        launch(args);
    }

    static public void addMessage(Message message)
    {
        Scenes.addMessage(message); //Tovább adja
    } 
}