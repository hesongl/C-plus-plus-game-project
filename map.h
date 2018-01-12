#include <vector>
#include <string>
#include "fssimplewindow.h"
// added 11/23 Chen Hu
#include "yspng.h"

#ifndef is_included_bubble
#include "bubble.h"
#endif

#define isFloor 0;
#define isBox 1;
#define isObstacle 2;
#define inExplosion 3;
#define isBubble 4;
#define isPlayer 5;


#ifndef MAP_IS_INCLUDED
#define MAP_IS_INCLUDED
class Map
{
protected:
	//enum map_state {floor = 0, box = 1, obstacle = 2, isWithinExposedZone=3, hasBubble=4, player = 5};
	Bubble bubbleMap[15][15];
	//map_state map[15][15];
	int map[15][15];
    //to be implemented...



	int toolmap[15][15];
	//added 11/23 Chen Hu Background pics
	//MyPng[0]: ground; MyPng[1]: box; MyPng[2]: obstacle; MyPng[3]: bubble around player(no use); MyPng[4]: bubble
	//[5]: Add life; [6]: add bubble; [7]: add speed; [8]: add range 
	YsRawPngDecoder *MyPng;


public:
	Map();
	//added 11/23 Chen Hu, destructor
	~Map();
	//11/19 hesongl setToolState
	void setToolState(int x, int y, int state);

	/*Map(std::string fileName)
	{
		//...load file, remaining to be completed
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				bubbleMap[i][j] = new Bubble(0,0,i,j,0); // just set state
			}
		}
	}*/
	void setPixel();
	void setBubbleMap(int x, int y, int state, int range, int layTime, int playerID);
	//void setBubbleRange(const int x, const int y, const int range);
	int  getPixel(int bitX, int bitY) const;
	int getID(int x, int y);
	void Draw();
	//check whether the current bit map zone is exposed or not
	void setMapState(int x, int y, int state);
	void setBubbleMapRange(int x, int y, int range);
	void checkExposeTime(); // traverse row and col
	void adjacentExplode(int x, int y, int range, int left, int right, int up, int down, int& num1, int& num2);//recursion
    int getMapState(int i, int j) const;
	int getBubbleMapState(int i, int j) const;
	int checkBubbleTime(int x, int y) const;
	int getRange(int x, int y) const;
	void setBlowTime(int x, int y);



	int getToolMapState(int bitx, int bity);
	void drawTool(int x, int y);
};
#endif