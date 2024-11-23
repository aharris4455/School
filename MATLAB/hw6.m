%HW6
%TODO:
%AWGN *
%QPSK *
%100 samp/sym * 
%RRC Puslse shaping * 
%Timing offset = +- half symbol interval *
%Phase offset = +- 90 deg * 
%RX matched filtering
%Calculate DA (data-aided) loglikelyhood 

Mqam = 4; % Modulation order
nSymb = 100; % Number of symbols per estimation block
osf = 100; % Oversampling factor
roff = 0.5; % Roll-off of RRC filter
span = 8; % Span of the RRC filter (in symbols)
nRRC = osf*span; % RRC filter order
%toff 0->10
toff = 10; % Timing offset in samples, -osf/2 < toff < osf/2
% Fractional timing offset = toff/osf
poff = 30; %Phase offset, degrees
% RRC filter:
hRRC = sqrt(osf)*rcosdesign(roff, span, osf);
% Input data % upsampling/interpolation:
in = randi(Mqam,1,nSymb)-1;
in = qammod(in,Mqam); % QAM symbols
upsamp = [zeros(1,toff+osf/2),1,zeros(1,osf/2-toff-1)]; % Notice the osf/2
% extra zeroes in the beginning. This is done to allow for
% negative time offsets. Take this into account when interpreting the
% estimated delay!
inOS = kron(in,upsamp);
t = conv(hRRC,inOS); % This is the generated TX signal
% Note: After RRC filtering in RX, the received signal contains
% impulse response tails of nRRC samples on both sides. Remove these
% before doing any other RX processing.
n = (1/sqrt(2))*(rand(size(t))+1j*rand(size(t))); %Complex AWGN
t_n = t + n; %Noisy signal

%Matched RX Filter 
rx_ft = hRRC;
rx = filter(rx_ft,1,t_n); %RX Filtering
rx = rx(1+(length(rx_ft)-1)/2:end); %Delay correction
%%

%% 
%ChatGPT spaghetti code: 
tauRange = -osf/2:1:osf/2;
phiRange = -90:1:90; % Phase offset range in degrees
L = zeros(length(tauRange), length(phiRange)); % Initialize log-likelihood matrix

% Define transmitted symbols (data-aided, assuming perfect knowledge of transmitted symbols)
txSymbols = in;

% Trim RX signal to account for RRC tails
rxTrim = rx(nRRC:end-nRRC); % Remove RRC filter tails

% Loop over possible timing and phase offsets
for i = 1:length(tauRange)
    tau = tauRange(i); % Current timing offset in samples

    % Apply fractional delay (interpolation for timing offset)
    rxInterp = resample(rxTrim, 1, osf, tau);

    for j = 1:length(phiRange)
        phi = deg2rad(phiRange(j)); % Current phase offset in radians

        % Compensate for phase offset
        rxCorrected = rxInterp .* exp(-1j * phi);

        % Calculate log-likelihood
        L(i, j) = real(sum(conj(rxCorrected) * txSymbols));
    end
end

% Find maximum log-likelihood and corresponding offsets
[maxL, idx] = max(L(:));
[iMax, jMax] = ind2sub(size(L), idx);
estimatedTau = tauRange(iMax);
estimatedPhi = phiRange(jMax);

% Display estimated offsets
fprintf('Estimated Timing Offset: %.2f samples\n', estimatedTau);
fprintf('Estimated Phase Offset: %.2f degrees\n', estimatedPhi);

% Plot Log-Likelihood Function
figure;
imagesc(phiRange, tauRange, L);
colorbar;
xlabel('Phase Offset (degrees)');
ylabel('Timing Offset (samples)');
title('DA Log-Likelihood Function');