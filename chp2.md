# Chapter 2 ~ Representing Code

### NOTES :

* In order to evaluate an arithmetic node, you need to know the numeric values of its subtrees, so you have to evaluate those first. That means working your way from the leaves up to the root—a post-order traversal:

* In our scanner’s grammar, the alphabet consists of individual characters and the strings are the valid lexemes—roughly “words”. In the syntactic grammar we’re talking about now, we’re at a different level of granularity. Now each “letter” in the alphabet is an entire token and a “string” is a sequence of tokens—an entire expression.

* Strings are derived from the rules of grammar that is defined. Hence, strings are called **derivations** and rules are called as **productions** (since they produce strings).

* You may have multiple rules with the same name. When you reach a nonterminal with that name, you are allowed to pick any of the rules for it, whichever floats your boat.

* Grammar is written as:
    * Rule_name -> Strings

    * Instead of repeating the rule name each time we want to add another production for it, we’ll allow a series of productions separated by a pipe (|).

    example: bread → "toast" | "biscuits" | "English muffin" ;


    * Further, we’ll allow parentheses for grouping and then allow | within that to select one from a series of options within the middle of a production.

   example: protein → ( "scrambled" | "poached" | "fried" ) "eggs" ;

   * Using recursion to support repeated sequences of symbols has a certain appealing purity, but it’s kind of a chore to make a separate named sub-rule each time we want to loop. So, we also use a postfix  to allow the previous symbol or group to be repeated zero or more times.

   example: crispiness → "really" "really"* ;

   * A postfix + is similar, but requires the preceding production to appear at least once.

   example: crispiness → "really"+ ;

   * A postfix ? is for an optional production. The thing before it can appear zero or one time, but not more.

   example: breakfast → protein ( "with" breakfast "on the side" )? ;


* The interpreter needs to select a different chunk of code to handle each expression type. With tokens, we can simply switch on the TokenType. But we don’t have a “type” enum for the syntax tree.

* Add an abstract interpret() method on expression which each subclass would then implement to interpret itself.

* This works alright for tiny projects, but it scales poorly. Like I noted before, these tree classes span a few domains. At the very least, both the parser and interpreter will mess with them. And if we added instance methods to the expression classes for every one of those operations, that would smush a bunch of different domains together. That violates separation of concerns and leads to hard-to-maintain code.

* Expression Problem: 

    * To treat an expression, a table is made, where rows are types, and columns are operations. Each cell represents the unique piece of code to implement that operation on that type.

    * An object-oriented language like Java assumes that all of the code in one row naturally hangs together. This makes it easy to extend the table by adding new rows. But to add new columns is not possible. For that ML is used, to implement an operation for a number of different types, you define a single function.

    * But to add this new part is hard. Hence this is called expression probelm.

* The Visitor Pattern:
    
    * The Visitor pattern is really about approximating the functional style within an OOP language. It lets us add new columns to that table easily. We can define all of the behavior for a new operation on a set of types in one place, without having to touch the types themselves. It does this the same way we solve almost every problem in computer science: by adding a layer of indirection.
    
    * To perform an operation, we call its accept() method and pass in the visitor for the operation we want to execute. Here, the specific subclass’s overriding implementation of accept()—turns around and calls the appropriate visit method on the visitor and passes itself to it.

* A Pretty Printer:
    
    * This is opposite to making a tree data structure from the expression.
    
    * To implement this, we define a new class.That means we need visit methods for each of the expression types we have so far. 

    * Each string expression is explicitly parenthesized, and all of its subexpressions and tokens are contained in that Like: (+ 1 2)

