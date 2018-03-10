package vp.svg.picture.components;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;

public interface Component {
   public void write(Writer output) throws IOException;
   default public void translate(float dx, float dy){};
   default public void flipHorizontal(float axis){};
   default public void flipVertical(float axis){};

}