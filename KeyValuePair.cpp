//To Compile: g++ -std=c++11  -o  k KeyValuePair.cpp 
//To Run: ./k

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <cassert>
//Header File for C++ BigInt Integers because Input Size is extremely large. Reference: https://github.com/sercantutar/infint
#include "InfInt.h" 
using namespace std;
int main()
{
    //Both declared as InfInt variables since Input Size is extremely large and k is used to iterate over it.
    InfInt inputSize,k; 
    int looper,index,counter;
    //String array to hold the comma separated Key/Value pair from Standard Input
    std::string arrString[2];
    //Ordered String Multimap to hold the Key/Value pairs
    std::multimap<std::string,std::string> myMap;
    //Ordered String Set to not allow duplicate keys from printing
    std::set<std::string> mySet;
    std::multimap<std::string,std::string>::iterator itMap;
    cout<<"Enter size of input"<<endl;
    cin>>inputSize;
    cout<<"Enter comma separated values. One key/value pair per line."<<endl;
    cin.ignore();
    for(k=0;k<inputSize;k++){
        //Splitting each Comman delimited Input String into 2 separate Strings
        looper=0;
        std::string str;
        std::getline(std::cin,str);
        std::stringstream ss(str);
        string token;
        while (getline(ss,token, ','))
        {
            arrString[looper]=token;
            looper++;
        }
        //Inserting the Key/Value pair in Multimap
        myMap.insert(std::make_pair(arrString[0],arrString[1]));
    }
    cout<<"\n\nOutput\n";
    //Iterating through entire Multimap
    for(itMap=myMap.begin();itMap!=myMap.end();++itMap){
        //If key has not been seen previously, I print it
        if(mySet.find(itMap->first)==mySet.end()){
            cout<<itMap->first<<":"<<endl;
            //Insert seen Key in Set so that I don't print it again
            mySet.insert(itMap->first);
            //Iterating through all the Values of the Key just printed
            auto result=myMap.equal_range(itMap->first);
            for(auto mysearch=result.first;mysearch!=result.second;++mysearch){
                //Printing each Value under its Key, one line per Value
                cout<<mysearch->second<<endl;
            }
            cout<<"\n\n";
        }
    }
    //Unit Testing:
    std::set<std::string> testSet;
    assert(testSet.size()==0);
    testSet.insert("Avinaba");
    assert(testSet.size()==1);
    testSet.insert("Dasgupta");
    assert(testSet.size()==2);
    testSet.insert("Avinaba");
    assert(testSet.size()==2);
    assert(testSet.find("Avinaba")!=testSet.end());
    assert(testSet.find("Dasgupta")!=testSet.end());
    assert(testSet.find("Avinaba Dasgupta")==testSet.end());
    testSet.insert("Avinaba Dasgupta");
    assert(testSet.find("Avinaba Dasgupta")!=testSet.end());
    assert(testSet.size()==3);
    testSet.erase("Avinaba");
    assert(testSet.find("Avinaba")==testSet.end());
    assert(testSet.size()==2);
    testSet.clear();
    assert(testSet.size()==0);
    assert(testSet.find("Dasgupta")==testSet.end());
    std::multimap<std::string,std::string> testMap;
    assert(testMap.size()==0);
    testMap.insert(std::make_pair("1","value1"));
    testMap.insert(std::make_pair("1","value2"));
    testMap.insert(std::make_pair("2","value1"));
    testMap.insert(std::make_pair("2","value2"));
    assert(testMap.size()==4);
    assert(testMap.find("1")!=testMap.end());
    assert(testMap.find("2")!=testMap.end());
    assert(testMap.find("3")==testMap.end());
    std::string testKey[2]={"1","2"};
    std::string testValue[4]={"value1","value2","value1","value2"};
    index=counter=0;
    std::multimap<std::string,std::string>::iterator testItMap;
    for(testItMap=testMap.begin();testItMap!=testMap.end();++testItMap){
        if(testSet.find(testItMap->first)==testSet.end()){
            assert(testItMap->first==testKey[index++]);
            testSet.insert(testItMap->first);
            auto testResult=testMap.equal_range(testItMap->first);
            for(auto mysearch=testResult.first;mysearch!=testResult.second;++mysearch){
                assert(mysearch->second==testValue[counter++]);
            }
        }
    }
    return 0;
}