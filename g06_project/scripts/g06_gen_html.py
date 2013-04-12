def inside_brace(string):
	for index in range(len(string)):
		if string[index]=='{':
			index1=index
		if string[index]=='}':
			index2=index
	return string[index1+1:index2]

mytex=open('../doc/g06_project_report.tex')
string=mytex.read()
import re

string=string.replace('\\\\*', '<br>')
#a=re.findall(r'\\documentclass[^\}]*\}',string)
#print(a)
string=re.sub(r'\\usepackage[^\}]*\}','',string)
string=re.sub(r'\\bibliographystyle[^\}]*\}','',string)
string=re.sub(r'\\bibliography[^\}]*\}','',string)
string=re.sub(r'\\documentclass[^\}]*\}','',string)
#string=string.replace(
#string=string.replace(
string=string.replace('\\begin{document}','<html> \n<head> \n<div align="center">')
string=string.replace('\\end{document}','</html> ')

from datetime import date
now = date.today()
string=string.replace('\\date{\\today}',str(now))
string=string.replace('\\maketitle','</div> \n</head>')
titlelist=re.findall(r'\\title\{[^\}]*',string)
title=titlelist[0][7:]
string=re.sub(r'\\title\{[^\}]*\}', '<h1>'+title+'</h1>', string)
authorlist=re.findall(r'\\author\{[^\}]*',string)
author=authorlist[0][8:]
string=re.sub(r'\\author\{[^\}]*\}', '<h3>'+author+'</h3>', string)

#print(titlelist)
#print(title)
#input()
#print(author)
sectionlist=re.findall(r'\\section[^\}]*',string)
#print(sectionlist)
for x in sectionlist:
	x=x[9:]
	#print(x)
	string=string.replace('\section{'+x+'}', '<h2>'+x+'</h2>')
#............................................................................
subsectionlist=re.findall(r'\\subsection[^\}]*',string)
for x in subsectionlist:
	x=x[12:]
	#print(x)
	string=re.sub(r'\\subsection\{'+x+'}', '<h3>'+x+'</h3>', string)
#............................................................................
imglist=re.findall(r'\\includegraphics[^\}]*\}',string)
for x in imglist:	
	if 'plot' in x:
		y='../plots/g06_'+inside_brace(x)+'.png'
	else:
		y='../images/'+inside_brace(x)+'.png'
	#print(y)
	string=string.replace(x, '<img src='+y+' > <br>')
	#print(string)
#.............................................................................
boldlist=re.findall(r'\\textbf[^\}]*\}',string)
for x in boldlist:	
	y='<b>'+inside_brace(x)+'</b>'
	#print(x)
	string=string.replace(x, y)
#.............................................................................
citelist=re.findall(r'\\cite[^\}]*\}',string)
#print(citelist)
for x in citelist:	
	string=string.replace(x, '')
#..................................................................................

string=string.replace('\\begin{center}','<div align="center">')
string=string.replace('\end{center}','</div>')
string=string.replace('\lq',"'")
string=string.replace('\\rq',"'")
string=string.replace('\\textgreater',">")
string=string.replace('$','')
string=string.replace('\\','')

#subsectionlist=[]
#s2=[]
#for x in sectionlist:
	#s1=re.findall(r'\\subsection\{[^\}]*', string)
	#for y in s1:
		#s2.append(y[12:])
	#subsectionlist.append(s2)
#print(subsectionlist)
#a=re.compile(r'Profil[.]*/html',re.S)
#string=string[:iter1];
#print(a.search(string))
f=open('../doc/g06_project_report.html','w')
f.write(string);
f.write(' ');
mytex.close();
f.close();
