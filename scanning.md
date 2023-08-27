# Chapter 1 : Scanning
* The scanner takes in user input as a series of characters and groups them into tokens.
* Every fundamental lexical unit that has a meaningful representation is called a lexeme. These lexemes are then converted to tokens.
* The token consists of useful data like keywords (reserved words), identifiers, numbers, strings, operators, etc.
* The scanner starts scanning from the first character of the code and regognizes individual characters into lexemes and when a particular lexeme is completed it is converted to a token.
* The Lexical Grammer is a set of rules that defines the lexemes of a language using regular expressions. If the rules are simple then it is considered as a regular language.
* Starting with Lexer Code, we will store the input as a string, define an empty list which will append tokens as scanner tranverses through the input line by line. After scanning is completed, it will add EOF (End of File) token to the list.
* If the user inputs any character that we have not defined in the lexer, it will report an error. But we continue scanning even if errors are present. Its better to report all errors at once rather than stopping at the first error.
* To determine the operators, we need to look at the second chracter as well. If both characters behaves like a valid operator, then we will consider them as a lexeme.
* Comments arent useful for this process and will ignore them. So we wont add them to the list of tokens.
* We also dont need whitespace(' '), newline('\n') for parsing, so will jump at the next following character.
* Characters enclosed between " " are considered as strings. When we create a string token, we will remove the quotes and store the string as a value.
* Number literals can be integers, floating point values, double, etc. We will check if decimal is included, if not it is an integer. If decimal is included and followed by one or more digits, then it is a floating point value. We use the same value of input in the token.
* To identify identifiers, we will check if the first character is an alphabet or an underscore. After reaching the end of the identifier, we will check if it is a keyword. If it is a keyword, we will add the keyword token to the list. If not, we will add the identifier token to the list.
 

