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
	BS.determineCharGender();
	BS.countBookWords();
	BS.countBookCharacters();
    }

    /**
     * Used by the findHero and findHeroine functions
     * @param gender The gender of the character
     */
    private String findProtagonist (String gender)
    {
	String protagonist = "";
	int maxFreq = 0;
	for (int i = 0, size = BS.firstNamesArray.length; i < size; ++i)
	    {
		String candidateForProtagonist = BS.firstNamesArray[i];
		if (BS.getGender.get (candidateForProtagonist).equals(gender))
		    if (BS.freq1.get (candidateForProtagonist) > maxFreq)
			{
			    protagonist = candidateForProtagonist;
			    maxFreq = BS.freq1.get (candidateForProtagonist);
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
	return this.findProtagonist ("Male");
    }

    /**
     * Uses findProtagonist function to find the heroine of the novel
     * @see FindActors#findProtagonist
     */
    public String findHeroine ()
    {
	return this.findProtagonist ("Female");
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
	for (int i = 0, size = BS.firstNamesArray.length; i < size; ++i)
	    {
		String candidateForVillain = BS.firstNamesArray[i];
		if (candidateForVillain != hero && candidateForVillain != heroine)
		    if (BS.freq1.get (candidateForVillain) > maxFreq)
			{
			    villain = candidateForVillain;
			    maxFreq = BS.freq1.get (candidateForVillain);
			}
	    }
	return villain;	
    }
}