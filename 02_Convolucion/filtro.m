sys = tf([1],[1,130*2*pi,700*700*2*pi]);
sys1 = tf([1],[1,70*2*pi,1220*1220*2*pi]);
sys2 = tf([1],[1,160*2*pi,2600*2600*2*pi]);

sigma(sys)
hold
sigma(sys1)
sigma(sys2)
%sigma(sys*sys1*sys2)
grid