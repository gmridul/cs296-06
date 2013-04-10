def giveCharacters():
    #take the novel name as input
    print("Enter the name of the novel")
    fileName=input()

    #open the file
    file=open(fileName)

    #read the whole file into a string str
    str=file.read()
    #and replace all newline characters by spaces
    str=str.replace ("\n",' ')

    #this creates a vector (of) words where each word is separated by a space in str
    words=str.split(' ')

    #for using regular expressions
    import re

    #modify the words to ignore all commas, semi-colons, colons, 's etc and store in wordsModified
    wordsModified=[]
    #iterate over all words
    for x in words:
        #this creates a list of all substrings of a word which are separated by ',',';' and ':' etc.
        lst=re.findall(r"[A-Za-z.\"?!]*",x)
        #from this list pick a word with the maximum length. For example, Oliver's will give Oliver
        r=[y for y in lst if y != '']
        pick=''
        for w in r:
            if len(w) > len(pick):
                pick=w
        #add pick to wordsModified
        wordsModified.append(w)

    #characters will store all characters found by a primitive search algo explained below
    characters=[]

    #A word is a candidate for the character if it starts with a capital letter and the word preceeding it doesn't end with a '.' or '?' or '!'
    for i in range(1,len(wordsModified)):
        if ('"' or '?' or '!') in wordsModified[i-1]:
            continue
        if wordsModified[i] != '':
            if wordsModified[i-1][-1:] != '.' and wordsModified[i][0].upper()==wordsModified[i][0]:
                #The word meets our characterisation. So, append it to characters
                characters.append(wordsModified[i])

    #Replace all instances of ",?,! by a null string, so that Darcy and Darcy? give the same character
    for i in range(len(characters)):
        characters[i]=characters[i].replace('"','')
        characters[i]=characters[i].replace('?','')
        characters[i]=characters[i].replace('!','')
        if characters[i][-1:] == '.':
            characters[i]=characters[i][:-1]
        #convert characters to all lower case for ease of search later
        characters[i]=characters[i].lower()

    #Define a dictionary freq to store how many times a certain character appears in the characters vector
    freq={}

    #Fill the dictionary freq
    for x in characters:
        if x in freq:
            freq[x]=freq[x]+1
        else:
            freq[x]=0

    #A set for the distinct characters filtered by their frequency
    filtered_characters=set()

    #We define some special words, so that our algorithm doesn't pick them as characters
    special_words = ['a','an','is','are','the','this','oh','of','for','yes','no','with','not','he','she','project','in','what','his','her','there','their','where','how','why','when','which','come','go','to','it','and','','mr','mrs','you','that','but','chapter','i']

    #discard characters which do not come too often
    for x in freq:
        if freq[x] > 30:
            if x in special_words:
                continue
            filtered_characters.add(x)

    #Since, by our algorithm thus far will also include places like England, France, Paris, London etc. , we need to remove them
    #We do this by noticing that place will be preceeded by a "in" or "at" most often than not
    #So, create a dictionary of numIn to store how many times the word "in" or "at" comes before each filtered_character
    numIn={}
    for x in filtered_characters:
        numIn[x]=0

    #This finds how many times in the novel does "in" or "at" comes for a word in filtered_characters
    for index in range(1,len(words)):
        lst=re.findall(r"[A-Za-z]*",words[index])
        r=[y for y in lst if y!='']
        pick=''
        for w in r:
            if len(w) > len(pick):
                pick=w.lower()
        if pick not in filtered_characters:
            continue
        if words[index-1] == 'in' or words[index-1] == 'at':
            numIn[pick] = numIn[pick]+1

    #Now the dictionary freq1 will store how many times a filtered character comes in the novel
    freq1={}
    for x in filtered_characters:
        freq1[x]=0

    #The dictionary fullNames stores how many times a full name comes in the novel
    fullNames={}
    #firstNames and lastNames are set of first and last names of the characters
    firstNames=set()
    lastNames=set()

    #Classify the characters as first names and titles
    #For this check if the two characters appear together in the novel and there is no special character like ',','.',';' etc. between them
    #Fill the dict fullNames and sets firstNames and lastNames
    for index in range(1,len(words)):
        lst1=re.findall(r"[A-Za-z]*",words[index-1])
        r1=[y for y in lst1 if y != '']
        pick1=''
        for w1 in r1:
            if len(w1) > len(pick1):
                pick1=w1.lower()
        lst2=re.findall(r"[A-Za-z]*",words[index])
        r2=[y for y in lst2 if y != '']
        pick2=''
        for w2 in r2:
            if len(w2) > len(pick2):
                pick2=w2.lower()
        if pick1 in filtered_characters and pick2 in filtered_characters:
            if words[index-1][-len(pick1):].lower() == pick1 and words[index][:len(pick2)].lower() == pick2:
                if (pick1,pick2) in fullNames:
                    fullNames[(pick1,pick2)]=fullNames[(pick1,pick2)]+1
                else:
                    fullNames[(pick1,pick2)]=1
                firstNames.add(pick1)
                lastNames.add(pick2)

    #We assume a first name cannot be a last name, therefore the set difference
    lastNames=lastNames-firstNames

    #Fill all the characters along with their frequencies in freq1
    for x in words:
        lst=re.findall(r"[A-Za-z]*",x)
        r=[y for y in lst if y != '']
        pick=''
        for w in r:
            if len(w) > len(pick):
                pick=w.lower()
        if pick in filtered_characters:
            freq1[pick]=freq1[pick]+1

    #Find the sum of all the frequencies of those characters which are not places
    sum=0
    for x in freq1:
        if numIn[x] <= 0.1 * freq1[x]:
            sum = sum + freq1[x]

    #Fix a threshold to be the 1.5% of total number of characters 
    #This will help discard characters that do not appear too often
    threshold = sum*0.015

    result={}
    #Finally store all the characters which are not places and do not appear too often along with their frequencies in sorted order in another dict result
    for x in sorted(freq1):
        #Do not print the last names
        if x in lastNames:
            continue
        #If more than 10% of the time, a character is preceeded by an "in" or "at", then it is classified as a place
        if numIn[x] > 0.1 * freq1[x]:
            continue
        #Not a character if appears too often too less
        if freq1[x] <= threshold:
            continue
        #Add to dict, the characters that do not have titles
        if x not in firstNames:
            result[x[0].upper()+x[1:]] = freq1[x]

        #Else find the best title for the character and add the character and title to the dict result
        else:
            title=''
            maxLen=0
            for y in fullNames:
                if y[0]==x:
                    if fullNames[y] > maxLen:
                        maxLen=fullNames[y]
                        title=y[1]
            result[x[0].upper()+x[1:]+' '+title[0].upper()+title[1:]]=freq1[x]
    return [str,result,fileName]

