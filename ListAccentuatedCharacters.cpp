//
//  ListAccentuatedCharacters.cpp
//  ListAccentuatedCharacters
//
//  Created by rominet on 16/02/14.
//  Copyright (c) 2014 Syan. All rights reserved.
//

#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "F.h"

using namespace std;




#define DEFAULT_ANSWER      (false)

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

bool getAnswerFromUser(string question, bool defaultValue);


int main(int argc, const char * argv[])
{
#ifndef DEBUG
    if(argc < 2) {
        printf("ListAccentuatedCharacters v1.0\n");
        printf("Usage: listaccentuatedcharacters fullpath [forbidden_name_1 [forbidden_name_2 [...]]]\n");
        return 0;
    }
#endif
    
#ifndef DEBUG
    string s = string(argv[1]);
#else
    string s = string("/Volumes/Data");
#endif
    
    if(s.size() == 0 || s.c_str()[0] != '/') {
        printf("Invalid path, quitting...\n");
        return 0;
    }
    
    printf("*****************************************************\n");
    printf("** Starting analyze of path: %s\n", s.c_str());
    
    
    vector<string> forbiddenNames;
    for(int i = 2; i < argc; ++i) {
        forbiddenNames.push_back(argv[i]);
        printf("  forbidding name: %s\n", argv[i]);
    }

#ifdef DEBUG
    forbiddenNames.push_back(".DS_Store");
#endif
    
    printf("\n");
    
    F *root = new F("", DT_DIR, s);
    ListF *list = root->listFiles(true, forbiddenNames);
    
    int count = 0;
    for(int i = 0; i < list->size(); ++i)
        if(!list->at(i)->isValidFileName())
            ++count;
    
    printf("** End of analyze: %d items to rename\n", count);
    printf("*****************************************************\n");
    
    for(int i = 0; i < list->size(); ++i) {
        if(!list->at(i)->isValidFileName()) {
            F* item = list->at(i);
            printf("%s\n", item->getPath(false).c_str());
            printf("    correct: %s\n", item->getName(false).c_str());
            printf("       into: %s\n", item->getName(true ).c_str());
            
            if(getAnswerFromUser("  -> Apply? (y/N): ", DEFAULT_ANSWER) == true) {
                int r = rename(item->getPath(false).c_str(), item->getPath(true).c_str());
                if(r == 0)
                    printf(ANSI_COLOR_GREEN "  -> renamed successfully\n\n" ANSI_COLOR_RESET);
                else
                    printf(ANSI_COLOR_RED   "  -> error while renaming (%s)\n\n" ANSI_COLOR_RESET, strerror(errno));
            }
            else
                printf("  -> not renamed\n\n");
            
            /*
            vector<string> v = item->getInvalidCharacters();
            printf(" invalid characters:");
            for(int j = 0; j < v.size(); ++j) {
                printf(" %s%s", v.at(j).c_str(), j == v.size() -1 ? "" : "  -  ");
            }
            printf("\n");
             */
        }
    }
    
    return 0;
}


bool getAnswerFromUser(string question, bool defaultValue) {
    string input = "";
    while (true) {
        printf("%s", question.c_str());
        getline(cin, input);
        
        if(input == "")
            return defaultValue;
        if(input == "n" || input == "N")
            return false;
        if(input == "y" || input == "Y")
            return true;
        
        printf("Invalid answer... ");
    }
    return defaultValue;
}


