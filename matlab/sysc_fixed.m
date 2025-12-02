% sysC_float.m
%
% S Arbogast
%
% script to run and cmpare systemC floating point implementation
%   Loads data from 
%           - floating_point_model.m
%               - floating_point_ref.mat
%           - fixed_point_model.m
%                - fixed_point_ref.mat
%
%   writes dn and un to txt 
%
%   run systemC model
%   bring sysC outputs dhatn.txt, en.txt, and w.txt into local folder 
%   script will read in values and run comparison
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%% init
clear; close all;
load("floating_point_ref.mat");
load("fixed_point_ref.mat");


%% write dn, un
xn_fid = fopen('dn_int.txt','w');
fprintf(xn_fid,'%d\n',[length(d_int16); d_int16']);% writes sample length first; writes 30 decimal places, 1 sample per line
fclose(xn_fid);

xn_fid = fopen('un_int.txt','w');
fprintf(xn_fid,'%d\n',[length(u_int16); u_int16']);% writes sample length first; writes 30 decimal places, 1 sample per line
fclose(xn_fid);

%% read dhat, en, w
% ensure dhatn.txt, en.txt, and w.txt have been placed locally
dhat_SC_raw = load("dhatn_int.txt");
dhat_SC = dhat_SC_raw(1:length(d_hat));
dhat_SC_raw32 = load("dhatn_int32.txt");
dhat_SC32 = dhat_SC_raw32(1:length(d_hat));
en_SC_raw = load("en_int.txt");
en_SC = en_SC_raw(1:length(e_vec));
w_SC = load("w_int.txt");

%% error

error_dhat = sum((d_hat_int16-dhat_SC').^2)
error_evec = sum((e_vec_int16-en_SC').^2)
error_w = sum((w_vec_int16-w_SC).^2)

%% plot
% d hat
figure
tiledlayout(2,1)
nexttile
plot(d_hat_int16,'-o')
hold on
plot(dhat_SC,"-x")
legend("ML", "sysC")
title(' Comparison of Fixed-Point $\hat{d}$',fontsize=14,Interpreter='latex')
xlabel('Magnitude')
ylabel('Sample [n]')
lim = ylim;
txt = sprintf("Squared Error: %d",error_dhat);
text(0,2*lim(1),txt,"FontSize",16);

%% plot
% error vector
figure
tiledlayout(2,1)
nexttile
plot(e_vec_int16,'-o')
hold on
plot(en_SC,"-x")
legend("ML", "sysC")
title(' Comparison of Fixed-Point Error Vector $e$ ',fontsize=14,Interpreter='latex')
xlabel('Magnitude')
ylabel('Sample [n]')
lim = ylim;
txt = sprintf("Squared Error: %d",error_evec);
text(0,2*lim(1),txt,"FontSize",16);

%% plot
% w coef
figure
tiledlayout(2,1)
nexttile
plot(w_vec_int16,'-o')
hold on
plot(w_SC,"-x")
legend("ML", "sysC")
title(' Comparison of Fixed-Point Coefficiants $\mathbf{\vec{w}}$',fontsize=14,Interpreter='latex')
xlabel('Magnitude')
ylabel('Sample [n]')
lim = ylim;
txt = sprintf("Squared Error: %d",error_w);
text(0,2*lim(1),txt,"FontSize",16);

%% print 
disp('error vector: first 10 samples');
[e_vec_int16(1:10)' en_SC(1:10)]

disp('d hat: first 10 samples')
[d_hat_int16(1:10)' dhat_SC(1:10)]

disp('Final W coef:')
[w_vec_int16; w_SC]

%% perfomance 
% snr
SNR_Eq_SC = snr_db(d_int16(conv_val:end-delay+1)',dhat_SC(conv_val+delay-1:end))

figure
eyeplot(dhat_SC(conv_val+delay-1:end));
title('Eye Diagram of Fixed-Point SystemC Covereged Waveform $\hat{d}$',fontsize=14,Interpreter='latex')


%% functions
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