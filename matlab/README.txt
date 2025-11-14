S Arbogast
Adaptive Channel Equalizer


MATLAB Script 1) float_point_model.m
This script models a 12 tap adaptive channel fitler usign least squares method in floatign point values. 

Inputs: all variable are set in the 'init' section
	parameter | type  | discription                 | default
	L         | int   | length of training sequence | 1012
	seed      | int   | seed for randi()            | 3
	n         | array | length of channel model     | 3
	beta      | float | channel bandwidth           | 3.0
	sd        | float | standard deviation of noise | 0.01
	mean      | float | mean of noise               | 0.0
	mu        | float | filter convergence rate     | 0.07
	taps      | int   | adaptive filter size        | 12
	tolerance | float | convergence range           | 0.1
	
The remainder of the script with run the floating point model, plot nessasry data, and save a .mat file of inputs and results. 

Outputs: 
	- Time plot and eye diagram of d, training sequence 
	- Time plot and eye diagram of u, corrupted sequence 
	- Time plot of error vector
	- Time plot of d hat
	- Eye diagram of converged d hat values
	- Impulse response of channel
	- Frequency and phase of channel
	- Impulse response of final fitler values w
	- Frequency and phase of final filter values
	
	- Print to consol
		- conv_val: esitmated convergence point of d hat
		- SNR_RX: SNR of corrupted sequence u
		- SNR_Eq: SNR of convereged values of d hat
		- final values of adaptive filter coeffiecents
	
	- Save to floating_point_ref.mat
		- Parmaters: l, seed, n, beta, sd, mean, mu, taps, 
		- computations: delay, d, u, d_hat, e_vec, w_vec, SNR_Rx, SNR_Eq, conv_val
		
		
MATLAB Script 2) fixed_point_model.m
This script models the 12 tap adaptive equalizer from floating_point_model.m in an integer based fixed point representation.  

Inputs: all variable are set in the 'init' section. The model loads the saved file 'floatign_point_ref.mat' to bring in identical parameters, ensuring accurate comparison. 

	parameter | type  | discription                                 | default
	word_size | int   | bits per word                               | 16
	M         | int   | bit shift of d hat computation 1/2^M = >> M | 14
	N         | int   | bit shift of e_vec computaion 1/2^N = >> N  | 15
	mu_bits   | int   | bit size equivlent of mu 1/2^(mu_bits)      | 4
	
The remiander of the script runs the fixed point model, generates results and plot, comparies the model to the floating point and saves resutls. 

Outputs: 
	- valid(): booling array of validation tests
	- Time and eye diagram of integer d 
	- Time and eye diagram of integer u
	- Time plot of integer error vector e
	- Time plot of integer d hat
	- Eye diagram of converged values of d hat
	- normalized comparison of float and fixed error vector
	- normalized comparison of float and fixed d hat 
	- normalized comparison of float and fixed w vector
	- comparison of float and fixed w vector frequency response 
	
	-Print to consol
		- conv_val: estimated convergance point of d hat 
		- SNR_RX: SNR of corrupted sequence u
		- SNR_Eq: SNR of convereged values of d hat
		- final values of adaptive filter coeffiecents
		
	- Save to floating_point_ref.mat
		- Parmaters: word_size, M, N, mu_bits 
		- computations: d_int16, u_int16, d_hat_int16, w_vec_int16, SNR_Rx, SNR_Eq,
				conv_val, error_w, error_evec, error_dhat
	