print("Enter the name of the novel")
fileName=input()
file=open(fileName)
str=file.read()
str=str.replace ("\n",' ')
words=str.split(' ')

import re
wordsModified=[]
for x in words:
    lst=re.findall(r"[A-Za-z.\"?!]*",x)
    r=[y for y in lst if y != '']
    pick=''
    for w in r:
        if len(w) > len(pick):
            pick=w
    wordsModified.append(w)

characters=[]

for i in range(1,len(wordsModified)):
    if ('"' or '?' or '!') in wordsModified[i-1]:
        continue
    if wordsModified[i] != '':
        if wordsModified[i-1][-1:] != '.' and wordsModified[i][0].upper()==wordsModified[i][0]:
            characters.append(wordsModified[i])

for i in range(len(characters)):
    characters[i]=characters[i].replace('"','')
    characters[i]=characters[i].replace('?','')
    characters[i]=characters[i].replace('!','')
    if characters[i][-1:] == '.':
        characters[i]=characters[i][:-1]
    characters[i]=characters[i].lower()

freq={}

for x in characters:
    if x in freq:
        freq[x]=freq[x]+1
    else:
        freq[x]=0

filtered_characters=set()

special_words = ['a','an','is','are','the','this','oh','of','for','yes','no','with','not','he','she','project','in','what','his','her','there','their','where','how','why','when','which','come','go','to','it','and','','mr','mrs','you','that','but','chapter','i'] # 'miss','sir','lady'

for x in freq:
    if freq[x] > 30:
        if x in special_words:
            continue
        filtered_characters.add(x)

numIn={}
for x in filtered_characters:
    numIn[x]=0

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

freq1={}
for x in filtered_characters:
    freq1[x]=0

fullNames={}
firstNames=set()
lastNames=set()

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

lastNames=lastNames-firstNames

for x in words:
    lst=re.findall(r"[A-Za-z]*",x)
    r=[y for y in lst if y != '']
    pick=''
    for w in r:
        if len(w) > len(pick):
            pick=w.lower()
    if pick in filtered_characters:
        freq1[pick]=freq1[pick]+1

sum=0
for x in freq1:
    if numIn[x] <= 0.1 * freq1[x]:
        sum = sum + freq1[x]

threshold = sum*0.015
print(threshold)

for x in freq1:
    if x in lastNames:
        continue
    if numIn[x] > 0.1 * freq1[x]:
        continue
    if freq1[x] <= threshold:
        continue
    if x not in firstNames:
        print([x[0].upper()+x[1:],freq1[x]])
    else:
        title=''
        maxLen=0
        for y in fullNames:
            if y[0]==x:
                if fullNames[y] > maxLen:
                    maxLen=fullNames[y]
                    title=y[1]
        #print([x+' '+title,freq1[x]])
        print([x[0].upper()+x[1:]+' '+title[0].upper()+title[1:],freq1[x]])
