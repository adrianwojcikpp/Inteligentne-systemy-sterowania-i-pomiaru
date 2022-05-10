clear all; close all;

A = [     0        1        0        0;
      157.8        0        0        0;
          0        0        0        1;
    -0.7171        0        0        0];

B = [     0; 
     -14.63; 
         0; 
    0.9756];
 
C = eye(size(A));
D = zeros(size(B));


if rank(ctrb(A,B)) == length(A)
    disp('System jest sterowalny');
else
    disp('System nie jest sterowalny');
end

if rank(obsv(A,C)) == length(A)
    disp('System jest obserwowalny');
else
    disp('System nie jest obserowalny');
end

poleRef = [-2, -2, -1+1i, -1-1i];

disp('Lokowanie biegunów - bieguny referencyjne: '); disp(sort(poleRef)');

K = acker(A,B,poleRef);

poleResult = eig(A-B*K)';

disp('Lokowanie biegunów - bieguny wynikowe: '); disp(sort(poleResult)');

K