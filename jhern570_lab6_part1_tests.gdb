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

test "PINA: 0x00 => PORTC: 0x00"
# Set inputs
setPINA 0x00
continue 5
# Set expect values
expectPORTC 0x00
# Check pass/fail
checkResult

# Example test:
test "PINA: 0x01 => PORTC: 0x21"
# Set inputs
setPINA 0x01
# Continue for several ticks
continue 5
# Set expect values
expectPORTC  0X21
# Check pass/fail
checkResult

test "PINA: 0x01, 0X00=> PORTC: 0x21"
# Set inputs
setPINA 0x01
setPINA 0x00
# Continue for several ticks
continue 5
# Set expect values
expectPORTC 0x21
# Check pass/fail
checkResult

test "PINA: 0x01, 0x00, 0x01, 0x00, 0x01 => PORTC: 0x0C"
# Set inputs
setPINA 0x01
setPINA 0x00
setPINA 0x01
setPINA 0x00
setPINA 0x01
# Continue for several ticks
continue 5
# Set expect values
expectPORTC 0x0C
# Check pass/fail
checkResult

test "PINA: 0x08 => PORTB: 0x00, PORTC: firstPress"
# Set inputs
setPINA 0x08
continue 2
# Set expect values
expectPORTB 0x00
expectPORTC firstPress
# Check pass/fail
checkResult

test "PINA: 0x04, 0x00,  0x02 => PORTB: 0x01, PORTC = secondPress"
# Set inputs
setPINA 0x04
continue 5
setPINA 0x00
continue 5
setPINA 0x02
continue 5
# Set expect values
expectPORTB 0x01
expectPORTC secondPress
# Check pass/fail
checkResult

test "PINA: 0x04, 0x00, 0x02, 0x00, 0x08 => PORTB: 0x00, state: pressI"
# Set inputs
setPINA 0x04
continue 2
setPINA 0x00
continue 2
setPINA 0x02
continue 2
setPINA 0x00
continue 2
setPINA 0x08
continue 2
# Set expect values
expectPORTB 0x00
expectPORTC pressI
# Check pass/fail
checkResult

test "PINA: 0x04, 0x02 => PORTB: 0x00, PORTC: firstPress"
# Set inputs
setPINA 0x04
# Continue for several ticks
continue 5
setPINA 0x02
continue 5
# Set expect values
expectPORTB 0x00
expectPORTC firstPress
# Check pass/fail
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
