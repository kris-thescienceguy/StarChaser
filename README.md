# Star Chaser: Automatic Dome Controller

The Star Chaser dome control project was led by Kris Turner as part an upgrade, commissioned by Keele Observatory, in order to improve the functionality of their 24" research, reflector telescope.

Keele Observatory is located in North Staffordshire,  between Manchester and Birmingham on a large estate with extensive woods, lakes and parkland, formerly owned by the Sneyd family. 97% of the university's research is classified as world leading and of international importance, as a result of the 2014 Research Excellence Framework (REF 2014).

The software and digital electronics were produced by **Kris Turner**, who was at the time of the project, was an undergraduate physics with chemistry student. The mechanical designs were produced by **Dr James Albinson**. **Alan Bagnell** advised on the design, and safety, of the electrical systems.

*A special mention must be made to the entirety of the Keele Observatory volunteers without who there would be no dome to upgrade.*

## Wiring Specifications ##
The system has several parts which may need to replaced over time so for ease of use a wiring colour chart has been produced. This should be used in conjunction with wiring diagrams provided.

### Pulse Switch ###
There is no doubt that the microcontroller will miss some encoder pulses. It may also count some twice. Whether by gain or loss of pulses it’s likely that with extended use and due to cumulative error the accuracy of the system will decrease over time. In order to prevent this, a zero point was chosen where the microcontroller knows the exact azimuth of the dome. Using a magnet on the dome structure and a fixed reed switch, a pulse is sent to the microcontroller when this zero point is reached.

On this interrupt, the microcontroller resets the pulses counted and hence the azimuth of the dome to a known position. This switch is also polled by the driver software as part of the AtHome subroutine.

| Switch Wire | Extended Cable |
| --- | --- |
| Red | Orange |
| Blue | Blue |

### Encoders ###
In order to accurately determine the position of the dome, two incremental encoders are used, although only one is required and currently configurd. Each encoder has four wires: VCC, GND, A Phase, and B Phase. Phase A and phase B are interchangable but will reverse the direction of the encoder. The encoder phase signals require an external pull-up resistor and although the ATTiny25 microcontroller provides internal pull-ups they do not appear to be strong enough.

#### Encoder A ####
| Encoder Function | Encoder Wire | Extended Cable |
| --- | --- | --- |
| VCC | Red | Orange |
| GND | Black | Blue |
| Phase A | Green | Green |
| Phase B | White | Brown |


