#include <vector>
class Map
{
protected:
	enum map_state {floor = 0, box = 1, obstacle = 2, isWithinExposedZone=3, hasBubble=4, player = 5};
	Bubble bubbleMap[15][15];
	map_state map[15][15];
    //to be implemented...
public:
	Map(string fileName)
	{
		//...load file, remaining to be completed
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				bubbleMap[i][j] = new Bubble(0,0,i,j,0); // just set state
			}
		}
	}
	void setPixel();
	int  getPixel();
	void Draw();
	//check whether the current bit map zone is exposed or not
	void setMapState();
	void checkExposeTime(); // traverse row and col
	void adjacentExplode(int x, int y, int range) //recursion
	{
		//base case:
			if (x <= 0 || x >= 14 || y <= 0 || y >= 14
			|| checkPos(x, y)) 
			{
				return;
			}
			int count = 1;
			while(count <= range && (x+count)<=14)
			{
				if(bubbleMap[x+count][y].getSate() == 1)   //向右侧查找
			    {
				    adjacentExplode(x+count,y,bubbleMap[x+count][y].getRange());
				    map[x+count][y] = 3;
				    break;
			    }
			    if(map[x+count][y] == box || map[x+count][y] == obstacle || map[x+count][y] == player)
			    {
			    	map[x+count][y] = 3;
			    	break;
			    }
			    map[x+count][y] = 3;
				count++;
			}
			int count = 1;
			while(count <= range && (x - count) >= 0)
			{
				if(bubbleMap[x-count][y].getSate() == 1)   //向右侧查找
			    {
				    adjacentExplode(x-count,y,bubbleMap[x-count][y].getRange());
				    map[x-count][y] = 3;
				    break;
			    }
			    if(map[x-count][y] == box || map[x-count][y] == obstacle || map[x-count][y] == player)
			    {
			    	map[x-count][y] = 3;
			    	break;
			    }
			    map[x-count][y] = 3;
				count++;
			}
			int count = 1;
			while(count <= range && (y + count) <= 14)
			{
				if(bubbleMap[x][y+count].getSate() == 1)   //向xia侧查找
			    {
				    adjacentExplode(x,y+count,bubbleMap[x][y+count].getRange());
				    map[x][y+count] = 3;
				    break;
			    }
			    if(map[x][y+count] == box || map[x][y+count] == obstacle || map[x][y+count] == player)
			    {
			    	map[x][y+count] = 3;
			    	break;
			    }
			    map[x][y+count] = 3;
				count++;
			}
			int count = 1;
			while(count <= range && (y - count) >= 0)
			{
				if(bubbleMap[x][y-count].getSate() == 1)   //向up侧查找
			    {
				    adjacentExplode(x,y-count,bubbleMap[x][y-count].getRange());
				    map[x][y-count] = 3;
				    break;
			    }
			    if(map[x][y-count] == box || map[x][y-count] == obstacle || map[x][y-count] == player)
			    {
			    	map[x][y-count] = 3;
			    	break;
			    }
			    map[x][y-count] = 3;
				count++;
			}
	}	
    int getMapState() const;
};