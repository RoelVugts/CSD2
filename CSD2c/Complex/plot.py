import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import csv
import sys

type = sys.argv[1]

# create a list and import data from output.csv file
data = list()
with open('./response.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        data.append(float(row[0]))

# transform list to numpy array
np_data = np.array(data)

# create samples for x axis
t = np.arange(0, len(data), 1)

# create plot
fig, ax = plt.subplots()
ax.plot(t, np_data)


if type == "amplitude":
    min = -80.
    max = 6.
    step = 6.0
    yname = "Gain (dB)"
    name = "Amplitude Response"
elif type == "phase":
    min = -2*3.1415926535897
    max = 2*3.1415926535897
    step = 3.1415926535897 / 4
    yname = "radians"
    name = "Phase Response"


plt.yticks(np.arange(min, max, step))
ax.set(xlabel='Point', ylabel=yname,
       title=name)
ax.grid()

# To save the result, outcomment the line below:
# fig.savefig("data_plot.png")
plt.show()