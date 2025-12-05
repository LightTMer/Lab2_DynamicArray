#include "pch.h"
#include "DynamicArray.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include <random>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;



namespace ArrayTests {

TEST_CLASS(DynamicArrayTests) {
public:

    TEST_METHOD(IntBasicOperations) {
        Array<int> a;

        for (int i = 0; i < 5; i++)
            a.insert(i * 10);

        Assert::AreEqual(5, a.size());
        Assert::AreEqual(20, a[2]);

        a.remove(1);
        Assert::AreEqual(4, a.size());
        Assert::AreEqual(20, a[1]);
    }

    TEST_METHOD(StringInsertAndRemove) {
        Array<std::string> a;

        a.insert("hello");
        a.insert("world");
        a.insert(1, "C++");

        Assert::AreEqual(3, a.size());
        Assert::AreEqual(std::string("hello"), a[0]);
        Assert::AreEqual(std::string("C++"), a[1]);
        Assert::AreEqual(std::string("world"), a[2]);

        a.remove(1);
        Assert::AreEqual(2, a.size());
        Assert::AreEqual(std::string("world"), a[1]);
    }

    TEST_METHOD(MoveSemanticsStringTest) {
        Array<std::string> a;

        for (int i = 0; i < 10; i++)
            a.insert("string_" + std::to_string(i));

        Assert::AreEqual(10, a.size());
        Assert::AreEqual(std::string("string_5"), a[5]);

        a.insert("NEW");
        Assert::AreEqual(11, a.size());
        Assert::AreEqual(std::string("NEW"), a[10]);

        Assert::AreEqual(std::string("string_0"), a[0]);
        Assert::AreEqual(std::string("string_9"), a[9]);
    }

    TEST_METHOD(IteratorWorksWithYourAPI) {
        Array<int> a;
        for (int i = 0; i < 7; ++i) a.insert(i + 1); 

        int expected = 1;
        for (auto it = a.iterator(); ; ) {
            Assert::AreEqual(expected, it.get());
          
            if (!it.hasNext()) break;
            it.next();
            ++expected;
        }
        
        Assert::AreEqual(7, expected);
    }


   
    TEST_METHOD(ReverseIteratorWorksWithYourAPI) {
        Array<int> a;
        for (int i = 0; i < 5; ++i) a.insert(i + 1); 

        int expected = 5;
        for (auto it = a.reverseIterator(); ; it.next()) {
            Assert::AreEqual(expected, it.get());
            if (!it.hasNext()) break;
            --expected;
        }
        --expected; 
        Assert::AreEqual(0, expected);
    }
	};
}