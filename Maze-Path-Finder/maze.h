enum actions{UP,DOWN,LEFT,RIGHT};
//coordinates of a state
using namespace std;
class point
{
public:
	point(){x=-1;y=-1;};
	point(int tx,int ty){x=tx;y=ty;}
	point(const point &source){x=source.x;y=source.y;}
	point & operator=(const point &source) {x=source.x;y=source.y;return *this;}
	bool operator != (const point &p){return (x!=p.x || y!=p.y);}
	bool operator == (const point &p){return (x==p.x && y==p.y);}
	void TakeInput(std::ifstream &stream){stream >> x;stream >> y;} //Added , std before ifstream to counter the 'undeclared identifier ifstream' error. 

	int getx(){return x;}
	int gety(){return y;}
	void setx(int xx){x=xx;}
	void sety(int yy){y=yy;}
private:
	int x;
	int y;
};


class Grid
{
public:
	bool ReadGridAndStartEnd(char *FileName,point &start,point &end);
	//you have to implement
	bool Navigate(point start,point goal);	
	//Writing Visited and Full/Exact Path to "visited.txt" and "path.txt" 
	bool Write_VisitedNExact_Path();	//Implementation is in maze.cpp 
	//Default Constructor
	Grid();
	//Actions {UP,Down,Left,Right} to check corresponding locations of current point 
	bool UP(point current);
	bool Down(point current);
	bool Left(point current);
	bool Right(point current);

	void Visit_Point(point current);
	bool Already_Visited(point current);
private:
	TwoDMatrix<int> maze;   //stores the actual maze...note this is from assignment 1
	//add private members like the stack for points to visit etc.
	//also you can add a TwoDMatrix of type bool to store whether a point is visited or not.
	stack<point,50> pointStack;	
	TwoDMatrix<bool> visited;	//Visited Matrix to Store all the Visited Points
	bool Maze_Complete; //If No Possible paths were located in Maze then Maze_Complete will be false and vice versa
};

Grid::Grid() :maze(0,0),visited(0,0){} //to counter the 'No default constructor exist' error

//{UP,DOWN,LEFT,RIGHT} functions
bool Grid::UP(point current)
{
		int x=current.getx()-1;	//row-1
		int y=current.gety();
		int item;				//To check legal location 
		bool location=false;	//To check validity of coordinate points
	
		location=maze.Get(x,y,item);
	if(location==true && item==1) 	return true;
		
		return false;

}
bool Grid::Down(point current)
{
		int x=current.getx()+1;	//Row+1
		int y=current.gety();
		int item;				//To check legal location 
		bool location=false;	//To check validity of coordinate points
	
		location=maze.Get(x,y,item);
	if(location==true && item==1) return true;
		
		
		return false;
}
bool Grid::Left(point current)
{
		int x=current.getx();
		int y=current.gety()-1;	//y-1
		int item;				//To check Legal Location 
		bool location=false;	//To check validity of coordinate points
	
		location=maze.Get(x,y,item);
	if(location==true && item==1) return true;
		
		
		return false;
}
bool Grid::Right(point current)
{
		int x=current.getx();
		int y=current.gety()+1;	//y+1
		int item;				//To check legal Location
		bool location=false;	//To check validity of coordinate points
	
		location=maze.Get(x,y,item);
	if(location==true && item==1) return true;
		
		
		return false;
}

//Visit a Point for the firt time
void Grid::Visit_Point(point current)
{
	int x=current.getx();	
	int y=current.gety();

	visited.Set(x,y,1);
} 
//Check for Already Visited Point
bool Grid::Already_Visited(point current)
{
	int x=current.getx();	//x-coordinate of point current
	int y=current.gety();	//y-coordinate of point current
	bool visit_check=0;		//to get the value 

	visited.Get(x,y,visit_check);
	
	if(visit_check==1) return true;
	return false;
}
//Navigate through the maze 
bool Grid::Navigate(point start,point goal)
{
	bool goalFound=false; //goalFound to locate the goal 
	bool action_check=false;	// action_check for actions like {Up,Down,Left,Right}
	bool Visit_check=false;		//To Check for Already visited point in Maze

	//Used to store the x and y coordinates of Current Point
	int x;
	int y;


	point CurrentPoint=start;	//Current point or  The point of the top of PointStack 
	point Updated_Point=start;	//Point corresponding to Current point (Either Up , down , left or Right)

	maze.Print(); //Origional maze 
	cout<<"Visited Paths"<<'\n';
	visited.Print(0);	//Visited_Path Maze

	pointStack.initialize();	//Initializing Point Stack
	pointStack.push(CurrentPoint);	//Pushing the Current Point on Stack

	while(!(pointStack.empty()) && goalFound==false)	//till pointStack is empty OR goal is found
	{

					pointStack.pop(CurrentPoint);	//Poping the Current point from stack
					Visit_Point(CurrentPoint);

					cout<<"Press any Key to Move Towards Destination ! "<<endl;
				cin.get();	//Pausing the Screen 

					visited.Print(0);

		if(CurrentPoint==goal) 
			goalFound=true;		//goal is Found
		else 
		{
			//Check for UP
					action_check=UP(CurrentPoint);	//Check for Corresponding Location
			if(action_check==true) 
			{
				x=CurrentPoint.getx() -1;
				Updated_Point=CurrentPoint;
				Updated_Point.setx(x);
				Visit_check=Already_Visited(Updated_Point);	//Check for Already Visited Location 

				if(Visit_check==false || Updated_Point==goal)
				{
					pointStack.push(Updated_Point);
				}
			}

			//Check for Down
					action_check=Down(CurrentPoint);
			if(action_check==true) 
			{
				
					x=CurrentPoint.getx() +1;
					Updated_Point=CurrentPoint;
					Updated_Point.setx(x);
					Visit_check=Already_Visited(Updated_Point);
				
				if(Visit_check==false || Updated_Point==goal)
				{
					pointStack.push(Updated_Point);
				}
			
			}

			//Check for Left 
					action_check=Left(CurrentPoint);
			if(action_check==true) 
			{
				y=CurrentPoint.gety() -1;
				Updated_Point=CurrentPoint;
				Updated_Point.sety(y);
				Visit_check=Already_Visited(Updated_Point);

				if(Visit_check==false || Updated_Point==goal)
				{
					pointStack.push(Updated_Point);
				}
			}

			//Check for Right 
					action_check=Right(CurrentPoint);
			if(action_check==true) 
			{
				y=CurrentPoint.gety() +1;
				Updated_Point=CurrentPoint;
				Updated_Point.sety(y);
				Visit_check=Already_Visited(Updated_Point);

				if(Visit_check==false || Updated_Point==goal)
				{
					pointStack.push(Updated_Point);
				}
			}

		
		}

	}

	if(goalFound==true) 
	{
		cout<<"Maze Has been Successfully Completed !"<<'\n';
		Maze_Complete=true;
	}
	else {
		cout<<"No Possible Paths found to the Destination ! "<<'\n';
	return false;
	Maze_Complete=false;
	}



//To Find Exact Path of the Maze 
	
//For This we need 3 Stacks , S1 (To Hold the Exact Path) , S2 (To hold the Junction points) , S3 (To Hold every point of each Junction point)

	stack<point,50> S1,S2,S3;
	S1.initialize();
	S2.initialize();
	S3.initialize();

//After this we need to copy the Visited_Maze_matrix to the Origional Maze_Matrix

	bool val=0;

	for(int i=0;i<maze.GetRows();i++)
		for(int j=0;j<maze.GetCols();j++)
		{
			visited.Get(i,j,val);
			if(val==1)
			{
				maze.Set(i,j,1);
			}
			else maze.Set(i,j,0);
		}

//Now Maze_Matrix contains only the points which we have already visited

		//First part of the process is to find the First Junction point (Containing more than one corresponding points) 
		//Till that just simply push every point in S1

		bool First_Junction=false;

		goalFound=false;  

		int count=0; //if count>1 then Junction Point Found, count represents # of corresponding valid points

		//Setting Current and Updated Point to Start 
		CurrentPoint=start; 
		Updated_Point=start;

		S1.push(CurrentPoint); //Pushing the Starting point in S1

		while((First_Junction!=true)&& goalFound==false)
		{

			if(CurrentPoint==goal) goalFound=true;
			else 
			{
				//Clearing the previous tracked path
				x=CurrentPoint.getx();
				y=CurrentPoint.gety();
				maze.Set(x,y,0);

				//Check for corresponding point in Upward location
				action_check=UP(CurrentPoint);
				if(action_check==true) 
			{
				
				x=CurrentPoint.getx() -1;
				y=CurrentPoint.gety();
				Updated_Point=CurrentPoint;
				Updated_Point.setx(x);
					count++;

					S2.push(Updated_Point);
			}

		//Check for corresponding point in Downward location
				action_check=Down(CurrentPoint);	
			if(action_check==true) 
			{
				
				x=CurrentPoint.getx() +1;
				y=CurrentPoint.gety();
				Updated_Point=CurrentPoint;
				Updated_Point.setx(x);
					count++;

					S2.push(Updated_Point);
			}

			//Check for corresponding point in Left direction
			action_check=Left(CurrentPoint);	
			if(action_check==true) 
			{
				
				x=CurrentPoint.getx();
				y=CurrentPoint.gety() -1;
				Updated_Point=CurrentPoint;
				Updated_Point.sety(y);
					count++;

					S2.push(Updated_Point);
			}

			//Check for corresponding point in Right Direction
				action_check=Right(CurrentPoint);	
			if(action_check==true) 
			{
				
				x=CurrentPoint.getx();
				y=CurrentPoint.gety() +1;
				Updated_Point=CurrentPoint;
				Updated_Point.sety(y);
					count++;
			
					S2.push(Updated_Point);
			}

			if(count==1)	//If only one corresponding point occurs relative to Current point
			{
				S2.pop(CurrentPoint);
				S1.push(CurrentPoint);
				count=0;
			}
			else 
			{
				First_Junction=true; //Junction Found

			}

			}

		}

		//If Goal is found prior to any Junction Point 
		if(goalFound==true){return true;}
		else 
		{
			//At this point S1 contains all the points prior to Junction Points , and S2 contains the Junction Points 

			//To store the initial Juction Points , there can be at max 3 such points (not 4 because we clear the already visited path)
			point First_Junction_Points[3];

			S2.pop(First_Junction_Points[0]);
			S2.pop(First_Junction_Points[1]);
			if(!S2.empty()) S2.pop(First_Junction_Points[2]);

			S2.push(First_Junction_Points[0]);
			S2.push(First_Junction_Points[1]);
			if(First_Junction_Points[2].getx() != -1 ) S2.push(First_Junction_Points[2]);

			//Now we have to test each of the Junction point till the Goal is found 
			count=1; //To calculate count of each point 
			
			int Count_Array[50]; //To store count of each point in S3
			for(int i=0;i<50;i++)
				Count_Array[i]=1;
			
			int Index_Count=0; //To Keep track of count_Array
			bool JunctionFound=false; //Junction_found
			bool Dead_end=false; //End of the path.

			stack <point,50>S4;
			S4.initialize();

			S2.pop(CurrentPoint);	//First Junction Point from S2 to S3
			S3.push(CurrentPoint);

			while(goalFound==false)
			{

				//From S2 to S3 each point one by one 
				if(JunctionFound==true || Dead_end==true){
				S2.pop(CurrentPoint);
				S3.push(CurrentPoint);
				JunctionFound=false;
				Dead_end=false;
				}
			//	Count_Array[Index_Count]=count; 

				//Clearing the previous tracked path
				x=CurrentPoint.getx();
				y=CurrentPoint.gety();
				maze.Set(x,y,0);

				//Check for corresponding point in Upward location
				action_check=UP(CurrentPoint);
				if(action_check==true) 
			{
				
				x=CurrentPoint.getx() -1;
				y=CurrentPoint.gety();
				Updated_Point=CurrentPoint;
				Updated_Point.setx(x);
					count++;

					S4.push(Updated_Point);
			}

		//Check for corresponding point in Downward location
				action_check=Down(CurrentPoint);	
			if(action_check==true) 
			{
				
				x=CurrentPoint.getx() +1;
				y=CurrentPoint.gety();
				Updated_Point=CurrentPoint;
				Updated_Point.setx(x);
					count++;

					S4.push(Updated_Point);
			}

			//Check for corresponding point in Left direction
			action_check=Left(CurrentPoint);	
			if(action_check==true) 
			{
				
				x=CurrentPoint.getx();
				y=CurrentPoint.gety() -1;
				Updated_Point=CurrentPoint;
				Updated_Point.sety(y);
					count++;

					S4.push(Updated_Point);
			}

			//Check for corresponding point in Right Direction
				action_check=Right(CurrentPoint);	
			if(action_check==true) 
			{
				
				x=CurrentPoint.getx();
				y=CurrentPoint.gety() +1;
				Updated_Point=CurrentPoint;
				Updated_Point.sety(y);
					count++;
			
					S4.push(Updated_Point);
			}


			if(count==2)
			{
				S4.pop(CurrentPoint);
				S3.push(CurrentPoint);
				
				if(CurrentPoint==goal) goalFound=true;

				Count_Array[Index_Count]=Count_Array[Index_Count]+(count-1); 
				count=1;
			}
			else if(count>2)	//Junction_Point Found
			{
				JunctionFound=true;

				while(!S4.empty())
				{
					S4.pop(CurrentPoint);

					if(CurrentPoint==goal)
					{
						S3.push(CurrentPoint);
						goalFound=true;
					}

						S2.push(CurrentPoint);
				}
						Index_Count++;
						count=1;
			}
			else if(count==1)	//Dead_End
			{
				bool Pop_Everything_From_S3 =false;
				Dead_end=true;
				count=0;

				//If S2 is not empty and it contains only the first junction points then pop everything from S3
				if(!S2.empty())
				{
					while(!S2.empty())
					{
						S2.pop(CurrentPoint);
						S4.push(CurrentPoint);

						count++;
					}
					if(count==1 || count==2)
					{
						S4.pop(CurrentPoint);
						S2.push(CurrentPoint);
						if(CurrentPoint==First_Junction_Points[0] || CurrentPoint==First_Junction_Points[1] || CurrentPoint==First_Junction_Points[2])
						{
							if(!S4.empty())
							{
								S4.pop(CurrentPoint);
								S2.push(CurrentPoint);
							if(CurrentPoint==First_Junction_Points[0] || CurrentPoint==First_Junction_Points[1] || CurrentPoint==First_Junction_Points[2])
							{
								Pop_Everything_From_S3 =true;
						
							}
							
							}// end of !S4.empty()
							else 
							{
								Pop_Everything_From_S3=true;
							}
						} 

					} //end of count==1 || count==2
					else 
					{

					while(!S4.empty())
						{
							S4.pop(CurrentPoint);
							S2.push(CurrentPoint);
						}
				
					}
					
				} //end of !S2.Empty()

				if(Pop_Everything_From_S3==true)
				{
					while(!S3.empty()) S3.pop();
					count=1;
					Index_Count=0;
				}
				else 
				{
					
					int i=Count_Array[Index_Count];
					while(i>=1)
					{
						S3.pop();
						i--;
					}

					Index_Count--;
					count=1;
				}

			}	//End of if (Count==1) //DeadEnd

		}	//end of While(goalFound==false)


		} //end of else, after if(goalFound==true)

		//Here S3 contains the portion of the exact path , so we will copy s3 to S1 then S1 will contain the exact full path. 

		while(!S3.empty())
		{
			S3.pop(CurrentPoint);
			S1.push(CurrentPoint);
		}

		//Now Initializing the Origional_maze with all the points in S1 stack
		//But first Initializing the maze with 0 
		for(int i=0;i<maze.GetRows();i++)
			for(int j=0;j<maze.GetCols();j++)
				maze.Set(i,j,0);

		while(!S1.empty())
		{
			S1.pop(CurrentPoint);
			x=CurrentPoint.getx();
			y=CurrentPoint.gety();
			maze.Set(x,y,1);
		}

		cout<<endl<<"Exact Full Path of Maze"<<endl; 
		maze.Print(0);
		

	return true; 

} //end of Navigate Function