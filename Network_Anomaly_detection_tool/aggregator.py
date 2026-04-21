import pandas as pd

INPUT_FILE = "data/traffic_raw.csv"
OUTPUT_FILE = "data/traffic_ts.csv"

def aggregate():
    df = pd.read_csv(INPUT_FILE)

    df['timestamp'] = pd.to_datetime(df['timestamp'])
    df.set_index('timestamp', inplace=True)

    # Resample per second
    ts = df.resample('1s').sum()

    ts.fillna(0, inplace=True)

    ts.to_csv(OUTPUT_FILE)
    print("Time series saved")

if __name__ == "__main__":
    aggregate()