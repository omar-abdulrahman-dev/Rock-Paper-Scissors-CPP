#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<string> 
using namespace std;

enum en_name_choice { stone = 1, paper = 2, scissors = 3 };
enum en_name_result { win = 1, drow = 2, lose = 3 };

struct stroundinfo
{
    short roundnumber = 0;
    en_name_choice player;
    en_name_choice machin;
    en_name_result winner;
};

struct stgameresult
{
    short totalround = 0;
    short playerwintimes = 0;
    short machinwintimes = 0;
    short drowtimes = 0;
    en_name_result finalresult;
};

int ReadNumberRounds() {
    int rounds;
    cout << "How many rounds from 1 to 10? \n";
    cin >> rounds;
    return rounds;
}

int RandomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

en_name_choice GetMachineChoice()
{
    return (en_name_choice)RandomNumber(1, 3);
}

en_name_choice readplayerchoice()
{
    int choice;
    do {
        cout << "Your choice : [1] stone , [2] paper , [3] scissors ?\n";
        cin >> choice;
    } while (choice < 1 || choice > 3);

    return (en_name_choice)choice;
}

string choicetostring(en_name_choice choice)
{
    if (choice == en_name_choice::stone)
        return "stone";
    else if (choice == en_name_choice::paper)
        return "paper";
    else
        return "scissors";
}

string winnertostring(en_name_result winner)
{
    if (winner == en_name_result::win)
        return "you";
    else if (winner == en_name_result::lose)
        return "machin";
    else
        return "drow";
}

// صلحنا هنا الاستلام عشان يكون Choice مش Result
en_name_result whowinround(en_name_choice player, en_name_choice machin)
{
    if (player == machin)
        return en_name_result::drow;

    if ((player == en_name_choice::stone && machin == en_name_choice::scissors)
        || (player == en_name_choice::paper && machin == en_name_choice::stone)
        || (player == en_name_choice::scissors && machin == en_name_choice::paper))
    {
        return en_name_result::win;
    }
    else
    {
        return en_name_result::lose;
    }
}

en_name_result WhoWonTheGame(short playerWins, short machineWins)
{
    if (playerWins > machineWins)
        return en_name_result::win;
    else if (machineWins > playerWins)
        return en_name_result::lose;
    else
        return en_name_result::drow;
}

stgameresult playgame(int round)
{
    stgameresult gameresult;
    gameresult.totalround = round;

    // صلحنا هنا (<=) عشان اللوب يكمل للآخر
    for (int i = 1; i <= round; i++) 
    {
        cout << "\nRound [" << i << "] begins : \n\n";

        stroundinfo roundinfo;

        roundinfo.roundnumber = i;
        roundinfo.player = readplayerchoice();
        roundinfo.machin = GetMachineChoice();
        roundinfo.winner = whowinround(roundinfo.player, roundinfo.machin);

        // شيلنا الـ return من هنا عشان اللوب مايقفش
        if (roundinfo.winner == en_name_result::win)
            gameresult.playerwintimes++;
        else if (roundinfo.winner == en_name_result::lose)
            gameresult.machinwintimes++;
        else
            gameresult.drowtimes++;

        cout << "______________________Round[" << i << "]________________________\n";
        // وحدنا الأسماء هنا عشان تشتغل مع الدوال بتاعتك
        cout << "Your choice is : " << choicetostring(roundinfo.player) << endl;
        cout << "Machine choice is : " << choicetostring(roundinfo.machin) << endl;
        cout << "Round winner : " << winnertostring(roundinfo.winner) << endl;
        cout << "______________________________________________________\n\n";
    }

    // ظبطنا الأسماء هنا
    gameresult.finalresult = WhoWonTheGame(gameresult.playerwintimes, gameresult.machinwintimes);

    return gameresult;
}

// وحدنا اسم الصندوق هنا عشان يبقى زي اللي فوق (stgameresult)
void PrintGameOver(stgameresult gameresult) {
    cout << "____________________________________________________________________\n\n";
    cout << "                             +++ game over +++                      \n\n";
    cout << "____________________________________________________________________\n\n";
    cout << "_________________________   game result   __________________________\n\n";
    cout << "Game rounds = " << gameresult.totalround << endl;
    cout << "You won times : " << gameresult.playerwintimes << endl;
    cout << "Machine won times : " << gameresult.machinwintimes << endl;
    cout << "Draw times : " << gameresult.drowtimes << endl;

    if (gameresult.finalresult == en_name_result::win) {
        system("color 2a");
        cout << "Result final : YOU WON!" << endl;
    }
    else if (gameresult.finalresult == en_name_result::lose) {
        system("color 4c");
        cout << "Result final : MACHINE WON!" << endl;
    }
    else {
        system("color 60");
        cout << "Result final : DRAW!" << endl;
    }
}

void StartGame() {
    char restart;
    do {
        system("cls");      
        system("color 0F"); 

        int rounds = ReadNumberRounds();
        
        stgameresult finalResults = playgame(rounds);
        
        PrintGameOver(finalResults);

        cout << "\nDo you want to play another game? (y/n) \n";
        cin >> restart;

    } while (restart == 'y' || restart == 'Y');
}

int main() {
    srand((unsigned)time(NULL));
    
    StartGame(); 
    
    return 0;
}