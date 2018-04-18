"""
Allow the user to control the car using the arrow keys.

UP arrow => accelerate
DOWN arrow => decelerate
RIGHT arrow => make a right turn
LEFT arrow => make a left turn

"""

"""
To pick up next time:

1. Play around with the parameters to get sensible outputs to the PSoC.
2. Think about how the current input to the PSoC will be shown to the user.

"""


from gpiozero import DigitalOutputDevice
import keyboard

# These pins are interpreted by the PSoC which in turn controls the motors
PIN_TO_PSOC_THEN_MOTOR = 5
PIN_TO_PSOC_THEN_SERVO = 6

# Initialize the controllers to the pins
gas_pedal = DigitalOutputDevice(PIN_TO_PSOC_THEN_MOTOR)
steering_wheel = DigitalOutputDevice(PIN_TO_PSOC_THEN_MOTOR)

# Variables to help control (Shouldn't start at zero..)

THROTTLE_DELTA = .05
BRAKE_DELTA = -.1
STEERING_DELTA = .1

throttle = 0.001
steer = 0.5

# Run an infinite loop...
while True:
    # Tell the PSoC to speed up the car...
    if keyboard.is_pressed('up'):
        throttle = min(throttle + THROTTLE_DELTA, 1.0)

    # Tell the PSoC to slow down the car
    if keyboard.is_pressed('down'):
        throttle = max(throttle + BRAKE_DELTA, 0.0)

    # Tell the PSoC to steer the car left
    if keyboard.is_pressed('left'):
        steer = max(throttle - STEERING_DELTA, 0.0)

    # Tell the PSoC to steer the car to the right
    if keyboard.is_pressed('right'):
        steer = max(throttle + STEERING_DELTA, 1.0)

    gas_pedal.blink(on_time=throttle, off_time=1-throttle)
    steer.blink(on_time=steer, off_time=1-steer)

    

        

    
