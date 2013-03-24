package cs296BookAnalysis;

import java.io.*;
import java.util.*;

/**
 * Finds the hero, heroine and villain of the book
 * @see Book
 * @see BookStatistics
 */
public class FindActors {
    BookStatistics BS;
    /**
     * @param path The path of the book file
     * Creates a new BookStatistics object
     * @see BookStatistics
     */
    public FindActors (String path) throws FileNotFoundException, IOException
    {
	BS = new BookStatistics(path);
    }

    /**
     * Used by the findHero and findHeroine functions
     * @param gender The gender of the character
     */
    public String findProtagonist (String gender)
    {
	String protagonist = "";
	int maxFreq = 0;
	for (int i = 0, size = BS.sortedCharacters.length; i < size; ++i)
	    {
		String candidateForProtagonist = BS.sortedCharacters[i];
		if (BS.getGender.get (candidateForProtagonist) == gender)
		    if (BS.result.get (candidateForProtagonist) > maxFreq)
			{
			    protagonist = candidateForProtagonist;
			    maxFreq = BS.result.get (candidateForProtagonist);
			}
	    }
	return protagonist;
    }

    /**
     * Uses findProtagonist function to find the hero of the novel
     * @see FindActors#findProtagonist
     */
    public String findHero ()
    {
	return this.findProtagonist ("M");
    }

    /**
     * Uses findProtagonist function to find the heroine of the novel
     * @see FindActors#findProtagonist
     */
    public String findHeroine ()
    {
	return this.findProtagonist ("F");
    }

    /**
     * Finds the villain of the novel
     */
    public String findVillain ()
    {
	String hero = this.findHero ();
	String heroine = this.findHeroine ();
	String villain = "";
	int maxFreq = 0;
	for (int i = 0, size = BS.sortedCharacters.length; i < size; ++i)
	    {
		String candidateForVillain = BS.sortedCharacters[i];
		if (candidateForVillain != hero && candidateForVillain != heroine)
		    if (BS.result.get (candidateForVillain) > maxFreq)
			{
			    villain = candidateForVillain;
			    maxFreq = BS.result.get (candidateForVillain);
			}
	    }
	return villain;	
    }
}