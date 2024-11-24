%Aukusti Harris

%PARAMETERS
R_s = 40e6;  %Symbol rate, 40 MHz
T_s = 1/R_s; %Symbol duration
F_s = 1/T_s; %Sampling Freq
M = 16;      %Modulation order, 16-QAM
r = 4;       %Oversampling factor
a = 0.30;    %Roll off factor
N_d = 10;    %RRC filter duration in symbols

N_bits = log2(M)*100e3;     %Number of bits
bits = randi(2,N_bits,1)-1; %Sequence of random bits
%%
%CHANNEL ENCODER
k = 4;
P = [1 0 1;1 1 1; 1 1 0; 0 1 1]; %Parity matrix
G = [ eye(k) P ]; %Generator matrix
%Shifting bits to k length words (blocks)
blocks = reshape(bits,k,[]).';
%Encoding bits 
encoded_bits = mod(blocks*G,2);
encoded_bits = encoded_bits.';
encoded_bits = encoded_bits(:);
%%
%GENERATION OF SYMBOLS
symbols = qammod(encoded_bits, M, "gray", "InputType","bit", ...
           "UnitAveragePower", true,"PlotConstellation",true);
N_symbols = length(symbols);

symbols_upsampled = zeros(size(1:r*N_symbols)); %Upsampling vector

symbols_upsampled(1:r:r*N_symbols) = symbols;   %Upsampled Symbols

b = rcosdesign(a,N_d,r,"sqrt");     %Filter 
st = filter(b,1,symbols_upsampled); %TX Filter
st = st(1+(length(b)-1)/2:end);     %Delay correction
%%
%EYE DIAGRAM
%eyediagram(st,2*r)
%%
% PLOTTING TX FILTER
NFFT = 2^14; %FFT Size
[H,w] = freqz(b,1,NFFT,"whole",F_s); %Calculate freq response
H_shift = fftshift(H);               %Shift freqs
f_shift = linspace(-F_s/2,F_s/2,length(H)); %Freq shift x-axis
figure(2);
plot(f_shift, abs(H_shift));
title('Amplitude Response of TX Filter');
xlabel('Frequency (Hz)');
ylabel('Amplitude');
grid on;
%Plotting the amplitude spectrum of the signal
f = -F_s/2:1/(NFFT*T_s):F_s/2-1/(NFFT*T_s); %Freq Vector
figure(3);
plot(f/1e6, fftshift(abs(fft(st,NFFT))));
title('Amplitude Spectrum of TX Signal');
xlabel('Frequency [MHz]')
ylabel('Amplitude')
grid on
%%
%CHANNEL PROFILE
h = ([-0.478-0.4781*1i, -0.3339+0.8264*1i, 0.0278-0.5302*1i, ...
    0.2233-0.3868*1i, 0.0221+0.3155*1i]);
h_abs = abs(h);              %Find magnitudes of coefficents
[h_max, index] = max(h_abs); %Get strongest tap and index
xt = filter(h,1,st);         %Pass TX signal through channel
%st = st(1+(length(b)-1)/2:end);
xt = xt(1+(length(h)-1)/2:end);
%xt = xt(index+1:end);        %Discard delay

%Random complex gaussian white noise
n = (1/sqrt(2))*(rand(size(xt))+1j*randn(size(xt))); 
P_s = var(st); %Signal power
P_n = var(n);  %Noise power
nsf = sqrt(P_s/P_n/10^(15/10)*(r/(1+a))); %Noise scailing factor
nsf_vector = sqrt(P_s/P_n./10.^(15./10)*(r/(1+a))); %Vector of noise scailing factors
xt = xt + nsf*n; %Noisy signal 

%%
%CHANNEL FREQ RESPONSE 
figure(4);
freqz(h,1,NFFT,'whole',F_s)
title('Amplitude and Phase Respone of the Channel');
%%
%AMPLITUDE SPECTRUM OF RX SIGNAL
f = -F_s/2:1/(NFFT*T_s):F_s/2-1/(NFFT*T_s); %Freq Vector
figure(5);
plot(f/1e6, 20*log10(fftshift(abs(fft(xt,NFFT)))));
title('Amplitude Spectrum of RX Signal');
xlabel('Frequency [MHz]')
ylabel('Amplitude')
grid on
%%
%MATCHED RX FILTER
ft = b;
figure(6);
plot(f/1e6, fftshift(abs(fft(ft, NFFT))));
xlabel('Frequency [MHz]')
ylabel('Amplitude')
title('RX filter f(t)')
grid on; 
rt = filter(ft,1,xt);            %RX filtering
rt = rt(1+(length(ft)-1)/2:end); %Delay Correction
%%
%Eye diagram of the RX signal

%eyediagram(rt,2*r)

%Comments:
%The generated eye diagram is very different to the tx signal
%The eye of the eye diagreram is not open
%%
%DOWNSAMPLING
qk = rt(1:r:end);      %Downsample RX signal
figure(7);
plot(qk(:),'b*')          %Plot RX symbols
grid on 
hold on
plot(symbols,'ro','MarkerFaceColor','r') %Plot original symbols
hold off
legend('RX Samples', 'Original Samples')
title('Original Samples vs RX Samples')
%%
%CHANNEL EQ
beta = 0.0001;             %Step size
eq_len = 31;             %EQ length
c_LMS = zeros(eq_len,1); %EQ coefficients, initializations
num_iter = 10000;         %Number of iterations

for i = 16:length(qk)-15
    rk = flipud(qk(i-15:i+15).');
    Ek(i) = symbols(i) - c_LMS.' * rk; %Using symbols as training symbols
    c_LMS = c_LMS + beta*Ek(i)*conj(rk);
end

%Ploting convergence
figure(8);
plot(abs(Ek));
title('LMS Error Convergence');
xlabel('Iteration');
ylabel('LMS Error');

%Filtering the whole sequence
qk_eq = filter(c_LMS, 1, qk);              %EQ the RX signal
qk_eq = qk_eq(1+(length(c_LMS)-1)/2:end);  %Correct delay

%Channel vs EQ
figure(5); 
%Plotting Channel
[H_channel,f_channel] = freqz(h,1,-R_s/2:R_s/400:R_s/2,R_s);
plot(f_channel/1e6,20*log10(abs(H_channel)),'b');
hold on;
%PLottting LMS EQ
[H_lms,f_lms]=freqz(c_LMS,1,-R_s/2:R_s/400:R_s/2,R_s); 
plot(f_lms/1e6,20*log10(abs(H_lms)),'r');
hold on;
%Plotting channel and EQ combined
tot = conv(c_LMS,h);
[H_comb,f_comb]=freqz(tot,1,-R_s/2:R_s/400:R_s/2,R_s); 
plot(f_comb/1e6,20*log10(abs(H_comb)),'g');
grid on;
legend('Channel','LMS EQ', 'Total');
xlabel('Frequency (MHz)')
ylabel('Magnitude (dB)')
%Magnitude and phase response of the EQ
figure(6);
freqz(c_LMS,1,-R_s/2:R_s/400:R_s/2,R_s);

%Constellations 
figure(7);
hold on;
plot(rt,'r*');
plot(qk_eq,'b*');
plot(symbols,'g*');
legend('RX Symbols','Equalized Symbols','Original Symbols')
title('Symbols before and after equalization')
xlabel('Re')
ylabel('Im')
%%
%SYMBOL DETECTION
%qamdemod demodulates the symbols and saves them as bits using 
%gray decoding
detected_bits = qamdemod(qk_eq, M, 'gray', 'OutputType', 'bit');
detected_bits = detected_bits.';
detected_bits = detected_bits(:);
%
%PUT CHANNEL DECODER HERE
n = 7;
H = [ P.' eye(3) ]; %Parity check matrix
%Discarding bits that are not a multiple of 7
detected_bits = detected_bits(1:floor(length(detected_bits)/n)*n); 
%Reshape into codewords 
detected_bits_reshaped = reshape(detected_bits, n, []).';
decoded_bits = [];
for i = 1:size(detected_bits_reshaped,1)
    codeword = detected_bits_reshaped(i, :);
    syndrome = mod(codeword*H',2);
    [~, error_pos] = ismember(syndrome, H.','rows');
    if error_pos ~= 0
        codeword(error_pos) = mod(codeword(error_pos),2);
    end
    decoded_bits = [decoded_bits, codeword(1:k)];
end

%%
%BER CALCULATION
bit_error = sum(bits(1:length(decoded_bits.')) ~= decoded_bits.');
ber = bit_error /  length(decoded_bits);
disp(['Bit Error Rate: ', num2str(ber)]);
