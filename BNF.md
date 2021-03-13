# Text evaluator's syntax in BNF

All whitespace that is not a terminal symbol is ignored
```bnf
<Configuration>         ::= <Expression>*

<Expression>            ::= <Method-Call> | <State-Descriptor>

<Method-Call>           ::= <Identifier> "(" (<Arguments> | "") ");"

<Arguments>             ::= <Identifier> | <One-Or-More-Argument>

<One-Or-More-Argument>  ::=  <Identifier> | <Identifier> "," <One-Or-More-Argument>

<State-Descriptor>      ::= <Identifier> "->" (<Connection> ";" | "{" <Connection>+ "}")

<Connection>            ::= <Identifier> ":" (<Rule> | "{" <Rule>+ "}")

<Rule>                  ::= <Character> "->" <Character> "," <Direction> ";" 

<Identifier>            ::= (<Letter> | <Number>)+

<Character>             ::= <Letter> | <Number> | <Quoted-Character>

<Quoted-Character>      ::= "'" (<Letter> | <Number> | <Symbol> | " ") "'"

<Letter>                ::= "a" | ... | "z" | "A" | ... | "Z" 

<Number>                ::= "0" | ... | "9"

<Symbol>                ::=  "|" | " " | "!" | "#" | "$" | "%" | "&" | "(" | ")" | "*" | "+" | "," | "-" | "." | "/" | ":" | ";" | ">" | "=" | "<" | "?" | "@" | "[" | "\" | "]" | "^" | "_" | "`" | "{" | "}" | "~"
```
