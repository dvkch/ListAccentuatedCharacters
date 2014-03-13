//
//  F.cpp
//  ListAccentuatedCharacters
//
//  Created by rominet on 16/02/14.
//  Copyright (c) 2014 Syan. All rights reserved.
//

#include "F.h"

#include <dirent.h>

using namespace std;

void insertInList(ListF *insert, ListF *into) {
    for(int i = 0; i < insert->size(); ++i)
        into->push_back(insert->at(i));
}


bool F::isDir() {
    return this->_dt_type == DT_DIR;
}

bool F::isRegularFile() {
    return this->_dt_type == DT_REG;
}

bool F::isValidFileName() {
    
    for(int i = 0; i < this->_name.size(); ++i)
        if(!isascii(this->_name.at(i)))
            return false;
    
    return true;
}

string F::getName(bool asciiOnly) {
    if(!asciiOnly)
        return this->_name;
    
    string cleanedUpName = "";
    for(int i = 0; i < this->_name.size(); ++i)
        if(isascii(this->_name.at(i)))
            cleanedUpName += this->_name.at(i);
    
    return cleanedUpName;
}

string F::getPath(bool asciiOnlyFileName) {
    if(this->_name.length() == 0)
        return this->_parentFolder;
    
    return this->_parentFolder + "/" + this->getName(asciiOnlyFileName);
}

string F::getParentFolder() {
    return this->_parentFolder;
}

std::vector<std::string> F::getInvalidCharacters() {
    
    vector<string> v;
    string s = "";
    
    string previous = "";
    bool previousIsAcii = true;
    
    for(int i = 0; i < this->_name.size(); ++i) {
        if(isascii(this->_name.at(i))) {
            if(s.size() != 0) {
                v.push_back(s);
                s = "";
            }
        }
        else {
            if(previousIsAcii)
                s += previous;
            s += this->_name.at(i);
        }
        
        previous = this->_name.at(i);
        previousIsAcii = isascii(this->_name.at(i));
    }
    
    if(s.size() != 0)
        v.push_back(s);
    
    return v;
}

F::F(string name, int dt_type, string parentFolder) {
    this->_dt_type = dt_type;
    this->_name = name;
    this->_parentFolder = parentFolder;
}

ListF *F::listFiles(bool recursive, std::vector<std::string> forbiddenNames)
{
    ListF *list = new ListF();
    
    if(!this->isDir())
        return list;
        
    DIR *d = opendir(this->getPath(false).c_str());
    if(!d)
        return list;
    
    struct dirent *content = NULL;
    while((content = readdir(d)) != NULL) {
        
        if(string("." ) == content->d_name ||
           string("..") == content->d_name)
            continue;
        
        bool forbidden = false;
        for(int i = 0; i < forbiddenNames.size(); ++i)
            if(forbiddenNames.at(i) == content->d_name) {
                forbidden = true;
                break;
            }
        
        if(forbidden)
            continue;
        
        F *item = new F(content->d_name, content->d_type, this->getPath(false));
        
        if(item->isDir() || item->isRegularFile())
            list->push_back(item);
        
        if(recursive)
            insertInList(item->listFiles(recursive, forbiddenNames), list);
    }
    
    closedir(d);
    return list;
}
