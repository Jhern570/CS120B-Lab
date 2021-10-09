# Test file for "Lab2_introToAVR"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x01 => PORTC: 0x08, state: pressA0"
# Set inputs
setPINA 0x01
# Continue for several ticks
continue 10
# Set expect values
expectPORTC 0x08
expect state pressA0
# Check pass/fail
checkResult

test "PINA: 0x02 => PORTC: 0x06, state: pressA1"
# Set inputs
setPINA 0x02
# Continue for several ticks
continue 5
# Set expect values
expectPORTC 0x06
expect state pressA1
# Check pass/fail
checkResult

test "PINA: 0x00 => PORTC: 0x07, state: waitPress"
# Set inputs
setPINA 0x00
continue 5
# Set expect values
expectPORTC 0x07
expect state waitPress
# Check pass/fail
checkResult

test "PINA: 0x03 => PORTC: 0x00, state: pressBoth"
# Set inputs
setPINA 0x03
continue 5
# Set expect values
expectPORTC 0x00
expect state pressBoth
# Check pass/fail
checkResult

test "PINA: 0x00, 0x01, 0x00, 0x02 => PORTC: 0x07, state: pressA1"
# Set inputs
setPINA 0x00
continue 5
setPINA 0x01
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
# Set expect values
expectPORTC 0x07
expect state pressA1
# Check pass/fail
checkResult

test "PINA: 0x00, 0x02, 0x00, 0x01 => PORTC: 0x07, state: pressA0"
# Set inputs
setPINA 0x00
continue 5
setPINA 0x02
continue 5
setPINA 0x00
continue 5
setPINA 0x01
continue 5
# Set expect values
expectPORTC 0x07
expect state pressA0
# Check pass/fail
checkResult



# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
