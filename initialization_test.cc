
// Megan Goodland, University of Toronto
// February 2019

// Tests for the initialization module, which performs:
// Uniform initialization of the simulation of ants walking on a table, subdivided into squares. 
// >>> Want to test this function with 5 cases. Small tables, making sure the ants get distributed uniformly.

#include "initialization.h"
#include <iostream>
#include <fstream>
#define BOOST_TEXT_DYN_LINK
#define BOOST_TEST_MODULE initialization_test
#include <boost/test/included/unit_test.hpp>


// Internal function that compares two rarrays, returns 1 if they are the same, 0 if they are different
int compare_rarrays(rarray<int,2>& a, rarray<int,2>& b){
    int length = a.extent(0); // input arrays are of the same size and square
    int test_result = 1; // 1 means pass, 0 means fail
    for (int i=0; i<length; i++) {
        for (int j=0; j<length; j++){
            if (a[i][j] == b[i][j]){
                test_result = 1;}
            else {
                test_result = 0;
                goto end_of_test;}
        }
    }
    goto end_of_test;
    end_of_test: return test_result;
}


// TEST CASE 1: Testing if function can make an even distribution on smallest matrix, outputs test results for each element
BOOST_AUTO_TEST_CASE(even_distribution){
    int length = 2;
    rarray<int,2> function_test(length,length);
    int n = 400; // number we want to distribute
    int f = n/(length*length); // f is the number that should appear in each square
    initialize_uniform(function_test, n); // run function with test array and n
    // check if the arrays are the same and inform of where a mismatch occurs
    for (int i=0; i<length; i++) {
        for (int j=0; j<length; j++){
            BOOST_CHECK_MESSAGE(function_test[i][j] == f, "value at " << i << " " << j);
        }
    }
}


// TEST CASE 2: Testing if function can make an even distribution of a larger number on a larger matrix
BOOST_AUTO_TEST_CASE(larger_numbers){
    // create two 5x5 rarrays, one to put in the function and another to compare with it
    int length = 5;
    rarray<int,2> function_test(length,length);
    rarray<int,2> compare(length,length); 
    int n = 10000; // number we want to distribute is n
    int f = n/(length*length); // f is the number that should appear in each square
    compare.fill(f);
    initialize_uniform(function_test, n); // run function with test array and n
    // check if the arrays are the same
    end_of_test: BOOST_CHECK_MESSAGE(compare_rarrays(function_test, compare) == 1, "function initialize_uniform with larger numbers");
}


// TEST CASE 3: Testing if function places a remainder of 1 in the final i,j position as it is supposed to
BOOST_AUTO_TEST_CASE(uneven_division_R1){
    // create two 5x5 rarrays, one to put in the function and another to compare with it
    int length = 5;
    rarray<int,2> function_test(length,length);
    rarray<int,2> compare(length,length); 
    int n = 10001; // number we want to distribute, should have a remainder of 1 when divided by lengthxlength
    int f = n/(length*length); // the number that should appear in each square, other than the one in the last position
    int ff = f+1; // the number that should appear in the final position
    compare.fill(f);
    compare[length-1][length-1] = ff; 
    // run function with test array and n
    initialize_uniform(function_test, n);
    // check if the arrays are the same
    end_of_test: BOOST_CHECK_MESSAGE(compare_rarrays(function_test, compare) == 1, "function initialize_uniform with an uneven division, remainder 1");
}


// TEST CASE 4: Testing if function places a remainder of 3 in even positions across the matrix
BOOST_AUTO_TEST_CASE(uneven_division_R3){
    // create two 5x5 rarrays, one to put in the function and another to compare with it
    int length = 5;
    rarray<int,2> function_test(length,length);
    rarray<int,2> compare(length,length); 
    int n = 10003; // number we want to distribute, should have a remainder of 3 when divided by lengthxlength
    int f = n/(length*length); // the number that should appear in each square, other than the positions with remainder
    int ff = f+1; // the number that should appear in the final 3 positions
    compare.fill(f);
    compare[1][3] = ff; compare[3][1] = ff; compare[4][4] = ff; 
    initialize_uniform(function_test, n); // run function with test array and n
    // check if the arrays are the same
    end_of_test: BOOST_CHECK_MESSAGE(compare_rarrays(function_test, compare) == 1, "function initialize_uniform with an uneven division, remainder 3");
}


// TEST CASE 5: Testing if function places a remainder of 5 in even positions across the matrix
BOOST_AUTO_TEST_CASE(uneven_division_R5){
    // create two 3x3 rarrays, one to put in the function and another to compare with it
    int length = 3;
    rarray<int,2> function_test(length,length);
    rarray<int,2> compare(length,length); 
    int n = 113; // number we want to distribute, should have a remainder of 5 when divided by lengthxlength
    int f = n/(length*length); // the number that should appear in each square, other than the positions with remainder
    int ff = f+1; // the number that should appear in the final 3 positions
    compare.fill(f);
    compare[0][1] = ff; compare[1][0] = ff; compare[1][2] = ff; compare[2][1] = ff; compare[2][2] = ff; 
    initialize_uniform(function_test, n); // run function with test array and n
    // Check if the arrays are the same
    BOOST_CHECK_MESSAGE(compare_rarrays(function_test, compare) == 1, "function initialize_uniform with an uneven division, remainder 5");
}


