.PHONY: test

test:
	javac -cp .:junit-4.12.jar NearlyEqualsTest.java
	java -cp .:junit-4.12.jar:hamcrest-core-1.3.jar org.junit.runner.JUnitCore NearlyEqualsTest
