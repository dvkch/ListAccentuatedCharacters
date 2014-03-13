//
//  F.h
//  ListAccentuatedCharacters
//
//  Created by rominet on 16/02/14.
//  Copyright (c) 2014 Syan. All rights reserved.
//

#ifndef __F_H__
#define __F_H__

#include <string>
#include <vector>

class F;

typedef std::vector<F*> ListF;

class F {
private:
    int _dt_type;
    std::string _name;
    std::string _parentFolder;
    
public:
    bool isDir();
    bool isRegularFile();
    bool isValidFileName();
    std::string getName(bool asciiOnly);
    std::string getPath(bool asciiOnlyFileName);
    std::string getParentFolder();
    std::vector<std::string> getInvalidCharacters();
    
    ListF *listFiles(bool recursive, std::vector<std::string> forbiddenNames);
    
    F(std::string name, int dt_type, std::string parentFolder);
};


#endif
