/*
 Microsoft Interview Coaching Pilot Program MICP 2018
Author: Akshama
Language: C++

/**********WEEK ONE***********/
/*
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.


//TEBOW IT

/*
1. T - TALK
Input: A string which may contain alphabets, numbers or special characters.
Output: An integer (length of the longest substring without repeating characters)

Clarified:
Handling Special Characters and Numbers - Handled in the same way as characters
Case sensitivity - Yes
Space separated strings - Considered Valid

2. E - EXAMPLES
Sample Input  ---- Output
abcabcbb            3
bbbb                1
pwwkew              3
Cbcdb               4
*empty string*      0
abc def             7


3. B - BRUTE-FORCE

Check for all substrings starting from each letter of the string and return the longest substring with no repeating characters.
For n*(n+1)/2 substrings, linear scanning would be done for unique characters with a time complexity of O(n^3).
4. O - OPTIMISE
Create a sliding window type of structure that updates the start pointer on each repetition of a character. A substring which is already checked isn't searched again.
Optimised time complexity is O(n).
5. W - WALK THROUGH
Explained as comments in the code
6. I - IMPLEMENT
*/
#include<iostream>
#include<string>
#include<utility>
#include<vector>

using namespace std;

int longestSubstring(string str)
{

    vector<int> visited(256,-1);
    //length of the current substring without any repeating character
    int curr=0;
    //length of the longest substring without any repeating character
    int longest=0;
    for(int i=0;i<str.length();i++)
    {

        //if this character is not yet processed/ processed but not present in current substring which is started again
        if(visited[str[i]]==-1 || visited[str[i]]<(i-curr) )
        {
            curr++;
            //Update the visited array value with the current index of the character
            visited[str[i]]=i;

            if(curr>longest)
                longest=curr;
        }

        else
        {
            //case of repetition of a character
            //reset the length of current substring without any repeating character and update the visited array value with the current index of the character.
            curr=i-visited[str[i]];
            visited[str[i]]=i;
        }

    }

    return longest;
}

//7. T - TEST

bool testlongestSubstring()
{
	//test for empty string
	if(longestSubstring("")!=0)	return false;
	//test for string with single character
	if(longestSubstring("a")!=1) return false;
	//test for string with multiple non repeating characters
	if(longestSubstring("abc")!=3) return false;
	//test for string with no repeating characters (different cases)
	if(longestSubstring("Bcdb")!=4) return false;
	//test for string with special characters and numbers
	if(longestSubstring("%#$909")!=5) return false;
	//test for string with spaces
	if(longestSubstring("abc def")!=7) return false;
	//test for string with all same characters
	if(longestSubstring("bbbbb")!=1) return false;

}
int main()
{
    string input;
    getline(cin, input);
    cout<<longestSubstring(input);
    if (testlongestSubstring())
		cout<<"\nAll test cases passed.";
	else
		cout<<"\nOne or more test cases failed.";
    return 0;
}

