# Chapter 2 : Representing Code 

* The code that we represent must be easy for the parser to produce and the interpreter to execute.

* If we are given an arithmetic expression, we can represent it as a tree. The subtrees denotes the numerical values and the nodes denote the operators. We then evaluate the given expression.

* A Context-Free Grammar takes a group of pieces it calls its **alphabet**. It then defines a set of **strings** which are in the grammar. Each string is a sequence of letters in the alphabet.

* Here, the individual letters are called **tokens** and the strings are called **expressions**. The grammar specifies expressions that are valid.

* When we generate a string from the rules of the grammar, we say that we **derive** the string. The string is called a **derivation** and the rules are called **productions**.

* The production consists of a title and a body which is a list of symbols of two types : 

    * **Terminal** : They are the letters of the grammar's alphabet and consists of literal values. Usually enclosed in quotes.

    * **Non-Terminal** : It points to another rule in the grammar. We may have a same name for different rules, in such case we can choose the rule according to the context. They are expressed as lowercase letters.

* We start with the first rule and choose its corresponding production randomly. Now we check for non-terminals and choose its production. We continue this process until we have only terminals left. Sometimes it may happen that the production we choose may point back to the same rule. This is called recursion which tells us that the language is context free. 

* **Enhancing Notation** : 

    * Productions separated by '|' instead of writing them on different lines. We'll also add parentheses '( )' to group the productions together.
    * We use the character '*' to denote zero or more repetitions of a symbol or group.
    * The '+' character is used to denote one or more occurence of a symbol or group.
    * The question mark '?' is used to indicate zero or one occurence of a symbol or group.

* **Grammar for expressions** : 

    * expression -> literal | unary | binary | grouping ;
    * literal -> NUMBER | STRING | "true" | "false" ;
    * grouping -> "(" expression ")" ;
    * unary -> ( "!" ) expression ;
    * binary -> expression ( operator ) expression ;
    * operator -> "==" | "!=" | "<" | ">" | ">=" | "<=" , etc. ;

NUMBER and STRING denote the literals depending on the language.

* **Syntax Tree** :

The grammar we defined is recursive and can be represented as a tree. We create a class for expressions and subclasses for productions. 

* **Expression Problem** :

1. We make a table in which types are listed in the rows and operations are listed in the columns. We then fill the table with the operations that are valid for each type. 
2. Java language assumes that all code in one row hangs together. Thus we can add new operations to the table without modifying the existing code. But we cannot add new types without modifying the existing code. This is called the Expression Problem.

* **Visitor Pattern** :

1. It adds a new operation to a family of classes without modifying the classes.
2. Each operation that can be performed on an expression is represented by a class. The class has a method for each type of expression. We can methods to the class using polymorphism. 
3. To perform an operation on expression, we call accept() method on the expression and pass the visitor object as an argument. The accept() method then calls the appropriate method on the visitor object.

* **A Pretty Printer** :

1. It will be very difficult to read the syntax tree. So we need to print the tree in a way that is easy to read. This process of producing a string of data in source language is called **pretty printing**. 
2. To show the nesting and grouping correctly, we define a new class. For subexpressions we use parentheses() helper method. 