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

for x in freq:
    if freq[x] > 30:
        filtered_characters.add(x)

freq1={}
for x in filtered_characters:
    freq1[x]=0

for x in words:
    lst=re.findall(r"[A-Za-z]*",x)
    r=[y for y in lst if y != '']
    pick=''
    for w in r:
        if len(w) > len(pick):
            pick=w.lower()
    if pick in filtered_characters:
        freq1[pick]=freq1[pick]+1

print(freq1)

