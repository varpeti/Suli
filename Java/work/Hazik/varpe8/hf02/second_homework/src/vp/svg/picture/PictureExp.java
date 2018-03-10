package vp.svg.picture;

public class PictureExp extends Exception {
    public PictureExp() { super(); }
    public PictureExp(String message) { super(message); }
    public PictureExp(String message, Throwable cause) { super(message, cause); }
    public PictureExp(Throwable cause) { super(cause); }
}