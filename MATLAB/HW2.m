%Author: Aukusti Harris
%Title: COMM.SYS.660 HW2
%16-QAM, Rs of 40 MHz, Oversampling Factor = 8, excess bandwidth 25%
Mqam = 16;
nSymb = 1000;
osf = 8;
roff = 0.25;
span = 8;        %Span of rrc in symbols
nRRC = osf*span; %RRC filter order
hRRC = sqrt(osf)*rcosdesign(roff, span, osf);
in = randi(Mqam, nSymb)-1; %Signal gen
sym = qammod(in, Mqam);    %Symbol mapping
sym_t = sym(:).';          %For plotting symbols
scatterplot(sym_t)
upsamp = [1,zeros(1,osf-1)];%Init zero vector
%Upsample the signal kron essentially repeats each sample but adds osf-1
%zeros behind said sample
symOS = kron(sym, upsamp); 
symOS = symOS(:).';    %reshaping to fit conv function
t = conv(hRRC, symOS); %TX signal (Convoluting singal with the tx filter)
t = t(span*osf+1:end-span*osf);
Rs = 40e6; %Symbol rate 
backOffVals = [10,5,0];
xSat = 1; %Saturation for PA model
p = 2.5;  %Shape parameter 
comp1dB = calc1dB(xSat, p); %Calculate the 1dB point
disp(comp1dB)
%%
%An array for the output signals
outputSignals = cell(length(backOffVals),1);
inputPower = abs(t).^2; %Calculate input power 
figure;
hold on;
for i = 1:length(backOffVals)
    backOffFactor = 10^(-backOffVals(i)/20)*10^(-comp1dB/20); %dB to linear 
    input = t*backOffFactor; %Adjust input signal 
    output = rapp(input, xSat, p); %Run signal through PA model
    outputSignals{i} = output; %Adds output signal to array for later use
    outputPower = abs(output).^2; %Calculate output power
    % AM-AM Plot
    plot(10*log10(inputPower), 10*log10(outputPower));
    xlabel('Input Power (dBm)');
    ylabel('Output Power (dBm)');
    title('AM-AM Conversion');
    grid on;
end
hold off; 
legend('10 dB Backoff', '5 dB Backoff', '0 dB Backoff');
%%
channelWidth = 40e6;
channelSpacing = 50e6;
NFFT = 2^14;
Fs = Rs*osf; %Sampling rate (320 MHz)

for i = 1:length(backOffVals)
    figure;
    %PSD's of input and output
    [PxxInput, fInput] = pwelch(t, [], [], NFFT, Fs); 
    [PxxOutput, fOutput] = pwelch(outputSignals{i}, [], [], NFFT, Fs);
    
    plot(fInput / 1e6, 10*log10(PxxInput), 'b'); 
    hold on;
    plot(fOutput / 1e6, 10*log10(PxxOutput), 'r');
    
    % ACLR evaluation
    aclrValue = calculateACLR(t, outputSignals{i}, Fs, channelWidth, channelSpacing, NFFT);
    title(sprintf('Power Spectrum (Back-off: %d dB, ACLR: %.2f dB)', backOffVals(i), aclrValue));
    xlabel('Frequency (MHz)');
    ylabel('Power Spectral Density (dBm/Hz)');
    legend('Input Signal', 'Output Signal');
    grid on;
end

function yt = rapp(xt, xSat, p)
    [xtTheta, xtRho] = cart2pol(real(xt),imag(xt)); %Carteisan to polar
    fA = xtRho ./ ((1 + (xtRho/xSat).^(2*p)).^(1/(2*p))); %AM-AM conversion
    yt = fA.*exp(1i*xtTheta);
end

function fA = AM_AM_Convesion(A, xSat, p)
    %AM/AM conversion 
    fA = A ./ ((1+(A/xSat).^(2*p)).^(1/(2*p)));
end

function dB1 = calc1dB(xSat, p)
     %1dB comp. point calculation 
     input = linspace(0,2,1000); %input signal 
     output = AM_AM_Convesion(input, xSat, p); %Pass sig. through PA model
     idealOutput = input; %Ideal output for comparison 
     %Find the index where the power is 1 dB below
     compIndex = find(20*log10(output./idealOutput) <= -1, 1);
     compPoint = input(compIndex); %Get value at index
     dB1 = 20*log10(compPoint); %Convert to dB
end


function aclrValue = calculateACLR(inputSignal, outputSignal, Fs, channelWidth, spacing, NFFT)
    % Calculate PSDs using Welch's method
    [PxxInput, fInput] = pwelch(inputSignal, [], [], NFFT, Fs);
    [PxxOutput, fOutput] = pwelch(outputSignal, [], [], NFFT, Fs);
    
    % Calculate total power in the desired band
    desiredBand = [0, channelWidth];
    inputPower = bandpower(PxxInput, fInput, desiredBand,"psd");
    
    % Calculate total power in the adjacent band
    adjacentBand = [channelWidth + spacing, channelWidth + 2 * spacing];
    adjacentPower = bandpower(PxxOutput, fOutput, adjacentBand,"psd");
    
    % ACLR calculation
    aclrValue = 10*log10(inputPower / adjacentPower);
end