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
test "PINA: 0x00 => PORTB: 0x00, PORTC: 0x00"
# Set inputs
setPINA 0x00
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x00
expectPORTC 0x00
# Check pass/fail
checkResult

# Add tests below

# Example test:
test "PINA: 0x10 => PORTB: 0x01, PORTC: 0x00"
# Set inputs
setPINA 0x10
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x01
expectPORTC 0x00
# Check pass/fail
checkResult

# Example test:
test "PINA: 0x01 => PORTB: 0x00, PORTC: 0x10"
# Set inputs
setPINA 0x01
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x00
expectPORTC 0x10
# Check pass/fail
checkResult

# Example test:
test "PINA: 0x11 => PORTB: 0x01, PORTC: 0x10"
# Set inputs
setPINA 0x11
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x01
expectPORTC 0x10
# Check pass/fail
checkResult

# Example test:
test "PINA: 0x18 => PORTB: 0x01, PORTC: 0x80"
# Set inputs
setPINA 0x18
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x01
expectPORTC 0x80
# Check pass/fail
checkResult

test "PINA: 0x81 => PORTB: 0x08, PORTC: 0x10"
# Set inputs
setPINA 0x81
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x08
expectPORTC 0x10
# Check pass/fail
checkResult

test "PINA: 0xAA => PORTB: 0x0A, PORTC: 0xA0"
# Set inputs
setPINA 0xAA
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x0A
expectPORTC 0xA0
# Check pass/fail
checkResult

test "PINA: 0xF0 => PORTB: 0x0F, PORTC: 0x00"
# Set inputs
setPINA 0xF0
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x0F
expectPORTC 0x00
# Check pass/fail
checkResult

test "PINA: 0x0F => PORTB: 0x00, PORTC: 0xF0"
# Set inputs
setPINA 0x0F
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x00
expectPORTC 0xF0
# Check pass/fail
checkResult

test "PINA: 0xFF => PORTB: 0x0F, PORTC: 0xF0"
# Set inputs
setPINA 0xFF
# Continue for several ticks
continue 5
# Set expect values
expectPORTB 0x0F
expectPORTC 0xF0
# Check pass/fail
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
