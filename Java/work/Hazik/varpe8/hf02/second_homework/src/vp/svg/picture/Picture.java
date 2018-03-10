package vp.svg.picture;

import java.util.regex.*;
import java.util.*;
import java.io.*;

import vp.svg.picture.components.*;
import vp.svg.SyntaxErrorException;
import vp.io.BuffWriter;


public class Picture {
    private ArrayList<Group> groups = new ArrayList<Group>();
    static private ArrayList<String> patterns = new ArrayList<String>() //Tetszik ez az anonymous inner class dolog.
    {{
        add("(add_line_segments) ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*)(.*)");
        add("(add_circle) ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*)(\\s*)");
        add("(add_rectangle) ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*) ([\\d\\-\\.]*)(\\s*)");
        add("(new_group)(\\s*)");
        add("(translate) ([\\d\\-\\.]*) ([\\d\\-\\.]*)(\\s*)");
        add("(flip_vertical) ([\\d\\-\\.]*)(\\s*)");
        add("(flip_horizontal) ([\\d\\-\\.]*)(\\s*)");
    }};
    static private ArrayList<String> pcom = new ArrayList<String>()
    {{
        add("add_line_segments");
        add("add_circle");
        add("add_rectangle");
        add("new_group");
        add("translate");
        add("flip_vertical");
        add("flip_horizontal");
    }};

    public Picture()
    {
    }

    private void s2c(String command) throws SyntaxErrorException //A egy sorból kiszedi a commandot és a paramétereket.
    {   
        for (int i=0;i<patterns.size();i++) 
        {
            Matcher m = Pattern.compile(patterns.get(i)).matcher(command); //Megtalálható-e a minta benne
            if (!m.find()) continue;

            for (int j=1;j<pcom.size();j++) //Megkeresi hogy melyik
            {
                if (!Objects.equals( pcom.get(j), m.group(1) ) ) continue;

                if (j!=3 && groups.size()<1) throw new SyntaxErrorException("A group is missing!"); //Ha még nincs group
                
                switch (j) 
                {
                    case 0:

                        break;
                    case 1:
                        groups.get(groups.size()-1).addComponent( new Circle( Float.parseFloat(m.group(2)), Float.parseFloat(m.group(3)), Float.parseFloat(m.group(4)) ) );
                        break;
                    case 2:
                        groups.get(groups.size()-1).addComponent( new Rectangle( Float.parseFloat(m.group(2)), Float.parseFloat(m.group(3)), Float.parseFloat(m.group(4)), Float.parseFloat(m.group(5)) ) );
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
        }
        throw new SyntaxErrorException("Unrecognizable command or missing/invaild parameters.");
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
