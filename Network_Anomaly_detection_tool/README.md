]## 📊 Network Traffic Anomaly Detection (Calculus-Based)

### 🔹 Overview
This project implements a network traffic anomaly detection system using Python and basic calculus concepts.  
It captures live network activity, converts it into time-series data, and identifies abnormal spikes using mathematical and statistical techniques.

We model network traffic as a function **f(t)**:
- **Derivative (f'(t))** → detects sudden spikes (rate of change)
- **Integral (∫f(t)dt)** → measures cumulative traffic load  

This project demonstrates how theoretical math concepts can be applied to real-world cybersecurity problems.

---

### 🔹 Features
- Live network traffic monitoring
- Time-series conversion (packets per second)
- Calculus-based analysis (derivative & cumulative sum)
- Statistical anomaly detection (mean + standard deviation)
- Interactive dashboard using Streamlit
- Traffic spike simulation for testing

---

### 🔹 Tech Stack
- **Python 3**
- **psutil** – network monitoring
- **pandas / numpy** – data processing
- **plotly / matplotlib** – visualization
- **streamlit** – dashboard UI

---

### 🔹 Project Structure

network-anomaly/
│── capture.py # Capture live network traffic
│── aggregator.py # Convert raw data → time-series
│── analysis.py # Apply calculus + anomaly detection
│── app.py # Streamlit dashboard
│── simulate.py # Generate artificial traffic spikes
│── data/ # Stores CSV outputs


---

### 🔹 How It Works (Pipeline)

1. **Data Capture**
   - Uses `psutil` to collect network statistics
   - Output file: `data/traffic_raw.csv`

2. **Data Aggregation**
   - Converts raw logs into time-series format (per second)
   - Output file: `data/traffic_ts.csv`

3. **Analysis**
   - Computes:
     - Derivative → rate of change
     - Integral → cumulative traffic
   - Detects anomalies using:
     ```
     threshold = mean + 3 × standard deviation
     ```
   - Output file: `data/anomalies.csv`

4. **Visualization**
   - Displays traffic patterns and anomaly points
   - Built using Streamlit + Plotly

---

### 🔹 Setup Instructions

#### 1. Clone the repository

```bash
git clone https://github.com/arindamkumarsingh/Projects
cd Network_Anomaly_detection_tool
```


#### 2. Create virtual environment

```bash
python -m venv venv
```


#### 3. Activate virtual environment

Linux/Mac:

```bash
source venv/bin/activate
```


Windows:

```bash
venv\Scripts\activate
```


#### 4. Install dependencies

```bash
pip install psutil pandas numpy matplotlib plotly streamlit
```


---

### 🔹 Running the Project

#### Step 1: Start capturing traffic

```bash
python capture.py
```


#### Step 2: Convert to time-series

```bash
python aggregator.py
```


#### Step 3: Run analysis

```bash
python analysis.py
```


#### Step 4: Launch dashboard

```bash
streamlit run app.py
```

---

### 🔹 Testing (Simulating Traffic Spike)

To generate artificial traffic spikes:

```bash
python simulate.py
```


Then rerun:
```bash
python aggregator.py
python analysis.py
```


Refresh the dashboard to observe anomaly detection.

---

### 🔹 Example Output
- Normal traffic → smooth graph  
- Spike/attack → sudden jump with highlighted anomaly points  

> ⚠️ Add screenshots here for better presentation in GitHub.

---

### 🔹 Detection Logic

An anomaly is flagged when:

traffic > mean + 3 × standard deviation


Additionally:
- Sudden increases in derivative indicate spike behavior
- Cumulative traffic helps analyze load patterns

---

### 🔹 Limitations
- Not a production-grade intrusion detection system
- Uses basic statistical methods (no machine learning)
- No deep packet inspection
- Limited to local/system-level monitoring

---

### 🔹 Future Improvements
- Machine learning models (Isolation Forest, LSTM)
- Protocol-level traffic analysis (TCP/UDP/ICMP)
- Real-time alert system (email/SMS)
- Auto-refreshing dashboard
- Deployment on cloud or embedded systems

---

### 🔹 Learning Outcomes
- Practical application of calculus in cybersecurity
- Understanding of time-series data processing
- Hands-on experience with network monitoring
- Building interactive data dashboards

---

### 🔹 Why This Project Matters
This project bridges the gap between theoretical mathematics and real-world applications by showing how calculus can be used to detect abnormal behavior in network systems.

---

### 🔹 Author
**Arindam Kumar Singh**

---