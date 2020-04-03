//
// Created by zyl on 2020/3/16.
//

#include "function_defs.h"


/******************************************************************************************/
/* Description: For strings S and T, we say "T divides S" if and only if S = T + ... + T 
 * (T concatenated with itself 1 or more times) Return the largest string X such that
 * X divides str1 and X divides str2.*/
/******************************************************************************************/
string Solution::gcdOfStrings(string str1, string str2) {
    int L = 0;
    int L1 = str1.size();
    int L2 = str2.size();
    if (L1 > L2)
        L = L2;
    else
        L = L1;
    string result;
    string strNow;
    int now_L = 0;
    while (L > 0) {
        if (L1 % L == 0 && L2 % L == 0) {
            if (!strNow.empty())
                strNow.clear();
            result = str1.substr(0, L);
            now_L = L;
            while (now_L <= L1 || now_L <= L2) {
                strNow += result;
                if (now_L <= L1 && strNow != str1.substr(0, now_L))
                    break;
                if (now_L <= L2 && strNow != str2.substr(0, now_L))
                    break;
                now_L += L;
            }
            if (now_L > L1 && now_L > L2)
                return result;
        }
        L--;
    }
    return "";
}

/******************************************************************************/
/* Description: Implement a method to perform basic string compression using
 * the counts of repeated characters. For example, the string aabcccccaaa would
 * become a2blc5a3. If the "compressed" string would not become smaller than
 * the original string, your method should return the original string.
 * You can assume the string has only uppercase and lowercase letters (a - z).*/
/******************************************************************************/
string Solution::compressString(string S) {
    if (S.empty())
        return "";
    string result;
    int num = 1;
    for (int i = 1; i < S.size(); i++) {
        if (S[i] == S[i-1])
            num++;
        else {
            result.push_back(S[i - 1]);
            string strNum = to_string(num);
            for (auto str: strNum)
                result.push_back(str);
            num = 1;
        }
    }
    result.push_back(S[S.size()-1]);
    string strNum = to_string(num);
    for (auto str: strNum)
        result.push_back(str);
    if (result.size() >= S.size())
        return S;
    else
        return result;
}

/********************************************************************************************************************/
/****************************************************** Solution: ***************************************************/
/* Solution 1: Use a map to store the char in chars and its count --need optimize                                   */
/* Solution 2: Use a vector to store and then find it directly because they are all a-z -- optimization 03//17/2020 */
/********************************************************************************************************************/
int Solution::countCharacters(vector<string> &words, string chars) {
   vector<int> char_num(26, 0);
   for (auto ch: chars)
       char_num[ch-'a']++;
   vector<int> temp;
   int count;
   int result = 0;
   for (auto word: words) {
       temp = char_num;
       count = 0;
       for (auto ch: word) {
           temp[ch-'a']--;
           if (temp[ch-'a'] < 0)
               break;
           else
               count++;
       }
       if (count == word.size())
           result += count;
   }
    return result;
}

/***********************************************************************************************/
/* Description: Given a list of words, we may encode it by writing a reference string S and a
 * list of indexes A. For example, if the list of words is ["time", "me", "bell"], we can write
 * it as S = "time#bell#" and indexes = [0, 2, 5].
 *
 * Then for each index, we will recover the word by reading from the reference string from that
 * index until we reach a "#" character.
 * What is the length of the shortest reference string S possible that encodes the given words?
 *
 * Solution 1:  use a vector (size 26) to store the list of words that end of index = end - 'a',
 * then find if current word is covered
 * Solution 2:  Trie (字典树) */
/***********************************************************************************************/

struct TrieNode {
    vector<TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false), children(26, nullptr) {}
};

int Solution::minimumLengthEncoding(vector<string> &words) {
    auto* root = new TrieNode();
    int length = 0;
    for (auto word : words) {
        int temp_length = 0;
        TrieNode* p = root;
        for (int i = word.size()-1; i >= 0; i--) {
            temp_length++;
            int pos = word[i] - 'a';
            if (!(p->children[pos])) {
                p->children[pos] = new TrieNode();
                if (i == 0) {
                    length += temp_length + 1;
                    p->isEndOfWord = true;
                }
            } else if (p->isEndOfWord && i != 0) {
                length -= temp_length + 1;
                p->isEndOfWord = false;
            }
            p = p->children[pos];
        }
    }
    delete root;
    return length;
}


/**************************************************************************************/
/* Description: Given a VPS seq, split it into two disjoint subsequences A and B,
 * such that A and B are VPS's (and A.length + B.length = seq.length).
 *
 * Now choose any such A and B such that max(depth(A), depth(B)) is the minimum
 * possible value.
 *
 * Return an answer array (of length seq.length) that encodes such a choice of A and B: 
 * answer[i] = 0 if seq[i] is part of A, else answer[i] = 1.  Note that even though
 * multiple answers may exist, you may return any of them.
 *
 * Solution:    naive method, two traverse,
 *              First determine the depth
 *              Then the minimum depth is determined and split */
/**************************************************************************************/
vector<int> Solution::maxDepthAfterSplit(string seq) {
    // first traverse, find the depth
    int count = 0;
    int depth = 0;
    for (auto a : seq) {
        if (a == '(') {
            count++;
            if (count > depth)
                depth = count;
        } else
            count--;
    }
    int max_split_depth = depth / 2;
    vector<int> result;
    count = 0;
    // second traverse, when go into depth deeper than max_depth, split it out
    for (auto a : seq) {
        if (a == '(') {
            count++;
            if (count <= max_split_depth)
                result.push_back(0);
            else
                result.push_back(1);
        } else {
            count--;
            if (count < max_split_depth)
                result.push_back(0);
            else
                result.push_back(1);
        }
    }
    return result;
}

/****************************************************************************************/
/* Description: Implement atoi which converts a string to an integer.
 * The function first discards as many whitespace characters as necessary until
 * the first non-whitespace character is found. Then, starting from this character,
 * takes an optional initial plus or minus sign followed by as many numerical digits as
 * possible, and interprets them as a numerical value.
 *
 * The string can contain additional characters after those that form the integral number,
 * which are ignored and have no effect on the behavior of this function.
 *
 * If the first sequence of non-whitespace characters in str is not a valid integral
 * number, or if no such sequence exists because either str is empty or it contains only
 * whitespace characters, no conversion is performed. If no valid conversion could be
 * performed, a zero value is returned.*/
/****************************************************************************************/
int Solution::myAtoi(const string& str) {
    int start = 0;
    while (start < str.size()) {
        if (str[start] != ' ')
            break;
        start++;
    }
    bool negative = false;
    if (str[start] == '-') {
        negative = true;
        start++;
    } else if (str[start] == '+')
        start++;
    int end = start;
    int new_start = -1;
    long result = 0;
    while (end < str.size()) {
        int digit = str[end] - '0';
        if (new_start < 0 && digit != 0)
            new_start = end;
        if (digit < 0 || digit > 9)
            break;
        else
            result = result * 10 + digit;
        if (new_start >= 0 && end - new_start > 9)
            return negative ? -2147483648 : 2147483647;
        end++;
    }
    if (result) {
        if (negative) {
            if (result <= 2147483648)
                return 0 - result;
            else
                return -2147483648;
        } else {
            if (result <= 2147483647)
                return result;
            else
                return 2147483647;
        }
    }
    else
        return 0;
}