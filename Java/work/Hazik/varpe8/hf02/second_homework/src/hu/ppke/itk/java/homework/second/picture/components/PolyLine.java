package hu.ppke.itk.java.homework.second.picture.components;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Writer;

public class PolyLine implements Component {
  public void write(Writer output) throws IOException {
    BufferedWriter bufferedWriter = new BufferedWriter(output);
    StringBuilder codeBuilder = new StringBuilder("<polyline points=\"");
    codeBuilder.append(getPointX(0)).append(',').append(getPointY(0));
    for (int i = 1; i < getNumberOfPoints(); i++) {
      codeBuilder.append(' ').append(getPointX(i)).append(',').append(
          getPointY(i));
    }
    codeBuilder.append("\" style='fill:none;stroke:black;stroke-width:2'/>");
    String code = codeBuilder.toString();
    bufferedWriter.write(code, 0, code.length());
    bufferedWriter.newLine();
    bufferedWriter.flush();
  }
}
