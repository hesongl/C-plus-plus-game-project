#include "player.h"

Player::Player(int px, int py, int num, int vel)
{
    x = px;
    y = py;
	tool["life"]       = 0;
	tool["num_bubble"] = 0;
	tool["accelerate"] = 0;
	tool["range"]      = 0;
	fund_v = vel;
    v = fund_v + 10*tool["accelarate"];
	fund_BubbleNum = num;
	BubbleNum = fund_BubbleNum + tool["num_bubble"];    
	isInBubble = false;
	fund_life = 1;
	life = fund_life + tool["life"];
	//std::unordered_map<std::string,int> temp({"life",0},{"num_bubble",0},{"speed",0},{"range",0});
	//tool.at("life") = 0;
	//tool.at("num_bubble") - 0;
	//tool.at("speed") = 0;
	//tool.at("range") = 0;
	state = 0;
	OnceInBubble = 0;
	MyPng = NULL;
	MyPng = new YsRawPngDecoder[3];
	if (YSOK == MyPng[0].Decode("p1.png"))
	{
		printf("Read p1 Width=%d Height=%d\n", MyPng[0].wid, MyPng[0].hei);
		MyPng[0].Flip();
	}
	else printf("Read p1 Error!\n");
	if (YSOK == MyPng[1].Decode("p2.png"))
	{
		printf("Read p2 Width=%d Height=%d\n", MyPng[1].wid, MyPng[1].hei);
		MyPng[1].Flip();
	}
	else printf("Read p2 Error!\n");
	if (YSOK == MyPng[2].Decode("around.png"))
	{
		printf("Read around Width=%d Height=%d\n", MyPng[2].wid, MyPng[2].hei);
		MyPng[2].Flip();
	}
	else printf("Read around Error!\n");
}
Player::~Player()
{
	if (NULL != MyPng)
	{
		delete[] MyPng;
		MyPng = NULL;
	}
}

void Player::addTool(int toolType)
{
	switch (toolType)
	{
	case 1:
		tool["life"]++;
		break;
	case 2:
		tool["num_bubble"]++;
		break;
	case 3:
		tool["accelerate"] += 2;
		break;
	case 4:
		tool["range"]++;
		break;
	}
}

bool Player::getTool(Map &map)
{
	int bitx = this->getX() / 50;
	int bity = this->getY() / 50;
	if (map.getToolMapState(bity, bitx) != 0)
	{ 
		int state = map.getToolMapState(bitx, bity);
 		addTool(state);
		update();
		map.setToolState(bity, bitx, 0);
		if(state == 4)
		{
			return true;
		}
	}
	return false;
}

void Player::update()
{
	this->life = fund_life + tool["life"];
	this->v    = fund_v    + tool["accelerate"];
	this->BubbleNum = fund_BubbleNum + tool["num_bubble"];
}

void Player::incVelocity()
{
	v += 5;
}

void Player::decVelocity()
{
	v -= 5;
}

void Player::incBubbleNum()
{
	BubbleNum++;
}

int Player::getBubbleNum() const
{
	return BubbleNum;
}

void Player::layBubble(Map &map, int range)
{
	if(BubbleNum > 0)
	{
		map.setMapState(this->getY()/50,this->getX()/50, 4);
		map.setBubbleMapRange(this->getY()/50,this->getX()/50,range);
		BubbleNum--;
		printf("%d	%d\n",this->getY(),this->getX());
	}
}

void Player::plusNum(int num)
{
	this->BubbleNum += num;
	//printf("life: %d	\n", life);
}

int Player::getX() const
{
//	printf("x: %d\n",x);
	return x;
}

int Player::getY() const
{
//	printf("y: %d\n", y);
	return y;
}

void Player::setState(int state)
{
	this->state = state;
}

void Player::Draw(int playernum)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRasterPos2d(x - 25, y);
	switch (playernum)
	{
	case 1:
		glDrawPixels(MyPng[0].wid, MyPng[0].hei, GL_RGBA, GL_UNSIGNED_BYTE, MyPng[0].rgba);
		break;
	case 2:
		glDrawPixels(MyPng[1].wid, MyPng[1].hei, GL_RGBA, GL_UNSIGNED_BYTE, MyPng[1].rgba);
		break;
	}
	if (state == 1) 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2d(x - 25, y);
		glDrawPixels(MyPng[2].wid, MyPng[2].hei, GL_RGBA, GL_UNSIGNED_BYTE, MyPng[2].rgba);
	}
	/*
	const double pi = 3.14159265359;
	const double r = 15.;
	const double r2 = 18.;
	double dx = 0, dy = 0;
	double cx = x;
	double cy = y - 50;

	glBegin(GL_TRIANGLES);
	glColor3ub(0, 0, 0);
	glVertex2d(x		, y);
	glVertex2d(x + 25	, y - 40);
	glVertex2d(x - 25	, y - 40);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex2d(x	, y - 40);
	glVertex2d(x + 5, y - 20);
	glVertex2d(x	, y - 15);
	glVertex2d(x - 5, y - 20);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 0);
	for (int i = 0; i < 33; ++i)
	{
		dx = r*cos((double)i*pi / 32.);
		dy = r*sin((double)i*pi / 32.);
		glVertex2d(cx + dx, cy + dy);
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(0, 255, 0);
	for (int i = 32; i < 65; ++i)
	{
		dx = r2*cos((double)i*pi / 32.);
		dy = r2*sin((double)i*pi / 32.);
		glVertex2d(cx + dx, cy + dy);
	}
	glEnd();
	*/
	//printf("%d	%d\n",x,y);

}

int Player::getState() const
{
	return this->state;
}

int Player::Hit(Map bitMap)
{
	double x1 = x - 15;
	double y1 = y - 30;
	double x2 = x + 15;
	double y2 = y - 30;
	double x3 = x + 15;
	double y3 = y;
	double x4 = x - 15;
	double y4 = y;
	return 0;
//	if (bitMap.getPixel((int)(x1 - 1) / 50, (int)(y1 - 1) / 50))
//	{

//	}
}

void Player::move(int direction, const Map &bitMap)
{
	int bitX, bitY;
	bitX = (int)x / 50;
	bitY = (int)y / 50;

	double x1 = x - 15;
	double y1 = y - 30;
	double x2 = x + 15;
	double y2 = y - 30;
	double x3 = x + 15;
	double y3 = y;
	double x4 = x - 15;
	double y4 = y;

	if (1 == OnceInBubble)
	{
		if (direction == 1 && (0 == bitMap.getPixel((int)(y1 - v) / 50, (int)x1 / 50) || 4 == bitMap.getPixel((int)(y1 - v) / 50, (int)x1 / 50)) &&
			(0 == bitMap.getPixel((int)(y2 - v) / 50, (int)x2 / 50) || 4 == bitMap.getPixel((int)(y2 - v) / 50, (int)x2 / 50)))
		{
			if ((y - v) < 15) {} // 11/30 Chen Hu: avoid step outside map
			else y -= v;
		}
		if (direction == 2 && (0 == bitMap.getPixel((int)y1 / 50, (int)(x1 - v) / 50) || 4 == bitMap.getPixel((int)y1 / 50, (int)(x1 - v) / 50)) &&
			(0 == bitMap.getPixel((int)y4 / 50, (int)(x4 - v) / 50) || 4 == bitMap.getPixel((int)y4 / 50, (int)(x4 - v) / 50)))
		{
			if ((x - 30) < 0) {}
			else x -= v;
		}
		if (direction == 3 && (0 == bitMap.getPixel((int)(y3 + v) / 50, (int)x3 / 50) || 4 == bitMap.getPixel((int)(y3 + v) / 50, (int)x3 / 50)) &&
			(0 == bitMap.getPixel((int)(y4 + v) / 50, (int)x4 / 50) || 4 == bitMap.getPixel((int)(y4 + v) / 50, (int)x4 / 50)))
		{
			if ((y + v) > 735) {}
			else y += v;
		}
		if (direction == 4 && (0 == bitMap.getPixel((int)y2 / 50, (int)(x2 + v) / 50) || 4 == bitMap.getPixel((int)y2 / 50, (int)(x2 + v) / 50)) &&
			(0 == bitMap.getPixel((int)y3 / 50, (int)(x3 + v) / 50) || 4 == bitMap.getPixel((int)y3 / 50, (int)(x3 + v) / 50)))
		{
			if ((x + v) > 735) {}
			else x += v;
		}
	}
	else
	{
		if (direction == 1 && 0 == bitMap.getPixel((int)(y1 - v) / 50, (int)x1 / 50) && 0 == bitMap.getPixel((int)(y2 - v) / 50, (int)x2 / 50))
		{
			if ((y - v) < 15) {}
			else y -= v;
		}
		if (direction == 2 && 0 == bitMap.getPixel((int)y1 / 50, (int)(x1 - v) / 50) && 0 == bitMap.getPixel((int)y4 / 50, (int)(x4 - v) / 50))
		{
			if ((x - 30) < 0) {}
			else x -= v;
		}
		if (direction == 3 && 0 == bitMap.getPixel((int)(y3 + v) / 50, (int)x3 / 50) && 0 == bitMap.getPixel((int)(y4 + v) / 50, (int)x4 / 50))
		{
			if ((y + v) > 735) {}
			else y += v;
		}
		if (direction == 4 && 0 == bitMap.getPixel((int)y2 / 50, (int)(x2 + v) / 50) && 0 == bitMap.getPixel((int)y3 / 50, (int)(x3 + v) / 50))
		{
			if ((x + v) > 735) {}
			else x += v;
		}
	}
//	printf("%d	%d",x,y);
}

void Player::CheckInBubble(const Map &bitMap)
{
	if (4 == bitMap.getPixel((int)y / 50, (int)x / 50))
	{
		OnceInBubble = 1;
	}
	else
	{
		OnceInBubble = 0;
	}
}

int Player::CheckInZone(const Map &map)
{
	int bitX = (int)(x / 50);
	int bitY = (int)(y / 50);
	if (3 == map.getMapState(bitX, bitY) && 0 == state)
	{
		//the player should be trapped
		tool["life"]--;
		printf("life: %d	\n", life);
		if (life==0)	state = 1;
		return 1;
	}
	else
	{
		return 0;
	}
}