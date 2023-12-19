import matplotlib.pyplot as plt
import pandas as pd

# First burst starts at 90ms
FIRST_BURST=90
# Burst Duration is 150ms
BURST_DURATION=150
# Time between bursts is 200ms
BURST_SLEEP=200
# Number of packets until SCIP integrates streamS
PACKET_THRESHOLD=20

# Get data from simulation result
data = pd.read_csv("result.csv")

# Select row based on values in two columns
# Column "name" == endToEndDelay:vector
# Column "type" == vector
result = data.loc[ (data["name"] == "endToEndDelay:vector") & (data["type"] == "vector")]

# Get timestamps of packet arrivals and delay measurements
# Since they are store as a single string, they have to be split and converted to float.
# Multiplication by 1000 converts the timestamps from (s) to (ms)
timestamps = [ float(x)*1000 for x in str(result["vectime"].values[0]).split() ]
delay = [ float(x)*1000 for x in str(result["vecvalue"].values[0]).split() ]

# The Omnet++ VoIP app adds the packetization rate (1 packet every 20ms) to the end-to-end delay.
# However, this delay does not come from the network so we subtract the 20ms from all delay measurements.
timestamps = list(map(lambda x: x-20,timestamps))

# Draw overload and queue qmptying phases in the figure
# Depends on simulation configuration, if it changes it has to be altered here as well
burst_starts = [FIRST_BURST + (BURST_DURATION + BURST_SLEEP) * x for x in range(0,3)]

# Queue emptying phase has an offset of BURST_DURATION to first burst
# this only works if bursts do not overlap and queue empty fully inbetween
# So BURST_SLEEP > BURST_DURATION
queue_emptying_start = [FIRST_BURST + BURST_DURATION + (BURST_DURATION + BURST_SLEEP) * x for x in range(0,3)]


# PLTO FIGURE
# Figure format
plt.figure(figsize=(10,7))
plt.rcParams.update({'font.size': 20})
plt.grid(which='major', linestyle='-')
plt.minorticks_on()
plt.grid(which='minor', linestyle='--')

plt.xlabel("Packet arrival time (ms)")
plt.ylabel("End-to-end delay (ms)")

plt.xlim([0,900])


# Plot end-to-end delay
plt.plot(timestamps,delay,"bx-",label="Per-packet latency")

# Plot time of stream integration between PACKET_THRESHOLD and next packet
#                            -- Distance between two packet arrivals --             -- Arrival time of PACKET_THRESHOLD --
integration_time = ((timestamps[PACKET_THRESHOLD]-timestamps[PACKET_THRESHOLD-1])/2) + timestamps[PACKET_THRESHOLD-1]
plt.axvline(integration_time,color="green",linewidth=5,linestyle="dashed",label="Stream integration")

# Plot Bursts
# Plot first overload phase and set label for legend
#   otherwise there would be one label in legend per overload phase
xmin = burst_starts[0]
plt.axvspan(xmin,xmin+BURST_DURATION,color="red",alpha=0.2,label="Overload phase")
# Plot all other bursts but dont set label for legend
for xmin in burst_starts[1:]:
    plt.axvspan(xmin,xmin+BURST_DURATION,color="red",alpha=0.2)
# Same as for plot burstsS
xmin = queue_emptying_start[0]
plt.axvspan(xmin,xmin+BURST_DURATION,color="orange",alpha=0.2,label="Queue emptying phase")
for xmin in queue_emptying_start[1:]:
    plt.axvspan(xmin,xmin+BURST_DURATION,color="orange",alpha=0.2)

# Store figureS
plt.legend()
plt.tight_layout()
plt.savefig("result.pdf",format="pdf",bbox_inches="tight")