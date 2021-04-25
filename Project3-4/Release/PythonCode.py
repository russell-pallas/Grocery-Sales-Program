import re
import string

list = []

newList = []


def GetFrequency():
    newFile = open("producelist.txt")

    for i in newFile:
        list.append(i.strip())
    newFile.close()

    for a in range(len(list)):
        newList.append(list[a])
        for j in range(len(newList)):
            if newList.count(list[a]) > 1:
                newList.pop()

    for b in range(len(newList)):
        print("{} {}".format(newList[b], list.count(newList[b])))


def GetNewList():
    newFile = open("producelist.txt")

    for i in newFile:
        list.append(i.strip())
    newFile.close()

    for a in range(len(list)):
        newList.append(list[a])
        for j in range(len(newList)):
            if newList.count(list[a]) > 1:
                newList.pop()

    for q in range(len(newList)):
        print(newList[q])
  

def GetIndividualFrequency(item):
    newFile = open("producelist.txt")

    for i in newFile:
        list.append(i.strip())
    newFile.close()

    print("{} {}".format(item, list.count(item)))
    



def CreateGraph():
    newFile = open("producelist.txt")

    for i in newFile:
        list.append(i.strip())
    newFile.close()

    for a in range(len(list)):
        newList.append(list[a])
        for j in range(len(newList)):
            if newList.count(list[a]) > 1:
                newList.pop()

    freqFile = open("frequency.dat", "w")

    for q in range(len(newList)):
        print("{} {}".format(newList[q], "*" * list.count(newList[q])))
        freqFile.write("{} {}\n".format(newList[q], "*" * list.count(newList[q])))







    
