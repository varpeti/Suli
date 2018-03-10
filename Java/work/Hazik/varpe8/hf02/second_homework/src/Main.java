import vp.svg.picture.Picture;
import java.io.Writer;

public class Main
{
    public static void main(String[] args) 
    {
        Picture picture = new Picture();
        try{
            picture.addComponent("new_group");
            picture.addComponent("add_circle -5 10 10");
            picture.addComponent("add_rectangle 20 10.5 5 5");
            picture.write("out.svg");
        }catch (Exception e) {
            e.printStackTrace();
        }
        

        try{System.in.read();}catch(Exception e){}
    }
}