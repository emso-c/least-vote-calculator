# least-vote-calculator
Proof of concept program for calculating least votes needed to make up a percentage.

Nobody probably asked for this highly specific program and most likely never will, but I did it nevertheless out of curiosity since I couldn't find anything close to this anywhere. Might not be the most efficient way to solve, but it still satisfies my needs.

## Functions
### int calculateLeastVotes(double target_percentage, double preferred_precision=0.1, bool more_info=false)
**target_percentage(double)**: The percentage you want to know about, between 0 and 100.

**preferred_precision(double)**: The approximity factor. The smaller the value, the smaller the error margin. Defaults to 0,1.
(Warning: You'll want some error margin to get more realistic results as most ratings you see on the internet shows approximate results. For instance 33.4% most likely means there's at least 3 votes, but if you set precision too small, like 0.1%, you'll get 335 as the answer which is more accurate but less realistic.)

**more_info(bool)**: Whether if you want to see more info or not. The info includes final percentage it found, error margin and vote distribution. Defaults to false.

**return(int)**: Number of votes needed.

### bool isClose(double value, double target_value,double precision=DBL_EPSILON)
**value(double)**: The first value you want to check.

**target_value(double)**: The second value you want to check.

**precision(double)**: The error margin you want to give. For instance setting it to 1 allows 1% error tolerance. Defaults to DBL_EPSILON, the smallest value of double.

**return(bool)**: Whether if the values are close according to precision.

## Usage
You can either modify main accoring to your needs or run the program on the command prompt.

Running the program on CMD, you can basically pass arguments to the function as follows:

    >> lvc 56.4 0.1 true
    Final percentage: 56.4103
    Error margin: 0.0102564
    Vote distribution: 22/17
    39
