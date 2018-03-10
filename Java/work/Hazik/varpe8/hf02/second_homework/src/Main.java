import vp.svg.picture.Picture;
import java.io.Writer;

public class Main
{
    public static void main(String[] args) 
    {
        Picture picture = new Picture();
        try{
            picture.build(args[0]);
            picture.write(args[1]);
        }catch (Exception e) {
            e.printStackTrace();
        }
        

        try{System.in.read();}catch(Exception e){}
    }
}