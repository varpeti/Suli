package vp.svg.picture;

import java.util.regex.*;
import java.util.*;
import java.io.*;

import vp.svg.picture.components.*;
import vp.svg.SyntaxErrorException;
import vp.io.BuffWriter;


public class Picture {
    private ArrayList<Group> groups = new ArrayList<Group>();
    static private ArrayList<String> pcom = new ArrayList<String>() //Tetszik ez az anonymous inner class dolog.
    {{
        add("(add_line_segments)(.*)");
        add("(add_circle)(.*)");
        add("(add_rectangle)(.*)");
        add("(new_group)(.*)");
        add("(translate)(.*)");
        add("(flip_vertical)(.*)");
        add("(flip_horizontal)(.*)");
        add("(merge)(.*)");
        add("(undo)(.*)");
    }};
    static private ArrayList<String> parg = new ArrayList<String>() 
    {{
        add(" ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*)(.*)");
        add(" ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*)(\\s*)");
        add(" ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*)(\\s*)");
        add("(\\s*)");
        add(" ([\\d\\-\\.]*) ([\\d\\-\\.]*)(\\s*)");
        add(" ([\\d\\-\\.]*)(\\s*)");
        add(" ([\\d\\-\\.]*)(\\s*)");
        add("(\\s*)");
        add("(\\s*)");
    }};

    public Picture()
    {
    }

    private void s2c(String command) throws SyntaxErrorException //A egy sorból kiszedi a commandot és a paramétereket.
    {   
        for (int i=0;i<pcom.size();i++) 
        {
            Matcher mc = Pattern.compile(pcom.get(i)).matcher(command); //Megtalálható-e command benne
            if (!mc.find()) continue;

            Matcher ma = Pattern.compile(parg.get(i)).matcher(mc.group(2)); // Argumentumok
            
            if (!ma.find()) throw new SyntaxErrorException("Invalid arguments!");

            if (i!=3 && groups.size()<1) throw new SyntaxErrorException("A group is missing!"); //Ha még nincs group
                    
            switch (i)
            {
                case 0: 
                    ArrayList<Float> args = new ArrayList<Float>();
                    args.add(Float.parseFloat(ma.group(1))); args.add(Float.parseFloat(ma.group(2))); //x1 y1
                    args.add(Float.parseFloat(ma.group(3))); args.add(Float.parseFloat(ma.group(4))); //x2 y2

                    Matcher mta = Pattern.compile("\\s*[\\d\\-\\.]*").matcher(ma.group(5)); // Ha több van mint 2 pont.

                    while(mta.find())  //Azokat is bearakja
                        try{ args.add(Float.parseFloat(mta.group())); }catch (Exception e) {}

                    if (args.size()%2==1) throw new SyntaxErrorException("Invalid arguments! (Odd number of args)");
                        
                    groups.get(groups.size()-1).addComponent( new PolyLine(args) );
                    break;
                case 1:
                    groups.get(groups.size()-1).addComponent( new Circle( Float.parseFloat(ma.group(1)), Float.parseFloat(ma.group(2)), Float.parseFloat(ma.group(3)) ) );
                    break;
                case 2:
                    groups.get(groups.size()-1).addComponent( new Rectangle( Float.parseFloat(ma.group(1)), Float.parseFloat(ma.group(2)), Float.parseFloat(ma.group(3)), Float.parseFloat(ma.group(4)) ) );
                    break;
                case 3:
                    groups.add(new Group() );
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
            }
            return;
        }
        throw new SyntaxErrorException("Unrecognizable command!");
    } 

    public void build(String filename) throws IOException
    {
        try ( BufferedReader br = new BufferedReader(new FileReader(filename)) ) //Elég idióta a szintaxisa, lényeg h bezárja ha minden jól megy.
        { 
            String line;
    
            while ( (line = br.readLine()) != null)
            {
               try{
                    System.out.println(line);
                    s2c(line);
                    System.out.println("");
                }catch (SyntaxErrorException e) {
                    e.printStackTrace();
                } 
            }
        }
    }

    public void write(String filename) throws IOException
    {
        FileWriter out = new FileWriter(filename);
        
        BuffWriter.addNewLine(out,"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>");
        BuffWriter.addNewLine(out,"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">");
        
        
        for (int i=0;i<groups.size();i++) 
        {
            groups.get(i).write(out);
        }

        BuffWriter.addNewLine(out,"</svg>");
    }
}
