print("Give the name of the novel file")
fileName = input()
file = open(fileName)
while True:
    line = file.readline()
    if "Title:" in line:
        print (line,end='')
    if "Author:" in line:
        print (line,end='')
        break;
file.close()






