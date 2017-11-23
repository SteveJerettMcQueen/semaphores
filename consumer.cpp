#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <math.h>
#include <pthread.h>

#include "consumer.hpp"
#include "util.hpp"

bool is_vowel_pred(char a, char b){
    return (a == b);
}

char find_nearest_vowel(std::vector<char> range, std::vector<char> vowels){
    auto result = find_first_of(range.begin(), range.end(), vowels.begin(), vowels.end(), is_vowel_pred);
    if (result != vowels.end()){
        int i = distance(range.begin(), result); 
        return range[i];
    } else if(result == vowels.end()){
        // // If the letter is greater than 'U' in the alphabet
        // // then the next vowel will always be 'A' because 'A'
        // // is the first vowel in the alphabet
        return 'A'; 
        
    }
    
}

int find_largest_distance(int d, int d2){
    if(d > d2){
        return d;
    } else if(d < d2){
        return d2;
    } else {
        return d;
    }
}

void *con_runner(void *arg){
    struct content_struct *arg_struct = (struct content_struct*) arg;

    // Consumer reads content from the buffer and finds
    // location of the letter in the alphabet
    char letter = arg_struct->buffer[0];
    int location = arg_struct->location_map.find(letter)->second + 1;
    bool location_is_even = (location % 2 == 0);
    
    if(location_is_even){
        
        // Consumer message to build
        std::string con_msg;
        
        // Iterator used for finding distance         
        std::vector<char>::iterator it;
        
        // Find closest vowel to left of the letter & distance
        std::vector<char>::iterator b = arg_struct->letters.begin();
        std::vector<char>::iterator e = arg_struct->letters.begin() + (location - 1);
        std::vector<char> left_range(b, e);
        std::reverse(left_range.begin(), left_range.end());
        char v1 = find_nearest_vowel(left_range, arg_struct->vowels);
        it = find(left_range.begin(),left_range.end(), v1);
        int dist_v1 = distance(left_range.begin(), it) + 1;
        
        // Find closest vowel to right of the letter
        std::vector<char>::iterator b2 = arg_struct->letters.begin() + location;
        std::vector<char>::iterator e2 = arg_struct->letters.end();
        std::vector<char> right_range(b2, e2);
        char v2 = find_nearest_vowel(right_range, arg_struct->vowels);
        it = find(right_range.begin(),right_range.end(), v2);
        int dist_v2 = distance(right_range.begin(), it) + 1;

        // Find the largest distance from the letter
        int largest_dist = find_largest_distance(dist_v1, dist_v2);

        // Build messages
        con_msg = con_msg + v1 + letter + v2;
        std::string s = con_msg;
        std::string t = s;
        
        if(dist_v1 > dist_v2){
            t = v1 + t + v1;
        } else if(dist_v1 < dist_v2){
            t = v2 + t + v2;
        } else {
            t = v1 + t + v1;
        }
        
        // Display information
        std::cout << "S: " << s << std::endl;
        std::cout << "T: " << t << std::endl;
        std::cout << "v1: " << v1 << " c: " << letter << " v2: " << v2 << std::endl;
        std::cout << "Dv1: " << dist_v1 <<  " Dv2: " << dist_v2 << std::endl;
        std::cout << "Largest Distance: " << largest_dist << std::endl;

    } else {
        
        std::cout << "Consumer: " << letter << " Location: " << location << std::endl;
        
    }
    
    pthread_exit(0);
}
