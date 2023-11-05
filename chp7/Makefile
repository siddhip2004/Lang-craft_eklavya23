CXX      := g++
CXXFLAGS := -ggdb -std=c++17
CPPFLAGS := -MMD

COMPILE  := $(CXX) $(CXXFLAGS) $(CPPFLAGS)

SRCS     := AstPrinterDriver.cpp GenerateAst.cpp siddhi.cpp
DEPS     := $(SRCS:.cpp=.d)


psiddhi: siddhi.o
	@$(COMPILE) $< -o $@


ast_printer: Expr.h AstPrinterDriver.o
	@$(COMPILE) AstPrinterDriver.o -o $@


generate_ast: GenerateAst.o
	@$(COMPILE) $< -o $@


Expr.h: generate_ast
	@./generate_ast .


.PHONY: clean
clean:
	rm -f *.d *.o ast_printer generate_ast psiddhi


-include $(DEPS)


.PHONY: test-expressions
test-expressions:
	@make psiddhi >/dev/null
	@echo "testing psiddhi with test-expressions.siddhi ..."
	@./psiddhi tests/test-expressions.siddhi 2>&1 | diff -u --color tests/test-expressions.siddhi.expected -;


.PHONY: test-expressions2
test-expressions2:
	@make psiddhi >/dev/null
	@echo "testing psiddhi with test-expressions2.siddhi ..."
	@./psiddhi tests/test-expressions2.siddhi | diff -u --color tests/test-expressions2.siddhi.expected -;

