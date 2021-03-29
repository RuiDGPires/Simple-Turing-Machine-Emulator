# Text evaluator's syntax in BNF

All whitespace that is not a terminal symbol is ignored
```bnf
<Configuration>         ::= <Expression>*

<Expression>            ::= [<Decorators>] (<Method-Call> | <State-Descriptor>)

<Decorators>            ::= "@" <Identifier> ("," <Identifier>)* ";"

<Method-Call>           ::= <Identifier> "(" (<Arguments> | "") ");"

<Arguments>             ::= <Identifier> | <One-Or-More-Argument>

<One-Or-More-Argument>  ::= <Identifier> | <Identifier> "," <One-Or-More-Argument>

<State-Descriptor>      ::= <Identifier> "->" (<Connection> | "{" <Connection>+ "}")

<Connection>            ::= [<Decorators>] <Identifier> ":" (<Rule> | "{" <Rule>+ "}")

<Rule>                  ::= [<Decorators>] <Character> "->" <Character> "," <Direction> ";" 

<Identifier>            ::=  <Quoted-Name> | <Name>

<Quoted-Name>           ::= '"' (<Letter> | <Number> | <Symbol>)+ '"'

<Name>                  ::= (<Letter> | <Number>)+

<Character>             ::= <Letter> | <Number> | <Quoted-Character>

<Quoted-Character>      ::= "'" (<Letter> | <Number> | <Symbol> | " ") "'"

<Direction>             ::= "r" | "R" | "l" | "L" | "s" | "S"

<Letter>                ::= "a" | ... | "z" | "A" | ... | "Z" 

<Number>                ::= "0" | ... | "9"

<Symbol>                ::=  "|" | " " | "!" | "#" | "$" | "%" | "&" | "(" | ")" | "*" | "+" | "," | "-" | "." | "/" | ":" | ";" | ">" | "=" | "<" | "?" | "@" | "[" | "\" | "]" | "^" | "_" | "`" | "{" | "}" | "~"
```

Comments are not described in the BNF above but are made using '#', commenting everything from there until the end of the line.
Anything that is commented is ignored