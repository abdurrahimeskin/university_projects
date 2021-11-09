import os
import sys
import  re
from collections import deque
listFile = []
listGen=[]
listNew=[]
listH=[]
listCopy=[]
HlistPath=[]

#printing the firt part of the makefile generator
def makeFile():
    ftr=("prog.exe:\t")
    fnr=("\t\tgcc  ")
    for ind in listFile:
        if ".c" in ind:
            str = re.search('/(\w+[^/]\w+.c)',ind ).group(1)
            strr=re.search('(.*).c',str).group(1)
            strr=(strr+".o  ")
            ftr=ftr+strr
            fnr=fnr+strr
    print(ftr)
    print(fnr+"-O program")

#printing the second part of the generator
def makeOfile():
    sayac = 0
    for cfile in listFile:
        if ".c" in cfile:
            ftr=re.search('/(\w+[^/]\w+).c',cfile).group(1)+".o:\t"
            ftr+=re.search('/(\w+[^/]\w+.c)',cfile).group(1)+" "
            for es in HlistPath[sayac]:
                ftr+=re.search('/(.*)',es).group(1)+" "
            print(ftr)

            fnr = ("\t\tgcc  -c  ")
            fnr+=re.search('/(\w+[^/]\w+.c)',cfile).group(1)
            print(fnr)
            sayac += 1



#it is the main traverse code
qlist = deque( [ sys.argv[1] ] )

while qlist:
  currentdir =  qlist.popleft()
  dircontents = os.listdir(currentdir)
  for name in dircontents:
     currentitem = currentdir + "/" + name
     if os.path.isdir(currentitem):
       qlist.append(currentitem)
     else:
        listFile.append(currentitem)

#traverse in the directory files and choose files which includes ".c" and add it to a list
for fileindex in listFile:

    if ".c" in fileindex:

        listGen=[]
        with open(fileindex) as f:
           for line in f:
               if '#include "'  in line:
                   st=re.search('"(.*)"',line).group(1)
                   listGen.append(st)

        listNew.append(listGen)

#copying c file's list to another one

listCopy=listNew[:]

#for all c files traverse them and find the directories which has '.h' extension
for files in listFile:
    if ".h" in files:
        listH.append(files)

#controlling the situation if there is not any ".h" in used into c files and print warning if that case appears

for absent in listH:
    key=False
    for search in listNew:
        for find in search:
          if find in absent:
              key=True

    if key==False:
       print(absent+" is not in usage Warning")
#decrease the list dimension to elaborate the same files in the list

for x in listNew:
    if listNew.count(x)>1:
        listNew.remove(x)

#if there is not any '.h' files in the c file intrinsically and print error if that situation occurs
for y in listCopy:
    key=False
    for b in y:
        for z in listH:
            if b in z:
                key = True
    if key == False:
        print(b + " cannot be founded " + " Error ")
        exit()
#traverse in the files' lists and add the path of the ".h" file to another list
for item in listNew:
    tempList = []
    for ite in item:
        for fh in listH:
            if ite in fh:
                tempList.append(fh)
    HlistPath.append(tempList)

#call the methods
makeFile()
makeOfile()



