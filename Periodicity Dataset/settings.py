# borders for length of a stream
STREAM_LENGTHS = range(36,37)
PACKETS_PER_PATTERN = range(2,5)

# Distribution normalized standard deviation
# Given in %
PERIODIC_STDDEV = range(0,5)

# Higher normalized stddev generates aperiodic streams
APERIODIC_STDDEV = range(5,100)

# random seeds for reproducability
SEEDS = [12352, 67245, 692478, 3423452, 695, 719838]

# Count of streams to generate per class
STREAM_COUNT = 1000

# Period range of TSN streams in us
PERIOD_RANGE = range(1, 1000000) # 1us to 1s

# Conversion factor for period ranges to s
PERIOD_FACTOR = 10**-6
ROUND_DIGITS = 10

# Location to store output
OUTPUT_FOLDER = "data"