import Matrix.Matrix;
import java.util.Arrays;

public class Main
{
    public static void main(String[] args) 
    {
    	
        Matrix a = new Matrix();
        {Integer[] i = {1,2,3}; a.new_col(i);}
        {Integer[] i = {4,5,6}; a.new_col(i);}
        a.print();
        Matrix b = new Matrix();
        {Integer[] i = {2,1,3}; b.new_col(i);}
        {Integer[] i = {1,2,2}; b.new_col(i);}
        b.print();

        Matrix c = a.add(b);
        c.print();

    }
}