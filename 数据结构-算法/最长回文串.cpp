//最长回文串
//参考：https://articles.leetcode.com/longest-palindromic-substring-part-ii/
//https://www.felix021.com/blog/read.php?2040
//2018.4.11
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
std::string preProcess(std::string s) {
  int n = s.length();
  if (n == 0) return "^$";
  std::string ret = "^";
  for (int i = 0; i < n; i++)
    ret += "#" + s.substr(i, 1);
 
  ret += "#$";
  return ret;
}
std::string longestPalindrome(std::string s) {
  std::string T = preProcess(s);
  int n = T.length();
  int *P = new int[n];
  int C = 0, R = 0;
  for (int i = 1; i < n-1; i++) {
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
    P[i] = (R > i) ? std::min(R-i, P[i_mirror]) : 0;
    
    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
      P[i]++;
 
    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }
  // Find the maximum element in P.
  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n-1; i++) {
    if (P[i] > maxLen) {
      maxLen = P[i];
      centerIndex = i;
    }
  }
  delete[] P;
  
  return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}
//我自己的解法
int main()
{
	std::string str;
	std::cin>>str;
	//用来存储以第i个字符结尾的最长回文串
	std::vector<int> dp(str.length(),1);	
	for(int i=1;i<str.length();i++)
	{
		int index=i-dp[i-1]-1;
		if(index>=0&&str[index]==str[i])
			dp[i]=dp[i-1]+2;
		else
		{
			int count=1;
			for(int j=index+1;j<i;j++)
			{
				if(str[j]==str[i])
				{
					int flag=0;
					for(int m=j+1,n=i-1;m<=n;m++,n--)
					{
						if(str[m]!=str[n])
						{
							flag=1;
							break;
						}
					}
					if(flag==0&&(i-j+1)>count)
						count=i-j+1;

				}
			}
			dp[i]=count;
		}
	}
	for(auto i:dp)
		std::cout<<i<<" ";
	std::cout<<longestPalindrome(str);
	int a;
	std::cin>>a;
	return 0;
}