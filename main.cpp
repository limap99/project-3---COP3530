#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include "Posts.h"



using namespace std;
using namespace std::chrono;

// try to put the posts.h code in posts.cpp
// add some comments to the code





int main()
{
    fstream dataset;
    dataset.open("dataset.csv", ios::in);

    int id, likes, dislikes;

    Posts posts;

    string line;
    getline(dataset, line);
    for(int i = 0; i < 100000; i++){ 
        getline(dataset, line);

        int commaIndex = line.find_first_of(',');
        string id = line.substr(0, commaIndex);

        line = line.substr(commaIndex + 1);

        commaIndex = line.find_first_of(',');
        string likes = line.substr(0, commaIndex);

        line = line.substr(commaIndex + 1);

        string dislikes = line;

        Post* post = new Post(id, likes, dislikes);
        posts.addPost(post);

       

    }

    while(true){
        int userInput;
        cout << "Select an option:\n 1. Get most liked post\n 2. Get most disliked post\n 3. Display most liked posts (descending order)\n 4. Display most disliked posts (descending order)\nInput: ";
        cin >> userInput;
        int total;

        switch (userInput)
        {
        case 1: // get most liked post
            posts.displayMaxLikedPost();
            break;
        case 2: // get most disliked post
            posts.displayMaxDislikedPost();
            break;
        case 3: // display the total posts with most likes
            cout << "Total: ";
            cin >> total;
            cout << '\n';
            posts.displayPostsLikes(total);
            cout << '\n';
            break;
        case 4:  // display the total posts with most dislikes
            cout << "Total: ";
            cin >> total;
            cout << '\n';
            posts.displayPostsDislikes(total);
            cout << '\n';
            break;
        default: // invalid input
            cout << "Input a valid option" << endl;
            break;
        }
    }
    

    

    // posts.displayMaxLikedPost();
    // posts.displayMaxDislikedPost();

    cout << "quick"<< endl;
}