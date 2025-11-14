% S Arbogast
% 4 Nov 2025
% floating_point_model.m
% implement floating point adaptive equilizer using LMS

%% init
clear; close all;
L = 1012; %sequnce length

% channel
n = [1 2 3]; % channel length
beta = 3.0; % channel bandwidth

%noise
sd = 0.01; % standard deviasion AWGN
mean = 0; % mean of AWGN

%qualizer
mu = 0.03; % convergance rate [0.01, 0.1]
taps = 12; % adaptive FIR filter tap count

%convergnace
tolerance = 0.1; % convergance test range 

%% run system

delay = ceil(taps/2);
d = 2*randi([0,1],1,L)-1; % traingin sequence {-1,1}
h = channel_impulse(n,beta);
v = sd .* rand(1,L) + mean; %gausse noise
u = filter(h,1,d) + v;

% fitler
u_vec = zeros(1,taps);
w_vec = zeros(1,taps);
d_vec = zeros(1,taps);
d_hat = zeros(1,L);
e_vec = zeros(1,L);

% run filter system
for i = 1:length(d)
    d_vec = [d(i) d_vec(1:end-1)];
    u_vec = [u(i) u_vec(1:end-1)];
    d_hat(i) = sum(w_vec.*u_vec);
    e_vec(i) = d_vec(delay)-d_hat(i);

    w_vec = w_vec + mu*u_vec*e_vec(i);
end

%% plots
% plot d
close all;
t = 0:(L-1);
figure
eyeplot(d);
title('Eye Diagram of Original Waveform')
figure
stem(t,d,"filled")
title("Sample Series of Original Waveform")
ylabel('Amplitude')
xlabel('Samples [n]')

%% plots
% plot u
offset = 0; % for eye diagram
t = 0:(L-1);
figure
eyeplot(u);
title('Eye Diagram of Corrupted Waveform')
figure
stem(t,u,"filled")
title("Sample Series of Corrupted Waveform")
ylabel('Amplitude')
xlabel('Samples [n]')

%% plots
% error
figure
plot(t,e_vec,LineWidth=1)
title('Floating Point Error Vector')
xlabel('Samples [n]')
ylabel('Magnitude')

%% plots
%recovered
conv_val = find_conv_sample(e_vec,tolerance)
conv_sig = d_hat(conv_val:end);

figure
eyeplot(conv_sig);
title('Eye Diagram of Covereged Waveform $\hat{d}$','Interpreter','latex')
figure
stem(t,d_hat,"filled")
title("Sample Series of $\hat{d}$ Waveform",'Interpreter','latex')
ylabel('Amplitude')
xlabel('Samples [n]')

%% plots
% channel
figure
stem(h,'filled',LineWidth=2)
title("Channel Impulse Response")
ylabel('Magnitude')
xlabel('Sample [n]')
xlim([0 4])
ylim([0 1.1])

figure
freqz(h,1)
title("Channel Frequency Response")

%% plots
% w coef
figure
stem(w_vec,"filled",LineWidth=2)
title("Adaptive Filter Impulse Response ")
ylabel("Magnitude")
xlabel('Sample [n]')
xlim([0 12])

figure
freqz(w_vec,1)
title("Adaptive Filter Frequency Response")

%% metrics
SNR_Rx = snr_db(d,u)
SNR_Eq = snr_db(d(conv_val:end-delay+1),d_hat(conv_val+delay-1:end))
disp("coef"); w_vec'

%% save
save('floating_point_ref',"L", 'seed', 'n', 'beta',"sd","mean","mu", ...
    "taps","delay","d","u","d_hat","e_vec","w_vec","SNR_Eq","SNR_Rx", ...
    "conv_val");


%% functions
function hn = channel_impulse(n,b)
    hn = zeros(1,length(n));
    for i = 1:length(n)
        hn(i) = 0.5*(1+cos((2*pi*(n(i)-length(n)+1)/b)));
    end
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

% convergance
function sample_num = find_conv_sample(conv_vec,tolerance)
    last_val = conv_vec(end);
    diff_array = abs(conv_vec-last_val);
    not_conv = find(diff_array>tolerance);
    sample_num = not_conv(end)+1;
end

% compute snr between Tx and Rx
function snr_db = snr_db(tx, rx)
    sig_power = sum(abs(tx).^2);
    noise_power = sum(abs((tx-rx)).^2);
    snr = sig_power/noise_power;
    snr_db = 10*log10(snr);
end