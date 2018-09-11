#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <list>
 
struct Player
{
	int id, points;
	std::string name;
 
	Player(int playerId, std::string playerName) :
			id(playerId), name(playerName)
	{
		points = 0;
	}
	void addPoints(int p)
	{
		points += p;
	}
};
 
int main()
{
	std::list<Player> listofPlayers =
	{ Player(22, "Sid"), Player(3, "Laura"), Player(43, "Riti"), Player(30,
			"Angel"), Player(2, "Laura") };
 
	std::cout << "*******Iterate std::list using Iterators*******" << std::endl;
 
//Create an iterator of std::list
	std::list<Player>::iterator it;
 
// Make iterate point to begining and incerement it one by one till it reaches the end of list.
	for (it = listofPlayers.begin(); it != listofPlayers.end(); it++)
	{
		// Access the object through iterator
		int id = it->id;
		std::string name = it->name;
		it->addPoints(2);
 
		//Print the contents
		std::cout << id << " :: " << name << std::endl;
 
	}
 
	std::cout
			<< "*******Iterate std::list using for_each and c++11's Lambda function *********"
			<< std::endl;
 
	std::for_each(listofPlayers.begin(), listofPlayers.end(),
			[](Player & player)
			{
				//Print the contents
				std::cout<<player.id<< " :: "<<player.name<<std::endl;
				player.addPoints(5);
			});
 
	std::cout
			<< "*******Iterate std::list using c++11 Range Based For Loop *********"
			<< std::endl;
 
	for (Player & player : listofPlayers)
	{
		std::cout << player.id << " :: " << player.name << std::endl;
		player.addPoints(3);
	}
 
	std::cout
			<< "*******Iterate std::list in backwords using Iterators *********"
			<< std::endl;
 
	//Create a reverse iterator of std::list
	std::list<Player>::reverse_iterator revIt;
 
	// Make iterate point to begining and incerement it one by one till it reaches the end of list.
	for (revIt = listofPlayers.rbegin(); revIt != listofPlayers.rend(); revIt++)
	{
		// Access the object through iterator
		int id = revIt->id;
		std::string name = revIt->name;
		rivIt->addPoints(9);
 
		//Print the contents
		std::cout << id << " :: " << name << std::endl;
 
	}
 
	return 0;
 
}
