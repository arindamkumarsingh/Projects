import psutil
import time
import csv
from datetime import datetime

OUTPUT_FILE = "data/traffic_raw.csv"

def capture(interval=1):
    print("Starting capture... Press Ctrl+C to stop")

    prev = psutil.net_io_counters()

    with open(OUTPUT_FILE, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["timestamp", "bytes_sent", "bytes_recv", "packets_sent", "packets_recv"])

    try:
        while True:
            time.sleep(interval)
            curr = psutil.net_io_counters()

            row = [
                datetime.now(),
                curr.bytes_sent - prev.bytes_sent,
                curr.bytes_recv - prev.bytes_recv,
                curr.packets_sent - prev.packets_sent,
                curr.packets_recv - prev.packets_recv
            ]

            with open(OUTPUT_FILE, "a", newline="") as f:
                writer = csv.writer(f)
                writer.writerow(row)

            print(row)

            prev = curr

    except KeyboardInterrupt:
        print("Capture stopped")

if __name__ == "__main__":
    capture()