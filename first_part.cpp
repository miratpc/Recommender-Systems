#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


int main() {
	// map to store data: user ID -> number of ratings
	map<string, int> user_ratings;
	// map to store data: movie ID -> number of ratings
	map<string, int> movie_ratings;

	
	// open the input file
	ifstream input_file("train.csv");
	// check if the file was opened successfully
	if (!input_file.is_open()) {
		cout << "Error: unable to open input file." << endl;
		return 1;
	}
	
	// read the file line by line
	string line;
	while (getline(input_file, line)) {
		// split the line by comma
		int pos = line.find(',');
		string user_id = line.substr(0, pos);
		line = line.substr(pos + 1);
		pos = line.find(',');
		string movie_id = line.substr(0, pos);

		
		// update the data in the maps
		user_ratings[user_id]++;
		movie_ratings[movie_id]++;
	}
	

	// close the input file
	input_file.close();


		// print the top 10 users by number of ratings
		cout << "Top 10 users by number of ratings:" << endl;
	map<int, string> sorted_users;
	for (auto& kv : user_ratings) {
		sorted_users[-kv.second] = kv.first;
	}

	
	int count = 0;
	for (auto& kv : sorted_users) {
		cout << "user " << kv.second << ": " << -kv.first << " ratings" << endl;
		count++;
		if (count >= 10) {
			break;
		}
	}
	
	// print the top 10 movies by number of ratings
	cout << "Top 10 movies by number of ratings:" << endl;
	map<int, string> sorted_movies;
	for (auto& kv : movie_ratings) {
		sorted_movies[-kv.second] = kv.first;
	}
	
	count = 0;
	for (auto& kv : sorted_movies) {
		cout << "movie " << kv.second << ": " << -kv.first << " ratings" << endl;
		count++;
		if (count >= 10) {
			break;
		}
	}

	

	return 0;
}

