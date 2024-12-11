%% HW7
mQAM = 64;       %Modulation order
nSymb = 1000;    %Number of symbols
osf = 8;         %Oversampling factor
roff = 0.25;     %Roll off for RRC 
span = 16;       %Span of RRC filter (symbols)
nRRC = osf*span; %RRC Filter order
%Rapp model params
xSat = 1; %Saturation amplitude
p = 2.5;  %Smoothness param
ord = 5; %Order for polynomial model 
%Design filter
hRRC = sqrt(osf)*rcosdesign(roff, span, osf);
%Generate signal and upsample/interpolation
in = randi(mQAM,1,nSymb)-1;
sym = qammod(in, mQAM);
upsamp = [1,zeros(1,osf-1)];
symOS = kron(sym,upsamp);
t = conv(hRRC,symOS); %tx signal 
db1 = calc1dB(xSat, p); %Calculate the 1 dB point
disp(['1 dB compression point: ', num2str(db1), ' dBm']);
%Current input power in dBm
input_power = 10 * log10(mean(abs(t).^2)) + 30; 
disp(['Current input power: ', num2str(input_power), ' dBm']);
desierdPower = db1 - input_power; %Calculate desired power level
scaling_factor = sqrt(10^(desierdPower/10)); %Scaling factor in linear scale
t_scaled = t*scaling_factor;
%Adjust tx signal power
adjustedPower_dBm = 10 * log10(mean(abs(t_scaled).^2)) + 30; 
disp(['Adjusted Power: ', num2str(adjustedPower_dBm), ' dBm']);

t_PA = rapp(t_scaled, xSat, p); %Pass the signal through the PA 

p_coeff = polyfit(t_scaled, t_PA, ord);       %Find polynomial coeffecients
pa_model_output = polyval(p_coeff, t_scaled); %Get the model output signal

%Calculate the NMSE
nmse = mean(abs(t_PA - pa_model_output).^2)/mean(abs(t_PA).^2);
nmse_db = 10*log10(nmse); %Convert to dB
disp(['NMSE (dB): ', num2str(nmse_db)]);
disp('Estimated Polynomial Coefficients:');
disp(p_coeff);

%Plot the figures
figure;
[pxx_orig, f] = pwelch(t_scaled, [], [], [], 'centered');
plot(f, 10*log10(pxx_orig), 'DisplayName', 'Original Signal','Color','c');
hold on
[pxx_PA, f] = pwelch(t_PA, [], [], [], 'centered');
plot(f, 10*log10(pxx_PA), 'DisplayName', 'DUT Output','Color','r');
[pxx_model, f] = pwelch(pa_model_output, [], [], [], 'centered');
plot(f, 10*log10(pxx_model), 'DisplayName', 'Polynomial Model Output','Color','b');
grid on
legend;
title('Spectra Comparison');
hold off;
%% Optinal 
% Params for Saleh Model
a_A = 0.9;
a_P = -0.35;
b_A = 0.29;
b_P = 1.0;
e = -0.36; 
t_Saleh = salehModel(t_scaled,a_A,b_A,a_P,b_P,e);

figure;
for n = 1:2:11
    p_coeff = polyfit(t_scaled, t_Saleh, n); %Coefficents
    model_output = polyval(p_coeff,t_scaled); %Model output
    %NMSE Calculation
    nmse = mean(abs(t_Saleh - model_output).^2)/mean(abs(t_Saleh).^2);
    nmse_db = 10*log10(nmse); %Convert to dB
    plot(n,nmse_db, '*','DisplayName', ['Order ', num2str(n)])
    disp(['NMSE (dB) for order ', num2str(n), ': ', num2str(nmse_db)]);
    hold on;
end 
grid on; 
xlabel('Polynomial Order'); 
ylabel('NMSE (dB)'); 
title('NMSE vs. Polynomial Order'); 
legend show; 
hold off;

% From the plot we can see that when the order increases, the NMSE decreases
% Between orders 3 and 5 we can see a steep fall off in NMSE. 

%%
%Orders for backoff comparison
ord1 = 3;
ord2 = 9;
%Calcualte 1dB point of the Saleh Model
db1_saleh = calc1dB_saleh(a_A,b_A,a_P,b_P,e);
disp(['1 dB point: ', num2str(db1_saleh)])
%Current power of the input signal in W
current_power = 10^((input_power-30)/10);
figure;
for backoff = 0:2:10
    fprintf('\n');
    fprintf('*******************************\n');
    fprintf('  Processing Backoff: %d dB  \n', backoff);
    fprintf('*******************************\n');

    desiredPower = db1_saleh - backoff; %Desired power of input signal
    disp(['Desired power: ', num2str(desiredPower)]);
    dp_w = 10^((desiredPower-30)/10); %Desired power in watts
    scaling_factor = sqrt(dp_w/current_power); %Scaling factor
    t_scaled = t*scaling_factor;
    %Adjust tx signal power
    adjustedPower_dBm = 10 * log10(mean(abs(t_scaled).^2)) + 30; 
    disp(['Adjusted power: ', num2str(adjustedPower_dBm),' dBm'])
    %For each backoff calculate NMSE and plot
    %Pass signal through model
    t_Saleh = salehModel(t_scaled, a_A, b_A, a_P, b_P, e); 
    
    %Calcualteing coefficents
    p_coeff_1 = polyfit(t_scaled, t_Saleh, ord1);
    disp(['Estimaited polynomial coefficents for order ',num2str(ord1)])
    disp(p_coeff_1)
    p_coeff_2 = polyfit(t_scaled, t_Saleh, ord2);
    disp(['Estimaited polynomial coefficents for order ',num2str(ord2)])
    disp(p_coeff_2)
    
    %Model outputs 
    model_out_1 = polyval(p_coeff_1, t_scaled);
    model_out_2 = polyval(p_coeff_2, t_scaled);

    %NMSE calcualtion
    nmse_1 = mean(abs(t_Saleh - model_out_1).^2)/mean(abs(t_Saleh).^2);
    nmse_2 = mean(abs(t_Saleh - model_out_2).^2)/mean(abs(t_Saleh).^2);
    
    %Convert to dB
    nmse_db_1 = 10*log10(nmse_1); %Convert to dB
    nmse_db_2 = 10*log10(nmse_2); %Convert to dB
    
    plot(backoff,nmse_db_1, 'ro','DisplayName', ['Order ', num2str(ord1)])
    plot(backoff,nmse_db_2, 'bx','DisplayName', ['Order ', num2str(ord2)])
    hold on;
end
grid on;
xlabel('Backoff (dB)')
ylabel('NMSE (dB)')
title('NMSE vs Backoff')
legend show;
hold off;

% From the outputs it seems that the coeffecients related to the Saleh model
% have more values in the imaginary portion of the coefficents. While there
% is some in the Rapp model coefficents, there sees to be "more going on" 
% with the coefficents of the Saleh model. From the plot we can see that
% NMSE has a parabolic effect ie values at 0 dB and 10 dB are less than 
% values at 6 dB for example. 

function yt = salehModel(xt, a_A, b_A, a_P, b_P, e)
    %Function that passes a signal through a Saleh model PA
    [xtTheta, xtRho] = cart2pol(real(xt), imag(xt));
    fA = a_A.*abs(xtRho)/(sqrt(1+b_A.*abs(xtRho).^3));
    fP = a_P./(nthroot(1+b_P.*abs(xt).^4,3)) - e;
    yt = fA.*exp(1j*(fP+xtTheta));
end

function yt = rapp(xt, xSat, p)
    %Function that passes a signal through a Rapp model PA
    [xtTheta, xtRho] = cart2pol(real(xt),imag(xt)); %Carteisan to polar
    fA = abs(xtRho) ./ ((1 + (abs(xtRho)/xSat).^(2*p)).^(1/(2*p))); %AM-AM conversion
    yt = fA.*exp(1i*xtTheta);
end

function fA = AM_AM_Convesion(A, xSat, p)
    %AM/AM conversion 
    fA = abs(A) ./ ((1+(abs(A)/xSat).^(2*p)).^(1/(2*p)));
end

function dB1 = calc1dB_saleh(a_A, b_A, a_P, b_P, e)
     %1dB comp. point calculation for the Saleh model
     input = linspace(-100,2,100); %input signal 
     output = salehModel(input,a_A,b_A,a_P,b_P,e); %Pass sig. through PA model
     idealOutput = input; %Ideal output for comparison 
     %Find the index where the power is 1 dB below
     compIndex = find(20*log10(output./idealOutput) <= -1, 1);
     compPoint = input(compIndex); %Get value at index
     dB1 = 20*log10(compPoint); %Convert to dB
end

function dB1 = calc1dB(xSat, p)
     %1dB comp. point calculation, Rapp model
     input = linspace(-100,2,100); %input signal 
     output = AM_AM_Convesion(input, xSat, p); %Pass sig. through PA model
     idealOutput = input; %Ideal output for comparison 
     %Find the index where the power is 1 dB below
     compIndex = find(20*log10(output./idealOutput) <= -1, 1);
     compPoint = input(compIndex); %Get value at index
     dB1 = 20*log10(compPoint); %Convert to dB
end

