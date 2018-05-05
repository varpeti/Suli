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
import javafx.scene.control.TextFormatter;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.util.converter.NumberStringConverter;
import javafx.stage.Stage;
import javafx.beans.value.*;

public class Scenes 
{   
    static private Message message;
    static private Stage stage;

    //Welcome scene

    static private TextField welcome_name_TextField;

    static private class Welcome_name_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            message.engineWrite(new Message.Packet("setname "+welcome_name_TextField.getText() ));
            stage.setScene(mainmenu());
        }
    }

    static public Scene welcome()
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
        welcome_name_TextField.setOnAction(new Welcome_name_EventHandler()); //Enter

        Button name_Button = new Button("OK");
        grid.add(name_Button, 2, 1);
        name_Button.setOnAction(new Welcome_name_EventHandler()); //Kattintás

        return new Scene(grid, 1024, 512);
    }

    //Main menu scene

    static private class mainmenu_startserver_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            stage.setScene(startserver());
        }
    }

    static private class mainmenu_joingame_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            stage.setScene(joingame());
        }
    }

    static public Scene mainmenu()
    {
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        HBox mainmenu_hbox = new HBox();
        mainmenu_hbox.setAlignment(Pos.CENTER);
        Text mainmenu_Text = new Text("Main Menu");
        mainmenu_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        mainmenu_hbox.getChildren().addAll(mainmenu_Text);
        grid.add(mainmenu_hbox, 0, 0);

        HBox startserver_hbox = new HBox();
        startserver_hbox.setAlignment(Pos.CENTER);
        Button startserver_Button = new Button("Start Server");
        startserver_Button.setOnAction(new mainmenu_startserver_EventHandler());
        startserver_hbox.getChildren().addAll(startserver_Button);
        grid.add(startserver_hbox,0,1);

        HBox joingame_hbox = new HBox();
        joingame_hbox.setAlignment(Pos.CENTER);
        Button joingame_Button = new Button("Join Game");
        joingame_Button.setOnAction(new mainmenu_joingame_EventHandler());
        joingame_hbox.getChildren().addAll(joingame_Button);
        grid.add(joingame_hbox,0,2);

        joingame_Button.setOnAction(new mainmenu_joingame_EventHandler());

        return new Scene(grid, 1024, 512);
    }

    //Start server scene

    static private TextField startserver_players_TextField;
    static private TextField startserver_ship2_TextField;
    static private TextField startserver_ship3_TextField;
    static private TextField startserver_ship4_TextField;
    static private TextField startserver_ship5_TextField;
    static private TextField startserver_port_TextField;

    static private class startserver_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            // TODO ellenőrzés!!! FIXME: Stupid user alert!!!
            message.engineWrite(new Message.Packet("startserver"
                + " " + startserver_players_TextField.getText()
                + " " + startserver_ship2_TextField.getText() 
                + " " + startserver_ship3_TextField.getText() 
                + " " + startserver_ship4_TextField.getText() 
                + " " + startserver_ship5_TextField.getText()
                + " " + startserver_port_TextField.getText()
            ));

            message.engineWrite(new Message.Packet("startclient"
                + " " + "localhost"
                + " " + startserver_port_TextField.getText()
            ));
        }
    }

    static public Scene startserver()
    {
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        Text name_Text = new Text("Settings");
        name_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        grid.add(name_Text, 0, 0, 2, 1);

        Label address_Label = new Label("Players:");
        grid.add(address_Label, 0, 1);
        startserver_players_TextField = new TextField("2");
        startserver_players_TextField.textProperty().addListener(new NumberField(startserver_players_TextField));
        grid.add(startserver_players_TextField, 1, 1);

        Label port_Label = new Label("Server port:");
        grid.add(port_Label, 0, 2);
        startserver_port_TextField = new TextField();
        startserver_port_TextField.textProperty().addListener(new NumberField(startserver_port_TextField));
        startserver_port_TextField.setText("3773");
        grid.add(startserver_port_TextField, 1, 2);

        Label ships_Label = new Label("Ships:");
        grid.add(ships_Label, 0, 3, 2, 1);

        Label ship2_Label = new Label("Small (2):");
        grid.add(ship2_Label, 0, 4);
        startserver_ship2_TextField = new TextField("1");
        startserver_ship2_TextField.textProperty().addListener(new NumberField(startserver_ship2_TextField));
        grid.add(startserver_ship2_TextField, 1, 4);

        Label ship3_Label = new Label("Normal (3):");
        grid.add(ship3_Label, 0, 5);
        startserver_ship3_TextField = new TextField("1");
        startserver_ship3_TextField.textProperty().addListener(new NumberField(startserver_ship3_TextField));
        grid.add(startserver_ship3_TextField, 1, 5);

        Label ship4_Label = new Label("Medium (4):");
        grid.add(ship4_Label, 0, 6);
        startserver_ship4_TextField = new TextField("1");
        startserver_ship4_TextField.textProperty().addListener(new NumberField(startserver_ship4_TextField));
        grid.add(startserver_ship4_TextField, 1, 6);

        Label ship5_Label = new Label("Large (5):");
        grid.add(ship5_Label, 0, 7);
        startserver_ship5_TextField = new TextField("1");
        startserver_ship5_TextField.textProperty().addListener(new NumberField(startserver_ship5_TextField));
        grid.add(startserver_ship5_TextField, 1, 7);

        Button start_Button = new Button("Start Server");
        grid.add(start_Button, 2, 8);
        start_Button.setOnAction(new startserver_EventHandler());

        //TODO: vissza gomb

        return new Scene(grid, 1024, 512);
    }

    // Joing game scene

    static private TextField joingame_address_TextField;
    static private TextField joingame_port_TextField;

    static private class joingame_EventHandler implements EventHandler<ActionEvent>
    {
        @Override
        public void handle(ActionEvent e) 
        {
            // TODO ellenőrzés!!! FIXME: Stupid user alert!!!
            message.engineWrite(new Message.Packet("startclient"
                + " " + joingame_address_TextField.getText()
                + " " + joingame_port_TextField.getText()
            ));
        }
    }

    static public Scene joingame()
    {
        GridPane grid = new GridPane();
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(25, 25, 25, 25));

        Text name_Text = new Text("Settings");
        name_Text.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
        grid.add(name_Text, 0, 0, 2, 1);

        Label address_Label = new Label("Ip/Domain:");
        grid.add(address_Label, 0, 1);
        joingame_address_TextField = new TextField("localhost");
        grid.add(joingame_address_TextField, 1, 1);

        Label port_Label = new Label("Port:");
        grid.add(port_Label, 0, 2);
        joingame_port_TextField = new TextField("3773");
        joingame_port_TextField.textProperty().addListener(new NumberField(joingame_port_TextField));
        grid.add(joingame_port_TextField, 1, 2);

        Button join_Button = new Button("Join");
        grid.add(join_Button, 2, 8);
        join_Button.setOnAction(new joingame_EventHandler());

        //TODO: vissza gomb

        return new Scene(grid, 1024, 512);
    }


    // Number TextField
    static private class NumberField implements ChangeListener<String> 
    {
        private TextField textField;
        @Override
        public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) 
        {
            if (!newValue.matches("\\d+")) 
            {
                textField.setText(newValue.replaceAll("[^\\d]", ""));
            }
        }

        public NumberField(TextField _textField)
        {
            textField = _textField;
        }
    }


    //Settings

    static public void addMessage(Message _message)
    {
        message = _message;
    }

    static public void addStage(Stage _stage)
    {
        stage = _stage;
    }
}