package vp.svg.picture;

import java.util.regex.*;
import java.util.*;

import vp.svg.picture.components.*;


public class Picture {
    private ArrayList<Component> components = new ArrayList<Component>();
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

    public Boolean addComponent(String command) //A Szövegből kiszedi hogy melyik command és a paramétereket.
    {   
        for (int i=0;i<patterns.size();i++) 
        {
            Matcher m = Pattern.compile(patterns.get(i)).matcher(command); //Megtalálható-e a minta benne
            if (!m.find()) continue;

            for (int j=1;j<pcom.size();j++) //Megkeresi hogy melyik
            {
                if (!Objects.equals( pcom.get(j), m.group(1) ) ) continue;
                
                switch (j) 
                {
                    case 0:
                        //Ah miért kell????
                        break;
                    case 1:
                        components.add(new Circle( Float.parseFloat(m.group(2)), Float.parseFloat(m.group(3)), Float.parseFloat(m.group(4)) ) );
                        break;
                    case 2:
                        components.add(new Rectangle( Float.parseFloat(m.group(2)), Float.parseFloat(m.group(3)), Float.parseFloat(m.group(4)), Float.parseFloat(m.group(5)) ) );
                        break;
                    case 3:
                        components.add(new Group());
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                }
                return true;
            }
        }
        return false;
    }   
}
