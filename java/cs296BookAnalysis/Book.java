package cs296BookAnalysis;

import java.io.*;

public class Book {

    String bookFileName;
    String author = null, title = null;
    String[] words = null;
    String text = null;

    public Book(String path) throws FileNotFoundException {
        bookFileName = path;
    }
    
    String getContent() throws FileNotFoundException, IOException {
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

    public void printBookTitle() throws IOException {
        if (title == null) {
            this.getBookTitle();
        }
        System.out.println(title);
    }

    public void printBookAuthor() throws IOException {
        if (author == null) {
            this.getBookAuthor();
        }
        System.out.println(author);
    }

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

    public String[] getBookCharacters() throws IOException {
        BufferedReader br;
        br = new BufferedReader(new FileReader(bookFileName));
        if (words == null) {
            words = getBookWords();
        }
        return null;
    }
}
