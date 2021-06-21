import matplotlib.pyplot as plt

ranges = []
timesRangeIndex = []
timesRangeSerial = []

k = []
timesKnnIndex = []
timesKnnSerial = []

fRange = open("statisticsRange.txt", "r")
fKNN = open("statisticsKNN.txt", "r")


for x in fRange:
    y = x.split(" ")
    ranges.append(y[0])
    timesRangeIndex.append(y[1])
    timesRangeSerial.append(y[2])

for x in fKNN:
    y = x.split(" ")
    k.append(y[0])
    timesKnnIndex.append(y[1])
    timesKnnSerial.append(y[2])



plt.subplot(2, 1, 1)
plt.plot(ranges, timesRangeIndex)
plt.plot(ranges, timesRangeSerial, 'r')
plt.ylabel("Time")
plt.xlabel("Range")


plt.subplot(2, 1, 2)
plt.plot(k, timesKnnIndex)
plt.plot(k, timesKnnSerial, 'r')
plt.ylabel("Time")
plt.xlabel("K-Neighbors")

plt.show()

    