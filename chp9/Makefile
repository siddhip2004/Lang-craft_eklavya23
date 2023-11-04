CXX      := g++
CXXFLAGS := -ggdb -std=c++17
CPPFLAGS := -MMD

COMPILE  := $(CXX) $(CXXFLAGS) $(CPPFLAGS)

SRCS     := AstPrinterDriver.cpp GenerateAst.cpp cypy.cpp
DEPS     := $(SRCS:.cpp=.d)


cypy: Expr.h Stmt.h cypy.o
	@$(COMPILE) cypy.o -o $@


ast_printer: Expr.h AstPrinterDriver.o
	@$(COMPILE) AstPrinterDriver.o -o $@


generate_ast: GenerateAst.o
	@$(COMPILE) $< -o $@


Expr.h Stmt.h: generate_ast
	@./generate_ast .


.PHONY: clean
clean:
	rm -f *.d *.o ast_printer generate_ast cypy


-include $(DEPS)

define make_test
.PHONY: $(1)
$(1):
	@make cypy >/dev/null
	@echo "testing cypy with $(1).cypy ..."
	@./cypy tests/$(1).cypy | diff -u --color tests/$(1).cypy.expected -;
endef


TESTS = \
test-bool\
test-for\
test-if \
test-oper\
test-printing\
test-string\
test-variable\
test-while\

$(foreach test, $(TESTS), $(eval $(call make_test,$(test))))


.PHONY: test-all
test-all:
	@for test in $(TESTS); do \
		make -s $$test; \
	done
