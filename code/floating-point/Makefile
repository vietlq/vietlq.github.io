.PHONY: test test_java test_cpp

test: test_java test_cpp

test_cpp:
	g++ -std=c++11 -Wall -pedantic -Werror -o nearly-equal.exe -I googletest/googletest/include googletest/googlemock/gtest/libgtest.a googletest/googlemock/gtest/libgtest_main.a nearly-equal.cpp
	./nearly-equal.exe

test_java:
	javac -cp .:junit-4.12.jar NearlyEqualsTest.java
	java -cp .:junit-4.12.jar:hamcrest-core-1.3.jar org.junit.runner.JUnitCore NearlyEqualsTest
