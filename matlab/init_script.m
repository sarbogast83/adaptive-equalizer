% S Arbogast
% 4 Nov 2025
% implement floating point adaptive equilizer using LMS

%% init

L = 1012; %sequnce length
rng(3); % seed randi

% channel
n = [1 2 3];
beta = 3.0;

%noise
sd = 0.2;
mean = 0;

%qualizer
mu = 0.03; 
taps = 12;

%% run system
d = 2*randi([0,1],1,L)-1; % traingin sequence {-1,1}
h = channel_impulse(n,beta);
v = sd .* rand(1,L) + mean; %gausse noise
u = filter(h,1,d) + v;
% u = filter(h,1,d);

% fitler
u_vec = zeros(1,taps);
w_vec = zeros(1,taps);
d_vec = zeros(1,taps);
d_hat = zeros(1,L);
e_vec = zeros(1,L);

for i = 1:length(d)
    d_vec = [d(i) d_vec(1:end-1)];
    u_vec = [u(i) u_vec(1:end-1)];
    d_hat(i) = sum(w_vec.*u_vec);
    e_vec(i) = d_vec(6)-d_hat(i);

    w_vec = w_vec + mu*u_vec*e_vec(i);
end

%% plots
% plot d
close all;
offset = 0; % for eye diagram
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
close all;
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




%% functions
function hn = channel_impulse(n,b)
    hn = zeros(1,length(n));
    for i = 1:length(n)
        hn(i) = 0.5*(1+cos((2*pi*(n(i)-length(n)+1)/b)));
    end
end

% eye diagram 
    % adapted form Lathi for 1 sps sigs
        % onedsignal: one dimentional time signal
        % Npeye: eye width in units of T
        % NSampT: samples per symbol
        % Toffset:symbol offset
        % function eyesuccess=eyeplot(onedsignal,Toffset)
        %     Npeye = 3; 
        %     NsampT = 1;
        %     Noff=floor(Toffset*NsampT);
        %     x_samples = [-1 0 1]; 
        %     Lperiod=floor((length(onedsignal)-Noff)/(Npeye*NsampT));
        %     Lrange=Noff+1:Noff+Lperiod*Npeye*NsampT;
        %     mdsignal=reshape(onedsignal(Lrange),[Npeye*NsampT Lperiod]);
        %     plot(x_samples,mdsignal,'k')
        %     y_max = max(onedsignal);
        %     y_min = min(onedsignal);
        %     axis([-1.05 1.05 y_min-.05 y_max+.05])% hadcoded x lims 
        % 
        %     xlabel('Sample [n]')
        %     ylabel('Magnitude [V]')
        %     eyesuccess=1;
        %     return
        % end
        function eyesuccess=eyeplot(onedsignal)
            shift = 3;
            x_samples = [-1 0 1]; 
            eye_array = zeros(length(onedsignal)-shift+1,shift);
            for i = 1:(length(onedsignal)-shift+1)
                eye_array(i,:) = onedsignal(i:(i+shift-1));
            end
            plot(x_samples,eye_array,'k')
            y_max = max(onedsignal);
            y_min = min(onedsignal);
            axis([-1.05 1.05 y_min-.05 y_max+.05])% hadcoded x lims 
           
            xlabel('Sample [n]')
            ylabel('Magnitude [V]')
            eyesuccess=1;
            return
        end