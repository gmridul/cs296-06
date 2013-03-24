package cs296BookAnalysis;

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class BookStatistics {

    Book B;
    int count = 0;
    Map<String, Integer> result;
    ArrayList<String> characters;
    

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
    
    private void findBookCharacters() {
 
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
    }
    
    public Map<String, Integer> countBookCharacters() {
        if(result.isEmpty()) {
            this.findBookCharacters();
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
        Set<String> firstNames = new HashSet<String>(), lastNames = new HashSet<String>();

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
        //Map<String, Integer> result = new HashMap<String, Integer>();
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
        return result;
    }
    
    public void determineCharGender() {
        if(result.isEmpty()) {
            this.findBookCharacters();
        }
        
        String around = null;
        Pair[] charGender = new Pair[characters.size()];
        for(int i=0;i<characters.size();i++) {
            charGender[i].l = characters.get(i);
            Pattern pattern = Pattern.compile("(\\S*[ ]){,10}"+charGender[i].l+"(\\S*[ ]){,20}");
            Matcher surround = pattern.matcher(B.text);
            while(surround.find()) {
                around += surround.group(1);
            }
            System.out.println(around);
           // pattern = Pattern.compile("")
        }
        
    
    }
}
