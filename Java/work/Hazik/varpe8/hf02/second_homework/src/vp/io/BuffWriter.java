package vp.io;

import java.io.*;

public class BuffWriter {
    static public void addNewLine(Writer writer,String line) throws IOException
    {
        BufferedWriter bufferedWriter = new BufferedWriter(writer);
        bufferedWriter.write(line, 0, line.length());
        bufferedWriter.newLine();
        bufferedWriter.flush();
    }
}