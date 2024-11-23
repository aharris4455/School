%% Comm.Sys.660 HW3 
%Aukusti Harris 
clear all, close all

R = 8; %Decimation Factor
fs_in = 61.44e6; %Sampling rate
B = 3e6; %Bandwidth
Fs_out = fs_in/R; %Output samling rate
F_pass = Fs_out/4; %Passband edge (Quarter of output sampling rate)
A = [1,0]; %Targeted Passband and stopband amplitudes
rp = 0.1;  %Passband ripple (dB) 
rs = 60;   %Stopband attenuation (dB)
%Passband and stopband ripple values (linear)
DEV = [(10^(rp/20)-1)/(10^(rp/10)+1), 10^(-rs/20)]; 

%%
%FIR Decimaitor Case A 
disp('Case A: All aliased spectral components are attenuated')
F_stop = Fs_out/2; %Stopband edge (half the output samp. rate)
F = [F_pass, F_stop]; %Band edges
[ord, Fo, Ao, W] = firpmord(F,A,DEV,fs_in);
[b, err] = firpm(ord, Fo, Ao, W);
%Iteration to get the correct passband ripple
erro = err;
while erro > DEV(1)
    ord = ord+1;
    [b, erro] = firpm(ord,Fo, Ao, W);
    BFinal = b;
    orde = ord;
    disp([orde, erro]);
end
while err <= DEV(1)
    orde = ord;
    ord = ord-1;
    BFinal = b;
    [b, err] = firpm(ord, Fo, Ao, W);
    disp([ord, err]);
end
figure;
freqz(b,1,0:1:Fs_out,fs_in);
%axis([0, Fs_out,-90,0]);
title('Frequency Response, Case A');
disp('Desired err: ')
disp(DEV(1));
disp(DEV(2));
disp('ord, err:');
disp([ord, err]);
figure;
stem(b);
%% Case C
disp('Case C: Transition band aliasing is allowed');

F_stop = Fs_out - F_pass; 
F = [F_pass, F_stop];
[ord, Fo, Ao, W] = firpmord(F,A,DEV,fs_in);
[b, err] = firpm(ord, Fo, Ao, W);
disp('ord, err: ');
disp([ord err]);

%Iteration to get the correct passband ripple
erro = err;
while erro > DEV(1)
    ord = ord+1;
    [b, erro] = firpm(ord,Fo, Ao, W);
    BFinal = b;
    orde = ord;
    disp([orde, erro]);
end
while err <= DEV(1)
    orde = ord;
    ord = ord-1;
    BFinal = b;
    [b, err] = firpm(ord, Fo, Ao, W);
    disp([ord, err]);
end

figure;
freqz(BFinal,1,0:1:Fs_out, fs_in);
title('Freqency Response, Case C');
figure;
stem(BFinal);
%% 2. CIC Filter
K = 1:1:5; %Order
M = 1; %Samples per stage
f = linspace(0, fs_in/2, 1000);
f_norm = f./fs_in;
nquist_zone = Fs_out/2; 
passband_limit = 1.5e6;
%cicDec = dsp.CICDecimator(R,M,K(3));
%fvtool(cicDec);
figure;
for i = 1:length(K)
    h_z = CIC_freq_res(f_norm, R, K(i));
    h_db = 20*log10(abs(h_z));
    plot(f/1e6, h_db);
    grid on; 
    hold on;
end
axis([0 35 -200 100])
title('CIC Filter Frequency Response for Order N = 1:5');
legend('N=1', 'N=2', 'N=3', 'N=4', 'N=5');
xlabel('Frequency (MHz)');
ylabel('Magnitude (dB)');
xline(nquist_zone/1e6, '--r', 'Alias zone start');
xline(passband_limit/1e6, '--b', 'Passband limit'); 
yline(-60, '--g', 'Attenuation');
legend show;
hold off; 
function h_z = CIC_freq_res(f,R,N)
    % f = Vector of normalized freqs
    % R = Decimation factor
    % N = order
    % h_z = Freq. res. of CIC filter (linear)
    h_z = (sin(pi * f* R) ./ sin(pi * f)).^N;
end