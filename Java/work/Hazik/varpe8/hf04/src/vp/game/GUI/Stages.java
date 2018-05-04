package vp.game.GUI;

import vp.net.Message;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class Stages 
{   
    static private Message message;

    static private TextField welcome_name_TextField;
    static private class Welcome_name_TextField_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            message.engineWrite(new Message.Packet("setname "+welcome_name_TextField.getText() ));
        }
    }

    static public void welcome(Stage primaryStage)
    {
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        Text name_Text = new Text("Welcome");
        name_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        grid.add(name_Text, 0, 0, 2, 1);

        Label name_Label = new Label("User Name:");
        grid.add(name_Label, 0, 1);

        welcome_name_TextField = new TextField();
        grid.add(welcome_name_TextField, 1, 1);

        Button name_Button = new Button("OK");
        grid.add(name_Button, 2, 1);

        name_Button.setOnAction(new Welcome_name_TextField_EventHandler());

        Scene scene = new Scene(grid, 1024, 512);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    static private class mainmenu_startserver_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            
        }
    }

    static private class mainmenu_joingame_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            
        }
    }

    static public void mainmenu(Stage primaryStage)
    {
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        Text mainmenu_Text = new Text("Main Menu");
        mainmenu_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        grid.add(mainmenu_Text, 0, 0, 2, 1);

        Button startserver_Button = new Button("Start Server");
        grid.add(startserver_Button, 1, 1);

        startserver_Button.setOnAction(new mainmenu_startserver_EventHandler());

        Button joingame_Button = new Button("Join Game");
        grid.add(joingame_Button, 1, 1);

        joingame_Button.setOnAction(new mainmenu_joingame_EventHandler());

        Scene scene = new Scene(grid, 1024, 512);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    static public void addMessage(Message _message)
    {
        message = _message;
    }
}