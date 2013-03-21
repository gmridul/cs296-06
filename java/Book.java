package cs296BookAnalysis;

import java.utils.*;
import java.io.*;

public class Book {

	BufferedReader br ;
	String bookFilename ;
	String author=null,title=null;
	
	Book(String path) {
		bookFilename = new String(path); 
 		br = new BufferedReader(new FileReader(path));
 	}

 	public String getBookTitle() {
 		
 		if(title = null)
	 		while(1) {
	 			String line = br.readLine();
	 			if(line.contains("Title:")) {
	 				title=line.substring(7);
	 				return title;
	 			}
	 		}
	 	else
	 		return title;
 	}

	public String getBookAuthor() {
 		
 		if(author=null)
	 		while(1) {
	 			String line = br.readLine();
	 			if(line.contains("Author:")) {
	 				author=line.substring(8);
	 				return author;
	 			}
	 		}
	 	else
	 		return author;
 	}

 	public void printBookTitle() {
 		System.out.println(title);
 	}

 	public void printBookAuthor() {
 		System.out.println(author);
 	}

 	public String[] getBookWords() {
 		String temp = null;
 		String text = null;
 		while(temp = br.readLine() != null) {
 			text+=temp;
 		}
 		return text.split("\\s++");
 	}
 }

		/*try {
 
 
			br = new BufferedReader(new FileReader("C:\\testing.txt"));
 
			while ((sCurrentLine = br.readLine()) != null) {
				System.out.println(sCurrentLine);
			}
 
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (br != null)br.close();
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
 
	}*/
