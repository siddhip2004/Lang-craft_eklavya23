# Scanning : Crafting Interpreters

### NOTES : 

* The core of the scanner is the loop.

* An interactive prompt also called a "REPL", Read a line, Evaluate it, Print the result, then Loop and do it all over again, is used to have an interactive converstaion with the interpreter.

* While scanning error handling is also necessary, to tell the user about any synatx error in a coorect place in code.

* Lexical analysis aims to scan through the list of characters and group them together into the smallest sequences that still represent something. Each of the blobs of characters is called a lexeme and the grouped data is called token.

* The raw source code as a simple string.The start and current fields are offsets that index into the string. The start field points to the first character in the lexeme being scanned, and current points at the character currently being considered. The line field tracks what source line current is on so we can produce tokens that know their location. 

* If a user throws a source file containing some characters that the language doesn't use, then those characters get silently discarded. And an error is reported.

* Scan != as a single lexeme. Likewise, <, >, and = can all be followed by = to create the other equality and comparison operators.

* Comments are lexemes, but they aren’t meaningful, and the parser doesn’t want to deal with them. So when we reach the end of the comment, we don’t call addToken(). When we loop back around to start the next lexeme, start gets reset and the comment’s lexeme disappears in a puff of smoke.

* To handle keywords, we see if the identifier’s lexeme is one of the reserved words. If so, we use a token type specific to that keyword. We define the set of reserved words in a map.

* After that identifier is scanned to check if it matches anything in the map.If so, that keywords's token type is used. Else it's a regular user defined identifier.


   

