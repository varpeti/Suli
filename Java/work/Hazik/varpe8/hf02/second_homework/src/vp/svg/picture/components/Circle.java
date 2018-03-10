package vp.svg.picture.components;


import java.io.*;

import vp.io.BuffWriter;

public class Circle implements Component {
    float x,y,r;

    public Circle(float _x, float _y, float _r)
    {
        x=_x; y=_y; r=_r;
        System.out.println("Circle: x:"+x+" y:"+y+" r:"+r);
    }

    public void write(Writer output) throws IOException 
    {
        BuffWriter.addNewLine(output,"<circle cx='" + getCenterX() + "' cy='" + getCenterY() + "' r='" + getRadius() + "' stroke='black' fill='black' />");
    }

    public float getCenterX(){return x;}
    public float getCenterY(){return y;}
    public float getRadius(){return r;}
}
