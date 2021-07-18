#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;

class Player {
	private:
	char playerName[30];
	int score;
	public:
	Player(){
	}
	Player(const Player &p){
        	strcpy(playerName,p.playerName);
		this->score = p.score;
	}
	void getPlayer(char name[],int turn,int score=0){
		strcpy(playerName,name);
		this->score = score;
	}
	char * getPlayerName(){
		return playerName;
	}
	int getScore(){
		return score;
	}
	void play(int force){
		srand(time(0));
		int random = (rand() % (20-15+1)) +15;
		if(abs(random-force) == 0){
				this->score += 50;
				cout<<"\t-----------------------------------------"<<endl;
				cout<<"\tBingo !! A perfect Drop.You got 50 Points"<<endl;
				cout<<"\t-----------------------------------------"<<endl;

		}else if(abs(random-force)<2 && abs(random-force)>0){
			this->score += 25;
			cout<<"\t----------------------------"<<endl;
			cout<<"\tAwesome ! you got 25 points."<<endl;
			cout<<"\t----------------------------"<<endl;
		}else{
			this->score += 0;
			cout<<"\t----------------------------"<<endl;
			cout<<"\tOops ! You Missed it."<<endl;
			cout<<"\t----------------------------"<<endl;

		}
		
	}
	void displayScore(){
		cout<<"\t\t"<<playerName<<"\t\tScore : "<<score<<endl;
	}

};
bool compare(Player p1,Player p2);
class Game {
	int participants;
	Player P[10];
	public:
	void getGameInfo(){
		cout<<"\n\t--------------------------------------------------";
		cout<<"\n\tEnter the number of Players(atleast 2 Players) : ";
		cin>>participants;
		char name[30];
		Player p;
		for(int i=0;i<participants;i++){
			cout<<"\n\tEnter the Player "<<i+1<<" Name : ";
			cin>>name;
			P[i].getPlayer(name,i+1);
		}
		cout<<"\t--------------------------------------------------\n";

	}
	int getParticipants(){
		return participants;
	}
	void getPlayers(){
		for(int i=0;i<participants;i++){
			P[i].getPlayerName();
		}
	}
	void startGame(){
		getGameInfo();
		int force;
		for(int j=0;j<3;j++){
			cout<<"\n\t ++++========++++ Round "<<j+1<<" ++++========++++"<<endl;
		for(int i=0;i<participants;i++){
			cout<<"\n\t-------- "<<P[i].getPlayerName()<<"'s turn-------"<<endl;
			while(true){
				try{
				cout<<"\n\tEnter the force between 20 and 15 : ";
				cin>>force;
				if(force>=15 and force<=20){
				P[i].play(force);
				break;
				}
				else
					throw force;
				}catch(int f){
					cout<<"\n\tEnter force between 20 and 15 only."<<endl;
			}
			}
		}
		sort(P,P+participants,compare);
		displayScoreboard();
		}
		ofstream outf;
		outf.open("History.dat",ios::app);
		outf.write((char*)this,sizeof(*(this)));
		outf.close();
	


	}
	void rules();
	void displayScoreboard();
	void showHistory();
     
};



bool compare(Player p1,Player p2){
	return (p1.getScore()>p2.getScore());
}

void Game :: displayScoreboard(){

        
	cout<<"\n\n **** **** **** **** **** **** **** **** **** ****";
      cout<<"\n *    *    *  * *  * *    *  * *  * *  * *  * *  *\n";
        cout<<" *    *    *  * *  * *    *  * *  * *  * *  * *  *\n";
	cout<<" **** *    *  * **** **** **** *  * **** **** *  *\n";
	cout<<"    * *    *  * *    *    *  * *  * *  * *    *  *\n";
	cout<<"    * *    *  * **   *    *  * *  * *  * **   *  *\n";
	cout<<" **** **** **** **** **** **** **** *  * **** ****\n";
	int flag = 0;
	for(int i=0;i<participants;i++){
		if(flag==0){
			cout<<"\n===================================================================";
			cout<<"\n\tPosition\t\tPlayer Name\t\t Score\n";
			cout<<"===================================================================\n";
			flag =-1;
		}
		cout<<"\t\t"<<i+1;
			P[i].displayScore();
	}
	cout<<"\n\n";
}

void Game::rules(){
    cout << "\n\n\t======PUT THE BALL IN BASKET RULES!======\n\n";
    cout << "\t1. Enter the magnitude of force \n";
    cout << "\t2. After each Ball Droped in the Basket Directly Player gets 50 Points \n";  
    cout << "\t3. After each Ball Droped in the Basket indirectly, Player gets 25 Points \n";
    cout << "\t4. If ball missed Basket, Player gets 0 Points \n\n";
}


void Game :: showHistory(){
	ifstream fin;
	fin.open("History.dat");
	Game G[100];

	cout<<"\n==========================================\n";
	cout<<"\t\tHistory\n";
	cout<<"==========================================\n";
	fin.seekg(0,ios::end);

	int c = fin.tellg()/sizeof(*(this));
	cout<<c<<endl;
	fin.seekg(0,ios::beg);
	for(int i=0;i<c;i++){
		fin.read((char*)&G[i],sizeof(G[i]));
	}
	if(c>0){
	for(int i=c-1;i>=0;i--){
		cout<<i+1<<"th Game"<<endl;
		G[i].displayScoreboard();
		
	}
	}else{
		cout<<"Empty"<<endl;
	}
	fin.close();
}

int main(){
	cout<<"\n\t\t============================== Put The Ball in Basket ==========================\n"<<endl;

		int o,c;
		Game g;
		while(true){
			cout<<"\n\t1.Start the Game\n\t2.Display Game Rules\n\t3.Show History\n\t4.Exit";
			cout<<"\n\n\tEnter your choice : ";
			cin>>o;
			switch(o){
				case 1:g.startGame();
				       break;
				case 2:g.rules();
				       break;
				case 3:g.showHistory();
				       break;
				case 4:exit(0);

			}
		}
		return 0;
}



			

		


	



