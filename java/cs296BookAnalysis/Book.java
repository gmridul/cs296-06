package cs296BookAnalysis;

import java.io.*;

/** 
 * Represents the book object
 * Contains the name, author, title and words in the book
 */
public class Book {

    String bookFileName;
    String author = null, title = null;
    String[] words = null;
    String text = null;

    /**
     * The constructor function for the class
     */
    public Book(String path) throws FileNotFoundException {
        bookFileName = path;
    }
    
    private String getContent() throws FileNotFoundException, IOException {
        if(text==null){
            BufferedReader br;
            br = new BufferedReader(new FileReader(bookFileName));
            String temp = null;
            while (true) {
                temp = br.readLine();
                if (temp == null) {
                    break;
                }
                temp = temp.replace(",", " ");
                temp = temp.replace("-", " ");
                temp = temp.replace("\"", "");
                temp = temp.replace(";", " ");
                temp = temp.replace(":", " ");
                text += temp + " ";
            }
            br.close();
        }
        return text;
    }

    /**
     * Finds the title of the book
     */
    public String getBookTitle() throws IOException {
        BufferedReader br;
        br = new BufferedReader(new FileReader(bookFileName));
        if (title == null) {
            while (true) {
                String line = br.readLine();
                if (line.contains("Title:")) {
                    br.close();
                    title = line.substring(7);
                    return title;
                }
            }
        } else {
            return title;
        }
    }

    /**
     * Finds the author of the book
     */
    public String getBookAuthor() throws IOException {
        BufferedReader br;
        br = new BufferedReader(new FileReader(bookFileName));
        if (author == null) {
            while (true) {
                String line = br.readLine();
                if (line.contains("Author:")) {
                    author = line.substring(8);
                    br.close();
                    return author;
                }
            }
        } else {
            return author;
        }
    }

    /**
     * Prints the title of the book by calling getBookTitle
     * @see Book#getBookTitle
     */
    public void printBookTitle() throws IOException {
        if (title == null) {
            this.getBookTitle();
        }
	System.out.println("The title of the book is ");
        System.out.println(title);
    }

    /**
     * Prints the author of the book by calling getBookAuthor
     * @see Book#getBookAuthor
     */
    public void printBookAuthor() throws IOException {
        if (author == null) {
            this.getBookAuthor();
        }
	System.out.println("The author of the book is ");
        System.out.println(author);
    }

    /**
     * Gets all the words of the book in the array words by calling getContent
     * @see Book#getContent
     */
    public String[] getBookWords() throws IOException {
        if (words != null) {
            return words;
        }
        else if(text==null) {
            this.getContent();
        }
        words = text.split(" ");
        
        return words;
    }

    /**
     * Determines all the words in the novel file
     */
    public String[] getBookCharacters() throws IOException {
        BufferedReader br;
        br = new BufferedReader(new FileReader(bookFileName));
        if (words == null) {
            words = getBookWords();
        }
        return null;
    }
}

