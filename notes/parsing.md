# Parsing ~ Chp 3:

### NOTES:

* Parsing—transmogrifying a sequence of tokens into one of those syntax trees.

* In order to have uniformity in evaluating a parsed tree, **precedence** and **associativity** is introduced:
  * Precedence determines which operator is evaluated first in an expression containing a mixture of different operators. Precedence rules tell us that we evaluate the '/' before the '-' in the above example. Operators with higher precedence are evaluated before operators with lower precedence. Equivalently, higher precedence operators are said to “bind tighter”.

  * Associativity determines which operator is evaluated first in a series of the same operator. When an operator is left-associative (think “left-to-right”), operators on the left evaluate before those on the right. Since - is left-associative, this expression.

* There is a whole pack of parsing techniques whose names are mostly combinations of “L” and “R”—LL(k), LR(1), LALR—along with more exotic beasts like parser combinators, Earley parsers, the shunting yard algorithm, and packrat parsing. For our first interpreter, one technique is more than sufficient: recursive descent.

* Recursive descent is considered a top-down parser because it starts from the top or outermost grammar rule (here expression) and works its way down into the nested subexpressions before finally reaching the leaves of the syntax tree. This is in contrast with bottom-up parsers like LR that start with primary expressions and compose them into larger and larger chunks of syntax.

* The body of the rule translates to code roughly like:

  * Terminal:	Code to match and consume a token

  * Nonterminal:	Call to that rule’s function
  * |:	if or switch statement
  * Astrick or +:	while or for loop
  * ?:	if statement

* Syntax Errors:
  * A parser has 2 jobs:
    * Given a valid sequence of tokens, produce a corresponding syntax tree.

    * Given an invalid sequence of tokens, detect any errors and tell the user about their mistakes.

  * The parser must:
    * Detect and report the error. 
    * Avoid crashing or hanging.
    * Be fast. 
    * Report as many distinct errors as there are
    * Minimize cascaded errors. (We want to report as many separate errors as we can, but we don’t want to report ones that are merely side effects of an earlier one.)

  * As soon as the parser detects an error, it enters panic mode. It knows at least one token doesn’t make sense given its current state in the middle of some stack of grammar productions.

  * Before it can get back to parsing, it needs to get its state and the sequence of forthcoming tokens aligned such that the next token does match the rule being parsed. This process is called synchronization.

  * With recursive descent, the parser’s state—which rules it is in the middle of recognizing—is not stored explicitly in fields.Each rule in the middle of being parsed is a call frame on the stack. In order to reset that state, we need to clear out those call frames.

* As the parser descends through the parsing methods for each grammar rule, it eventually hits primary(). If none of the cases in there match, it means we are sitting on a token that can’t start an expression. We need to handle that error too.<br>
<br>
{Primary→ NUMBER | STRING | "true" | "false" | "nil"
               | "(" expression ")" ;}

* With that, all that remains in the parser is to define an initial method to kick it off. When a syntax error does occur, this method returns null. That’s OK. The parser promises not to crash or hang on invalid syntax, but it doesn’t promise to return a usable syntax tree if an error is found. As soon as the parser reports an error, the required function(or rule) is called, and subsequent phases are skipped.         
