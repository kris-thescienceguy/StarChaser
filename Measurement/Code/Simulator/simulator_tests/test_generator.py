import numpy as np
import matplotlib.pyplot as plt
'''
' Test Parameters
'''

w_speed = 3 #rpm
ppr = 400 #pulses per rotation
T = 0.1 # 0.1 seconds of data
samplingRate = 1000
'''
' Calculations
'''

x = open('10rpm.txt', mode='w')

ppm = w_speed * ppr #pulses per minute
pHz = ppm/60 #pulse frequency

t = np.arange(0, T, 1/samplingRate)
sineA = np.sin(2*3.14*pHz*t)
sineB = np.sin(2*3.14*pHz*t + (3.14/2))

phaseA = []
phaseB = []
for i in range(0, len(t)):
    if sineA[i] > 0:
        phaseA.append(1)
    else:
        phaseA.append(0)
        
    if sineB[i] > 0:
        phaseB.append(1)
    else:
        phaseB.append(0)

for i in range(0, len(t)):
    outputVal = phaseA[i]*2 + phaseB[i]
    x.write(str(outputVal) + "\n")

plt.plot(t, phaseA)
plt.plot(t, phaseB)
plt.show()
x.close()
