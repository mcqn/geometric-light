# Geometric Light

Code for the interactive Neopixel LED art installation designed and built with Simon Armstrong.

First installed as [the Christmas lights in Williamson Square in Liverpool in 2017](https://mcqn.com/ibal191), and since then shown at Makerfaire UK and [in the Hornby Library at Liverpool Makefest](https://www.instagram.com/p/BkpLNwRn1uq/).

## Files

There are a variety of test and prototyping sketches here, but the key folders are:

 * [PlayTheSquare](PlayTheSquare) - Arduino code for Teensy boards which controls up to eight "baubles" via an OctoWS2811 shield and up to two input controllers
 * [controller](controller) - Ruby code to run on a Raspberry Pi and marshal messages between up to four Teensy boards running the `PlayTheSquare` code over USB
 * [pi-controller](pi-controller) - Ansible scripts to provision a Raspberry Pi running `controller`
 * [stats](stats) - Some basic stats run on the activity log captured by `controller` during the Christmas 2017 installation

