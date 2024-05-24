# Finite-Automata
This is a Finite Automata implementation according to Formal Languages and Automata Theory course.

# PROJECT CONTAINS: 

## DFA, NFA, LAMBDA-NFA
The implemented Lambda-NFA can handle lambda transitions and certain edge cases associated with them, such as lambda-cycles.
The separate implementation of a DFA or simple NFA class is not necessary, because the Lambda-NFA already handles all the cases.

Project structure overview:
I implemented the class for a Lambda-NFA using another class for representing a single state's data (information about the state tag value and the state's transitions to other states), and multiple data structures, such as vectors, unordered maps, smart pointers and a stack.

## PARSER
I implemented the Parser class, used for parsing a Regular Expression for converting it into a NFA.

## NFA to DFA conversion

## PUSHDOWN AUTOMATA

## CONTEXT FREE GRAMMAR
This Project also includes context free grammar word acceptance, using CYK algorithm.

## FINITE STATE TRANSDUCER
Finally, Finite State Transducer, it is like a Lambda-NFA, but it has an output tape, and checks if 2 strings are in a relation.
