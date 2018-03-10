package vp.svg.picture.components;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;

public class Rectangle implements Component {

    public Rectangle(float _x, float _y, float _w, float _h)
    {
        System.out.println("Rectangle: x:"+_x+" y:"+_y+" w:"+_w+" h:"+_h);
    }


    public void write(Writer output) throws IOException 
    {
        BufferedWriter bufferedWriter = new BufferedWriter(output);
        String code = "<rect x='" + getTopLeftX() + "' y='" + getTopLeftY() + "' " +
            "" + "width='" + getWidth() + "' height='" + getHeight() + "' " +
            "stroke='black' " + "fill='black' />";
        bufferedWriter.write(code, 0, code.length());
        bufferedWriter.newLine();
        bufferedWriter.flush();
    }
    public float getTopLeftX(){return (float)0.0;}
    public float getTopLeftY(){return (float)0.0;}

    public float getHeight(){return (float)0.0;}
    public float getWidth(){return (float)0.0;}
}
