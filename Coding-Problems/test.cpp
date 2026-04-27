/* 
*  Unit Testing.cpp
* 
*  Description: This file uses Google Test as unit testing for vector functionality.
*               These unit tests verify correct behavior for creating, adding, resizing, 
*               clearing, erasing, reserving, and accessing vector elements. This file 
*               contains both positive and negative unit tests to show success as well as
*               failure cases.
* 
*  Author: Carl LaLonde
* 
*  Date: 03/29/2026
* 
*/

#include "pch.h"
#include "gtest/gtest.h"
#include <vector>

using namespace std;

// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment {
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test {
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override { 
        // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override { 
        //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count) {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull) {
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate) {
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail) {
//    FAIL();
//}

TEST_F(CollectionTest, CanAddToEmptyVector) {
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    EXPECT_FALSE(collection->empty());
    // if not empty, what must the size be?
    EXPECT_EQ(collection->size(), 1);
}

TEST_F(CollectionTest, CanAddFiveValuesToVector) {
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);

    // is collection still empty?
    EXPECT_FALSE(collection->empty());
    // if not empty, what should size be?
    EXPECT_EQ(collection->size(), 5);
}

// Verify that max size is greater than or equal to size of 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqualTo) {
    // Test different max sizes
    vector<int> maxSizes = { 0, 1, 5, 10 };

    for (int size : maxSizes) {
        //reset collection for each loop iteration
        collection->clear();
        
        // is colleciton empty?
        ASSERT_TRUE(collection->empty());
        // if empty, size must be 0
        ASSERT_EQ(collection->size(), 0);

        if (size > 0) {
            add_entries(size);
        }

        // max_size should always be greater than or equal to current size
        EXPECT_GE(collection->max_size(), collection->size());

        // size should match test size
        EXPECT_EQ(collection->size(), size);
    }

}

// Verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqual) {
    // Test multiple sizes
    vector<int> capacitySizes = { 0, 1, 5, 10 };

    for (int size : capacitySizes) {
        // reset collection for each loop iteration
        collection->clear();

        // is colleciton empty?
        ASSERT_TRUE(collection->empty());
        // if empty, size must be 0
        ASSERT_EQ(collection->size(), 0);

        // add entries only when size is greater than 0
        if (size > 0) {
            add_entries(size);
        }

        // capacity should be greater than or equal to size
        EXPECT_GE(collection->capacity(), collection->size());

        // size shoule match test size
        EXPECT_EQ(collection->size(), size);
        
    }
}

// Verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesColleciton) {
    // start with 1 entry
    add_entries(1);

    // is colleciton empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 1
    ASSERT_EQ(collection->size(), 1);

    // increase size to 5
    collection->resize(5);

    // is collection size of 5
    EXPECT_EQ(collection->size(), 5);
    // collection should not be empty
    EXPECT_FALSE(collection->empty());
}

// Verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesColleciton) {
    // start with 10 entries
    add_entries(10);

    // is collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 10
    ASSERT_EQ(collection->size(), 10);

    // decreases size to 5
    collection->resize(5);

    // is collection size of 5
    EXPECT_EQ(collection->size(), 5);
    // collection should not be empty
    EXPECT_FALSE(collection->empty());
}

// Verify that resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeDecreasesCollectionToZero) {
    // start with 10 entries
    add_entries(10);

    // is collection empty?
    ASSERT_FALSE(collection->empty());
    //if not empty, size must be 10
    ASSERT_EQ(collection->size(), 10);

    // decrease size to 0
    collection->resize(0);

    // is collection empty?
    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);

}

// Verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection) {
    // start with 5 entries
    add_entries(5);

    // is collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 5
    ASSERT_EQ(collection->size(), 5);

    // clear the collection
    collection->clear();

    // is collection empty
    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// Verify erase(bein) erase(end) removes elements in range.
TEST_F(CollectionTest, EraseBeginEndErasesCollection) {
    // start with 10 entries
    add_entries(10);

    // is collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 10
    ASSERT_EQ(collection->size(), 10);

    // Erase all element in range of begin and end
    collection->erase(collection->begin(), collection->end());

    // verify the collection is not empty
    EXPECT_TRUE(collection->empty());
    EXPECT_EQ(collection->size(), 0);
}

// Verify reserve increases the capacity but not hte size of the collection
TEST_F(CollectionTest, ResearveIncreasesCapacityNotCollection) {
    // start with 10 entries
    add_entries(10);

    //is collection empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 10
    ASSERT_EQ(collection->size(), 10);

    // Stores the original size
    size_t originalSize = collection->size();

    // increase reserved space for 15 elements
    collection->reserve(15);

    // capacity should be 15
    EXPECT_GE(collection->capacity(), 15);
    // size of elements should not change
    EXPECT_EQ(collection->size(), originalSize);
}

// Verify the std::out_of_range exception is thrown when calling at() with an index out of bounds (negative test)
TEST_F(CollectionTest, OutOfRangeIsThrownWhenAtIsOutOfBounds) {
    //start with 10 entries
    add_entries(10);

    // is vector empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, size must be 10
    ASSERT_EQ(collection->size(), 10);

    // invalid index must throw an excpetion
    EXPECT_THROW(collection->at(20), out_of_range);
}

// verify values are not equal after using push_back to add them
TEST_F(CollectionTest, ValuesAreNotEqualAfterPushBack) {
    // is collection empty?
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    // add two new values
    collection->push_back(10);
    collection->push_back(20);

    // verify the size of collection is 2
    ASSERT_EQ(collection->size(), 2);
    // value of two elements should not be equal
    EXPECT_NE(collection->at(0), collection->at(1));
}

// Verifies that at() throws an out_of_range exception on an empty collection
TEST_F(CollectionTest, AtThrowsOutOfRangeExceptionOnEmptyCollection) {
    // is collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, size should be zero
    ASSERT_EQ(collection->size(), 0);

    // accessing an index on empty vector throws an out of range exception
    EXPECT_THROW(collection->at(10), out_of_range);
    
}