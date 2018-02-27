/*
 Microsoft Interview Coaching Pilot Program MICP 2018
Author: Akshama
Language: C++
/**********WEEK THREE***********/
/*
Word Break
Given an input string and a dictionary of words, find out if the input string can be segmented into a space-separated sequence of dictionary words.
For example, consider the following dictionary: { pear, salmon, foot, prints, footprints, leave, you, sun, girl, enjoy },
Examples:
Given the string “youenjoy”,
Output: True (The string can be segmented as “you enjoy”)
Input: “youleavefootprints”,
Output: True (The string can be segmented as “you leave footprints” or “you leave foot prints”)
Input:salmonenjoyapples
Output: False

//TEBOW IT
/*
1. T - TALK
INPUT: Dictionary of String and a String
OUTPUT: Boolean - True/False
Clarified:
Null input string or null dictionary - Exception
Case sensitive -  Yes
Special characters - No
Empty string or Empty dictionary - Return False

2. E - EXAMPLES
2.1 Valid Inputs and corresponding expected outputs:

	 	a. Dictionary { 'he', 'heart', 'cat' }, String = 'heartcat' -> TRUE
	 	b. Dictionary { 'he', 'heart', 'art', 'artist' }, String = 'heartist' -> TRUE
	 	c. Dictionary {' '}, String = ' ' -> FALSE

2.2 Invalid Input and corresponding expected outputs:

	  	a. Dictionary is NULL, String is NULL -> Exception

3. B - BRUTE-FORCE

3.1
Find all possible ways of breaking up the input string. For each possible set of word breaks, check if one or more of them matches words in the dictionary.
If yes, return true, else return false.
Time complexity: O(2^n * m) where:
n = length of input string
m = length of word dictionary

3.2
Iterate over the entire length of the string character by character. If no match is found with the words in the dictionary even when you reach the end of the string, return false.
If you found a match, repeat this same algorithm for the remaining portion of the input string (i.e. recursive call)

Complexity
Time: O(2^n)
Space: O(n^2)

4. O - OPTIMISE
As we can see, the Word Break problem has an optimal substructure. Also, it can be broken down into multiple subproblems.
Hence, we can use Dynamic Programming to solve this problem wherein the subproblems will be memoised rather than being computed again and again.
-> Use an array for storing the results of the subproblems.
-> -1: not encountered, 0: encountered, 1: can be segmented i.e, one or more of the word breaks of the string matches words in the dictionary.
-> Consider all prefixes of the current string, If prefix is found in dictionary, then recurse for suffix.
5. W - WALK THROUGH
Explained as comments in the code
6. I - IMPLEMENT
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool wordBreak(vector<string> const &dict, string str, vector<int> &canBeSegmented)
{
    int len = str.size();
    if (len == 0)
        return true;
    //subproblem encountered for the first time
    if (canBeSegmented[len] == -1)
    {
        //mark subproblem as seen
        canBeSegmented[len] = 0;
        for (int i = 1; i <= len; i++)
        {
            // consider all prefixes of current string
            string prefix = str.substr(0, i);
            // if prefix is found in dictionary, then recurse for suffix
            if (find(dict.begin(), dict.end(), prefix) != dict.end() && wordBreak(dict, str.substr(i), canBeSegmented))
                return canBeSegmented[len] = 1;

        }
    }
    // return solution to current sub-problem
    return canBeSegmented[len];
}

//T - TEST
bool testWordBreak()
{
    vector<string> dict = { "pear", "salmon", "foot", "prints", "footprints", "leave", "you", "sun", "girl", "enjoy" ,"heart", "artist", "he", "art" };
    string str1 = ""; //empty dict and empty string
    string str2 = "heartist"; //string can be segmented
    string str3 = "You"; //case sensitivity
    vector<int> canBeSegmented1(str1.length() + 1, -1);
    if (wordBreak({""}, "",canBeSegmented1 )!= false) //empty dict and empty string
    {
        cout<<"\nOne or more test cases failed";
        return false;
    }
    vector<int> canBeSegmented2(str2.length() + 1, -1);
    if (wordBreak(dict,"youleavefootprints", canBeSegmented2)!=true) //string can be segmented
    {
        cout<<"\nOne or more test cases failed";
        return false;
    }
    vector<int> canBeSegmented3(str3.length() + 1, -1);
    if (wordBreak(dict,"You", canBeSegmented3)!=false)//case sensitivity
    {
        cout<<"\nOne or more test cases failed";
        return false;
    }
    cout<<"\nAll test cases passed";
    return true;
}
int main()
{
    vector<string> dict = { "pear", "salmon", "foot", "prints", "footprints", "leave", "you", "sun", "girl", "enjoy" ,"heart", "artist", "he", "art" };
    string str;
    cin>>str;
    if(str.length())
    {
        vector<int> canBeSegmented(str.length() + 1, -1);
        //subproblems vector, initialized as -1 for all values.
        // -1: not encountered, 0: encountered, 1: can be segmented i.e, one or more of the word breaks of the string matches words in the dictionary.
        if (wordBreak(dict, str, canBeSegmented))
            cout << "True";
        else
            cout << "False";
    }
    else
        cout << "False";
    testWordBreak();
    return 0;
}
