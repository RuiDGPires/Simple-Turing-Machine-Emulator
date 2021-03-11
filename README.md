# Simple-Turing-Machine-Emulator
A simple turing machine emulator

This was made with the goal of practising C++ and for fun.

## Todo 
- [ ] Text evaluator for ease of use
- [ ] Extensive testing
- [ ] Some documentation and comments


### Example

Explaining what's in _main.cpp_:

```
tm.setAccept("qac");
tm.setReject("qrej");
tm.setInitial("qi");
```
The code above sets all the essencial states of a Turing Machine: the accept, reject and initial states
The argument is just the name which these states will be referenced by.
Only the initial state will be a "real" state, as in, can (and should) have connections to other states.

```
setRejectNoConnection(true);
```
This line makes it so that every connection that is not defined, is treated as rejecting the input.

```
tm.addState("q1");
```
This function just adds a possible state for the machine.
Once again, the argument is the name

```
tm.getState("qi").addRule('0', 'x',tmch::RIGHT, "q1");
```
This line defines a connection that goes from the state "qi" to the state "q1", recognizing the character '0' and writing 'x' in it's spot. It also shifts the pointer of the machine (in the input line) to the right.

```
tm.load("0111111");
```
This line loads the parameter as the input to the machine. This function also sets the current state to the previously defined initial state.

```
while(tm.state != tmch::ACCEPT && tm.state != tmch::REJECT){
    tm.step();
}
```
Run the program until it is accepted or rejected

```
std::cout << tm << std::endl;
```
Print the current configuration of the machine