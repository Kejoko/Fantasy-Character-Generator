//
//  FantasyCharacter.cpp
//  C++ Fantasy Character Generator
//
//  Created by Keegan Kochis on 12/6/18.
//  Copyright © 2018 Keegan Kochis. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

class Character {
public:
    //  Data fields for each Character
    std::string firstName;
    std::string lastName;
    std::string race;
    std::string sex;
    std::string height;
    std::string title;
    std::string nickName;
    int age;
    
    //  Default constructor for Character
    Character() {
        firstName = "John";
        lastName = "Smith";
        race = "Human";
        sex = "Male";
        title = "Mr.";
        nickName = "The Man";
        age = 30;
    }
    
    /*  Constructor for Character, given a file for each of the following:
     *  race data, first names, last names, titles, nick names
     */
    Character(std::string rdFileName, std::string fnFileName, std::string lnFileName, std::string tFileName, std::string nnFileName) {
        //  Get race data from rdFileName
        std::string raceDataArr[4];
        genRaceData(rdFileName, raceDataArr);
        race = raceDataArr[0];
        
        //  Randomly generater sex
        sex = genSex(raceDataArr[1].compare("Y") == 0);
        
        //  Randomly generate height
        height = genHeight(stoi(raceDataArr[2]));
        
        //  Randomly generate an age
        age = genAge(stoi(raceDataArr[3]));
        
         /*
        //  Randomly generate first name from fnFileName and last name from lnFileName
        firstName = genString(fnFileName, race + "_" + sex);
        lastName = genString(lnFileName, race);
        
        //  Randomly generate a title from tFileName and nickname from nnFileName
        title = genString(tFileName, race + "_" + sex);
        nickName = genString(nnFileName, race);
         */
        
    }
    
    /*  Method to generate a string, given a file name, a subsection of the file and
    *   how many options belong to that subsection
    */
    std::string genString(std::string fileName, std::string subsection) {
        //  Open a file
        std::ifstream infile;
        infile.open(fileName);
        
        //  Read in strings from file until one matches subsection
        std::string currString = "Blank";
        while (currString.compare(subsection) != 0) {
            infile >> currString;
        }
        
        //  Read in an int
        int numValues;
        infile >> numValues;
        
        //  Set seed and generate an integer on interval (0, numValues]
        srand((int)time(NULL));
        int randValue = rand() % numValues + 1;
        
        //  Read in an integer and string until integer matches randValue
        int currValue = 0;
        std::string randString;
        while (currValue != randValue) {
            //  Read in  int
            infile >> currValue;
            
            //  Read in a string
            infile >> randString;
        }
        
        //  Close the file we opened
        infile.close();
        
        //  Return generated string
        return randString;
    }
    
    void genRaceData(std::string fileName, std::string raceDataArr[]) {
        //  Gather raceData string from fileName
        std::string raceData = genString(fileName, "Races");
        
        //  Parse raceData for race, sex ability, height, and max age
        //  Get location of first comma and retreieve race, then shorten raceData
        int commaPos = (int)raceData.find(",");
        raceDataArr[0] = raceData.substr(0, commaPos);
        raceData = raceData.substr(commaPos + 1, raceData.length());
        
        //  Get location of next comma, retrieve sex ability, shorten raceData
        commaPos = (int)raceData.find(",");
        raceDataArr[1] = raceData.substr(0, commaPos);
        raceData = raceData.substr(commaPos + 1, raceData.length());
        
        //  Get location of next comma, retrieve average height, shorten raceData
        commaPos = (int)raceData.find(",");
        raceDataArr[2] = raceData.substr(0, commaPos);
        raceData = raceData.substr(commaPos + 1, raceData.length());
        
        //  Retrieve the remaining int of raceData for max age
        raceDataArr[3] = raceData;
    }
    
    /*  A method to generate wether the character is male or female, depending on whether
     *  the race allows it, given a race, and a file name containing race data
     */
    std::string genSex(bool sexAbil) {
        //  If ability for different sexes is true,
        //  randomly choose male or female
        if (sexAbil == true) {
            int mf = rand() % 2 + 1;
            if (mf == 1)
                return "Male";
            else if (mf == 2)
                return "Female";
            else
                return "genSexERR";
        }
        else
            return "Genderless";
    }
    
    /*  Method to generate the height of character, given the average height
     *  of the characters race
     */
    std::string genHeight(int avgHeight) {
        //  Randomly generate the amount to add to average height index
        int heightValue = avgHeight + ((rand() % 3) - 1);
        
        //  Interpret the determined height index
        switch (heightValue) {
            case 2:
                return "Midget";
            case 3:
                return "Very Short";
            case 4:
                return "Short";
            case 5:
                return "Average";
            case 6:
                return "Tall";
            case 7:
                return "Very Tall";
            case 8:
            case 9:
                return "Giant";
            default:
                return "genHeightERR";
        }
    }
    
    /*  Method to generate a random age, given max age of character's race
     */
    int genAge(int maxAge) {
        //  Set seed and generate random age
        srand((int)time(NULL));
        
        /*
        //  Implementation 1
        return (rand() % maxAge + 1);
        */
        
        /*
        //  Implementation 2
        //  Generate 2 random numbers on interval [1, maxAge],
        //  then generate a number between them
        int rand1 = rand() % maxAge + 1;
        int rand2 = rand() % maxAge + 1;
        if (rand1 <= rand2)
            return (rand() % rand2 + rand1);
        else
            return (rand() % rand1 + rand2);
        */
        
        
        //  Implementation 3
        //  Generate a random number on interval [1, maxAge/2] and generate
        //  a random number on the interval [maxAge/2, maxAge] then
        //  generate a random number between them
        int randLow = rand() % (maxAge/2) + 1;
        int randHigh = rand() % (maxAge/2) + (maxAge/2);
        return (rand() % randHigh + randLow);
        
    }
};

int main() {
    
    //  Create character for testing
    Character defaultCharacter;
    
    //  Generate random character using proper files
    Character randomCharacter("fcg_RaceData.txt", "fcg_FirstNames.txt", "fcg_LastNames.txt", "fcg_PreNames.txt", "");
    std::cout << randomCharacter.race << " " << randomCharacter.height << " " << randomCharacter.age << " " << randomCharacter.sex << std::endl;
 
    return 0;
}
