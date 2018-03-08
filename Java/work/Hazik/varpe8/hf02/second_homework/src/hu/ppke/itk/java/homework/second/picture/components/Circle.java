package hu.ppke.itk.java.homework.second.picture.components;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;

public class Circle implements Component {
    public void write(Writer output) throws IOException 
    {
        BufferedWriter bufferedWriter = new BufferedWriter(output);
        String code = "<circle cx='" + getCenterX() + "' cy='" + getCenterY() + "' r='" +
            getRadius() + "' stroke='black' fill='black' />";
        bufferedWriter.write(code, 0, code.length());
        bufferedWriter.newLine();
        bufferedWriter.flush();
    }
    public float getCenterX(){return (float)0.0;};
    public float getCenterY(){return (float)0.0;};
    public float getRadius(){return (float)0.0;};
}
