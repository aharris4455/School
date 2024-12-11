%% HW 8 and 9 
% 1. ICF
%% Define simulation parameters
NClipIterMax = 20; % number of ICF iterations
PAPRlimit = [3,6,9]; % Target PAPR level
Nbins = 10000; % number of PAPR calculation bins
% 5G: 20 MHz channel, 15 kHz SCS, normal CP
M = 64; % M-ary modulation order
bandwidth = 20;
bOFDM = 2^10; % Number of OFDM symbols
deltaf = 60e3;
Nprb = 24; % Number of active resource blocks
nAct = Nprb*12; % Number of active subcarriers
overSamplingFactor = 4; % oversampling factor
L_OFDM = overSamplingFactor*2^ceil(log2(nAct)); 
L_CP = (L_OFDM/1024)*72; % 72
% OFDM IFFT size
%% OFDM signal generation
% Input data on active subcarries. Shift around DC
% Bit generation
Nbits = nAct; % Total number of active REs
bits = randi([0 M-1],Nbits,bOFDM);
% M-QAM modulation
switch M
    case 1024
        Xact = sqrt(680)^(-1)*qammod(bits,M);
    case 256
        Xact = sqrt(170)^(-1)*qammod(bits,M);
    case 64
        Xact = sqrt(42)^(-1)*qammod(bits,M);
    case 16
        Xact = sqrt(10)^(-1)*qammod(bits,M);
    case 4
        Xact = sqrt(2)^(-1)*qammod(bits,M);
    otherwise
        error('Not allowed')
end
% OFDM modulation, with oversampling, without CP insertion
Bin = 0;
extension = zeros(L_OFDM-nAct, bOFDM);
Xint = circshift([fftshift(Xact, 1); extension], [floor(Bin)-floor(nAct/2) 0]);
activeindices = ismember(0:L_OFDM-1,mod(Bin+[-floor(nAct/2):ceil(nAct/2)-1],L_OFDM)).';
xInt = ifft(Xint); % original OFDM signal
%% PAPR reduction

%%%% Initialization of parameters used in PAPR reduction
it = length(PAPRlimit);
bins = 100;
originals = zeros(it, bins-1);
orig_edges = zeros(it, bins-1);
icf_vals = zeros(it, bins-1);
icf_edges = zeros(it, bins-1);

for idx = 1:it
    x = xInt;
    PAPRlim = PAPRlimit(idx);
    [phi,A] = cart2pol(real(x),imag(x)); % cartesian-to-polar conversion
    clip_level_dB = 10*log10(mean(abs(A(:)).^2)) + PAPRlim;
    clip_level = 10.^(clip_level_dB/20);
    clip_levelInt = clip_level;
    % initial PAPR computation
    Peak_out = abs(x).^2;
    P_out = mean(abs(x(:)).^2);
    disp(['P_out ',num2str(P_out)]);
    PAPRmax = 10*log10(max(max(Peak_out./P_out)));
    Niter = 0;
    disp(['PAPR MAX: ',num2str(PAPRmax)]);
    while (PAPRmax>PAPRlim)&&(Niter<NClipIterMax)
        % clip
        % ENVELOPE CLIPPING:
        [phi,A] = cart2pol(real(x),imag(x)); % cartesian-to-polar conversion
        clip_level_dB = 10*log10(mean(abs(A(:)).^2)) + PAPRlim;
        clip_level = 10.^(clip_level_dB/20);
        A(A>clip_level) = clip_level;
        x = A.*exp(1i*phi);
        % FFT
        clippedX = fft(x);
        % Filtering
        filteredX = icf_filtering(clippedX, activeindices); % <-- YOU SHOULD IMPLEMENT THIS
        % IFFT
        x = ifft(filteredX);
        Peak_out = abs(x).^2;
        P_out = mean(abs(x(:)).^2);
        PAPRmax = 10*log10(max(max(Peak_out./P_out)));
        Niter = Niter+1;
        if Niter > NClipIterMax
            PAPRmax = 0;
        end
    end

    %Initalizes arrays for storing PAPR values
    PAPR_orignal = zeros(1,bOFDM);
    PAPR_ICF  = zeros(1, bOFDM);

    for i = 1:bOFDM
        peak_original = max(abs(xInt(:,i)).^2); %Calculate peak
        avg_original = mean(abs(xInt(:,1)).^2); %Calculate avg
        %PAPR of original signal
        PAPR_orignal(i) = 10*log10(peak_original/avg_original);

        peak_icf = max(abs(x(:,i)).^2); %Peak of icf signal
        avg_icf = mean(abs(x(:,i)).^2); %Avg of icf signal
        %PAPR of icf signal
        PAPR_ICF(i) = 10*log10(peak_icf/avg_icf);
    end

    %CCDF of original signal
    [counts_original, edges_original] = histcounts(PAPR_orignal, 'BinEdges', ...
        linspace(0,max(PAPR_orignal),bins));
    ccdf_original = 1-cumsum(counts_original)/sum(counts_original);
    
    %CCDF of icf signal
    [counts_icf, edges_icf] = histcounts(PAPR_ICF, 'BinEdges', ...
        linspace(0,max(PAPR_ICF), bins));
    ccdf_icf = 1-cumsum(counts_icf)/sum(counts_icf);
    
    %Store results
    originals(idx, :) = ccdf_original;
    orig_edges(idx, :) = edges_original(1:end-1);
    icf_vals(idx, :) = ccdf_icf;
    icf_edges(idx, :) = edges_icf(1:end-1);
end
% figure;
% semilogy(edges_original(1:end-1), ccdf_original, 'b','LineWidth',2);
% hold on;
% semilogy(edges_icf(1:end-1),ccdf_icf,'r','LineWidth',2);
% xlabel('PAPR (dB)');
% ylabel('CCDF');
% legend('Original Signal', 'ICF-Reduced Signal');
% grid on;
% title('PAPR CCDF for Original and ICF-Reduced Signals');

figure;
semilogy(orig_edges(1, :), originals(1, :), 'LineWidth', 2);
hold on;
for idx = 1:it
    semilogy(icf_edges(idx, :), icf_vals(idx, :), 'LineWidth', 2);
    hold on;
end
hold off;
xlabel('PAPR (dB)');
ylabel('CCDF');
grid on;
title('PAPR CCDF for Original and ICF-Reduced Signals');
legend('Orignal Signal','ICF Reduced Signal, Clipping Level: 3 dB', ...
       'ICF Reduced Signal, Clipping Level: 6 dB', ...
       'ICF Reduced Signal, Clipping Level: 9 dB');
 

%% NMSE 
nmse = 10*log10(sum(abs(x(:) - xInt(:)).^2) / sum(abs(xInt(:)).^2));
disp(['NMSE: ', num2str(nmse), ' dB']);
%% PSD 
Fs = deltaf * L_OFDM; %Sampling frequency for PSD
[pxx_original, f_original] = pwelch(xInt(:), hamming(512), ...
                                    256, 4096, Fs, 'centered');
[pxx_icf, ~] = pwelch(x(:), hamming(512), ...
                                    256, 4096, Fs, 'centered');
[pxx_clipped, ~] = pwelch(clippedX(:), hamming(512), ...
                                    256, 4096, Fs, 'centered');
noFilterX = fft(xInt);
noFilterX(abs(noFilterX) > clip_level) = clip_level;
x_nofilter = ifft(noFilterX);
[pxx_noFilter, ~] = pwelch(x_nofilter(:), hamming(512), ...
                                    256, 4096, 1, 'centered');

figure;
plot(f_original, 10*log10(pxx_original), 'b', 'LineWidth', 1.5);
hold on;
plot(f_original, 10*log10(pxx_icf), 'r', 'LineWidth', 1.5);
hold on;
plot(f_original, 10*log10(pxx_noFilter), 'k--', 'LineWidth', 1.5); % PSD of clipped signal
xlabel('Frequency [MHz]');
ylabel('PSD [dB/Hz]');
title('PSD of Signals');
grid on;
hold off;
legend('Original','ICF','Clipped')
%%

function filteredX = icf_filtering(clippedX, activeindicies)
    % 288 active carriers, 2048 total
    % 880 288 880
    % filteredX = clippedX;
    % filteredX(1:880, :) = 0;
    % filteredX(1168:end, :) = 0;
    filteredX = zeros(size(clippedX));
    filteredX(activeindicies, :) = clippedX(activeindicies, :);
end