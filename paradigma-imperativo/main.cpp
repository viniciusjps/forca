#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

typedef struct{
	int points;
	int lifes;
	string nickname;
}player;

typedef struct{
	string name;
}level;

void add_points(player &gamer, level &actual_level) {
	if (actual_level.name == "PYTHON") {
		gamer.points += 20;
	} else if (actual_level.name == "JAVA") {
		gamer.points += 30;
	} else if (actual_level.name == "ASSEMBLY") {
		gamer.points += 50;
	}
}

/* Set level
*/
void set_level(level &actual_level, int round) {
	if (round <= 3) {
		actual_level.name = "PYTHON";
	} else if (round >= 4 && round <= 6) {
        actual_level.name = "JAVA";
	} else if (round >= 7 && round <= 10) {
        actual_level.name = "ASSEMBLY";
	}
}

void start_score(player &gamer1, player &gamer2) {
	gamer1.points = 0;
	gamer2.points = 0;
}

void start_life(player &gamer1, player &gamer2) {
	gamer1.lifes = 0;
	gamer2.lifes = 0;
}

/* This function add  to the player
 */

 void add_lifes(player &gamer, level &actual_level) {
	if (actual_level.name == "PYTHON") {
		gamer.lifes += 7;
	} else if (actual_level.name == "JAVA") {
		gamer.lifes += 5;
	} else if (actual_level.name == "ASSEMBLY") {
		gamer.lifes += 3;
	}
}

void transfer_points(level &actual_level, player &winner_player, player &loser_player) {
	int points;
	if (actual_level.name == "PYTHON") {
		points = loser_player.points * 0.1;
	} else if (actual_level.name == "JAVA") {
		points = loser_player.points * 0.15;
	} else if (actual_level.name == "ASSEMBLY") {
		points = loser_player.points * 0.2;
	}
	winner_player.points += points;
	loser_player.points -= points;
}

void  penalize_player(level actual_level, player &gamer) {
	int penalty;

	if (actual_level.name == "PYTHON") {
		penalty = 2;
	} else if (actual_level.name == "JAVA") {
		penalty = 5;
	} else if (actual_level.name == "ASSEMBLY") {
		penalty = 8;
	}

	gamer.lifes--;
	gamer.points -= penalty;
}

vector<int> contains(string actual_word, char letter) {
    vector<int> index;
    for (int i = 0; i < actual_word.size(); i++) {
        if (actual_word[i] == letter) {
            index.push_back(i);
        }
    }
    return index;
}

void update_status_of_word(vector<int> index, string &actual_status_of_word, char letter) {
	for (int i = 0; i < index.size(); i++) {
		actual_status_of_word[index[i]] = letter;
	}
}

/* Verifica se a letra esta na palavra,
 * e imprime a situacao da palavra no momento
*/
void verify_letter(player &gamer, char letter, level &actual_level, string actual_word, string &actual_status_of_word) {
	vector<int> index = contains(actual_word, letter);
	if (index.size() == 0) {
        cout << "A palavra nao possui essa letra! -1 tentativa, proximo:\n\n";
        penalize_player(actual_level, gamer);
	}

	update_status_of_word(index, actual_status_of_word, letter);
}

void model_word(int word_length, string &actual_status_of_word) {
	for (int i = 0; i < word_length; i++) {
		actual_status_of_word += "_";
	}
}

void player_status(player &gamer) {
	cout << "Status: " << gamer.nickname << endl;
	cout << "=> Tentativas restantes: " << gamer.lifes << endl;
	cout << "=> Total de pontos: " << gamer.points << endl;
}

void receive_letter(player &gamer, level &actual_level, string actual_word, string &actual_status_of_word){
    char letter;
    cout << gamer.nickname + ", digite uma letra: ";
    cin >> letter;
	verify_letter(gamer, letter, actual_level, actual_word, actual_status_of_word);
	player_status(gamer);
}

//========================FILES AREA============================

typedef struct{
	string word;
	vector<string> synonyms;
	vector<string> _class;
	int syllables;
}word_data;

vector<string> split(string s, char c) {
	string buff = "";
	vector<string> v;

	for(int i = 0; i < s.size(); i++)
	{
		if(s[i] != c) buff+=s[i]; else
		if(s[i] == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);

	return v;
}

string get_line_data(int number_word) {
    srand(time(NULL));
    int line = rand() % number_word + 1;
    ifstream file("dicionario.csv");
    string value;
    for (int i = 0; i < line; i++)
    {
         getline ( file, value, '\n' );
    }
    return value;
}

word_data get_word_data(string line_data) {
    word_data data_word;
    vector<string> data = split(line_data, ',');
    data_word.word = data[0];
    data_word.synonyms = split(data[1], '.');
    data_word._class = split(data[2], '.');
    data_word.syllables = split(data[3], '-').size();

    return data_word;
}

// Utils
void to_string_vector(vector<string> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size()-1) {
            cout << ", ";
        }
    }
    cout << endl;
}

// Utils
void to_string_word_data(word_data w) {
    cout << "Palavra: " << w.word << endl;
    cout << "Sinonimo: ";
    to_string_vector(w.synonyms);
    cout << "Classes: ";
    to_string_vector(w._class);
    cout << "Silabas: " << w.syllables << endl;
}

//===========================FILES AREA=================================

string selection_word(word_data data) {
	string word = data.word;
	cout << endl << "Sorteando a palavra..." << endl;
	sleep(2);
	return word;
}

void compare_words(string actual_word, player &actual_player, level &actual_level) {
    string word;
    cin >> word;
    if (actual_word != word) {
        penalize_player(actual_level, actual_player);
    }
}

void set_actual_player(player &actual_player, player &last_player, string &actual_status_of_word){
	actual_player = last_player;
	cout << actual_status_of_word << endl << endl;
}

int main() {
	// VARIAVEIS
	player player1, player2;
	level actual_level;
	bool state_game;
	int round_game;
	string actual_word;
	string actual_status_of_word;
	int number_word = 95;
    bool gamer_win = 0;
    player actual_player;

	// INICIALIZANDO AS VARIAVEIS
	round_game = 1;
    set_level(actual_level, round_game);
    start_score(player1, player2);
    start_life(player1, player2);
	add_lifes(player1, actual_level);
	add_lifes(player2, actual_level);
	add_points(player1, actual_level);
	add_points(player2, actual_level);

	// DADOS JOGADOR
	cout << "Nome jogador 1: ";
	cin >> player1.nickname;
	cout << "Nome jogador 2: ";
	cin >> player2.nickname;

	state_game = player1.lifes != 0 || player2.lifes != 0;

	string line_data = get_line_data(number_word); //Linha com dados da palavra obtida do dicionario
  	word_data actual_word_data = get_word_data(line_data); // struct contendo dados da palavra
  	actual_word = selection_word(actual_word_data);
	model_word(actual_word.size(), actual_status_of_word);

	while (state_game) {
		receive_letter(player1, actual_level, actual_word, actual_status_of_word);
		set_actual_player(actual_player, player1, actual_status_of_word);

		// system("clear");
		receive_letter(player2, actual_level, actual_word, actual_status_of_word);
		set_actual_player(actual_player, player2, actual_status_of_word);
		// system("clear");

        int covered_size = actual_word.size() - contains(actual_status_of_word, '_').size();
        if (covered_size >= (actual_word.size() * 0.4)) {
            cout << "Digite a palavra completa: ";
            compare_words(actual_word, actual_player, actual_level);
        }
		if (covered_size == 0) {
            round_game++;
            cout << "Parabens! Proxima rodada..." << endl;
		}
	}
	return 0;
}