# Example
The following Turing Machine accepts all input that starts with two '0's and has more than one '1' after them.

![diagram](images/diagram.png)


Let's say we want to test the input "001111". There are several ways to do this.
1. [Using the GUI app](#gui)
2. [Using the command line app](#cmd)
3. [Using the text evaluator library](#evl)
4. [Using the Turing Machine library directly](#lib)

The configuration file will be [example.conf](example.conf), and it follows the syntax described in [BNF.md](BNF.md):

<a name="gui"></a>
## Using the GUI
    (Under construction)

<a name="cmd"></a>
## Using the command line app

The test is simply run with the following command (linux terminal):
>./tm example.conf 001111
>

---
<a name="evl"></a>
## Using the text evaluator library

```cpp
#include "turingmachine/include/turingmachine.hpp"
#include "evaluator/include/evaluator.hpp"

(...)

tmch::TuringMachine tm = tmch::TuringMachine();
evl::Evaluator e(&tm);
if (e.evalFile("example.conf")){
    tm.load("001111");
    tm.run();
    std::cout << tm << std::endl;
}
```
---
<a name="lib"></a>
## Using the Turing Machine library directly

```cpp
#include "turingmachine/include/turingmachine.hpp"

(...)

tmch::TuringMachine tm;
tm.setAccept("qac");
tm.setReject("qrej");
tm.setInitial("qi");
tm.setRejectNoConnection(true);
tm.addState("q1");
tm.addState("q2");
tm.addState("q3");

tm.getState("qi").addRule('0', 'x',tmch::RIGHT, "q1");

tm.getState("q1").addRule('0', 'x',tmch::RIGHT, "q2");

tm.getState("q2").addRule('1', '1',tmch::RIGHT, "q3");

tm.getState("q3").addRule('1', '1',tmch::RIGHT, "q3");

tm.getState("q3").addRule(' ', ' ',tmch::RIGHT, "qac");


tm.load("001111");

tm.run();
std::cout << tm << std::endl;

return 0;
```

---
```cpp
tm.setAccept("qac");
tm.setReject("qrej");
tm.setInitial("qi");
```
The code above sets all the essencial states of a Turing Machine: the accept, reject and initial states
The argument is just the name which these states will be referenced by.
Only the initial state will be a "real" state, as in, can (and should) have connections to other states.

```cpp
setRejectNoConnection(true);
```
This line makes it so that every connection that is not defined, is treated as rejecting the input.

```cpp
tm.addState("q1");
```
This function just adds a possible state for the machine.
Once again, the argument is the name

```cpp
tm.getState("qi").addRule('0', 'x',tmch::RIGHT, "q1");
```
This line defines a connection that goes from the state "qi" to the state "q1", recognizing the character '0' and writing 'x' in it's spot. It also shifts the pointer of the machine (in the input line) to the right.

```cpp
tm.load("0111111");
```
This line loads the parameter as the input to the machine. This function also sets the current state to the previously defined initial state.

```cpp
tm.run();
```
Run the program until it is accepted or rejected

```cpp
std::cout << tm << std::endl;
```
Print the current configuration of the machine
