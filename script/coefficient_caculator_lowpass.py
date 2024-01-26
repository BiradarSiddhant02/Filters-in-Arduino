import scipy.signal

# Analog filter specifications
analog_b = list()  # Numerator coefficients of analog filter
analog_a = list()

analog_b, analog_a = scipy.signal.butter(2, 100, 'low', analog = True)

# Sampling frequency and desired digital filter specifications
fs = 1000  # Sampling frequency in Hz
digital_cutoff_frequency = 100  # Digital filter cutoff frequency in Hz

# Convert analog filter to digital filter using bilinear transform
digital_b, digital_a = scipy.signal.bilinear(analog_b, analog_a, fs)

# Create a TransferFunction object for the digital filter
digital_tf = scipy.signal.TransferFunction(digital_b, digital_a, dt=1/fs)

# Display the digital filter coefficients
formatted_b = ", ".join(f"{value:.8e}" for value in digital_b)
formatted_a = ", ".join(str(value) for value in digital_a)

print(f"double b[] = {{{formatted_b}}};")
print(f"double a[] = {{{formatted_a}}};")

