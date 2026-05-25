"""
Smart Water Sump Cleaning Robot
Raspberry Pi Controller Script

Author  : Pradeep S Sangannanavr (USN: 1HK22EC122)
College : HKBK College Of Engineering
Dept    : Electronics and Communication Engineering

This script runs on the Raspberry Pi and sends HTTP commands
to the ESP32 to control the robot's movement and cleaning system.

Communication: Raspberry Pi → (HTTP over WiFi) → ESP32
"""

import requests
import time
import logging

# -------- CONFIGURATION --------
ESP32_IP = "http://192.168.1.100"   # Replace with your ESP32's actual IP address
REQUEST_TIMEOUT = 2                  # Seconds before a request times out

# -------- LOGGING --------
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s"
)
log = logging.getLogger(__name__)


# ========================================================
#  COMMAND SENDER
# ========================================================

def send(command: str) -> bool:
    """
    Send an HTTP GET command to the ESP32.

    Args:
        command: The endpoint to call (e.g. 'forward', 'cleanON')

    Returns:
        True if the request succeeded, False otherwise.
    """
    url = f"{ESP32_IP}/{command}"
    try:
        response = requests.get(url, timeout=REQUEST_TIMEOUT)
        log.info(f"Sent '{command}' → HTTP {response.status_code}")
        return True
    except requests.exceptions.ConnectionError:
        log.error(f"Connection failed for command '{command}'. Is the ESP32 online?")
    except requests.exceptions.Timeout:
        log.warning(f"Command '{command}' timed out after {REQUEST_TIMEOUT}s.")
    except Exception as e:
        log.error(f"Unexpected error for command '{command}': {e}")
    return False


# ========================================================
#  MOVEMENT HELPERS
# ========================================================

def forward(duration: float = 1.0):
    send("forward")
    time.sleep(duration)

def backward(duration: float = 1.0):
    send("back")
    time.sleep(duration)

def turn_left(duration: float = 0.5):
    send("left")
    time.sleep(duration)

def turn_right(duration: float = 0.5):
    send("right")
    time.sleep(duration)

def stop(duration: float = 0.5):
    send("stop")
    time.sleep(duration)

def clean_on(duration: float = 3.0):
    send("cleanON")
    time.sleep(duration)

def clean_off(duration: float = 1.0):
    send("cleanOFF")
    time.sleep(duration)

def auto_mode():
    send("auto")


# ========================================================
#  CLEANING PATTERNS
# ========================================================

def sweep_pattern(passes: int = 3):
    """
    Perform a simple back-and-forth sweep cleaning pattern.

    Args:
        passes: Number of forward-backward passes to complete.
    """
    log.info(f"Starting sweep pattern ({passes} passes)...")
    clean_on(0)  # Turn on cleaning without waiting

    for i in range(passes):
        log.info(f"Pass {i + 1}/{passes}")
        forward(2.0)
        turn_right(0.6)
        forward(2.0)
        turn_left(0.6)

    clean_off()
    stop()
    log.info("Sweep pattern complete.")


def spiral_pattern():
    """
    Perform a simple expanding spiral pattern for full coverage.
    """
    log.info("Starting spiral pattern...")
    clean_on(0)

    delay = 0.5
    for _ in range(4):
        forward(delay)
        turn_right(0.4)
        delay += 0.3

    clean_off()
    stop()
    log.info("Spiral pattern complete.")


# ========================================================
#  MAIN — EXAMPLE AUTOMATIC CONTROL LOOP
# ========================================================

if __name__ == "__main__":
    log.info(f"Connecting to ESP32 at {ESP32_IP} ...")

    # Quick connectivity check
    if not send("stop"):
        log.error("Cannot reach ESP32. Check IP address and WiFi connection.")
        exit(1)

    log.info("ESP32 reachable. Starting cleaning sequence...")

    try:
        # --- Phase 1: Move into position ---
        forward(2.0)
        turn_left(0.5)
        forward(1.0)

        # --- Phase 2: Run sweep cleaning ---
        sweep_pattern(passes=3)

        # --- Phase 3: Final position ---
        stop(1.0)
        log.info("Cleaning sequence finished.")

    except KeyboardInterrupt:
        log.info("Interrupted by user. Stopping robot...")
        send("cleanOFF")
        send("stop")
