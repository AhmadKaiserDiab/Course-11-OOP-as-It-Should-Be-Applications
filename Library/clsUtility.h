#pragma once
#include <iostream>
#include <ctime>
#include "clsString.h"
#include "clsDate.h"
using namespace std;

class clsUtility
{
    public:
        enum enCharType {
            CapitalLetter = 1, SmallLetter = 2,
            Digit = 3, MixChars = 4, SpecialCharacter = 5
        };

        static void Srand()
        {
            srand((unsigned)time(NULL));
        }

        static int RandomNumber(int From, int To)
        {
            int RandomNumber = rand() % (To - From + 1) + From;
            return RandomNumber;
        }

        static char GetRandomCharacter(enCharType CharType)
        {
            //updated this method to accept mixchars
            if (CharType == MixChars)
            {
                //Capital/Samll/Digits only
                CharType = (enCharType)RandomNumber(1, 3);
            }

            switch (CharType)
            {
                case enCharType::SmallLetter :
                {
                    return char(RandomNumber(97, 122));
                    break;
                }
                case enCharType::CapitalLetter:
                {
                    return char(RandomNumber(65, 90));
                    break;
                }
                case enCharType::Digit:
                {
                    return char(RandomNumber(48, 57));
                    break;
                }
                case enCharType::SpecialCharacter:
                {
                    return char(RandomNumber(33, 47));
                    break;
                }
                defualt:
                {
                    return char(RandomNumber(65, 90));
                    break;
                }
        }
        }

        static string GenerateWord(enCharType CharType, short WordLength)
        {
            string Word = "";
            for (short i = 1; i <= WordLength; i++)
            {
                Word = Word + GetRandomCharacter(CharType);
            }
            return Word;
        }

        static string GenerateKey(enCharType CharType = MixChars)
        {
            string Key = "";
            Key = Key + GenerateWord(CharType, 4) + "-" + 
                        GenerateWord(CharType, 4) + "-" + 
                        GenerateWord(CharType, 4) + "-" + 
                        GenerateWord(CharType, 4);
            return Key;
        }

        static void GenerateKeys(short NumberOfKeys, enCharType CharType )
        {
            for (short i = 1; i <= NumberOfKeys; i++)
            {
                cout << "Key [" << i << "]: " 
                    << GenerateKey(CharType) << endl;
            }
        }

        static void Swap(int &a, int &b)
        {
            int Temp = a;
            a = b;
            b = Temp;
        }

        static void Swap(double &a, double &b)
        {
            double Temp = a;
            a = b;
            b = Temp;
        }

        static void Swap(char &a, char& b)
        {
            char Temp;
            Temp = a;
            a = b;
            b = Temp;
        }

        static void Swap(bool &a, bool& b)
        {
            bool Temp;
            Temp = a;
            a = b;
            b = Temp;
        }

        static void Swap(string &a, string &b)
        {
            string Temp = a;
            a = b;
            b = Temp;
        }

        static void Swap(clsDate &a, clsDate &b)
        {
            clsDate ::SwapDates(a, b);
        }

        static void ShuffleArray(int Array[100], short Size)
        {
            for (short i = 0; i < Size; i++)
                Swap(Array[RandomNumber(1, Size) - 1],
                    Array[RandomNumber(1, Size) - 1]);
        }

        static void ShuffleArray(double Array[100], short Size)
        {
            for (short i = 0; i < Size; i++)
                Swap(Array[RandomNumber(1, Size) - 1],
                    Array[RandomNumber(1, Size) - 1]);
        }

        static void ShuffleArray(char Array[100], short Size)
        {
            for (short i = 0; i < Size; i++)
                Swap(Array[RandomNumber(1, Size) - 1],
                    Array[RandomNumber(1, Size) - 1]);
        }

        static void ShuffleArray(string Array[100], short Size)
        {
            for (short i = 0; i < Size; i++)
                Swap(Array[RandomNumber(1, Size) - 1],
                    Array[RandomNumber(1, Size) - 1]);
        }

        static void FillArrayWithRandomNumbers(int Array[100], short Size, short From, short To)
        {
            for (short i = 0; i < Size; i++)
            {
                Array[i] = RandomNumber(From, To);
            }
        }

        static void FillArrayWithRandomWords(string Array[100], short Size, enCharType CharType, short WordLength)
        {
            for (short i = 0; i < Size; i++)
            {
                Array[i] = GenerateWord(CharType, 8);
            }
        }

        static void FillArrayWithRandomKeys(string Array[100], short NumberOfKeys, enCharType CharType)
        {
            for (short i = 0; i < NumberOfKeys; i++)
                Array[i] = GenerateKey(CharType);
        }

        static string Tabs(short TabsNumber)
        {
            string Tab = "";
            for (short i = 1; i <= TabsNumber; i++)
                Tab = Tab + "\t";
            return Tab;
        }

        static string EncryptText(string Text, short EncryptionKey)
        {
            for (int i = 0; i < Text.size(); i++)
                Text[i] = char(Text[i] + EncryptionKey);
            return Text;
        }

        static string DecryptText(string EncryptedText, short EncryptionKey)
        {
            for (int i = 0; i < EncryptedText.length(); i++)
                EncryptedText[i] = char(EncryptedText[i] - EncryptionKey);
            return EncryptedText;
        }

        static string NumberToText(int Number)
        {
            if (Number == 0)
            {
                return "";
            }

            if (Number >= 1 && Number <= 19)
            {
                string arr[] = {"", "One", "Two",
                                "Three", "Four", "Five", "Six", "Seven",
                                "Eight", "Nine", "Ten", "Eleven", "Twelve",
                                "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                                "Seventeen", "Nineteen"};
                return arr[Number] + " ";
            }

            if (Number >= 20 && Number <= 99)
            {
                string arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty",
                                "Sixty", "Seventy", "Eighty", "Ninety"};
                return arr[Number / 10] + " " + NumberToText(Number % 10);
            }

            if (Number >= 100 && Number <= 199)
            {
                return "One Hundred " + NumberToText(Number % 100);
            }

            if (Number >= 200 && Number <= 999)
            {
                return NumberToText(Number / 100) + "Hundreds " +
                        NumberToText(Number % 100);
            }

            if (Number >= 1000 && Number <= 1999)
            {
                return "One Thousand " + NumberToText(Number % 1000);
            }
            
            if (Number >= 2000 && Number <= 999999)
            {
                return NumberToText(Number / 1000) + "Thousands " +
                        NumberToText(Number % 1000);
            }

            if (Number >= 1000000 && Number <= 1999999)
            {
                return "One Million " + NumberToText(Number % 1000000);
            }

            if (Number >= 2000000 && Number <= 999999999)
            {
                return NumberToText(Number / 1000000) + "Millions " +
                        NumberToText(Number % 1000000);
            }

            if (Number >= 1000000000 && Number <= 1999999999)
            {
                return "One Billion " + NumberToText(Number % 1000000000);
            }

            else
            {
                return NumberToText(Number / 1000000000) + "Billions " +
                        NumberToText(Number % 1000000000);
            }
        }
};