CXX      := g++
CXXFLAGS := -ggdb -std=c++17
CPPFLAGS := -MMD

COMPILE  := $(CXX) $(CXXFLAGS) $(CPPFLAGS)

SRCS     := siddhi.cpp
DEPS     := $(SRCS:.cpp=.d)


psiddhi: siddhi.o
	@$(COMPILE) $< -o $@


.PHONY: clean
clean:
	rm -f *.d *.o psiddhi


-include $(DEPS)


.PHONY: test-lexing
test-lexing:
	@make psiddhi >/dev/null
	@echo "testing psiddhi with test-lexing.siddhi ..."
	@./psiddhi tests/test-lexing.siddhi | diff -u --color tests/test-lexing.siddhi.expected -;


.PHONY: test-lexing2
test-lexing2:
	@make psiddhi >/dev/null
	@echo "testing psiddhi with test-lexing2.siddhi ..."
	@./psiddhi tests/test-lexing2.siddhi | diff -u --color tests/test-lexing2.siddhi.expected -;