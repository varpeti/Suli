package hu.ppke.itk.java.homework.second.picture.components;

import java.io.Writer;
import java.io.IOException;

interface Component {
   public void write(Writer output) throws IOException;
   default public void translate(float dx, float dy){};
   default public void flipHorizontal(float axis){};
   default public void flipVertical(float axis){};

}