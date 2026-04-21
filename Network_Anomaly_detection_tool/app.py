import streamlit as st
import pandas as pd
import plotly.express as px

st.title("📊 Network Traffic Anomaly Detection")

df = pd.read_csv("data/anomalies.csv", parse_dates=['timestamp'])
df.set_index('timestamp', inplace=True)

traffic = df['packets_recv']

# GRAPH
fig = px.line(df, x=df.index, y=traffic, title="Traffic Over Time")

# Highlight anomalies
anomalies = df[df['anomaly']]
fig.add_scatter(x=anomalies.index, y=anomalies['packets_recv'],
                mode='markers', marker=dict(color='red', size=8),
                name="Anomaly")

st.plotly_chart(fig)

st.subheader("Detected Anomalies")
st.write(anomalies)