xk = zeros(32,1)';
N=32
n = 0:N;
xn = cos(n*2*pi*0.0005*62.5);
fn = zeros(N-1,1)';
for k = 0:N-1
   aux = 0;
   for n = 0:N-1
       xm = cos(n*2*pi*62.5*0.0005)* exp(-i*2*pi*n*k/32);
       aux = aux + xm;
   end
   fn(1,k+1) = aux;
end
m = abs(fn);
plot(0:N-1,abs(fn))