import cs296BookAnalysis.*;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * The driver class for the complete analysis of the book
 */
public class BookAnalysisG06 {

    /**
     * @param args Accepts the name of the book file
     */
    public static void main(String[] args) throws FileNotFoundException, IOException {
        Book mybook = new Book(args[0]);
	System.out.println(mybook.getBookTitle());
	System.out.println(mybook.getBookAuthor());
	BookStatistics bookStats = new BookStatistics(args[0]);
	System.out.println(bookStats.countBookWords());
	System.out.println(bookStats.countBookCharacters());
	String [] sortedCharacters = bookStats.sortBookCharacters();
	for (int i = 0, size = sortedCharacters.length; i < size; ++i)
	    {
		System.out.println(sortedCharacters[i]);
	    }
	// bookStats.determineCharGender(); 
    }
}

