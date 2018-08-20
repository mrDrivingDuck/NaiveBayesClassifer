#include <iostream>
#include "NaiveBayesClassifier.h"
using namespace std;

/*

 * @Author      : Mr Dk.
 * @Date        : 2018.6.18
 * @Description : Test the function of NaiveBayesClassifier
 * 
 * @DataSet     : Monk's problem
 * @URL         : http://archive.ics.uci.edu/ml/datasets/MONK%27s+Problems
 * 
 */

int main()
{
    NaiveBayesClassifier nbc ("../test/monks-3.train", "../test/monks-3.test", 6);
    nbc.Initialize();
    nbc.Execute();

    return 0;
}