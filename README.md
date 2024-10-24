#RECOMMENDER SYSTEMS USING C++

## Overview
This project focuses on developing a movie recommendation system using neighborhood-based collaborative filtering algorithms. The system analyzes past user interactions, such as views, ratings, and purchases, to generate personalized movie recommendations.

## Contents
1. [Top 10 Users and Top 10 Movies](#top-10-users-and-top-10-movies)
2. [Recommendation System](#recommendation-system)
3. [Technologies Used](#technologies-used)

## Top 10 Users and Top 10 Movies
In the first part of the project, the program reads an input file (`train.csv`) and outputs the top 10 users and movies based on their rating count. 

### Libraries Used
- **iostream**: Provides input/output stream objects.
- **fstream**: Provides file stream objects.
- **map**: Allows efficient lookup and insertion of elements using key-value pairs.
- **string**: Represents a sequence of characters.
- **algorithm**: Provides various algorithms such as sorting.

### Process
1. **Data Structures**:
   - `user_ratings`: A map storing user IDs and their corresponding rating counts.
   - `movie_ratings`: A map storing movie IDs and their corresponding rating counts.

2. **File Handling**:
   - Opens `train.csv`, reads the file line by line, extracts user and movie IDs, and increments their respective counts.

3. **Sorting and Output**:
   - Sorts the maps in decreasing order of rating counts and prints the top 10 users and movies.

## Recommendation System
In the second part, the aim is to create a movie recommendation system utilizing collaborative filtering algorithms.

### Data Files
- `train.csv`: Contains historical ratings used to build the recommendation model.
- `test.csv`: Used for testing the model's predictions.

### Libraries Used
- **<iostream>**, **<fstream>**, **<vector>**, **<unordered_map>**, **<cmath>**, **<algorithm>**, etc.

### Process
1. **Cosine Similarity Function**:
   - A function is defined to calculate cosine similarity between two vectors.

2. **Model Building**:
   - Reads data from `train.csv` and `test.csv`, storing user ratings in a hash map.

3. **Predictions**:
   - For each item in the test data, it calculates predicted ratings using both user-based and item-based collaborative filtering.

4. **Output**:
   - Writes the user ID, item ID, and predicted rating to `submission.csv`.

## Technologies Used
- C++
- Collaborative Filtering Algorithms
- File I/O for Data Handling

## Conclusion
This project effectively demonstrates the use of data structures and algorithms in building a movie recommendation system, highlighting the importance of collaborative filtering in providing personalized experiences.

