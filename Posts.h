#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include "Post.h"

using namespace std;
using namespace std::chrono;


class Posts{
    private:
        vector<Post*> postsVector;
        Post* maxLikedPost;
        Post* maxDislikedPost;
        int postsVectorSize = 100000;
        const int run = 32; // will be used in the tim sort algorithm

    public:
        void addPost(Post* post) {
            postsVector.push_back(post);
            if(post->getLikes() >= maxLikedPost->getLikes()){
                maxLikedPost = post;
            }
            if(post->getDislikes() >= maxDislikedPost->getDislikes()){
                maxDislikedPost = post;
            }


        }

        void displayPostsLikes(int total){
            vector<Post*> msV = postsVector;
            vector<Post*> qsV = postsVector;
            vector<Post*> tsV = postsVector;

            auto start = high_resolution_clock::now();

            msV = mergeSort(msV, 0, postsVectorSize - 1, "likes");
            cout << "Merge Sort: " << endl;
            displayP(total, msV);

            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " microseconds" << endl;

            start = high_resolution_clock::now();

            qsV = quickSort(qsV, 0, postsVectorSize - 1, "likes");
            cout << "\n Quick Sort: " << endl;
            displayP(total, qsV);

            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " microseconds" << endl;


            start = high_resolution_clock::now();

            tsV = timSort(tsV, postsVectorSize, "likes");
            cout << "\n Tim Sort: " << endl;
            displayP(total, tsV);

            stop = high_resolution_clock::now();

            duration = duration_cast<microseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " microseconds" << endl;

        }

        void displayPostsDislikes(int total){
            vector<Post*> msV = postsVector;
            vector<Post*> qsV = postsVector;
            vector<Post*> tsV = postsVector;

            auto start = high_resolution_clock::now();

            msV = mergeSort(msV, 0, postsVectorSize - 1, "dislikes");
            cout << "Merge Sort: " << endl;
            displayP(total, msV);

            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " microseconds" << endl;

            start = high_resolution_clock::now();

            qsV = quickSort(qsV, 0, postsVectorSize - 1, "dislikes");
            cout << "\n Quick Sort: " << endl;
            displayP(total, qsV);

            stop = high_resolution_clock::now();
            duration = duration_cast<microseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " microseconds" << endl;

            start = high_resolution_clock::now();

            tsV = timSort(tsV, postsVectorSize, "dislikes");
            cout << "\n Tim Sort: " << endl;
            displayP(total, tsV);

            stop = high_resolution_clock::now();

            duration = duration_cast<microseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " microseconds" << endl;
        }


        void displayP(int total, vector<Post*> v){
            for(int i = 0; i < total; i++){
                //Post* post = postsVector[i];
                cout << "ID: " << v[postsVectorSize-1-i]->getId() << " Likes: " << v[postsVectorSize-1-i]->getLikes() << " Dislikes: " << v[postsVectorSize-1-i]->getDislikes() << endl;
            }
        }

        void displayMaxLikedPost(){
            cout << "Most Liked Post: " << endl;
            cout << "\nID: " << maxLikedPost->getId() << " Likes: " << maxLikedPost->getLikes() << " Dislikes: " << maxLikedPost->getDislikes() <<  "\n" << endl;
        }
        void displayMaxDislikedPost(){
            cout << "Most Disliked Post: " << endl;
            cout << "\nID: " << maxDislikedPost->getId() << " Likes: " << maxDislikedPost->getLikes() << " Dislikes: " << maxDislikedPost->getDislikes() << "\n" << endl;
        }
        vector<Post*> quickSort(vector<Post*>& v, int low, int high, string condition){
            if(low < high){
                int pivot = partition(v, low, high, condition);
                quickSort(v, low, pivot - 1, condition);
                quickSort(v, pivot + 1, high, condition);
            }
            return v;
        }

        int partition(vector<Post*>& v, int low, int high, string condition){
            int pivot;
            // setting pivot to be the start value
            if(condition == "likes")
                pivot = v[low]->getLikes();
            else if(condition == "dislikes")
                pivot = v[low]->getDislikes();
            
            int up = low;
            int down = high;

            while(up < down){ // while up and down haven't crossed each other
                for(int j = up; j < high; j++){
                    if(condition == "likes"){
                        if(v[up]->getLikes() > pivot){
                            break;
                        }
                    }
                    else if(condition == "dislikes"){
                        if(v[up]->getDislikes() > pivot){
                            break;
                        }
                    }
                  
                    up++;
                }
                for(int j = high; j > low; j--){
                    if(condition == "likes"){
                        if(v[down]->getLikes() < pivot){
                            break;
                        }
                    }
                    else if(condition == "dislikes"){
                        if(v[down]->getDislikes() < pivot)
                            break;
                    }

                    down--;
                }
                if(up < down) // when up and down cross each other swap its positions and restart the loop
                    swap(v[up], v[down]);
            }
            // after the loop has ended switch the pivot with down
            swap(v[low], v[down]);
            return down;
        }
        vector<Post*> mergeSort(vector<Post*>& v, int left, int right, string condition){

            if(left < right){
                int mid = left + (right - left) / 2;
                mergeSort(v, left, mid, condition);
                mergeSort(v, mid + 1, right, condition);

                merge(v, left, mid, right, condition);
            }
            return v;
        }

        // merge two sub vectors from posts
        void merge(vector<Post*>& v, int left, int mid, int right, string condition){
            int n1 = mid - left + 1; 
            int n2 = right - mid;
            vector<Post*> leftVector(n1), rightVector(n2); // declaring the vectors that will hold the split values that will be merged

            // storing the appropriate values in the left and right vectors
            for(int i = 0; i < n1; i++){
                leftVector[i] = v[left + i];
            }
            for(int j = 0; j < n2; j++){
                rightVector[j] = v[mid + 1 + j];
            }

            // merge the vectors into the main posts vector
            int i, j, k;
            i = 0;
            j = 0;
            k = left;

            while(i < n1 && j < n2){
                if(condition == "likes"){
                    if(leftVector[i]->getLikes() <= rightVector[j]->getLikes()){
                    v[k] = leftVector[i];
                    i++;
                    }
                    else{
                    v[k] = rightVector[j];
                    j++;
                    }
                }
                else if(condition == "dislikes"){
                    if(leftVector[i]->getDislikes() <= rightVector[j]->getDislikes()){
                    v[k] = leftVector[i];
                    i++;
                    }
                    else{
                    v[k] = rightVector[j];
                    j++;
                    }
                }
            
                k++;
            }

            // when we run out of elements in either X or Y append the remaining elements
            while(i < n1){
                v[k] = leftVector[i];
                i++; 
                k++;
            }
            while(j < n2){
                v[k] = rightVector[j];
                j++;
                k++;
            }
        }

        void insertionSort(vector<Post*>& v, int left, int right, string condition){
            for(int i = left + 1; i <= right; i++){
                Post* temp = v[i];
                int j = i - 1;
                if(condition == "likes"){
                    while(j >= left && v[j]->getLikes() > temp->getLikes()){
                    v[j+1] = v[j];
                    j--;
                    }
                }
                else if(condition == "dislikes"){
                    while(j >= left && v[j]->getDislikes() > temp->getDislikes()){
                    v[j+1] = v[j];
                    j--;
                    }
                }
                
                v[j+1] = temp;
            }
        }

        vector<Post*> timSort(vector<Post*> v, int n, string condition){
            for(int i = 0; i < n; i+=run){
                insertionSort(v, i, min((i + run-1), (n-1)), condition);
            }

            for(int size = run; size < n; size = 2 * size){
                for(int left = 0; left < n; left += 2 * size){
                    int mid = left + size - 1;
                    int right = min((left + 2*size - 1), (n-1));

                    if(mid < right)
                        merge(v, left, mid, right, condition);
                }
            }

            return v;
        }
  

};