import cs296BookAnalysis.*;
import java.io.FileNotFoundException;
import java.io.IOException;


public class BookAnalysisG06 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws FileNotFoundException, IOException {
        Book mybook = new Book(args[0]);
	System.out.println(mybook.getBookTitle());
	System.out.println(mybook.getBookAuthor());
	BookStatistics bookStats = new BookStatistics(args[0]);
	System.out.println(bookStats.countBookWords());
	System.out.println(bookStats.findBookCharacters()); 
    }
}

