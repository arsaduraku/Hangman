#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <utility>  


using namespace std;

// Struktura ruan statistikat e lojtarit, përfshirë fitoret, humbjet dhe shkallën e suksesit.
struct PlayerStats {
    int wins;
    int losses;
    float successRate;
};

//Funksioni shfaq fjalen duke zevendesuar shkronjat e pazbuluara me _ , bazuar ne vektorin guessed, qe tregon cilat shkronja jane gjetur.
void printWord(string word, vector<bool> guessed) { 
    for (size_t i = 0; i < word.size(); i++) {
        if (guessed[i]) {
            cout << word[i] << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

//Funksioni kontrollon nese te gjitha shkronjat e fjales jane gjetur duke verifikuar nese te gjitha vlerat ne vektorin `guessed` jane `true`.
bool isWordGuessed(vector<bool> guessed) {
    for (bool g : guessed) {
        if (!g) return false;
    }
    return true;
}



//Funksioni ruan statistikat e lojtarit ne nje skedar te quajtur ("stats.txt") duke perdorur objektin `ofstream`.
void saveStats(PlayerStats stats) {
    ofstream file("stats.txt");
    if (file.is_open()) {
        file << stats.wins << " " << stats.losses << " " << stats.successRate << endl;
        file.close();
    }
}
//Funksioni lexon statistikat e lojtarit nga skedari ("stats.txt") duke perdorur `ifstream` dhe i kthen ato si nje strukture `PlayerStats`.
PlayerStats loadStats() {
    ifstream file("stats.txt");  //fstream
    PlayerStats stats = { 0, 0, 0.0 };
    if (file.is_open()) {
        file >> stats.wins >> stats.losses >> stats.successRate;
        file.close();
    }
    return stats;
}

//Funksioni menaxhon lojen e gjetjes se fjales duke ndjekur perpjekjet e lojtarit, perditesuar statusin e shkronjave te gjetura dhe ruajtur statistikat e fitores ose humbjes.
void playGame(string word, string hint, PlayerStats& stats) {
    vector<bool> guessed(word.length(), false);
    int attempts = 6;
    char letter;
    bool hintUsed = false;

    while (attempts > 0) {
        printWord(word, guessed);
        cout << "Tentativat e mbetura: " << attempts << endl;
        cout << "Gjej shkronjen (ose shtyp '?' per nje informate): ";
        cin >> letter;
        

        if (letter == '?' && !hintUsed) {
            cout << "Informate: " << hint << endl;
            hintUsed = true;
            continue;
        }
        else if (letter == '?' && hintUsed) {
            cout << "Ju keni perdorur informaten!" << endl;
            continue;
        }

        bool found = false;
        for (size_t i = 0; i < word.length(); i++) {
            if (word[i] == letter) {
                if (!guessed[i]) {
                    guessed[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            attempts--; // Zvogelon perpjekjet vetem nese supozimi eshte i pasakte
        }

        if (isWordGuessed(guessed)) {
            cout << "Urime! E keni gjetur fjalen." << endl;
            stats.wins++;
            break;
        }
    }

    if (attempts == 0) {
        cout << "Keni humbur! Fjala ishte: " << word << endl;
        stats.losses++;
    }

    stats.successRate = (stats.wins * 100.0) / (stats.wins + stats.losses);
    saveStats(stats);
}


//Funksioni `main` inicializon lojen duke zgjedhur nje fjale random nga lista, ngarkon statistikat e lojtarit dhe ekzekuton funksionin `playGame` per te filluar lojen.
int main() {
    map<int, vector<pair<string, string>>> difficultyWords = {
       {1, {{"kompjuteri", "Nje pajisje elektronike qe perpunon te dhena dhe kryen llogaritje komplekse permes softuerit dhe harduerit te tij."}}},
       {2, {{"powerpoint", "Nje program i zhvilluar nga Microsoft qe perdoret per te krijuar prezantime vizuale."},
            {"projekti", "Nje pune ose detyre e planifikuar qe ka nje qellim specifik dhe zakonisht perfshin disa hapa per ta realizuar."}}},
       {3, {{"figma", "Nje mjet i fuqishem per dizajnin e nderfaqeve UI/UX qe funksionon ne internet."},
            {"github", "Nje platforme e njohur per ruajtjen dhe ndarjen e kodit burimor. "}}}
    };
}
