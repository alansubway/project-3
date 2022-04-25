import re
import string






def printlist():
    # Opens the input file and reads.  Then places the file into list.
    f = open (r"Text.txt")
    myList = f.read()
    f.close()

    # break the string into list of words 
    myList = myList.split()
    # create list to print each item with no duplicates
    emptyList = []

    # loop until string values present in list
    for i in myList:             

        # checking for duplicacy
        if i not in emptyList:

            # insert value in emptyList
            emptyList.append(i) 

    for i in range(0, len(emptyList)):

        # count the frequency of each word and print
        print(emptyList[i], myList.count(emptyList[i]))
    
        

def getSpecificItem(v):
    # opens file and reads input. Creates list.
    f = open (r"Text.txt")
    myList = f.read()

    # returns the count of the specified item

    return myList.count(v);

def getHistogram():
    f = open (r"Text.txt")
    myList = f.read()

    f.close()
    # splits list into words
    myList = myList.split()
    # creates empty list to write to
    emptyList = []

    # loop till string values present in list
    for i in myList:             

        # checking for duplicacy
        if i not in emptyList:

            # insert value in str2
            emptyList.append(i) 

    writeHistogram = open ("frequency.dat", "w")

    for i in range(0, len(emptyList)):

        # count the frequency of each word and write name and frequncy on each line
        writeHistogram.write(emptyList[i])
        writeHistogram.write(" ")
        howMany = myList.count(emptyList[i])
        writeHistogram.write(str(howMany))
        writeHistogram.write("\n")

    # close the file
    writeHistogram.close()



    
