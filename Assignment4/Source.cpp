﻿#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <numeric>


using namespace std;
const wstring CARD_NUM[] = { L"emp",L"A",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"10",L"J",L"Q",L"K" };

class Card {

public:
	Card() {
		this->cardNum = CARD_NUM[0];
		suit = emp;
		this->cardValue = 0;

	}
	int  getCardIndexValue() {
		return this->cardIndexValue;
	}
	void display() {
		wcout << cardNum;

		if (suit == club) {
			wcout << L"♣";
		}
		else if (suit == diamond) {
			wcout << L"♦";

		}
		else if (suit == heart) {
			wcout << L"♥";

		}
		else if (suit == spade) {
			wcout << L"♠";
		}
		else
		{
			wcout << L"";
		}
		//wcout << L"(" << cardValue << L")";
	}
	void setCard(int suiteIndex, int cardNum) {

		if (suiteIndex == 1)
		{
			suit = club;
		}
		else if (suiteIndex == 2)
		{
			suit = diamond;
		}
		else if (suiteIndex == 3)
		{
			suit = heart;
		}
		else if (suiteIndex == 4)
		{
			suit = spade;
		}
		else if (suiteIndex == 0)
		{
			suit = emp;
		}
		this->cardNum = CARD_NUM[cardNum];
		cardIndexValue = cardNum;
		this->cardValue = cardNum > 10 ? 10 : cardNum;
	}
	wstring getCardNum() {
		return this->cardNum;
	}
	int getCardValue() {
		return this->cardValue;
	}
	~Card() {};
private:
	enum SUITE
	{
		emp, club, diamond, heart, spade
	};
	wstring cardNum;
	SUITE suit;
	int cardValue;
	int cardIndexValue;
};

class Player {
public:
	Player() {}
	Player(wstring playerName) {
		statusGo = false;
		this->platerName = playerName;
		score = 0;
	}
	void setGoStatus() {
		this->statusGo = true;
	}
	bool getGoStatus() {
		return statusGo;
	}
	vector<Card> getHand() {
		return this->hand;
	}
	void emptyHandByIndex(int i) {
		this->hand[i].setCard(0, 0);
	}
	void removeFromHand(int i) {
		this->hand.erase(hand.begin() + i);
	}
	void setHand(vector<Card> hand) {
		this->hand = hand;
	}
	wstring getPlayerName() {
		return this->platerName;
	}
	int getScore() {
		return this->score;
	}
	void setCut(Card c) {
		cut = c;
	}
	Card getCut() {
		return cut;
	}
	void draw() {

	}
	void printHand() {
		for (int i = 0; i < hand.size(); i++)
		{
			hand[i].display();
			if ((i + 1) != hand.size())
			{
				wcout << ",";
			}
		}
	}
	;
private:
	wstring platerName;
	bool statusGo;
	vector<Card> hand;
	int score;
	Card cut;
	;

};


class Board {
public:
	Board(vector<Player> players, vector<Card> deck) {
		this->deck = deck;
		this->players = players;
		roundScore = 0;
	}
	void printScore() {
		for (int i = 0; i < this->players.size(); i++)
			wcout << this->players[i].getPlayerName() << " :                 " << this->players[i].getScore() << endl;
	}
	void setFirstHand(vector<vector<Card>> fh) {
		this->playerHands = fh;
	}
	vector<Card> getCrib() {
		return this->crib;
	}
	void pushToCrib(Card c) {
		this->crib.push_back(c);
	}
	void pushToRoundPlay(Card c) {
		this->roundPlay.push_back(c);
	}
	Card getCut() {
		return this->cut;
	}
	void setCut(Card c) {
		this->cut = c;
	}
	vector<Card> getDeck() {
		return this->deck;
	}

	vector<Card> getRoundPlay() {
		return this->roundPlay;
	}
	void clearRoundPlay() {
		this->roundPlay.clear();
	}
	vector<Player> getPlayers() {
		return this->players;
	}
	void addToPlayers(Player p) {
		this->players.push_back(p);
	}

	int getRoundScore() {
		return roundScore;
	}

	void setRoundScore(int i) {
		this->roundScore = i;
	}
	bool setRoundScore(Card c) {

		if (c.getCardValue() + getRoundScore() > 31) {
			wcout << endl << c.getCardValue() << " + " << getRoundScore() << " >31, Please choose another card.\n";
			return false;
		}
		else
		{
			this->roundScore += c.getCardValue();
			return true;
		}
	}

	void setDealer(Player dealer) {
		this->dealer = dealer;
	}
	wstring getDealerName() {
		return this->dealer.getPlayerName();
	}
	Player getDealer() {
		return this->dealer;
	}
	bool isDealer(Player p) {
		return p.getPlayerName() == dealer.getPlayerName();
	}
	;
private:
	vector<Card> deck;
	Card cut;
	vector<Card> roundPlay;
	vector<Card> crib;
	vector<vector<Card>> playerHands; //store original hands
	vector<Player> players;
	Player dealer;
	int roundScore;
};




int getRand(int randMax) {
	int random_integer = rand() % randMax + 1;
	return random_integer;
}

Card drawCard(vector<Card>&deck) {
	int rand = getRand(52);
	Card tempCard = deck[rand - 1];
	int num = 0;
	while (tempCard.getCardNum() == L"emp"&&num<52) {
		rand = getRand(52);
		tempCard = deck[rand - 1];
		num++;
	}
	if (num>52)
	{
		wcout << "Deck is empty";
	}
	else {
		deck[rand - 1].setCard(0, 0);
	}
	return tempCard;
}
Card cutDeck(vector<Card>&deck) {
	int rand = getRand(52);
	Card tempCard = deck[rand - 1];
	int num = 0;
	while (tempCard.getCardNum() == L"emp"&&num<52) {
		rand = getRand(52);
		tempCard = deck[rand - 1];
		num++;
	}
	if (num>52)
	{
		wcout << "Deck is empty";
	}
	return tempCard;
}

void shuflleDeck(vector<Card>&deck) {

	int rand1, rand2;
	for (int i = 0; i < 52; i++)
	{
		rand1 = getRand(52);
		rand2 = getRand(52);
		do {
			rand2 = getRand(52);
		} while (rand1 == rand2);
		Card tempCard = deck[rand1 - 1];
		deck[rand1 - 1] = deck[rand2 - 1];
		deck[rand2 - 1] = tempCard;
	}

}
void displayDeck(vector<Card>deck) {

	for (int k = 0; k < 52; k++)
	{
		if (k % 13 == 0 && k != 0)
		{
			wcout << endl;
		}
		wcout << " ";
		deck[k].display();
	}
	wcout << endl;
}

vector<Card> createDeck() {
	vector<Card> deck;
	for (int i = 1; i <= 4; i++)
	{
		for (int k = 1; k <= 13; k++)
		{
			Card card;
			card.setCard(i, k);
			deck.push_back(card);
		}
	}
	return deck;
}

Player cutProcess(vector<Player>& tempPlayers, vector<Card>& tempDeck) {
	bool tie;
	vector<Card>  cutPool;
	Player p;
	int biggest = 0;
	do {
		//display players and its cut
		tie = false;
		for (int k = 0; k < tempPlayers.size(); k++)
		{
			tempPlayers[k].setCut(cutDeck(tempDeck));
			wcout << tempPlayers[k].getPlayerName() << ": ";
			tempPlayers[k].getCut().display();
			wcout << endl;
			if (tempPlayers[k].getCut().getCardIndexValue()>biggest)
			{
				biggest = tempPlayers[k].getCut().getCardIndexValue();
			}
		}
		int counter = 0;
		for (int k = 0; k < tempPlayers.size(); k++)
		{
			if (tempPlayers[k].getCut().getCardIndexValue() == biggest)
			{
				counter++;
				p = tempPlayers[k];
			}
		}
		if (counter>1)
		{
			tie = true;
			wcout << "There is a tie, recut" << endl;
		}
	} while (tie);

	return p;
}


class Game {
public:
	Game(Board& myboard) {
		this->myboard = &myboard;
	}
	void postGameProcess() {

	}

	//TEST SCORE CALCULATIONS
	//***********************

	//int updateMark(points) {

	//}

	//int fifteenHand(vector<vector<Card>> totalHands) {
	//	int points = 0;

	//	//updateMark(points);
	//}

	// //I need to pass the current board... not the crib
	//int fifteenCrib(vector<Card> crib) {

	//	int points = 0;
	//	int sum = accumulate(crib.begin(), crib.end(), 0);
	//	if (sum == 15) {
	//		points = 2;
	//		cout << "Gained " << points << " points" << endl;
	//		go();
	//	}
	//	else if (sum == 31){
	//		points = 2;
	//		cout << "Gained " << points << " points" << endl;
	//		//Dont include go
	//	}
	//	//updateMark(points);
	//}

	//int pair(vector<vector<Card>> totalHands) {
	//	int points;
	//	//updateMark(points);
	//}

	//int flush(vector<vector<Card>> totalHands) {
	//	int points;
	//	//updateMark(points);
	//}
	//
	//int runs(vector<vector<Card>> totalHands) {
	//	int points;
	//	//updateMark(points);
	//}

	//int go() { //pass last person 
	//	int points;
	//	//updateMark(points);
	//}


	//***********************

	Board* getBoard() {
		return myboard;
	}
	bool canPlay(vector<Card> hand) {
		int  intFlag = 0,
			roundScore = myboard->getRoundScore();
		for (int i = 0; i < hand.size(); i++)
		{
			if (roundScore + hand[i].getCardValue() > 31) 	intFlag++;
		}
		if (intFlag == hand.size()) return false;
		else return true;
	}

	void setlastTurnPI(Player p, vector<Player> ps) {
		// figure next player
		for (int i = 0; i < ps.size(); i++)
		{

			if (ps[i].getPlayerName() == p.getPlayerName())
			{
				lastTurnPI = i;
			}
		}
	}
	int getnextTurnPI(int lastTurnPI, vector<Player> ps) {
		int nextTurnPI;
		if ((lastTurnPI + 1) == ps.size()) nextTurnPI = 0;
		else nextTurnPI = lastTurnPI + 1;
		return nextTurnPI;
	}
	int getlastTurnPI() {
		return lastTurnPI;
	}
	int getLastPlayCarPI() {
		return this->lastPlayCardPI;
	}
	void setLastPlayCarPI(Player p, vector<Player> ps) {
		for (int i = 0; i < ps.size(); i++)
		{
			if (ps[i].getPlayerName() == p.getPlayerName())
			{
				this->lastPlayCardPI = i;
			}
		}
	}
	void menu() {
		game_greeting(); //greeting and create players

						 // temp variables declaration		
		int playerNum = myboard->getPlayers().size();
		vector<Player> tempPlayers = myboard->getPlayers();
		vector<Card> tempDeck = myboard->getDeck();

		wcout << "Players please take your seats." << endl;
		wcout << L"Status: The match is ready to start." << endl;
		wcout << "The deck has been cut with the following results. " << endl;
		Player dealer = cutProcess(tempPlayers, tempDeck);
		myboard->setDealer(dealer);
		shuflleDeck(tempDeck);
		wcout << endl << dealer.getPlayerName() << " " << "is the Dealer" << endl;
		wcout << "Status: The dealer will now shuffle the deck and start the match." << endl;
		wcout << "shuffling deck ......" << endl;
		wcout << "Draw cards ......" << endl;

		vector<vector<Card>> totalHands;
		for (int k = 0; k < playerNum; k++)
		{
			vector<Card> hand;
			for (int i = 0; i < drawNum; i++) // use draw num
			{
				hand.push_back(drawCard(tempDeck));
				tempPlayers[k].setHand(hand);	 // save to player.hand		
			}
			totalHands.push_back(hand); // save to fist board.firsthand 
		}

		myboard->setFirstHand(totalHands);

		displayBoard(tempDeck, myboard, tempPlayers);

		wcout << "Status: Creating the crib for the round." << endl;

		int pHandsize, intIn;
		for (int k = 0; k < playerNum; k++) // loop players
		{
			displayBoard(tempDeck, myboard, tempPlayers);
			pHandsize = tempPlayers[k].getHand().size(); // get hand size			
			for (int i = 0; i < toCribNum; i++)  // loop toCribNum
			{
				displayBoard(tempDeck, myboard, tempPlayers);
				wcout << tempPlayers[k].getPlayerName() << ", what card would you like to discard to the Crib?(input by order, between 1~" << pHandsize << ")" << endl;
				while (!(wcin >> intIn) || intIn>pHandsize || intIn<1) {
					if (intIn>pHandsize || intIn<1)
					{
						wcout << "you must choose between 1~" << pHandsize << ", no alphabet character allowed";
					}
					wcin.clear();
					wcin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				myboard->pushToCrib(tempPlayers[k].getHand()[intIn - 1]); // push to crib vector
				wcout << tempPlayers[k].getPlayerName() << " played ";
				tempPlayers[k].getHand()[intIn - 1].display(); wcout << endl;
				tempPlayers[k].removeFromHand(intIn - 1);
			}
		}
		displayBoard(tempDeck, myboard, tempPlayers);

		if (fromDeckNum == 1)
		{
			Card c = drawCard(tempDeck);
			c = drawCard(tempDeck);
			c.display();
			wcout << "was cut from deck to Crib(3 players)" << endl;
			myboard->pushToCrib(c);
		}

		//cc.~Card;
		Card tc = drawCard(tempDeck);
		myboard->setCut(tc);


		// dealer cut
		wcout << "Status: " << dealer.getPlayerName() << " cut the deck revealing the ";
		tc.display();
		setlastTurnPI(dealer, tempPlayers);
		wcout << "\nStatus : The round pegging can now commence." << endl;

		pegging(tempDeck, tempPlayers);
	}
	;
private:
	int drawNum, toCribNum, fromDeckNum;
	int lastTurnPI; // last turns player index
	int lastPlayCardPI;
	int totalScore;
	Board *myboard;
	void gameCheck(Board *tempBoard, vector<Player> tempPlayers) {

		int counter = 0;
		bool allGO;
		for (int i = 0; i < tempPlayers.size(); i++)
		{
			if (tempPlayers[i].getGoStatus())
			{
				counter++;
			}
		}
		if (counter == tempPlayers.size()) allGO = true;
		else   allGO = false;
		// check pairs, runs 15,31
		if (tempBoard->getRoundScore() == 31 || allGO)
		{
			if (allGO)
				wcout << "no one can play," << tempPlayers[getLastPlayCarPI()].getPlayerName() << " played last card" << endl;
			else  wcout << "round score reaches 31, clear round play" << endl;
			tempBoard->setRoundScore(0);
			tempBoard->clearRoundPlay();
			/*wcout << tempPlayers[getLastPlayCarPI()].getPlayerName() << " is the person who last played card " << endl;*/
		}


	}
	bool canPegging(vector<Player> tempPlayers) {

		int counter = 0;
		for (int i = 0; i < tempPlayers.size(); i++)
		{
			if (tempPlayers[i].getHand().size() == 0)
			{
				counter++;
			}
		}
		if (counter == tempPlayers.size()) return false;
		else  return true;
		//	//checkAllPlayersStatus
		//	int counter = 0;
		//for (int i = 0; i < tempPlayers.size(); i++)
		//	{
		//		if (tempPlayers[i].getGoStatus())
		//		{
		//			counter++;
		//		}		
		//	}
		//if (counter== tempPlayers.size()) return false;
		//else  return true;
	}
	void displayBoard(vector<Card>tempDeck, Board *tempBoard, vector<Player>tempPlayers) {
		system("pause");
		wcout << wstring(2, '\n');
		system("cls");
		wcout << "  --------------------Deck section  ------------------------------  \n" << endl;
		wcout << " Cut : ";
		tempBoard->getCut().display();
		wcout << "\n Crib : ";
		if (tempBoard->getCrib().empty())
		{
			wcout << "none";
		}
		else {
			for (int i = 0; i < tempBoard->getCrib().size(); i++)
			{
				tempBoard->getCrib()[i].display();
			}
		}
		wcout << endl;
		//displayDeck(tempDeck);
		wcout << endl << "  -------------------- Score section  ------------------------------- \n" << endl;
		tempBoard->printScore();


		if (!tempBoard->getRoundPlay().empty())
		{
			wcout << endl << "  -------------------- Round Played  ------------------------------ \n" << endl;
			wcout << "Round score : " << tempBoard->getRoundScore() << endl;
			wcout << "Round Play: " << endl;
			for (int i = 0; i < tempBoard->getRoundPlay().size(); i++)
			{
				tempBoard->getRoundPlay()[i].display();
			}
		}


		wcout << endl << "  -------------------- Player's hand   ------------------------------ \n" << endl;
		for (int k = 0; k < tempPlayers.size(); k++)
		{
			wcout << tempPlayers[k].getPlayerName();
			if (myboard->isDealer(tempPlayers[k].getPlayerName())) wcout << " <D> ";
			wcout << ": ";
			tempPlayers[k].printHand();
			wcout << endl << endl;
		}




	}
	void pegging(vector<Card> tempDeck, vector<Player> tempPlayers) {

		int pHandsize, intIn, k = getnextTurnPI(getlastTurnPI(), tempPlayers);
		while (canPegging(tempPlayers)) {
			displayBoard(tempDeck, myboard, tempPlayers);
			pHandsize = tempPlayers[k].getHand().size(); // get hand size				

			if (canPlay(tempPlayers[k].getHand()) && pHandsize != 0)
			{
				wcout << endl << tempPlayers[k].getPlayerName() << ", what card would you like to play?(input by order, between 1~" << pHandsize << ")" << endl;
				while (!(wcin >> intIn) || intIn>pHandsize || intIn <1 || !(myboard->setRoundScore(tempPlayers[k].getHand()[intIn - 1]))) {
					if (intIn>pHandsize || intIn <1)
					{
						wcout << "you must choose between 1~" << pHandsize << ", no alphabet character allowed";
					}
					wcin.clear();
					wcin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				myboard->pushToRoundPlay(tempPlayers[k].getHand()[intIn - 1]); // push to roundplay vector			
				wcout << tempPlayers[k].getPlayerName() << " played ";
				tempPlayers[k].getHand()[intIn - 1].display(); wcout << endl;
				tempPlayers[k].removeFromHand(intIn - 1);
				setLastPlayCarPI(tempPlayers[k], tempPlayers);
			}
			else {
				tempPlayers[k].setGoStatus();
				// player can't play card ,go
				if (pHandsize == 0)
				{
					wcout << endl << tempPlayers[k].getPlayerName() << "has empty hand, " << " GO ";
				}
				else {
					wcout << endl << tempPlayers[k].getPlayerName() << "can't play a card(sum more than 31), " << " GO ";
				}
			}
			gameCheck(myboard, tempPlayers);
			if (++k >= tempPlayers.size())
			{
				k = 0;
			}
		}
	}

	void game_greeting() {
		int intIn;
		wcout << L"\n Welcome to Cribbage in C++.  Press Q at any time to quit." << endl;
		wcout << L"How many players are there (2, 3, or 4)? " << endl;
		while (!(wcin >> intIn) || intIn>4) {
			wcout << "you can only decare 2-4 players";
			wcin.clear();
			wcin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (intIn == 2)
		{
			drawNum = 6;
			toCribNum = 2;
			fromDeckNum = 0;
		}
		else if (intIn == 3)
		{
			drawNum = 5;
			toCribNum = 1;
			fromDeckNum = 1;
		}
		else if (intIn == 4)
		{
			drawNum = 5;
			toCribNum = 1;
			fromDeckNum = 0;
		}
		wchar_t str[50];
		wstring wstr;
		for (int i = 0; i < intIn; i++)
		{
			wcout << "Player " << i + 1 << ", please enter your name" << endl;
			ws(wcin); // get rid of space
			wcin.getline(str, 50);
			wstr = str;
			Player tempPlayer(str);
			getBoard()->addToPlayers(tempPlayer);
		}
	}
};


int main() {
	vector<Card> createDeck();
	void displayDeck(vector<Card> deck);
	void menu(Game myGame);
	int getRand(int randMax);
	Card drawCard(vector<Card>&deck);
	Card cutDeck(vector<Card>&deck);
	void shuflleDeck(vector<Card> deck);
	Player cutProcess(vector<Player>& tempPlayers, vector<Card>& tempDeck);


	_setmode(_fileno(stdout), _O_U16TEXT);
	srand(time(NULL));
	vector<Card> deck = createDeck();
	vector<Player> Players;
	Board myBoard(Players, deck);
	Game myGame(myBoard);
	myGame.menu();

	system("pause");
	return 0;
}
