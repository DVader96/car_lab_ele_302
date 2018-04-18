## To-do Items

1. The pi will send two square waves of varying widths to the PSoC. We need to translate these waves into inputs to the driving motor and servo motor. We therefore need to build interrupts and also modify the navigation and speed control code to use inputs from the pi.

2. We need to connect 2 pins from the raspberry pi to 2 pins on the PSoC. Rad said he'll deliver a Pi Cobbler which will allow us to connect to the pi's pins.

3. Once the Pi and the PSoC are connected, and the software on both is completed, we need to tune the instance variables in [control_car.py](https://github.com/dchege711/car_lab_ele_302/blob/navigation/pi_software/control_car.py) such that pressing the arrow keys changes the car's speed or direction in a reasonable way.

#### Tuesday, April 17th (Chege)

* I added [control_car.py](https://github.com/dchege711/car_lab_ele_302/blob/navigation/pi_software/control_car.py). 
* I wasn't able to test and find good parameters to drive the car.
* I'll email Radd for directions on how to make KK connections to the Pi's pins.
