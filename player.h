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
