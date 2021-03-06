CS 296- Assignment 7
Group no. 06
Sagar Jha - 110100024
Sudipto Biswas - 110050048
Mridul Garg - 110050030

All the submitted work is our own and we have not copied it from anywhere.

Note: Novel that we have chosen is Oliver Twist written by Charles Dickens
		  give input as oliver_twist.txt when the scripts ask for it

Algorithm used for this assignment:

1. To find Title and Author: (Python Script - g06_bookinfo.py)
We input the text file in a python string. Then search for the keywords 'Title: ' and 'Author: ' and print whatever follows both in their respective lines.

2. To find the list of Characters and their number of appearances: (Python Script - g06_bookchars.py)
We input the entire text file in a string. Then remove all the newline characters and create a vector of all the words separated by a single whitespace. We use the python3 re library to rewrite the words with commas, semicolons, colons etc. into two words separated by a whitespace in place of ',' / ';'/ ':' . Then we maintain another empty list where we will add the characters one by one as we go through the string. A word is a candidate for the character if it starts with a capital letter and the word preceeding it doesn't end with a '.' or '?' or '!'. We then replace all instances of ",?,! by a null string, so that Darcy and Darcy? give the same character. We use a dictionary data structure to create a frequency table i.e. every character would be mapped to its number of appearances. We keep in a string stored some of the usual words which appear very frequently and may pass as characters but arent so. For eg: a, this, the, if, for etc. So we check that these words are not there in our character list/ dictionary. We keep the count of the appearances of each character in the dictionary and only keep the ones with frequency > 30. Then again there might be cities and places which pass on as characters. To get rid of them, we assume that generally words like 'in' and 'at' come just before the places rather than characters. So we search for such characters with more than 10% times being preceded by in/at. We classify them as places. Also there can be characters with name and surname being used at different places. In such cases, we might consider the name and surname of the same person to be different characters. To avoid that we keep a check if two character names come one after another, without any demarker. This means the entire two words is the character name and both mean the same person. We keep the character name as the entire name. and everytime any of the two names is referred to as, we consider them to be of this one character.
 
3. To find the gender of all the characters and to approximate the protagonists( hero and heroine) and the antagonist: (Python Script - g06_bookactors.py)
We here take the list provided by the last script. ie a dictionary data structure consisting of the character names mapped to their number of appearances. We use the re library from python3 package to store, for each appearance of the character, 10 words before and 20 words after the given word. Then we concatenate all such strings for all the appearances and find the number of appearances of he/him/He/Him/his/His - number of appearances of she/She/Her/her. If the number thus obtained is > 0 , then the character is most likely to be male, if < 0 then female, otherwise undetermined. Based on these values for every character, we create another dictionary with the characters being mapped to their gender.
For finding the protagonists i.e. hero and heroine, we find out the characters (male and female) with the maximum number of appearances. For the antagonist, we find the second most appearing character other than the protagonists. 
