#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{
    private:
        string _Value;

    public:
        clsString()
        {
            _Value = "";
        }

        clsString(string Value)
        {
            _Value = Value;
        }

        void SetValue(string Value)
        {
            _Value = Value;
        }

        string Value()
        {
            return _Value;
        }

        static short Length(string S)
        {
            return S.length();
        }

        short Length()
        {
            return _Value.length();
        }

        static void PrintFirstLetterOfEachWord(string S1) 
        {
            cout<<"This is The first Letters OF Each Word of The String : \n";
            bool isFirstLetter = true;
            for (int i = 0; i < S1.size(); i++) {
                if(S1[i] !=  ' ' && isFirstLetter)
                    cout<<S1[i]<< "  ";
                isFirstLetter = S1[i] ==  ' ' ? true : false ;
            }
            cout<<endl;
        }

        void PrintFirstLetterOfEachWord() 
        {
            PrintFirstLetterOfEachWord(_Value);
        }

        static string UpperFirstLetterOfEachWord(string Line)
        {
            bool isFirstLetter = true;
            for (int i = 0; i < Line.size(); i++) {
                if(Line[i] !=  ' ' && isFirstLetter)
                    Line[i] = toupper(Line[i]);
                isFirstLetter = Line[i] ==  ' ' ? true : false ;
            }
            return Line;
        }

        void UpperFirstLetterOfEachWord()
        {
            _Value = UpperFirstLetterOfEachWord(_Value);
        }

        static string LowerFirstLetterOfEachWord(string Line)
        {
            bool isFirstLetter = true;
            for (int i = 0; i < Line.size(); i++) {
                if(Line[i] !=  ' ' && isFirstLetter)
                    Line[i] = tolower(Line[i]);
                isFirstLetter = Line[i] ==  ' ' ? true : false ;
            }
            return Line;
        }

        void LowerFirstLetterOfEachWord()
        {
            _Value = LowerFirstLetterOfEachWord(_Value);
        }

        static string UpperAllString(string line)
        {
            for (int i = 0; i < line.size(); i++)
                line[i] = toupper(line[i]);
            return line;
        }

        void UpperAllString()
        {
            _Value = UpperAllString(_Value);
        }

        static string LowerAllString(string line)
        {
            for (int i = 0; i < line.size(); i++)
                line[i] = tolower(line[i]);
            return line;
        }

        void LowerAllString() 
        {
            _Value = LowerAllString(_Value);
        }

        static char InvertLetterCase(char character)
        {
            return isupper(character) ? tolower(character) : toupper(character) ;
        }

        static string InvertAllLettersCase(string line)
        {
            for (int i = 0; i < line.size(); i++)
                line[i] = InvertLetterCase(line[i]);
            return line;
        }

        void InvertAllLettersCase()
        {
            _Value = InvertAllLettersCase(_Value);
        }

        static void PrintCharactersCountInString(string Line)
        {
            cout<<"\nString Length =            "<<Line.length()<<endl;

            cout<<"Capital Letters Count =    "<<
                    GetCapitalLettersCountInString(Line)
                    <<endl;

            cout<<"Small Letters Count =      "<<
                    GetSmallLettersCountInString(Line)
                    <<endl;

            cout<<"Special Characters Count = "<<
                    GetSpecialLettersCountInString(Line)
                    <<endl;

            cout<<"Numbers Count =            "<<
                    GetNumbersCountInString(Line)
                    <<endl;

            cout<<"Empty Charactes Count =    "<<
                    GetEmptyCharactersCountInString(Line)
                    <<endl;
        }

        void PrintCharactersCountInString()
        {
            PrintCharactersCountInString(_Value);
        }

        static short GetSmallLettersCountInString(string Line)
        {
            short SmallLettersCount = 0;
            for (int i = 0; i < Line.length(); i++)
                if(islower(Line[i]))
                    SmallLettersCount++;
            return SmallLettersCount;
        }

        short GetSmallLettersCountInString()
        {
            return GetSmallLettersCountInString(_Value);
        }

        static short GetCapitalLettersCountInString(string Line)
        {
            short CapitalLettersCount = 0;
            for (int i = 0; i < Line.length(); i++)
                if(isupper(Line[i]))
                    CapitalLettersCount++;
            return CapitalLettersCount;
        }

        short GetCapitalLettersCountInString()
        {
            return GetCapitalLettersCountInString(_Value);
        }

        static short GetSpecialLettersCountInString(string Line)
        {
            short SpecialLettersCount = 0;
            for (int i = 0; i < Line.length(); i++)
                if(ispunct(Line[i]))
                    SpecialLettersCount++;
                return SpecialLettersCount;
        }

        short GetSpecialLettersCountInString()
        {
            return GetSpecialLettersCountInString(_Value);
        }

        static short GetNumbersCountInString(string Line)
        {
            short NumbersCount = 0;
            for (int i = 0; i < Line.length(); i++)
                if(isdigit(Line[i]))
                    NumbersCount++;
                return NumbersCount;
        }

        short GetNumbersCountInString()
        {
            return GetNumbersCountInString(_Value);
        }

        static short GetEmptyCharactersCountInString(string Line)
        {
            short EmptyCharactersCount = 0;
            for (int i = 0; i < Line.length(); i++)
                if(isspace(Line[i]))
                    EmptyCharactersCount++;
                return EmptyCharactersCount;
        }

        short GetEmptyCharactersCountInString()
        {
            return GetEmptyCharactersCountInString(_Value);
        }

        static short GetCharacterCountInString(string Line , char Character)
        {
            short CharacterCount = 0;
            for (int i = 0 ; i < Line.length();i++)
                if(Line[i] == Character)
                    CharacterCount++;
            return CharacterCount;
        }

        short GetCharacterCountInString(char Character)
        {
            return GetCharacterCountInString(_Value,Character);
        }

        static short GetAllMatchingCharacterCountInString(string Line , char Character)
        {
            short CharacterCount = 0;
            for (int i = 0 ; i < Line.length();i++)
                if(Line[i] == toupper(Character) || Line[i] == tolower(Character) )
                    CharacterCount++;
            return CharacterCount;
        }   

        short GetAllMatchingCharacterCountInString(char Character)
        {
            return GetAllMatchingCharacterCountInString(_Value,Character);
        }

        static bool IsVowel(char ch)
        {
            ch = tolower(ch);
            return (ch== 'a') || (ch== 'e') || (ch== 'i') || (ch== 'o') || (ch== 'u');
        }

        static short CountVowels(string S)
        {
            short VowelsCount = 0;
            for (int i = 0; i < S.length(); i++)
                if(IsVowel(S[i]))
                    VowelsCount++;
            return VowelsCount;
        }

        short CountVowels()
        {
            return CountVowels(_Value);
        }

        static void PrintEachVowelInString(string S)
        {
            cout<<"All Vowels In String is: ";
            for (int i = 0; i < S.length(); i++)
                if(IsVowel(S[i]))
                    cout<<S[i]<<"   ";
            cout<<endl;
        }

        void PrintEachVowelInString()
        {
            PrintEachVowelInString(_Value);
        }

        static void PrintEachWordInString(string S1)
        {
            cout << "\nYour string wrords are: \n\n";

            string delim = " "; // delimiter
            string sWord; // define a string variable

            short pos = 0;

            // use find() function to get the position of the delimiters
            while ((pos = S1.find(delim)) != std::string::npos) {
                sWord = S1.substr(0, pos); // store the word
                if (sWord != "") 
                    cout << sWord << endl;
                S1.erase(0, pos + delim.length()); /* erase() until positon and move to next word. */
            }
            if (S1 != "") 
                cout << S1 << endl; // it print The last word of the string.
        }

        void PrintEachWordInString()
        {
            PrintEachWordInString(_Value);
        }

        //Return Words Count
        static short CountWords(string S1)
        {
            string delim = " "; // delimiter  
            short Counter = 0;
            short pos = 0;
            string sWord; // define a string variable  

            // use find() function to get the position of the delimiters  
            while ((pos = S1.find(delim)) != std::string::npos)
            {
                sWord = S1.substr(0, pos); // store the word   
                if (sWord != "")
                {
                    Counter++;
                }
                //erase() until positon and move to next word.
                S1.erase(0, pos + delim.length());
            }

            if (S1 != "")
            {
                Counter++; // it counts the last word of the string.
            }

            return Counter;
        }

        short CountWords()
        {
            return CountWords(_Value);
        };

        static vector <string> Split(string S1, string Delim)
        {
            vector<string> vString;
            short pos = 0;
            string sWord; // define a string variable

            // use find() function to get the position of the delimiters
            while ((pos = S1.find(Delim)) != std::string::npos) {
                sWord = S1.substr(0, pos); // store the word

                if (sWord != "")
                    vString.push_back(sWord);

                // erase() until positon and move to next word.
                S1.erase(0, pos + Delim.length()); 
                }
                if (S1 != "")
                    vString.push_back(S1); // it adds last word of the string.
            return vString;
        }

        vector<string> Split(string Delim)
        {
            return Split(_Value,Delim);
        }

        static string TrimLeft(string S)
        {
            for (short i = 0; i < S.length(); i++)
            {
                if (S[i] != ' ')
                {
                    return S.substr(i, S.length() - i);
                }
            }
            return "";
        }

        void TrimLeft()
        {
            _Value = TrimLeft(_Value);
        }

        static string TrimRight(string S)
        {
            for (short i = S.length() - 1; i >= 0; i--)
            {
                if (S[i] != ' ')
                {
                    return S.substr(0, i + 1);
                }
            }
            return "";
        }

        void TrimRight()
        {
            _Value = TrimRight(_Value);
        }

        static string Trim(string S)
        {
            return TrimLeft(TrimRight(S));
        }

        void Trim()
        {
            _Value = Trim(_Value);
        }

        static string JoinString(vector <string> vWords , string Seperator)
        {
            string S = "";
            for(string & Word : vWords )
            {
                S = S + Word + Seperator;
            }
            return S.substr(0,S.length() - Seperator.length());
        }

        static string JoinString(string arrWords[], short length , string Seperator )
        {
            string S = "";
            for(int i = 0 ; i < length ; i++ )
            {
                S = S + arrWords[i] + Seperator;
            }
            return S.substr(0,S.length() - Seperator.length());
        }

        static string ReverseStringWords(string S)
        {
            vector <string> vWords = Split(S , " ");
            S = "";
            for(int i = vWords.size() - 1 ; i >= 0 ; i--)
                S = S + vWords[i] + " ";
            return S.substr(0,S.length() - 1);
        }

        void ReverseStringWords()
        {   
            _Value = ReverseStringWords(_Value);
        }

        static string ReplaceWord(string S , string WhereToReplace , string WhatToReplaceWith  , bool MatchCase = true)
        {
            vector <string> vWords = Split(S , " ");
            for(string & Word : vWords)
            {
                if(MatchCase) 
                {
                    string S1 = LowerAllString(Word);
                    string S2 = LowerAllString(WhereToReplace);
                    if( S1 == S2)
                    {
                        Word = WhatToReplaceWith;
                    }
                }
                else
                {
                    if(Word == WhereToReplace)
                    {
                        Word = WhatToReplaceWith;
                    }
                }
            }   
            return JoinString(vWords , " ");
        }

        string ReplaceWord(string WhereToReplace , string WhatToReplaceWith  , bool MatchCase = true)
        {
            return ReplaceWord(_Value , WhereToReplace, WhatToReplaceWith, MatchCase);
        }

        static string RemovePunctuations(string S)
        {
            for(int i = 0 ; i < S.length(); i++)
                if(ispunct(S[i]))
                    S.erase(i--,1);
            return S;
        }

        string RemovePunctuations()
        {
            return RemovePunctuations(_Value);
        }

};
