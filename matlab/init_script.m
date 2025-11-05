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
sd = 0.01;
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
hold on
plot(e_vec)


% functions
function hn = channel_impulse(n,b)
    hn = zeros(1,length(n));
    for i = 1:length(n)
        hn(i) = 0.5*(1+cos((2*pi*(n(i)-length(n)+1)/b)));
    end
end