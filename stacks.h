#include <iostream>

#ifndef STACKS_H
#define STACKS_H

//write the code for stack template here...NOTE you are passing 
//size as paramter to the template
template <class typeName,int maxSize>		//NOTE how the template is written with maxSize as upper limit on stack size
class stack
{
public:
	//implement the interface
	stack(){size=maxSize;}
	bool push(typeName item)
	{
		if(full())
		{
			return false;
		}
		else 
		{
			arr[index]=item;
			index++;
		}
			return true;
	}
	bool pop(typeName &item)
	{
		if(empty()) return false;
		else 
		{
			index--;
			item=arr[index];
		}
		return true;
	}
	bool pop()
	{ //Pop without returning the top-value
		if(empty()) return false;
		else 
		{
			index--;
		}
		return true;
	}
	bool empty()
	{
		if(index==0) return true; 
		else return false;
	}
	bool full()
	{
		if(index==maxSize) return true;
		else return false;
	}
	void initialize(){index=0;};

private:
	//add your private members/methods here
	typeName arr[maxSize];			//maxSize is from template parameter
	int index;	//Index of arr
	int size;	//Size of Stack
};



#endif

