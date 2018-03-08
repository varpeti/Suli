package hu.ppke.itk.java.homework.second.picture.components;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;

public class Rectangle implements Component {
  public void write(Writer output) throws IOException {
    BufferedWriter bufferedWriter = new BufferedWriter(output);
    String code = "<rect x='" + getTopLeftX() + "' y='" + getTopLeftY() + "' " +
        "" + "width='" + getWidth() + "' height='" + getHeight() + "' " +
        "stroke='black' " + "fill='black' />";
    bufferedWriter.write(code, 0, code.length());
    bufferedWriter.newLine();
    bufferedWriter.flush();
  }
}
