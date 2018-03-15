package vp.svg.picture.components;

import java.util.ArrayList;
import java.io.*;

import vp.io.BuffWriter;

public class Group implements Component {

    private ArrayList<Component> components = new ArrayList<Component>();

    public Group()
    {
        System.out.println("Group");
    }

    public void write(Writer output) throws IOException
    {
        BuffWriter.addNewLine(output,"<g>");

        for (int i=0;i<components.size();i++) 
        {
            components.get(i).write(output);
        }

        BuffWriter.addNewLine(output,"</g>");
    }

    public void addComponent(Component comp)
    {
        components.add(comp);
    }

    public void translate(float dx, float dy)
    {
        for (int i=0;i<components.size();i++){components.get(i).translate(dx,dy);}
        System.out.println("Translate: x:"+dx+" y:"+dy);
    }
    public void flipHorizontal(float axis)
    {
        for (int i=0;i<components.size();i++){components.get(i).flipHorizontal(axis);}
        System.out.println("FlipHorizontal: "+axis);
    }
    public void flipVertical(float axis)
    {
        for (int i=0;i<components.size();i++){components.get(i).flipVertical(axis);}
        System.out.println("FlipVertical: "+axis);
    }
}
