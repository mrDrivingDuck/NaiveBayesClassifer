#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;

/*
 * @Author      : Mr Dk.
 * @Finished    : 2018.6.18 
 * @Copyright   : Jingtang Zhang
 * @Description : Implementation of Naive Bayes Classifier
 * 
 * @Parameter discription
 * 
 *      @Param of data set
 *          tag attr1 attr2 attr3 ... attrn
 *      @Param of Constructor
 *          string train_dir : Directory of training set
 *          string test_dir  : Directory of testing set
 *          int argv_num     : Number of attributes in a line
 */

class NaiveBayesClassifier {
    private:
        /*    Inner param    */
        int argv_num;
        string train_dir;
        string test_dir;
        /*    Data structure of training set    */
        vector <vector <int> > Attributes;
        vector <int> Tag;
        set <int> AllTags;
        /*    Param for output    */
        int result_true;
        int result_false;
        
        bool Predict(int real_tag, vector <int> &attr);
        double Attr_Probability(int attr_column, int value);
        double Attr_CondProbability(int attr_column, int value, int tag_cond);
        double Tag_Probability(int tag);
        void Print();

    public:
        /*    Constructor    */
        NaiveBayesClassifier(string train_dir, string test_dir, int argv_num) {
            this -> train_dir = train_dir;
            this -> test_dir = test_dir;
            this -> argv_num = argv_num;
            Attributes.resize(argv_num);
        }
        /*    Loading file of training set    */
        void Initialize();
        /*    Loading file of testing set    */
        void Execute();
};

void NaiveBayesClassifier::Print() {
    // cout << "TRUE : " << result_true << " FALSE : " << result_false << endl;
    cout << "Classification Precision : ";
    cout << ((double) result_true) / (result_true+result_false);
    cout << " (" << result_true << "/" << result_true+result_false << ")" << endl;
}

void NaiveBayesClassifier::Execute() {
    ifstream fin (test_dir.c_str());
    if (!fin.is_open()) {
        cout << "Error loading test file" << endl;
        exit(0);
    }

    result_true = 0;
    result_false = 0;

    while (!fin.eof()) {
        char line[1024];
        stringstream ss;
        int tag;
        vector <int> attr;
        attr.reserve(argv_num);

        fin.getline(line, 1024);
        if (0 == strcmp(line, "")) {
            break;
        }

        char *p = strtok(line, " ");
        ss << p;
        ss >> tag;
        ss.str("");
        ss.clear();

        for (int i = 0; i < argv_num; i++) {
            p = strtok(NULL, " ");
            int arg;
            ss << p;
            ss >> arg;
            ss.str("");
            ss.clear();

            attr.push_back(arg);
        }

        bool result = Predict(tag, attr);
        if (result == true) {
            result_true++;
        } else {
            result_false++;
        }
    }

    fin.close();
    Print();
}

/*
    P(attr[column] == value | tag_cond)
*/
double NaiveBayesClassifier::Attr_CondProbability(int attr_column, int value, int tag_cond) {
    double total_cond = 0;
    double attr_cond = 0;
    for (unsigned int i = 0; i < Tag.size(); i++) {
        if (Tag[i] == tag_cond) {
            total_cond++;
            if (Attributes[attr_column][i] == value) {
                attr_cond++;
            }
        }
    }

    return attr_cond / total_cond;
}

/*
    P(tag)
*/
double NaiveBayesClassifier::Tag_Probability(int tag) {
    int tag_count = count(Tag.begin(), Tag.end(), tag);
    return ((double) tag_count) / Tag.size();
}

/*
    P(attr[column] == value)
*/
double NaiveBayesClassifier::Attr_Probability(int attr_column, int value) {
    int attr_count = count(Attributes[attr_column].begin(), Attributes[attr_column].end(), value);
    return ((double) attr_count) / Attributes[attr_column].size();
}

/*
    P(tag | attr[0] attr[1] ... attr[n-1]) =
        P(attr[0] | tag) * P(attr[1] | tag) * ... * P(attr[n-1] | tag) * P(tag) /
        P(attr[0]) * P(attr[1]) * ... * P(attr[n-1])
*/
bool NaiveBayesClassifier::Predict(int real_tag, vector <int> &attr) {
    double max_prob = 0.0;
    int predict_tag;
    set <int>::iterator setIter;

    for (setIter = AllTags.begin(); setIter != AllTags.end(); setIter++) {
        int tag = *setIter;
        double prob = Tag_Probability(tag);
        for (unsigned int i = 0; i < attr.size(); i++) {
            prob *= Attr_CondProbability(i, attr[i], tag);
        }
        for (unsigned int i = 0; i < attr.size(); i++) {
            prob /= Attr_Probability(i, attr[i]);
        }

        if (prob >= max_prob) {
            max_prob = prob;
            predict_tag = tag;
        }
    }

    if (predict_tag == real_tag) {
        return true;
    } else {
        return false;
    }
}

void NaiveBayesClassifier::Initialize() {
    ifstream fin (train_dir.c_str());
    if (!fin.is_open()) {
        cout << "Error loading Train file" << endl;
        exit(0);
    }

    while (!fin.eof()) {
        char line[1024];
        stringstream ss;
        int tag;

        fin.getline(line, 1024);
        if (0 == strcmp(line, "")) {
            break;
        }

        char *p = strtok(line, " ");
        ss << p;
        ss >> tag;
        ss.str("");
        ss.clear();
        Tag.push_back(tag);
        AllTags.insert(tag);

        for (int i = 0; i < argv_num; i++) {
            p = strtok(NULL, " ");
            int arg;
            ss << p;
            ss >> arg;
            ss.str("");
            ss.clear();

            Attributes[i].push_back(arg);
        }
    }

    fin.close();
}
