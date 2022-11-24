/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <cctype>
#include <fstream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include "hashmap.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;

/* This function is intended to return a string which
 * includes only the letter characters from the original
 * (all non-letter characters are excluded)
 *
 * WARNING: The provided code is buggy!
 *
 * Use test cases to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string lettersOnly(string s)
{
    string result = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (isalpha(s[i]))
        {
            result += s[i];
        }
    }
    return result;
}

const string MAPS_TO_ZERO = toLowerCase("AEIOUHWY");
const string MAPS_TO_ONE = toLowerCase("BFPV");
const string MAPS_TO_TWO = toLowerCase("CGJKQSXZ");
const string MAPS_TO_THREE = toLowerCase("DT");
const string MAPS_TO_FOUR = toLowerCase("L");
const string MAPS_TO_FIVE = toLowerCase("MNB");
const string MAPS_TO_SIX = toLowerCase("R");

string encodeLetters(const string &letters)
{
    string encoded = "";
    for (auto letter : toLowerCase(letters))
    {

        if (stringContains(MAPS_TO_ZERO, letter))
        {
            encoded += "0";
        }
        else if (stringContains(MAPS_TO_ONE, letter))
        {
            encoded += "1";
        }
        else if (stringContains(MAPS_TO_TWO, letter))
        {
            encoded += "2";
        }
        else if (stringContains(MAPS_TO_THREE, letter))
        {
            encoded += "3";
        }
        else if (stringContains(MAPS_TO_FOUR, letter))
        {
            encoded += "4";
        }
        else if (stringContains(MAPS_TO_FIVE, letter))
        {
            encoded += "5";
        }
        else if (stringContains(MAPS_TO_SIX, letter))
        {
            encoded += "6";
        }
    }

    return encoded;
}

string removeAdjacentDuplicates(const string &str)
{
    if (!str.length())
        return "";

    string coalesced = "";
    size_t i = 1;
    size_t n = str.length();

    coalesced += str[0];

    while (i < n)
    {
        if (str.at(i - 1) != str.at(i))
        {
            coalesced += str.at(i);
        }
        i++;
    }

    return coalesced;
}

string removeZeros(const string &str)
{
    return stringReplace(str, "0", "");
}

string soundex(string s)
{

    string result = "";

    result += removeAdjacentDuplicates(encodeLetters(s));

    result[0] = toUpperCase(s[0]);

    result = removeZeros(result);

    if (result.length() < 4)
    {
        string zeros(4 - result.length(), '0');
        result += zeros;
    }

    return result.substr(0, 4);
}

void soundexSearch(string filepath)
{
    // This provided code opens the specified file
    // and reads the lines into a vector of strings
    ifstream in;
    Vector<string> allNames;
    HashMap<string, Vector<string> *> encodedNames{};

    if (openFile(in, filepath))
    {
        readEntireFile(in, allNames);
    }
    cout << "Read file " << filepath << ", "
         << allNames.size() << " names found." << endl;

    for (auto name : allNames)
    {
        auto code = soundex(name);

        if (encodedNames.containsKey(code))
        {
            auto *vec = encodedNames.get(code);
            vec->add(name);
        }
        else
        {
            Vector<string> *names = new Vector<string>{};
            names->add(name);
            encodedNames.put(code, names);
        }
    }

    // The names read from file are now stored in Vector allNames
    string surname = "";
    do
    {
        surname = getLine("Enter a surname (RETURN to quit): ");

        auto code = soundex(surname);
        auto *vec = encodedNames.get(code);
        vec->sort();
        cout << "Matches from database: " << *vec << "\n";

    } while (surname.length());
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Test exclude of punctuation, digits, and spaces")
{
    string s = "O'Hara";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "tldr");
}

PROVIDED_TEST("Sample inputs from handout")
{
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase")
{
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase")
{
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros")
{
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen")
{
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels")
{
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel")
{
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes")
{
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes")
{
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's")
{
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh")
{
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case")
{
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

STUDENT_TEST("lettersOnly")
{
    EXPECT_EQUAL(lettersOnly("Van Niekerk"), "VanNiekerk");
    EXPECT_EQUAL(lettersOnly(" 23ABC"), "ABC");
    EXPECT_EQUAL(lettersOnly("abc1234 "), "abc");
    EXPECT_EQUAL(lettersOnly("#12AcC#@"), "AcC");
}

STUDENT_TEST("encodeLetters")
{
    EXPECT_EQUAL(encodeLetters("ABC"), "012");
    EXPECT_EQUAL(encodeLetters("Lod"), "403");
    EXPECT_EQUAL(encodeLetters("rob"), "601");
    EXPECT_EQUAL(encodeLetters("NIL"), "504");
}

STUDENT_TEST("removeAdjacentDuplicates")
{
    EXPECT_EQUAL(removeAdjacentDuplicates(""), "");
    EXPECT_EQUAL(removeAdjacentDuplicates("1"), "1");
    EXPECT_EQUAL(removeAdjacentDuplicates("11"), "1");
    EXPECT_EQUAL(removeAdjacentDuplicates("1111"), "1");
    EXPECT_EQUAL(removeAdjacentDuplicates("112233"), "123");
    EXPECT_EQUAL(removeAdjacentDuplicates("222025"), "2025");
    EXPECT_EQUAL(removeAdjacentDuplicates("12345"), "12345");
}
