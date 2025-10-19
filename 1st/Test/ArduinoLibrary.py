import serial
import time
from robot.api.deco import keyword

class ArduinoLibrary:
    def __init__(self, com_port="COM3", baud_rate=9600, timeout=2):
        self.com_port = com_port
        self.baud_rate = baud_rate
        self.timeout = timeout
        self.arduino = None

    @keyword
    def open_arduino(self):
        if self.arduino is None:
            try:
                self.arduino = serial.Serial(self.com_port, self.baud_rate, timeout=self.timeout)
                time.sleep(2)
            except Exception as e:
                raise RuntimeError(f"Cannot open Arduino on {self.com_port}: {e}")

    @keyword
    def close_arduino(self):
        if self.arduino is not None:
            self.arduino.close()
            self.arduino = None

    @keyword
    def wait_for_ready(self, timeout=10):
        if self.arduino is None:
            raise RuntimeError("Arduino not opened")
        start_time = time.time()
        while True:
            if time.time() - start_time > timeout:
                raise RuntimeError("Arduino READY signal not received within timeout")
            line = self.arduino.readline().decode(errors="ignore").strip()
            if line:
                print(f"<Arduino>: {line}")
            if "READY" in line:
                return

    @keyword
    def send_command(self, command):
        if self.arduino is None:
            raise RuntimeError("Arduino not opened")
        self.arduino.write((command + "\r\n").encode())
        time.sleep(0.3)
        lines = []
        while self.arduino.in_waiting > 0:
            line = self.arduino.readline().decode(errors="ignore").strip()
            if line:
                lines.append(line)
        return lines

    @keyword
    def verify_response(self, expected, lines):
        if not any(expected in line for line in lines):
            raise AssertionError(f"Expected '{expected}', got {lines}")
