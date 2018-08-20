# Naive Bayes Classifier

Author : Mr Dk.

Date : 2018.6.18, Nanjing, Jiangsu, China.

Description : Implementation of _Naive Bayes Classifier_ with _C/C++_.

---

#### Theory

* Based on : _Bayes' theorem_

  <img src="http://www.forkosh.com/mathtex.cgi? P(Y | X_1 X_2 X_3 ... X_n) = \frac{P (X_1 X_2 X_3 ... X_n | Y) P(Y)}{P (X_1 X_2 X_3 ... X_n)}">

* __Naive__ -- Assume all attributes are __independent__ in condition

* According to _Bayes' theorem_, we can have:

  <img src="http://www.forkosh.com/mathtex.cgi? P(Y | X_1 X_2 X_3 ... X_n) = \frac{P (X_1 | Y) P(X_2 | Y) P(X_3 | Y) ... P(X_n | Y) P(Y)}{P (X_1) P(X_2) P(X_3) ... P(X_n)}">

* Then, we can get all probabilities in the equation above

* Then, we can get _Probability_ of classes(Y) in different conditions($X_i$)

* Samples are classified into the class with maximum _Probability of Y_ 

---

#### Data Set

* MONK's Problem
* URL : http://archive.ics.uci.edu/ml/datasets/MONK%27s+Problems
* Format : TAG arg1 arg2 arg3 arg4 arg5 arg6 IDENTITY

---

#### How To Use

* include the header file _NaiveBayesClassifier.h_
* Instantiate an object of class _NaiveBayesClassifier_
* Constructor parameters:
  * __string train_dir__ : File of training set
  * __string test_dir__ : File of testing set
  * __int argv_num__ : Number of attributes in a line
* Call the function _Initialize()_ to load training sets
* Call the function _Execute()_ to load testing sets and start classification

---

#### Test Result

* __monk-1__ : Classification Precision : 0.712963 (308/432)
* __monk-2__ : Classification Precision : 0.615741 (266/432)
* __monk-3__ : Classification Precision : 0.972222 (420/432)

---

