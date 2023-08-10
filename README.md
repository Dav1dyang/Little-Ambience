# Little Ambience

![Tabletop_light](./photos/Introduction_slide.png)

A series of speculative products designed by David Yang. For more information, please visit: https://davidyang.work/Little-Ambience-Detail

## Intro

Little Ambience is a series of speculative household electronics that simulate the remote presence of people and places without relying on video calls. The series comprises two electronics: a tabletop/wall mount light and a pair of humidifiers. The light, designed to resemble a window, displays the sky from a location where people feel connected. The humidifiers are placed in different locations or homes and activate only when both sense the presence of people in the space.

Little Ambience takes the simulation of nature and senses, such as light and smell, to gently decorate a living space with a presence of a place or a person we care about and love. Mirroring the form it takes, Little Ambience interacts passively.

Little Ambience draws inspiration from light and space artists such as James Turrell and Olafur Eliasson, as well as design and material-focused studios like CW&T and Teenage Engineering.

## Code

The code is only for functionality testing. It is made specifically to run on ESP32 and a custom PCB.

Right now, the code provided will be able to test out the gradient lights function for the Day & Night light and the mist trigger for the Water & Air humidifier. A few critical steps still need to be taken for it actually to work (Looking for developers to collab!).

Here are the functions list:

### Day and Night (TableTop Light)

| Function                | Done? |
| ----------------------- | ----- |
| Gradient Color Test     | Yes   |
| 24 hours sky color test | No    |
| ESP32 WIFI Connection   | No    |
| Weather API Integration | No    |
| Weather Animations      | No    |
| Audio Intergration      | No    |
| Backend Server          | No    |

### Water and Air (Humidifier)

| Function              | Done? |
| --------------------- | ----- |
| Mist Trigger Test     | Yes   |
| PIR Sensor Test       | No    |
| ESP32 WIFI Connection | No    |
| Backend server        | No    |

I used chroma.js with glitch to host a simple server to generate gradient values: https://glitch.com/edit/#!/little-ambience-server

## Little Ambience PCB V1.1

This PCB design utilizes its small footprint to fit into the product. It uses JST connectors for NeoPixels and Lipo Battery. It has USB Mirco for charging.

## Next Steps

I will work on this project's code as much as I can. But I would love to seek help from a professional coder. Moreover, I want to set up live cameras pointing at the sky and find a way to map the sky to Day and Night light.
