package LessThan10;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Test;

import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;
import org.junit.runner.RunWith;
import static org.junit.Assert.assertEquals;

@RunWith(Parameterized.class)
public class LessThan10_test 
{
    private Integer input;
    private Boolean expcectedOutput;
    
    public LessThan10_test(Integer input, Boolean expcectedOutput)
    {
        this.input = input;
        this.expcectedOutput = expcectedOutput;
    }

    @Parameterized.Parameters
    public static Collection cases()
    {

        return Arrays.asList
        (
            new Object[][] 
            {
                {+00,   true    },
                {+03,   true    },
                {+11,   false   },
                {-11,   true    },
                {999,   false   },
                {+10,   false   },
            }
        );
   }

    @Test
    public void testPrimeNumberChecker() 
    {
        assertEquals( expcectedOutput, LessThan10.islessthan10(input) );
    }
}