//To compile: g++ -std=c++11  -o  s StringReversal.cpp 
//To run: ./s

#include <iostream>
#include <string>
#include <cassert>
using namespace std;
//Boolean method to check if string is Palindrome
bool isPalindrome(string s){
    int length=s.length();
    for(int i=0;i<length/2;i++){
        if(s[i]!=s[length-1-i]){
            return false;
        }
    }
    return true;
}
//Method to reverse the string
string reverseString(string s) {
    //No need to reverse string consisting of only whitespace
    if(s.find_first_not_of(' ')==std::string::npos)
        return s;
    //No need to reverse empty string
    if(s=="")
        return s;
    //No need to reverse string of unit length
    if(s.length()==1)
        return s;
    //No need to reverse a Palindrome string
    if(isPalindrome(s))
        return s;
    //For all other cases, we reverse the string
    int length=s.length()-1;
    //String reversal is done without using auxillary string buffer or temporary variable
    for(int i=0;i<s.length()/2;i++){
        s[i]+=s[length];
        s[length]=s[i]-s[length];
        s[i]=s[i]-s[length--];
    }
    return s;
}
int main(){
    std::string myStr,raw_str1,raw_str2;
    cout<<"Enter Input String:"<<endl;
    std::getline(std::cin,myStr);
    myStr=reverseString(myStr);
    cout<<myStr<<endl;
    //Unit Testing:
    assert(reverseString("")=="");
    assert(reverseString(" ")==" ");
    assert(reverseString("      ")=="      ");
    assert(reverseString("a")=="a");
    assert(reverseString(".")==".");
    assert(reverseString("camac")=="camac");
    assert(reverseString("abcdedcba")=="abcdedcba");
    assert(reverseString("Avinaba")=="abanivA");
    assert(reverseString("142 783")=="387 241");
    assert(reverseString("Avinaba Dasgupta")=="atpugsaD abanivA");
    assert(reverseString("   Avi    ")=="    ivA   ");
    raw_str1=R"(\n\t)";
    raw_str2=R"(t\n\)";
    assert(reverseString(raw_str1)==raw_str2);
    raw_str1=R"("'"''"'"'"')";
    raw_str2=R"('"'"'"''"'")";
    assert(reverseString(raw_str1)==raw_str2);
    return 0;
}