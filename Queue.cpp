//To Compile: g++ -o q Queue.cpp
//To run: ./q

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;
//Using template class to build generic Queue
template <class T>
class Queue{
private:
	std::stack<T> pushStack;
	std::stack<T> popStack;
public:
	Queue(){}
	void enqueue(T data){
		pushStack.push(data);
	}
	T dequeue(){
		if(!isEmpty()){
			T data;
			if(popStack.empty()){
				while(!pushStack.empty()){
					data=pushStack.top();
					pushStack.pop();
					popStack.push(data);
				}
			}
			data=popStack.top();
			popStack.pop();
			return data;
		}
	}
	bool isEmpty(){
		return pushStack.empty() && popStack.empty();
	}
};
int main(){
	Queue<std::string> q0;
	q0.enqueue("Avinaba");
	q0.enqueue("Dasgupta");
	cout<<q0.dequeue()<<endl;
	cout<<q0.dequeue()<<endl;
	Queue<int> q1;
	q1.enqueue(1);
	q1.enqueue(2);
	cout<<q1.dequeue()<<endl;
	cout<<q1.dequeue()<<endl;
	Queue<double> q2;
	q2.enqueue(1.544);
	q2.enqueue(2.873);
	cout<<q2.dequeue()<<endl;
	cout<<q2.dequeue()<<endl;
	Queue<char> q3;
	q3.enqueue('a');
	q3.enqueue('b');
	cout<<q3.dequeue()<<endl;
	cout<<q3.dequeue()<<endl;
	//Unit Testing:
	Queue<int> testQueue;
	assert(testQueue.isEmpty()==true);
	testQueue.enqueue(1);
	testQueue.enqueue(2);
	assert(testQueue.dequeue()==1);
	assert(testQueue.dequeue()==2);
	assert(testQueue.isEmpty()==true);
	testQueue.enqueue(NULL);
	assert(testQueue.dequeue()==0);
	assert(testQueue.isEmpty()==true);
	testQueue.enqueue(1);
	testQueue.enqueue(2);
	testQueue.dequeue();
	testQueue.enqueue(3);
	assert(testQueue.dequeue()==2);
	assert(testQueue.dequeue()==3);
	assert(testQueue.isEmpty()==true);
	return 0;
}