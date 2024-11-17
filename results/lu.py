import matplotlib.pyplot as plt

# Data for the new plot
processes = [1, 2, 4, 8, 16]
spin_lock_lu_times = [71, 36, 18, 9, 5]
mcs_lock_lu_times = [70, 36, 18, 10, 6]

# Calculate speedup
spin_lock_lu_speedup = [spin_lock_lu_times[0] / time for time in spin_lock_lu_times]
mcs_lock_lu_speedup = [mcs_lock_lu_times[0] / time for time in mcs_lock_lu_times]
ideal_speedup = processes  # Ideal speedup is linear with the number of processes

# Plot
plt.figure()
plt.plot(processes, spin_lock_lu_speedup, marker='o', label='Spin Lock LU')
plt.plot(processes, mcs_lock_lu_speedup, marker='s', label='MCS Lock LU')
plt.plot(processes, ideal_speedup, 'r--', label='Ideal Speedup')  # Ideal speedup line

# Labels and title
plt.xlabel('Number of Processes')
plt.ylabel('Speedup')
plt.title('Speedup vs Number of Processes for LU')
plt.legend()
plt.grid(True)

# Save to PDF
plt.savefig('lu_speedup.pdf')
