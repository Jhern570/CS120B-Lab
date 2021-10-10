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
test "PINA: 0x01 => PORTB: 0x00, PORTC: pressX"
# Set inputs
setPINA 0x01
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x00
expectPORTC  pressX
# Check pass/fail
checkResult

test "PINA: 0x02 => PORTB: 0x00, PORTC: pressY"
# Set inputs
setPINA 0x02
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x00
expectPORTC pressY
# Check pass/fail
checkResult

test "PINA: 0x04 => PORTB: 0x00, PORTC: pressP"
# Set inputs
setPINA 0x04
# Continue for several ticks
continue 5
continue 5
# Set expect values
expectPORTB 0x00
expectPORTC pressP
# Check pass/fail
checkResult


test "PINA: 0x00 => PORTB: 0x00, PORTC: waitPress"
# Set inputs
setPINA 0x00
continue 5
# Set expect values
expectPORTC 0x00
expect state waitPress
# Check pass/fail
checkResult

test "PINA: 0x08 => PORTB: 0x00, PORTC: waitPress"
# Set inputs
setPINA 0x08
continue 5
# Set expect values
expectPORTB 0x00
expectPORTC waitPress
# Check pass/fail
checkResult

test "PINA: 0x04, 0x02 => PORTB: 0x01, PORTC = unlock"
# Set inputs
setPINA 0x00
continue 2
setPINA 0x04
continue 2
setPINA 0x02
continue 2
# Set expect values
expectPORTB 0x01
expectPORTC unlock
# Check pass/fail
checkResult

test "PINA: 0x04, 0x02, 0x08 => PORTB: 0x00, state: pressI"
# Set inputs
setPINA 0x04
continue 2
setPINA 0x02
continue 2
setPINA 0x08
continue 2
# Set expect values
expectPORTB 0x00
expectPORTC pressI
# Check pass/fail
checkResult



# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
