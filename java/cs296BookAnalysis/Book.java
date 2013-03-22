package cs296BookAnalysis;

import java.io.*;

public class Book {
    
	String bookFilename ;
	String author=null,title=null;
	
	public Book(String path) throws FileNotFoundException {
            bookFilename = path; 
 	}

 	public String getBookTitle() throws IOException {
 		
            BufferedReader br ;
            br = new BufferedReader(new FileReader(bookFilename));
            if(title == null)
                    while(true) {
                            String line = br.readLine();
                            if(line.contains("Title:")) {
                                    title=line.substring(7);
                                    br.close();
                                    return title;
                            }
                    }
            else
                    return title;
 	}

	public String getBookAuthor() throws IOException {
 		BufferedReader br ;
                br = new BufferedReader(new FileReader(bookFilename));
 		if(author == null)
	 		while(true) {
	 			String line = br.readLine();
	 			if(line.contains("Author:")) {
	 				author=line.substring(8);
                                        br.close();
	 				return author;
	 			}
	 		}
	 	else
	 		return author;
 	}

 	public void printBookTitle() throws IOException {
            if(title==null) {
                this.getBookTitle();
            }
            System.out.println(title);
 	}

 	public void printBookAuthor() throws IOException {
            if(author==null) {
                this.getBookAuthor();
            }
            System.out.println(author);
 	}

 	public String[] getBookWords() throws IOException {
            BufferedReader br ;
            br = new BufferedReader(new FileReader(bookFilename));
            String temp = null;
            String text = null;
            while(true) {
                temp = br.readLine();
                if(temp == null)
                    break;
                text+=temp;
            }
            br.close();
            return text.split("\\s++");
 	}
 }

