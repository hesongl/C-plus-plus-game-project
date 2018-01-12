#include <vector>
class Map
{
protected:
	enum map_state {floor = 0, box = 1, obstacle = 2, isWithinExposedZone=3, hasBubble=4, player = 5};
	Bubble bubbleMap[15][15];
	map_state map[15][15];
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
};

class Player
{
protected:
	int BubbleNum;
	//std::vector<Bubble> bubbles;
	Bubble myBubble;
	std::vector<Tool> tools;
	int trapTime;
	int state; //0：healthy, 1:trapped 2:dead
	int x,y;
	int v;
	// int id;
public:
	Player(int px, int py, int num, int vel )
	void incVelocity();
	void decVelocity();
	void incBubbleNum();
	void layBubble();
	int getX() const;
	int getY() const;
	int setState();
	void countTrapTime();
	//judge which zone is the person 


};
//检查爆炸的顺序： 对每一个player，检查它的每一个bomb，到时间了或者在爆炸范围内就引爆，同时调用map.setMapState()更新爆炸区，检查完然后再更新爆炸区域内的
//人，道具，并且画
//最后不要忘了每个loop末尾更新mapstate，去掉所有的exposed
class Bubble
{
protected:
	int playId;
	int range;
	int bitx, bity;
	const int blowTime;
	int layTime;
	int state; //0: inactive, 1 avtive
public:
	Bubble(int state, int pId, int xzone, int yzone, int lTime);
	Bubble(const Bubble& other)
	{
		state = other.state;
		playId = pId;
		bitx = xzone;
		bity = yzone;
		layTime = lTime;
	}
	void expose();
	void checkTime();
	void setBitX(int x);
	void setBitY(int y);
	void increaseRange();
	int getRange();
	int getSate();
	Bubble ~(){};
	const Bubble& operator=(const Bubble& other)
	{
		state = other.state;
		playId = pId;
		bitx = xzone;
		bity = yzone;
		layTime = lTime;
		return *this;
	}
};

class Tool
{
	
};

class Menu
{

};

int main()
{
	Map map;
}
