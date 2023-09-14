#include <gtest/gtest.h>
#include "mymap.h"
#include "myrandom.h"

// netid: rshah268
// Copy and Clear Stress Test
TEST(mymap, Copy) {
    
    // Create two mymaps m1 and m2
    mymap<int, int> m1;
    mymap<int, int> m2;
    int n = 10000;
    srand(time(0));


    for(int  i = 0; i < n; i++) {

        // Generate two random numbers
        int key = rand()%100000;
        int val = rand()%100000;

        // Insert them in map1
        m1.put(key, val);

        // Insert different elements in map2
        if(i % 2) {
            m2.put(val, key);
        }
    }

    // At this point they must be unequal
    ASSERT_NE(m1.Size(), m2.Size());


    // Set map2 equals to map1
    m2 = m1;

    // Both should be the same size and contain the same elements
    ASSERT_EQ(m1.Size(), m2.Size());
    ASSERT_EQ(m1.toString(), m2.toString());

    // Clear map1
    m1.clear();

    // Now they are unequal again
    ASSERT_NE(m1.Size(), m2.Size());
    // Map1 must be empty
    ASSERT_EQ(m1.Size(), 0);
    m2.clear();
    
}

//Test for operator[] on already balanced tree.
// //netid: lsasu2
TEST(mymap, operatorBrackets){
    mymap<int, string> test;
    map<int, string> omap;
    int n= 10;
    int arr[] = {40, 25, 60, 18, 35, 80, 30, 38, 50, 70};

    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(rand()%40);
        test.put(arr[i], value);
        omap.emplace(arr[i], value);
    }
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

    //Value not in map
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[i*1000], "");
        ASSERT_EQ(test.Size(), n+i+1);
    }

    //Duplicate values
    for (int i = 0; i < n; i++) {
        string value = "MAX: " + to_string(rand()%40);
        test.put(arr[i], value);
        omap[arr[i]] = value;
    }
    for(int i=0; i<n;i++){
        ASSERT_EQ(test[arr[i]], omap[arr[i]]);
    }

    test.clear();
    omap.clear();
}


TEST(mymap, one) {
    mymap<int, int> map;
    mymap<int, int> m2;
    int n = 10;
    int arr[] = {2, 1, 3, 6, 7, 8, 5 ,10 ,9 ,4};
    int order[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }
    EXPECT_EQ(map.Size(), 10);
    EXPECT_EQ(m2.Size(), 0);

    mymap<int, int> mapCopy = map;
    m2 = mapCopy;

    EXPECT_EQ(mapCopy.Size(), 10);
    EXPECT_EQ(map.Size(), 10);
    EXPECT_EQ(m2.Size(), 10);



    string sol = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\nkey: 4 value: 4\nkey: 5 value: 5\nkey: 6 value: 6\nkey: 7 value: 7\nkey: 8 value: 8\nkey: 9 value: 9\nkey: 10 value: 10\n";  


    EXPECT_EQ(sol, mapCopy.toString());
    // EXPECT_EQ(sol, m2.toString());

    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(map.contains(arr[i]));
    }

    EXPECT_EQ(map.Size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(map[arr[i]], arr[i]);
        EXPECT_EQ(map.Size(), 10);
    }
    int j = 0;
    for (auto key : mapCopy) {
        EXPECT_EQ(order[j++], key);
    }

    map.clear();
    m2.clear();
    mapCopy.clear();
    EXPECT_EQ(map.toString(), "");
    EXPECT_EQ(map.Size(), 0);

    EXPECT_EQ(mapCopy.Size(), 0);
}

// // netid: jcruz85
// // string value test
TEST(mymap, MSOne) {
    mymap<int, string> map;
    int arr[] = {1, 2, 3};
    string arr2[] = {"pedro", "martin", "steven"};

    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr2[i]);
    }
    EXPECT_EQ(map.Size(), 3);

    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(map.contains(arr[i]));
    }

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(map.get(arr[i]), arr2[i]);
        EXPECT_EQ(map.Size(), 3);
    }
    map[7];
    map.put(7, "alex");
    //    cout << map.toString();
    cout << "MY TEST PASSED" << endl;
}
// netid: jcruz85
// milestone one and two test
TEST(mymap, milestoneOne){
    mymap<int, int> testMap;
    map<int, int> mapSol;
    int n = 1000;
    for(int i=1; i <= n; i++ ) {
        int key = randomInteger(0, n);
        int val = randomInteger(0, n);
        testMap.put(key, val);
        mapSol[key] = val;
    }
    EXPECT_EQ(testMap.Size(), mapSol.size());

    stringstream solution("");
    for(auto pair : mapSol){
        solution << "key: " << pair.first;
        solution << " value: " << pair.second << endl;

        EXPECT_TRUE(testMap.contains(pair.first));
        EXPECT_EQ(testMap.get(pair.first), pair.second);
    }
//    cout << solution.str() << mapSol.size() << endl;
//    cout << testMap.toString() << testMap.Size() << endl;
    EXPECT_EQ(testMap.toString(), solution.str());
    cout << "MILESTONE ONE AND TWO PASSED" << endl;
}

// netid: jcruz85
// milestone three test
TEST(mymap, milestoneThree){
    mymap<int, int> myTest;
    map<int, int> otherTest;
    int seed = 10;
    for(int i=0; i<seed; i++){
        int key = randomInteger(0, seed);
        int val = randomInteger(0, seed);
        // cout << key << " " << val << endl;
        myTest.put(key, val);
        otherTest[key] = val;
    }

    cout << myTest.toString();

    // ASSERT_EQ(myTest.toString(), ss.str());

    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    int order[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }

    int i = 0;
    for (auto key : map) {
        EXPECT_EQ(order[i++], key);
    }

    cout << "MILESTONE THREE PASSED" << endl;
}

// netid: jcruz85
// clear func test
TEST(mymap, testClear){
    mymap<int, int> testMap;
    int n = 1000;
    for(int i=0; i<n; i++){
        int key = randomInteger(0, n);
        int val = randomInteger(0, n);

        testMap.put(key, val);
        EXPECT_NE(testMap.Size(), 0);
    }
    testMap.clear();
    ASSERT_EQ(testMap.Size(), 0);
    // Test valgrind as well
    cout << "CLEAR FUNCTION PASSED" << endl;
}

// netid: jcruz85
// operator equals test
TEST(mymap, testOperatorEquals){
    mymap<int, int> mapOrig;
    mymap<int, int> mapCopy;
    int n = 1000;
    for(int i=0; i<n; i++){
        int key = randomInteger(0, n);
        int val = randomInteger(0, n);
        mapOrig.put(key, val);
    }

    mapCopy = mapOrig;
    ASSERT_EQ(mapOrig.Size(), mapCopy.Size());
    ASSERT_EQ(mapOrig.toString(), mapCopy.toString());
    cout << "OPERATOR EQUALS PASSED" << endl;
}

// netid: jcruz85
// copy constructor test
TEST(mymap, testCopy){
    mymap<int, int> mapOrig;
    int n = 1000;
    for(int i=0; i<n; i++){
        int key = randomInteger(0, n);
        int val = randomInteger(0, n);
        mapOrig.put(key, val);
    }

    mymap<int, int> mapCopy = mapOrig;
    ASSERT_EQ(mapOrig.Size(), mapCopy.Size());
    ASSERT_EQ(mapOrig.toString(), mapCopy.toString());
    cout << "COPY CONSTRUCTOR PASSED" << endl;
}

//tkoope2
//Copy Constructor
TEST(copyConstructor, IIConCopy) {
 mymap<int, int> m;
 map<int, int> correct;
 vector<int> keys;
 int key;
 int val;
 int arrSize = 15;
 int high = 500, low = 0;
 int modOp = (high - (low + 1)) + low;


 //Populate
 for (int i = 0; i < arrSize; i++) {
  key = rand() % modOp;
  val = rand() % modOp;

  keys.push_back(key);

  m.put(key, val);
  correct[key] = val;
 }

 EXPECT_EQ(m.Size(), correct.size()) << "mymap != map\n";
 
 mymap<int, int> m2 = m;
 EXPECT_EQ(m.toString(), m2.toString()) << "Copy operator formating off\n";
 EXPECT_EQ(m2.Size(), correct.size()) << "M2's size does not match correct's\n";

 //Both have the same return value on keys
 int compA;
 int compB;
 for (auto& k : keys) {
  compA = m2[k];
  compB = correct[k];
  EXPECT_EQ(compA, compB) << compA << " != " << compB << "\t Incorrect Copy Constructor\n";
 }
}

//tkoope2
//Copy Operator test <int, int>
TEST(Operator, IICopyP) {
 mymap<int, int> m;
 mymap<int, int> m2;

 //Populate 1 and 2
 int key, value, high, low, modOp;
 int arrSize = rand() % 100;

 string mOriginal, m2Original;

 //Populate m
 high = 500;
 low = 1;
 modOp = (high - (low + 1)) + low;
 for (int i = 0; i < arrSize; i++) {
  key = rand() % modOp;
  value = rand() % modOp;
  m.put(key, value);
 }

 //Populate m2
 high = 1000; 
 low = 500;
 modOp = (high - (low + 1)) + low;
 for (int i = 0; i < arrSize; i++) {
  key = rand() % modOp;
  value = rand() % modOp;
  m2.put(key, value);
 }

 m = m2;

 EXPECT_EQ(m.Size(), m2.Size()) << "IIEquals; size difference\n";
 EXPECT_NE(mOriginal, m.toString()) << "m should not still equal original\n";
 EXPECT_EQ(m2.toString(), m.toString()) << "toString() !=\n" << "M:\n" << m.toString() << "\nM2:\n" << m2.toString() << endl;;
}

// milestone 1 tests 
// ssulta24
// default constructor Test and size Test
TEST(mymap, defaultConstructor) {

    // create a mymap
    mymap<int, int> m; 

    // check if the size is 0
    EXPECT_EQ(m.Size(), 0);

}

// ssulta24
// put Test and size Test
TEST(mymap, put) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.Size(), 3);

}

// ssulta24
// get Test
TEST(mymap, get) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.get(1), 1);
    EXPECT_EQ(m.get(2), 2);
    EXPECT_EQ(m.get(3), 3);
    EXPECT_EQ(m.get(4), 0);

}

// ssulta24
// contains Test
TEST(mymap, containsKey) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.contains(1), true);
    EXPECT_EQ(m.contains(2), true);
    EXPECT_EQ(m.contains(3), true);
    EXPECT_EQ(m.contains(4), false);

}

// ssulta24
// toString Test
TEST(mymap, tostr) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {3, 2, 1};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    string sol = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\n";
    EXPECT_EQ(sol, m.toString());

}

// ssulta24
// operator[] Test
TEST(mymap, operator) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m[1], 1);
    EXPECT_EQ(m[2], 2);
    EXPECT_EQ(m[3], 3);
    EXPECT_EQ(m[4], 0);

}

// ssulta24
// stress test combining all the tests above 
TEST(mymap, stressTest) {

    // create a mymap
    mymap<int, int> m; 

    vector< int > arr;

    for (int i = 0; i < 10000; i++) {
        int num = randomInteger(0, 10000);
        // append num to arr 
        arr.push_back(num);
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m[i], arr[i]);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.contains(i), true);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.get(i), arr[i]);
    }

    EXPECT_EQ(m.Size(), 10000);
}
// netid: msiddi73
// Testing Put with random int key (Testing Size and toString)
TEST(Put, randomIntInt){

    map<int, int> m;
    mymap <int, int> mymap;
    stringstream s;

    int randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;
    
    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){
                
            randomKey = randomInteger(0, 100);
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();
        
    }

}

// netid: msiddi73
// Testing put with random char key (Testing Size and toString)
TEST(Put, randomCharInt){

    map<char, int> m;
    mymap <char, int> mymap;
    stringstream s;

    char randomKey = 0;
    int randomValue = 0;
    int randomSize = 0;
    string test;
    

    for (int i = 0; i < 35; i++){

        test = "";
        s.str("");

        randomSize = randomInteger(1, 50);

        for (int p = 0; p < randomSize; p++){
                
            randomKey = randomInteger(65, 90); // get uppercase characthers
            randomValue = randomInteger(0, 100);

            m[randomKey] = randomValue;
            mymap.put(randomKey, randomValue);

        }

        for (auto const& x : m){
            s << "key: " << x.first << " value: " << x.second << "\n";
        }

        test = mymap.toString();

        ASSERT_EQ(mymap.Size(), m.size());
        ASSERT_EQ(test, s.str());

        mymap.clear();
        m.clear();
        
    }

}