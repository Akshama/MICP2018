/*
 Microsoft Interview Coaching Pilot Program MICP 2018
Author: Akshama
Language: C++
/**********WEEK TWO***********/
/*
3SUM: Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
Note: The solution set must not contain duplicate triplets.
For example, given array S = [-1, 0, 1, 2, -1, -4],
A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
//TEBOW IT
/*
1. T - TALK
Input: An array of integers (positive, negative or even 0). 
Output: Array elements that add up to zero, in the form of unique triplets.
Clarified:
Duplicate numbers - May be present
2. E - EXAMPLES
2.1 Valid Inputs and corresponding expected outputs:
	
	 	a. [-1, 0, 1, 2, -1, -4] -> [ [-1, 0, 1], [-1, -1, 2]]
	 	b. [-2,0,1,1,2] -> [[-2,0,2],[-2,1,1]]
	 	
2.2 Invalid Input and corresponding expected outputs:
	  
	  	a. [] -> NULL
	  	b. NULL ->  NULL
	  	c. [3] -> NULL
	  	d. [10, 10, 10] -> NULL (as it has no solution)

3. B - BRUTE-FORCE

4. O - OPTIMISE
Similar method as the 2Sum problem (Given an array of integers, return indices of the two numbers such that they add up to a specific target).
For each element of the input array, determine the 2Sum taking the target value as negative of the current value and remaining array as input to the 2Sum.
a + b = -c
From here, we have two solutions.
1. Binary Search 
  1.1 Insert all the element sum values (a[i]+a[j]) to a set, O(n*n).
  1.2 Check whether -c is in the set(log(n*n)) using Binary Search.
  (Sorting the array necessary before using binSearch, hence time complexity of O(nlogn) for sorting.
2. As in the 2sum problem, we can solve it in O(n) using the Two Scan method:
  Using two pointers, i and j. i begins from the starting index of the array while j begins from the end.
  a[i]+a[j] = target, find one, ++i, ++j
  a[i]+a[j] > target, --j;
  a[i]+a[j] < target, ++j;
  Using this, we get a time complexity of O(n^2).
  enum c: p[i]+p[j] ? c
5. W - WALK THROUGH
Explained as comments in the code
6. I - IMPLEMENT
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
vector<vector<int> > threeSum(vector<int> &num)
{
	//sort the array
    sort(num.begin(), num.end());
    //ret contains the resultant triplets
    vector<vector<int> > res;
    //tuple format of the result
    vector<int> tuples(3);
    for (int i = 0; i < (num.size() - 2); ++i) 
    {
      // ignore duplicate elements
    	if (i > 0 && num[i] == num[i-1])
    		continue;
      	//int target = -num[i];
      	int start = i+1, end = num.size()-1;
      	while (start < end) 
	{
			//found a triplet with sum as 0
        	if (num[start] + num[end] + num[i] == 0) 
		{
         		tuples[0] = num[i];
          		tuples[1] = num[start];
          		tuples[2] = num[end];
          		res.push_back(tuples);
          		++start;
          		--end;
        	} 	
		else if (num[start] + num[end] > (-num[i]))
          		--end;
        	else 
          		++start;  
       }
    }
    //if no such triplet exists, return null
    if (res.empty())
    	return vector<vector<int> >();
    //else, if solution(s) exist, return them as triplets
    sort(res.begin(), res.end());
    int len = 1;
    for (int i = 1; i < res.size(); ++i)
    	if (res[len-1] != res[i])
        	res[len++] = res[i];
    return vector<vector<int> >(res.begin(), res.begin()+len);
}
//6. T - TEST
//Multiple triplets exist
//[-1, 0, 1, 2, -1, -4] -> [ [-1, 0, 1], [-1, -1, 2]]
int testThreeSum1()
{
    int flag=0;
    freopen("test1.in", "r", stdin);
    vector<int> inp;
  	int a;
 	while (scanf("%d,", &a) != EOF )
    	inp.push_back(a);
	vector<vector<int> > computedRes = threeSum(inp);
	vector<vector<int> > actualRes{ { -1, -1, 2 },
                               { -1, 0, 1 }};
    for (int i = 0; i < computedRes.size(); ++i)
	{
    	for (int j = 0; j < 3; ++j)
      		{
      		    if(computedRes[i][j] == actualRes[i][j])
                    continue;
                else
                    {
                        flag=1;
                        break;
                    }
      		}
  	}
  	if(flag)
        cout<<"\nOne or more test cases failed\n";
    else
        cout<<"\nPassed\n";
  	return 0;
}

//When no such triplet exists
//[-1,1,2,-2] -> NULL
int testThreeSum2()
{
    int flag=0;
    freopen("test2.in", "r", stdin);
    vector<int> inp;
  	int a;
 	while (scanf("%d,", &a) != EOF )
    	inp.push_back(a);
	vector<vector<int> > computedRes = threeSum(inp);
	vector<vector<int> > actualRes{};
    for (int i = 0; i < computedRes.size(); ++i)
	{
    	for (int j = 0; j < 3; ++j)
      		{
      		    if(computedRes[i][j] == actualRes[i][j])
                    continue;
                else
                    {
                        flag=1;
                        break;
                    }
      		}
  	}
  	if(flag)
        cout<<"\nOne or more test cases failed\n";
    else
        cout<<"\nPassed\n";
  	return 0;
}

//Null input
int testThreeSum3()
{
    int flag=0;
    freopen("test3.in", "r", stdin);
    vector<int> inp;
  	int a;
 	while (scanf("%d,", &a) != EOF )
    	inp.push_back(a);
	vector<vector<int> > computedRes = threeSum(inp);
	vector<vector<int> > actualRes{};
    for (int i = 0; i < computedRes.size(); ++i)
	{
    	for (int j = 0; j < 3; ++j)
      		{
      		    if(computedRes[i][j] == actualRes[i][j])
                    continue;
                else
                    {
                        flag=1;
                        break;
                    }
      		}
  	}
  	if(flag)
        cout<<"\nOne or more test cases failed\n";
    else
        cout<<"\nPassed\n";
  	return 0;
}
int main() 
{
	freopen("input.in", "r", stdin);
  	vector<int> inp;
  	int a;
 	while (scanf("%d,", &a) != EOF )
    	inp.push_back(a);
	vector<vector<int> > result = threeSum(inp);
  	for (int i = 0; i < result.size(); ++i) 
	{
    		for (int j = 0; j < 3; ++j)
      			cout << result[i][j] << " ";
    		cout << endl;
  	}
	testThreeSum1();
  	testThreeSum2();
  	testThreeSum3();
  	return 0;
} 


