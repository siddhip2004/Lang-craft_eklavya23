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


.PHONY: test-parsing
test-parsing:
	@make psiddhi >/dev/null
	@echo "testing psiddhi with test-parsing.siddhi ..."
	@./psiddhi tests/test-parsing.siddhi | diff -u --color tests/test-parsing.siddhi.expected -;


