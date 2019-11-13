#!/usr/bin/env python3
import sys, os, re, numpy
import numpy as np
import matplotlib.pyplot as plt

#--------------------------------------------------------------------------#
def main(output_file):
    concentration = []
    step = []

    file = open(output_file, "r")
    file_lines = file.readlines()
    for line in file_lines:
        m=re.search( r'(.+) (.+)', line, re.M|re.I)
        if m:
            step.append(float(m.group(1)))
            concentration.append(float(m.group(2)))

    figure(step, concentration, output_file)

#--------------------------------------------------------------------------#
def figure(x, y, this_label, title = ""):
    plt.plot(x,y, label=this_label)
    plt.xlabel("x axis")
    plt.ylabel("concentration")
    plt.legend()
    plt.title(title)

#--------------------------------------------------------------------------#
plt.figure()
for arg in range(1, len(sys.argv)):
    main(sys.argv[arg])
plt.show()
print("done")
