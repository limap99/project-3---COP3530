#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Post{
    private:
        string id;
        int likes;
        int dislikes;
    public:
        Post(string inputId, string inputLikes, string inputDislikes){
            id = inputId;
            likes = stoi(inputLikes);
            dislikes = stoi(inputDislikes);
        }
        string getId(){
            return id;
        }
        int getLikes(){
            return likes;
        }
        int getDislikes(){
            return dislikes;
        }
};