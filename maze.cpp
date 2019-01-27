#include <iostream>
#include <fstream>
#include "matrix.h"
#include "stacks.h"
#include "maze.h"
using namespace std;


bool Grid::ReadGridAndStartEnd(char *FileName,point &start,point &end)
{
	int rows,cols;
	int i,j,temp;
	ifstream stream(FileName);
	if (!stream.is_open())
		return false;
	
	stream >>rows;
	stream >>cols;
	start.TakeInput(stream);
	end.TakeInput(stream);
	
	
	maze.initialize(rows,cols);
	visited.initialize(rows,cols);

	//Highlight the Starting and Ending points in Visited Maze
	i=start.getx();
	j=start.gety();
	visited.Set(i,j,1);

	i=end.getx();
	j=end.gety();
	visited.Set(i,j,1);

	for (i=0;i<rows;++i)
	{	for (j=0;j<cols;++j)
		{	
			stream >> temp;
			maze.Set(i,j,temp);
		}
	}

	return true;
}

bool Grid::Write_VisitedNExact_Path()
{
	if(Maze_Complete==false) 
	{
			cout<<endl<<"As Maze was not Completed , So No Possible paths can be written. Please modify Grid.txt and try again ! "<<endl;
			return false;
	}
	ofstream ofile_Full("path.txt");
	ofstream ofile_Visited("visited.txt");
	
	//For Full/Exact Path
	int rows=maze.GetRows();
	int cols=maze.GetCols();
	int val=0;

	for(int i=0;i<rows;i++)
	{	
		for(int j=0;j<cols;j++)
		{
			maze.Get(i,j,val);
			ofile_Full<<val<<"\t\t";
		}
			ofile_Full<<endl;
	}

	//For Visited Path

	 rows=visited.GetRows();
	cols=visited.GetCols();
	 bool value=0;

	for(int i=0;i<rows;i++)
	{	
		for(int j=0;j<cols;j++)
		{
			visited.Get(i,j,value);
			ofile_Visited<<value<<"\t\t";
		}
			ofile_Visited<<endl;
	}



	return true;
}


int main()
{
	Grid g;
	point start;
	point end;
	g.ReadGridAndStartEnd("grid.txt",start,end);	
	//implement the navigate function
	g.Navigate(start,end);
	//now add functions to print the results to file and call them here
	g.Write_VisitedNExact_Path();

} 

