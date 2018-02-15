package Matrix;

import java.util.Vector;
import java.util.Arrays;

public class Matrix {
    public Vector< Vector<Integer> > m = new Vector< Vector<Integer> >();

    public Matrix add(Matrix other)
    {
        Matrix ret = new Matrix();
        for (int y = 0;y<this.m.size();y++) {
            Vector<Integer> seg = new Vector<Integer>();
            for (int x = 0;x<this.m.get(0).size();x++) {
                seg.add( this.m.get(y).get(x)+other.m.get(y).get(x) );
            }
            ret.m.add(seg);
        }
        return ret;
    }

    public void new_col(int[] x)
    {
        Vector<Integer> seg = new Vector<Integer>();
        for (int i=0;i<x.length;i++) 
        {
            seg.add(x[i]);    
        }
        this.m.add(seg);
    }

    public Integer get(int x,int y)
    {
        return this.m.get(y).get(x);
    }

    public void print()
    {
        for (int y = 0;y<this.m.size();y++) {
            for (int x = 0;x<this.m.get(0).size();x++) {
                System.out.print(this.m.get(y).get(x) + " ");
            }
            System.out.println();
        }
    }

    public Matrix()
    {
        System.out.println(this);
    }
}