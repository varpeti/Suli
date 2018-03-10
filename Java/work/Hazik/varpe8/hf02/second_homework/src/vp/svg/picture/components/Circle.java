package vp.svg.picture.components;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;

public class Circle implements Component {

    public Circle(float centerX, float centerY, float radius)
    {
        System.out.println("Circle: x:"+centerX+" y:"+centerY+" r:"+radius);
    }

    public void write(Writer output) throws IOException 
    {
        BufferedWriter bufferedWriter = new BufferedWriter(output);
        String code = "<circle cx='" + getCenterX() + "' cy='" + getCenterY() + "' r='" +
            getRadius() + "' stroke='black' fill='black' />";
        bufferedWriter.write(code, 0, code.length());
        bufferedWriter.newLine();
        bufferedWriter.flush();
    }
    public float getCenterX(){return (float)0.0;}
    public float getCenterY(){return (float)0.0;}
    public float getRadius(){return (float)0.0;}
}
