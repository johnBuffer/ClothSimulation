# Cloth Simulation

Very simple cloth simulation using Verlet position based physics.

![image](https://github.com/johnBuffer/ClothSimulation/blob/main/images/image_1.png)

# Commands

|Command|Action|
|---|---|
|**Left click**|Move view|
|**Wheel**|Zoom|
|**Right click**|Move cloth|
|**Middle click**|Cut cloth|

# Compilation

To compile just navigate to the main directory of 'ClothSimulation'
e.g. user@debian:~/ClothSimulation$
Here open a terminal and first make sure you have cmake, build-essential and gdb installed, if not you can just run;

`sudo apt-get install cmake build-essential gdb`

Now in the main directory run `cmake .`
Next run `make`
Then you can run the script with `sudo ./Cloth`
