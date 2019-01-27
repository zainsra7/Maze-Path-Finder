#ifndef MATRIX_H
#define MATRIX_H

#include<windows.h>
#include <iostream>
using namespace std;

template <class elementType>
class TwoDMatrix
{
public:
	//constructor
	TwoDMatrix(int TotalRows,int TotalCols);
	//destructor
	~TwoDMatrix();
	//Copy constructor 
	TwoDMatrix( const TwoDMatrix& mat );
	//operator =
	//FILL HERE AND MAKE A DEEP COPY	
	TwoDMatrix& operator =(const TwoDMatrix &mat);

	void initialize(int TotalRows,int TotalCols);
	//input the matrix from the user
	//the user will input Row by row
	void TakeInput();

	//return the total rows of the matrix
	int GetRows();

	//return the total cols of the matrix
	int GetCols();

	//Get a value of an element at index i,j and return in val
	//return false on error and true on valid operation
	bool Get(int i,int j,elementType &val);

	//set the value of an element at location i,j to val
	//return false on error and true on valid operation
	bool Set(int i,int j,elementType val);
	//return the actual index of item (i,j) in the 1D array where it is stored
	int GetActualLocation(int i,int j);	

	//should print the matrix in 2D matrix form (Modified it to highlight Staerting and Ending points of the maze)
	void Print(); 

	//Multiply this matrix with matrix a and store the result in res
	//return false on error and true on valid operation
	bool Multiply(TwoDMatrix &a,TwoDMatrix *res);
	
	//Add this matrix to matrix a and store the result in res
	//return false on error and true on valid operation
	bool Add(TwoDMatrix &a,TwoDMatrix *res);

	//Print for Visited Matrix and full_path Matrix
	void Print(int x);
	
	
private:
	elementType *Arr;  //the array has to be stored in a single dimension using row major order
	int row,col;
	int size; 
};

//add the implementation of the functions here and NOT INLINE
template <class T>
//Overloaded Constructor
TwoDMatrix<T>::TwoDMatrix(int TotalRows,int TotalCols){
	row=TotalRows; 
	col=TotalCols;
	size=row*col;
	Arr=new T[size];
	for(int i=0;i<size;i++)
		Arr[i]=0;
} 

template <typename T>
//Destructor
TwoDMatrix<T>::~TwoDMatrix(){delete []Arr;} //Giving the Memory back to Heap

template <class T>
//Copy Constructor 
TwoDMatrix<T>::TwoDMatrix( const TwoDMatrix& mat )
{
	row=mat.row;
	col=mat.col;
	size=mat.size;
	Arr= new T[size];
	for(int i=0;i<size;i++)
		Arr[i]=mat.Arr[i];
} 
template <class T>
//Assingment Operator =
TwoDMatrix<T>& TwoDMatrix<T>::operator=(const TwoDMatrix& mat)
{
	if(this!= &mat)
	{
	row=mat.row;
	col=mat.col;
	size=mat.size;
	delete []Arr;
	Arr=new T[size];
	for(int i=0;i<size;i++)
		Arr[i]=mat.Arr[i];
	}
	return *this;
}  

template <class T>
//Initializing Matrix 
void TwoDMatrix<T>::initialize(int TotalRows,int TotalCols)
{
	row=TotalRows; 
	col=TotalCols;
	size=row*col;
	Arr=new T[size];
	for(int i=0;i<size;i++)
		Arr[i]=0;
}
template <class T>
//Take Input () , Prompting for Input
void TwoDMatrix<T>::TakeInput()
{
	T x;	//Used to store the user Input
	int index=0;	//Used to control the index of Array
	cout<<endl<<"It's a "<<row<<" x "<<col<<" Matrix"<<endl;
	for (int i=0; i<row;i++)  
	{
		for(int j=0;j<col;j++)
	{
		cout<<"Please Enter a Valid Input = ";
		cin>>x;
		index=i*col+j;
		Arr[index]=x;
	}
	
	}
	cout<<endl;
} 
template <class T>
//GetCols()
int TwoDMatrix<T>::GetCols(){return col;} //Returning the Columns of a Matrix

template <class T>
//Get Rows()
int TwoDMatrix<T>::GetRows(){return row;} //Returning the Rows of a Matrix

template<class T>
//Getter for Element of a Matrix at location (i,j)
bool TwoDMatrix<T>::Get(int i,int j,T &val)
{
	if(i<0 || j<0 || i>row || j>col) return false;	//Invalid Coordinates
	int index=i*col+j;	//Formula to access the (i,j) element in 1D array in row major order
	val=Arr[index];
	return true;
}

template <class T>
//Setter for Element into a Matrix at location (i,j)
bool TwoDMatrix<T>::Set(int i,int j,T val)
{
	if(i<0 || j<0 || i>row || j>col) return false;	//Invalid Coordinates
	int index=i*col+j;	//Formula to access the (i,j) element in 1D array in row major order
	Arr[index]=val;
	return true;
}
template <class T>
//Getter for Actual location of element in 1D Array 
int TwoDMatrix<T>::GetActualLocation(int i,int j)
{
	int index=i*col+j; 
	return index;	//returning Index i.e the Actual location in 1D Array form
}

template <class T>
//Print () for Printing a Matrix
void TwoDMatrix<T>::Print()
{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);	//Used for Changing text color

		int index=0;
		cout<<endl<<"Origional Maze"<<endl;
		SetConsoleTextAttribute(console, 224);	//Black =0 , Yellow=14 so 0+14*16 = Black Foreground + Yellow background
		cout<<endl<<"   ";

	for(int i=0;i<col;i++)
		cout<<i<<"  ";
		cout<<endl;

	for(int i=0;i<row;i++)
	{
		SetConsoleTextAttribute(console, 224);	
		if(i<=9)cout<<i<<"  "; 
		else cout<<i<<" ";
		SetConsoleTextAttribute(console, 240);	//Black Foreground + White background
		for(int j=0;j<col;j++)
		{
		index=i*col+j;
		cout<<Arr[index]<<"  ";
		}
		cout<<endl;
	}
		cout<<endl;
		SetConsoleTextAttribute(console, 7);	//Default 
		
} 

template <class T>
//Multiply () for Multiplication of Two matrices.
bool TwoDMatrix<T>::Multiply(TwoDMatrix &a,TwoDMatrix *res)
{
	if(col!= a.row){return false;} //condition for Multiplication (Column of first matrix must be equal to the row of second matrix)

	int m=0,count=1,index=0,k=0; //k is used in indexing for the 'This'/calling matrix , m is used in indexing for 'a' matrix , 'index' is used in indexing of 'res' matrix and count is used for counting number of steps in every complete process (e.g in a 2x2 * 2x3 ,when count becomes greater than (2*3) will indicate that the first row has been calculated) 
	T sum;	//To store the sum of calculation
	
	
	res->row=row;	//Row of first matrix as the Row of Resultant matrix
	res->col=a.col;	//Column of First matrix as the column of Resultant Matrix
	res->size=(res->row)*(res->col); //Calculating Size of Resultant Matrix
	res->Arr=new T[res->size];	//Creating Resultant Arr

	for(int i=0;i<size;i=i+col){ //Loop for controling the Rows of the first matrix
		k=i;
		while(count<(a.size)){ // Process till count < size of resultant matrix
		for(int j=0;j<col;j++)	//Loop for controlling the Columns of the first matrix
		
		{		sum=sum+ (Arr[k]*a.Arr[m]);	//Calculating Sum
				m=m+a.col;	//Increasing Index of Second Matrix to the location for next calculation 
				if(m>=a.size) m=(m%a.col)+1;	//If m index goes out of bounds from the Arr array of resulatnt matrix
				count++; //Incrementing count
				k++; //Incrementing k 
		}
		
		res->Arr[index++]=sum;	//Storing the result in resulatnt matrix Array
		sum=0; //Initializing sum to 0
		k=i; //Initializing k back to the first element of the current row of the Matrix 1 
		}
		count=1;	//Initializing count to 1 for the next row of resultant matrix  
		m=0;		//Intizialing m back to the first element of Matrix 2 
	}
	return true;  
}
	
template <class T>
//Add() for Addition of Two Matrices
bool TwoDMatrix<T>::Add(TwoDMatrix &a,TwoDMatrix *res)
{
	if(row!= a.row || col!=a.col){return false;} //Condition for Addition ( Row and Col of A and B must be eqaul)
	
	T sum;	//Used to store calculation result

	//Initializing the resultant matrix
	res->row=row;
	res->col=col;
	res->size=(res->row)*(res->col);
	res->Arr=new T[res->size];
	
	int index=0; //Used to control the Index of all the three Matrices

	for(int i=0;i<row;i++)//Loop for Controling the Row
	{
			for(int j=0;j<col;j++) //Loop for controlling the Column
			{
				index=i*col+j; //Formula to caclulate the correct Index location
				sum=Arr[index]+a.Arr[index];
				res->Arr[index]=sum;
			}	
	
	
	}
	return true;
} 

template <class T>
//Print(x) to Highlight the 1's in the Matrix.
void TwoDMatrix<T>::Print(int x) //Print For Visited Matrix and Full_path matrix	
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);	//Used for Changing text color

		int index=0;
		SetConsoleTextAttribute(console, 224);	//Black =0 , Yellow=14 so 0+14*16 = Black Foreground + Yellow background
		cout<<endl<<"   ";

	for(int i=0;i<col;i++)
		cout<<i<<"  ";
		cout<<endl;

	for(int i=0;i<row;i++)
	{
		SetConsoleTextAttribute(console, 224);	
		if(i<=9)cout<<i<<"  "; 
		else cout<<i<<" ";
		SetConsoleTextAttribute(console, 240);	//Black Foreground + White background
		for(int j=0;j<col;j++)
		{
		index=i*col+j;
		if(Arr[index]==1) 
		{
			SetConsoleTextAttribute(console, 176); //Black Foreground + Light Blue background
			cout<<Arr[index]<<"  ";
			SetConsoleTextAttribute(console, 240);
		}
		else cout<<Arr[index]<<"  ";
		}
		cout<<endl;
	}
		cout<<endl;
		SetConsoleTextAttribute(console, 7);	//Default 



}


#endif
