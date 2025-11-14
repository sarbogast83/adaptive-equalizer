% S Arbogast
% 6 Nov 2025
% fixed_point_model.m
% ficed point model adaptation of adatptive channel equalizer
% models fixed point based on floating_point_model.m 
% tests for overflow, plot and save resutls, compare models

%% init
clear; close all;
load("floating_point_ref.mat");

word_size = 16;
M = 14; % d hat scale
N = 15; % coef scale
mu_bits = 5; % bit representaion of mu= 1/2^(mu_bits)

%% scale received signal
u_max = max(abs(u));
scale_factor = (2^15-1)/u_max;
d_int16 = round(d*scale_factor);
valid(1) = validate(d_int16,word_size);
u_int16 = round(u*scale_factor);
valid(2) = validate(u_int16,word_size);

%% system
% fitler
u_vec_int = zeros(1,taps);
w_vec_int16 = zeros(1,taps);
d_vec_int = zeros(1,taps);
d_hat_int16 = zeros(1,L);
d_hat_int32 = zeros(1,L);
e_vec_int16 = zeros(1,L);
ue_int32 = zeros(1,taps);


for i = 1:length(d)
    d_vec_int = [d_int16(i) d_vec_int(1:end-1)];
    u_vec_int = [u_int16(i) u_vec_int(1:end-1)];
    d_hat_int32(i) = sum(w_vec_int16.*u_vec_int);
    d_hat_int16(i) = floor(d_hat_int32(i)/(2^M));
    e_vec_int16(i) = d_vec_int(delay)-d_hat_int16(i);
    ue_int32 = u_vec_int*e_vec_int16(i);
    w_vec_int16 = w_vec_int16 + floor(ue_int32/(2^(mu_bits+N)));
    
end

%% validate outputs
valid(3) = validate(d_hat_int16,word_size);
valid(4) = validate(e_vec_int16,word_size);
valid(5) = validate(w_vec_int16,word_size);
valid(6) = validate(ue_int32,32);
valid(7) = validate(d_hat_int32,32);
if sum(valid) ~= size(valid)
    disp('OVERFLOW ERROR!')
    valid
    return;
end

%% verificaiton of M, N, mu for overflow
% word size verification
close all;
figure
max_word = 2^(word_size-1)-1
yline([max_word -1*max_word],'--r')
hold on 
plot(w_vec_int16)

figure
yline([max_word -1*max_word],'--r')
hold on 
plot(e_vec_int16)
% 
% figure
% norm_w_int = w_vec_int16/(max(abs(w_vec_int16)));
% norm_w = w_vec/(max(abs(w_vec)));
% freqz(norm_w,1)
% hold on 
% freqz(norm_w_int,1);

%% plot
% d_int
close all;
t = 0:(L-1);
figure
eyeplot(d_int16);
title('Eye Diagram of Original Integer Waveform')

figure
stem(t,d_int16,"filled")
title("Sample Series of Original Integer Waveform")
ylabel('Amplitude')
xlabel('Samples [n]')

%% plots
% plot u
figure
eyeplot(u_int16);
title('Eye Diagram of Corrupted Integer Waveform')
figure
stem(t,u_int16,"filled")
title("Sample Series of Corrupted Integer Waveform")
ylabel('Amplitude')
xlabel('Samples [n]')

%% plots
% error
figure
plot(t,e_vec_int16)
title('Error Vector of Fixed Point Implementation')
xlabel('Samples [n]')
ylabel('Magnitude')

%% plots
%recovered
tolerance = floor(0.1*(2^(word_size-1)));
conv_val = find_conv_sample(e_vec_int16,tolerance)
conv_sig = d_hat_int16(conv_val:end);

figure
eyeplot(conv_sig);
title('Eye Diagram of Covereged Integer Waveform')
figure
stem(t,d_hat_int16,"filled")
title("Sample Series of d hat Integer Waveform")
ylabel('Amplitude')
xlabel('Samples [n]')

%% norm comparison 
% normalize
norm_d_int = d_hat_int16/max(abs(d_hat_int16));
norm_e_int = e_vec_int16/max(abs(e_vec_int16));
norm_w_int = w_vec_int16/max(abs(w_vec_int16));
norm_d = d_hat/max(abs(d_hat));
norm_e = e_vec/max(abs(e_vec));
norm_w = w_vec/max(abs(w_vec));

% compute error
error_dhat = sum((norm_d-norm_d_int).^2)
error_evec = sum((norm_e-norm_e_int).^2)
error_w = sum((norm_w-norm_w_int).^2)

figure
tiledlayout(2,1);
nexttile
stem(t,norm_d,"filled")
hold on 
stem(t,norm_d_int)
title('Comparison of Float and Fixed Implementation')
subtitle('$\hat{d}$','fontsize',14,'Interpreter','latex')
legend("Float","Fixed")
txt = sprintf("Squared Error: %d",error_dhat);
text(0,-2,txt);

figure
tiledlayout(2,1);
nexttile
plot(norm_e,'LineWidth',2)
hold on 
plot(norm_e_int)
title('Comparison of Float and Fixed Implementation')
subtitle('Error Vector')
legend("Float","Fixed")
txt = sprintf("Squared Error: %d",error_evec);
text(0,-2,txt);

figure
tiledlayout(2,1);
nexttile
plot(norm_w,'-x','LineWidth',2)
hold on 
plot(norm_w_int,'-o')
title('Comparison of Float and Fixed Implementation')
subtitle('Filter Coeffients')
legend("Float","Fixed")
txt = sprintf("Squared Error: %d",error_w);
text(0,-1,txt);

figure
freqz(norm_w,1)
hold on 
freqz(norm_w_int,1)
title("Comparison of Float and Fixed Implementation")
subtitle("Frequency")

%% metrics
SNR_Rx = snr_db(d_int16,u_int16)
SNR_Eq = snr_db(d_int16(conv_val:end-delay+1), ...
    d_hat_int16(conv_val+delay-1:end))
disp("coef"); w_vec_int16'

%% Save 
save('fixed_point_ref',"word_size","M","N","mu_bits","SNR_Eq","SNR_Rx", ...
    "conv_val","d_int16","u_int16","d_hat_int16","w_vec_int16", ...
    "error_w","error_evec","error_dhat");

%% functions


function valid = validate(sig,word_size)
    max_bit = (log2(max(abs(sig))));
    if max_bit <= word_size-1
        valid = true;
    else
        valid = false;
    end
end

function sample_num = find_conv_sample(conv_vec,tolerance)
    last_val = conv_vec(end);
    diff_array = abs(conv_vec-last_val);
    not_conv = find(diff_array>tolerance);
    sample_num = not_conv(end)+1;
end

% eye diagram
function eyesuccess=eyeplot(onedsignal)
    shift = 3;
    x_samples = [-0.5 0 0.5]; 
    eye_array = zeros(length(onedsignal)-shift+1,shift);
    for i = 1:(length(onedsignal)-shift+1)
        eye_array(i,:) = onedsignal(i:(i+shift-1));
    end
    plot(x_samples,eye_array,'k')
    y_max = max(onedsignal);
    y_min = min(onedsignal);
    axis([-.55 .55 y_min-.05 y_max+.05])% hadcoded x lims 
   
    xlabel('Sample [n]')
    ylabel('Magnitude [V]')
    eyesuccess=1;
end

% compute snr between Tx and Rx
function snr_db = snr_db(tx, rx)
    sig_power = sum(abs(tx).^2);
    noise_power = sum(abs((tx-rx)).^2);
    snr = sig_power/noise_power;
    snr_db = 10*log10(snr);
end