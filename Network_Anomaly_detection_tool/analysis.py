import pandas as pd

INPUT_FILE = "data/traffic_ts.csv"
OUTPUT_FILE = "data/anomalies.csv"

def analyze():
    df = pd.read_csv(INPUT_FILE, parse_dates=['timestamp'])
    df.set_index('timestamp', inplace=True)

    traffic = df['packets_recv']

    # DERIVATIVE (rate of change)
    df['derivative'] = traffic.diff()

    # INTEGRAL (cumulative sum)
    df['integral'] = traffic.cumsum()

    # THRESHOLD
    mean = traffic.mean()
    std = traffic.std()

    threshold = mean + 3 * std

    # ANOMALY CONDITION
    df['anomaly'] = traffic > threshold

    df.to_csv(OUTPUT_FILE)

    print("Analysis complete")
    print("Threshold:", threshold)
    print("Anomalies:\n", df[df['anomaly']])

if __name__ == "__main__":
    analyze()