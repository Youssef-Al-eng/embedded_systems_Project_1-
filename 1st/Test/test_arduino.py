import serial
import time

COM_PORT = "COM3"
BAUD_RATE = 9600
TIMEOUT = 2

COMMAND_TESTS = [
    {"command": "on", "expected": "LED turned ON"},
    {"command": "of", "expected": "LED turned OFF"},
    {"command": "Anything", "expected": "Invalid command"},
]

BUTTON_TESTS = [
    {"state": "pressed", "expected": "BUTTON_PRESSED"},
    {"state": "released", "expected": "BUTTON_RELEASED"},
]

try:
    arduino = serial.Serial(COM_PORT, BAUD_RATE, timeout=TIMEOUT)
except Exception as e:
    print(f"Error opening {COM_PORT}: {e}")
    exit(1)

while True:
    line = arduino.readline().decode().strip()
    if "READY" in line:
        break

all_passed = True

for test in COMMAND_TESTS:
    cmd = test["command"]
    expected = test["expected"]
    arduino.write((cmd + "\r\n").encode())
    time.sleep(0.3)
    response_lines = []
    while arduino.in_waiting > 0:
        line = arduino.readline().decode().strip()
        if line:
            response_lines.append(line)
    if not any(expected in line for line in response_lines):
        all_passed = False
        print(f"❌ Command '{cmd}' FAILED: Expected '{expected}', got {response_lines}")
        break
    else:
        print(f"✅✅ Command '{cmd}' PASSED")

if all_passed:
    for test in BUTTON_TESTS:
        state = test["state"]
        expected = test["expected"]
        input(f"Please {state} the pushbutton and press Enter...")
        time.sleep(0.3)
        response_lines = []
        while arduino.in_waiting > 0:
            line = arduino.readline().decode().strip()
            if line:
                response_lines.append(line)
        if not any(expected in line for line in response_lines):
            all_passed = False
            print(f"❌ Button '{state}' FAILED: Expected '{expected}', got {response_lines}")
            break
        else:
            print(f"✅✅ Button '{state}' PASSED")

if all_passed:
    print("\n✅✅ ALL TESTS PASSED ✅✅")
else:
    print("\n❌ SOME TESTS FAILED ❌")

arduino.close()
