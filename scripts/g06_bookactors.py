import re
from give_characters import giveCharacters

vec=giveCharacters()
cl = vec[1]
str1 = vec[0]

d = {}
temp=[]
str2=''
g=0
for x in cl:
    temp = re.findall('(?:[\x00-\x1F\x21-\xff]*[ ]){,10}'+re.escape(x)+'(?:[ ][\x00-\x1F\x21-\xff]*){,20}',str1)
    str2=''
    for y in temp:
        str2 = str2+y
    g=len(re.findall(' His | his | him | Him | He | he ',str2)) - len(re.findall(' Her | her | She | she ',str2))
    if g>0:
    	d[x]='Male'
    elif g<0:
    	d[x]='Female'
    else:
    	d[x]='Undetermined'

for x in cl:
    print('%s : %i : %s'%(x,cl[x],d[x]))
print('\n')
hero=''
heroine=''
vil=''
freqhm=0
freqhf=0
freqvil=0
mf=0
ff=0
for x in d:
    d[x]=(cl[x],d[x])
#d[x] = (frequency of x, gender of x)

for x in d:
    if d[x][1]=='Male':
        if d[x][0]>freqhm:
            freqvil=freqhm
            vil=hero
            freqhm=d[x][0]
            hero=x
        elif d[x][0]>freqvil:
            freqvil=d[x][0]
            vil=x
    elif d[x][1]=='Female':
        if d[x][0]>freqhf:
            freqvil=freqhf
            vil=heroine
            freqhf=d[x][0]
            heroine=x
        elif d[x][0]>freqvil:
            freqvil=d[x][0]
            vil=x

print('The main characters of the novel are the following:\nHero : %s \nHeroine : %s \nVillain : %s'%(hero,heroine,vil))
