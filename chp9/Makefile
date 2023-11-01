CXX      := g++
CXXFLAGS := -ggdb -std=c++17
CPPFLAGS := -MMD

COMPILE  := $(CXX) $(CXXFLAGS) $(CPPFLAGS)

SRCS     := AstPrinterDriver.cpp GenerateAst.cpp siddhi.cpp
DEPS     := $(SRCS:.cpp=.d)


psiddhi: Expr.h Stmt.h siddhi.o
	@$(COMPILE) siddhi.o -o $@


ast_printer: Expr.h AstPrinterDriver.o
	@$(COMPILE) AstPrinterDriver.o -o $@


generate_ast: GenerateAst.o
	@$(COMPILE) $< -o $@


Expr.h Stmt.h: generate_ast
	@./generate_ast .


.PHONY: clean
clean:
	rm -f *.d *.o ast_printer generate_ast psiddhi


-include $(DEPS)

define make_test
.PHONY: $(1)
$(1):
	@make psiddhi >/dev/null
	@echo "testing psiddhi with $(1).siddhi ..."
	@./psiddhi tests/$(1).siddhi | diff -u --color tests/$(1).siddhi.expected -;
endef


TESTS = \
test-statements \
test-statements2 \
test-statements3 \
test-statements4 \
test-statements5 \
test-statements6 \
test-control-flow \
test-control-flow2 \
test-control-flow3 \
test-control-flow4 \
test-control-flow5 \
test-control-flow6 \

$(foreach test, $(TESTS), $(eval $(call make_test,$(test))))


.PHONY: test-all
test-all:
	@for test in $(TESTS); do \
		make -s $$test; \
	done