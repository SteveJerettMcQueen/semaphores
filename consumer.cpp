#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <semaphore.h>

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
    } 
    
}

int find_largest_distance(int d, int d2){
    if(d >= d2){
        return d;
    } else {
        return d2;
    } 
}

void *con_runner(void *arg){
    struct content_struct *arg_struct = (struct content_struct*) arg;

    std::ostringstream os;

    // Reads the content from the buffer and finds
    // the location of the letter in the alphabet
    for(int i = 0; i < arg_struct->buffer.size(); i++){
        
        sem_wait(&arg_struct->full);
        sem_wait(&arg_struct->sem);
        
        // Enter critical section on shared resource
        char letter = arg_struct->buffer.at(i);
        // Exit critical section on shared resource
        
        sem_post(&arg_struct->sem);
        sem_post(&arg_struct->empty);

        int location = arg_struct->location_map.find(letter)->second + 1;
        bool location_is_even = (location % 2 == 0);
        
        if(location_is_even){
            
            // Consumer message to build
            std::string con_msg, con_msg2;
            
            // Split vector into 2 ranges: left & right of the letter
            std::vector<char>::iterator lb = arg_struct->letters.begin();
            std::vector<char>::iterator le = arg_struct->letters.begin() + (location - 1);
            std::vector<char> left_range(lb, le);
            std::reverse(left_range.begin(), left_range.end());
            
            std::vector<char>::iterator rb = arg_struct->letters.begin() + location;
            std::vector<char>::iterator re = arg_struct->letters.end();
            std::vector<char> right_range(rb, re);
            
            char v1, v2;
            int dist_v1, dist_v2, lgst_dist;
            std::vector<char>::iterator it; // Iterator used for finding distance
            
            // Special Case for letters 'V', 'X', & 'Z'
            if(location == 22 || location == 24 || location == 26){
                
                v1 = find_nearest_vowel(left_range, arg_struct->vowels);
                it = find(left_range.begin(),left_range.end(), v1);
                dist_v1 = distance(left_range.begin(), it) + 1;
                
                // The next nearest vowel to the right will always be 'A' 
                // for letters in even a location after the last vowel 
                // in the alphabet 'U' 
                v2 = 'A';
                it = find(right_range.begin(),right_range.end(), v2);
                dist_v2 = distance(right_range.begin(), it) + 1;
                
            } else {
                
                v1 = find_nearest_vowel(left_range, arg_struct->vowels);
                it = find(left_range.begin(),left_range.end(), v1);
                dist_v1 = distance(left_range.begin(), it) + 1;
                
                v2 = find_nearest_vowel(right_range, arg_struct->vowels);
                it = find(right_range.begin(),right_range.end(), v2);
                dist_v2 = distance(right_range.begin(), it) + 1;
                
            }
    
            // Build messages
            con_msg = con_msg + v1 + letter + v2;
            con_msg2 = con_msg;
            
            if(dist_v1 >= dist_v2){
                con_msg2 = v1 + con_msg2 + v1;
            } else {
                con_msg2 = v2 + con_msg2 + v2;
            } 
            
            // Find the largest distance from the letter
            lgst_dist = find_largest_distance(dist_v1, dist_v2);
            
            // Record information
            os << "Consumer[" << i <<"]: " << letter << std::endl;
            os << "S: " << con_msg << ";" << std::endl;
            os << "T: " << con_msg2 << ";" << std::endl;
            os << "v1-> (" << v1 << "); c-> (" << letter << "); v2-> (" << v2 << ");" <<std::endl;
            os << "Dv1 = " << dist_v1 <<  " : Dv2 = " << dist_v2 << ";" << std::endl;
            os << "Largest Distance = " << lgst_dist << ";" << std::endl;

        } else {
            
            os << "Consumer[" << i <<"]: " << letter << std::endl;
            
        }
        
            os << "------------------------------------------------" << std::endl;
        
    }

    // Writes and read status to shared variable
    pthread_mutex_lock(&arg_struct->mutex);
    arg_struct->status = os.str();
    std::cout<< arg_struct->status << std::endl;
    pthread_mutex_unlock(&arg_struct->mutex);

}
