import cs296BookAnalysis.*;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * The driver class for the complete analysis of the book
 */
public class BookAnalysisG06 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws FileNotFoundException, IOException 
    {
        Book mybook = new Book(args[0]);
	System.out.println(mybook.getBookTitle());
	System.out.println(mybook.getBookAuthor());
	BookStatistics bookStats = new BookStatistics(args[0]);
	System.out.println(bookStats.countBookWords());
	System.out.println(bookStats.countBookCharacters());
	String [] sortedCharacters = bookStats.sortBookCharacters();
	System.out.println("The characters in sorted order are :- ");
	for (int i = 0, size = sortedCharacters.length; i < size; ++i)
	    {
		System.out.println(sortedCharacters[i]);
	    }
	FindActors myactors = new FindActors(args[0]);
	System.out.println("Hero : " + myactors.findHero());
	System.out.println("Heroine : " + myactors.findHeroine());
	System.out.println("Villain : " + myactors.findVillain());
    }
}

