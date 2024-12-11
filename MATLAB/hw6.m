%HW6
%Aukusti Harris 
clear all;
Mqam = 4;        % Modulation order (QPSK)
nSymb = 100;     % Number of symbols per estimation block
osf = 100;       % Oversampling factor
roff = 0.5;      % Roll-off of RRC filter
span = 8;        % Span of the RRC filter (in symbols)
nRRC = osf * span; % RRC filter order
SNR_dB = [0 10 20]; % SNR values in dB
numIterations = 1; % Number of iterations

% Arrays to store errors
timingErrors = zeros(1, numIterations);
phaseErrors = zeros(1, numIterations);


for iter = 1:numIterations
    % Random timing and phase offsets for each iteration
    toff = randi([-osf/2, osf/2]); % Random timing offset
    poff = randi([-90, 90]);       % Random phase offset, in degrees
    disp(['Timing offset: ', num2str(toff)]);
    disp(['Phase offset: ', num2str(poff)]);
    % Root Raised Cosine (RRC) filter
    hRRC = sqrt(osf) * rcosdesign(roff, span, osf);
    in = randi(Mqam, 1, nSymb) - 1;
    in = qammod(in, Mqam); % Generate QPSK symbols
    upsamp = [zeros(1, toff + osf/2), 1, zeros(1, osf/2 - toff - 1)]; % Time offset padding
    inOS = kron(in, upsamp); % Oversample input symbols
    t = conv(hRRC, inOS);    % Transmitted signal after RRC filtering

    % Add phase offset to the transmitted signal
    t = t * exp(1j * deg2rad(poff));

    % Add AWGN for a given SNR level
    signal_power = mean(abs(t).^2); %Signal power in time domain
    noise_power = signal_power/(osf*10^(SNR_dB(3)/10));
    %noise_power = 10^(-SNR_dB(3) / 10); 
    noise = sqrt(noise_power / 2) * (randn(size(t)) + 1j * randn(size(t)));
    t_n = t + noise; % Signal with added noise

    % Matched RX Filter
    rx_ft = hRRC;
    rx = filter(rx_ft, 1, t_n);   % RX Filtering (Matched filter output)
    rx = rx(1 + (length(rx_ft) - 1):end); % Delay correction
    %rx = downsample(rx, osf);     % Downsample received signal
    N_est_sym = length(rx);       % Number of estimated symbols

    % Timing and phase offsets for log-likelihood calculation
    timingOffsets = linspace(-osf/2, osf/2, 200); % In symbols
    phaseOffsets = linspace(-pi/2, pi/2, 200);    % In radians
    L = zeros(length(timingOffsets), length(phaseOffsets));
    tau = max(sum(conj(in(1:nSymb)) .* rx(1:nSymb)));
    theta = imag(tau);
    disp(['Tau: ', num2str(tau)]);
    disp(['Theta: ', num2str(theta)]);
    % Calculate DA log-likelihood for different offsets
    % for k = 1:length(timingOffsets)
    %     for m = 1:length(phaseOffsets)
    %         timingOffset = timingOffsets(k);
    %         phaseOffset = phaseOffsets(m);
    %         phaseTerm = exp(-1j * phaseOffset);
    %         ll = real(phaseTerm * sum(conj(in(1:100)) .* rx(1:100)));
    %         L(k, m) = ll;
    %     end
    % end
    
    % Find estimated offsets that maximize the log-likelihood
    [~, maxIdx] = max(L(:));
    [maxRow, maxCol] = ind2sub(size(L), maxIdx);
    estimatedTimingOffset = timingOffsets(maxCol);
    estimatedPhaseOffset = phaseOffsets(maxCol);
    disp(['Estimated Timing Offset: ', num2str(estimatedTimingOffset)]);
    disp(['Estimated Phase Offset: ', num2str(rad2deg(estimatedPhaseOffset)), ' degrees']);
    % Calculate errors
    timingEstError = abs(estimatedTimingOffset - toff);
    phaseEstError = abs(estimatedPhaseOffset - deg2rad(poff));

    % Store errors for plotting
    timingErrors(iter) = timingEstError;
    phaseErrors(iter) = phaseEstError;
end

% % Plot timing and phase errors
% figure;
% subplot(2,1,1);
% plot(1:numIterations, timingErrors, 'b');
% xlabel('Iteration');
% ylabel('Timing Error');
% title('Timing Estimation Error Over 100 Iterations');
% 
% subplot(2,1,2);
% plot(1:numIterations, rad2deg(phaseErrors), 'r');
% xlabel('Iteration');
% ylabel('Phase Error (degrees)');
% title('Phase Estimation Error Over 100 Iterations');
