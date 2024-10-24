#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using namespace std;

double cosine(vector<string> A, vector<string> B) {
	double a = stod(A[1]);
	double b = stod(B[0]);
	double c = stod(A[2]);
	double d = stod(B[1]);
	double x = (a * b) + (c * d);
	double y = (a * a) + (c * c);
	double z = (b * b) + (d * d);
	double r = x / sqrt(y * z);
	return r;

}

int main() {
	fstream myFile;
	string line, word;
	myFile.open("train.csv", ios::in);
	unordered_map<string, vector<string>> listOfRow;
	vector<string> row;
	for (int i = 0; i <= 1048570; i++) {
		row.clear();
		getline(myFile, line);
		stringstream s(line);
		while (getline(s, word, ',')) {
			row.push_back(word);
		}
		listOfRow[row[0]] = row;
	}
	vector<string> row_test;
	vector<vector<string>> row_test_list;
	string lin;
	fstream myFile2;
	myFile2.open("test.csv", ios::in);
	for (int i = 0; i <= 5000; i++) {
		row_test.clear();
		getline(myFile2, lin);
		stringstream s(lin);
		while (getline(s, word, ',')) {
			row_test.push_back(word);
		}
		row_test_list.push_back(row_test);
	}

	ofstream submit;
	submit.open("submission.csv");

	double rating_predicted_user, rating_predicted_item;
	vector<double> bests;
	unordered_map<string, vector<double>> item_ratings;
	// Compute predicted rating using item-based collaborative filtering
	for (const auto& pair : listOfRow) {
		const string& key = pair.first;
		const vector<string>& value = pair.second;
		if (item_ratings.find(value[1]) == item_ratings.end()) {
			item_ratings[value[1]] = { stod(value[2]) };
		}
		else {
			item_ratings[value[1]].push_back(stod(value[2]));
		}
	}
	for (int a = 0; a <= 5000; a++) {
		bests.clear();
		// Compute predicted rating using user-based collaborative filtering
		for (const auto& pair : listOfRow) {
			const string& key = pair.first;
			const vector<string>& value = pair.second;
			double sim = cosine(row_test_list[a], value);
			if (sim > 0.6) { // Only consider ratings from users that are similar to the target user
				bests.push_back(stod(value[2]));
			}
		}
		if (!bests.empty()) {
			rating_predicted_user = accumulate(bests.begin(), bests.end(), 0.0) / bests.size();
		}
		else {
			// If there are no similar users, use the average rating of all users as the prediction
			vector<double> all_ratings;
			for (const auto& pair : listOfRow) {
				const string& key = pair.first;
				const vector<string>& value = pair.second;
				all_ratings.push_back(stod(value[2]));
			}
			rating_predicted_user = accumulate(all_ratings.begin(), all_ratings.end(), 0.0) / all_ratings.size();
		}
		// Compute predicted rating using item-based collaborative filtering
		bests.clear();
		for (const auto& pair : item_ratings) {
			const string& key = pair.first;
			const vector<double>& value = pair.second;
			if (key.compare(row_test_list[a][1]) == 0) {
				bests = value;
				break;
			}
		}
		if (!bests.empty()) {
			rating_predicted_item = accumulate(bests.begin(), bests.end(), 0.0) / bests.size();
		}
		else {
			// If there are no ratings for the item, use the average rating of all items as the prediction
			vector<double> all_ratings;
			for (const auto& pair : item_ratings) {
				const vector<double>& value = pair.second;
				all_ratings.insert(all_ratings.end(), value.begin(), value.end());
			}
			rating_predicted_item = accumulate(all_ratings.begin(), all_ratings.end(), 0.0) / all_ratings.size();
		}

		double rating_predicted = (rating_predicted_user * 0.9 + rating_predicted_item * 0.1);
		// Write the predicted rating to the submission file
		submit << row_test_list[a][0] << "," << rating_predicted << endl;
	}
	return 0;
}
