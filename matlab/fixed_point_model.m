% S Arbogast
% 6 Nov 2025
% fixed_point_model.m
% 

%% init
clear;
load("floating_point_ref.mat");
word_size = 16;


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

M = 14; % d hat scale
N = 15; % coef scale
for i = 1:length(d)
    d_vec_int = [d_int16(i) d_vec_int(1:end-1)];
    u_vec_int = [u_int16(i) u_vec_int(1:end-1)];
    d_hat_int32(i) = sum(w_vec_int16.*u_vec_int);
    d_hat_int16(i) = d_hat_int32(i)/(2^M);
    e_vec_int16(i) = d_vec_int(delay)-d_hat_int16(i);
    ue_int32 = u_vec_int*e_vec_int16(i);
    w_vec_int16 = w_vec_int16 + ue_int32/(2^(5+N));
    
end

%% validate outputs
valid(3) = validate(d_hat_int16,word_size);
valid(4) = validate(e_vec_int16,word_size);
valid(5) = validate(w_vec_int16,word_size);
valid(6) = validate(ue_int32,32);
valid(7) = validate(d_hat_int32,32);

%% plots
close all;
figure
max_word = 2^(word_size-1)-1
yline([max_word -1*max_word],'--r')
hold on 
plot(w_vec_int16)

figure
plot(e_vec_int16)

figure
norm_w_int = w_vec_int16/(max(abs(w_vec_int16)));
norm_w = w_vec/(max(abs(w_vec)));
freqz(norm_w,1)
hold on 
freqz(norm_w_int,1);

%% functions
% conservative scalling to reduce overflow
function x_hat = m_scale(x, word_size, m)
    scale = (2^(word_size-m-1))-1;
    norm = x/(max(abs(sig)));
    b = scale * norm;
    x_hat = floor(b);
end

function valid = validate(sig,word_size)
    max_bit = (log2(max(abs(sig))));
    if max_bit <= word_size-1
        valid = true;
    else
        valid = false;
    end
end