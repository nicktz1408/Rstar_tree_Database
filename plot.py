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
    timesRangeIndex.append(int(y[1])*1.0/1000)
    timesRangeSerial.append(int(y[2])*1.0/1000)

for x in fKNN:
    y = x.split(" ")
    k.append(y[0])
    timesKnnIndex.append(int(y[1])*1.0/1000)
    timesKnnSerial.append(int(y[2])*1.0/1000)



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

    