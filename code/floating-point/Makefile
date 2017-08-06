.PHONY: all cpp java test test_java test_cpp
.PHONY: build_java build_cpp

all: cpp java

test: test_java test_cpp

cpp: build_cpp test_cpp

java: build_java test_java

build_cpp:
	g++ -std=c++11 -Wall -pedantic -Werror -o nearly-equal.exe -I googletest/googletest/include googletest/googlemock/gtest/libgtest.a googletest/googlemock/gtest/libgtest_main.a nearly-equal.cpp

test_cpp:
	./nearly-equal.exe

build_java:
	javac -cp .:junit-4.12.jar NearlyEqualsTest.java

test_java:
	java -cp .:junit-4.12.jar:hamcrest-core-1.3.jar org.junit.runner.JUnitCore NearlyEqualsTest
