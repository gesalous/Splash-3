import matplotlib.pyplot as plt

# Data for the second plot
processes = [1, 2, 4, 8, 16]
spin_lock_water_nsquared_times = [45, 24, 13, 7, 3]
mcs_lock_water_nsquared_times = [44, 23, 13, 6, 4]

# Calculate speedup
spin_lock_water_nsquared_speedup = [spin_lock_water_nsquared_times[0] / time for time in spin_lock_water_nsquared_times]
mcs_lock_water_nsquared_speedup = [mcs_lock_water_nsquared_times[0] / time for time in mcs_lock_water_nsquared_times]
ideal_speedup = processes  # Ideal speedup is linear with the number of processes

# Plot
plt.figure()
plt.plot(processes, spin_lock_water_nsquared_speedup, marker='o', label='Spin Lock Water N^2')
plt.plot(processes, mcs_lock_water_nsquared_speedup, marker='s', label='MCS Lock Water N^2')
plt.plot(processes, ideal_speedup, 'r--', label='Ideal Speedup')  # Ideal speedup line

# Labels and title
plt.xlabel('Number of Processes')
plt.ylabel('Speedup')
plt.title('Speedup vs Number of Processes')
plt.legend()
plt.grid(True)

# Save to PDF
plt.savefig('water_nsquared_speedup.pdf')
