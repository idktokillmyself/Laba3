CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -O0 -g
COVERAGE_FLAGS = -O0 -g -fprofile-arcs -ftest-coverage

TARGET = lab3_oop
COVERAGE_TARGET = lab3_coverage
TEST_TARGET = lab3_test

SOURCES = src/AVLTree.cpp src/main_final.cpp
TEST_SOURCES = src/AVLTree.cpp src/test_coverage.cpp

RELEASE_OBJECTS = $(SOURCES:.cpp=.release.o)
DEBUG_OBJECTS = $(SOURCES:.cpp=.debug.o)
COVERAGE_OBJECTS = $(TEST_SOURCES:.cpp=.coverage.o)

all: release

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET).debug

coverage: CXXFLAGS += $(COVERAGE_FLAGS)
coverage: $(COVERAGE_TARGET)

test: coverage
	./$(COVERAGE_TARGET)

html-report: coverage
	./$(COVERAGE_TARGET)
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.filtered.info
	genhtml coverage.filtered.info --output-directory coverage_report
	@echo "HTML отчет создан: coverage_report/index.html"

$(TARGET): $(RELEASE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET).debug: $(DEBUG_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(COVERAGE_TARGET): $(COVERAGE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.release.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.debug.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.coverage.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o *.gcno *.gcda *.gcov coverage.info coverage.filtered.info
	rm -f $(TARGET) $(TARGET).debug $(COVERAGE_TARGET)
	rm -rf coverage_report html_coverage
	rm -f *.txt *.bin

run: release
	./$(TARGET)

.PHONY: all release debug coverage test html-report clean run
