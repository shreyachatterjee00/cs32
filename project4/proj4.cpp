//
//  main.cpp
//  Proj4
//
//  Created by Shreya Chatterjee on 5/29/19.
//  Copyright © 2019 Shreya Chatterjee. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int CPB = 4;
//chars per bucket

class HashBucket { //class for Hash Table
    
public:
    HashBucket(int offsetParameter, string bytesParameter) {
        bytes = bytesParameter;
        offset = offsetParameter;
    }
    
    int getOffset() {
        return offset;
    }
    
    string getBytes() {
        return bytes;
    }
private:
    string bytes;   //val
    int offset;     //key
    
};

string convertToString(istream & original, size_t & length) {
    string returnString;
    
    //find length
    original.seekg(0, original.end);    //set position to end of stream
    length = original.tellg();          //get length depending on where position left off
    original.seekg(0, original.beg);    //set position back to beginning
    
    char next;
    for (int i = 0; i < length; i++) {
        original.get(next);
        if (next == '\\') {
            original.get(next);
            if (next == 'n') {
                returnString += ('\n');
                length--;
            }
        }
        else {
            returnString += (next);
        }
    }

    return returnString;
}

void insertIntoHash(vector<HashBucket> & vec, int size, string old) {
    int stringIterator = 0;
    string temporaryString;
    int offset = 0;
    for (int i = 0; i < size; i++) {
        temporaryString = "";
        //find value
        for (int j = stringIterator; j < (stringIterator + CPB); j++) {
            temporaryString += old[j];
        }
        stringIterator += CPB;
        
        HashBucket h(offset, temporaryString);
        vec.push_back(h);
        offset += CPB;
    }
}

/*finds equal values within the hash table. returns the index that starts the longest match. count is changed to the number of characters in the match. if no match is found, return -1*/
int isInTable (vector<HashBucket> vec, int size, string sequence, int & count, int newOffset, int & oldOffset, string old, string newString) {
    count = 0;
    int count2 = 0;
    int index = -1;
    vector<int> indexes;
    for (int i = 0; i < size; i++) {
        if (vec[i].getBytes() == sequence) {
            indexes.push_back(vec[i].getOffset());
        }
    }
    
    
    if (indexes.empty()) {
        return -1;              //no matches
    }
    
    else {
        for (int i = 0; i < indexes.size(); i++) {
            int originalNew = newOffset;
            count2 = 0;
            int ind = indexes[i];
            while (old[ind] == newString[originalNew]) {
                count2++;
                ind++;
                originalNew++;
            }
            
            if (count2 > count) {
                count = count2;
                index = indexes[i];
                oldOffset = index;
            }
        }
    }
    return index;
}

int isInAnyBucket (string oldS, string newS, int oldOff, int newOff) {
    string temp = "";
    temp += newS[newOff];
    int index = -1;
    int count = 0;
    int count2 = 0;
    
    size_t size;
    
    size = oldS.size();
    
    vector <int> indexes;
    for (int i = oldOff; i < size; i++) {
        if (oldS[i] == newS[newOff] && oldS[i + 1] == newS[newOff + 1] && oldS[i + 2] == newS[newOff + 2]) {
            indexes.push_back(i);
        }
    }
    
    if (indexes.empty()) {
        return -1;              //no matches
    }
    
    else {
        for (int i = 0; i < indexes.size(); i++) {
            int originalNew = newOff;
            count2 = 0;
            int ind = indexes[i];
                while (oldS[ind] == newS[originalNew]) {
                    if (ind >= oldS.size()) {
                        break;
                    }
                    count2++;
                    ind++;
                    originalNew++;
                }
            
            if (count2 > count) {
                count = count2;
                index = indexes[i];
                oldOff = index;
            }
        }
    }
    
    
    return index;
}

int anyEqualValues (string oldS, string newS, int & count, int newOffset, int & oldOffset, int & index) {
    count = 1;      //current longest substring
    int count2 = 0;
    index = -1;     //starting index of current longest substring
    
    vector<int> indexes;
    
    size_t size;
    if (oldS.size() - oldOffset > CPB) {
        size = oldOffset + CPB;
    }
    else {
        size = oldS.size();
    }
    
    
    for (int i = oldOffset; i < size; i++) {
        if (newS[newOffset] == oldS[i]) {
            indexes.push_back(i);
        }
    }
    
    if (indexes.empty()) {
        return -1;
    }
    
    for (int i = 0; i < indexes.size(); i++) {
        int ind = indexes[i];
        count2 = 0;
        int originalNew = newOffset;
        while (oldS[ind] == newS[originalNew]) {
            count2++;
            if (ind != (oldS.size() - 1) && newOffset != newS.size() - 1) {
                ind++;
                originalNew++;
            }
            
            else {
                break;
            }
        }
        
        if (count2 > count) {
            count = count2;
            index = indexes[i];
            //oldOffset = index;
            oldOffset = index;
            count2 = 0;
        }
    }
    
    return index;
}

//writes copy instruction to output
void copySeq (ostream & diff, int offset, int numberChar) {
        diff << "C" << numberChar << "," << offset;
}

//write add instruction to output
void addSeq (ostream & diff, string toAdd, size_t numberChar) {
    diff << "A" << numberChar << ":" << toAdd;
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff) {
    //read contents of old file into a string
    
    string oldFileString;
    string newFileString;
    size_t oldLength;
    size_t newLength;
    
    oldFileString = convertToString(fold, oldLength);
    newFileString = convertToString(fnew, newLength);
    
    if (oldFileString[oldFileString.size() - 1] == '\n' && newFileString[newFileString.size() - 1] != '\n') {
        oldFileString.pop_back(); //pop the new line if only the old string has one
    }
    
    //for the if else
    int count;
    int ifElseIndex;
    int oldOffset = 0;
    
    //for all CPB character sequences in the old file's string
    int numberBuckets = oldLength / CPB;
    if (CPB * numberBuckets < oldFileString.size()) {
        numberBuckets++;
    }
    
    //insert that sequence and the offset where it was found into a hash table
    vector<HashBucket> hashVec; //vector of HashBucket objs
    
    insertIntoHash(hashVec, numberBuckets, oldFileString);
    
    int offset;
    //start processing the new file's string, starting from offset 0 until the end
    for (offset = 0; offset < newFileString.size(); ) {
        
        
        //look up the N character sequence that starts at offset j in the new string
        string newNString;
        
        for (int j = offset; j < (offset + CPB); j++) {
            newNString += newFileString[j];
        }
        
        
        //if this sequence is in the table
        int L;
        int index = isInTable(hashVec, numberBuckets, newNString, L, offset, oldOffset, oldFileString, newFileString);
        if (index != -1 && offset != newFileString.size())  {
            //determine how long the match goes on (call this L)
            //write a copy instruction to the diff file to copy L bytes from offset F
            copySeq(fdiff, index, L);
            //continue at offset j = j + L
            offset = offset + L;
            oldOffset = oldOffset + L;
        }
        
        
        //if not in table, still check if any values are equal
        else if (anyEqualValues(oldFileString, newFileString, count, offset, oldOffset, ifElseIndex) != -1 && offset != newFileString.size()) {
            copySeq(fdiff, ifElseIndex, count);
            offset = offset + count;
            oldOffset = oldOffset + count;
        }
        
        else {
            string toAdd = "";
            int randomOldOff = oldOffset;      //old offset should never be changed here
            while ((isInTable(hashVec, numberBuckets, newNString, L, offset, randomOldOff, oldFileString, newFileString) == -1) && (anyEqualValues(oldFileString, newFileString, count, offset, randomOldOff, ifElseIndex) == -1) && offset != newFileString.size()) {
                
                int place = isInAnyBucket(oldFileString, newFileString, oldOffset, offset);
                
                if (place != -1) {
                    oldOffset = place;
                    break;
                }
                
                else {
                    
                    randomOldOff = oldOffset;
                    
                    toAdd += newNString[0];
                    offset++;
                    
                    newNString = "";
                    for (int j = offset; j < (offset + CPB); j++) {
                        newNString += newFileString[j];
                    }
                    
                    if (offset == newFileString.size()) {
                        size_t toAddSize = toAdd.size();
                        addSeq(fdiff, toAdd, toAddSize);
                        
                        return;
                        
                    }
                }
            }
            if (!toAdd.empty()) {
                if (offset == newFileString.size() - 1 && newFileString[offset] == '\n') {
                    //for smallmart example
                    toAdd += newFileString[offset];
                    offset++;
                }
                size_t toAddSize = toAdd.size();
                
                addSeq(fdiff, toAdd, toAddSize);
            }
            
        }
    }
    return;
    
}

bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;           //reads the character(s) into n for length
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
    if (!inf.get(cmd))
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
        case '\r':
        case '\n':
            return true;
    }
    return false;
}

//returns true if it was able to apply diff
//returns false if there's something incorrect about diff
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew) {
    
    //char command
    char command = ' ';
    //int length, offset
    int length = 0;
    int offset = 0;
    
    //while command does not equal x
    while (command != 'x') {
        
        //getCommand (fdiff, command, length, offset)
        bool result = getCommand(fdiff, command, length, offset);
        
        //if getCommand returns false
        if (!result)
            return false;
        
        //if offset or length are less than 0
        if (offset < 0 || length < 0) {
            return false;
        }
        
        //if command is A
        if (command == 'A') {
            char next;
            //from 0 to the value of length
            for (int i = 0; i < length; i++) {
                //if next character in fdiff is not get-able
                if (!fdiff.get(next)) {
                    return false;
                }
                
                else {
                    //write the character onto the new stream
                    fnew << next;
                }
            }
        }
        
        
        //if command is C
        if (command == 'C') {
            char next;
            //get position offset in fold
            fold.seekg(offset);
            //loop length times
            for (int i = 0; i < length; i++) {
                //if next character in fold is not getable
                if (!fold.get(next)) {
                    return false;
                }
           
                else {
                    //write character into the new stream
                    fnew << next;
                }
            }
        }
        
        if (command == '\n' || command == '\r') {
            offset++;
            continue;
        }
        
    }
    return true;
    
}

