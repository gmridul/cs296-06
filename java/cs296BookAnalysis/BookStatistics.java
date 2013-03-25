package cs296BookAnalysis;

import java.io.*;
import java.util.*;

public class BookStatistics {

    Book B;
    int count = 0;
    Map<String, Integer> result = new TreeMap<String, Integer>();
    Set<String> firstNames;

    public BookStatistics(String path) throws FileNotFoundException, IOException {
        B = new Book(path);
        B.getBookWords();
        result = new HashMap<String, Integer>();
    }

    public int countBookWords() {
        for (int i = 0, size = B.words.length; i < size; ++i) {
            if (B.words[i].length() != 0) {
                count++;
            }
        }
        return count;
    }
	
	private int min(int a, int b) {
		if(a>b) { return b;} 
		return a;
	}
	private int max(int a, int b) {
		if(a<b) { return b;} 
		return a;
	}
    private void findBookCharacters() {
        ArrayList<String> characters = new ArrayList<String>();
        for (int i = 1, size = B.words.length; i < size; ++i) {
            if (B.words[i - 1].contains("\"") || B.words[i - 1].contains("?") || B.words[i - 1].contains("!") && B.words[i - 1].contains(".")) {
                continue;
            }
            if (B.words[i].length() != 0) {
                if (Character.isUpperCase(B.words[i].charAt(0))) {
                    characters.add(B.words[i]);
                }
            }
        }
        String[] newCharacters = new String[characters.size()];
        characters.toArray(newCharacters);
        Map<String, Integer> freq = new HashMap<String, Integer>();
        for (int i = 0, size = newCharacters.length; i < size; ++i) {
            String str = newCharacters[i];
            str = str.replace("?", "");
            str = str.replace(".", "");
            str = str.replace("!", "");
            str = str.replace("'s", "");
            str = str.toLowerCase();
            Integer numTimes = freq.get(str);
            if (numTimes == null) {
                freq.put(str, 1);
            } else {
                freq.put(str, numTimes + 1);
            }
        }

        Set<String> filtered_characters = new HashSet<String>();
        String[] specialWords = {"a", "an", "is", "are", "the", "this", "oh", "of", "for", "yes", "no", "with", "not", "he", "she", "project", "in", "what", "his", "her", "there", "their", "where", "how", "why", "when", "which", "come", "go", "to", "it", "and", "", "mr", "mrs", "you", "that", "but", "chapter", "i", "if", "on", "they", "at", "as", "here", "i'll", "i'm", "after", "gutenberg"};
        Set<String> specialWordsSet = new HashSet<String>(Arrays.asList(specialWords));
        Set<String> keys = freq.keySet();
        for (String s : keys) {
            if (freq.get(s) > 30) {
                if (specialWordsSet.contains(s)) {
                    continue;
                }
                filtered_characters.add(s);
            }
        }

        Map<String, Integer> fullNames = new HashMap<String, Integer>();
        firstNames = new HashSet<String>();
        Set<String> lastNames = new HashSet<String>();

        for (int i = 1, size = B.words.length; i < size; ++i) {
            String str1 = B.words[i - 1];
            str1 = str1.replace("'s", "");
            str1 = str1.replace("?", "");
            str1 = str1.replace(".", "");
            str1 = str1.replace("!", "");
            str1 = str1.toLowerCase();
            String str2 = B.words[i];
            str2 = str2.replace("'s", "");
            str2 = str2.replace("?", "");
            str2 = str2.replace(".", "");
            str2 = str2.replace("!", "");
            str2 = str2.toLowerCase();
            String word1 = B.words[i - 1].toLowerCase();
            String word2 = B.words[i].toLowerCase();
            if (filtered_characters.contains(str1) && filtered_characters.contains(str2)) {
                if (word1.endsWith(str1) && word2.startsWith(str2)) {
                    Integer num = fullNames.get(str1 + str2);
                    if (num == null) {
                        fullNames.put(str1 + str2, 1);
                    } else {
                        fullNames.put(str1 + str2, num + 1);
                    }
                    firstNames.add(str1);
                    lastNames.add(str2);
                }
            }
        }

        lastNames.removeAll(firstNames);

        Map<String, Integer> freq1 = new HashMap<String, Integer>();
        for (int i = 0, size = B.words.length; i < size; ++i) {
            String str = B.words[i];
            str = str.replace("'s", "");
            str = str.replace("?", "");
            str = str.replace(".", "");
            str = str.replace("!", "");
            str = str.toLowerCase();
            if (!filtered_characters.contains(str)) {
                continue;
            }
            Integer num = freq1.get(str);
            if (num == null) {
                freq1.put(str, 1);
            } else {
                freq1.put(str, num + 1);
            }
        }

        int sum = 0;
        for (String s : filtered_characters) {
            sum += freq1.get(s);
        }

        int threshold = (int) (sum * 0.015);
        for (String s : filtered_characters) {
            if (lastNames.contains(s)) {
                continue;
            }
            if (freq1.get(s) <= threshold) {
                continue;
            }
            if (!firstNames.contains(s)) {
                result.put(s, freq1.get(s));
            } else {
                String title = "";
                int occurrence = 0;
                for (String z : lastNames) {
                    if (fullNames.get(s + z) != null) {
                        if (fullNames.get(s + z) > occurrence) {
                            title = z;
                            occurrence = fullNames.get(s + z);
                        }
                    }
                }
                result.put((s + " " + title), freq1.get(s));
            }
        }
    }

    public int countBookCharacters() {
        if (result.isEmpty()) {
            this.findBookCharacters();
        }
        return result.size();
    }

    public void determineCharGender() {
        if (result.isEmpty()) {
            this.findBookCharacters();
        }
        String around = "";
        Pair[] charGender = new Pair[result.size()];
        int i = 0;
        for (String key : firstNames) {
            charGender[i] = new Pair();
            charGender[i].setl(key);
            int steps = 0;
            int tempcount = 0;
            int gen = 0;
            for (int j = 0; j < B.words.length; j++) {
                if (B.words[j].toLowerCase().contains(key)) {
                	
                	int high=min(j+21,B.words.length);
                	int low=max(j-11,0);
                	for(int k=low;k<high;k++) {
                		
                        if (B.words[k].toLowerCase().equals("he") || B.words[k].toLowerCase().equals("his") || B.words[k].toLowerCase().equals("him")) {
                            gen++;
                            
                            //System.out.println("hihi");
                        } else if (B.words[k].toLowerCase().equals("she") || B.words[k].toLowerCase().equals("her"))  {
                            gen--;
                            //System.out.println("hihihi");
                        }
                    }
                }
            }
            if (gen > 0) {
                            charGender[i].setr("Male");
                            //System.out.println("reached male gender");
                        } else if (gen < 0) {
                            charGender[i].setr("Female");
                            //System.out.println("reached female gender");
                        } else {
                            charGender[i].setr("Undetermined");
                            //System.out.println("reached und gender");
                        }
            i++;
        }
    }

    public void printCharCounts() {
        if(result == null) {
            this.countBookCharacters();
        }
        for(String key : result.keySet()) {
            System.out.println(key+" : "+result.get(key));
        }
    }
    
    public void printCharCountsWithGender() {
    	if(   
    }
}
