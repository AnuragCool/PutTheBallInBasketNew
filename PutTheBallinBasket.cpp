#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;



class Player {
	private:
	char playerName[30];
	int score;
	int rank;
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
	vector<Player> P;
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
			p.getPlayer(name,i+1);
			P.push_back(p);
		}
		cout<<"\t--------------------------------------------------\n";

	}
	int getParticipants(){
		return participants;
	}
	void startGame(){
		P.clear();
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
		sort(P.begin(),P.end(),compare);
		displayScoreboard();
		}
		fstream outf;
			for(int i=0;i<P.size();i++){
			cout<<P[i].getPlayerName();
		}


		outf.open("History.txt",ios::app|ios::out);
		outf.write((char *) &(*(this)),sizeof(*(this)));

		for(int i=0;i<P.size();i++){
			cout<<P[i].getPlayerName();
		}
		outf.close();



	}
	void rules();
	void displayScoreboard();
     
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
	for(int i=0;i<P.size();i++){
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

void start(){
		
	
}

void  showHistory(){
	ifstream fin;
	fin.open("History.txt");
	Game g1;
	vector<Game> G;

	cout<<"\n==========================================\n";
	cout<<"\t\tHistory\n";
	cout<<"==========================================\n";
	fin.seekg(0,ios::end);

	int c = fin.tellg()/sizeof(g1);
	cout<<c<<endl;
	fin.seekg(0,ios::beg);
	for(int i=0;i<c;i++){
		fin.read((char*)&g1,sizeof(g1));
		G.push_back(g1);
	}
	cout<<G.size();
	if(G.size()>0){
	for(int i=G.size()-1;i>=0;i--){
		cout<<i+1<<"th Game"<<endl;
		G[i].displayScoreboard();
		
	}
	}else{
		cout<<"Empty"<<endl;
	}
	G.clear();
	fin.close();
}

int main(){
	cout<<"\n\t\t============================== Put The Ball in Basket ==========================\n"<<endl;

		int o;
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
				case 3:showHistory();
				       break;
				case 4:exit(0);

			}
		}
		return 0;
}



			

		


	



