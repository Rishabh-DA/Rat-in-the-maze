#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include <stack>
using namespace std;

void changeColor(int desiredColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),desiredColor);
}

class maze
{
    int rows,cols;
    int **arr;
    struct position{
    int row;
    int col;
    };
    stack<position> path_r;
    stack<position> change;
    stack<position>path_d;
    stack<position>file;
     int countd,countr;
   struct position offset[4];

public:
    maze()
    {
        rows=10;cols=10;
        arr=new int*[rows];
        for(int i=0;i<rows;i++)
            arr[i]=new int[cols];

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
                arr[i][j]=0;
        }

    offset[0].row=0;offset[0].col=1; //right
    offset[1].row=1;offset[1].col=0; //down
    offset[2].row=-1;offset[2].col=0; //up
    offset[3].row=0;offset[3].col=-1; //left

    countd=0;countr=0;
    }
    void get_dimensions();
    void display_maze();
    void maze_coord_file();
    void maze_file();
    bool update_maze_single(int x,int y);
    bool update_maze_horizontal(int a,int b,int y);
    bool update_maze_vertical(int a,int b,int x);
    bool update_maze_diagonal(int a,int b,int x,int y);
    bool find_path_r(int x,int y);
    bool find_path_d(int x,int y);
    bool output_path();
};

void maze::get_dimensions()
{
    cout<<"enter the dimensions of the maze:\n";
    cout<<"no. of rows: ";
    cin>>rows;
    cout<<"no. of columns: ";
    cin>>cols;
    rows=rows+2;
    cols=cols+2;
    arr=new int*[rows];
    for(int i=0;i<rows;i++)
        arr[i]=new int[cols];

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
                arr[i][j]=0;
        }
        //TOP TO BOTTOM
        for(int k=0;k<rows;k++)
        {
            arr[k][0]=1;
            arr[k][cols-1]=1;
        }
        //LEFT TO RIGHT
        for(int i=0;i<cols;i++)
        {
            arr[0][i]=1;
            arr[rows-1][i]=1;
        }
}

void maze:: display_maze()
{
    int x=30,y=5;
    int x1=26,y1=6;
    changeColor(13);//DARK PINK
    //FROM TOP TO BOTTOM
    for(int i=0;i<rows-2;i++)
    {
            gotoxy(x1,y1+i);
            cout<<i+1;
            y1++;
    }
    x1=31;y1=3;
    //FROM LEFT TO RIGHT
    for(int j=0;j<cols-2;j++)
    {
        gotoxy(x1+j,y1);
        cout<<j+1;
        x1++;
    }

    for(int i=1;i<rows-1;i++)
    {
        x=30;
        for(int j=1;j<cols-1;j++)
            {
                gotoxy(x+j,y+i);
                if(arr[i][j]==0)
                {
                changeColor(14);//LIGHT YELLOW
                cout<<arr[i][j];
                }else if(arr[i][j]==1){
                changeColor(12);//RED
                cout<<arr[i][j];
                }
                else{
                    changeColor(2);//GREEN
                    cout<<arr[i][j];
                }
                x++;
            }
            y++;
    }

    changeColor(7);
    cout<<endl<<endl<<endl;
}

bool maze::update_maze_single(int x,int y)
{
    try{
    if(x>rows-2 || y>cols-2)
    {
        throw 1;
    }
        arr[x][y]=1;
        return true;
    }
    catch(int i)
    {
        cout<<"\n invalid position\n\n";
        return false;
    }
}

bool maze::update_maze_horizontal(int a,int b,int y)
{
    try{
    if(a>rows-2 || b>cols-2  || y>cols-2)
        throw 1;

        for(int i=b;i<=y;i++)
            arr[a][i]=1;
        return true;
    }
    catch(int i)
    {
        cout<<"\ninvalid input\n\n";
        return false;
    }
}

bool maze::update_maze_vertical(int a,int b,int x)
{
    try{
    if(a>rows-2 || b>cols-2  || x>rows-2)
        throw 1;
        for(int i=a;i<=x;i++)
            arr[i][b]=1;
            return true;
    }
    catch(int i){
        cout<<"\ninvalid input\n\n";
        return false;
    }
}

bool maze:: update_maze_diagonal(int a,int b,int x,int y)
{
    int i,j;
    try{
    if(a>rows-2 || b>cols-2 || x>rows-2 || y>cols-2 ||(x-a!=y-b))
        throw 1;
            for(i=a,j=b;j<=y;i++,j++)
            {
                arr[i][j]=1;
            }
            return true;
        }
        catch(int k){
            cout<<"\ninvalid input\n\n";
            return false;
        }
}

bool maze::find_path_r(int x,int y)
{
    struct position here;
    here.row=x;here.col=y;

    if(x==rows-2 && y==cols-2)
    {
        path_r.push(here);
        return true;
    }

    arr[x][y]=1;
    change.push(here);
    int option = 0;
    int lastOption = 3;

    //offset[0].row=0;offset[0].col=1; //right
    //offset[1].row=1;offset[1].col=0; //down
    //offset[2].row=-1;offset[2].col=0; //up
    //offset[3].row=0;offset[3].col=-1; //left

    while(option<=lastOption)
    {
        if(arr[here.row+offset[option].row][here.col+offset[option].col]==0)
        {
            path_r.push(here);
            countr++;
            if(!(find_path_r(here.row+offset[option].row,here.col+offset[option].col)))
            {
                path_r.pop();
                countr--;
                option++;
            }
            else{break;}
        }
        else
            option++;
    }
    if(option>lastOption)
        return false;
    return true;
}

bool maze::find_path_d(int x,int y)
{
    struct position here;
    here.row=x;here.col=y;

    if(x==rows-2 && y==cols-2)
    {
        path_d.push(here);
        return true;
    }

    arr[x][y]=1;
    change.push(here);
    int option[4]={1,0,2,3};
    int index = 0;
    int lastOption = 3;

    /*offset[0].row=0;offset[0].col=1; //right
    offset[1].row=1;offset[1].col=0; //down
    offset[2].row=-1;offset[2].col=0; //up
    offset[3].row=0;offset[3].col=-1; //left*/

    while(index<=lastOption)
    {
        if(arr[here.row+offset[option[index]].row][here.col+offset[option[index]].col]==0)
        {
            path_d.push(here);
            countd++;
            if(!(find_path_d(here.row+offset[option[index]].row,here.col+offset[option[index]].col)))
            {
                path_d.pop();
                countd--;
                index++;
            }
            else{break;}
        }
        else
            index++;
    }
    if(index>lastOption)
        return false;
    return true;
}


bool maze::output_path()
{
    find_path_r(1,1);
    //CHANGE ALL THE CO ORDINATES WE HAVE CHANGED BACK TO 0
    while(!change.empty())
    {
        arr[change.top().row][change.top().col]=0;
        change.pop();
    }
    find_path_d(1,1);

    while(!change.empty())
    {
        arr[change.top().row][change.top().col]=0;
        change.pop();
    }

    if(countd==0 && countr==0)
    {
        return false;
    }
    else if(countr<=countd)
    {
        while(!path_r.empty())
    {
        arr[path_r.top().row][path_r.top().col]=5;
        file.push(path_r.top());
        path_r.pop();
    }
    return true;
    }
     else
    {
        while(!path_d.empty())
    {
        arr[path_d.top().row][path_d.top().col]=5;
        file.push(path_d.top());
        path_d.pop();
    }
    return true;
    }
}

void maze::maze_coord_file()
{
    ofstream fout;
    fout.open("coord.txt");
    while(!file.empty())
    {
        fout<<"["<<file.top().row<<","<<file.top().col<<"]\n";
        file.pop();
    }
}

void maze::maze_file()
{
    ofstream out;
    out.open("maze.txt");
    for(int i=1;i<rows-1;i++)
    {
        for(int j=1;j<cols-1;j++)
        {
            out<<arr[i][j]<<" ";
        }
        out<<"\n";
    }
}

void path_finding()
{
    maze m;
    m.get_dimensions();
    system("cls");
    m.display_maze();
    int flag=1,k,x1,y1,x2,y2;
    while(flag==1)
    {
        changeColor(3);//BLUE
        cout<<"1)enter only a single obstacle\n2)enter obstacles horizontally\n3)enter obstacles vertically\n4)enter obstacles diagonally\n5)finished setting up obstacles\n";
        cin>>k;
        switch(k)
        {
            case 1:cout<<"\nenter the coordinates where you want to insert the obstacle:\n";
            cout<<"row: ";
            cin>>x1;
            cout<<"column: ";
            cin>>y1;
            if(m.update_maze_single(x1,y1))
            {
                system("cls");
                m.display_maze();
            }
            break;

            case 2:cout<<"\nenter the staring coordinates from where you want to insert the obstacle:\n";
            cout<<"starting row: ";
            cin>>x1;
            cout<<"starting column: ";
            cin>>y1;
            cout<<"enter ending column till where you want to insert the obstacle: ";
            cin>>y2;
            if(m.update_maze_horizontal(x1,y1,y2))
            {
                system("cls");
                m.display_maze();
            }
            break;

            case 3:cout<<"\nenter the staring coordinates from where you want to insert the obstacle:\n";
            cout<<"starting row: ";
            cin>>x1;
            cout<<"starting column: ";
            cin>>y1;
            cout<<"enter ending row till where you want to insert the obstacle: ";
            cin>>x2;
            if(m.update_maze_vertical(x1,y1,x2))
            {
                system("cls");
                m.display_maze();
            }
            break;

            case 4:cout<<"\nenter the staring coordinates from where you want to insert the obstacle:\n";
            cout<<"starting row: ";
            cin>>x1;
            cout<<"starting column: ";
            cin>>y1;
            cout<<"enter the staring coordinates from where you want to insert the obstacle:\n";
            cout<<"ending row: ";
            cin>>x2;
            cout<<"ending column: ";
            cin>>y2;
            if(m.update_maze_diagonal(x1,y1,x2,y2))
            {
                system("cls");
                m.display_maze();
            }
            break;

            case 5:flag=0;
                    system("cls");
                    break;
            default:cout<<"\ninvalid input";
        }
    }

    if(m.output_path())
    {
    m.display_maze();
    m.maze_coord_file();
    m.maze_file();
    }
    else{
        cout<<"no path found";
    }
}
