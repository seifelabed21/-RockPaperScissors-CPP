#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>

using namespace std;

enum enRPS {rock = 1, paper = 2, scissors = 3};
enum enWinner {Player = 1, Computer = 2, Draw = 3};

struct stRound_Info{
    short round_number = 0;
    enRPS player_choice;
    enRPS computer_choice;
    enWinner winner;
    string round_winner = "";
};

struct stCounters{
    int player_count = 0;
    int computer_count = 0;
    int draw_count = 0;
};

struct stGame_Resuls{
    short number_of_rounds;
    stCounters Game_Counters;
    enWinner winner;
    string winner_name;
};

int Read_How_Many_Rounds(){
    int n = 0;
    do
    {
        cout << "How many rounds you wanna play (1 - 10) : ";
        cin >> n;
    } while (n<1 || n>10);
    return n;
}

int Random_Number(int From, int To){
    int random = 0;
    random = rand() % (To - From + 1) + From;
    return random;
}

enRPS Read_Player_Choice(){
    int choice = 0;
    do
    {
        cout << endl;
        cout << "Your Choice ([1] Rock, [2] Paper, [3] Scissors) : ";
        cin >> choice;
    } while(choice != 1 && choice != 2 && choice != 3);
    return (enRPS) choice;
}

enRPS Generate_computer_Choice(){
    return (enRPS) Random_Number(1,3);
}

string Get_Round_Choice(enRPS choice){
    switch (choice)
    {
        case enRPS::rock:
            return "Rock";
        case enRPS::paper:
            return "Paper";
        case enRPS::scissors:
            return "Scissors";
        default:
            return "Rock";
    }
}

enWinner Get_Winner(stRound_Info round){
    if (round.player_choice == round.computer_choice)
        return enWinner::Draw;
    else if (round.player_choice == enRPS::rock)
        if (round.computer_choice == enRPS::paper)
            return enWinner::Computer;
    else if (round.player_choice == enRPS::paper)
        if (round.computer_choice == enRPS::scissors)
            return enWinner::Computer;
    else if (round.player_choice == enRPS::scissors)
        if (round.computer_choice == enRPS::rock)
            return enWinner::Computer;   
    return enWinner::Player;
}

string Get_Winner_Name(enWinner winner){
    switch(winner)
    {
        case enWinner::Computer:
            return "[Computer]";
        case enWinner::Player:
            return "[Player]";
        default:
            return "[No Winner]";
    }
}

void Print_Round_Menu(stRound_Info round){
    cout << endl; 
    cout << "------------ Round [" << round.round_number << "] -----------" << endl;
    cout << "Player Choice   : " << Get_Round_Choice(round.player_choice) << endl;
    cout << "Computer Choice : " << Get_Round_Choice(round.computer_choice) << endl;
    cout << "Round winner    : " << round.round_winner << endl;
    cout << "----------------------------------" << endl;
    cout << endl;
}

void Print_Game_Over(){
    cout << "\t\t" << "---------------------------------------" << endl;
    cout << "\t\t" << "\t+++ G a m e O v e r +++\t" << endl;
    cout << "\t\t" << "---------------------------------------" << endl << endl;
    
}

void Print_Game_Results_Menu(stGame_Resuls results){
    cout << "\t\t" << "-----------[ Game Results ]------------" << endl;
    cout << "\t\t" << "Game Rounds        : " << results.number_of_rounds << endl;
    cout << "\t\t" << "Player won times   : " << results.Game_Counters.player_count << endl;
    cout << "\t\t" << "Computer won times : " << results.Game_Counters.computer_count << endl;
    cout << "\t\t" << "Draw times         : " << results.Game_Counters.draw_count << endl;
    cout << "\t\t" << "Final Winner       : " << results.winner_name << endl;
    cout << "\t\t" << "---------------------------------------" << endl;
}

void Update_Counters(enWinner winner,struct stCounters& Game_counter){
    if (winner == enWinner::Computer)
        Game_counter.computer_count++;
    else if (winner == enWinner::Player)
        Game_counter.player_count++;
    else 
        Game_counter.draw_count++;
}

void Winner_Animation(string winner){
    if (winner == "[Player]")
    {
        system("color 20");
    }
    else if (winner == "[Computer]")
    {
        system("color 40");
        cout << "\a";
    }
    else if (winner == "[No Winner]")
    {
        system("color 60");
    }
}

void Get_Final_Winner(stGame_Resuls& results){
    if (results.Game_Counters.player_count>results.Game_Counters.computer_count)
        results.winner = enWinner::Player;
    else if (results.Game_Counters.player_count<results.Game_Counters.computer_count)
        results.winner = enWinner::Computer;
    else
        results.winner = enWinner::Draw;
}

void Reset_Screen(){

}

stGame_Resuls Play_A_Game(int number_of_rounds){
    cout << endl;
    stGame_Resuls Results;
    stRound_Info round_info;
    Results.number_of_rounds = number_of_rounds;
    for (int round_number = 1; round_number<=number_of_rounds; round_number++)
    {
        cout << "\n Round [" << round_number << "] Begins : \n";

        round_info.round_number = round_number;
        round_info.player_choice = Read_Player_Choice();
        round_info.computer_choice = Generate_computer_Choice();
        round_info.winner = Get_Winner(round_info);
        round_info.round_winner = Get_Winner_Name(round_info.winner);

        Winner_Animation(round_info.round_winner);
        Update_Counters(round_info.winner,Results.Game_Counters);
        Print_Round_Menu(round_info);
    }
    Get_Final_Winner(Results);
    Results.winner_name = Get_Winner_Name(Results.winner);
    return Results;
}

void Start_Game(){
    char choice = 'y';
    do
    {
        stGame_Resuls Results = Play_A_Game(Read_How_Many_Rounds());
        cout << endl << endl;
        Print_Game_Over();
        Print_Game_Results_Menu(Results);
        cout << "\t\t" << "Do you want to play again (Y/N) : ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
}

int main(){
    srand((unsigned)time(NULL));
    Start_Game();
    return 0;
}
