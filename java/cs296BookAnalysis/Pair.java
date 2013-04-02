/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package cs296BookAnalysis;
import java.io.*;
/**
 * represent a pair of two strings
 * @author mridul
 */
class Pair {
    String l,r;
    /** The constructor initialises both l and r to empty strings
     */
    public Pair() {
	l="";
	r="";
    }
    
    /** Sets the first argument of the pair
     */
    public void setl(String s) {
	l=s;
    }

    /** Sets the second argument of the pair
     */
    public void setr(String s) {
	r=s;
    }
  
    /** Gives the first argument of the pair
     */
    public String getl()
    {
	return l;
    }

    /** Gives the second argument of the pair
     */
    public String getr()
    {
	return r;
    }
}

