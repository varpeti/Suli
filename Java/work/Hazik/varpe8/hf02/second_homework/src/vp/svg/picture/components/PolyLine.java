package vp.svg.picture.components;

import java.io.*;
import java.util.ArrayList;

import vp.io.BuffWriter;

public class PolyLine implements Component {

    private ArrayList<Float> coords;

    //public PolyLine(Float... coords){}  //Csak azért hogy sexy legyen? Ah nem kell ez nekem, majd másor :D
    
    public PolyLine(ArrayList<Float> _coords)
    {
        coords = new ArrayList<Float>(_coords);
        System.out.println("PolyLine: no:"+coords.size()/2);
    }

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
    
    public float getPointX(int i){return (float)coords.get(i*2);}
    public float getPointY(int i){return (float)coords.get(i*2+1);}
    public int getNumberOfPoints(){return coords.size()/2;}

}
