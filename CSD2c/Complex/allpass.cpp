#include <iostream>
#include <vector>

using namespace std;

// FIR allpass filter function
vector<double> fir_allpass_filter(vector<double> signal, vector<double> taps) {
    int n = signal.size();        // number of input samples
    int m = taps.size();          // number of filter taps
    vector<double> filtered_signal(n + m - 1, 0);  // initialize filtered signal vector
    cout << "Initializing filtered signal vector" << endl;

    vector<double> delay_line(m, 0);    // initialize delay line with m taps
    cout << "Initializing delay lilne" << "\n" << endl;

    // Loop over each sample of the input signal
    for (int i = 0; i < n + m - 1; i++) {
        double y = 0;

        // If the current sample is within the range of the input signal
        if (i < n) {
            delay_line[0] = signal[i];   // add the current sample to the delay line
            cout << "Delay_line[0] = " << signal[i] << endl;
        }
        cout << "\n" << endl;

        // Compute the filter output by multiplying each tap with its corresponding delayed input sample
        for (int j = 0; j < m; j++) {
            y += taps[j] * delay_line[j];
            cout << "Multiplying tap[" << j << "] = " << taps[j] << " with delay_line[" << j << "] = " << delay_line[j] << "    Result = " << taps[j] * delay_line[j] << "\n" << endl;
        }
        cout << "output = " << y << endl;
        cout << "\n" << endl;

        // Shift the delay line
        for (int j = m - 1; j >= 1; j--) {
            delay_line[j] = delay_line[j-1];
            cout << "Delay_line[" << j << "] = " << delay_line[j-1] << endl;
        }
        cout << "\n" << endl;

        filtered_signal[i] = y;    // store the output sample
        cout << "Store output sample " << i << " with value " << y << endl;
    }
    cout << "\n" << endl;

    return filtered_signal;    // return the filtered signal
}

int main() {
    // Example usage
    vector<double> signal = {1.0, 2.0, 3.0, 4.0, 5.0};    // Input signal
    vector<double> taps = {0.25, -0.5, 0.25};            // Filter taps

    cout << "Using input signal: ";

    for (double x : signal)
        cout << x << " ";
    cout << "\n" << endl;

    cout << "Using filter coefs: ";

    for (double f : taps)
        cout << f << " ";
    cout << "\n" << endl;

    vector<double> filtered_signal = fir_allpass_filter(signal, taps);    // Apply filter to input signal
    
    cout << "filtered signal: ";

    // Print the filtered signal
    for (double y : filtered_signal) {
        cout << y << " ";
    }
    cout << endl;

    return 0;
}
