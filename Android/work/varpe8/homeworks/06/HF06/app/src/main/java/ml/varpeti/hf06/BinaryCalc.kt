package ml.varpeti.hf06

class BinaryCalc
{
    fun add(a : CharSequence, b : CharSequence) : CharSequence
    {
        val ai = Integer.parseInt(a.toString(),2)
        val bi = Integer.parseInt(b.toString(),2)
        return (ai+bi).toString(2)
    }

    fun sub(a : CharSequence, b : CharSequence) : CharSequence
    {
        val ai = Integer.parseInt(a.toString(),2)
        val bi = Integer.parseInt(b.toString(),2)
        return (ai-bi).toString(2)
    }
}