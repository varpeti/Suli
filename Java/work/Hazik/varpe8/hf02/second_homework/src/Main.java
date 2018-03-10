import vp.svg.picture.Picture;

public class Main
{
    public static void main(String[] args) 
    {
        Picture picture = new Picture();
        picture.addComponent("new_group");
        picture.addComponent("add_circle 135 -2.3 -10 ");
        picture.addComponent("add_rectangle 135 -2.3 -10 -34.82");

        try{System.in.read();}catch(Exception e){}
    }
}