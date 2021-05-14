#include <iostream>
#include <float.h>
#include <math.h>

#define MAX_PERCENTAGE  100.0
#define MIN_PERCENTAGE  0.0

// Checks if two values are close enough with a % error tolerance (use DBL_EPSILON for little to none tolerance)
bool isClose(double value, double target_value,double precision=DBL_EPSILON){
    precision=(precision<0)?0:(precision>100)?100:precision;
    precision=(precision==DBL_EPSILON)?(DBL_EPSILON*MAX_PERCENTAGE/value):precision;  // work around
    return (value + (value*precision/MAX_PERCENTAGE) >= target_value && value - (value*precision/MAX_PERCENTAGE) <= target_value);
}

// Calculates at least how many votes would be needed to make up a percentage with a brute force approach
int calculateLeastVotes(double target_percentage, double preferred_precision=0.1, bool more_info=false){
    if(target_percentage<MIN_PERCENTAGE || target_percentage>MAX_PERCENTAGE)
        return -1;
    if(target_percentage == MIN_PERCENTAGE){
        if(more_info){
            std::cout << "No error margin" << std::endl;
            std::cout << "Votes (up/down): 0/1" << std::endl;
        }
        return 1;
    }
    int votes = 1;
    while(true){
        double initital_percentage = MAX_PERCENTAGE/votes;
        int final_vote;
        double final_percentage;
        bool found = false;
        int upvotes = 1;
        int downvotes = votes-1;
        for(double curr_percentage = initital_percentage; curr_percentage<=MAX_PERCENTAGE; curr_percentage+=initital_percentage){
            if(isClose(curr_percentage, target_percentage, DBL_EPSILON)){   // DO NOT use '==' for comparing double variable types, use approximation instead. 
                if(more_info){
                    std::cout << "No error margin" << std::endl;
                    std::cout << "Votes distribution: " << upvotes-1 << "/" << downvotes+1 << std::endl;
                }
                return votes;
            }
            if(isClose(curr_percentage, target_percentage, preferred_precision)){
                // try to get as close as possible by reducing the precision few more times (if possible)
                found = true;
                preferred_precision /= 10;
                final_vote = votes;
                final_percentage = curr_percentage;
            }
            else{
                if(found){
                    if(more_info){
                        std::cout << "Final percentage: " << final_percentage << std::endl;
                        std::cout << "Error margin: " << std::fabs(target_percentage-final_percentage) << std::endl;
                        std::cout << "Votes distribution: " << upvotes-1 << "/" << downvotes+1 << std::endl;
                    }
                    return final_vote;
                }
            }
            upvotes++;
            downvotes--;
        }
        votes++;
    }
}

int main(int argc, char **argv){

    if(argc==1){
        std::cout << "Error: At least one argument expected" << std::endl;
        return 1;
    }

    double percentage = std::stod(argv[1]);
    double precision = 0.1;
    bool info = false;
    if(argc==3)
        precision = std::stod(argv[2]);
    if(argc==4)
        info = (std::string(argv[3])=="true")?true:info;

    std::cout << calculateLeastVotes(percentage, precision, info) << std::endl;
    return 0;
}