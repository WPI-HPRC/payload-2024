import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd


def replace_negatives_with_previous(series):
    # Create a copy to avoid the SettingWithCopyWarning
    series = series.copy()
    for i in range(1, len(series)):
        if series[i] < 0:
            series[i] = series[i - 1]
    return series



# Function to animate 3D points
def animate_3d(x_points, y_points, z_points, timestamps):
    # Ensure inputs are NumPy arrays
    x_points = np.array(x_points)
    y_points = np.array(y_points)
    z_points = np.array(z_points)
    timestamps = np.array(timestamps)

    if len(x_points) != len(y_points) or len(y_points) != len(z_points) or len(z_points) != len(timestamps):
        raise ValueError("All input arrays must have the same length.")

    # Create a 3D plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")
    ax.set_xlim(min(x_points), max(x_points))
    ax.set_ylim(min(y_points), max(y_points))
    ax.set_zlim(min(z_points), max(z_points))
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")

    # Initialize the scatter plot and trail line
    scatter = ax.scatter([], [], [], c="red", s=50)
    trail, = ax.plot([], [], [], c="blue", linewidth=2)

    # Add a text element for displaying timestamps
    timestamp_text = ax.text2D(0.05, 0.95, "", transform=ax.transAxes, fontsize=12, color="blue")

    # Update function for animation
    def update(frame):
        # Update scatter plot for the current point
        scatter._offsets3d = ([x_points[frame]], [y_points[frame]], [z_points[frame]])

        # Update the trail line to include all points up to the current frame
        trail.set_data(x_points[:frame + 1], y_points[:frame + 1])
        trail.set_3d_properties(z_points[:frame + 1])

        # Update the timestamp text
        timestamp_text.set_text(f"Timestamp: {timestamps[frame]}")

        return scatter, trail, timestamp_text

    # Animate
    frames = len(x_points)
    ani = FuncAnimation(fig, update, frames=frames, interval=0.5, blit=False)

    # Explicitly refresh the figure during animation
    plt.draw()
    plt.show()

def animate_3d_with_gps(x_points, y_points, z_points, timestamps, gpsLat, gpsLong):
    # Ensure inputs are NumPy arrays for calculations
    x_points = np.array(x_points, dtype=float)
    y_points = np.array(y_points, dtype=float)
    z_points = np.array(z_points, dtype=float)
    gpsLat = np.array(gpsLat, dtype=float)
    gpsLong = np.array(gpsLong, dtype=float)
    timestamps = np.array(timestamps)

    # Validate inputs
    n = len(x_points)
    if len(y_points) != n or len(z_points) != n or len(gpsLat) != n or len(gpsLong) != n or len(timestamps) != n:
        raise ValueError("All input arrays must have the same length.")

    # Create a figure with subplots
    fig = plt.figure(figsize=(12, 8))
    ax_3d = fig.add_subplot(121, projection="3d")
    ax_gps = fig.add_subplot(122)

    # Configure the 3D plot
    ax_3d.set_xlim(min(x_points), max(x_points))
    ax_3d.set_ylim(min(y_points), max(y_points))
    ax_3d.set_zlim(min(z_points), max(z_points))
    ax_3d.set_xlabel("X")
    ax_3d.set_ylabel("Y")
    ax_3d.set_zlabel("Z")

    # Configure the GPS plot
    ax_gps.set_title("GPS Latitude vs Longitude")
    ax_gps.set_xlabel("Longitude")
    ax_gps.set_ylabel("Latitude")
    ax_gps.set_xlim(min(gpsLong), max(gpsLong))
    ax_gps.set_ylim(min(gpsLat), max(gpsLat))

    # Initialize the 3D scatter plot and trail
    scatter_3d = ax_3d.scatter([], [], [], c="red", s=50)
    trail_3d, = ax_3d.plot([], [], [], c="blue", linewidth=2)

    # Initialize the GPS trail plot
    trail_latlong, = ax_gps.plot([], [], c="green", linewidth=2, label="Lat vs Long")
    point_latlong = ax_gps.scatter([], [], c="orange", s=50, label="Current Point")

    # Add a legend for the GPS plot
    ax_gps.legend()

    # Add a text element for displaying timestamps
    timestamp_text = ax_3d.text2D(0.05, 0.95, "", transform=ax_3d.transAxes, fontsize=12, color="blue")

    # Update function for animation
    def update(frame):
        # Update 3D scatter and trail
        scatter_3d._offsets3d = ([x_points[frame]], [y_points[frame]], [z_points[frame]])
        trail_3d.set_data(x_points[:frame + 1], y_points[:frame + 1])
        trail_3d.set_3d_properties(z_points[:frame + 1])

        # Update GPS trail
        trail_latlong.set_data(gpsLong[:frame + 1], gpsLat[:frame + 1])
        point_latlong.set_offsets([[gpsLong[frame], gpsLat[frame]]])

        # Update timestamp
        timestamp_text.set_text(f"Timestamp: {timestamps[frame]}")

        return scatter_3d, trail_3d, trail_latlong, point_latlong, timestamp_text

    # Animate
    frames = n
    ani = FuncAnimation(fig, update, frames=frames, interval=50, blit=False)

    plt.tight_layout()
    plt.show()


# Example input data
flightdata = pd.read_csv("flightdata11.csv")
flightdata = flightdata.query("gpsLat != 0")
flightdata = flightdata.query("altitude > -100")
flightdata = flightdata.query("timestamp > 5067763")
print(min(flightdata["altitude"]))

x = flightdata["gpsLat"]  # Example x points
y = flightdata["gpsLong"]  # Example y points
z = flightdata["altitude"]  # Example z points
timestamps = flightdata["timestamp"]  # Example timestamps
print(
    "max x: ",
    max(x),
    "min x: ",
    min(x),
    "max y: ",
    max(y),
    "min y: ",
    min(y),
    "max z: ",
    max(z),
    "min z: ",
    min(z),
)

# Call the function to animate
animate_3d_with_gps(x, y, z, timestamps,x,y)
