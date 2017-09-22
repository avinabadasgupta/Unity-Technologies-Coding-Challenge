//To compile: g++ -std=c++11  -o  s StatsCollector.cpp 
//To run: ./s

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
//Header File for C++ BigInt Integers because there are about 20,000 http requests/second. Reference: https://github.com/sercantutar/infint
#include "InfInt.h" 
using namespace std;
class StatsCollector{
private:
	std::vector<InfInt> responseBuffer;
	double average;
	int bufferSize;
	int timeout;
public:
	//Member functions, mostly used for testing
	StatsCollector();
	int getBufferSize();
	int getTimeOut();
	double getAverage();
	void pushValue(int);
	double getMedian();
	void clear();
	InfInt getDatatIndex(int);
};
//Constructor
StatsCollector::StatsCollector(){
	average=0;
	bufferSize=0;
	timeout=19000;
	//Limiting Vector size to 19000 and storing Frequency of every Respnse time from 0 to 19000
	for(int i=0;i<timeout;i++){
		responseBuffer.push_back(0);
	}
}
int StatsCollector::getBufferSize(){
	return bufferSize;
}
int StatsCollector::getTimeOut(){
	return timeout;
}
double StatsCollector::getAverage(){
	return average;
}
void StatsCollector::pushValue(int responseTimeMs){
	//If Response time is not a number
	if(isnan(responseTimeMs)){
		throw std::logic_error("Response Time is not a Number");
	}
	//If respnse time is lesser than 0
	if(responseTimeMs<0){
		throw std::logic_error("Response time cannot be Negative");
	}
	//If Response time is greater than timeout, I consider it as 19000
	if(responseTimeMs>=timeout){
		responseTimeMs=timeout;
	}
	int total=(average*bufferSize)+responseTimeMs;
	average=double(total)/(bufferSize+1);
	responseBuffer[responseTimeMs]=responseBuffer[responseTimeMs]+1;
	bufferSize++;
}
double StatsCollector::getMedian(){
	if(bufferSize>0){
		bool sizeEven=(bufferSize%2==0);
		int midBuffer;
      	if(sizeEven){
      		midBuffer=bufferSize/2;
      	}
      	else{
      		midBuffer=(bufferSize-1)/2;
      	}
      	InfInt sum=0;
      	int i=0,prevSum=0;
      	double result=0;
		while(sum<=midBuffer){
        	if (responseBuffer[i]>0){
        		sum=sum+responseBuffer[i];
          		if(sizeEven){
            		result=double(prevSum+i)/2;
            		prevSum=i;
          		}
        	}
        	i++;
      	}
      	if(!sizeEven){
      		result=i-1;
      	}
      	return result;
	} 
	else{
		return -1;
    }
}
void StatsCollector::clear(){
	std::fill(responseBuffer.begin(),responseBuffer.end(),0);
	bufferSize=average=0;
}
InfInt StatsCollector::getDatatIndex(int index){
	return responseBuffer[index];
}
int main(){
	//Unit Testing:
	StatsCollector s;
	assert(s.getBufferSize()==0);
	assert(s.getAverage()==0);
	assert(s.getTimeOut()==19000);
	s.pushValue(425);
	s.pushValue(181);
	s.pushValue(376);
	s.pushValue(12);
	s.pushValue(100);
	assert(s.getMedian()==181);
	assert(s.getDatatIndex(0)==0);
	assert(s.getDatatIndex(12)==1);
	assert(s.getDatatIndex(100)==1);
	assert(s.getDatatIndex(181)==1);
	assert(s.getDatatIndex(376)==1);
	assert(s.getDatatIndex(425)==1);
	assert(s.getBufferSize()==5);
	s.clear();
	assert(s.getBufferSize()==0);
	s.pushValue(1);
	s.pushValue(1);
	s.pushValue(2);
	s.pushValue(3);
	s.pushValue(4);
	assert(s.getMedian()==2);
	s.clear();
	s.pushValue(0);
	assert(s.getAverage()==0);
	s.pushValue(1);
	assert(s.getAverage()==0.5);
	s.clear();
	assert(s.getMedian()==-1);
	s.pushValue(1);
	assert(s.getMedian()==1);
	s.pushValue(2);
	assert(s.getMedian()==1.5);
	s.pushValue(2);
	assert(s.getMedian()==2);
	return 0;
}