package vp.svg.picture.components;

import java.io.*;

import vp.io.BuffWriter;

public class PolyLine implements Component {
    public void write(Writer output) throws IOException 
    {
        StringBuilder codeBuilder = new StringBuilder("<polyline points=\"");
        codeBuilder.append(getPointX(0)).append(',').append(getPointY(0));
        for (int i = 1; i < getNumberOfPoints(); i++) 
        {
            codeBuilder.append(' ').append(getPointX(i)).append(',').append(getPointY(i));
        }
        codeBuilder.append("\" style='fill:none;stroke:black;stroke-width:2'/>");
        
        BuffWriter.addNewLine(output,codeBuilder.toString());
    }
    
    public float getPointX(int i){return (float)0.0;}
    public float getPointY(int i){return (float)0.0;}
    public int getNumberOfPoints(){return 0;}

}
